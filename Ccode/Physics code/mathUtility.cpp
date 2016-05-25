#include "mathUtility.h"

//Point2D::Point2D(){}
//Point2D::~Point2D(){}

Point2D::Point2D(float x, float y){
	this->x = x;
	this->y = y;
}

float Point2D::getX(){
	return x;
}

float Point2D::getY(){
	return y;
}

void Point2D::setX(float x){
	this->x = x;
}

void Point2D::setY(float y){
	this->y = y;
}

void Point2D::setPoint(Point2D point){
	this->x = point.getX();
	this->y = point.getY();
}


int distance(Point2D point1, Point2D point2){
	float x_dis = point1.getX() - point2.getX();
	float y_dis = point1.getY() - point2.getY();

	return sqrt(x_dis * x_dis + y_dis * y_dis);
}


