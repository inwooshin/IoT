#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
 
SoftwareSerial mySoftwareSerial(3, 1); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
 
/**************************************************************************/
 
/***********************************************************************/

int vol = 20;
 
void setup() {
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  
  Serial.println();
  Serial.println("DFRobot DFPlayer Mini Demo");
  Serial.println("Initializing DFPlayer ... (May take 3~5 seconds)");
   
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
   
  myDFPlayer.volume(16);  //Set volume value. From 0 to 30
   
  /**************************************************************************/
 
}
 
void loop() {
  while(!Serial);
  Serial.println(vol);
  myDFPlayer.volume(vol); 
  vol++;
  myDFPlayer.play(20);
  delay(3000);
  myDFPlayer.play(7);
  delay(3000);
  if(vol >= 25) vol = 18;
}
 
