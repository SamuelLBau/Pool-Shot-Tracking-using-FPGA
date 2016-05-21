#!/usr/bin/env python

# 1. get while ball postion and direction
# 2. get the move path and extend the path until it hits something
# 3. move the white ball at the collision point
# 4. apply collision calculation on while ball and the hitten ball
# 5. calculate the afterward path
# 6. repeat #(2-5) on every pool ball on the table

#physics calculation need math package
import numpy as np
import cv2
import math as m
from BillardBall import *
from mathUnits import *
from Table import *


class Failure(Exception):
    """Failure exception"""
    def __init__(self,value):
        self.value=value
    def __str__(self):
        return repr(self.value)



class Linear_function:
	def __init__(self, point1 = None, point2 = None, slope = None, constant = None, vector = None):
		if point1 != None and point2 != None:
			self.slope = (point1.y - point2.y)/(point1.x - point2.x)
			self.constant = point1.y - self.slope * point1.x

		elif slope != None and constant != None:
			self.slope = slope
			self.constant = constant

		elif vector != None:
			self.slope = vector.y_factor/ vector.x_factor

			if point1 != None:
				self.constant = point1.y - self.slope * point1.x
			elif point2 != None:
				self.constant = point2.y - self.slope * point2.x
			else:
				print "\ninvalid data input stream"

		else:
			print "\ninvalid data input stream"


	def getValue(self, x):
		return x * self.slope + self.constant


