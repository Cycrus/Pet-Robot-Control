/**********************************************************************
 * CurrentSensor.hpp
 * 
 * A class representing a 20A current sensor Module.
 * Extends the base Module class.
 * 
 * Author: Cyril Marx
 * Created: October 2022
 **********************************************************************/

#ifndef CURRENTSENSOR_HPP
#define CURRENTSENSOR_HPP

#include "../base_libraries/Module.hpp"

#define NULLVALUE 531.5
#define VpA 125           // Value has been empirically derived
#define VOLTFACTOR 5000

class CurrentSensor : public Module
{
  public:
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor. Defines the pin and type of the DHT module.
  //
  CurrentSensor(uint8_t analog_pin);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default copy constructor.
  //
  CurrentSensor(const CurrentSensor&) = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default destructor.
  //
  ~CurrentSensor() = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Initializes the module.
  //
  void initModule();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Getters.
  //
  float getCurrent();
  float getCurrentPerHour();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Clears the Ampere current buffer back to 0.0. Should be called after data was sent out.
  //
  void resetBuffers();

  private:
  float mAh_;
  float ampere_;
  uint8_t module_pin_;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 1. Collect data and convert to usable values.
  //
  void stepOne() override;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 2. Is not called.
  //
  void stepTwo() override;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 3. Is not called.
  //
  void stepThree() override;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 4. Is not called.
  //
  void stepFour() override;
};

#endif //CURRENTSENSOR_HPP
