/**********************************************************************
 * DCMotor.cpp
 * 
 * Implementation of the DCMotor class.
 * 
 * Author: Cyril Marx
 * Created: February 2023
 **********************************************************************/

#include "DCMotor.hpp"

DCMotor::DCMotor(uint8_t force_gpio, uint8_t direction_gpio, float correction_factor) :
force_gpio_(force_gpio),
direction_gpio_(direction_gpio),
correction_factor_(correction_factor),
force_(0),
min_force_(110),
max_force_(250)
{
  time_list_[0] = 0;
  setMaxSteps(1);
}

//-----------------------------------------------------------------------------------------------------------------
void DCMotor::initModule()
{
  pinMode(direction_gpio_, OUTPUT);
  pinMode(force_gpio_, OUTPUT);
}

//-----------------------------------------------------------------------------------------------------------------
void DCMotor::setForce(int8_t force)
{
  if(force > 100)
  {
    force = 100;
  }
  else if(force < -100)
  {
    force = -100;
  }

  uint8_t max_input_value = 100;
  uint16_t force_range = max_force_ - min_force_;

  if(force == 0)
  {
    force_ = 0;
  }
  else if(force > 0)
  {
    force_ = min_force_ + ((float)force / (float)max_input_value) * force_range;
  }
  else if(force < 0)
  {
    force_ = -min_force_ + ((float)force / (float)max_input_value) * force_range;
  }
}

//-----------------------------------------------------------------------------------------------------------------
int8_t DCMotor::getForce()
{
  int8_t normalized_force = 0;
  uint16_t force_range = max_force_ - min_force_;

  if(force_ > 0)
  {
    normalized_force = ((float)force_ - (float)min_force_) / (force_range) * 100.0;
  }
  else if(force_ < 0)
  {
    normalized_force = - ((float)force_ + (float)min_force_) / (force_range) * 100.0;
  }
  else
  {
    normalized_force = 0;
  }

  return normalized_force;
}

//-----------------------------------------------------------------------------------------------------------------
int16_t DCMotor::getRawForce()
{
  return force_;
}

//-----------------------------------------------------------------------------------------------------------------
void DCMotor::stepOne()
{
  if(force_ > 0)
  {
    digitalWrite(direction_gpio_, LOW);
    analogWrite(force_gpio_, force_ * correction_factor_);
  }
  else
  {
    digitalWrite(direction_gpio_, HIGH);
    analogWrite(force_gpio_, -force_ * correction_factor_);
  }
}

//-----------------------------------------------------------------------------------------------------------------
void DCMotor::stepTwo()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void DCMotor::stepThree()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void DCMotor::stepFour()
{
  // Not used.
}