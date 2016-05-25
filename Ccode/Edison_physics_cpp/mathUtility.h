#ifndef mathUtility_h
#define mathUtility_h

//#include <stdio.h>
#include "math.h"


class Point2D{

public:
	Point2D(){};
	~Point2D(){};
	Point2D(float x, float y);
	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
	void setPoint(Point2D point);

private:
	float x;
	float y;
};



class Vector2D{
public:
	Vector2D(){};
	~Vector2D(){};
	Vector2D(float x_factor, float y_factor){
		this-> x_factor = x_factor;
		this-> y_factor = y_factor;
	}
	Vector2D(Point2D from_point, Point2D to_point){
		x_factor = to_point.getX() - from_point.getX();
		y_factor = to_point.getY() - from_point.getY();
	}

	float getX(){return x_factor;}
	void  setX(float x){this->x_factor = x;}
	float getY(){return y_factor;}
	void  setY(float y){this->y_factor = y;}

	Vector2D getVector(){return Vector2D(x_factor, y_factor);}

	float length(){return sqrt(x_factor * x_factor + y_factor * y_factor);}

	Vector2D add(Vector2D vector){return Vector2D(x_factor + vector.x_factor, y_factor + vector.y_factor);}

	Vector2D subtract(Vector2D vector){return Vector2D(x_factor -vector.x_factor, y_factor - vector.y_factor);}

	Vector2D scale(float scale){return Vector2D(x_factor * scale, y_factor * scale);}

	Vector2D normal(){return Vector2D(y_factor, -1 * x_factor);}



private:
	float x_factor;
	float y_factor;
};



class Linear_function{
public:
	float slope;
	float constant;

	Linear_function(){};
	~Linear_function(){};
	Linear_function(Point2D point1, Point2D point2);
	Linear_function(float slope, float constant);
	Linear_function(Point2D point,Vector2D vector);
	float getValue(float x);
};

int distance(Point2D point1, Point2D point2);



#endif