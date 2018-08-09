/*
 * Created By: Ryan Canty
 * LEDVANCE
 * 4/24/18
*/

#define LEVEL_SERVER_MODEL_ID	0x1002
#define LEVEL_CLIENT_MODEL_ID	0x1003

#define OP_LEVEL_GET			0x8205
#define OP_LEVEL_SET			0x8206
#define OP_LEVEL_SET_UNACK		0x8207
#define OP_LEVEL_STATUS			0x8208

void lighting_set_node(const char *args);
bool level_client_init(uint8_t ele);
