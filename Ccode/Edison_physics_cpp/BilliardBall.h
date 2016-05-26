#ifndef BilliardBall_h
#define BilliardBall_h
#include "stdafx.h"
#include "mathUtility.h"

//#include <stdio.h>

class BilliardBall{
public:
	BilliardBall();
	~BilliardBall();
	BilliardBall(int ballNum, float radius, Point2f position);
	void setPosition(float x, float y);
	void setPosition(Point2f point);
	Point2f getPosition();
	int getNumber();
	void setNumber(int number);
	float getRadius();
	void setRadius(float radius);
	Vector2D getVelocity();
	void setVelocity(Vector2D velocity);
	void move(Vector2D move);
	void addVelocity(Vector2D amount);
	bool checkInPocket();
	void setPocket(bool status);

	Point2f position;
	int number;
	int radius;
	Vector2D velocity;
	float speed;
	bool inPocket;
};



#endif

