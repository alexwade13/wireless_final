#include "Transmitter.h"
#include "Arduino.h"
#include "Packet.h"
#include "XBee.h"

#define htons(A) ((((uint16_t)(A) & 0xff00) >> 8) | (((uint16_t)(A) & 0x00ff) << 8))

Transmitter::Transmitter(int address, int pan, int channel)
{
  // the channel configuration of the device
  m_address = htons(address);
  m_pan = htons(pan);
  m_channel = channel;
  m_xbee = XBee();

  // generate the AT commands necesary to configure the device
  AtCommandRequest myRequest = AtCommandRequest( (uint8_t*)"MY", (uint8_t*)&m_address, 2 );
  AtCommandRequest chRequest = AtCommandRequest( (uint8_t*)"CH", (uint8_t*)&m_channel, 1);
  AtCommandRequest idRequest = AtCommandRequest( (uint8_t*)"ID", (uint8_t*)&m_pan, 2);
  
  AtCommandRequest at_read_my = AtCommandRequest( (uint8_t*)"MY");
  AtCommandRequest at_read_ch = AtCommandRequest( (uint8_t*)"CH");
  AtCommandRequest at_read_id = AtCommandRequest( (uint8_t*)"ID");
  AtCommandRequest at_read_mm = AtCommandRequest( (uint8_t*)"MM");

  // initialize serial
  Serial1.begin(38400);

  // enter AT mode
  Serial1.write("+++");
  delay(1200);

  // initial AT commands
  Serial1.write("ATAP2\r");
  Serial1.write("ATWR\r");
  Serial1.write("ATCN\r");

  // read out the data generated by above AT command
  while ( Serial1.available() ) {
    Serial1.read();
  }

  m_xbee.setSerial(Serial1);

  // 5 second delay
  for (int i=0; i < 5; i ++){
    Serial.print("Delay ");
    Serial.print(i);
    Serial.println(" of 5\n");
    delay(1000);
  }
  // send off the generated requests
  m_xbee.send(myRequest);
  rxPacket();

  m_xbee.send(chRequest);
  rxPacket();

  m_xbee.send(idRequest);
  rxPacket();

  m_xbee.send(at_read_my);
  rxPacket();
  m_xbee.send(at_read_ch);
  rxPacket();
  m_xbee.send(at_read_id);
  rxPacket();
  m_xbee.send(at_read_mm);
  rxPacket(); 
}

void 
Transmitter::rxPacket() 
{
  Serial.println("Reading a packet...\n");
  if ( m_xbee.readPacket(1000) ) {
    Serial.println("Received the packet...");
    XBeeResponse response = m_xbee.getResponse();
    if ( response.getApiId() == TX_STATUS_RESPONSE ) {
      handleTXResponse(response);
    } else if ( response.getApiId() == RX_16_RESPONSE ) {
      handleRXResponse(response);
    } else if ( response.getApiId() == AT_COMMAND_RESPONSE ) {
      handleATResponse(response);
    } else {
      Serial.println("RX: unknown response: ");
      Serial.println(response.getApiId());
    }
  } else if ( m_xbee.getResponse().isError() ) {
    Serial.println("Error reading packet: ");
    Serial.println(m_xbee.getResponse().getErrorCode());
    Serial.println("\n");
  }
}

void 
Transmitter::txPacket(String header, float value, uint16_t destAddress)
{
  Packet pack = Packet(header, (int) value, destAddress);
  Tx16Request req = pack.getTx16Request();
  m_xbee.send(req);
}

void 
Transmitter::txPacket(String header, int value, uint16_t destAddress)
{
  Packet pack = Packet(header, value, destAddress);
  Tx16Request req = pack.getTx16Request();
  m_xbee.send(req);
}

void 
Transmitter::handleTXResponse(XBeeResponse response)
{
}

void 
Transmitter::handleRXResponse(XBeeResponse response)
{
}

void 
Transmitter::handleATResponse(XBeeResponse response)
{
}
