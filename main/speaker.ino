#include "speaker.h"

void dft_setup() {
  mySoftwareSerial.begin(9600);
  
  Serial.println();
  Serial.println("DFRobot DFPlayer Mini Demo");
  Serial.println("Initializing DFPlayer ... (May take 3~5 seconds)");
   
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("Unable to begin:");
    Serial.println("1.Please recheck the connection!");
    Serial.println("2.Please insert the SD card!");
    while(true){
      if (myDFPlayer.begin(mySoftwareSerial)) {
        break;
      }
      Serial.println("아직도 안됨 ㅠ");
      delay(1000);
    }
  }
  Serial.println("DFPlayer Mini online.");
   
  //myDFPlayer.volume(vol); 
 
}
 
