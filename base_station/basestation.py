'''
basestation.py: collects data from the sensors and sends data to Parse
Author: Li Li (ll024)
Revised from the base station code in CS379 - Sensor Project
'''

from xbeestub import *
from xbeechat import *
from struct import *
import sys
# note that the path below should be changed to your local path
sys.path.append('/home/ll024/GymAware/cs379-final-project-gymaware/base_station/parse/')
from basestation_parse_driver import *

# to get seconds since epoch
import time

# for parsing serialized data
import struct

# threading stuff
import os
import sys
import signal

class Packet():
    """Class that encloses a message sent between a Sender and a Receiver.

    Attributes:
      header(str): the header of the packet
      content: the content of the packet
    """
    def __init__(self, header, content=''):
        # store away the values
        self.header = header
        self.content = content

    """
    parses the raw string into a packet object.
    """
    @staticmethod
    def parse(raw):
        # enforce proper typing of argument (this could cause problems)
        if type(raw) is not str:
            raise Error('invalid content provided')

        # split raw data into parts depending on the size of the packet
        header = raw[0:4]
        ser_content = raw[4:]

        # convert the serialized verion into raw format. It assumes that the packet received is in big endian
        content = struct.unpack("!i", ser_content)[0]

        # build the packet object
        packet = Packet(header, content)

        return packet

    """
    serializes the packet into a string.
    """
    def serialize(self):
        ser_content = struct.pack
        return self.header + self.content

class Receiver:
  """Class that receives messages from a Sender object
  """
  def __init__(self, usb, pan_id, address, channel=15):
    # configure the XBee radio, if in debug mode, instantiate stubbing class
    self.x = None
    self.last_data_received_time = time.time()
    if len(sys.argv) > 1 and sys.argv[1] == "debug":
        #print("Starting basestation in stub mode...")
        self.x = XbeeStub(self._on_packet, "stub_data.txt")
    else:
        print("Starting basestation...")
        self.x = XbeeChat(usb, pan_id, address, channel, self._on_packet)

  def _on_packet(self, xbee, packet):
    """
    receives a packet from a Sender object
    """

    #print("packet", packet)

    if 'rf_data' in packet:
      #print("Got rf packet!")
      # parse and process the packet
      s_packet = Packet.parse(packet['rf_data'])
      #print(packet['rf_data'])
      self._process_packet(s_packet)

  def _process_packet(self, s_packet):
    """
    processes a packet
    """

    # make sure the process packet interval to be at least
    # 5 seconds to prevent it from crashing
    if time.time() - self.last_data_received_time < 5:
      return;
    self.last_data_received_time = time.time()

    # handle packets with different headers
    if s_packet.header == "SDIR":
        data = RawData.create(SensorType.short_distance, s_packet.content)
    elif s_packet.header == "LDIR":
        data = RawData.create(SensorType.long_distance, s_packet.content)
    elif s_packet.header == "USDS":
        data = RawData.create(SensorType.ultrasonic, s_packet.content)
    elif s_packet.header == "IRTS":
        data = RawData.create(SensorType.infrared, s_packet.content)
    else:
        #send a raw data packet to parse to indicate an unknown packet
        data = RawData.create(SensorType.null, 0)
    data.save()

  def close(self):
      if self.x:
          self.x.close()
          self.x.join()


# program main for the receiver program
def main():
    r = None
    try:
        for val in ["0", "1", "2", "3", "4"]:
            try:
                #print("Attempting /dev/ttyUSB" + val)
                r = Receiver("/dev/ttyUSB" + val, 1000, 100)
            except Exception as a:
                continue
            break

        if r is None:
            #print("Could not connect to /dev/ttyUSB*")
            exit()

        while True:
            time.sleep(0.1)
    except KeyboardInterrupt:
        #print("bye")
        r.close()

main()
