/**********************************************************************
 * BMP280Module.hpp
 * 
 * A class representing a single BMP280 Module.
 * Extends the base Module class.
 * 
 * Author: Cyril Marx
 * Created: September 2022
 **********************************************************************/

#ifndef BMP280MODULE_HPP
#define BMP280MODULE_HPP

#include <Adafruit_BMP280.h>
#include "../base_libraries/Module.hpp"

class BMP280Module : public Module
{
  public:
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor.
  //
  BMP280Module();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default copy constructor.
  //
  BMP280Module(const BMP280Module&) = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default destructor.
  //
  ~BMP280Module() = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Initializes the address of the module on the I2C bus.
  //
  void initModule();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the last valid temperature measured by the module in degree Celsius.
  //
  int16_t getTemperature();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the last valid pressure value measured by the module in hectopascal.
  //
  uint16_t getPressure();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the last valid altitude calculated by the module in meter.
  //
  uint16_t getAltitude();

  private:
  Adafruit_BMP280 module_object_;
  
  int16_t temperature_;
  uint16_t pressure_;
  uint16_t altitude_;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 1. Measures temperature.
  //
  void stepOne() override;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 2. Measures pressure.
  //
  void stepTwo() override;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 3. Calculates altitude.
  //
  void stepThree() override;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 4. Is not called.
  //
  void stepFour() override;
};

#endif //BMP280MODULE_HPP
