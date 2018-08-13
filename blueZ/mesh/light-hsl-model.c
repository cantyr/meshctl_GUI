#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdbool.h>
#include <sys/uio.h>
#include <wordexp.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <glib.h>

#include "src/shared/shell.h"
#include "src/shared/util.h"
#include "mesh/mesh-net.h"
#include "mesh/keys.h"
#include "mesh/net.h"
#include "mesh/node.h"
#include "mesh/prov-db.h"
#include "mesh/util.h"
#include "mesh/light-hsl-model.h"

static uint8_t trans_id;
static uint16_t hsl_app_idx = APP_IDX_INVALID;

static int client_bind(uint16_t app_idx, int action)
{
	if (action == ACTION_ADD) {
		if (hsl_app_idx != APP_IDX_INVALID) {
			return MESH_STATUS_INSUFF_RESOURCES;
		} else {
			hsl_app_idx = app_idx;
			printf("HSL client model: new binding %4.4x\n",
								app_idx);
		}
	} else {
		if (hsl_app_idx == app_idx)
			hsl_app_idx = APP_IDX_INVALID;
	}
	return MESH_STATUS_SUCCESS;
}

static void print_remaining_time(uint8_t remaining_time)
{
	uint8_t step = (remaining_time & 0xc0) >> 6;
	uint8_t count = remaining_time & 0x3f;
	int secs = 0, msecs = 0, minutes = 0, hours = 0;

	switch (step) {
	case 0:
		msecs = 100 * count;
		secs = msecs / 1000;
		msecs -= (secs * 1000);
		break;
	case 1:
		secs = 1 * count;
		minutes = secs / 60;
		secs -= (minutes * 60);
		break;

	case 2:
		secs = 10 * count;
		minutes = secs / 60;
		secs -= (minutes * 60);
		break;
	case 3:
		minutes = 10 * count;
		hours = minutes / 60;
		minutes -= (hours * 60);
		break;

	default:
		break;
	}

	printf("\n\t\tRemaining time: %d hrs %d mins %d secs %d msecs\n",
						hours, minutes, secs, msecs);

}

static bool client_msg_recvd(uint16_t src, uint8_t *data,
				uint16_t len, void *user_data)
{
	uint32_t opcode;
	int n;

	if (mesh_opcode_get(data, len, &opcode, &n)) {
		len -= n;
		data += n;
	} else
		return false;

	printf("HSL Model Message received (%d) opcode %x\n",
								len, opcode);
	print_byte_array("\t",data, len);

	switch (opcode & ~OP_UNRELIABLE) {
	default:
		return false;

	case OP_LIGHT_HSL_STATUS:
		if (len != 1 && len != 3)
			break;

		printf("Node %4.4x: Off Status present = %s",
						src, data[0] ? "ON" : "OFF");

		if (len == 3) {
			printf(", target = %s", data[1] ? "ON" : "OFF");
			print_remaining_time(data[2]);
		} else
			printf("\n");
		break;
	}

	return true;
}


static uint32_t target;
static uint32_t parms[8];

static uint32_t read_input_parameters(int argc, char *argv[])
{
	uint32_t i;

	if (!argc)
		return 0;

	--argc;
	++argv;

	if (!argc || argv[0][0] == '\0')
		return 0;

	memset(parms, 0xff, sizeof(parms));

	for (i = 0; i < sizeof(parms)/sizeof(parms[0]) && i < (unsigned) argc;
									i++) {
		sscanf(argv[i], "%d", &parms[i]);
		if (parms[i] == 0xffffffff)
			break;
	}

	return i;
}

static void cmd_set_node(int argc, char *argv[])
{
	uint32_t dst;
	char *end;

	dst = strtol(argv[1], &end, 16);
	if (end != (argv[1] + 4)) {
		printf("Bad unicast address %s: "
				"expected format 4 digit hex\n", argv[1]);
		target = UNASSIGNED_ADDRESS;
	} else {
		printf("Controlling HSL for node %4.4x\n", dst);
		target = dst;
		set_menu_prompt("HSL", argv[1]);
	}
}

static bool send_cmd(uint8_t *buf, uint16_t len)
{
	struct mesh_node *node = node_get_local_node();
	uint8_t ttl;

	if(!node)
		return false;

	ttl = node_get_default_ttl(node);

	return net_access_layer_send(ttl, node_get_primary(node),
					target, hsl_app_idx, buf, len);
}

static void cmd_get_status(int argc, char *argv[])
{
	uint16_t n;
	uint8_t msg[32];
	struct mesh_node *node;

	if (IS_UNASSIGNED(target)) {
		printf("Destination not set\n");
		return;
	}

	node = node_find_by_addr(target);

	if (!node)
		return;

	n = mesh_opcode_set(OP_LIGHT_HSL_GET, msg);

	if (!send_cmd(msg, n))
		printf("Failed to send \"HSL GET\"\n");
}

static void cmd_set(int argc, char *argv[])
{
	uint16_t n;
	uint8_t msg[32];
    uint8_t *hsl;
	struct mesh_node *node;

	if (IS_UNASSIGNED(target)) {
		printf("Destination not set\n");
		return;
	}

	node = node_find_by_addr(target);

	if (!node)
		return;

	if ((read_input_parameters(argc, argv) != 1) &&
                                (parms[0] > 360 || parms[0] < 0) &&
                                (parms[1] > 100 || parms[1] < 0) &&
                                (parms[2] > 100 || parms[2] < 0)) {
		printf("Bad arguments: Expecting \"<0-360> <0-100> <0-100> <0-64> <0-1280>\"\n");
		return;
	}

	n = mesh_opcode_set(OP_LIGHT_HSL_SET, msg); 
        
        
        //Lightness - Hue - Sat - TransID - TT - Delay
        hsl = (uint8_t *)&parms[2];
		msg[n++] = *hsl++;
		msg[n++] = *hsl;
        hsl = (uint8_t *)&parms[0];
		msg[n++] = *hsl++;
		msg[n++] = *hsl;
        hsl = (uint8_t *)&parms[1];
		msg[n++] = *hsl++;
		msg[n++] = *hsl;
        msg[n++] = trans_id++;
        hsl = (uint8_t *)&parms[3];
        msg[n++] = *hsl;
        parms[4] /= 5;
        hsl = (uint8_t *)&parms[4];
        msg[n++] = *hsl;
        
	if (!send_cmd(msg, n))
		printf("Failed to send \"HSL SET\"\n");

}

static struct mesh_model_ops client_cbs = {
	client_msg_recvd,
	client_bind,
	NULL,
	NULL
};

bool hsl_client_init(uint8_t ele)
{
	if (!node_local_model_register(ele, HSL_CLIENT_MODEL_ID,
					&client_cbs, NULL))
		return false;

	return true;
}