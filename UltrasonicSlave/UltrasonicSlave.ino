/*
   UltrasonicSlave.ino
   Note: Only digital pins 2 and 3 work for interrupts.

   Authors: Danial Mahmoud and Jonas Eiselt
   Date: 2018-04-27
*/

const byte ledPin = 13;
const byte tonePin = 9;
const byte interruptPin = 2;

const double cycles = 15;
const double frequency = 55000;
double offsetTime = 0;

double durationUs = 0;
volatile byte flag = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(tonePin, OUTPUT);

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), transmitUltrasound, RISING);

  if (frequency == 40000)
    offsetTime = 220;
  else if (frequency == 45000)
    offsetTime = 220;
  else if (frequency == 50000)
    offsetTime = 220;
  else if (frequency == 55000)
    offsetTime = 215;
  else if (frequency == 60000)
    offsetTime = 220;
    
  // Approximate value which gives 15 cycles
  durationUs = (cycles / frequency) * 1000 * 1000;
  durationUs = durationUs - offsetTime;
  delay(10);
  
  Serial.print(durationUs);
  Serial.println(" microseconds");
}

void loop()
{
  /*if (flag == 1)
    {
    tone(tonePin, frequency);
    delayMicroseconds(durationUs);
    noTone(tonePin);

    flag = 0;
    }*/

  tone(tonePin, frequency);
  delayMicroseconds(durationUs);
  noTone(tonePin);

  delay(100);
}

void transmitUltrasound()
{
  flag = 1;
}

