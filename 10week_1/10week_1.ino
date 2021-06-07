#include <ESP8266WiFi.h>

WiFiClient mClient; //얘를 이용해서 tcp ip 접속을 하는 것이다! 클래스다!
//TCP 클라이언트랑 동일하다!


/*
 * 이 과정을 한다고 함
 * AT+CIPSTART="TCP",ServerAddr",portNum
 * AT+CIPSEND=N
 * AT+CIPCLOSE
 */

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.begin("netis","a987654321!");

  while(1){
    if(WiFi.status() == WL_CONNECTED) break;
    else{Serial.print('.'); delay(500);}
  }
  Serial.printf("WiFi Connected...!\r\n");
}

void loop() {
  if(mClient.connected() == 0){ //커넥팅이 안되어있을 경우
    mClient.connect("www.mju.ac.kr", 80); //tcp 로 접속
    
    return ;   
  }

  mClient.printf("GET /sites/mjukr/intro/intro.html HTTP/1.1\r\n");
  mClient.printf("host: www.mju.ac.kr\r\n");
  mClient.printf("\r\n");
  mClient.printf("\r\n");
  delay(200);

  Serial.printf("Now start....!\r\n\r\n");

  while(1){
    int readChar = mClient.read();
    if(readChar == -1){ //esp8266이 메모리가 작아서 한번에 다 읽어오지 못하기 때문에 한번더
                        // 보낼 수 있는지 확인하는 구문이다.
      delay(1000);
      if(mClient.available() == 0){
        Serial.printf("\r\n\r\nThis is END...\r\n");
        break;  
      }  
    }  
    Serial.printf("%c",readChar);
  }
  delay(5000); //5초마다 새로고침
  //tcpIpClient.connected();
  //tcpIpClient.print(1);
  //tcpIpClient.available(); //Serial.available uart 데이터가 얼마나 옴?
  //tcp 꺼는 서버에서 몇바이트 읽어옴 ㅇㅇ
  //tcpIpClient.read(); //Integer return ! <-> char 할경우 0~255 다 표현해야되서 -1 표현이 불가
  // 그래서 int 형을 사용해서 0~255 와 -1 도 표현해줌, 참고로 int 형의 범위는 -2^31 <-> 2^31 -1
  //tcpIpClient.stop(); // tcpIp 연결을 끊어버린다. 
} 
