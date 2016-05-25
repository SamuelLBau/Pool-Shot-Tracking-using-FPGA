#ifndef BilliardBall_h
#define BilliardBall_h
#include "mathUtility.h"

//#include <stdio.h>

class BilliardBall{
public:
	BilliardBall();
	~BilliardBall();
	BilliardBall(int ballNum, float radius, Point2D position);
	void setPosition(float x, float y);
	void setPosition(Point2D point);
	Point2D getPosition();
	int getNumber();
	void setNumber(int number);
	int getRadius();
	void setRadius(int radius);
	Vector2D getVelocity();
	void setVelocity(Vector2D velocity);
	void move(Vector2D move);
	void addVelocity(Vector2D amount);
	bool checkInPocket();
	void setPocket(bool status);

	Point2D position;
	int number;
	int radius;
	Vector2D velocity;
	float speed;
	bool inPocket;
};



#endif

