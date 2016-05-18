#!/usr/bin/env python

import math as m
from mathUnits import *

""" billiardball class """
class BilliardBall:
	def __init__(self, number, radius, position):

		#############
		self.position = position
		#############

		self.number = number
		self.color = None
		self.radius = radius
		self.velocity = Vector2D(0, 0)
		self.speed = 0.0
		self.inPocket = False

	def setPosition(self, x = None, y = None, point = None):

		if x != None and y != None:
			self.position.x = x
			self.position.y = y

		elif point != None:
			self.position = point

		else:
			print "invalid input stream"


	def getNumber(self):
		return self.number

	def setNumber(self, number):
		self.number = number

	def getColor(self):
		return self.color

	def setColor(self, color):
		self.color = color

	def getRadius(self):
		return self.radius

	def setRadius(self, radius):
		self.radius = radius


	def getVelocity(self):
		return self.velocity

	def setVelocity(self, velocity):
		self.velocity = velocity
		self.speed = velocity.length()


	def move(self, move):

		#move
		self.position.setX(self.position.getX() + move.getX())
		self.position.setY(self.position.getY() + move.getY())

		#rotate
		#TODO--

	def addVelocity(self, amount):
		self.velocity.setX(self.velocity.getX() + amount.getX())
		self.velocity.setY(self.velocity.getY() + amount.getY())

	def inPocket(self):
		return self.inPocket

	def putInPocket(self):
		self.inPocket = true
		# take it out of the array


	