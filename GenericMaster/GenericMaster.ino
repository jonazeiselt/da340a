/*
   GenericMaster.ino

   Authors: Danial Mahmoud and Jonas Eiselt
   Date: 2018-04-27
*/

const byte ledPin = 13;
const byte transmitPin = 8;

double timeIntervalMs = 1000;
double delayDurationMs = 0;

void setup()
{
  delayDurationMs = timeIntervalMs / 2;

  pinMode(ledPin, OUTPUT);
  pinMode(transmitPin, OUTPUT);
}

/*
   Sends signal at specific intervals depending on the variable
   timeIntervalMs
*/
void loop()
{
  digitalWrite(ledPin, HIGH);
  digitalWrite(transmitPin, HIGH);
  delay(delayDurationMs);

  digitalWrite(ledPin, LOW);
  digitalWrite(transmitPin, LOW);
  delay(delayDurationMs);
}
