
//import cv2

//#include "mathUtility.cpp"
//#include <array>
#include "stdafx.h"
#include "Table.h"


Pocket::Pocket(int number, Point2f position){
	this -> position = position;
	this -> number = number;
}

int Pocket::getNumber(){
	return number;
}

void Pocket::setNumber(int number){
	this -> number = number;
}

Point2f Pocket::getPosition(){
	return position;
}

void Pocket::setPosition(Point2f position){
	this -> position = position;
}



Cue::Cue(Point2f position){
	this -> position = position;
}

Point2f Cue::getPosition(){
	return position;
}

void Cue::setPosition(Point2f position){
	this -> position = position;
}

Vector2D Cue::getVelocity(){
	return velocity;
}

void Cue::setVelocity(Vector2D velocity){
	this -> velocity.setX(velocity.getX());
	this -> velocity.setY(velocity.getY());
}




Table::Table(int width, int length){
	this -> width = width;
	this -> length = length;

	int radius = 30;


	pocket1 = Pocket(1, Point2f(0 + radius,     0 + radius));
	pocket2 = Pocket(2, Point2f(width/2,  		0 + radius/2));
	pocket3 = Pocket(3, Point2f(width - radius, 0 + radius));
	pocket4 = Pocket(4, Point2f(0 + radius,     length - radius ));
	pocket5 = Pocket(5, Point2f(width/2,  		length - radius/2));
	pocket6 = Pocket(6, Point2f(width - radius, length - radius));


	//pockets = new Pocket[6];

	//pockets[0] = pocket1;
	//pockets[1] = pocket2;
	//pockets[2] = pocket3;
	//pockets[3] = pocket4;
	//pockets[4] = pocket5;
	//pockets[5] = pocket6;

	
	//pockets = new std::vector<Pocket*>;

	pockets.push_back(pocket1);
	pockets.push_back(pocket2);
	pockets.push_back(pocket3);
	pockets.push_back(pocket4);
	pockets.push_back(pocket5);
	pockets.push_back(pocket6);
	
	
}

Table::~Table(){

/*
	delete pocket1;
	delete pocket2;
	delete pocket3;
	delete pocket4;
	delete pocket5;
	delete pocket6;


	delete pockets;
	*/
}

int Table::getLength(){
	return length;
}

void Table::setLength(int length){
	this -> length = length;
}

int Table::getWidth(){
	return width;
}

void Table::setWidth(int width){
	this -> width = width;
}

Pocket Table::getPocket(int number){
	return pockets[number - 1];
	//return pockets[number - 1];
}


/*	def showPockets(self, img = None):

		for pocket in self.pockets:
			if img == None:
				print "pocket ", pocket.number, " loacted at: (", pocket.position.x, ",", pocket.position.y, ")"
			else:
				cv2.circle(img,(int(pocket.position.x),int(pocket.position.y)), 30, (0,0,255), 2)
				font = cv2.FONT_HERSHEY_SIMPLEX
				cv2.putText(img, str(pocket.number), (pocket.position.x, pocket.position.y), font, 1, (0,0,255), 2)
*/

