/**********************************************************************
 * RFIDReader.cpp
 * 
 * Implementation of the RFID reader class.
 * 
 * Author: Cyril Marx
 * Created: October 2022
 **********************************************************************/

#include "RFIDReader.hpp"

RFIDReader::RFIDReader(uint8_t rst_pin, uint8_t ss_pin) :
module_object_(rst_pin, ss_pin),
message_code_(0)
{
  time_list_[0] = 2;
  time_list_[1] = 2;
  time_list_[2] = 2;
  setMaxSteps(3);
}

//-----------------------------------------------------------------------------------------------------------------
void RIFDReader::initModule()
{
  SPI.begin();
  module_object_.PCD_Init();
  for (byte i = 0; i < 6; i++)
  {
    rfid_key_.keyByte[i] = 0xFF;
  }
}

//-----------------------------------------------------------------------------------------------------------------
uint8_t RFIDReader::getMessageCode()
{
  return message_code_;
}

//-----------------------------------------------------------------------------------------------------------------
bool RFIDReader::checkByteArray(byte *arr, String str)
  {
    int pos = 0;
    while(true)
    {
      if(arr[pos] == 0)
      {
        break;
      }

      if(pos > str.length())
      {
        break;
      }
      
      if(arr[pos] != (byte)str[pos])
      {
        return false;
      }

      pos++;
    }

    return true;
  }

//-----------------------------------------------------------------------------------------------------------------
void RFIDReader::stepOne()
{
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
}

//-----------------------------------------------------------------------------------------------------------------
void RFIDReader::stepTwo()
{
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
}

//-----------------------------------------------------------------------------------------------------------------
void RFIDReader::stepThree()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void RFIDReader::stepFour()
{
  // Not used.
}