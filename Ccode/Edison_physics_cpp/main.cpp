#include "BilliardGame.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;


int main(){
	cout<<"____________________________________________________"<<endl;
	cout<<"                                                    "<<endl;
	cout<<"          Pool Ball Game Simulation begin           "<<endl;
	cout<<"____________________________________________________\n\n"<<endl;



	BilliardGame bg = BilliardGame();

	Point2f white_ball_pos  = Point2f(1061.0, 510.0);
	Point2f yellow_ball_pos = Point2f(863.0, 268.0);
	Point2f blue_ball_pos = Point2f(271.0, 316.0);
	Point2f brown_ball_pos = Point2f(780.0, 58.0);
	Point2f orange_ball_pos = Point2f(698.0, 185.0);
	Point2f green_ball_pos = Point2f(624.0, 213.0);
	Point2f black_ball_pos = Point2f(71.0, 92.0);
	Vector2D sim_velocity = Vector2D(white_ball_pos, yellow_ball_pos).scale(0.5);


    Point2f testpoint = Point2f(0, 0);
    

	bg.balls[0].setPosition(white_ball_pos);
	bg.balls[9].setPosition(yellow_ball_pos);
	bg.balls[2].setPosition(blue_ball_pos);
	bg.balls[5].setPosition(orange_ball_pos);
	bg.balls[6].setPosition(green_ball_pos);
	bg.balls[7].setPosition(brown_ball_pos);
	bg.balls[8].setPosition(black_ball_pos);


	bg.balls[0].setVelocity(sim_velocity);



	BilliardBall white = bg.balls[0];
		//cv2.circle(img,(int(white.position.x),int(white.position.y)), white.radius, (0,0,255), 2)

	BilliardBall yellow = bg.balls[9];
		//cv2.circle(img,(int(yellow.position.x),int(yellow.position.y)), yellow.radius, (0,0,255), 2)


	BilliardBall blue = bg.balls[2];
		//cv2.circle(img,(int(blue.position.x),int(blue.position.y)), blue.radius, (0,0,255), 2)

	BilliardBall orange = bg.balls[5];
		//cv2.circle(img,(int(orange.position.x),int(orange.position.y)), orange.radius, (0,0,255), 2)

	BilliardBall green = bg.balls[6];
		//cv2.circle(img,(int(green.position.x),int(green.position.y)), green.radius, (0,0,255), 2)

	BilliardBall brown = bg.balls[7];
		//cv2.circle(img,(int(brown.position.x),int(brown.position.y)), brown.radius, (0,0,255), 2)

	BilliardBall black = bg.balls[8];
		//cv2.circle(img,(int(black.position.x),int(black.position.y)), black.radius, (0,0,255), 2)




	BilliardBall haloBall = bg.getCollisionPos(&bg.balls[0], &bg.balls[9]);


	cout<<"white ball located at: (" << white.position.x << "," << white.position.y << ")" <<endl;
	cout << "white ball speed is: " << white.speed << endl;
	cout << "yellow ball located at: (" << yellow.position.x << "," << yellow.position.y << ")" <<endl;
	//cout << "the closest pocket to yellow is: " << bg.getClosestPocket(yellow) << endl;
	cout << "collision point is at: ("<< haloBall.position.x << "," << haloBall.position.y << ")" << endl;

	yellow = bg.balls[9];

	cout << "After collision: \n       yellow ball speed is: " << yellow.speed << endl;



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

		white_ball_pos  = Point2f(1061.0, 510.0)
		yellow_ball_pos = Point2f(863.0, 268.0)
		blue_ball_pos = Point2f(271.0, 316.0)
		brown_ball_pos = Point2f(780.0, 58.0)
		orange_ball_pos = Point2f(698.0, 185.0)
		green_ball_pos = Point2f(624.0, 213.0)
		black_ball_pos = Point2f(71.0, 92.0)

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

		#p = Point2f(0,0)

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


