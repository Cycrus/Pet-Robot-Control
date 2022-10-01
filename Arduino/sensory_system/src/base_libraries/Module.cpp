/**********************************************************************
 * Module.cpp
 * 
 * Implementation of the module base class.
 * 
 * Author: Cyril Marx
 * Created: September 2022
 **********************************************************************/

#include "Module.hpp"

Module::Module() :
last_activation_time_(0),
max_steps_(4),
curr_step_(0)
{
  for(uint8_t i = 0; i < STEP_NUM; i++)
  {
    time_list_[i] = 0;
  }

  method_list_[0] = &Module::stepOne;
  method_list_[1] = &Module::stepTwo;
  method_list_[2] = &Module::stepThree;
  method_list_[3] = &Module::stepFour;
}

//-----------------------------------------------------------------------------------------------------------------
Module::~Module()
{
  
}

//-----------------------------------------------------------------------------------------------------------------
void Module::triggerModule(uint32_t curr_time)
{
  uint16_t time_diff = calcTimeDiff(curr_time);

  if(!triggeringRequirements())
  {
    return;
  }

  if(time_diff >= time_list_[curr_step_])
  {
    (this->*method_list_[curr_step_])();
    incrementCurrStep();
    last_activation_time_ = curr_time;
  }
}

//-----------------------------------------------------------------------------------------------------------------
void Module::setMaxSteps(uint8_t max_steps)
{
  max_steps_ = max_steps;
  if(max_steps_ > STEP_NUM)
  {
    max_steps_ = STEP_NUM;
  }
}

//-----------------------------------------------------------------------------------------------------------------
void Module::resetCurrStep()
{
  curr_step_ = 0;
}

//-----------------------------------------------------------------------------------------------------------------
uint8_t Module::getCurrStep()
{
  return curr_step_;
}

//-----------------------------------------------------------------------------------------------------------------
bool Module::triggeringRequirements()
{
  return true;
}

//-----------------------------------------------------------------------------------------------------------------
uint16_t Module::calcTimeDiff(uint32_t curr_time)
{
  uint16_t time_diff = 0;
  
  if(curr_time > last_activation_time_)
  {
    time_diff = curr_time - last_activation_time_;
  }
  else
  {
    last_activation_time_ = curr_time;
  }

  return time_diff;
}

//-----------------------------------------------------------------------------------------------------------------
void Module::incrementCurrStep()
{
  curr_step_++;
  if(curr_step_ >= max_steps_)
  {
    curr_step_ = 0;
  }
}
