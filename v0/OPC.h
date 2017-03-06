
#define MAX_DATA_LEN 65535

class OPCMessage {
public:
  uint8_t chan;
  uint8_t cmd;
  uint16_t len;
  uint8_t data[MAX_DATA_LEN];

  OPCMessage(){
    chan = 0;
    cmd  = 0;
    len  = 0;
    memset(data, 0, MAX_DATA_LEN);
  }

  uint8_t parse(uint8_t *msg){
    chan = msg[0];
    cmd = msg[1];
    len = (msg[2] << 8) | msg[3];
    memcpy(data, &(msg[4]), len);
  }

};
