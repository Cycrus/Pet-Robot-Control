/**********************************************************************
 * DCMotor.hpp
 * 
 * Class responsible to control a DC Motor with an H bridge controller.
 * 
 * Author: Cyril Marx
 * Created: February 2023
 **********************************************************************/

#ifndef DCMOTOR_HPP
#define DCMOTOR_HPP

#include "../utilities/Module.hpp"

class DCMotor : public Module
{
  public:
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor. Defines the pins and the correction factor of the motors force.
  ///
  /// @param  force_gpio          The gpio number of the pin the force data is transferred to. Must be PWM.
  /// @param  direction_gpio      The gpio number of the pin the direction data is transferred to.
  /// @param  correction_factor   A factor to correct the force of the motor. Useful for motor synchronization.
  //
  DCMotor(uint8_t force_gpio, uint8_t direction_gpio, float correction_factor = 1.0);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default copy constructor.
  //
  DCMotor(const DCMotor&) = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default destructor.
  //
  ~DCMotor() = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Initializes the module by setting the GPIO pins accordingly.
  //
  void initModule() override;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the force of the motor. -128 - 128.
  ///
  /// @param  force   The force of the motor.
  //
  void setForce(int16_t force);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the force of the motor.
  ///
  /// @param  force   The force of the motor.
  //
  int8_t getForce();

  private:
  uint8_t force_gpio_;
  uint8_t direction_gpio_;
  int16_t force_;
  float correction_factor_;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 1. Sets the force and direction of the motor.
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

#endif // DCMOTOR_HPP