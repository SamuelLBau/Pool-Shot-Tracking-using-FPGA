#include "BilliardGame.h"


BilliardGame::BilliardGame(){
	table = Table(1212, 634);

	whiteBall =  BilliardBall(0, 18, Point2D(0,0));
	yellowBall = BilliardBall(1, 1, Point2D(0,0));
	blueBall =   BilliardBall(2, 18, Point2D(0,0));
	redBall =    BilliardBall(3, 1, Point2D(0,0));
	purpleBall = BilliardBall(4, 1, Point2D(0,0));
	orangeBall = BilliardBall(5, 18, Point2D(0,0));
	greenBall =  BilliardBall(6, 18, Point2D(0,0));
	brownBall =  BilliardBall(7, 18, Point2D(0,0));
	blackBall =  BilliardBall(8, 18, Point2D(0,0));
	strYellowBall = BilliardBall(9, 18, Point2D(0,0));
	strBlueBall =   BilliardBall(10, 1, Point2D(0,0));
	strRedBall =    BilliardBall(11, 1, Point2D(0,0));
	strPurpleBall = BilliardBall(12, 1, Point2D(0,0));
	strOrangeBall = BilliardBall(13, 1, Point2D(0,0));
	strGreenBall =  BilliardBall(14, 1, Point2D(0,0));
	strBrownBall =  BilliardBall(15, 1, Point2D(0,0));

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


BilliardBall BilliardGame::getCollisionPos(BilliardBall* moveBall, BilliardBall* stayBall){
		int radius = (*moveBall).radius;
		float sx = (*stayBall).position.getX();
		float sy = (*stayBall).position.getY();

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
			Point2D x1y1 = Point2D(x1, y1);

			float x2 = ((-1 * b) + sqrt(delta)) / (2 * a);
			float y2 = move_function.getValue(x2);
			Point2D x2y2 = Point2D(x2, y2);


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



int BilliardGame::getClosestPocket(BilliardBall ball){

	float min_dist = INFINITY;
	int pocket_num = 0;

	for(int i = 0; i < 6; i++){

		float dist = distance(ball.position, table.pockets[i].position);
		if(dist < min_dist){
			min_dist = dist;
			pocket_num = table.pockets[i].number;
		}
	}
	return pocket_num;
}
