#include "mux.h"
#include "string.h"

void YSelect(int Y){
  digitalWrite(SPin[0], STable[Y][0]);
  digitalWrite(SPin[1], STable[Y][1]);
  digitalWrite(SPin[2], STable[Y][2]);
  digitalWrite(SPin[3], STable[Y][3]);
}

void mux_led_setup() {
  pinMode(SIG, OUTPUT); 
  digitalWrite(SIG, HIGH);

  for (int i = 0; i < 4; i++)
  {
    pinMode(SPin[i], OUTPUT); 
    digitalWrite(SPin[i], LOW);
  }
}

void mux_button_setup() {
  
  pinMode(SIG, INPUT_PULLUP); 

  for (int i = 0; i < 4; i++)
  {
    pinMode(SPin[i], OUTPUT); 
    digitalWrite(SPin[i], LOW);
  }
}

void buttonWaiting(int button, String s[]){
   YSelect(button);
  int stato;
  stato=digitalRead(SIG);
  //Serial.println(stato);
  if(stato == 0){
    Serial.printf("%s 클릭!\n", s[button].c_str());
    delay(1000);
  }
}

void buttonPalling(){
  buttonWaiting(0, s);
  buttonWaiting(1, s);
  buttonWaiting(2, s);
  buttonWaiting(3, s);
  buttonWaiting(4, s);
  buttonWaiting(5, s);
  buttonWaiting(6, s);
}
//mux로 led 사용 방법
/*
void loop() {
  for(int i = 0; i < push ; i++){
    YSelect(i);
    timeCount++;
    delay(1);
  }
  //trigger 추후에 수정
  if(weightCount >= 50){push++; weightCount -= 50;}
}
*/

//버튼 입력
/*
void loop() {
  buttonPalling();
}
*/
