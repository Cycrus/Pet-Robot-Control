#include <TinyGPSPlus.h>

#define SENSOR Serial1

TinyGPSPlus gps;

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}

void setup() {
  // put your setup code here, to run once:
  SENSOR.begin(9600);
  Serial.begin(9600);
}

int i = 0;
void loop() {
  // put your main code here, to run repeatedly:
  while(SENSOR.available())
  {
    char input = SENSOR.read();
    
    if(gps.encode(input))
    {
      displayInfo();
    }
    
    /*Serial.print(input);
    if(input == '$')
    {
      i++;
    }*/
  }

  /*if(i >= 10)
  {
    while(true);
  }*/
}
