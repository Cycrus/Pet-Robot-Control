/**********************************************************************
 * module.cpp
 * 
 * Implementation of the ultrasonic distance measuring base class.
 * 
 * Author: Cyril Marx
 * Created: September 2022
 **********************************************************************/

 #include "UltrasonicDistanceModule.hpp"

UltrasonicDistanceModule::UltrasonicDistanceModule(uint8_t trigger_pin, uint8_t echo_pin) :
distance_(0),
trigger_pin_(trigger_pin),
echo_pin_(echo_pin)
{
  time_list_[0] = 0;
  time_list_[1] = 5;
  time_list_[2] = 10;

  max_steps_ = 3;
}

//-----------------------------------------------------------------------------------------------------------------
UltrasonicDistanceModule::~UltrasonicDistanceModule()
{
  
}

//-----------------------------------------------------------------------------------------------------------------
void UltrasonicDistanceModule::initModule()
{
  pinMode(trigger_pin_, OUTPUT);
  pinMode(echo_pin_, INPUT);
}

//-----------------------------------------------------------------------------------------------------------------
int16_t UltrasonicDistanceModule::getDistance()
{
  return distance_;
}

//-----------------------------------------------------------------------------------------------------------------
void UltrasonicDistanceModule::stepOne()
{
  digitalWrite(trigger_pin_, LOW);
}

//-----------------------------------------------------------------------------------------------------------------
void UltrasonicDistanceModule::stepTwo()
{
  digitalWrite(trigger_pin_, HIGH);
}

//-----------------------------------------------------------------------------------------------------------------
void UltrasonicDistanceModule::stepThree()
{
  digitalWrite(trigger_pin_, LOW);
  int16_t duration = pulseIn(echo_pin_, HIGH);
  int16_t distance = (duration / 2) * SONIC_SPEED;

  if(distance > MAX_DISTANCE)
  {
    distance_ = 500;
  }
  else if(distance > 0)
  {
    distance_ = distance;
  }
}

//-----------------------------------------------------------------------------------------------------------------
void UltrasonicDistanceModule::stepFour()
{
  
}
