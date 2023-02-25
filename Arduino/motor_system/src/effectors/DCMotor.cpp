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
force_(0)
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
void DCMotor::setForce(int16_t force)
{
  force_ = force;
}

//-----------------------------------------------------------------------------------------------------------------
int8_t DCMotor::getForce()
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
    analogWrite(force_gpio_, force_ * correction_factor_ * -1);
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