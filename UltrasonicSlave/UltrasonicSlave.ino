/*
 * UltrasonicSlave.ino
 * Note: Only digital pins 2 and 3 work for interrupts.
 * 
 * Authors: Danial Mahmoud and Jonas Eiselt
 * Date: 2018-04-27
 */

const byte ledPin = 13;
const byte interruptPin = 2; 

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), transmitUltrasound, RISING);
}

void loop() 
{
  // Do nothing
}

void transmitUltrasound()
{
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
}

