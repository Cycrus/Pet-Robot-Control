/**********************************************************************
 * WT61Module.hpp
 * 
 * A class representing a WT61 gyroscope and accelerator module.
 * Extends the base Module class.
 * 
 * Author: Cyril Marx
 * Created: October 2022
 **********************************************************************/

#ifndef WT61MODULE_HPP
#define WT61MODULE_HPP

#include "Module.hpp"
#include "JY901.h"

#define WT61_UART Serial2

class WT61Module : public Module
{
  public:
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor. Defines the pin and type of the DHT module.
  //
  WT61Module(bool calibrate);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default copy constructor.
  //
  WT61Module(const WT61Module&) = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default destructor.
  //
  ~WT61Module() = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Initializes the module.
  //
  void initModule();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Getters.
  //
  float getAccX();
  float getAccY();
  float getAccZ();
  float getGyrX();
  float getGyrY();
  float getGyrZ();
  float getAngX();
  float getAngY();
  float getAngZ();

  private:
  float acc_x_;
  float acc_y_;
  float acc_z_;
  float gyr_x_;
  float gyr_y_;
  float gyr_z_;
  float ang_x_;
  float ang_y_;
  float ang_z_;

  bool do_initial_calibration_;

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

#endif //WT61MODULE_HPP
