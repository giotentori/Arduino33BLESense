#include <Arduino_LSM9DS1.h>

float x, y, z;
float vel=0;
int degreesX = 0;
int degreesY = 0;
//motore b : motore adibito all'inclinazione angolare da 0 a +90°
int enB = 10;
int in1 = 6;
int in2 = 5;
//motore a: motore adibito all'inclinazione da 0 a -90°
int in3 = 4;
int in4 = 3;
int enA = 9;

void setup() {
  // inizializzazione seriale
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");
  // inizializzazione IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // stampa dei parametri relativi all'accelerometro sul monitor seriale
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");

  //impostazione dei motori come output
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // lettura dei dati forniti dall'accelerometro ,se disponibili
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

  }
  // accesione dei motori
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  // inclinazione sull'asse positivo delle y
  if (y > 0.1) {
    y = 100 * y;
    degreesY = map(y, 0, 97, 0, 90);// mappatura dei valori forniti da arduino sui gradi di inclinazione
    Serial.print("inclinazione sinistra ");
    Serial.print(degreesY);
    Serial.println("  degrees");
    vel = map(y, 0, 90, 0, 255); // mappatura dei valori di velocita' del motore in base ai gradi di inclinazione
    digitalWrite(in1, LOW); // motore di destra spento
    digitalWrite(in2, LOW);

  // imposta la velocità in base al valore dei gradi di inclinazione range: (0~255)
  analogWrite(enB, vel);
    
  }
  // inclinazione sull'asse negativo delle y
  if (y < -0.1) {
    y = 100 * y;
    degreesY = map(y, 0, -97, 0, -90);
    Serial.print("inclinazione destra ");
    Serial.print(degreesY);
    Serial.println("  degrees");
    vel = map(y, 0, -90, 0, 255);
    digitalWrite(in3, LOW); // motore di sinistra spento 
    digitalWrite(in4, LOW);
    analogWrite(enA, vel);


  }
  // arduino statico nessuna o quasi inclinazione
  if(y<=0.1 && y>=-0.1){
    x = 100 * y;
    degreesX = map(y, 0, 97, 0, 90);
    Serial.print("nessuna inclinazione ");
    Serial.print(degreesY);
    Serial.println("  degrees");
    
  // impostazione della velocita' costante 
  analogWrite(enA, 100);

  // impostazione della velocita' costante
  analogWrite(enB,100);
  }
  
  delay(50); // pausa necessaria per la visualizzazione corretta sul monitor seriale
}
