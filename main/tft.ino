#include "tft.h"

SdFat SD;         // SD 클래스 객체를 생성
Adafruit_ImageReader reader(SD); //sd 카드를 읽어오기 위한 read 객체 생성

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST); //각 tft 핀을 설정한다.
Adafruit_Image img;        // 메모리에 올려줄 이미지 파일을 load 하는 객체main
ImageReturnCode stat;

void tftOn(char* bmpName){        //tft에 bmp파일을 출력하는 함수.
  reader.loadBMP(bmpName, img);
  img.draw(tft,0,0);
}

void tftOff(){           //tft화면을 초기화 하는 함수.
  tft.fillScreen(0);     // and clear screen
}

void tft_setup(void) { 

  pinMode(D4,INPUT_PULLUP);

  tft.initR(INITR_BLACKTAB); //tft 의 초기 설정을

  if(!SD.begin(SD_CS, SD_SCK_MHZ(10))) { // sd 카드 연결을 시작하고, 10MHz 로 통신한다.
    Serial.println("SD begin() failed");
    delay(1000); //sd 카드를 읽어오지 못할 경우 진행이 안되도록 한다.
  }

  tft.fillScreen(0);

  //초기 사진
  tftOn("/init.bmp");

  delay(2000);
}
