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
ModuleSyncer::addModule(Module &new_module)
{
  module_list_.push_back(module);
  module_number_++;
}

//-----------------------------------------------------------------------------------------------------------------
void ModuleSyncer::initAllModules()
{
  for(Module &module : module_list_)
  {
    module.initModule();
  }
}

//-----------------------------------------------------------------------------------------------------------------
void ModuleSyncer::triggerModule()
{
  module_list.at(curr_module_).triggerModule();
}