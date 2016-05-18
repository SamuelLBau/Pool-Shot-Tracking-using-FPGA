#!/usr/bin/env python

import math as m



def distance(point1, point2):
	x_dis = point1.x - point2.x
	y_dis = point1.y - point2.y
	return m.sqrt(x_dis * x_dis + y_dis * y_dis)



# Position class defintion
""" move to a new module """
class Point2D:
	def __init__(self, x , y):
		self.x = x
		self.y = y

	def getX(self):
		return self.x

	def setX(self, x):
		self.x = x

	def getY(self):
		return self.y

	def setY(self, y):
		self.y = y




""" velocity class """
class Vector2D:
	def __init__(self, x_factor = None, y_factor = None, from_point = None, to_point = None):

		if x_factor != None and y_factor != None:
			self.x_factor = x_factor
			self.y_factor = y_factor

		elif from_point != None and to_point != None:
			self.x_factor = to_point.x - from_point.x
			self.y_factor = to_point.y - from_point.y

		else:
			print "\nERROR: invalid input data stream\n"


	def getX(self):
		return self.x_factor

	def setX(self, x):
		self.x_factor = x

	def getY(self):
		return self.y_factor

	def setY(self, y):
		self.y_factor = y

	def getVector(self):
		return Vector2D(self.x_factor, self.y_factor)

	def length(self):
		return m.sqrt(self.x_factor * self.x_factor + self.y_factor * self.y_factor)

	def getVectorLength(self):
		return math.sqrt((self.x_factor * self.x_factor)+(self.y_factor * self.y_factor))

	def add(self, vector):
		return Vector2D(self.x_factor+vector.x_factor, self.y_factor+vector.y_factor)

	def subtract(self, vector):
		return Vector2D(self.x_factor-vector.x_factor, self.y_factor-vector.y_factor)

	def scale(self, scale):
		return Vector2D(self.x_factor*scale, self.y_factor*scale)

	def normal(self):
		return Vector2D(self.y_factor, -1 * self.x_factor)

