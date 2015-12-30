#include "UltraSonic.h"
#include "Arduino.h"



UltraSonic::UltraSonic(int pin)
{
  pwPin = pin;
}

long
UltraSonic::readRaw()
{
  pinMode(pwPin, INPUT);
  long pulse = pulseIn(pwPin, HIGH);
  return pulse;
}

long
UltraSonic::readInches()
{
  pinMode(pwPin, INPUT);
  long pulse = pulseIn(pwPin, HIGH);
  long inches = pulse/147;
  return inches;
}

long
UltraSonic::readCentimeters()
{
  pinMode(pwPin, INPUT);
  long pulse = pulseIn(pwPin, HIGH);
  // conversion to inches then cm
  long cm = (pulse/147) * 2.54;
  return cm;
}


void
UltraSonic::print()
{

  long pulse = pulseIn(pwPin, HIGH);
  //147uS per inch
  long inches = pulse/147;
  //change inches to centimetres
  long cm = inches * 2.54;
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(500);
}

