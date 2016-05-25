#include "stdafx.h"
#include "mathUtility.h"

//Point2D::Point2D(){}
//Point2D::~Point2D(){}



int distance(Point2f point1, Point2f point2){
	float x_dis = point1.x - point2.x;
	float y_dis = point1.y - point2.y;

	return sqrt(x_dis * x_dis + y_dis * y_dis);
}


Linear_function::Linear_function(Point2f point1, Point2f point2){
	slope = (point1.y - point2.y)/(point1.x - point2.x);
	constant = point1.y - slope * point1.y;
}

Linear_function::Linear_function(float slope, float constant){
	this -> slope = slope;
	this -> constant = constant;
}

Linear_function::Linear_function(Point2f point, Vector2D vector){
	slope = vector.getY()/ vector.getX();
	constant = point.y - slope * point.x;
}

float Linear_function::getValue(float x){
	return x * slope + constant;
}
