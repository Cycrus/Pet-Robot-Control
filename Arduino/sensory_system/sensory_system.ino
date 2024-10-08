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

#include "ModuleSyncer.hpp"
#include "DataSender.hpp"

//-----------------------------------------------------------------------------------------------------------------
// Timers
uint32_t curr_time = 0;

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

// Module Syncer for Ultrasonic Distance Modules
ModuleSyncer *ultrasonic = new ModuleSyncer();

// DataSender
DataSender *data_sender = new DataSender(115200, 200);
uint8_t i = 0;

//-----------------------------------------------------------------------------------------------------------------
void setup() {
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

  ultrasonic->addModule(distance_front);
  ultrasonic->addModule(distance_back);
  ultrasonic->initAllModules();

  data_sender->initModule();
}

//-----------------------------------------------------------------------------------------------------------------
void loop() {
  uint32_t fps_check_time = millis();
  uint32_t frame_delay = fps_check_time - curr_time;
  uint16_t fps = 1000 / frame_delay;

  curr_time = millis();

  ultrasonic->triggerModule(curr_time);
  //bmp280->triggerModule(curr_time);  // New sensor 1
  //dht11->triggerModule(curr_time);
  //mq135->triggerModule(curr_time);
  rfid_reader->triggerModule(curr_time);

  compass->triggerModule(curr_time);
  //current_1->triggerModule(curr_time);
  //current_2->triggerModule(curr_time);
  //current_3->triggerModule(curr_time);

  data_sender->addData(distance_front->getDistance());
  data_sender->addData(distance_back->getDistance());
  data_sender->addData((bmp280->getTemperature() + dht11->getTemperature()) / 2);
  data_sender->addData(bmp280->getPressure());
  data_sender->addData(bmp280->getAltitude());
  data_sender->addData(dht11->getHumidity());
  data_sender->addData(mq135->getGasPPM());
  data_sender->addData(rfid_reader->getMessageCode());

  data_sender->addData(compass->getX());
  data_sender->addData(compass->getY());
  data_sender->addData(compass->getZ());
  data_sender->addData(compass->getHeading());
  data_sender->addData(current_1->getCurrentPerHour() + current_2->getCurrentPerHour() + current_3->getCurrentPerHour());
  data_sender->addData(current_1->getCurrent() + current_2->getCurrent() + current_3->getCurrent());

  data_sender->addData(wt61_module->getAccX());
  data_sender->addData(wt61_module->getAccY());
  data_sender->addData(wt61_module->getAccZ());
  data_sender->addData(wt61_module->getGyrX());
  data_sender->addData(wt61_module->getGyrY());
  data_sender->addData(wt61_module->getGyrZ());
  data_sender->addData(wt61_module->getAngX());
  data_sender->addData(wt61_module->getAngY());
  data_sender->addData(wt61_module->getAngZ());
  data_sender->addData(gps_module->getLon());
  data_sender->addData(gps_module->getLat());

  data_sender->addData(gps_module->getYear());
  data_sender->addData(gps_module->getMonth());
  data_sender->addData(gps_module->getDay());
  data_sender->addData(gps_module->getHour());
  data_sender->addData(gps_module->getMinute());
  data_sender->addData(gps_module->getSecond());
  data_sender->addData(gps_module->getCentisecond());
  data_sender->addData(gps_module->getAltitude());
  data_sender->addData(gps_module->getSpeed());
  data_sender->addData(gps_module->getCourse());
  data_sender->addData(gps_module->getSatelliteNumber());
  data_sender->addData(fps);

  bool has_sent = data_sender->triggerModule(curr_time);

  if(has_sent)
  {
    current_1->resetBuffers();
    current_2->resetBuffers();
    current_3->resetBuffers();
  }

  data_sender->resetData();

  delay(10);
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
