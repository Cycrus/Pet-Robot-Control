/**********************************************************************
 * GasModule.hpp
 * 
 * A class representing a single MQ135 gas sensor module.
 * Extends the base Module class.
 * 
 * Author: Cyril Marx
 * Created: September 2022
 **********************************************************************/

#ifndef GASMODULE_HPP
#define GASMODULE_HPP

#include "../base_libraries/MQ135.h"
#include "../utilities/Module.hpp"

class GasModule : public Module
{
  public:
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor.
  //
  GasModule(uint8_t analog_pin);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default copy constructor.
  //
  GasModule(const GasModule&) = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default destructor.
  //
  ~GasModule() = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Calibrates the module with the current gas PPM value.
  //
  void initModule();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the last valid temperature measured by the module in degree Celsius.
  //
  float getGasPPM();
  
  private:
  MQ135 module_object_;
  float gas_ppm_;
  float rzero_;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 1. Measures gas ppm.
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

#endif //GASMODULE_HPP
