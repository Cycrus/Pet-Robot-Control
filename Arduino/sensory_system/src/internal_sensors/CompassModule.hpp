/**********************************************************************
 * CompassModule.hpp
 * 
 * A class representing a HMC5883 compass Module.
 * Extends the base Module class.
 * 
 * Author: Cyril Marx
 * Created: October 2022
 **********************************************************************/

#ifndef COMPASSMODULE_HPP
#define COMPASSMODULE_HPP

#include <Wire.h>
#include <Adafruit_HMC5883_U.h>
#include "../utilities/Module.hpp"

class CompassModule : public Module
{
  public:
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor. Defines the pin and type of the DHT module.
  //
  CompassModule(uint16_t module_id, float declination_angle);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default copy constructor.
  //
  CompassModule(const CompassModule&) = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default destructor.
  //
  ~CompassModule() = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Initializes the module.
  //
  void initModule();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the declination angle to a new value.
  //
  void setDeclinationAngle(float declination_angle);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Getters.
  //
  float getX();
  float getY();
  float getZ();
  float getHeading();

  private:
  float mag_x_;
  float mag_y_;
  float mag_z_;
  float heading_;
  float declination_angle_;
  sensors_event_t module_event_;
  Adafruit_HMC5883_Unified module_object_;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 1. Collects module data.
  //
  void stepOne() override;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 2. Corrects and assigns data.
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

#endif //COMPASSMODULE_HPP
