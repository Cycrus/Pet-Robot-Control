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
#include <vector>

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
  //
  void triggerModule();

   getModule(uint8_t)

  private:
  uint8_t module_number_;
  uint8_t curr_module_;
  std::vector<Module*> module_list_;
};

#endif //MODULESYNCER_HPP