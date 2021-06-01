#include <Adafruit_GFX.h>         
#include <Adafruit_ST7735.h>      
#include <SdFat.h>                
#include <Adafruit_SPIFlash.h>    
#include <Adafruit_ImageReader.h> 

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
 
SoftwareSerial mySoftwareSerial(D9, D2); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

#define USE_SD_CARD //sd 카드를 사용함
#define SD_CS    D8 // SD card select pin
#define TFT_CS   D3 // TFT select pin
#define TFT_DC   D1 // TFT display/command pin
#define TFT_RST  -1 // Or set to -1 and connect to Arduino RESET pin

SdFat SD;         // SD 클래스 객체를 생성
Adafruit_ImageReader reader(SD); //sd 카드를 읽어오기 위한 read 객체 생성

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST); //각 tft 핀을 설정한다.
Adafruit_Image img;        // 메모리에 올려줄 이미지 파일을 load 하는 객체
ImageReturnCode stat;

void tftOn(char* bmpName){        //tft에 bmp파일을 출력하는 함수.
  reader.loadBMP(bmpName, img);
  img.draw(tft,0,0);
}

void tftOff(){           //tft화면을 초기화 하는 함수.
  tft.fillScreen(0);     // and clear screen
}

void setup(void) { 

  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  while(!Serial);

  tft.initR(INITR_BLACKTAB); //tft 의 초기 설정을

  if(!SD.begin(SD_CS, SD_SCK_MHZ(10))) { // sd 카드 연결을 시작하고, 10MHz 로 통신한다.
    Serial.println("SD begin() failed");
    delay(1000); //sd 카드를 읽어오지 못할 경우 진행이 안되도록 한다.
  }

  tft.fillScreen(0);

  //초기 사진
  tftOn("/init.bmp");

    if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("Unable to begin:");
    Serial.println("1.Please recheck the connection!");
    Serial.println("2.Please insert the SD card!");
    while(!myDFPlayer.begin(mySoftwareSerial)){
      Serial.println("아직도 안됨 ㅠ");
      delay(200); 
    }
  }
  Serial.println("DFPlayer Mini online.");
   
  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
  
  delay(2000);
}

int count = 1;

void loop() {
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
      myDFPlayer.play(3);
      delay(3000);
      myDFPlayer.play(7);
      delay(3000);
  myDFPlayer.play(8);
  delay(3000);
  myDFPlayer.play(9);
  delay(3000);
  myDFPlayer.play(10);
  delay(3000);
  myDFPlayer.play(11);
  delay(3000);
  myDFPlayer.play(12);
  delay(3000);
  myDFPlayer.play(13);
  delay(3000);
  myDFPlayer.play(14);
  delay(3000);
  myDFPlayer.play(15);
  delay(3000);
 myDFPlayer.play(6);
  delay(3000);
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
      
    /*
    if(button1 == LOW || button2 == LOW) //버튼을 누를 시 사진 바뀜
    {
      if(button1 == LOW){
        count = (count - 1);
        if(count <= 0) count = 3;
        Serial.println("1");}
      if(button2 == LOW){count = (count + 1) % 3; Serial.println("2");}
      if(count == 0){ 
        tftOn("/menu_1.bmp");
        delay(1000);
        }
      else if(count == 1){tftOn("/menu_2.bmp"); delay(1000);}
      else if(count == 2){tftOn("/menu_3.bmp"); delay(1000);}
    }
    //else count = 3;*/
}
