/**********************************************************************
 * ModuleSyncer.hpp
 * 
 * A wrapper class around multiple modules of the same type used to
 * synchronize them to prevent module interference, if this is an issue.
 * Currently only alternates the activation of all modules.
 * 
 * Author: Cyril Marx
 * Created: October 2022
 **********************************************************************/

#ifndef MODULESYNCER_HPP
#define MODULESYNCER_HPP

#include "Module.hpp"
#include <ArduinoSTL.h>

class ModuleSyncer
{
  public:
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor.
  //
  ModuleSyncer();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default copy constructor.
  //
  ModuleSyncer(const ModuleSyncer&) = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default destructor.
  //
  ~ModuleSyncer() = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Adds a module to the .
  ///
  /// @param  new_module  The new module to add to the internal module vector.
  //
  void addModule(Module *new_module);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Initializes all modules in the internal module vector.
  //
  void initAllModules();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Triggers one of the modules based on the internal counter curr_module_.
  ///
  /// @param  curr_time   The time of the current CPU loop.
  //
  void triggerModule(uint32_t curr_time);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Returns one of the included modules based on its id in the vector. Returns nullptr if id is invalid.
  ///
  /// @param  module_id   The id of the module to return.
  ///
  /// @return Module*     The module with the given id in the vector.
  //
  Module *getModule(uint8_t module_id);

  private:
  uint8_t module_number_;
  uint8_t curr_module_;
  std::vector<Module*> module_list_;
};

#endif //MODULESYNCER_HPP