#include "BilliardGame.h"


BilliardGame::BilliardGame(){
	table = Table(1212, 634);

	whiteBall =  BilliardBall(0, 18, Point2f(0,0));
	yellowBall = BilliardBall(1, 18, Point2f(0,0));
	blueBall =   BilliardBall(2, 18, Point2f(0,0));
	redBall =    BilliardBall(3, 18, Point2f(0,0));
	purpleBall = BilliardBall(4, 18, Point2f(0,0));
	orangeBall = BilliardBall(5, 18, Point2f(0,0));
	greenBall =  BilliardBall(6, 18, Point2f(0,0));
	brownBall =  BilliardBall(7, 18, Point2f(0,0));
	blackBall =  BilliardBall(8, 18, Point2f(0,0));
	strYellowBall = BilliardBall(9, 18, Point2f(0,0));
	strBlueBall =   BilliardBall(10, 18, Point2f(0,0));
	strRedBall =    BilliardBall(11, 18, Point2f(0,0));
	strPurpleBall = BilliardBall(12, 18, Point2f(0,0));
	strOrangeBall = BilliardBall(13, 18, Point2f(0,0));
	strGreenBall =  BilliardBall(14, 18, Point2f(0,0));
	strBrownBall =  BilliardBall(15, 18, Point2f(0,0));

	balls[0] = whiteBall;
	balls[1] = yellowBall;
	balls[2] = blueBall;
	balls[3] = redBall;
	balls[4] = purpleBall;
	balls[5] = orangeBall;
	balls[6] = greenBall;
	balls[7] = brownBall;
	balls[8] = blackBall;
	balls[9] = strYellowBall;
	balls[10] = strBlueBall;
	balls[11] = strRedBall;
	balls[12] = strPurpleBall;
	balls[13] = strOrangeBall;
	balls[14] = strGreenBall;
	balls[15] = strBrownBall;
}

BilliardGame::BilliardGame(vector<Point2f> ballCenters, vector<int> ballIds, vector<float> ballRadii,Size inSize,
 vector<Point2f>* collisionCircles, vector<float>* collisionRadii, vector<Point2f>* shotLines){

	table = Table(inSize.width, inSize.height);

	for(int i = 0; i < 16; i++){
		balls[i] = BilliardBall(-1, 0, Point2f(-100,-100));
	}

	bool cueFound = false;

	for(int i = 0; i < ballIds.size(); i++){

		//overwritten will take place
		balls[ballIds[i]] = BilliardBall(ballIds[i], ballRadii[i], ballCenters[i]);

		if(ballIds[i] == CUE_BALL_ID)
			cueFound = true;
	}

	if(!cueFound)
		return;

	BilliardBall cueBall = balls[CUE_BALL_ID];

	for(int i = 0; i < 16; i++){

		if(balls[i].getNumber() == CUE_BALL_ID || balls[i].getNumber() == -1)
			continue;


		BilliardBall haloBall = getCollisionPos(getPocket(balls[i], cueBall), balls[i], cueBall);

		if (haloBall.getNumber() == -1)
			continue;

		//render suggest-shot
		collisionCircles->push_back(haloBall.position);
		collisionRadii->push_back(haloBall.radius);
		shotLines->push_back(cueBall.position);
		shotLines->push_back(haloBall.position);

		//render shot to pocket
		collisionCircles->push_back(getPocket(balls[i], cueBall).position);
		collisionRadii->push_back(balls[i].radius);
		shotLines->push_back(getPocket(balls[i], cueBall).position);
		shotLines->push_back(balls[i].position);
	}

}

