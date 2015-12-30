#ifndef UltraSonic_H
#define UltraSonic_H

#include "Arduino.h"
#include "Packet.h"
#include "XBee.h"

class UltraSonic
{
public:
  UltraSonic(int pwPin);
  long readRaw();
  long readInches();
  long readCentimeters();
  void print();

private:
  int pwPin;
 
};

#endif // UltraSonic_H

