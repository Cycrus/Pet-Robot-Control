/**********************************************************************
 * LedRing.cpp
 * 
 * Implementation of the LedRing class.
 * 
 * Author: Cyril Marx
 * Created: February 2023
 **********************************************************************/

#include "LedRing.hpp"

LedRing::LedRing(uint8_t gpio_pin, uint8_t led_number) :
color_(0),
prev_color_(0),
r_(0),
g_(0),
b_(0),
gpio_pin_(gpio_pin),
led_number_(led_number),
led_element_(nullptr)
{
  time_list_[0] = 50;
  setMaxSteps(1);
}

//-----------------------------------------------------------------------------------------------------------------
LedRing::~LedRing()
{
  if(led_element_ != nullptr)
  {
    free(led_element_);
    led_element_ = nullptr;
  }
}

//-----------------------------------------------------------------------------------------------------------------
void LedRing::initModule()
{
  led_element_ = new Adafruit_NeoPixel(led_number_, gpio_pin_, NEO_GRB + NEO_KHZ800);
  led_element_->begin();
  led_element_->clear();
  led_element_->show();
}

//-----------------------------------------------------------------------------------------------------------------
void LedRing::setColor(uint8_t r, uint8_t g, uint8_t b)
{
  r_ = r;
  g_ = g;
  b_ = b;
  color_ = led_element_->Color(r, g, b);
}

//-----------------------------------------------------------------------------------------------------------------
uint32_t LedRing::getColor()
{
  return color_;
}

//-----------------------------------------------------------------------------------------------------------------
void LedRing::stepOne()
{
  if(color_ != prev_color_)
  {
    led_element_->fill(color_, 0, led_number_);
    led_element_->show();
    prev_color_ = color_;
  }
}

//-----------------------------------------------------------------------------------------------------------------
void LedRing::stepTwo()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void LedRing::stepThree()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void LedRing::stepFour()
{
  // Not used.
}