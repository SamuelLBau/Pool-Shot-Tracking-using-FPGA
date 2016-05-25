#include "BilliardBall.h"
//#include "mathUtility.cpp"


BilliardBall::BilliardBall(int ballNum, float radius, Point2D position){
	this-> number = ballNum;
	this-> radius = radius;
	this-> position = position;
	this-> velocity = Vector2D(0,0);
	this-> speed = 0;
	this-> inPocket = false;
}

BilliardBall::BilliardBall(){}
BilliardBall::~BilliardBall(){}

void BilliardBall::setPosition(float x, float y){
	position.setX(x);
	position.setY(y);
}

void BilliardBall::setPosition(Point2D point){
	position.setPoint(point);
}

Point2D BilliardBall::getPosition(){
	return position;
}

int BilliardBall::getNumber(){
	return number;
}

void BilliardBall::setNumber(int number){
	this-> number = number;
}

int BilliardBall::getRadius(){
	return radius;
}

void BilliardBall::setRadius(int radius){
	this-> radius = radius;
}

Vector2D BilliardBall::getVelocity(){
	return velocity;
}

void BilliardBall::setVelocity(Vector2D velocity){
	this -> velocity = velocity;
	this -> speed = velocity.length();
}

void BilliardBall::move(Vector2D move){
	position.setX(position.getX() + move.getX());
	position.setY(position.getY() + move.getY());

}

void BilliardBall::addVelocity(Vector2D amount){
	velocity.setX(velocity.getX() + amount.getX());
	velocity.setY(velocity.getY() + amount.getY());
}

bool BilliardBall::checkInPocket(){
	return inPocket;
}

void BilliardBall::setPocket(bool status){
	inPocket = status;
}


Linear_function::Linear_function(Point2D point1, Point2D point2){
	slope = (point1.getY() - point2.getY())/(point1.getX() - point2.getX());
	constant = point1.getY() - slope * point1.getY();
}

Linear_function::Linear_function(float slope, float constant){
	this -> slope = slope;
	this -> constant = constant;
}

Linear_function::Linear_function(Point2D point, Vector2D vector){
	slope = vector.getY()/ vector.getX();
	constant = point.getY() - slope * point.getX();
}

float Linear_function::getValue(float x){
	return x * slope + constant;
}
