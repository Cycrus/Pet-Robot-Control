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
#include "src/effectors/LedRing.hpp"
#include "src/effectors/DCMotor.hpp"

//-----------------------------------------------------------------------------------------------------------------
// Timers
uint32_t curr_time = 0;

//-----------------------------------------------------------------------------------------------------------------
// DataReceiver
DataReceiver *data_receiver = new DataReceiver(57600, 200);

//-----------------------------------------------------------------------------------------------------------------
// Effectors
LedRing *led_ring = new LedRing(13, 12);
DCMotor *right_motor = new DCMotor(3, 2, 1.0);
DCMotor *left_motor = new DCMotor(9, 8, 0.66);

void setup()
{
  data_receiver->initModule();
  led_ring->initModule();
  right_motor->initModule();
  left_motor->initModule();
}

void loop()
{
  uint32_t fps_check_time = millis();
  uint32_t frame_delay = fps_check_time - curr_time;
  uint16_t fps = 1000 / frame_delay;

  curr_time = millis();

  Serial.flush();
  data_receiver->triggerModule(curr_time);

  if(data_receiver->getSize() == 7)
  {
    right_motor->setForce(data_receiver->getSignedShort(0));
    left_motor->setForce(data_receiver->getSignedShort(2));
    
    led_ring->setColor(data_receiver->getByte(4),
                       data_receiver->getByte(5),
                       data_receiver->getByte(6));
    data_receiver->resetDataBuffer();
  }

  led_ring->triggerModule(curr_time);
  right_motor->triggerModule(curr_time);
  left_motor->triggerModule(curr_time);
}