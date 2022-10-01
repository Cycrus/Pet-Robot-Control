/**********************************************************************
 * GPSModule.cpp
 * 
 * Implementation of the BN-880 GPS module class.
 * 
 * Author: Cyril Marx
 * Created: October 2022
 **********************************************************************/

#include "GPSModule.hpp"

GPSModule::GPSModule(int8_t timezone_correction) :
gps_lat_(0.0),
gps_long_(0.0),
gps_year_(0),
gps_month_(0),
gps_day_(0),
gps_hour_(0),
gps_minute_(0),
gps_second_(0),
gps_centisecond_(0),
gps_speed_(0.0),
gps_altitude_(0),
gps_course_(0),
gps_satellite_num_(0),
date_validity_(false),
time_validity_(false),
location_validity_(false),
speed_validity_(false),
altitude_validity_(false),
course_validity_(false),
satellite_validity_(false),
timezone_correction_(timezone_correction)
{
  time_list_[0] = 16;
  setMaxSteps(2);
}

//-----------------------------------------------------------------------------------------------------------------
void GPSModule::initModule()
{
  GPS_UART.begin(9600);
}

//-----------------------------------------------------------------------------------------------------------------
int8_t GPSModule::getTimezoneCorrection()
{
  return timezone_correction_;
}

//-----------------------------------------------------------------------------------------------------------------
double GPSModule::getLat()
{
  return gps_lat_;
}

//-----------------------------------------------------------------------------------------------------------------
double GPSModule::getLon()
{
  return gps_lon_;
}

//-----------------------------------------------------------------------------------------------------------------
uint16_t GPSModule::getYear()
{
  return gps_year_;
}

//-----------------------------------------------------------------------------------------------------------------
uint16_t GPSModule::getMonth()
{
  return gps_month_;
}

//-----------------------------------------------------------------------------------------------------------------
uint16_t GPSModule::getDay()
{
  return gps_day_;
}

//-----------------------------------------------------------------------------------------------------------------
uint16_t GPSModule::getHour()
{
  return gps_hour_;
}

//-----------------------------------------------------------------------------------------------------------------
uint16_t GPSModule::getMinute()
{
  return gps_minute_;
}

//-----------------------------------------------------------------------------------------------------------------
uint16_t GPSModule::getSecond()
{
  return gps_second_;
}

//-----------------------------------------------------------------------------------------------------------------
uint16_t GPSModule::getCentisecond()
{
  return gps_centisecond_;
}

//-----------------------------------------------------------------------------------------------------------------
float GPSModule::getSpeed()
{
  return gps_speed_;
}

//-----------------------------------------------------------------------------------------------------------------
uint16_t GPSModule::getAltitude()
{
  return gps_altitude_;
}

//-----------------------------------------------------------------------------------------------------------------
int16_t GPSModule::getCourse()
{
  return gps_course_;
}

//-----------------------------------------------------------------------------------------------------------------
uint8_t GPSModule::getSatelliteNumber()
{
  return gps_satellite_num_;
}

//-----------------------------------------------------------------------------------------------------------------
bool GPSModule::isTimeValid()
{
  return time_validity_;
}

//-----------------------------------------------------------------------------------------------------------------
bool GPSModule::isDateValid()
{
  return date_validity_;
}

//-----------------------------------------------------------------------------------------------------------------
bool GPSModule::isLocationValid()
{
  return location_validity_;
}

//-----------------------------------------------------------------------------------------------------------------
bool GPSModule::isSpeedValid()
{
  return speed_validity_;
}

//-----------------------------------------------------------------------------------------------------------------
bool GPSModule::isAltitudeValid()
{
  return altitude_validity_;
}

//-----------------------------------------------------------------------------------------------------------------
bool GPSModule::isCourseValid()
{
  return course_validity_;
}

//-----------------------------------------------------------------------------------------------------------------
bool GPSModule::isSatelliteValid()
{
  return satellite_validity_;
}

//-----------------------------------------------------------------------------------------------------------------
void GPSModule::stepOne()
{
  while(GPS_UART.available())
  {
    module_object_.encode(GPS_UART.read())
  }
  GPS_UART.flush();

  location_validity_ = module_object_.location.isValid();
  date_validity_ = module_object_.date.isValid();
  time_validity_ = module_object_.time.isValid();
  speed_validity_ = module_object_.speed.isValid();
  altitude_validity_ = module_object_.speed.isValid();
  course_validity_ = module_object_.course.isValid(),
  satellite_validity_ = module_object_.satellites.isValid();

  if(location_validity_)
  {
    gps_lat_ = module_object_.location.lat();
    gps_lon_ = module_object_.location.lng();
  }

  if(date_validity_)
  {
    gps_year_ = module_object_.date.year();
    gps_month_ = module_object_.date.month();
    gps_day_ = module_object_.date.day();
  }

  if(time_validity_)
  {
    gps_hour_ = module_object_.time.hour() + timezone_correction_;
    gps_minute_ = module_object_.time.minute();
    gps_second_ = module_object_.time.second();
    gps_centisecond_ = module_object_.time.centisecond();
  }

  if(speed_validity_)
  {
    gps_speed_ = (float)module_object_.speed.kmph / 3.6;
  }
  else
  {
    gps_speed_ = 0.0;
  }

  if(altitude_validity_)
  {
    gps_altitude_ = module_object_.altitude.meters();
  }

  if(course_validity_)
  {
    gps_course_ = module_object_.course.deg();
  }
  
  if(satellite_validity_)
  {
    gps_satellite_num_ = module_object_.satellites.value();
  }
  else
  {
    gps_satellite_num_ = 0;
  }
}

//-----------------------------------------------------------------------------------------------------------------
void GPSModule::stepTwo()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void GPSModule::stepThree()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void GPSModule::stepFour()
{
  // Not used.
}
