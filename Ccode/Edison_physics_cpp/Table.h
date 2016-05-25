#ifndef Table_h
#define Table_h

//#include <stdio.h>
#include <vector>
#include "mathUtility.h"


class Pocket{
public:
	Point2D position;
	int number;

	Pocket(){};
	~Pocket(){};
	Pocket(int number, Point2D position);
	int getNumber();
	void setNumber(int number);
	Point2D getPosition();
	void setPosition(Point2D point);
};


class Cue{
public:
	Point2D position;
	Vector2D velocity;

	Cue(){};
	~Cue(){};
	Cue(Point2D position);
	Point2D getPosition();
	void setPosition(Point2D point);
	Vector2D getVelocity();
	void setVelocity(Vector2D velocity);

};



class Table{
public:
	int width;
	int length;

	Pocket pocket1;
	Pocket pocket2;
	Pocket pocket3;
	Pocket pocket4;
	Pocket pocket5;
	Pocket pocket6;

	//Pocket* pockets;
	std::vector<Pocket> pockets;

	Table(){};
	~Table();
	Table(int width, int length);
	int getLength();
	void setLength(int length);
	int getWidth();
	void setWidth(int width);
	Pocket getPocket(int number);
	void showPockets();

private:

};
#endif