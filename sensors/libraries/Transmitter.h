#ifndef Transmitter_H
#define Transmitter_H

#include "Arduino.h"
#include "Packet.h"
#include "XBee.h"

class Transmitter
{
public:
  Transmitter(int address, int pan, int channel);
  void rxPacket();
  void txPacket(String header, float temperature, uint16_t destAddress);
  void txPacket(String header, int temperature, uint16_t destAddress);

private:
  void handleTXResponse(XBeeResponse);
  void handleRXResponse(XBeeResponse);
  void handleATResponse(XBeeResponse);
  uint16_t m_address;
  uint16_t m_pan;
  uint8_t m_channel;
  XBee m_xbee;
};

#endif // Transmitter_H
