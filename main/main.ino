#include "google.h"
#include "mux.h"
#include "speaker.h"
#include "tft.h"

#define USE_SD_CARD //sd 카드를 사용함
#define SD_CS    D8 // SD card select pin
#define TFT_CS   D3 // TFT select pin
#define TFT_DC   D1 // TFT display/command pin
#define TFT_RST  D2 // Or set to -1 and connect to Arduino RESET pin

int push = 1;
String s[6] = {"영점", "아래", "오른쪽", "가운데", "왼쪽", "위쪽"};

ICACHE_RAM_ATTR void myISR(){ //인터럽트 시 호출될 함수
  myDFPlayer.stop(); //mp3 플레이 상태에서 멈춰준다.
}

int vol = 18;

void setup(){
  Serial.begin(9600);

  //google_setup();
  //dft_setup();
  //mux_button_setup();
  tft_setup();

  tftOn("/init.bmp");
}

void loop() {
  /*
  int button1 = digitalRead(2);
  int button2 = digitalRead(10);

     if (button1 == LOW && button2 == HIGH)
     {
      count = count - 1;
      if(count <= 0) count = 0;
      Serial.println(count);
      }
     else if (button2 == LOW && button1 == HIGH)
     {
      count = count + 1;
      if(count >= 2) count = 2;
      Serial.println(count);
      }
      else if(button1 == HIGH && button2 == HIGH) {
        Serial.print("tq : ");
        Serial.println(count);
      }
      
     if(count == 0){ 
        tftOn("/menu_1.bmp");
        }
      else if(count == 1){
        tftOn("/memu_2.bmp"); 
        }
      else {tftOn("/menu_3.bmp");}
      */
}
