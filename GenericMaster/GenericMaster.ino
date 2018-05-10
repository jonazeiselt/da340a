/*
   GenericMaster.ino

   Authors: Danial Mahmoud and Jonas Eiselt
   Date: 2018-04-27
*/

const byte slave1Pin = 8;
const byte slave2Pin = 9;
const byte slave3Pin = 10;
const byte slave4Pin = 11;

int slaveCounter = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(slave1Pin, OUTPUT);
  pinMode(slave2Pin, OUTPUT);
  pinMode(slave3Pin, OUTPUT);
  pinMode(slave4Pin, OUTPUT);

  Serial.println("Enter s to start");
  while (Serial.read() != 's');
  Serial.println("Running..");
}

/*
   Sends signal at specific intervals depending on the variable
   timeIntervalMs
*/
void loop()
{
  if (slaveCounter == 4)
  {
    slaveCounter = 0;
    // delay(40);
  }

  int slavePin = 8 + slaveCounter;
  digitalWrite(slavePin, HIGH);
  delay(20);
  digitalWrite(slavePin, LOW);

  slaveCounter++;
}
