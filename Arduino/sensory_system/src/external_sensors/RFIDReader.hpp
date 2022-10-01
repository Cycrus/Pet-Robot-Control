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
#include <MFRC522.h>
#include "../base_libraries/Module.hpp"

#define MSG_LEN 1

class RFIDReader : public Module
{
  public:
  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor. Defines the pin and type of the DHT module.
  //
  RFIDReader(uint8_t rst_pin, uint8_t ss_pin);

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
  /// Returns the last message by the 
  //
  uint8_t getMessageCode();

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the last valid humidity value measured by the module in percent.
  //
  static bool checkByteArray(byte *arr, String str);

  private:
  MFRC522 module_object_;
  uint8_t message_code_;
  MFRC522::MIFARE_Key rfid_key_;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 1. Used for Authentification.
  //
  void stepOne() override;

  //-----------------------------------------------------------------------------------------------------------------
  ///
  /// Step 2. Used for Collecting the message.
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
