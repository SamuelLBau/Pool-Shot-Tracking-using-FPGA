#ifndef BilliardGame_h
#define BilliardGame_h

#include <iostream>
#include "BilliardBall.h"
#include "Table.h"
using namespace std;

class BilliardGame{
public:
	Table table;

	BilliardBall whiteBall;
	BilliardBall yellowBall;
	BilliardBall blueBall;
	BilliardBall redBall;
	BilliardBall purpleBall;
	BilliardBall orangeBall;
	BilliardBall greenBall;
	BilliardBall brownBall;
	BilliardBall blackBall;
	BilliardBall strYellowBall;
	BilliardBall strBlueBall;
	BilliardBall strRedBall;
	BilliardBall strPurpleBall;
	BilliardBall strOrangeBall;
	BilliardBall strGreenBall;
	BilliardBall strBrownBall;

	BilliardBall balls[16];

	BilliardGame();
	~BilliardGame(){};
	BilliardBall getCollisionPos(BilliardBall* moveBall, BilliardBall* stayBall);
	void transformBall(int num, Vector2D move);
	int getClosestPocket(BilliardBall ball);

};



#endif