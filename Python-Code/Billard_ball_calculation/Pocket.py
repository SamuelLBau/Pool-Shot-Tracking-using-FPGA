
from mathUnits import *

class Table:
	def __init__(self, length, width):
		self.length = length
		self.width = width

		self.pocket1 = Pocket(1, Point2D(0,          self.length))
		self.pocket2 = Pocket(2, Point2D(self.width, self.length))
		self.pocket3 = Pocket(3, Point2D(0,          self.length/2))
		self.pocket4 = Pocket(4, Point2D(self.width, self.length/2))
		self.pocket5 = Pocket(5, Point2D(0,          0))
		self.pocket6 = Pocket(6, Point2D(self.width, 0))

		self.pockets = [self.pocket1, self.pocket2, self.pocket3, \
						self.pocket4, self.pocket5, self.pocket6 ]

	def getLength(self):
		return self.length

	def setLength(self, length):
		self.length = length

	def getWidth(self):
		return self.width

	def setWidth(self, width):
		self.width = width

	def getPocket(self, number):
		return self.pockets[number - 1]





class Pocket:
	def __init__(self, number, position):
		self.position = position
		self.number = number

	def getNumber(self):
		return self.number

	def setNumber(self, number):
		self.number = number

	def getPosition(self):
		return position

	def setPosition(self, position):
		self.position = position