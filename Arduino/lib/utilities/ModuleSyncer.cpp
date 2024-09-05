/**********************************************************************
 * ModuleSyncer.cpp
 * 
 * Implementation of the ultrasonic distance syncing class.
 * 
 * Author: Cyril Marx
 * Created: October 2022
 **********************************************************************/

#include "ModuleSyncer.hpp"

ModuleSyncer::ModuleSyncer() :
module_number_(0),
curr_module_(0)
{

}

//-----------------------------------------------------------------------------------------------------------------
void ModuleSyncer::addModule(Module *new_module)
{
  module_list_.push_back(new_module);
  module_number_++;
}

//-----------------------------------------------------------------------------------------------------------------
void ModuleSyncer::initAllModules()
{
  for(Module *module : module_list_)
  {
    module->initModule();
  }
}

//-----------------------------------------------------------------------------------------------------------------
void ModuleSyncer::triggerModule(uint32_t curr_time)
{
  Module *curr_module_instance = module_list_.at(curr_module_);
  curr_module_instance->triggerModule(curr_time);
  if(curr_module_instance->getCurrStep() == 0)
  {
    curr_module_++;
    if(curr_module_ >= module_number_)
    {
      curr_module_ = 0;
    }
  }
}

//-----------------------------------------------------------------------------------------------------------------
Module *ModuleSyncer::getModule(uint8_t module_id)
{
  if(module_id >= module_number_)
  {
    return nullptr;
  }
  return module_list_.at(module_id);
}