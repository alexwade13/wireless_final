#include "LongDistance.h"

LongDistance::LongDistance(int pin)
{
  m_pin = pin;
}

uint16_t
LongDistance::readRaw()
{
  return analogRead(m_pin);
}

float
LongDistance::readInches()
{
  return readingToInches(readRaw());
}

float
LongDistance::readCentimeters()
{
  return readingToCentimeters(readRaw());
}

void
LongDistance::print(uint16_t sensorValue)
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
LongDistance::readingToInches(uint16_t reading)
{
  if(reading < 16)
    reading = 16;

  return readingToCentimeters(reading) / 2.54;
}

float
LongDistance::readingToCentimeters(uint16_t reading)
{
  if (reading < 25)  reading = 25;
  return 9646.0 / (reading - 16.92);
}
