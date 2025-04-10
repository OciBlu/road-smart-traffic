#include <Arduino.h>
#include <DFPlayer_Mini_Mp3.h>
#include <SoftwareSerial.h>
//#include <Arduino_FreeRTOS.h>

//Setup RX dan TX pin modul DFPlayer

//Setup Serial untuk Modul DFPlayer RX pin 5, TX pin 6
SoftwareSerial SoundSerial(5, 6);

//Setup deklarasi pin
//1.Setup Ultasonic pin trigPin & echoPin
#define trigPin 9
#define echoPin 10
//2.Setup Trafficlight pin
#define redLed 2
#define yellowLed 3
#define greenLed 4
//3.Setup Sound pin
#define buzzer 5
#define TestLed 7

long duration;
int distance;

void checkViolation();

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(TestLed,OUTPUT);

  //Setup MP3
  /*SoundSerial.begin (9600);  
  mp3_set_serial (SoundSerial);
  delay(5); 
  mp3_set_volume (15);
  delay(1000);
  */
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
  delay(5000);

  // LAMPU MERAH
  digitalWrite(redLed, HIGH);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);

  unsigned long startTime = millis();
  while (millis() - startTime < 5000) { // selama 10 detik lampu merah
    checkViolation(); // terus cek pelanggaran
  }

  //Mematikan Suara Peringatan setelah lampu merah mati
  digitalWrite(TestLed, LOW);
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
/*
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");
*/
  //eksekusi ketika melewati batas marka 
   if (distance < 20) {
    digitalWrite(TestLed, HIGH);
  }
  
  else {
    digitalWrite(TestLed, LOW);
  }
}
