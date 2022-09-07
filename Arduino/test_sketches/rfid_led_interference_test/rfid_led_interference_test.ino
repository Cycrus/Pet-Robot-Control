/*
 * Initial Author: ryand1011 (https://github.com/ryand1011)
 *
 * Reads data written by a program such as "rfid_write_personal_data.ino"
 *
 * See: https://github.com/miguelbalboa/rfid/tree/master/examples/rfid_write_personal_data
 *
 * Uses MIFARE RFID card using RFID-RC522 reader
 * Uses MFRC522 - Library
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
*/

#include <SPI.h>
#include <MFRC522.h>

#include <Adafruit_NeoPixel.h>

#define LEDPIN 3
#define NUMPIXELS 12

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

int loop_num = 0;
Adafruit_NeoPixel ring(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

bool checkByteArray(byte *arr, String str)
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

//*****************************************************************************************//
void setup() {
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println(F("Read payload on a MIFARE PICC:"));    //shows in serial that it is ready to read
  ring.begin();
}

//*****************************************************************************************//
void loop() {

  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  bool can_read = true;

  //-------------------------------------------

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    can_read = false;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    can_read = false;
  }

  //Serial.println(F("**Card Detected**"));

  //-------------------------------------------

  //mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

  //-------------------------------------------

  //Serial.print(F("Payload: "));

  if (can_read)
  {
    byte payload_buffer[18];
  
    len = 18;
  
  
  
    //---------------------------------------- GET PAYLOAD
  
    block = 1;
  
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("Authentication failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      mfrc522.PCD_StopCrypto1();
      return;
    }
  
    status = mfrc522.MIFARE_Read(block, payload_buffer, &len);
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("Reading failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      mfrc522.PCD_StopCrypto1();
      return;
    }
  
    //PRINT PAYLOAD
    Serial.println("");
    for (uint8_t i = 0; i < 16; i++) {
      Serial.write(payload_buffer[i]);
    }
    Serial.println("");
  
  
    //----------------------------------------
  
    //Serial.println(F("\n**End Reading**\n"));
  
    if(checkByteArray(payload_buffer, "pos"))
    {
      Serial.println("Positive Feedback Received");
    }
    else if(checkByteArray(payload_buffer, "neg"))
    {
      Serial.println("Negative Feedback Received");
    }
    else
    {
      Serial.println("Did not understand feedback.");
    }

    //mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }

  ring.clear();

  uint32_t c = ring.Color(0, 0, 0);

  if(loop_num % 4 == 0)
  {
    c = ring.Color(10, 0, 10);
  }
  else if(loop_num % 3 == 0)
  {
    c = ring.Color(20, 0, 0);
  }
  else if(loop_num % 2 == 0)
  {
    c = ring.Color(0, 20, 0);
  }
  else
  {
    c = ring.Color(0, 0, 20);
  }

  for(int i = 0; i < NUMPIXELS; i++)
  {
    ring.setPixelColor(i, c);
    ring.show();
  }

  loop_num++;

  delay(100); //change value if you want to read cards faster
}
//*****************************************************************************************//
