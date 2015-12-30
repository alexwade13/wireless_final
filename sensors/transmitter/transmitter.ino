#include <XBee.h>
#include <Wire.h>
#include <Packet.h>
#include <Transmitter.h>
#include <LongDistance.h>
#include <ShortDistance.h>
#include <InfraredThermometer.h>
#include <UltraSonic.h>

//-----------------------------
// Pin Configuration
//-----------------------------
int longDistancePin = A0;
int shortDistancePin = A1;
int ultraSonicPin = 7;
// Infrared is on I2C (pins 2 and 3)

//-----------------------------
// Addressing Details
//-----------------------------
uint16_t destAddress = 100;
uint16_t myAddress = 200;
uint16_t myPan = 1000;
uint8_t myCh = 15;

//-----------------------------
// Sensor Objects
//-----------------------------
Transmitter* transmitter;
LongDistance* longDistance;
ShortDistance* shortDistance;
InfraredThermometer* infraredTherm;
UltraSonic* ultraSonic;

void setup(){
  Serial.begin(9600);
  transmitter = new Transmitter(myAddress, myPan, myCh);
  longDistance = new LongDistance(longDistancePin);
  //shortDistance = new ShortDistance(shortDistancePin);
  infraredTherm = new InfraredThermometer();
  ultraSonic = new UltraSonic(ultraSonicPin);
}

void loop(){
  transmitter->txPacket("LDIR", longDistance->readInches(), destAddress);
  //transmitter->txPacket("SDIR", shortDistance->readInches(), destAddress);
  //transmitter->txPacket("IRTS", (float) infraredTherm->readFahrenheit(), destAddress);
  transmitter->txPacket("USDS", (int) ultraSonic->readInches(), destAddress);
  
  Serial.print("Long Inches: ");
  Serial.print(longDistance->readInches());
  //Serial.print("  Short Inches: ");
  //Serial.print(shortDistance->readInches());
  //Serial.print("  Fahrenheit: ");
  //Serial.print(infraredTherm->readFahrenheit());
  Serial.print("  Ultra Inches: ");
  Serial.print(ultraSonic->readInches());
  Serial.println();
  
  delay(10000);
}
