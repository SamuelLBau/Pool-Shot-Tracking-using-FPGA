#ifndef mathUtility_h
#define mathUtility_h

#include "math.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

class Vector2D{
public:
	Vector2D(){};
	~Vector2D(){};
	Vector2D(float x_factor, float y_factor){
		this-> x_factor = x_factor;
		this-> y_factor = y_factor;
	}
	Vector2D(Point2f from_point, Point2f to_point){
		x_factor = to_point.x - from_point.x;
		y_factor = to_point.y - from_point.y;
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
	Linear_function(Point2f point1, Point2f point2);
	Linear_function(float slope, float constant);
	Linear_function(Point2f point,Vector2D vector);
	float getValue(float x);
};

int distance(Point2f point1, Point2f point2);
bool checkBetweenTwoPoints(Point2f point_to_be_check, Point2f point1, Point2f point2);
bool pointIsOnLine(Point2f point, Linear_function function);


#endif