BilliardBall BilliardGame::getCollisionPos(Pocket pocket, BilliardBall ball, BilliardBall cueBall){

	if(pocket.number == -1){
		return BilliardBall(-1, 0, Point2f(-100, -100));
	}

	float radius = cueBall.radius;
	float sx = ball.position.x;
	float sy = ball.position.y;

	Vector2D to_pocket_vector = Vector2D(pocket.position, ball.position);
	Linear_function to_pocket_function = Linear_function(ball.position, to_pocket_vector);
	float a = to_pocket_function.slope * to_pocket_function.slope + 1;
	float b = 2 * (to_pocket_function.slope * to_pocket_function.constant - to_pocket_function.slope * sy - sx);
	float c = sx * sx - 4 * radius * radius + (sy - to_pocket_function.constant) * (sy - to_pocket_function.constant);
	float delta = b * b - 4 * a * c;

	float x1 = ((-1 * b) - sqrt(delta)) / (2 * a);
	float y1 = to_pocket_function.getValue(x1);
	Point2f x1y1 = Point2f(x1, y1);

	float x2 = ((-1 * b) + sqrt(delta)) / (2 * a);
	float y2 = to_pocket_function.getValue(x2);
	Point2f x2y2 = Point2f(x2, y2);

	if (distance(cueBall.position, x1y1) < distance(cueBall.position, x2y2)){

		if(checkBallInteraction(ball, cueBall))
			return BilliardBall(-1, 0, Point2f(-100, -100));
		return BilliardBall(99, cueBall.radius, x1y1);
	}
	else{
		if(checkBallInteraction(ball, cueBall))
			return BilliardBall(-1, 0, Point2f(-100, -100));
		return BilliardBall(99, cueBall.radius, x2y2);
	}
}


bool BilliardGame::checkBallInteraction(BilliardBall ball, BilliardBall cueBall){
	Linear_function move_function = Linear_function(ball.position, cueBall.position);
	float radius = ball.radius;

	for(int i=0; i < 16; i++){

		if(checkBetweenTwoPoints(balls[i].position, ball.position, cueBall.position)){

			float dist = abs(move_function.slope * balls[i].position.x + move_function.constant
				 - balls[i].position.y)/(sqrt(move_function.slope * move_function.slope + 1));

			if(dist <= 2 * radius){
				return true;
			}
		} 
	}
	return false;
}



BilliardBall BilliardGame::getCollisionPos(BilliardBall* moveBall, BilliardBall* stayBall){
	float radius = (*moveBall).radius;
	float sx = (*stayBall).position.x;
	float sy = (*stayBall).position.y;

	Linear_function move_function = Linear_function((*moveBall).getPosition(), (*moveBall).getVelocity());
	float a = move_function.slope * move_function.slope + 1;
	float b = 2 * (move_function.slope * move_function.constant - move_function.slope * sy - sx);
	float c = sx * sx - 4 * radius * radius + (sy - move_function.constant) * (sy - move_function.constant);
	float delta = b * b - 4 * a * c;

	if (delta <= 0){
		cout<<"no collision detected";
		return *moveBall;
	}

	else{
		float x1 = ((-1 * b) - sqrt(delta)) / (2 * a);
		float y1 = move_function.getValue(x1);
		Point2f x1y1 = Point2f(x1, y1);

		float x2 = ((-1 * b) + sqrt(delta)) / (2 * a);
		float y2 = move_function.getValue(x2);
		Point2f x2y2 = Point2f(x2, y2);


		Linear_function x1y1_to_stay_function = Linear_function(x1y1, (*stayBall).position);

		Linear_function x2y2_to_stay_function = Linear_function(x2y2, (*stayBall).position);

		float tan_x1y1 = (x1y1_to_stay_function.slope - move_function.slope) / (1 + x1y1_to_stay_function.slope * move_function.slope);

		float tan_x2y2 = (x2y2_to_stay_function.slope - move_function.slope) / (1 + x2y2_to_stay_function.slope * move_function.slope);

		if (distance((*moveBall).position, x1y1) < distance((*moveBall).position, x2y2)){

			float theta = M_PI/2 - atan(tan_x1y1);

			float new_stay_sp = (*moveBall).speed * sin(theta);

			Vector2D new_stay_ve = Vector2D(x1y1, (*stayBall).position);

			float k = new_stay_sp / new_stay_ve.length();

			(*stayBall).setVelocity(new_stay_ve.scale(k));

			float new_move_sp = (*moveBall).speed * cos(theta);
			Vector2D new_move_ve = new_stay_ve.normal();
			float k_ = new_move_sp / new_move_ve.length();

			BilliardBall haloBall = BilliardBall(99, 9, x1y1);
			haloBall.setVelocity(new_move_ve.scale(k_));

			return haloBall;
		}

		else{

			float theta = M_PI/2 - atan(tan_x2y2);

			float new_stay_sp = (*moveBall).speed * sin(theta);

			Vector2D new_stay_ve = Vector2D(x2y2, (*stayBall).position);

			float k = new_stay_sp / new_stay_ve.length();

			(*stayBall).setVelocity(new_stay_ve.scale(k));

			float new_move_sp = (*moveBall).speed * cos(theta);
			Vector2D new_move_ve = new_stay_ve.normal();
			float k_ = new_move_sp / new_move_ve.length();

			BilliardBall haloBall = BilliardBall(99, 9, x2y2);
			haloBall.setVelocity(new_move_ve.scale(k_));


			return haloBall;
		}
	}
}


