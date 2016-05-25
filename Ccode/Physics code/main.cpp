
//import cv2

//#include "math.h"
#include <iostream>
//#include <array>
#include "BilliardBall.h"
//#include "mathUtility.h"
#include "Table.h"
using namespace std;

// class Failure(Exception):
//     """Failure exception"""
//     def __init__(self,value):
//         self.value=value
//     def __str__(self):
//         return repr(self.value)



class Linear_function{
public:
	float slope;
	float constant;

	Linear_function();
	~Linear_function();
	Linear_function(Point2D point1, Point2D point2);
	Linear_function(float slope, float constant);
	Linear_function(Point2D point,Vector2D vector);
	float getValue(float x);
};

Linear_function::Linear_function(){}
Linear_function::~Linear_function(){}

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
	~BilliardGame();
	BilliardBall getCollisionPos(BilliardBall moveBall, BilliardBall stayBall);
	void transformBall(int num, Vector2D move);
	int getClosestPocket(BilliardBall ball);

};

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


BilliardBall BilliardGame::getCollisionPos(BilliardBall moveBall, BilliardBall stayBall){
		int radius = moveBall.radius;
		float sx = stayBall.position.getX();
		float sy = stayBall.position.getY();

		Linear_function move_function = Linear_function(moveBall.getPosition(), moveBall.getVelocity());
		float a = move_function.slope * move_function.slope + 1;
		float b = 2 * (move_function.slope * move_function.constant - move_function.slope * sy - sx);
		float c = sx * sx - 4 * radius * radius + (sy - move_function.constant) * (sy - move_function.constant);
		float delta = b * b - 4 * a * c;

		if (delta <= 0){
			cout<<"no collision detected";
			return moveBall;
		}

		else{
			float x1 = ((-1 * b) - sqrt(delta)) / (2 * a);
			float y1 = move_function.getValue(x1);
			Point2D x1y1 = Point2D(x1, y1);

			float x2 = ((-1 * b) + sqrt(delta)) / (2 * a);
			float y2 = move_function.getValue(x2);
			Point2D x2y2 = Point2D(x2, y2);


			Linear_function x1y1_to_stay_function = Linear_function(x1y1, stayBall.position);

			Linear_function x2y2_to_stay_function = Linear_function(x2y2, stayBall.position);

			float tan_x1y1 = (x1y1_to_stay_function.slope - move_function.slope) / (1 + x1y1_to_stay_function.slope * move_function.slope);

			float tan_x2y2 = (x2y2_to_stay_function.slope - move_function.slope) / (1 + x2y2_to_stay_function.slope * move_function.slope);

			if (distance(moveBall.position, x1y1) < distance(moveBall.position, x2y2)){

				float theta = M_PI/2 - atan(tan_x1y1);

				float new_stay_sp = moveBall.speed * sin(theta);

				Vector2D new_stay_ve = Vector2D(x1y1, stayBall.position);

				float k = new_stay_sp / new_stay_ve.length();

				stayBall.setVelocity(new_stay_ve.scale(k));

				float new_move_sp = moveBall.speed * cos(theta);
				Vector2D new_move_ve = new_stay_ve.normal();
				float k_ = new_move_sp / new_move_ve.length();

				BilliardBall haloBall = BilliardBall(99, 9, x1y1);
				haloBall.setVelocity(new_move_ve.scale(k_));

				return haloBall;
			}

			else{

				float theta = M_PI/2 - atan(tan_x2y2);

				float new_stay_sp = moveBall.speed * sin(theta);

				Vector2D new_stay_ve = Vector2D(x2y2, stayBall.position);

				float k = new_stay_sp / new_stay_ve.length();

				stayBall.setVelocity(new_stay_ve.scale(k));

				float new_move_sp = moveBall.speed * cos(theta);
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
		float dist = distance(ball.position, table.pockets->at(i).position);
		if(dist < min_dist){
			min_dist = dist;
			pocket_num = table.pockets->at(i).number;
		}
	}

	return pocket_num;
}




int main(){
	cout<<"____________________________________________________"<<endl;
	cout<<"                                                    "<<endl;
	cout<<"          Pool Ball Game Simulation begin           "<<endl;
	cout<<"____________________________________________________\n\n"<<endl;

}

/*
	def simulate(self):

		print "____________________________________________________"
		print "                                                    "
		print "          Pool Ball Game Simulation begin           "
		print "____________________________________________________\n\n"
		img = cv2.imread('simple_game_crop.png')
		height, width, channels = img.shape
		print "image width: ", width
		print "image height: ", height

		white_ball_pos  = Point2D(1061.0, 510.0)
		yellow_ball_pos = Point2D(863.0, 268.0)
		blue_ball_pos = Point2D(271.0, 316.0)
		brown_ball_pos = Point2D(780.0, 58.0)
		orange_ball_pos = Point2D(698.0, 185.0)
		green_ball_pos = Point2D(624.0, 213.0)
		black_ball_pos = Point2D(71.0, 92.0)

		sim_velocity = Vector2D(from_point = white_ball_pos, to_point = yellow_ball_pos).scale(0.5)


		self.balls[0].setPosition(point = white_ball_pos)
		self.balls[9].setPosition(point = yellow_ball_pos)
		self.balls[2].setPosition(point = blue_ball_pos)
		self.balls[5].setPosition(point = orange_ball_pos)
		self.balls[6].setPosition(point = green_ball_pos)
		self.balls[7].setPosition(point = brown_ball_pos)
		self.balls[8].setPosition(point = black_ball_pos)

		# check balls have velocity or not
		self.balls[0].setVelocity(sim_velocity)

		#p = Point2D(0,0)

		white = self.balls[0]
		cv2.circle(img,(int(white.position.x),int(white.position.y)), white.radius, (0,0,255), 2)

		yellow = self.balls[9]
		cv2.circle(img,(int(yellow.position.x),int(yellow.position.y)), yellow.radius, (0,0,255), 2)


		blue = self.balls[2]
		cv2.circle(img,(int(blue.position.x),int(blue.position.y)), blue.radius, (0,0,255), 2)

		orange = self.balls[5]
		cv2.circle(img,(int(orange.position.x),int(orange.position.y)), orange.radius, (0,0,255), 2)

		green = self.balls[6]
		cv2.circle(img,(int(green.position.x),int(green.position.y)), green.radius, (0,0,255), 2)

		brown = self.balls[7]
		cv2.circle(img,(int(brown.position.x),int(brown.position.y)), brown.radius, (0,0,255), 2)

		black = self.balls[8]
		cv2.circle(img,(int(black.position.x),int(black.position.y)), black.radius, (0,0,255), 2)



		p = self.getCollisionPos(self.balls[0], self.balls[9])


		print "white ball located at: (", white.position.x, ",", white.position.y, ")"
		print "white ball speed is: ", white.speed
		print "yellow ball located at: (", yellow.position.x, ",", yellow.position.y, ")"
		print "the closest pocket to yellow is: ", self.getClosestPocket(yellow)
		print "collision point is at: (", p.x, ",", p.y, ")"

		yellow = self.balls[9]

		print "After collision: \n       yellow ball speed is: ", yellow.speed



		cv2.line(img, (int(white.position.x),int(white.position.y)), (int(white.position.x+white.velocity.x_factor),
			int(white.position.y+white.velocity.y_factor)), (0,0,255), 2)


		cv2.line(img, (int(yellow.position.x),int(yellow.position.y)), (int(yellow.position.x+yellow.velocity.x_factor),
			int(yellow.position.y+yellow.velocity.y_factor)), (0,0,255), 2)


		cv2.circle(img,(int(p.x),int(p.y)), white.radius, (0,0,255), 2)

		q = self.haloBall
		cv2.line(img, (int(q.position.x),int(q.position.y)), (int(q.position.x+q.velocity.x_factor),int(q.position.y+q.velocity.y_factor)), (0,0,255), 2)



		self.table.showPockets(img)

		cv2.imshow('image',img)
		cv2.waitKey(0)
		cv2.destroyAllWindows()


		print "\n\n##########simulation terminated successfully##########\n"

		

if __name__ == '__main__':
	g = BilliardGame()
	g.simulate()
*/


