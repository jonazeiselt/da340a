/*
   UltrasonicSlave.ino
   Note: Only digital pins 2 and 3 work for interrupts.

   Authors: Danial Mahmoud and Jonas Eiselt
   Date: 2018-04-27
*/

const byte ledPin = 13;
const byte tonePin = 9;
const byte interruptPin = 2;

const double frequency = 45000;
const double cycles = 22;

double durationUs = 0;
volatile byte flag = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(tonePin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), transmitUltrasound, RISING);

  // Approximate value which gives 22 cycles
  durationUs = (cycles / frequency) * 1000 * 1000;
  durationUs = durationUs - 316;

  Serial.print(durationUs);
  Serial.println(" microseconds");
}

void loop()
{
  if (flag == 1)
  {
    tone(tonePin, frequency);
    delayMicroseconds(durationUs);
    noTone(tonePin);

    flag = 0;
  }
}

void transmitUltrasound()
{
  flag = 1;
}

