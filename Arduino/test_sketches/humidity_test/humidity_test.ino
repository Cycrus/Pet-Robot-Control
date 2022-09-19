#include <DHT.h>

#define DHT_GPIO 30

DHT dht(DHT_GPIO, DHT11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("% ... ");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  delay(1000);
}
