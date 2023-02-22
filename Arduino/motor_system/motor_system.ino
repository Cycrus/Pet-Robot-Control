/**********************************************************************
 * motor_system.ino
 * 
 * Entry point and main controller functions for the sensory system on
 * the Arduino Mega.
 * 
 * Author: Cyril Marx
 * Created: September 2022
 **********************************************************************/

#include "src/utilities/DataReceiver.hpp"

//-----------------------------------------------------------------------------------------------------------------
// Timers
uint32_t curr_time = 0;

//-----------------------------------------------------------------------------------------------------------------
// DataReceiver
DataReceiver *data_receiver = new DataReceiver(115200, 200);

void setup()
{
  data_receiver->initModule();
}

void loop()
{
  uint32_t fps_check_time = millis();
  uint32_t frame_delay = fps_check_time - curr_time;
  uint16_t fps = 1000 / frame_delay;

  curr_time = millis();

  data_receiver->triggerModule(curr_time);
}