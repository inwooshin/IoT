

#include "config.h"
#include <Arduino.h>
#define delayPin D2
AdafruitIO_Feed *counter = io.feed("LedControlFeed");

void setup() {

  Serial.begin(115200);

  pinMode(delayPin, OUTPUT);
  
  while (! Serial);
  
  Serial.print("Connecting to Adafruit IO");

  io.connect();

  counter->onMessage(handleMessage);

  while (io.mqttStatus() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  counter->get();

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  io.run();

}

void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  Serial.println(data->value());

  int state = data->toInt();
  //김치볶음밥 0번, 김치찌개 1번, 된장찌개 2번
  if(state == 0) {
    Serial.print("김치볶음밥 메뉴 안내 실행!\n");
    }
  else if(state == 1) {
    Serial.print("김치찌개 메뉴 안내 실행!\n");
    }
  else{
    Serial.print("된장찌개 메뉴 안내 실행!\n");
  }
}
