/**********************************************************************
 * DataReceiver.hpp
 * 
 * Class responsible to receive a bytestream via UART serial and store
 * it in a byte buffer.
 * 
 * Author: Cyril Marx
 * Created: February 2023
 **********************************************************************/

#include "Module.hpp"

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
  /// Receives all data.
  //
  void receiveData();

  private:
  uint32_t baud_rate_;
  uint16_t max_buffer_size_;
  uint16_t curr_buffer_size_;
  uint8_t *data_buffer_;

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