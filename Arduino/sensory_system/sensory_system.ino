/**********************************************************************
 * sensory_system.ino
 * 
 * Entry point and main controller functions for the sensory system on
 * the Arduino Mega.
 * 
 * Author: Cyril Marx
 * Created: September 2022
 **********************************************************************/

#include "src/external_sensors/UltrasonicDistanceModule.hpp"
#include "src/external_sensors/BMP280Module.hpp"
#include "src/external_sensors/HumidityModule.hpp"
#include "src/external_sensors/GasModule.hpp"
#include "src/external_sensors/RFIDReader.hpp"

uint32_t curr_time = 0;
uint32_t last_time = 0;

// Module Declarations
UltrasonicDistanceModule distance_front(24, 13);
UltrasonicDistanceModule distance_back(22, 12);
BMP280Module bmp280;
HumidityModule dht11(30, DHT11); 
GasModule mq135(A3);

void setup() {
  Serial.begin(9600);
  
  distance_front.initModule();
  distance_back.initModule();
  bmp280.initModule();
  dht11.initModule();
  mq135.initModule();
}

void loop() {
  curr_time = millis();

  distance_front.triggerModule(curr_time);
  distance_back.triggerModule(curr_time);
  bmp280.triggerModule(curr_time);
  dht11.triggerModule(curr_time);
  mq135.triggerModule(curr_time);

  if(curr_time - last_time >= 1000)
  {
    Serial.print("Front distance = ");
    Serial.println(distance_front.getDistance());
    Serial.print("Back distance = ");
    Serial.println(distance_back.getDistance());
    Serial.print("Temperature = ");
    Serial.println((bmp280.getTemperature() + dht11.getTemperature()) / 2);
    Serial.print("Pressure = ");
    Serial.println(bmp280.getPressure());
    Serial.print("Altitude = ");
    Serial.println(bmp280.getAltitude());
    Serial.print("Humidity = ");
    Serial.println(dht11.getHumidity());
    Serial.print("Gas PPM = ");
    Serial.println(mq135.getGasPPM());
    Serial.println("*******************************************");
    last_time = curr_time;
  }
}
