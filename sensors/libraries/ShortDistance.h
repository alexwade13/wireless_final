#ifndef ShortDistance_H
#define ShortDistance_H

#include <Arduino.h>
#include <Packet.h>
#include <XBee.h>

class ShortDistance
{
public:
  ShortDistance(int pin);
  uint16_t readRaw();
  float readInches();
  float readCentimeters();
  void print(uint16_t sensorValue);

private:
  int m_pin;
  float readingToInches(uint16_t reading);
  float readingToCentimeters(uint16_t reading);
};

#endif // ShortDistance_H