void BilliardGame::transformBall(int num, Vector2D move){
	balls[num].move(move);
}



Pocket BilliardGame::getClosestPocket(BilliardBall ball){

	float min_dist = INFINITY;
	int pocket_num = 0;

	for(int i = 0; i < 6; i++){

		float dist = distance(ball.position, table.pockets[i].position);
		if(dist < min_dist){
			min_dist = dist;
			pocket_num = table.pockets[i].number;
		}
	}
	return table.pockets[pocket_num - 1];
}


Pocket BilliardGame::getPocket(BilliardBall ball, BilliardBall cueBall){

	int pocket_num = 0;
	int index;
	std::vector<Pocket> new_pockets = table.pockets;
	bool foundBest = false;

	while(!foundBest && !new_pockets.empty()){
		float min_dist = INFINITY;
		float dist_ball_to_pocket;

		for(int i = 0; i < new_pockets.size(); i++){
			dist_ball_to_pocket = distance(ball.position, new_pockets[i].position);
			if (dist_ball_to_pocket < min_dist){
				min_dist = dist_ball_to_pocket;
				pocket_num = new_pockets[i].number;
				index = i;
			}
			
		}

		Pocket pocket = table.pockets[pocket_num - 1];

		Vector2D to_pocket_vector = Vector2D(pocket.position, ball.position);
		Linear_function to_pocket_function = Linear_function(ball.position, to_pocket_vector);
		float radius = cueBall.radius;
		float sx = ball.position.x;
		float sy = ball.position.y;
		float a = to_pocket_function.slope * to_pocket_function.slope + 1;
		float b = 2 * (to_pocket_function.slope * to_pocket_function.constant - to_pocket_function.slope * sy - sx);
		float c = sx * sx - 4 * radius * radius + (sy - to_pocket_function.constant) * (sy - to_pocket_function.constant);
		float delta = b * b - 4 * a * c;

		float x1 = ((-1 * b) - sqrt(delta)) / (2 * a);
		float y1 = to_pocket_function.getValue(x1);
		Point2f x1y1 = Point2f(x1, y1);

		float x2 = ((-1 * b) + sqrt(delta)) / (2 * a);
		float y2 = to_pocket_function.getValue(x2);
		Point2f x2y2 = Point2f(x2, y2);

		if (distance(cueBall.position, x1y1) < distance(cueBall.position, x2y2)){

			float dist_xy_to_pocket = distance(x1y1, pocket.position);

			if ( dist_xy_to_pocket <= min_dist || checkBallInteraction(ball, cueBall)){
				new_pockets.erase(new_pockets.begin() + index);
				continue;
			}
			else
				foundBest = true;

		}
		else{
			float dist_xy_to_pocket = distance(x2y2, pocket.position);


			if ( dist_xy_to_pocket <= min_dist || checkBallInteraction(ball, cueBall)){
				new_pockets.erase(new_pockets.begin() + index);
				continue;
			}
			else
				foundBest = true;
		}
	}

	if(!foundBest) return Pocket(-1, Point2f(0,0));
	else return table.pockets[pocket_num - 1];
}


