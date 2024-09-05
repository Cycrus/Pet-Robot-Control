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
curr_buffer_size_(MIN_BUFFER_SIZE),
data_buffer_(nullptr)
{
  time_list_[0] = 33;
  setMaxSteps(1);
}

//-----------------------------------------------------------------------------------------------------------------
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

  for(uint16_t byte_pos = 0; byte_pos < size; byte_pos++)
  {
    data_buffer_[curr_buffer_size_] = bytes[byte_pos];
    curr_buffer_size_++;
  }
}

//-----------------------------------------------------------------------------------------------------------------
void DataSender::changeBytes(uint8_t *bytes, uint16_t size, uint16_t offset)
{
  if(offset + size >= max_buffer_size_)
  {
    return;
  }

  for(uint16_t byte_pos = 0; byte_pos < size; byte_pos++)
  {
    data_buffer_[offset + byte_pos] = bytes[byte_pos];
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

void DataSender::addData(int8_t data)
{
  data_buffer_[curr_buffer_size_] = data;
  curr_buffer_size_++;
}

void DataSender::addData(int16_t data)
{
  addBytes((uint8_t*)(&data), 2);
}

void DataSender::addData(int32_t data)
{
  addBytes((uint8_t*)(&data), 4);
}

void DataSender::addData(float data)
{
  addBytes((uint8_t*)(&data), 4);
}

void DataSender::addData(double data)
{
  addBytes((uint8_t*)(&data), 8);
}

//-----------------------------------------------------------------------------------------------------------------
void DataSender::formatData()
{
  uint32_t end_of_message = -2;
  addBytes((uint8_t*)(&end_of_message), 4);
  changeBytes((uint8_t*)(&curr_buffer_size_), 2, 0);
}

//-----------------------------------------------------------------------------------------------------------------
void DataSender::sendData()
{
  uint8_t start_signature[START_SIGNATURE_BYTE_NUM];
  for(int i = 0; i < START_SIGNATURE_BYTE_NUM; i++)
    start_signature[i] = PACKET_START_SIGNATURE;
  Serial.write(start_signature, START_SIGNATURE_BYTE_NUM);
  Serial.write((uint8_t*)&curr_buffer_size_, 2);
  Serial.write(data_buffer_, curr_buffer_size_);
  Serial.flush();
}

//-----------------------------------------------------------------------------------------------------------------
void DataSender::resetData()
{
  curr_buffer_size_ = MIN_BUFFER_SIZE;
}

//-----------------------------------------------------------------------------------------------------------------
void DataSender::stepOne()
{
  sendData();
}

//-----------------------------------------------------------------------------------------------------------------
void DataSender::stepTwo()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void DataSender::stepThree()
{
  // Not used.
}

//-----------------------------------------------------------------------------------------------------------------
void DataSender::stepFour()
{
  // Not used.
}
