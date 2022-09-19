/* 
 A small script for interpreting 20 volt current sensor.

 Author Cyril Marx
 
 Date August 2022
*/

// Extra Source: https://funduino.de/nr-41-stromstaerkesensor-arduino

#define SENSOR_GPIO A2
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
    value = analogRead(SENSOR_GPIO);
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
