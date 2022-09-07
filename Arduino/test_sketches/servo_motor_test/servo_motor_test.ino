// Connect SCL to A5 and SDA to A4
// Do not forget the servo power to an external powr source (not one of the boards).

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define servoMIN 150
#define servoMAX 600

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);
}

void loop() {
  // put your main code here, to run repeatedly:
  pwm.setPWM(0, 0, servoMAX);
  Serial.println("MIN");
  //delay(1000);

  /*pwm.setPWM(0, 0, servoMAX);
  Serial.println("MAX");
  delay(1000);*/
}
