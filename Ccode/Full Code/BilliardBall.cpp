#include "stdafx.h"
#include "BilliardBall.h"
//#include "mathUtility.cpp"


BilliardBall::BilliardBall(int ballNum, float radius, Point2f position){
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
	position.x = x;
	position.y = y;
}

void BilliardBall::setPosition(Point2f point){
	position = point;
}

Point2f BilliardBall::getPosition(){
	return position;
}

int BilliardBall::getNumber(){
	return number;
}

void BilliardBall::setNumber(int number){
	this-> number = number;
}

float BilliardBall::getRadius(){
	return radius;
}

void BilliardBall::setRadius(float radius){
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
	position.x += move.getX();
	position.y += move.getY();

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

