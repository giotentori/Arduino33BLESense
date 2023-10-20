#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for Serial Monitor to open

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor.");
    while (true);
    }
}

// inizializiamo i pin relativi alle gesture e quello pwm per la distanza
int su = 2;
int giu = 3;
int destra = 4;
int sinistra = 5;
int prox = 10; // pin per la distanza
int distanza = 0; // variabile che indica la prossimità
int temp=0;
int dis=0;
unsigned long lastUpdate = 0;

void loop() {
      // controlliamo che la feature di prossimità sia disponibile
  if (APDS.proximityAvailable()){
    distanza = APDS.readProximity();
  } 
    dis = map(distanza, 0, 250, 0, 30); //mappiamo la prossimita sulla distanza in cm
    temp = map(dis, 0, 30, 0, 255); //mappiamo la lettura di distanza sull'intensita
    analogWrite(prox,temp);
    
    delay(50);
    
  // Check if a gesture reading is available
  if (APDS.gestureAvailable()) {
    int gesture = APDS.readGesture();
    switch (gesture) {
      case GESTURE_UP:
        Serial.println("Detected UP gesture");
        digitalWrite(su,HIGH);
        digitalWrite(giu,LOW);
        digitalWrite(destra,LOW);
        digitalWrite(sinistra,LOW);
        break;

      case GESTURE_DOWN:
        Serial.println("Detected DOWN gesture");
        digitalWrite(su,LOW);
        digitalWrite(giu,HIGH);
        digitalWrite(destra,LOW);
        digitalWrite(sinistra,LOW);
        break;

      case GESTURE_LEFT:
        Serial.println("Detected LEFT gesture");
        digitalWrite(su,LOW);
        digitalWrite(giu,LOW);
        digitalWrite(destra,LOW);
        digitalWrite(sinistra,HIGH);
        break;

      case GESTURE_RIGHT:
        Serial.println("Detected RIGHT gesture");
        digitalWrite(su,LOW);
        digitalWrite(giu,LOW);
        digitalWrite(destra,HIGH);
        digitalWrite(sinistra,LOW);
        break;

      default:
        // Ignore
        break;
    }
  }
  
  // Print updates every 100 ms
  if (millis() - lastUpdate > 100) {
    lastUpdate = millis();
    Serial.print("PR=");
    Serial.println(temp);
  }
}
