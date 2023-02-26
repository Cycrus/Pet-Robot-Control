// Connect SCL to A5 and SDA to A4
// Do not forget the servo power to an external power source (not one of the boards).

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int instruction = 0;
int prev_servo_pos = 0;
int servo_pos = 360;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    instruction = Serial.read();
  }

  if(instruction == 45)
  {
    servo_pos -= 10;
    Serial.println(servo_pos);
  }
  else if(instruction == 43)
  {
    servo_pos += 10;
    if(servo_pos > 4095)
      servo_pos = 4095;
    Serial.println(servo_pos);
  }

  if(servo_pos != prev_servo_pos)
  {
    pwm.setPWM(0, 0, servo_pos);
    pwm.setPWM(1, 0, servo_pos);
  }

  instruction = 0;
  prev_servo_pos = servo_pos;
}
