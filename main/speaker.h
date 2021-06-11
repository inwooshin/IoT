#ifndef DFT_H
#define DFT_H

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(3, 1); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void dft_setup();

#endif
