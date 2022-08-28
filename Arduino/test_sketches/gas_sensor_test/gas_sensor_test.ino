// You only need to connect the analog out pin. Just ignore the digital pin.

#include "MQ135.h"

#define ANALOGPIN A0

MQ135 gasSensor = MQ135(ANALOGPIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  float rzero = gasSensor.getRZero();
  delay(3000);
  Serial.print("MQ135 RZERO Calibration Value : ");
  Serial.println(rzero);
}

void loop() {
  // put your main code here, to run repeatedly:
  float ppm = gasSensor.getPPM();
  delay(1000);
  digitalWrite(13,HIGH);
  Serial.print("CO2 ppm value : ");
  Serial.println(ppm);
}
