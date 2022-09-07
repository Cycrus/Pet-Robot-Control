/*
 * dc_motor_test.ino
 * 
 * A small script for remote control of H-Bridge controlled robot with two dc motors.
 * 
 * Author: Cyril Marx
 * Date: August 2022
 */

int instruction = 0;
const float MOTOR_DIFF_CORRECTION = 0.94;

int right_speed = 150;
int left_speed = (float)right_speed * MOTOR_DIFF_CORRECTION;

const int I_NOTHING = 10;
const int I_FORWARD = 119;
const int I_RIGHT = 100;
const int I_BACKWARD = 115;
const int I_LEFT = 97;
const int I_STOP = 113;

const int GPIO_LEFT_SPEED = 9;
const int GPIO_RIGHT_SPEED = 3;
const int GPIO_LEFT_DIRECTION = 8;
const int GPIO_RIGHT_DIRECTION = 2;

const int FORWARD = LOW;
const int BACKWARD = HIGH;


void setup() {
  pinMode(GPIO_LEFT_SPEED, OUTPUT);
  pinMode(GPIO_RIGHT_SPEED, OUTPUT);
  pinMode(GPIO_LEFT_DIRECTION, OUTPUT);
  pinMode(GPIO_RIGHT_DIRECTION, OUTPUT);

  Serial.begin(9600);
}

void loop(){
  if(Serial.available() > 0)
  {
    int new_instruction = Serial.read();
    if(new_instruction != I_NOTHING)
    {
      instruction = new_instruction;
    }
  }

  if(instruction == I_FORWARD)
  {
    digitalWrite(GPIO_LEFT_DIRECTION, FORWARD);
    digitalWrite(GPIO_RIGHT_DIRECTION, FORWARD);
    analogWrite(GPIO_LEFT_SPEED, left_speed);
    analogWrite(GPIO_RIGHT_SPEED, right_speed);
  }
  else if(instruction == I_BACKWARD)
  {
    digitalWrite(GPIO_LEFT_DIRECTION, BACKWARD);
    digitalWrite(GPIO_RIGHT_DIRECTION, BACKWARD);
    analogWrite(GPIO_LEFT_SPEED, left_speed);
    analogWrite(GPIO_RIGHT_SPEED, right_speed);
  }
  else if(instruction == I_RIGHT)
  {
    digitalWrite(GPIO_LEFT_DIRECTION, FORWARD);
    digitalWrite(GPIO_RIGHT_DIRECTION, BACKWARD);
    analogWrite(GPIO_RIGHT_SPEED, right_speed);
    analogWrite(GPIO_LEFT_SPEED, left_speed);
  }
  else if(instruction == I_LEFT)
  {
    digitalWrite(GPIO_RIGHT_DIRECTION, FORWARD);
    digitalWrite(GPIO_LEFT_DIRECTION, BACKWARD);
    analogWrite(GPIO_RIGHT_SPEED, right_speed);
    analogWrite(GPIO_LEFT_SPEED, left_speed);
  }
  else if(instruction == I_STOP)
  {
    digitalWrite(GPIO_RIGHT_DIRECTION, FORWARD);
    digitalWrite(GPIO_LEFT_DIRECTION, FORWARD);
    analogWrite(GPIO_RIGHT_SPEED, 0);
    analogWrite(GPIO_LEFT_SPEED, 0);
  }
}
