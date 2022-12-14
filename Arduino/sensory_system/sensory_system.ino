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

#include "src/internal_sensors/CompassModule.hpp"
#include "src/internal_sensors/CurrentSensor.hpp"
#include "src/internal_sensors/WT61Module.hpp"
#include "src/internal_sensors/GPSModule.hpp"

//-----------------------------------------------------------------------------------------------------------------
uint32_t curr_time = 0;
uint32_t last_time = 0;

//-----------------------------------------------------------------------------------------------------------------
// External Module Declarations
UltrasonicDistanceModule *distance_front = new UltrasonicDistanceModule(24, 13);
UltrasonicDistanceModule *distance_back = new UltrasonicDistanceModule(22, 12);
BMP280Module *bmp280 = new BMP280Module();
HumidityModule *dht11 = new HumidityModule(30, DHT11); 
GasModule *mq135 = new GasModule(A3);
RFIDReader *rfid_reader = new RFIDReader(10, 9);

// Internal Module Declarations
CompassModule *compass = new CompassModule(12345, -0.0890118);
CurrentSensor *current_1 = new CurrentSensor(A0);
CurrentSensor *current_2 = new CurrentSensor(A1);
CurrentSensor *current_3 = new CurrentSensor(A2);
WT61Module *wt61_module = new WT61Module(true);
GPSModule *gps_module = new GPSModule(2);

//-----------------------------------------------------------------------------------------------------------------
void setup() {
  Serial->begin(19200);
  
  distance_front->initModule();
  distance_back->initModule();
  bmp280->initModule();
  dht11->initModule();
  mq135->initModule();
  rfid_reader->initModule();

  compass->initModule();
  current_1->initModule();
  current_2->initModule();
  current_3->initModule();
  wt61_module->initModule();
  gps_module->initModule();
}

//-----------------------------------------------------------------------------------------------------------------
void loop() {
  uint32_t fps_check_time = millis();
  uint32_t frame_delay = fps_check_time - curr_time;
  uint32_t fps = 1000 / frame_delay;

  curr_time = millis();

  distance_front->triggerModule(curr_time);
  distance_back->triggerModule(curr_time);
  bmp280->triggerModule(curr_time);
  dht11->triggerModule(curr_time);
  mq135->triggerModule(curr_time);
  rfid_reader->triggerModule(curr_time);

  compass->triggerModule(curr_time);
  current_1->triggerModule(curr_time);
  current_2->triggerModule(curr_time);
  current_3->triggerModule(curr_time);

  if(curr_time - last_time >= 1000)
  {
    Serial.print("Front distance = ");
    Serial.println(distance_front->getDistance());
    Serial.print("Back distance = ");
    Serial.println(distance_back->getDistance());
    Serial.print("Temperature = ");
    Serial.println((bmp280->getTemperature() + dht11->getTemperature()) / 2);
    Serial.print("Pressure = ");
    Serial.println(bmp280->getPressure());
    Serial.print("Altitude = ");
    Serial.println(bmp280->getAltitude());
    Serial.print("Humidity = ");
    Serial.println(dht11->getHumidity());
    Serial.print("Gas PPM = ");
    Serial.println(mq135->getGasPPM());
    Serial.print("RFID Message = ");
    Serial.println(rfid_reader->getMessageCode());

    Serial.print("Compass coords = ");
    Serial.print(compass->getX()); Serial.print(" | "); Serial.print(compass->getY()); Serial.print(" | "); Serial.println(compass->getZ());
    Serial.print("Compass heading = ");
    Serial.println(compass->getHeading());
    Serial.print("Current in mAh = ");
    Serial.println(current_1->getCurrentPerHour() + current_2->getCurrentPerHour() + current_3->getCurrentPerHour());
    Serial.print("Current in Milliampere = ");
    Serial.println(current_1->getCurrent() + current_2->getCurrent() + current_3->getCurrent());
    Serial.print("Acceleration = ");
    Serial.print(wt61_module->getAccX()); Serial.print(" | "); Serial.print(wt61_module->getAccY()); Serial.print(" | "); Serial.println(wt61_module->getAccZ());
    Serial.print("Gyroscope = ");
    Serial.print(wt61_module->getGyrX()); Serial.print(" | "); Serial.print(wt61_module->getGyrY()); Serial.print(" | "); Serial.println(wt61_module->getGyrZ());
    Serial.print("Angle = ");
    Serial.print(wt61_module->getAngX()); Serial.print(" | "); Serial.print(wt61_module->getAngY()); Serial.print(" | "); Serial.println(wt61_module->getAngZ());
    Serial.print("GPS Location = ");
    Serial.print(gps_module->getLon()); Serial.print(" | "); Serial.println(gps_module->getLat());
    Serial.print("GPS Datetime = ");
    Serial.print(gps_module->getDay()); Serial.print("."); Serial.print(gps_module->getMonth()); Serial.print("."); Serial.print(gps_module->getDay());
    Serial.print(" ... "); Serial.print(gps_module->getHour()); Serial.print(":"); Serial.print(gps_module->getMinute()); Serial.print(":");
    Serial.print(gps_module->getSecond()); Serial.print("."); Serial.println(gps_module->getCentisecond());
    Serial.print("GPS Data = ");
    Serial.print("Altitude: "); Serial.print(gps_module->getAltitude()); Serial.print(" | Speed: "); Serial.print(gps_module->getSpeed());
    Serial.print(" | Course: "); Serial.print(gps_module->getCourse()); Serial.print(" | Satellites: "); Serial.println(gps_module->getSatelliteNumber());
    Serial.print("FPS = ");
    Serial.println(fps);
    Serial.print("Frame Delay = ");
    Serial.println(frame_delay);
    Serial.println("*******************************************");
    Serial.println("");
    last_time = curr_time;

    current_1->resetBuffers();
    current_2->resetBuffers();
    current_3->resetBuffers();
  }
}

//-----------------------------------------------------------------------------------------------------------------
void serialEvent1()
{
  gps_module->triggerModule(curr_time);
}

//-----------------------------------------------------------------------------------------------------------------
void serialEvent2() 
{
  wt61_module->triggerModule(curr_time);
}
