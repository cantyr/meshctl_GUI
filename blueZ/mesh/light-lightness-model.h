/*
 * Created By: Ryan Canty
 * LEDVANCE
 * 3/15/18
*/

#define LIGHTNESS_SERVER_MODEL_ID	0x1300
#define LIGHTNESS_CLIENT_MODEL_ID	0x1302

#define OP_LIGHTNESS_GET			0x824B
#define OP_LIGHTNESS_SET			0x824C
#define OP_LIGHTNESS_SET_UNACK		0x824D
#define OP_LIGHTNESS_STATUS			0x824E

void lighting_set_node(const char *args);
bool lightness_client_init(uint8_t ele);
