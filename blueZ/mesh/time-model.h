/*
 * Created By: Ryan Canty
 * LEDVANCE
 * 3/15/18
*/

#define TIME_CLIENT_MODEL_ID        	0x1202

#define OP_TIME_GET             0x8237
#define OP_TIME_SET				0x5C
#define OP_TIME_STATUS			0x5D


void lighting_set_node(const char *args);
bool time_client_init(uint8_t ele);
