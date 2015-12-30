/*
 * Author: Li Li (ll024)
 */

#include "Packet.h"
#include "Arduino.h"
#include "XBee.h"

Packet::Packet(String header, uint32_t value, uint16_t address)
{
  setHeader(header);
  setValue(value);
  setAddress(address);
}

void
Packet::setHeader(String header)
{
  for (int i = 0; i < 4; i++) {
    m_header[i] = header.charAt(i);
  }
}

void
Packet::setValue(uint32_t value)
{
  m_value = value;
}

void
Packet::setAddress(uint16_t address)
{
  m_address = address;
}

Tx16Request
Packet::getTx16Request()
{
  setPayload();
  m_tx16Request = Tx16Request(m_address, (uint8_t*)&m_payload, 8);
  return m_tx16Request;
}

void
Packet::setPayload()
{
  //copy the header to payload
  for (int i = 0; i < 4; i++) {
    m_payload[i] = m_header[i];
  }

  //copy the value to payload
  uint8_t* p = (uint8_t*) &m_value;
  for (int i = 0; i < 4; i++) {
    //this is little endian though. Not sure if we need to change it to big endian
    m_payload[i+4] = p[3-i];
  }
}

void
Packet::printPayload()
{
  Serial.print("payload: ");
  for (int i = 0; i < 8; i++) {
    Serial.print(m_payload[i]);
  }
  Serial.println();
}

SolarPacket::SolarPacket(uint32_t value, uint16_t address)
  : Packet("SOLR", value, address)
{
}

void
SolarPacket::setHeader(String header)
{
  // do nothing
}

DistancePacket::DistancePacket(uint32_t value, uint16_t address)
  : Packet("DIST", value, address)
{
}

void
DistancePacket::setHeader(String header)
{
  // do nothing
}


HoneyTempPacket::HoneyTempPacket(uint32_t value, uint16_t address)
  : Packet("HONT", value, address)
{
}

void
HoneyTempPacket::setHeader(String header)
{
  // do nothing
}

HoneyHumiPacket::HoneyHumiPacket(uint32_t value, uint16_t address)
  : Packet("HONH", value, address)
{
}

void
HoneyHumiPacket::setHeader(String header)
{
  // do nothing
}

void
ThermistorPacket::setHeader(String header)
{
  // do nothing
}

ThermistorPacket::ThermistorPacket(uint32_t value, uint16_t address)
  : Packet("THRM", value, address)
{
}

void
DoorPacket::setHeader(String header)
{
  // do nothing
}

DoorPacket::DoorPacket(uint32_t value, uint16_t address)
  : Packet("DOOR", value, address)
{
}

void
MotionPacket::setHeader(String header)
{
  // do nothing
}

MotionPacket::MotionPacket(uint32_t value, uint16_t address)
  : Packet("MOTN", value, address)
{
}
