#include <ArduinoBLE.h>

// service UUID 128bit generato con guidgenerator.com
BLEService cambioColoreService("8407f9e0-7d5e-4d97-bf99-a9b763b4b22c");

BLEByteCharacteristic RossoChar("8407f9e0-7d5e-4d97-bf99-a9b763b4b22c", 
    BLERead | BLEWrite); // sono le funzioni che il service è in grado di implementare

BLEByteCharacteristic BiancoChar("8407f9e0-7d5e-4d97-bf99-a9b763b4b22c",
    BLERead | BLEWrite);

BLEByteCharacteristic BluChar("8407f9e0-7d5e-4d97-bf99-a9b763b4b22c",
    BLERead | BLEWrite);

int ledRosso = 2;
int ledBianco = 3;
int ledBlu = 4;

void setup() { //inizializiamo la comunicazione seriale con il monitor
  Serial.begin(9600);
  while (!Serial);

  pinMode(LED_BUILTIN, OUTPUT); // inizializzazione del led integrato su arduino per indicare che il central è connesso

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }
  // settaggio del nome della piattaforma
  BLE.setLocalName("Giorgio");
  // settaggio dell'ID del service 
  BLE.setAdvertisedService(cambioColoreService); 
  
  //aggiunta la caraatteristica al servizio
  cambioColoreService.addCharacteristic(RossoChar);
  cambioColoreService.addCharacteristic(BiancoChar);
  cambioColoreService.addCharacteristic(BluChar);
  
 // inserimento del servizio nell'interfaccia dei servizi
  BLE.addService(cambioColoreService);

  //inizializzazione dei valori delle caratteristiche
  RossoChar.writeValue(0);
  BiancoChar.writeValue(0);
  BluChar.writeValue(0);
    
  // start advertising
  BLE.advertise();
  Serial.println("In attesa di connessione ... ");


}

void loop() {
  //attesa e connessione
  BLEDevice central = BLE.central();

  // Quando il centrale è connesso ad una periferica:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's BT address:
    Serial.println(central.address());
    // turn on the LED to indicate the connection:
    digitalWrite(LED_BUILTIN, HIGH); // accendi il led integrato se c'e' connessione

    // fai questo finche' è connesso:
    while (central.connected()) {
      if(RossoChar.written()){
        int valRosso = RossoChar.value();
        Serial.println(valRosso);
        if(valRosso>0){
          digitalWrite(ledRosso,HIGH);
          digitalWrite(ledBianco,LOW);
          digitalWrite(ledBlu,LOW);
        }
      }
      if(BiancoChar.written()){
        int valBianco = BiancoChar.value();
        Serial.println(valBianco);
          if(valBianco>0){
            digitalWrite(ledRosso,LOW);
            digitalWrite(ledBianco,HIGH);
            digitalWrite(ledBlu,LOW);
        }
      }
      if(BluChar.written()){
        int valBlu = BluChar.value();
        Serial.println(valBlu);
          if(valBlu>0){
            digitalWrite(ledRosso,LOW);
            digitalWrite(ledBianco,LOW);
            digitalWrite(ledBlu,HIGH);
        }
      }
    }
  }
    // appena si disconnette:
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
}
