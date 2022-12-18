#include <Servo.h>
Servo servomotor;

// Pines para el Control del movimiento
int Motor1A = 13; 
int Motor1B = 12;  
int Motor2C = 8; 
int Motor2D = 10; 

// Lecturas del servomotor
int servoPos = 0;
int servoleerizq = 0;
int servoleerder = 0;

//Pines para el control de velocidad
int velmotor1 = 5; 
int velmotor2 = 6;

//Pines para el sensor ultrasonido y variables para calcular distancia
int ultrasonidopin = 2; 
int trigPin = 3; 
long duracion; 
int distancia; 
int delayVal;

void setup() {
  delay(1000);
  //le asignamos el pin 9 al servo
  servomotor.attach(9);

  pinMode(trigPin, OUTPUT); 
  pinMode(ultrasonidopin, INPUT); 

  //Pines de los motores
  pinMode(Motor1A,OUTPUT);
  pinMode(Motor1B,OUTPUT);
  pinMode(Motor2C,OUTPUT);
  pinMode(Motor2D,OUTPUT);
  pinMode(velmotor1, OUTPUT);
  pinMode(velmotor2, OUTPUT);

  //Velocidades de los motores
  analogWrite(velmotor1, 75); 
  analogWrite(velmotor2, 80);  

  servomotor.write(90); 
  Serial.begin(9600);
}

void loop() {
  delay(50); 
  
  //Calcula la distancia
  distancia = CalcularDistancia();

  //Si la distancia es menor que 10 cm
  if(distancia < 15){
    //Se detiene primero para calcular la direccion.
    detener();
    
    //Busca a la derecha con angulo de 10 y toma la distancia
    servomotor.write(10); 
    delay(600); 
    servoleerder = CalcularDistancia();

    //Busca a la izquierda con angulo de 170 y toma la distancia
    servomotor.write(170);  
    delay(600); 
    servoleerizq = CalcularDistancia();

    //regresa al frente 
    servomotor.write(90);  
    delay(600); 

    //Va para la direccion con mayor distancia a un objeto.
    if(servoleerizq > servoleerder){
      girarIzq();
    }

    if(servoleerder >= servoleerizq){
      girarDer(); 
    }
  }

  //Si no hay nada el carro continua 
  if(distancia > 15){
    Avanzar();
  }
  
}

void detener(){
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor2D, LOW);                       
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor2D,LOW); 
}

void girarDer(){
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor2D,LOW);
  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor2D,LOW);
  delay(250);
}

void girarIzq(){
  digitalWrite(Motor1A,LOW);
  digitalWrite(Motor2D, LOW);
  digitalWrite(Motor1A,LOW);
  digitalWrite(Motor2D, HIGH);
  delay(250);
}

void Avanzar(){
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor2D, LOW);                       
  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor2D,HIGH); 
}

int CalcularDistancia(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Calculamos la conversion
  duracion = pulseIn(ultrasonidopin, HIGH);
  distancia = duracion * 0.034 / 2;

  return distancia;    
}

