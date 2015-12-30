"""
basestation_parse_driver: communicates between the base station and the Parse backend.

Author: Li Li (ll024)
"""

from parse_rest.connection import register
from parse_rest.datatypes import Object
from enum import Enum

# Register the app
APPLICATION_ID = "TXKbSqb0WSRZ6fWAf0Ebe1i9zKZffnfi5upTorIN"
REST_API_KEY = "nREKzZcJ01dq5ECDJHaYUNvb6Q1LxIdbaoHFK31i",
MASTER_KEY = "lEovyfkywcKkBqWwcUG2YXr9eiXC4UsAVeuoCdot"

register(APPLICATION_ID, REST_API_KEY, master_key = MASTER_KEY)

class SensorType(Enum):
	"""
	Enum SensorType: specifies the type of the sensor
	"""
	null = 1
	ultrasonic = 2
	long_distance = 3
	short_distance = 4
	infrared = 5

class EquipmentType(Enum):
	"""
	Enum EquipmentType: specifies the equipment type
	"""
	null = 1
	treadmill = 2


class RawData(Object):
	"""
	class RawData: Represents the raw data sent to the Parse backend.
	Note: To save teh data to Parse, call save().
	"""

	@staticmethod
	def create():
		'''
		Creates a RawData object with null equipment type, null sensor type and no data. 
		Users might need to call the setter methods to set those types later.
		'''
		return RawData(sensor_type = SensorType.null.name, data=0)
	
	@staticmethod
	def create(sensor_type, data):
		'''
		Creates a RawData object with specified equipment type,k sensor type and data

		equipment_type: an EquipmentType enum
		sensor_type: a SensorType enum
		data: a number representing the data
		'''
		return RawData(sensor_type = sensor_type.name, data=data)

	def set_sensor_type(sensor_type):
		'''
		Sets the sensor type
	
		sensor_type: a SensorType enum
		'''
		self.sensor_type = sensor_type.name

	def set_data(data):
		'''
		Sets the data 

		data: a number representing the data
		'''
		self.data = data
