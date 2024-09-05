/**********************************************************************
 * HumidityModule.hpp
 * 
 * A class representing a single DHT 11 humidity Module.
 * Extends the base Module class.
 * 
 * Author: Cyril Marx
 * Created: September 2022
 **********************************************************************/

#ifndef HUMIDITYMODULE_HPP
#define HUMIDITYMODULE_HPP

#include <DHT.h>
#include "Module.hpp"

class HumidityModule : public Module
{
  public:
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor. Defines the pin and type of the DHT module.
  //
  HumidityModule(uint8_t pin, uint8_t type);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default copy constructor.
  //
  HumidityModule(const HumidityModule&) = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default destructor.
  //
  ~HumidityModule() = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Initializes the module.
  //
  void initModule();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the last valid temperature measured by the module in degree Celsius.
  //
  int16_t getTemperature();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the last valid humidity value measured by the module in percent.
  //
  uint8_t getHumidity();

  private:
  DHT module_object_;
  
  int16_t temperature_;
  uint8_t humidity_;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 1. Measures temperature.
  //
  void stepOne() override;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 2. Measures humidity.
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

#endif //HUMIDITYMODULE_HPP
