/**********************************************************************
 * RFIDReader.hpp
 * 
 * A class representing an RFID reader module.
 * Extends the Module base class.
 * 
 * Author: Cyril Marx
 * Created: October 2022
 **********************************************************************/

#ifndef RFIDREADER_HPP
#define RFIDREADER_HPP

#include <SPI.h>
#include "../base_libraries/MFRC522.h"
#include "../utilities/Module.hpp"

#define MSG_LEN 18
#define RFID_RESET_TIME 500

class RFIDReader : public Module
{
  public:
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor. Defines the pin and type of the DHT module.
  //
  RFIDReader(uint8_t ss_pin, uint8_t rst_pin);

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default copy constructor.
  //
  RFIDReader(const RFIDReader&) = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Default destructor.
  //
  ~RFIDReader() = default;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Initializes the module.
  //
  void initModule();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the last message read by the reader.
  //
  uint8_t getMessageCode();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Resets the message code back to 0.
  //
  void resetMessageCode();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the last valid humidity value measured by the module in percent.
  //
  static bool checkByteArray(byte *arr, String str);

  private:
  MFRC522 module_object_;
  uint8_t message_code_;
  uint32_t message_time_;
  MFRC522::MIFARE_Key rfid_key_;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 1. Collects a new message if an RFID chip is detected in triggeringRequirements().
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

#endif //RFIDREADER_HPP
