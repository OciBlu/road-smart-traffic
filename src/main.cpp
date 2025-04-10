#include <Arduino.h>
#include <DFPlayer_Mini_Mp3.h>
#include <SoftwareSerial.h>
#include <Arduino_FreeRTOS.h>

//Setup RX dan TX pin modul DFPlayer

//Setup Serial untuk Modul DFPlayer RX pin 5, TX pin 6
SoftwareSerial SoundSerial(5, 6);

//Setup Serial untuk Data Lampu Merah RX pin 7, TX pin 8
SoftwareSerial LightSerial(7, 8);

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

String Kondisi_redLed;
String baca_redLed;

float baca_distance;
float nilai_distance;

//Deklarasi tipedata
float duration, distance;

//Task Trafficlight
static void task1(void *pvParameters) {
  for (;;) {
    //Green ON
    digitalWrite(greenLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    //Yellow ON
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, HIGH);
    vTaskDelay(2500 / portTICK_PERIOD_MS);
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(redLed, LOW);
    vTaskDelay(2500 / portTICK_PERIOD_MS);

    //RedLed ON
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, HIGH);
    //vTaskDelay(5000 / portTICK_PERIOD_MS);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration*.0343)/2; // Satuan panjang CM
    
    //Serial.println("Distance: ");
    //Serial.println(distance);
    unsigned long startTime = millis();
    while (millis() - startTime < 5000) {
      if (distance < 20) {
        digitalWrite(TestLed, HIGH);
      }
      else {
        digitalWrite(TestLed, LOW);
      }
    //delay(100); // beri jeda biar gak terlalu sering
  }

    //eksekusi ketika melewati batas marka 
    
    
    
      
  }
}

//Task Ultrasonic Sensor (HC SR04)
static void task2(void *pvParameters) {
  for (;;) {
    digitalWrite(trigPin, LOW);
    vTaskDelay(2 / portTICK_PERIOD_MS);
    digitalWrite(trigPin, HIGH);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    digitalWrite(trigPin, LOW);


  }
}


//Task Sound Peringatan
static void task3(void *pvParameters) {
  for (;;) {
    //Kondisi_redLed = "redLed_ON";
    //nilai_distance = distance < 20;

    while (LightSerial.available()== 0) { }
    while (Serial.available()== 0) { }

    baca_redLed = LightSerial.readString();
    Serial.print(" baca serial");
    Serial.print( baca_redLed);

    baca_distance = Serial.parseFloat();
    Serial.println( baca_distance);
    vTaskDelay(100 / portTICK_PERIOD_MS);

    if (baca_redLed == "redLed_ON" && baca_distance < 20){
      digitalWrite(TestLed, HIGH);
    }
    else{
      digitalWrite(TestLed, LOW);
    }
    
  }
}



void setup() {
  Serial.begin (9600);
  SoundSerial.begin(9600);
  LightSerial.begin(9600);
  pinMode(TestLed, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  //pinMode(buzzer, OUTPUT);

  
  //Setup TaskCreate
  //Setup TaskCreate Trafficlight
  xTaskCreate(
    task1,                    // Function that should be called
    "Task1",                  // Name of the task (for debugging)
    configMINIMAL_STACK_SIZE, // Stack size (bytes)
    NULL,                     // Parameter to pass
    tskIDLE_PRIORITY + 2,     // Task priority
    NULL                      // Task handle
    );

  
  //Setup TaskCreate Ultrasonic Sensor (HC SR04)
  xTaskCreate(
    task2,                    // Function that should be called
    "Task2",                  // Name of the task (for debugging)
    configMINIMAL_STACK_SIZE, // Stack size (bytes)
    NULL,                     // Parameter to pass
    tskIDLE_PRIORITY + 2,     // Task priority
    NULL                      // Task handle
    );
  
  //Setup TaskCreate Sound Peringatan
  xTaskCreate(
    task3,                    // Function that should be called
    "Task3",                  // Name of the task (for debugging)
    configMINIMAL_STACK_SIZE, // Stack size (bytes)
    NULL,                     // Parameter to pass
    tskIDLE_PRIORITY + 2,     // Task priority
    NULL                      // Task handle
    );
  
  

    //Menjalankan Task
    vTaskStartScheduler();
}


void loop() {
 
}