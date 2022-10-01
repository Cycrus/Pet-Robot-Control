/**********************************************************************
 * CurrentSensor.cpp
 * 
 * Implementation of the current sensor module class.
 * 
 * Author: Cyril Marx
 * Created: October 2022
 **********************************************************************/

#include "CurrentSensor.hpp"

CurrentSensor::CurrentSensor(uint8_t analog_pin) :
mAh_(0.0),
ampere_(0.0),
module_pin_(analog_pin)
{
  time_list_[0] = 16;
  setMaxSteps(1);
}

//-----------------------------------------------------------------------------------------------------------------
void CurrentSensor::initModule()
{

}

//-----------------------------------------------------------------------------------------------------------------
float CurrentSensor::getCurrent()
{
  return ampere_;
}

//-----------------------------------------------------------------------------------------------------------------
float CurrentSensor::getCurrentPerHour()
{
  return mAh_;
}

//-----------------------------------------------------------------------------------------------------------------
void CurrentSensor::resetBuffers()
{
  mAh_ = 0.0;
  ampere_ = 0.0;
}

//-----------------------------------------------------------------------------------------------------------------
void CurrentSensor::stepOne()
{
  double sensor_value = 0.0;
  sensor_value = analogRead(module_pin_);
  sensor_value -= NULLVALUE;
  if(sensor_value < 0.0)
  {
    sensor_value = 0.0;
  }

  float sensor_voltage = (sensor_value / 1024.0) * VOLTFACTOR;
  mAh_ = (sensor_voltage /  VpA);

  double mA_ms = mAh_ / 3600000;
  ampere_ += mA_ms * last_activation_time_;
}

//-----------------------------------------------------------------------------------------------------------------
void CurrentSensor::stepTwo()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void CurrentSensor::stepThree()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void CurrentSensor::stepFour()
{
  // Not used.
}
