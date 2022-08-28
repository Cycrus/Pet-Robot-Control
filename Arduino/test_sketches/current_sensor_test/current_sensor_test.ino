/* 
 CREATED BY AATIK"s LAB
 FOR TESTING PURPOSE

SENSOR CONNECTIONS

GND_PIN -> GND OF ARDUINO
VCC     -> 5v PIN OF ARDUINO
OUT     -> A0 PIN OF ARDUNO
 
 This code is for the 5A sensor, if 20A or 30A sensor.
 You need to MODIFY/REPLACE (.0264 * analogRead(A0) -13.51) this formula to 
 
(.19 * analogRead(A0) -25) for 20A sensor
(.044 * analogRead(A0) -3.78) for 30A sensor
*/

// Extra Source: https://funduino.de/nr-41-stromstaerkesensor-arduino

#define NULLVALUE 531.5
#define VpA 125           // Value has been empirically derived
#define VOLTFACTOR 5000

void setup() {
  Serial.begin(9600);
}

void loop() {

  double value = 0.0;
  double average = 0.0;
  for(int i = 0; i < 1000; i++) 
  {
    value = analogRead(A0);
    //average = average + (.0264 * value - 13.51) / 1000;
    average += value;
    delay(1);
  }
  average = average / 1000;

  average -= NULLVALUE;
  if(average < 0.0)
  {
    average = 0.0;
  }

  float volt = (average / 1024.0) * VOLTFACTOR;
  float amps = (volt /  VpA);
  
  Serial.print("Sensor Value = ");
  Serial.print(average);
  Serial.print(" ..... Amps = ");
  Serial.print(amps);
  Serial.println(" A");
}
