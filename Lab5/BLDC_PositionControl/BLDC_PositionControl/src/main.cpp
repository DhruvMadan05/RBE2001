#include <Arduino.h>

#define pin1 5
#define pin2 9
#define pin3 10

int interval = 500; // micro seconds
int lastPosition = 0;

void setup()
{
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
}

void step(int position)
{
  switch (position)
  {
  case 0:
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    delay(interval);
    break;
  case 1:
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, LOW);
    delay(interval);
    break;
  case 2:
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, LOW);
    delay(interval);
    break;
  case 3:
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, HIGH);
    delay(interval);
    break;
  case 4:
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, HIGH);
    delay(interval);
    break;
  case 5:
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, HIGH);
    delay(interval);
    break;
  }
}

void spinCW(int goal)
{
  int startPosition = lastPosition;
  int currentPosition = startPosition;
  for (int i = 0; i < goal; i++)
  {
    currentPosition--;
    if (currentPosition < 0)
    {
      currentPosition = 5;
    }
    step(currentPosition);
  }
  lastPosition = currentPosition;
  printf("Last Position: %d\n", lastPosition);
}

void spinCCW(int goal)
{
  int startPosition = lastPosition;
  int currentPosition = startPosition;
  for (int i = 0; i < goal; i++)
  {
    currentPosition++;
    if (currentPosition > 5)
    {
      currentPosition = 0;
    }
    step(currentPosition);
  }
  lastPosition = currentPosition;
  printf("Last Position: %d\n", lastPosition);
}

// Main loop
void loop()
{
  // Lab Signoff
  spinCW(11);
  delay(15000);
  spinCCW(21);
  delay(13000);
  spinCW(6);
  delay(10000);
}