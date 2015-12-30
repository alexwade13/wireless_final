#ifndef InfraredThermometer_H
#define InfraredThermometer_H

#include "Arduino.h"
#include "Packet.h"
#include "XBee.h"
#include <Wire.h>
#include <Adafruit_MLX90614.h>

class InfraredThermometer
{
public:
  InfraredThermometer();
  double readCelcius();
  double readFahrenheit();
  void print();

private:
  Adafruit_MLX90614 mlx;
};

#endif // InfraredThermometer_H
