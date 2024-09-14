/**********************************************************************
 * DataSender.hpp
 * 
 * A class responsible for serializing all generated data and sending it
 * via the Serial port 0.
 * 
 * Author: Cyril Marx
 * Created: February 2023
 **********************************************************************/

#ifndef DATASENDER_HPP
#define DATASENDER_HPP

#include "Module.hpp"

#define MIN_BUFFER_SIZE 0
#define PACKET_START_SIGNATURE 254
#define START_SIGNATURE_BYTE_NUM 4

class DataSender : public Module
{
  public:
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor. Defines the baud rate of the sender.
  ///
  /// @param  baud_rate    The baud rate of the serial connection.
  /// @param  buffer_size  The maximum size of the buffer. Constantly reserves that amount of bytes in memory.
  //
  DataSender(uint32_t baud_rate, uint16_t buffer_size);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default copy constructor.
  //
  DataSender(const DataSender&) = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor. Frees memory for data buffer. Probably never used on microcontroller.
  //
  ~DataSender();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Initializes the module.
  //
  void initModule() override;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Adds a number of bytes to the end of the data buffer.
  ///
  /// @param  bytes   The byte list to add to the buffer.
  /// @param  size    The size of the bytes list to add.
  //
  void addBytes(uint8_t *bytes, uint16_t size);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Changes a number of bytes somewhere in the data buffer.
  ///
  /// @param  bytes     The byte list to add to the buffer.
  /// @param  size      The size of the bytes list to add.
  /// @param  offset    The position where the byte array should be inserted.
  //
  void changeBytes(uint8_t *bytes, uint16_t size, uint16_t offset);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Appends data to the buffer.
  ///
  /// @param  data  The data to append to the buffer.
  //
  void addData(uint8_t data);
  void addData(uint16_t data);
  void addData(uint32_t data);
  void addData(int8_t data);
  void addData(int16_t data);
  void addData(int32_t data);
  void addData(float data);
  void addData(double data);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Resets all data in the data buffer and sets its size back to 2, which is the default length to send the size.
  //
  void resetData();

  private:
  uint8_t *data_buffer_;
  uint32_t baud_rate_;
  uint16_t max_buffer_size_;
  uint16_t curr_buffer_size_;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Sends all data via the UART serial connection.
  //
  void sendData();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 1. Formats the buffered data, sends it via the serial port and resets the buffer.
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

#endif // DATASENDER_HPP