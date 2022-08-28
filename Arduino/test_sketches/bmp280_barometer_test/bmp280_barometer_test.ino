// Connect SDA to A4 and SCL to A5
// 3.3 Volt

#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

void setup() {
  // put your setup code here, to run once:
  bmp.begin(BMP280_ADDRESS_ALT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = bmp.readTemperature();
  float pressure = bmp.readPressure();
  float altitude = bmp.readAltitude();

  Serial.print("Temperature = ");
  Serial.println(temp);
  Serial.print("Pressure = ");
  Serial.println(pressure);
  Serial.print("Altitude = ");
  Serial.println(altitude);
  Serial.println("");
  delay(1000);
}
