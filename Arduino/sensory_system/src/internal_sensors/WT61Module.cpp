/**********************************************************************
 * WT61Module.cpp
 * 
 * Implementation of the WT61 module class.
 * 
 * Author: Cyril Marx
 * Created: October 2022
 **********************************************************************/

#include "WT61Module.hpp"

WT61Module::WT61Module(bool calibrate) :
acc_x_(0.0),
acc_y_(0.0),
acc_z_(0.0),
gyr_x_(0.0),
gyr_y_(0.0),
gyr_z_(0.0),
ang_x_(0.0),
ang_y_(0.0),
ang_z_(0.0),
do_initial_calibration_(calibrate)
{
  time_list_[0] = 16;
  setMaxSteps(1);

  acc_correction_ = 32768 * 16;
  gyr_correction_ = 32768 * 2000;
  ang_correction_ = 32768 * 180;
}

//-----------------------------------------------------------------------------------------------------------------
void WT61Module::initModule()
{
  WT61_UART.begin(9600);

  if(do_initial_calibration_)
  {
    //Angle Initialization (Set z to 0)
    byte data0[] = {0xFF, 0xAA, 0x52};
    WT61_UART.write(data0, 3);

    delay(50);

    //Accelerometer Calibration
    byte data1[] = {0xFF, 0xAA, 0x67};
    WT61_UART.write(data1, 3);

    delay(50);
  }

  //Wake Up
  byte data2[] = {0xFF, 0xAA, 0x60};
  WT61_UART.write(data2, 3);
  
  delay(20);
    
  // Horizontal Installation
  byte data3[] = {0xFF, 0xAA, 0x61};
  WT61_UART.write(data3, 3);

  delay(20);
}

//-----------------------------------------------------------------------------------------------------------------
void WT61Module::stepOne()
{
  while (WT61_UART.available())
  {
    JY901.CopeSerialData(SENSOR.read());
  }
  WT61_UART.flush();

  acc_x_ = (float)JY901.stcAcc.a[0] / acc_correction_;
  acc_y_ = (float)JY901.stcAcc.a[1] / acc_correction_;
  acc_z_ = (float)JY901.stcAcc.a[2] / acc_correction_;
  gyr_x_ = (float)JY901.stcGyro.w[0] / gyr_correction_;
  gyr_y_ = (float)JY901.stcGyro.w[1] / gyr_correction_;
  gyr_z_ = (float)JY901.stcGyro.w[2] / gyr_correction_;
  ang_x_ = (float)JY901.stcAngle.Angle[0] / ang_correction_;
  ang_y_ = (float)JY901.stcAngle.Angle[1] / ang_correction_;
  ang_z_ = (float)JY901.stcAngle.Angle[2] / ang_correction_;
}

//-----------------------------------------------------------------------------------------------------------------
void WT61Module::stepTwo()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void WT61Module::stepThree()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void WT61Module::stepFour()
{
  // Not used.
}
