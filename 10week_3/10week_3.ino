#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

WiFiClient mTCPClient; //클라이언트 클래스 필요!
PubSubClient mMQTTClient; //클래스 객체 필요

int MPU_add = 0x68, TurnOn = 0;

int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ, offTemp = 0;

void insCB(const char topic[], byte *data, unsigned int length){
  char tempbuffer[20]= {0,};
  memcpy(tempbuffer, data, (length > 19? 19 : length));  
  Serial.printf("Topic : %s, New data come : %s\r\n", topic, tempbuffer); 
  if(strcmp(topic, "TEMP") == 0) offTemp = 0;
  else if(strcmp(topic, "ACCEL") == 0) offTemp = 1;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Hello world...!");
  Wire.begin(4,5);
  Wire.beginTransmission(MPU_add);
  Wire.write(0x6B);

  Wire.write(1);
  Wire.endTransmission(true);

  //Who am i 로 읽어옴
  Wire.beginTransmission(MPU_add);
  Wire.write(0x75);
  Wire.endTransmission(true);

  Wire.requestFrom(MPU_add, 1, true);

  char who = Wire.read();
  Serial.println(who, HEX);

  //2000도로 Gyro 해상도를 바꿔줌
  Wire.beginTransmission(MPU_add);
  Wire.write(0x1B);

  Wire.write(0x18);
  Wire.endTransmission(true);
  
  //accelerometer 해상도 16으로 변경
  Wire.beginTransmission(MPU_add);
  Wire.write(0x1C);

  Wire.write(0x18);
  Wire.endTransmission(true);

  pinMode(2, OUTPUT);
  analogWrite(2, 1023);
  WiFi.begin("netis", "a987654321!");

  while(1){
    if(WiFi.status() == WL_CONNECTED) break;
    else{delay(500);  Serial.print('.');}
  }
  Serial.println("WiFi Connect complete...!");
  Serial.println("MQTT Connect...");

  mMQTTClient.setClient(mTCPClient);
  mMQTTClient.setServer("test.mosquitto.org", 1883);
  mMQTTClient.setCallback(insCB);
  //콜백을 등록을 했으니 어떤 토픽에 대해서 이벤트를 받을 것이냐? 는 등록을 해야됨
  
  int connectResult = mMQTTClient.connect("INS_Device_ESP8266");
  Serial.printf("MQTT connect Result : %d", connectResult);

  mMQTTClient.subscribe("MJUEE/NEWIOT/#"); //이거는 반드시 connect 된 다음에
                                           //해야된다. 이유는 나도 모름 ㅎ 이라고 하심
  
}

int i = 0;
unsigned long long lastMs = 0;
#define Delay_ms 1000

void loop() {
  //매 1초마다 콜하고 싶은 것?
  if(millis() - lastMs >= Delay_ms){
     lastMs = millis(); // esp8266 켜지고 나서 얼만큼의 ms 가 지났는가?
    //data 를 보내는 것!
    Serial.printf("if MQTT Connected : %d\r\n", mMQTTClient.connected());
    char str[80];
    sprintf(str, "SIN, CNT:%d\r\n", i); //버퍼에 데이터를 집어넣는 것이다.
    i++;
    mMQTTClient.publish("MJUEE/IOT/INS", "SIN");
  }

  Wire.beginTransmission(MPU_add);
  Wire.write(0x3B); // 처음에 값은 레지스터의 주소, 
  Wire.endTransmission();

  Wire.requestFrom(MPU_add, 14, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();

  if(offTemp == 0){
  Serial.print("Tmp = "); Serial.print(Tmp / 340 + 36.53);
  Serial.println();
  }
  else{
    
  Serial.print("AX = "); Serial.print(AcX);
  Serial.print(", AY = "); Serial.print(AcY);
  Serial.print(", AZ = "); Serial.print(AcZ);
  Serial.println();
    
  }
  
  mMQTTClient.loop();
}
