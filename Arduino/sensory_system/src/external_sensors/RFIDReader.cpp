/**********************************************************************
 * RFIDReader.cpp
 * 
 * Implementation of the RFID reader class.
 * 
 * Author: Cyril Marx
 * Created: October 2022
 **********************************************************************/

#include "RFIDReader.hpp"

RFIDReader::RFIDReader(uint8_t ss_pin, uint8_t rst_pin) :
module_object_(ss_pin, rst_pin),
message_code_(0)
{
  time_list_[0] = 100;
  time_list_[1] = 1;
  setMaxSteps(2);
}

//-----------------------------------------------------------------------------------------------------------------
void RFIDReader::initModule()
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

void RFIDReader::resetMessageCode()
{
  message_code_ = 0;
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
bool RFIDReader::triggeringRequirements()
{
  if(getCurrStep() == 0)
  {
    return true;
  }
  
  if(!module_object_.PICC_IsNewCardPresent()) {
    return false;
  }

  if(!module_object_.PICC_ReadCardSerial()) {
    return false;
  }

  return true;
}

//-----------------------------------------------------------------------------------------------------------------
void RFIDReader::stepOne()
{
  resetMessageCode();
}

//-----------------------------------------------------------------------------------------------------------------
void RFIDReader::stepTwo()
{
  MFRC522::StatusCode status;
  
  uint8_t block = 1;
  uint8_t length = MSG_LEN;
  uint8_t payload_buffer[length];

  status = module_object_.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &rfid_key_, &(module_object_.uid));
  if(status != MFRC522::STATUS_OK)
  {
    module_object_.PCD_StopCrypto1();
    resetCurrStep();
    return;
  }

  status = module_object_.MIFARE_Read(block, payload_buffer, &length);
  if(status != MFRC522::STATUS_OK)
  {
    module_object_.PCD_StopCrypto1();
    resetCurrStep();
    return;
  }
  else
  {
    message_code_ = payload_buffer[0];
  }
  
  module_object_.PCD_StopCrypto1();
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
