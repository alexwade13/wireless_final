/**
 * Packet: The C++ equivalence of the python Packet class defined in basestation.py
 * This class encasulates Tx16Request class. Note that seems like "16" means
 * the length of the address. Since we are only concerning about addresses 
 * like "100" and "200", a 16-bit address is enough.
 *
 * This class only represents the outgoing packets, so we only care about
 * creating the packet, and don't need to support parsing incoming packets.
 * 
 * Author: Li Li (ll024)
 */

#ifndef Packet_H
#define Packet_H

#include "Arduino.h"
#include "XBee.h"

class Packet
{
public:
  Packet(String header, uint32_t value, uint16_t address);

  /**
   * Sets the header of the packet. It only copies the first four bytes 
   * of the string to the packet heaer.
   */
  void setHeader(String header);

  /**
   * Sets the 32-bit value being sent in the packet
   */
  void setValue(uint32_t value);

  /**
   * Sets the 16-bit address
   */
  void setAddress(uint16_t address);
  
  //for debug use
  void printPayload();
  Tx16Request getTx16Request();

private:
  void setPayload();
  char m_header[4];
  uint32_t m_value;
  uint16_t m_address;
  char m_payload[8];

  Tx16Request m_tx16Request;
};


/* NOTE: These classes were written for the last project. 
 * We need to change them to GymAware.
 */
class SolarPacket : public Packet
{
public:
  SolarPacket(uint32_t value, uint16_t address);
  void setHeader(String header);
};


class DistancePacket : public Packet
{
public:
  DistancePacket(uint32_t value, uint16_t address);
  void setHeader(String header);
};

class HoneyTempPacket : public Packet
{
public:
  HoneyTempPacket(uint32_t value, uint16_t address);
  void setHeader(String header);
};

class HoneyHumiPacket : public Packet
{
public:
  HoneyHumiPacket(uint32_t value, uint16_t address);
  void setHeader(String header);
};

class ThermistorPacket: public Packet
{
public:
  ThermistorPacket(uint32_t value, uint16_t address);
  void setHeader(String header);
};

class DoorPacket: public Packet
{
public:
  DoorPacket(uint32_t value, uint16_t address);
  void setHeader(String header);
};

class MotionPacket: public Packet
{
public:
  MotionPacket(uint32_t value, uint16_t address);
  void setHeader(String header);
};
#endif // Packet_H