class BilliardGame:

	def __init__(self):

		self.table = Table(1212, 634)

		self.whiteBall =  BilliardBall(0, 18, Point2D(0,0))
		self.yellowBall = BilliardBall(1, 1, Point2D(0,0))
		self.blueBall =   BilliardBall(2, 18, Point2D(0,0))
		self.redBall =    BilliardBall(3, 1, Point2D(0,0))
		self.purpleBall = BilliardBall(4, 1, Point2D(0,0))
		self.orangeBall = BilliardBall(5, 18, Point2D(0,0))
		self.greenBall =  BilliardBall(6, 18, Point2D(0,0))
		self.brownBall =  BilliardBall(7, 18, Point2D(0,0))
		self.blackBall =  BilliardBall(8, 18, Point2D(0,0))
		self.strYellowBall = BilliardBall(9, 18, Point2D(0,0))
		self.strBlueBall =   BilliardBall(10, 1, Point2D(0,0))
		self.strRedBall =    BilliardBall(11, 1, Point2D(0,0))
		self.strPurpleBall = BilliardBall(12, 1, Point2D(0,0))
		self.strOrangeBall = BilliardBall(13, 1, Point2D(0,0))
		self.strGreenBall =  BilliardBall(14, 1, Point2D(0,0))
		self.strBrownBall =  BilliardBall(15, 1, Point2D(0,0))

		self.balls = [ self.whiteBall,  self.yellowBall, \
		               self.blueBall,   self.redBall, \
		               self.purpleBall, self.orangeBall, \
		               self.greenBall,  self.brownBall, \
		               self.blackBall,      self.strYellowBall, \
		               self.strBlueBall,   self.strRedBall, \
		               self.strPurpleBall, self.strOrangeBall, \
		               self.strGreenBall,  self.strBrownBall]



	def transformBall(self, number, vector):
		self.balls[number].move(vector)


	def getCollisionPos(self, moveBall, stayBall):
		#moveBall = self.balls[moveBallNum]
		#stayBall = self.balls[stayBallNum]
		radius = moveBall.radius
		sx = stayBall.position.x
		sy = stayBall.position.y
		#moveFunc = LinearFunc(0, moveBall.velocity.x)

		move_function = Linear_function(point1 = moveBall.position, vector = moveBall.velocity)
		a = move_function.slope * move_function.slope + 1.0
		b = 2.0 * (move_function.slope * move_function.constant - move_function.slope * sy - sx)
		c = sx * sx - 4.0 * radius * radius + (sy - move_function.constant) * (sy - move_function.constant)
		delta = b * b - 4.0 * a * c

		if delta <= 0:
			raise Failure("\nSimulation terminated unexpectedly\n ERROR: no collision detected")

		#elif delta == 0:
		#	collision_x = (-1 * b) / (2 * a)
		#	collision_y = move_function.getValue(collision_x)
		#	return Point2D(collision_x, collision_y)

		else:
			x1 = ((-1 * b) - m.sqrt(delta)) / (2 * a)
			y1 = move_function.getValue(x1)
			x1y1 = Point2D(x1, y1)

			x2 = ((-1 * b) + m.sqrt(delta)) / (2 * a)
			y2 = move_function.getValue(x2)
			x2y2 = Point2D(x2, y2)


			x1y1_to_stay_function = Linear_function(point1 = Point2D(x1, y1), point2 = stayBall.position)

			x2y2_to_stay_function = Linear_function(point1 = Point2D(x2, y2), point2 = stayBall.position)

			tan_x1y1 = (x1y1_to_stay_function.slope - move_function.slope) / (1 + x1y1_to_stay_function.slope * move_function.slope)

			tan_x2y2 = (x2y2_to_stay_function.slope - move_function.slope) / (1 + x2y2_to_stay_function.slope * move_function.slope)

			if distance(moveBall.position, x1y1) < distance(moveBall.position, x2y2):

				theta = m.pi/2 - m.atan(tan_x1y1)

				new_stay_sp = moveBall.speed * m.sin(theta)

				new_stay_ve = Vector2D(from_point = x1y1, to_point = stayBall.position)

				k = new_stay_sp / new_stay_ve.length()

				stayBall.setVelocity(new_stay_ve.scale(k))
				#self.balls[stayBallNum].setVelocity(new_stay_ve.scale(k))

				new_move_sp = moveBall.speed * m.cos(theta)
				new_move_ve = new_stay_ve.normal()
				k_ = new_move_sp / new_move_ve.length()

				self.haloBall = BilliardBall(99, 9, x1y1)
				self.haloBall.setVelocity(new_move_ve.scale(k_))

				return x1y1

			else:

				theta = m.pi/2 - m.atan(tan_x2y2)
				#print "tan_x2y2 = ", tan_x2y2
				#print "delta = ", m.degrees(m.atan(tan_x2y2))
				#print "theta = ", m.degrees(theta)


				new_stay_sp = moveBall.speed * m.sin(theta)
				#print "move ball speed = ", moveBall.speed
				#print "new_stay_sp = ", new_stay_sp


				new_stay_ve = Vector2D(from_point = x2y2, to_point = stayBall.position)
				#print "new_stay_ve = (", new_stay_ve.x_factor, ",", new_stay_ve.y_factor, ")"

				k = new_stay_sp / new_stay_ve.length()
				#print "new_stay_ve.length = ", new_stay_ve.length()
				#print "scale k = ", k

				stayBall.setVelocity(new_stay_ve.scale(k))

				#self.balls[stayBallNum].setVelocity(new_stay_ve.scale(k))

				new_move_sp = moveBall.speed * m.cos(theta)
				new_move_ve = new_stay_ve.normal()
				k_ = new_move_sp / new_move_ve.length()

				self.haloBall = BilliardBall(99, 9, x2y2)
				self.haloBall.setVelocity(new_move_ve.scale(k_))


				return x2y2



	def getClosestPocket(self, ball):

		min_dist = float('inf')
		pocket_num = 0
		for pocket in self.table.pockets:
			dist = distance(ball.position, pocket.position)
			if dist < min_dist:
				min_dist = dist
				pocket_num = pocket.number

		return pocket_num



	def simulate(self):

		print "____________________________________________________"
		print "                                                    "
		print "          Pool Ball Game Simulation begin           "
		print "____________________________________________________\n\n"
		img = cv2.imread('simple_game_crop.png')
		height, width, channels = img.shape
		print "image width: ", width
		print "image height: ", height

		white_ball_pos  = Point2D(1061.0, 510.0)
		yellow_ball_pos = Point2D(863.0, 268.0)
		blue_ball_pos = Point2D(271.0, 316.0)
		brown_ball_pos = Point2D(780.0, 58.0)
		orange_ball_pos = Point2D(698.0, 185.0)
		green_ball_pos = Point2D(624.0, 213.0)
		black_ball_pos = Point2D(71.0, 92.0)

		sim_velocity = Vector2D(from_point = white_ball_pos, to_point = yellow_ball_pos).scale(0.5)


		self.balls[0].setPosition(point = white_ball_pos)
		self.balls[9].setPosition(point = yellow_ball_pos)
		self.balls[2].setPosition(point = blue_ball_pos)
		self.balls[5].setPosition(point = orange_ball_pos)
		self.balls[6].setPosition(point = green_ball_pos)
		self.balls[7].setPosition(point = brown_ball_pos)
		self.balls[8].setPosition(point = black_ball_pos)

		# check balls have velocity or not
		self.balls[0].setVelocity(sim_velocity)

		#p = Point2D(0,0)

		white = self.balls[0]
		cv2.circle(img,(int(white.position.x),int(white.position.y)), white.radius, (0,0,255), 2)

		yellow = self.balls[9]
		cv2.circle(img,(int(yellow.position.x),int(yellow.position.y)), yellow.radius, (0,0,255), 2)


		blue = self.balls[2]
		cv2.circle(img,(int(blue.position.x),int(blue.position.y)), blue.radius, (0,0,255), 2)

		orange = self.balls[5]
		cv2.circle(img,(int(orange.position.x),int(orange.position.y)), orange.radius, (0,0,255), 2)

		green = self.balls[6]
		cv2.circle(img,(int(green.position.x),int(green.position.y)), green.radius, (0,0,255), 2)

		brown = self.balls[7]
		cv2.circle(img,(int(brown.position.x),int(brown.position.y)), brown.radius, (0,0,255), 2)

		black = self.balls[8]
		cv2.circle(img,(int(black.position.x),int(black.position.y)), black.radius, (0,0,255), 2)



		p = self.getCollisionPos(self.balls[0], self.balls[9])


		print "white ball located at: (", white.position.x, ",", white.position.y, ")"
		print "white ball speed is: ", white.speed
		print "yellow ball located at: (", yellow.position.x, ",", yellow.position.y, ")"
		print "the closest pocket to yellow is: ", self.getClosestPocket(yellow)
		print "collision point is at: (", p.x, ",", p.y, ")"

		yellow = self.balls[9]

		print "After collision: \n       yellow ball speed is: ", yellow.speed



		cv2.line(img, (int(white.position.x),int(white.position.y)), (int(white.position.x+white.velocity.x_factor),
			int(white.position.y+white.velocity.y_factor)), (0,0,255), 2)


		cv2.line(img, (int(yellow.position.x),int(yellow.position.y)), (int(yellow.position.x+yellow.velocity.x_factor),
			int(yellow.position.y+yellow.velocity.y_factor)), (0,0,255), 2)


		cv2.circle(img,(int(p.x),int(p.y)), white.radius, (0,0,255), 2)

		q = self.haloBall
		cv2.line(img, (int(q.position.x),int(q.position.y)), (int(q.position.x+q.velocity.x_factor),int(q.position.y+q.velocity.y_factor)), (0,0,255), 2)



		self.table.showPockets(img)

		cv2.imshow('image',img)
		cv2.waitKey(0)
		cv2.destroyAllWindows()


		print "\n\n##########simulation terminated successfully##########\n"

		

if __name__ == '__main__':
	g = BilliardGame()
	g.simulate()



