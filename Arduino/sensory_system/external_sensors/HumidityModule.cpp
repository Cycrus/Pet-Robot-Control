/**********************************************************************
 * HumidityModule.cpp
 * 
 * Implementation of the DHT 11 humidity module class.
 * 
 * Author: Cyril Marx
 * Created: September 2022
 **********************************************************************/

#include "HumidityModule.hpp"

HumidityModule::HumidityModule(uint8_t pin, uint8_t type) :
module_object_(pin, type),
temperature_(0),
humidity_(0)
{
  time_list_[0] = 5;
  time_list_[1] = 5;
  setMaxSteps(2);
}

//-----------------------------------------------------------------------------------------------------------------
void HumidityModule::initModule()
{
  module_object_.begin();
}

//-----------------------------------------------------------------------------------------------------------------

int16_t HumidityModule::getTemperature()
{
  return temperature_;
}

//-----------------------------------------------------------------------------------------------------------------
uint8_t HumidityModule::getHumidity()
{
  return humidity_;
}

//-----------------------------------------------------------------------------------------------------------------
void HumidityModule::stepOne()
{
  temperature_ = module_object_.readTemperature();
}

//-----------------------------------------------------------------------------------------------------------------
void HumidityModule::stepTwo()
{
  humidity_ = module_object_.readHumidity();
}

//-----------------------------------------------------------------------------------------------------------------
void HumidityModule::stepThree()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void HumidityModule::stepFour()
{
  // Not used.
}
