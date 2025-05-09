#include <Arduino.h>
#include <DFPlayer_Mini_Mp3.h>
#include <SoftwareSerial.h>
//#include <Arduino_FreeRTOS.h>

//Setup RX dan TX pin modul DFPlayer

//Setup Serial untuk Modul DFPlayer RX pin 5, TX pin 6
SoftwareSerial SoundSerial(5, 6);

//Setup deklarasi pin
//1.Setup Ultasonic pin trigPin & echoPin
#define trigPin 10
#define echoPin 9
//2.Setup Trafficlight pin
#define redLed 2
#define yellowLed 3
#define greenLed 4
//3.Setup Sound pin
#define buzzer 5
#define SoundRelay 7

long duration;
int distance;

void checkViolation(); //tidak dipakai jika pakai ArduinoIDE

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(SoundRelay,OUTPUT);

}

void loop() {
  // LAMPU HIJAU
  digitalWrite(redLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, HIGH);
  delay(5000);

  // LAMPU KUNING
  digitalWrite(redLed, LOW);
  digitalWrite(yellowLed, HIGH);
  digitalWrite(greenLed, LOW);
  delay(2000);

  // LAMPU MERAH
  digitalWrite(redLed, HIGH);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);

  unsigned long startTime = millis();
  while (millis() - startTime < 30000) { // selama 10 detik lampu merah
    checkViolation(); // terus cek pelanggara
  }

  //Mematikan Suara Peringatan setelah lampu merah mati
  digitalWrite(SoundRelay, LOW);
}

void checkViolation() {
  // Trigger sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
 
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  //eksekusi ketika melewati batas marka 
   if (distance < 20 && distance != 0 ) {
    digitalWrite(SoundRelay, HIGH);
    delay(8000);
  }
  
  else {
    digitalWrite(SoundRelay, LOW);
  }
}
