#include "MsgService.h"

char data;

void setup(){ 
  MsgService.init();
}

void loop(){
  //if (MsgService.isMsgAvailable()){
    MsgService.sendMsg("NORMAL");
    MsgService.sendMsg("ON");
    delay(2000);
    MsgService.sendMsg("PREALARM");
    MsgService.sendMsg("ON");
    delay(3000);
    MsgService.sendMsg("ALARM");
    MsgService.sendMsg("OFF");
    delay(2000);

    MsgService.sendMsg("12");
    MsgService.sendMsg("2");
    MsgService.sendMsg("20");
    MsgService.sendMsg("6");
    delay(2000);
  //}
};