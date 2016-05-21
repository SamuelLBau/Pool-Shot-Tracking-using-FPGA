#!/usr/bin/env python

import numpy as np
import cv2
from mathUnits import *

class Table:
	def __init__(self, width, length):
		self.length = length
		self.width = width

		self.cue = Cue(Point2D(0,0))

		radius = 30
		self.pocket1 = Pocket(1, Point2D(0 + radius,           	0 + radius))
		self.pocket2 = Pocket(2, Point2D(self.width/2,  		0 + radius/2))
		self.pocket3 = Pocket(3, Point2D(self.width - radius, 	0 + radius))
		self.pocket4 = Pocket(4, Point2D(0 + radius,          	self.length - radius ))
		self.pocket5 = Pocket(5, Point2D(self.width/2,  		self.length - radius/2))
		self.pocket6 = Pocket(6, Point2D(self.width - radius, 	self.length - radius))



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

	def showPockets(self, img = None):

		for pocket in self.pockets:
			if img == None:
				print "pocket ", pocket.number, " loacted at: (", pocket.position.x, ",", pocket.position.y, ")"
			else:
				cv2.circle(img,(int(pocket.position.x),int(pocket.position.y)), 30, (0,0,255), 2)
				font = cv2.FONT_HERSHEY_SIMPLEX
				cv2.putText(img, str(pocket.number), (pocket.position.x, pocket.position.y), font, 1, (0,0,255), 2)






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


class Cue:
	def __init__(self, position):
		self.position = position
		self.velocity = None

	def getPosition(self):
		return self.position

	def setPosition(self, position):
		self.position = position

	def getVelocity(self):
		return self.velocity

	def setVelocity():
		self.velocity = None