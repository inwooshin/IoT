#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  
  Serial.begin(115200);
  delay(1000);
  Serial.println("Hello world...!");
  WiFi.mode(WIFI_AP_STA);
  delay(1000);
  // 몇번의 모드를 설정했는지
  Serial.println(WiFi.getMode());

  //현재 와이파이 중 어떤 것을 선택할 수 있는지
  int found = WiFi.scanNetworks(0, 1);
  Serial.printf("I found ssid num : %d\r\n", found);

  int i = 0;
  Serial.println("SSID\t\tStrength\t\tchannel\t\tMAC");
  for(i = 0 ; i < found ; i++){
      Serial.printf("%s\t\t%d\t\t%d\t\t%s\r\n",
      WiFi.SSID(i).c_str(), WiFi.RSSI(i), WiFi.channel(i), WiFi.BSSIDstr(i).c_str());
  }
  WiFi.begin("MJU_Wireless", "");
  WiFi.setAutoReconnect(1);
  
    int connResult = WiFi.waitForConnectResult();
    if (connResult == WL_CONNECTED){
      Serial.printf("conn Ok\r\n");
    }
    else{
      Serial.printf("conn fail, reason : %d\r\n", connResult);
    }

  Serial.printf("My Gateway : %s\r\n", WiFi.gatewayIP().toString().c_str());
  Serial.printf("My IP : %s\r\n", WiFi.localIP().toString().c_str());
}

void loop() {
  // put your main code here, to run repeatedly:
  Ping.ping("www.google.com");
  int returnMs = Ping.averageTime();

  Serial.printf("www.google.com time : %d ms\r\n", returnMs);

  for(int i = 0 ; i < returnMs ; i++){
    digitalWrite(2, LOW);
    delay(100);
    digitalWrite(2, HIGH);
    delay(100);
  }
  
  delay(5000);
  
}
