#include <Wire.h>
#include "JY901.h"

#define SENSOR Serial2

void setup() 
{
  Serial.begin(9600);
  SENSOR.begin(9600);

  //Angle Initialization (Set z to 0)
  byte data0[] = {0xFF, 0xAA, 0x52};
  SENSOR.write(data0, 3);

  delay(100);

  //Accelerometer Calibration
  byte data1[] = {0xFF, 0xAA, 0x67};
  SENSOR.write(data1, 3);

  delay(100);

  //Wake Up
  byte data2[] = {0xFF, 0xAA, 0x60};
  SENSOR.write(data2, 3);
  
  delay(100);
    
  // Horizontal Installation
  byte data3[] = {0xFF, 0xAA, 0x61};
  SENSOR.write(data3, 3);

  delay(100);
}

void loop() 
{
  //print received data. Data was received in serialEvent;
  Serial.print("Acc:");Serial.print((float)JY901.stcAcc.a[0]/32768*16);Serial.print(" ");Serial.print((float)JY901.stcAcc.a[1]/32768*16);Serial.print(" ");Serial.println((float)JY901.stcAcc.a[2]/32768*16);
  
  Serial.print("Gyro:");Serial.print((float)JY901.stcGyro.w[0]/32768*2000);Serial.print(" ");Serial.print((float)JY901.stcGyro.w[1]/32768*2000);Serial.print(" ");Serial.println((float)JY901.stcGyro.w[2]/32768*2000);
  
  Serial.print("Angle:");Serial.print((float)JY901.stcAngle.Angle[0]/32768*180);Serial.print(" ");Serial.print((float)JY901.stcAngle.Angle[1]/32768*180);Serial.print(" ");Serial.println((float)JY901.stcAngle.Angle[2]/32768*180);
  
  Serial.println("");

  delay(2000);
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent2() 
{
  while (SENSOR.available())
  {
    JY901.CopeSerialData(SENSOR.read()); //Call JY901 data cope function
  }
  SENSOR.flush();
}
