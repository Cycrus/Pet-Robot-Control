/**********************************************************************
 * DataReceiver.hpp
 * 
 * Class responsible to receive a bytestream via UART serial and store
 * it in a byte buffer.
 * 
 * Author: Cyril Marx
 * Created: February 2023
 **********************************************************************/

#ifndef DATARECEIVER_HPP
#define DATARECEIVER_HPP

#include "Module.hpp"

enum ReadState {SEARCH_DATA, READ_SIZE, READ_DATA};

class DataReceiver : public Module
{
  public:
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor. Defines the baud rate and buffer size of the receiver.
  ///
  /// @param  baud_rate    The baud rate of the serial connection.
  /// @param  buffer_size  The maximum size of the buffer. Constantly reserves that amount of bytes in memory and
  //
  DataReceiver(uint32_t baud_rate, uint16_t buffer_size);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default copy constructor.
  //
  DataReceiver(const DataReceiver&) = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor. Frees memory for data buffer. Probably never used on microcontroller.
  //
  ~DataReceiver();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Initializes the module by reserving memory and initializing the serial connection.
  //
  void initModule() override;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Returns a pointer to the first element of the buffer.
  //
  uint8_t *getBuffer();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the current size of the buffer.
  //
  uint16_t getSize();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Getters to receive the data in various data types at certain positions.
  ///
  /// @param  pos   The position of the desired data in the data_buffer_.
  //
  int8_t getSignedByte(uint16_t pos);
  int16_t getSignedShort(uint16_t pos);
  int32_t getSignedInt(uint16_t pos);
  uint8_t getByte(uint16_t pos);
  uint16_t getShort(uint16_t pos);
  uint32_t getInt(uint16_t pos);
  float getFloat(uint16_t pos);
  double getDouble(uint16_t pos);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Fills the whole data buffer with zeroes.
  //
  void resetDataBuffer();

  private:
  uint32_t baud_rate_;
  uint16_t max_buffer_size_;
  uint16_t curr_buffer_size_;
  uint8_t *data_buffer_;
  ReadState read_state_;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Receives all data.
  //
  void receiveData();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 1. Receives all data and stores it into a buffer.
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

#endif // DATARECEIVER_HPP