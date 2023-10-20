#include <Arduino_HTS221.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }
}

void loop() {
  // read all the sensor values
  float temperature = HTS.readTemperature();
  float humidity    = HTS.readHumidity();

  // print each of the sensor values
  Serial.print("Temperatura = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidità    = ");
  Serial.print(humidity);
  Serial.println(" %");

  // print an empty line
  Serial.println();

  // wait 1 second to print again
  delay(1000);
}
