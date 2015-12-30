#include "ShortDistance.h"

ShortDistance::ShortDistance(int pin)
{
  m_pin = pin;
}

uint16_t
ShortDistance::readRaw()
{
  return analogRead(m_pin);
}

float
ShortDistance::readInches()
{
  return readingToInches(readRaw());
}

float
ShortDistance::readCentimeters()
{
  return readingToCentimeters(readRaw());
}

void
ShortDistance::print(uint16_t sensorValue)
{
  long inches = readingToInches(sensorValue);
  long cm = readingToCentimeters(sensorValue);
 
  Serial.print(inches);
  Serial.print("in, or ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
}

float
ShortDistance::readingToInches(uint16_t reading)
{
  if(reading < 16)
    reading = 16;

  return readingToCentimeters(reading) / 2.54;
}

float
ShortDistance::readingToCentimeters(uint16_t reading)
{
  return 2070.0 / (reading - 11);
}
