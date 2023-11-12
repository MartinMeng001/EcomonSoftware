#include "Logic4Input.h"

Logic4Input::Logic4Input(){
  
}
// 1= on event, 2= off event, 0=no event
int Logic4Input::setStatus(int status){
  if(_status&0x0F == status){
    return checkEvent();
  }else{
    _status=status;
    time4status = millis();
  }
  return 0;
}
int Logic4Input::checkEvent(){
  uint32_t now=millis();
  if(now<time4status) {
    time4status=now;
    return 0;
  }else{
    if(now-time4status>50){
      if(_status&0x0F == 0){
        _status|=0x80;
        if(_status&0x0F == 1)return 1;
        else return 2;
      }
    }
  }
  return 0;
}
