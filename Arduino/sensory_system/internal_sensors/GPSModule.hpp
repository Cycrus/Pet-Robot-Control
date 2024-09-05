/**********************************************************************
 * GPSModule.hpp
 * 
 * A class representing a BN-880 GPS module.
 * Extends the base Module class.
 * 
 * Author: Cyril Marx
 * Created: October 2022
 **********************************************************************/

#ifndef GPSMODULE_HPP
#define GPSMODULE_HPP

#include <TinyGPSPlus.h>
#include "../utilities/Module.hpp"

#define GPS_UART Serial1

class GPSModule : public Module
{
  public:
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor. Defines the pin and type of the DHT module.
  //
  GPSModule(int8_t timezone_correction);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default copy constructor.
  //
  GPSModule(const GPSModule&) = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default destructor.
  //
  ~GPSModule() = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Initializes the module.
  //
  void initModule();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Sets a new timezone correction for the module.
  //
  void setTimezoneCorrection(int8_t value);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Getters.
  //
  int8_t getTimezoneCorrection();
  double getLat();
  double getLon();
  uint16_t getYear();
  uint16_t getMonth();
  uint16_t getDay();
  uint16_t getHour();
  uint16_t getMinute();
  uint16_t getSecond();
  uint16_t getCentisecond();
  float getSpeed();
  uint16_t getAltitude();
  int16_t getCourse();
  uint8_t getSatelliteNumber();
  bool isDateValid();
  bool isTimeValid();
  bool isLocationValid();
  bool isSpeedValid();
  bool isAltitudeValid();
  bool isCourseValid();
  bool isSatelliteValid();

  private:
  int8_t timezone_correction_;
  double gps_lat_;
  double gps_lon_;
  uint16_t gps_year_;
  uint16_t gps_month_;
  uint16_t gps_day_;
  uint16_t gps_hour_;
  uint16_t gps_minute_;
  uint16_t gps_second_;
  uint16_t gps_centisecond_;
  float gps_speed_;
  uint16_t gps_altitude_;
  int16_t gps_course_;
  uint8_t gps_satellite_num_;
  bool date_validity_;
  bool time_validity_;
  bool location_validity_;
  bool speed_validity_;
  bool altitude_validity_;
  bool course_validity_;
  bool satellite_validity_;

  TinyGPSPlus module_object_;

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

#endif //GPSMODULE_HPP
