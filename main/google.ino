#include "google.h"

AdafruitIO_Feed *counter = io.feed("LedControlFeed"); //LedControlFeed 를 접속할 경로로 설정한다.

void google_setup() {

  io.connect(); //Adafruit 서버에 커넥트

  counter->onMessage(handleMessage);

  // it's own, io.mqttStatus() < AIO_CONNECTED
  while (io.mqttStatus() != AIO_CONNECTED) { 
    //연결상태가 되면 .을 입력하지 않고 while 문을 벗어남
    delay(500);
  }

  counter->get(); //서버에서 값을 가져온다.

}

void handleMessage(AdafruitIO_Data *data) {

  int state = data->toInt();
  if(state == 0) {
    myDFPlayer.play(2);
  }
  else if(state == 1) {
    myDFPlayer.play(3);
  }
  else {
    myDFPlayer.play(4);
  }
}
