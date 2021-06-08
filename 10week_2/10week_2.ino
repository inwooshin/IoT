#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h> //얘를 사용하려면 json 을 해석해서 풀어놓을 공간이 필요하다. 임시버퍼가 필요

DynamicJsonDocument doc(2048);
//StaticJsonDocument<2048> doc; //요런식으로 임시버퍼를 선언해주는 것이다. 1kb 보다 더많은 것을 선언하고
                              //싶으면 위의 방식 밑의 방식은 더 작은 것!

HTTPClient mClient;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  WiFi.begin("netis", "a987654321!");

  while(1){
      if(WiFi.status() == WL_CONNECTED) break;
      else{Serial.print('.'); delay(500);}
  }
  Serial.printf("\r\n ready to internet...!\r\n");
}

void loop() {
  mClient.begin("http://api.openweathermap.org/data/2.5/weather?q=pyeongtaek&appid=983101ac4e309d52c32946a8294ae487");
  //http class 객체로 만들어준 것은 begin 함수시 http 를 무조건 붙여야함!

  int getResult = mClient.GET();
  if(getResult == HTTP_CODE_OK){
    //정상이다  
    String receivedData = mClient.getString();
    Serial.printf("%s\r\n\r\nEND Transmission\r\n", receivedData.c_str());
    deserializeJson(doc, receivedData); //요렇게 하면 해석이 끝난다..!
    //float a = doc["id"];
    //main key -> temp -> 282.55
    //float tmp = doc["main"]["temp"];
    Serial.printf("현재 온도 : %f\r\n", (float)(doc["main"]["temp"]) - 273.0); //이렇게 float으로 묶어서
                                                                //하는 것을 파일 캐스팅이라고함
    const char * city = doc["name"];                                                               
    Serial.printf("이곳의 도시는 %s 입니다.\r\n", city);
    const char * weather = doc["weather"][0]["main"];
    const char* detailWeather = doc["weather"][0]["description"];
    Serial.printf("날씨 상태는 %s 이고 자세히는 %s 입니다.\r\n", weather,detailWeather);
  } //GET 어쩌구 메소드 보내는 것과 같음
  else{
    //Error가 있는 것이다.  
    Serial.printf("err, code : %d\r\n", getResult);
  }

  mClient.end();
  delay(5000);
}
