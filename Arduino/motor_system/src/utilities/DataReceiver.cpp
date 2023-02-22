/**********************************************************************
 * DataReceiver.cpp
 * 
 * Implementation of the DataReceiver.
 * 
 * Author: Cyril Marx
 * Created: February 2023
 **********************************************************************/

#include "DataReceiver.hpp"

DataReceiver::DataReceiver(uint32_t baud_rate, uint16_t buffer_size) :
baud_rate_(baud_rate),
max_buffer_size_(buffer_size),
curr_buffer_size_(0),
data_buffer_(nullptr),
read_state_(ReadState::SEARCH_DATA)
{
  time_list_[0] = 0;
  setMaxSteps(1);
}

//-----------------------------------------------------------------------------------------------------------------
DataReceiver::~DataReceiver()
{
  if(data_buffer_ != nullptr)
  {
    free(data_buffer_);
  }
}

//-----------------------------------------------------------------------------------------------------------------
void DataReceiver::initModule()
{
  if(!Serial)
  {
    Serial.begin(baud_rate_);
  }
  data_buffer_ = (uint8_t*)malloc(max_buffer_size_);
  for(uint16_t byte = 0; byte < max_buffer_size_; byte++)
  {
    data_buffer_[byte] = 0;
  }
}

//-----------------------------------------------------------------------------------------------------------------
int8_t DataReceiver::getSignedByte(uint16_t pos)
{
  if(pos >= curr_buffer_size_)
  {
    return 0;
  }

  int8_t data = (int8_t)data_buffer_[pos];
  return data;
}

int16_t DataReceiver::getSignedShort(uint16_t pos)
{
  if(pos + 1 >= curr_buffer_size_)
  {
    return 0;
  }

  int16_t data = *((int16_t*)(&data_buffer_[pos]));
  return data;
}

int32_t DataReceiver::getSignedInt(uint16_t pos)
{
  if(pos + 3 >= curr_buffer_size_)
  {
    return 0;
  }

  int32_t data = *((int32_t*)(&data_buffer_[pos]));
  return data;
}

float DataReceiver::getFloat(uint16_t pos)
{
  if(pos + 3 >= curr_buffer_size_)
  {
    return 0;
  }

  float data = *((float*)(&data_buffer_[pos]));
  return data;
}

double DataReceiver::getDouble(uint16_t pos)
{
  if(pos + 7 >= curr_buffer_size_)
  {
    return 0;
  }

  double data = *((double*)(&data_buffer_[pos]));
  return data;
}

uint8_t DataReceiver::getByte(uint16_t pos)
{
  if(pos >= curr_buffer_size_)
  {
    return 0;
  }

  uint8_t data = (uint8_t)data_buffer_[pos];
  return data;
}

uint16_t DataReceiver::getShort(uint16_t pos)
{
  if(pos + 1 >= curr_buffer_size_)
  {
    return 0;
  }

  uint16_t data = *((uint16_t*)(&data_buffer_[pos]));
  return data;
}

uint32_t DataReceiver::getInt(uint16_t pos)
{
  if(pos + 3 >= curr_buffer_size_)
  {
    return 0;
  }

  uint32_t data = *((uint32_t*)(&data_buffer_[pos]));
  return data;
}

//-----------------------------------------------------------------------------------------------------------------
void DataReceiver::resetDataBuffer()
{
  for(uint16_t pos = 0; pos < curr_buffer_size_; pos++)
  {
    data_buffer_[pos] = 0;
  }
}

//-----------------------------------------------------------------------------------------------------------------
void DataReceiver::receiveData()
{
  uint8_t end_flag_counter = 0;
  uint16_t data_size = 0;

  while(true)
  {
    if(read_state_ == ReadState::READ_SIZE)
    {
      uint8_t size_bytes[2];
      size_bytes[0] = Serial.read();
      size_bytes[1] = Serial.read();
      uint16_t size_buffer = *((uint16_t*)(&size_bytes)) - 6;
      if(size_buffer > max_buffer_size_)
      {
        read_state_ = ReadState::SEARCH_DATA;
      }
      else
      {
        curr_buffer_size_ = size_buffer;
        read_state_ = ReadState::READ_DATA;
      }
    }

    else if(read_state_ == ReadState::READ_DATA)
    {
      for(uint16_t byte_pos = 0; byte_pos < curr_buffer_size_; byte_pos++)
      {
        uint8_t byte = Serial.read();
        data_buffer_[byte_pos] = byte;
      }
      read_state_ = ReadState::SEARCH_DATA;
    }

    else
    {
      uint8_t byte = Serial.read();
      if(byte == 0xFF)
      {
        end_flag_counter++;
      }
      else
      {
        end_flag_counter = 0;
      }

      if(end_flag_counter >= 4)
      {
        read_state_ = ReadState::READ_SIZE;
        break;
      }
    }
  }
}

//-----------------------------------------------------------------------------------------------------------------
void DataReceiver::stepOne()
{
  receiveData();
}

//-----------------------------------------------------------------------------------------------------------------
void DataReceiver::stepTwo()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void DataReceiver::stepThree()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void DataReceiver::stepFour()
{
  // Not used.
}
