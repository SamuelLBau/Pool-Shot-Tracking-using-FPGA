#include "mathUtility.h"

//Point2D::Point2D(){}
//Point2D::~Point2D(){}



int distance(Point2f point1, Point2f point2){
	float x_dis = point1.x - point2.x;
	float y_dis = point1.y - point2.y;

	return sqrt(x_dis * x_dis + y_dis * y_dis);
}

bool checkBetweenTwoPoints(Point2f point_to_be_check, Point2f point1, Point2f point2){

	float min_x = min(point1.x, point2.x);
	float max_x = max(point1.x, point2.x);
	float min_y = min(point1.y, point2.y);
	float max_y = max(point1.y, point2.y);

	if( point_to_be_check.x > min_x &&
		point_to_be_check.x < max_x &&
		point_to_be_check.y > min_y &&
		point_to_be_check.y < max_y){
		return true;
	}
	return false;
}

bool pointIsOnLine(Point2f point, Linear_function function){

	if(function.getValue(point.x) == point.y){
		return true;
	}
	return false;
}


Linear_function::Linear_function(Point2f point1, Point2f point2){
	slope = (point1.y - point2.y)/(point1.x - point2.x);
	constant = point1.y - slope * point1.x;
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
