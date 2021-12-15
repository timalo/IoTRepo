#include <SoftwareSerial.h>

SoftwareSerial BTSlave(6, 7);
int in1 = 4;

char c = ' ';

void setup() {
  BTSlave.begin(9600);
  Serial.begin(9600);
  // put your setup code here, to run once:
  //pin for relay module control
  pinMode(in1, OUTPUT);
  digitalWrite(in1, LOW);

}

void loop() {
  delay(100);
  c = ' ';
  // put your main code here, to run repeatedly:
  // Keep reading from HC-06 and send to Arduino Serial Monitor, also save received char to var c
  if (BTSlave.available()){
    c = BTSlave.read();
    Serial.write(c);
  }
  // Keep reading from Arduino Serial Monitor and send to HC-06
  if (Serial.available()){
    BTSlave.write(Serial.read());
  }
  if(c == '1'){
    Serial.println("kettle on");
    digitalWrite(in1, HIGH);
  }
  else if (c == '2'){
    Serial.println("kettle off");
    digitalWrite(in2, LOW);
  }

  
  //This was used to check if BTmodule is paired with other BT module, might be useful later
  /*if(digitalRead(BTStatePin) == HIGH){
    //Serial.println("conn");
  } */
  //test for blinking kettle on/off
  /*digitalWrite(in1, LOW);
  delay(3000);
  digitalWrite(in1, HIGH);
  delay(3000); */
}
