#include <Adafruit_GFX.h>         
#include <Adafruit_ST7735.h>      
#include <SdFat.h>                
#include <Adafruit_SPIFlash.h>    
#include <Adafruit_ImageReader.h> 
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Q2HX711.h>
#include <Adafruit_NeoPixel.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "Arduino.h"
#include "DFPlayer_Mini_Mp3.h"
#include "ESP8266_ST7735.h"
#include "TextGraphicsFunctions.h"

// 컨트롤 핀
#define PIN            A0

// WS2812B 의 연결된 개수
#define NUMPIXELS      1

// Delay 값
#define delayval 500 

//#define Relay1  D1

#define WLAN_SSID       "INS"             // Your SSID  //check
#define WLAN_PASS       "sksmswjstjf2!"        // Your password  //check

/************************* Adafruit.io Setup ********************rlatj*************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "EnochOf"            // Replace it with your username  //check
#define AIO_KEY         "aio_GIKS55qveBhkIml4iFUPJuNtX8tm"   // Replace with your Project Auth Key  //check

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

//구글 변수들
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe Light1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/LedControlFeed"); // FeedName  //check

const byte hx711_data_pin = 10;
const byte hx711_clock_pin = D0; // 로드셀 모듈인 HX711에서 받은 DATA PIN을 D1 PIN에, CLORK핀은 D2핀에 연결한다.

Q2HX711 hx711(hx711_data_pin, hx711_clock_pin); //로드셀 무게센서 클래스를 형성한다.

String s[6] = {"영점", "아래", "오른쪽", "가운데", "왼쪽", "위쪽"};
int count = 0;

ESP8266_ST7735 lcd = ESP8266_ST7735(TFT_CS, TFT_DC);

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}

void tftOn(char* bmpName){        //tft에 bmp파일을 출력하는 함수.
  reader.loadBMP(bmpName, img);
  img.draw(tft,0,0);
}

void tftOff(){           //tft화면을 초기화 하는 함수.
  tft.fillScreen(0);     // and clear screen
}

void setup(void) {   
  Serial.begin(9600);
  while(!Serial);

  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
  
  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&Light1);

  tft.initR(INITR_BLACKTAB); //tft 의 초기 설정

  while(!SD.begin(SD_CS, SD_SCK_MHZ(18))) { // sd 카드 연결을 시작하고, 18MHz 로 통신한다.
    Serial.println("SD begin() failed");
    delay(1000); //sd 카드를 읽어오지 못할 경우 진행이 안되도록 한다.
  }

  tft.fillScreen(0);
  
  //초기 사진
  tftOn("/init.bmp");

  //mux_button_setup();

  pinMode(D0, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);

  mp3_set_serial(Serial);
  delay(1);

  mp3_set_volume(18);
}
int countChange = 0;

double weightCount(){
  double reading=0;
  reading = (double)((hx711.read()-8233600)/3300*100 - 1600) / 10;
  
  return reading;
}

void lcdDraw(const char s[]){
  lcd.setRotation(1); 
  drawCenteredText(110, 2, s, COLOR_BLACK);
  lcd.setRotation(0);
}

double clic = 0;

void MenuCount(char* s, int mp3, double cmp, double err){
  mp3_play(mp3);
  double boundary = millis();
  int first = 0, bfirst = 0, bstart = 0;
  
  while(true){
    tftOn(s);
    double doubleWeight = weightCount() - clic;
    String strWeight = "";
    strWeight += doubleWeight;

    lcdDraw(strWeight.c_str());
    
    int b1 = digitalRead(D2);
    int b2 = digitalRead(D4);
    
    if(b1 == 0 && bstart == 0){
       bstart = millis();
    }
    else if(b1 == 1 && bstart > 0 ){
      if(millis() - bstart > 700) mp3_stop();
      else break;
      bstart = 0;
    }
    if(b2 == 0){
      clic = weightCount();
    }
    
    double min = cmp - cmp * err, max = cmp + cmp * err;
    if(doubleWeight >= min && doubleWeight <= max){
      if(first == 0){
        boundary = millis();
        first = 1;
      }

      if(millis() - boundary > 1500){
        break;
      }
    }
    else{first = 0; boundary = millis();}
  }
}

void kimchiB(){
  mp3_play(2); 
  tftOn("kimbok0.bmp");
  delay(4000);
  MenuCount("kimbok1.bmp", 20, 95, 0.15);
  MenuCount("kimbok2.bmp", 21, 160, 0.1);
  MenuCount("kimbok3.bmp", 22, 250, 0.1);
  tftOn("end.bmp");
  mp3_play(50);
  delay(5000);
  tftOn("/menu_1.bmp");
  count = 0;
}

//sound 20 - 22, kimbok0 - 3

void kimchiJ(){
  mp3_play(3);
  tftOn("kj0.bmp");
  delay(4000);
  MenuCount("kj1.bmp", 7, 380, 0.05);
  MenuCount("kj2.bmp", 8, 120, 0.1);
  MenuCount("kj3.bmp", 9, 180, 0.1);
  MenuCount("kj4.bmp", 10, 60, 0.2);
  MenuCount("kj5.bmp", 11, 1000, 0.1);
  tftOn("end.bmp");
  mp3_play(50);
  delay(5000);
  tftOn("/menu_1.bmp");
  count = 0;
}

void dwenjang(){
  mp3_play(4);
  tftOn("dj0.bmp");
  delay(5000);
  MenuCount("dj1.bmp", 30, 750, 0.1);
  MenuCount("dj2.bmp", 31, 100, 0.1);
  MenuCount("dj3.bmp", 32, 270, 0.1);
  MenuCount("dj4.bmp", 33, 1000, 0.1);
  MenuCount("dj5.bmp", 34, 180, 0.1);
  tftOn("end.bmp");
  mp3_play(50);
  delay(5000);
  tftOn("/menu_1.bmp");
  count = 0;
}

int first = 0, Start = 0;

void ledStripOn(int i){
  Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ400);

  pixels.begin(); // This initializes the NeoPixel library.
   pixels.setBrightness(20); // LED 밝기 : 255가 최대 0이 최소 입니다.
  pixels.show();
  
    pixels.setPixelColor(i, pixels.Color(0,0,255,0)); // 0번 LED 남색 ON
    pixels.show();
}

void loop() {
     int b1 = digitalRead(D2);
     int b3 = digitalRead(D4);
     //int b2 = digitalRead(10); //구글 핀
     int b4 = digitalRead(9);
      
     MQTT_connect();
     
     Adafruit_MQTT_Subscribe *subscription = mqtt.readSubscription(1);

     if (subscription == &Light1) {
          tftOn("/menu_google.bmp");
          Serial.print("Got: ");
          Serial.println((char *)Light1.lastread);  
          if(*Light1.lastread == 0){
            kimchiB();
          }
          else if(*Light1.lastread == 1){
            dwenjang();
          }
          else {
            kimchiJ();
          }
     }
      
     if(b1 == 0 || b3 == 0 || b4 ==0){
       if (b1 == 0)
       {
        count -= 1;
        if(count <= -1) count = 2;
        Serial.println(count);
        countChange = 1;
        if(first == 0){
          Start = millis();
          first = 1;
        }
       }
       else if(b3 == 0){
        if(count == 0){ kimchiJ();
                        }
        else if(count == 1){kimchiB();}
        else if(count == 2){dwenjang();}
       }

        /*
       else if (b2 == 0)
       {
        count = (count + 1) % 3;
        Serial.println(count);
        countChange = 1;
       }
       */
        
        if(countChange == 1){
           if(count == 0){ 
              tftOn("/menu_1.bmp");
           }
           else if(count == 1){
              tftOn("/menu_2.bmp");
           }
           else {tftOn("/menu_3.bmp");}
        }
       countChange = 0;
     }
     
     delay(1);

}
