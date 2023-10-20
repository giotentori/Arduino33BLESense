
#include <Arduino_LSM9DS1.h>
const float thresholdAccelerazione = 2.5; // valore limite lettura
const float thresholdVibrazioni = 3;//valore limite vibrazioni
const int numeroCampioni = 100; // numero di campioni voluto
int letturaCampioni = numeroCampioni;

void setup() {
  Serial.begin(9600); 
  while (!Serial);

  if (!IMU.begin()) { 
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  Serial.println("XA,YA,ZA,XG,YG,ZG");
}

void loop() {
  float xa, ya, za, xg, yg, zg;
  while(letturaCampioni==numeroCampioni){
    if (IMU.accelerationAvailable()){
      IMU.readAcceleration(xa, ya, za);
      // somma della lettura per confrontarla con il threshold
      float somma = abs(xa) + abs(ya) + abs(za);
      if(somma >= thresholdAccelerazione){
        letturaCampioni = 0;
        break;
      }
    }
  }
  while(numeroCampioni>letturaCampioni){
    if (IMU.accelerationAvailable() & IMU.gyroscopeAvailable()){
      //Lettura dei valori dell'accelerometro e del giroscopio
      IMU.readAcceleration(xa, ya, za);
      IMU.readGyroscope(xg, yg, zg);
      letturaCampioni++;

      float sommaV = abs(xa) + abs(ya) + abs(za);
      if(sommaV>=thresholdVibrazioni){ // Vibrazioni sono consistenti
        // stammpiamo i dati a monitor seriale in
        // in formato CSV

        //Le vibrazioni consistenti vengono stampate con margine
        //per distinguerle da quelle leggere
        Serial.print('\t');
        Serial.print(xa,3);
        Serial.print(',');
        Serial.print(ya,3);
        Serial.print(',');
        Serial.print(za,3);
        Serial.print(',');
      
        Serial.print(xg,3);
        Serial.print(',');
        Serial.print(yg,3);
        Serial.print(',');
        Serial.println(zg,3);
      }else{
        Serial.print(xa,3);
        Serial.print(',');
        Serial.print(ya,3);
        Serial.print(',');
        Serial.print(za,3);
        Serial.print(',');
      
        Serial.print(xg,3);
        Serial.print(',');
        Serial.print(yg,3);
        Serial.print(',');
        Serial.println(zg,3);
      }
      Serial.println();
      if(letturaCampioni==numeroCampioni){
        // conclusa la raccolta dati
        Serial.println();
        //separiamo la fine lettura
        Serial.print("+++++++++++++++++++++++++++++");
        Serial.println();
      }
    }
  }    
}
