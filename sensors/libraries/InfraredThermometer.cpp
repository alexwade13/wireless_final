#include "InfraredThermometer.h"

InfraredThermometer::InfraredThermometer()// why no pin?
{
  mlx = Adafruit_MLX90614();
  mlx.begin();
}

double
InfraredThermometer::readCelcius()
{
  return mlx.readAmbientTempC();
}

double
InfraredThermometer::readFahrenheit()
{
  return mlx.readAmbientTempF();
}

void
InfraredThermometer::print()
{
  long C = mlx.readAmbientTempF();
  long F = mlx.readAmbientTempC();
 
  Serial.print(C);
  Serial.print(" Celcius, or ");
  Serial.print(F);
  Serial.print("Fahrenheit");
  Serial.println();
}

