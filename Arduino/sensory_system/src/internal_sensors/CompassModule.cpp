/**********************************************************************
 * CompassModule.cpp
 * 
 * Implementation of the HMC5883 compass module class.
 * 
 * Author: Cyril Marx
 * Created: October 2022
 **********************************************************************/

#include "CompassModule.hpp"

CompassModule::CompassModule(uint16_t module_id, float declination_angle) :
module_object_(module_id),
declination_angle_(declination_angle),
mag_x_(0.0),
mag_y_(0.0),
mag_z_(0.0),
heading_(0.0)
{
  time_list_[0] = 14;
  time_list_[1] = 0;
  setMaxSteps(2);
}

//-----------------------------------------------------------------------------------------------------------------
void CompassModule::initModule()
{
  module_object_.begin();
}

//-----------------------------------------------------------------------------------------------------------------
void CompassModule::setDeclinationAngle(float declination_angle)
{
  declination_angle_ = declination_angle;
}

//-----------------------------------------------------------------------------------------------------------------
float CompassModule::getX()
{
  return mag_x_;
}

//-----------------------------------------------------------------------------------------------------------------
float CompassModule::getY()
{
  return mag_y_;
}

//-----------------------------------------------------------------------------------------------------------------
float CompassModule::getZ()
{
  return mag_z_;
}

//-----------------------------------------------------------------------------------------------------------------
float CompassModule::getHeading()
{
  return heading_;
}

//-----------------------------------------------------------------------------------------------------------------
void CompassModule::stepOne()
{
  module_object_.getEvent(&module_event_);
}

//-----------------------------------------------------------------------------------------------------------------
void CompassModule::stepTwo()
{
  mag_x_ = module_event_.magnetic.x;
  mag_y_ = module_event_.magnetic.y;
  mag_z_ = module_event_.magnetic.z;
  heading_ = atan2(mag_y_, mag_x_);

  heading_ += declination_angle_;

  if(heading_ < 0)
  {
    heading_ += 2 * PI;
  }

  if(heading_ > 2 * PI)
  {
    heading_ -= 2 * PI;
  }
}

//-----------------------------------------------------------------------------------------------------------------
void CompassModule::stepThree()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void CompassModule::stepFour()
{
  // Not used.
}
