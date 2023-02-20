/**********************************************************************
 * ModuleSyncer.hpp
 * 
 * Implementation of the data sender class.
 * 
 * Author: Cyril Marx
 * Created: February 2023
 **********************************************************************/

#include "DataSender.hpp"

DataSender::DataSender(uint32_t baud_rate, uint16_t buffer_size) :
baud_rate_(baud_rate),
max_buffer_size_(buffer_size),
curr_buffer_size_(0),
data_buffer_(nullptr)
{
  time_list_[0] = 0;
  setMaxSteps(1);
}

DataSender::~DataSender()
{
  if(data_buffer_ != nullptr)
  {
    free(data_buffer_);
    data_buffer_ = nullptr;
  }
}

//-----------------------------------------------------------------------------------------------------------------
void DataSender::initModule()
{
  Serial.begin(baud_rate_);
  data_buffer_ = malloc(max_buffer_size_);
}

//-----------------------------------------------------------------------------------------------------------------
void DataSender::addBytes(uint8_t *bytes, uint16_t size)
{
  if(curr_buffer_size_ + size >= max_buffer_size_)
    {
      return;
    }

  for(uint8_t byte_pos = 0; byte_pos < size; byte_pos++)
  {
    data_buffer_[curr_buffer_size_] = bytes[byte_pos];
    curr_buffer_size_++;
  }
}

//-----------------------------------------------------------------------------------------------------------------
void DataSender::addData(uint8_t data)
{
  data_buffer_[curr_buffer_size_] = data;
  curr_buffer_size_++;
}

void DataSender::addData(uint16_t data)
{
  addBytes((uint8_t*)(&data), 2);
}

void DataSender::addData(uint32_t data)
{
  addBytes((uint8_t*)(&data), 4);
}

void DataSender::addData(float data)
{
  addBytes((uint8_t*)(&data), 4);
}
