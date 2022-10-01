/**********************************************************************
 * Module.hpp
 * 
 * The base class for module implementation. Contains default methods
 * to override, as well as a custom timer system.
 * 
 * Author: Cyril Marx
 * Created: September 2022
 **********************************************************************/

#ifndef MODULE_HPP
#define MODULE_HPP

#include <stdint.h>
#include "Arduino.h"

#define STEP_NUM 4

class Module
{
  public:
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor. Creates the base framework for dynamic method calling.
  //
  Module();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default copy constructor.
  //
  Module(const Module&) = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Virtual destructor.
  //
  virtual ~Module() = 0;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// The function to call to run the module base on this class. Works by iterating through the different virtual
  /// methods based on the times inserted in the time_list.
  ///
  /// @param curr_time  The current time in milliseconds since the start of the script.
  //
  void triggerModule(uint32_t curr_time);

  protected:
  uint8_t max_steps_;
  uint32_t last_activation_time_;
  uint16_t time_list_[STEP_NUM];
  void (Module::*method_list_[STEP_NUM])();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the actual maximum amount of steps for the module. Cannot exceed STEP_NUM.
  //
  void setMaxSteps(uint8_t max_steps);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Resets the current step back to 0.
  //
  void resetCurrStep();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// A method to override to set requirements that the triggerModule() function can even be called.
  ///
  /// @return   bool    If true, the triggerModule() function can be triggered.
  //
  bool triggeringRequirements();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// The first step the module can carry out in the loop. MUST be overridden, even if not used.
  //
  virtual void stepOne() = 0;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// The second step the module can carry out in the loop. MUST be overridden, even if not used.
  //
  virtual void stepTwo() = 0;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// The third step the module can carry out in the loop. MUST be overridden, even if not used.
  //
  virtual void stepThree() = 0;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// The fourth step the module can carry out in the loop. MUST be overridden, even if not used.
  //
  virtual void stepFour() = 0;

  private:
  uint8_t curr_step_;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Calculates the time difference between the last time getMeasurement() did something and the current time.
  /// If the timer overflows after about 50 days, the whole timing procedure starts at 0 again.
  ///
  /// @param curr_time  The current time in milliseconds since the start of the script.
  ///
  /// @return           The calculated difference.
  //
  uint16_t calcTimeDiff(uint32_t curr_time);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Increments the current step after getMeasurement() did something. If it exceeds the defined max steps the
  /// module can perform, it resets at 0.
  //
  void incrementCurrStep();
};

#endif //MODULE_HPP
