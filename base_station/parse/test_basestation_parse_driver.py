"""
Test basestation_parse_driver

Author: Li Li (ll024)
"""

from basestation_parse_driver import *

rawData = RawData.create(SensorType.ultrasonic, 3)

rawData.save()
