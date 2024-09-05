/**********************************************************************
 * LedRing.hpp
 * 
 * Class responsible to control a LED element on the robot. Offers limited
 * capabilities by only coloring the complete LED element in a certain
 * color.
 * 
 * Author: Cyril Marx
 * Created: February 2023
 **********************************************************************/

#ifndef LEDRING_HPP
#define LEDRING_HPP

#include "Module.hpp"
#include <Adafruit_NeoPixel.h>

class LedRing : public Module
{
  public:
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor. Defines the pin and the number of leds in the element.
  ///
  /// @param  gpio_pin    The gpio number of the pin the led element is plug into.
  /// @param  led_number  The number of single leds on the led element.
  //
  LedRing(uint8_t gpio_pin, uint8_t led_number);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default copy constructor.
  //
  LedRing(const LedRing&) = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor. Frees memory from led element. Probably never called in a microprocessor.
  //
  ~LedRing();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Initializes the module by reserving memory and initializing the serial connection.
  //
  void initModule() override;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the color that the LED element should adopt in its next activation.
  /// @param  r   Red amount.
  /// @param  g   Green amount.
  /// @param  b   Blue amount.
  //
  void setColor(uint8_t r, uint8_t g, uint8_t b);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the current color of the module.
  ///
  /// @return   The color of the module as a single 32 bit number.
  //
  uint32_t getColor();

  private:
  uint32_t prev_color_;
  uint32_t color_;
  uint8_t r_;
  uint8_t g_;
  uint8_t b_;
  uint8_t gpio_pin_;
  uint8_t led_number_;
  Adafruit_NeoPixel *led_element_;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 1. Reconfigures the LED on the led element.
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

#endif // LEDRING_HPP