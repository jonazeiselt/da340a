/* 
   SquarewaveGenerator.ino
   Generates square wave on Arduino Uno. 
   The function tone() continues until noTone() is called if tone() has 
   no duration parameter. 

   The frequency range of the Tone library is 31 Hz to around 65 kHz.
   See: https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/
   See: https://github.com/bhagman/Tone#ugly-details

   Date: 2018-04-25
 */

int pin = 11;
double frequency = 54000;
unsigned long duration = 0;
unsigned long actualDuration = 0;
double cycles = 12;

void setup() 
{
  pinMode(pin, OUTPUT);
  // tone(pin, frequency);
  
  /* Calculate duration (12 cycles) */
  duration = (cycles/frequency)*1000*1000;
  actualDuration = duration - 170;
  //tone(pin, frequency, duration);
}

void loop() 
{
  tone(pin, frequency);
  delayMicroseconds(actualDuration);
  noTone(pin);
  
  delay(100);
}
