/**********************************************************************
 * ServoMotor.cpp
 *
 * Implementation of the ServoMotor class.
 *
 * Author: Cyril Marx
 * Created: February 2023
 **********************************************************************/

#include "ServoMotor.hpp"

ServoMotor::ServoMotor(uint8_t servo_id, uint16_t default_pos, uint16_t min_pos, uint16_t max_pos) :
servo_id_(servo_id),
curr_pos_(default_pos_),
default_pos_(default_pos),
min_pos_(min_pos),
max_pos_(max_pos),
step_size_(0),
max_step_size_(20),
min_step_size_(0),
servo_driver_(nullptr)
{
  time_list_[0] = 16;
  setMaxSteps(1);
}

//-----------------------------------------------------------------------------------------------------------------
void ServoMotor::assignDriver(Adafruit_PWMServoDriver *servo_driver)
{
  servo_driver_ = servo_driver;
}

//-----------------------------------------------------------------------------------------------------------------
void ServoMotor::initModule()
{
  if (servo_driver_ == nullptr)
  {
    servo_driver_ = new Adafruit_PWMServoDriver();
    servo_driver_->begin();
    servo_driver_->setPWMFreq(60);
    delay(50);
  }

  servo_driver_->setPWM(servo_id_, 0, default_pos_);
  delay(100);
}

//-----------------------------------------------------------------------------------------------------------------
Adafruit_PWMServoDriver *ServoMotor::getDriver()
{
  return servo_driver_;
}

//-----------------------------------------------------------------------------------------------------------------
void ServoMotor::setForce(int8_t speed)
{
  // time_list_[0]
  // step_size_

  uint8_t max_input_value = 128;
  uint16_t step_size_range = max_step_size_ - min_step_size_;

  step_size_ = ((float)speed / (float)max_input_value) * step_size_range;
}

//-----------------------------------------------------------------------------------------------------------------
int8_t ServoMotor::getStepSize()
{
  return step_size_;
}

//-----------------------------------------------------------------------------------------------------------------
void ServoMotor::performStep()
{
  uint16_t next_pos = curr_pos_ + step_size_;

  if (next_pos < min_pos_)
  {
    next_pos = min_pos_;
  }
  else if (next_pos > max_pos_)
  {
    next_pos = max_pos_;
  }

  if (next_pos != curr_pos_)
  {
    servo_driver_->setPWM(servo_id_, 0, next_pos);
    curr_pos_ = next_pos;
  }
}

//-----------------------------------------------------------------------------------------------------------------
void ServoMotor::stepOne()
{
  performStep();
}

//-----------------------------------------------------------------------------------------------------------------
void ServoMotor::stepTwo()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void ServoMotor::stepThree()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void ServoMotor::stepFour()
{
  // Not used.
}