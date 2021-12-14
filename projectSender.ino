
#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(12, 13); // RX | TX 
// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

#define echoPin 5 // attach pin D6 Arduino to pin Echo of HC-SR04
#define trigPin 6 //attach pin D7 Arduino to pin Trig of HC-SR04

void setup() 
{
  Serial.begin(9600);
  Bluetooth.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT 
}

void loop() 
{
  //TODO: if millis() > 21600000 then go to loop
  //we want to enter the loop only after the Arduino has been on for at least 6 hours, this time can be changed later
  delay(500);
  if(readDist() < 50){
    Bluetooth.write("1");
    Serial.println("sent order to start the kettle");
  }
  // Keep reading from HC-06 and send to Arduino Serial Monitor
  if (Bluetooth.available()){
    Serial.write(Bluetooth.read());
  }
  // Keep reading from Arduino Serial Monitor and send to HC-06
  if (Serial.available()){
    Serial.println("sent");
    Bluetooth.write(Serial.read());
  }
}

int readDist(){
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return(distance);
}
