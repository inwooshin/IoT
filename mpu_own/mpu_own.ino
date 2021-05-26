#include <Wire.h>

int MPU_add = 0x68, TurnOn = 0;

int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup() {
  Serial.begin(115200);
  
  Wire.begin(4,5);
  Wire.beginTransmission(MPU_add);
  Wire.write(0x6B);

  Wire.write(1);
  Wire.endTransmission(true);
}

void loop() {
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

  Serial.print("AX = "); Serial.print(AcX);
  Serial.print(", AY = "); Serial.print(AcY);
  Serial.print(", AZ = "); Serial.print(AcZ);

  Serial.print(", Tmp = "); Serial.print(Tmp / 340 + 36.53);

  Serial.print(", GX = "); Serial.print(GyX);
  Serial.print(", GY = "); Serial.print(GyY);
  Serial.print(", GZ = "); Serial.print(GyZ);
  Serial.println();

  delay(1000);
}
