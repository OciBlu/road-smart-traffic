#include <Arduino.h>
#include <DFPlayer_Mini_Mp3.h>
#include <SoftwareSerial.h>
#include <Arduino_FreeRTOS.h>

//Setup SoftwareSerial  RX pin 5, TX pin 6
SoftwareSerial serial(5, 6);

#define trigPin 9
#define echoPin 10
#define redLed 2
#define yellowLed 3
#define greenLed 4
#define buzzer 5

//Task Trafficlight
static void task1(void *pvParameters) {
  for (;;) {
    //Green ON
    digitalWrite(greenLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    //Yellow ON
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
      vTaskDelay(5000 / portTICK_PERIOD_MS);
      
  }
}

void setup() {
  //pinMode(trigPin, OUTPUT);
  //pinMode(echoPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  //pinMode(buzzer, OUTPUT);

  /*//Setup MP3
  serial.begin (9600);  
  mp3_set_serial (serial);
  delay(5); 
  mp3_set_volume (20);
  delay(1000);*/

  //Setup TaskCreate
  xTaskCreate(
    task1,                    // Function that should be called
    "Task1",                  // Name of the task (for debugging)
    configMINIMAL_STACK_SIZE, // Stack size (bytes)
    NULL,                     // Parameter to pass
    tskIDLE_PRIORITY + 2,     // Task priority
    NULL                      // Task handle
    );

    vTaskStartScheduler();

}

void loop() {
 
}