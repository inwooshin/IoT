#ifndef TFT_H
#define TFT_H

#include <Adafruit_GFX.h>         
#include <Adafruit_ST7735.h>      
#include <SdFat.h>                
#include <Adafruit_SPIFlash.h>    
#include <Adafruit_ImageReader.h>

void tftOn(char* bmpName);
void tftOff();
void tft_setup(void);
int count = 0;

/*
void loop() {
    int buttonState = digitalRead(D4);
    if(buttonState == 0) //버튼을 누를 시 사진 바뀜
    {
      if(count == 0){ 
        tftOn("/IU.bmp");
        count = 1;
        }
      else{tftOn("/s.bmp"); count = 0;}
    }
}
*/

#endif
