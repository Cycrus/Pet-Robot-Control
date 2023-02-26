/**********************************************************************
 * ServoMotor.hpp
 * 
 * Class responsible to control a servo motor with a PCA9685 servo driver.
 * 
 * Author: Cyril Marx
 * Created: February 2023
 **********************************************************************/

#ifndef SERVOMOTOR_HPP
#define SERVOMOTOR_HPP

#include "../utilities/Module.hpp"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class ServoMotor : public Module
{
  public:
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor. Sets all critical values of the motor.
  ///
  /// @param  servo_id       The id of the servo on the driver board.
  /// @param  default_pos    The default (relaxed) position of the servo motor.
  /// @param  min_pos        The minimum position the servo motor can have.
  /// @param  max_pos        The maximum position the servo motor can have.
  //
  ServoMotor(uint8_t servo_id, uint16_t default_pos, uint16_t min_pos, uint16_t max_pos);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default copy constructor.
  //
  ServoMotor(const ServoMotor&) = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default destructor.
  //
  ~ServoMotor() = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Assigns the driver device where the servo is plugged into to the object.
  ///
  /// @param  servo_driver    The object representing the servo driver device.
  //
  void assignDriver(Adafruit_PWMServoDriver *servo_driver);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Initializes the module by setting the GPIO pins accordingly.
  //
  void initModule();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the driver of the servo motor.
  ///
  /// @return   The driver device object of the motor.
  //
  Adafruit_PWMServoDriver *getDriver();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the movement speed for the servo motor.
  ///
  /// @param  speed   The new speed and direction of the servo.
  //
  void setForce(int8_t speed);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the current step size of the driver.
  ///
  /// @return   The current step size of the driver.
  //
  int8_t getStepSize();

  private:
  uint8_t servo_id_;
  uint16_t curr_pos_;
  uint16_t default_pos_;
  uint16_t min_pos_;
  uint16_t max_pos_;
  int8_t step_size_;
  int8_t max_step_size_;
  int8_t min_step_size_;
  Adafruit_PWMServoDriver *servo_driver_;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Performs a single step of the servo motor depending on all stored parameters.
  //
  void performStep();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 1. Sets the motors to the given value.
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

#endif // SERVOMOTOR_HPP