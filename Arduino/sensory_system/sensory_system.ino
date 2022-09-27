/**********************************************************************
 * sensory_system.ino
 * 
 * Entry point and main controller functions for the sensory system on
 * the Arduino Mega.
 * 
 * Author: Cyril Marx
 * Created: September 2022
 **********************************************************************/

#include "UltrasonicDistanceModule.hpp"

uint32_t curr_time = 0;
uint32_t last_time = 0;

UltrasonicDistanceModule distance_front(24, 13);
UltrasonicDistanceModule distance_back(22, 12);

void setup() {
  Serial.begin(9600);
  
  distance_front.initModule();
  distance_back.initModule();
}

void loop() {
  curr_time = millis();

  distance_front.getMeasurement(curr_time);
  distance_back.getMeasurement(curr_time);

  if(curr_time - last_time >= 1000)
  {
    Serial.print("Front = ");
    Serial.println(distance_front.getDistance());
    Serial.print("Back = ");
    Serial.println(distance_back.getDistance());
    Serial.println("");
    last_time = curr_time;
  }
}
