int MUXPinS0 = D1;
int MUXPinS1 = D2;
int MUXPinS2 = D3;
int MUXPinS3 = D4;
// wire (multiplexor)EN to (ESP)GND, SIG to A0, VCC to 3v3 and GND to GND

void lightOn(int MUXyPin) {
  digitalWrite(MUXPinS3, HIGH && (MUXyPin & B00001000));
  digitalWrite(MUXPinS2, HIGH && (MUXyPin & B00000100));
  digitalWrite(MUXPinS1, HIGH && (MUXyPin & B00000010));
  digitalWrite(MUXPinS0, HIGH && (MUXyPin & B00000001));
  return ;
}

void lightOff(int MUXyPin) {
  digitalWrite(MUXPinS3, LOW && (MUXyPin & B00001000));
  digitalWrite(MUXPinS2, LOW && (MUXyPin & B00000100));
  digitalWrite(MUXPinS1, LOW && (MUXyPin & B00000010));
  digitalWrite(MUXPinS0, LOW && (MUXyPin & B00000001));
  return ;
}

void setup()
{
  Serial.begin(115200);
  pinMode(MUXPinS0, OUTPUT);
  pinMode(MUXPinS1, OUTPUT);
  pinMode(MUXPinS2, OUTPUT);
  pinMode(MUXPinS3, OUTPUT);
}

void loop()
{
  Serial.println("Values");
  
  lightOn(0);
  delay(50);
  lightOff(0);
  delay(50);
}
