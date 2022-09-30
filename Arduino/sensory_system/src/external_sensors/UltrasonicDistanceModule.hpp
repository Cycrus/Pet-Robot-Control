/**********************************************************************
 * UltrasonicDistance.hpp
 * 
 * A class representing a single ultrasonic distance measuring module.
 * Extends the Module base class.
 * 
 * Author: Cyril Marx
 * Created: September 2022
 **********************************************************************/

#ifndef ULTRASONICDISTANCEMODULE_HPP
#define ULTRASONICDISTANCEMODULE_HPP

#include "../base_libraries/Module.hpp"

#define SONIC_SPEED 0.03432
#define MAX_DISTANCE 500

class UltrasonicDistanceModule : public Module
{
  public:
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor. Sets the timing and the pins of the module.
  ///
  /// @param trigger_pin    The pin used for triggering the ultrasound signal.
  /// @param echo_pin       The pin used for measuring the time the sound needs to return.
  //
  UltrasonicDistanceModule(uint8_t trigger_pin, uint8_t echo_pin);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default copy constructor.
  //
  UltrasonicDistanceModule(const UltrasonicDistanceModule&) = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default destructor.
  //
  ~UltrasonicDistanceModule() = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Initializes the pins of the module.
  //
  void initModule();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the last valid distance measured by the module in cm.
  //
  int16_t getDistance();

  private:
  int16_t distance_;
  uint8_t trigger_pin_;
  uint8_t echo_pin_;
  
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 1. Turns the ultrasound off.
  //
  void stepOne() override;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 2. Turns the ultrasound on.
  //
  void stepTwo() override;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 3. Turns the ultrasound off and measures the distance.
  //
  void stepThree() override;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 4. Is not called.
  //
  void stepFour() override;
};

#endif //ULTRASONICDISTANCEMODULE_HPP
