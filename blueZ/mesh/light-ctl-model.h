/*
 * Created By: Ryan Canty
 * LEDVANCE
 * 3/15/18
*/

#define CTL_CLIENT_MODEL_ID                     0x1305

#define OP_LIGHT_CTL_GET			0x825D
#define OP_LIGHT_CTL_SET			0x825E
#define OP_LIGHT_CTL_STATUS			0x8260


void lighting_set_node(const char *args);
bool ctl_client_init(uint8_t ele);
