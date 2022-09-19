#include <IRremote.h>

IRsend irsend;
void setup()
{
    Serial.begin(9600); // Initialize serial interface
}
void loop()
{
  Serial.println("Switch");
  irsend.sendLG(11, 0x880094D, 1); // code for Sony TV power command
  delay(5000); // wait 5 seconds
}
