/**********************************************************************
 * motor_system.ino
 * 
 * Entry point and main controller functions for the sensory system on
 * the Arduino Mega.
 * 
 * Author: Cyril Marx
 * Created: September 2022
 **********************************************************************/

#include "DataSender.hpp"
#include "DataReceiver.hpp"
#include "src/effectors/LedRing.hpp"
#include "src/effectors/DCMotor.hpp"
#include "src/effectors/ServoMotor.hpp"

//-----------------------------------------------------------------------------------------------------------------
// Timers
uint32_t curr_time = 0;

//-----------------------------------------------------------------------------------------------------------------
// DataReceiver
DataReceiver *data_receiver = new DataReceiver(57600, 200);

//-----------------------------------------------------------------------------------------------------------------
// DataSender
DataSender *data_sender = new DataSender(57600, 50);

//-----------------------------------------------------------------------------------------------------------------
// Effectors
LedRing *led_ring = new LedRing(13, 12);
DCMotor *right_motor = new DCMotor(3, 2, 1.0);
DCMotor *left_motor = new DCMotor(9, 8, 0.85);
ServoMotor *x_axis_servo = new ServoMotor(0, 350, 250, 450);
ServoMotor *z_axis_servo = new ServoMotor(1, 400, 300, 500);

//-----------------------------------------------------------------------------------------------------------------
void setup()
{
  data_receiver->initModule();

  led_ring->initModule();
  right_motor->initModule();
  left_motor->initModule();

  x_axis_servo->initModule();
  z_axis_servo->assignDriver(x_axis_servo->getDriver());
  z_axis_servo->initModule();

  data_sender->initModule();
}

//-----------------------------------------------------------------------------------------------------------------
void loop()
{
  uint32_t fps_check_time = millis();
  uint32_t frame_delay = fps_check_time - curr_time;
  uint16_t fps = 1000 / frame_delay;

  curr_time = millis();

  data_receiver->triggerModule(curr_time);

  if(data_receiver->getSize() == 7)
  {
    right_motor->setForce(data_receiver->getSignedByte(0));
    left_motor->setForce(data_receiver->getSignedByte(1));

    x_axis_servo->setForce(data_receiver->getSignedByte(2));
    z_axis_servo->setForce(data_receiver->getSignedByte(3));
    
    led_ring->setColor(data_receiver->getByte(4),
                       data_receiver->getByte(5),
                       data_receiver->getByte(6));
    data_receiver->resetDataBuffer();
  }

  led_ring->triggerModule(curr_time);
  right_motor->triggerModule(curr_time);
  left_motor->triggerModule(curr_time);
  x_axis_servo->triggerModule(curr_time);
  z_axis_servo->triggerModule(curr_time);
  
  data_sender->addData(right_motor->getForce());
  data_sender->addData(left_motor->getForce());
  data_sender->addData(x_axis_servo->getCurrPosition());
  data_sender->addData(x_axis_servo->getForce());
  data_sender->addData(z_axis_servo->getCurrPosition());
  data_sender->addData(z_axis_servo->getForce());

  data_sender->triggerModule(curr_time);

  data_sender->resetData();
}