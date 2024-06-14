#include <NewPing.h>

// Pinos dos motores
#define pinMotorD1 3 // Motor Direito Reverso
#define pinMotorD2 5 // Motor Direito Frente
#define pinMotorE1 6 // Motor Esquerdo Frente
#define pinMotorE2 9 // Motor Esquerdo Reverso

// Pinos dos sensores Infravermelho
#define pinSensorD 4
#define pinSensorE 7

// Pinos do sensor ultrassônico
const int trigPin = 2;
const int echoPin = 8;
const int maxDistance = 100; // Distância máxima em cm que o sensor irá medir

// Instanciando o objeto NewPing
NewPing sonar(trigPin, echoPin, maxDistance);

void setup() {
  // Configuração dos pinos dos motores
  pinMode(pinMotorD1, OUTPUT);
  pinMode(pinMotorD2, OUTPUT);
  pinMode(pinMotorE1, OUTPUT);
  pinMode(pinMotorE2, OUTPUT);

  // Configuração dos pinos dos sensores
  pinMode(pinSensorD, INPUT);
  pinMode(pinSensorE, INPUT);

  // Inicializando a comunicação serial (para depuração)
  Serial.begin(9600);
}

void loop() {
  // Lendo os sensores infravermelho
  int leituraEsquerda = digitalRead(pinSensorE);
  int leituraDireita = digitalRead(pinSensorD);

  // Medindo a distância com o sensor ultrassônico
  int distancia = sonar.ping_cm();

  motorEsquerdoFrente(100);
  motorDireitoReverso(100);

  if (distancia > 0 && distancia <= 30) {
      // Evitar a borda da arena
      motorEsquerdoReverso(250);
      motorDireitoReverso(250);
        if (leituraEsquerda == HIGH || leituraDireita == HIGH) {
          // Sensor esquerdo detecta borda, voltar para a direita
          motorEsquerdoFrente(150);
          motorDireitoFrente(100);
          delay(1000);
        } 
  }

  // Opcional: imprimir a distância para depuração
  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println(" cm");
}

// Funções para controlar os motores

void motorEsquerdoFrente(int velocidade) {
  analogWrite(pinMotorE1, velocidade);
  analogWrite(pinMotorE2, 0);
}

void motorEsquerdoReverso(int velocidade) {
  analogWrite(pinMotorE1, 0);
  analogWrite(pinMotorE2, velocidade);
}

void motorDireitoFrente(int velocidade) {
  analogWrite(pinMotorD1, 0);
  analogWrite(pinMotorD2, velocidade);
}

void motorDireitoReverso(int velocidade) {
  analogWrite(pinMotorD1, velocidade);
  analogWrite(pinMotorD2, 0);
}

void pararMotores() {
  analogWrite(pinMotorE1, 0);
  analogWrite(pinMotorE2, 0);
  analogWrite(pinMotorD1, 0);
  analogWrite(pinMotorD2, 0);
}