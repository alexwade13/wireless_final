import time
import threading

class XbeeStub(threading.Thread):
    def __init__(self, callback, filename):
        super(XbeeStub, self).__init__()
        self.callback = callback
        self.file = open(filename, 'r')

        # wait for the other thread to start up, throw exception if
        # it is taking too long
        self.startedEvent = threading.Event()
        self.start()
        if not self.startedEvent.wait(5):
            raise Exception('XbeeStub failed to start')

    def run(self):
        # we started the other thread!
        self.startedEvent.set()

        while True:
            # emit the packet, return if it's null
            packet = self.emit_packet()
            if packet is None:
                return

            # send the function the callback (use None for the xbee object for
            # now since we don't use it in implementation
            self.callback(None, packet)

    def close(self):
        # close the file
        self.file.close()

    def emit_packet(self):
        line = self.file.readline()
        if line == "":
            return None

        return {'rf_data': line[:-1],
                'rssi': '0',
                'source_addr': '\x00\x00',
                'id': 'rx',
                'options': '\x00'
                }
