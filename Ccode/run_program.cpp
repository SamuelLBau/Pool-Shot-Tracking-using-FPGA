#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
  Mat im = imread(argc == 2 ? argv[1] : "lena.jpg", 1);
  if (im.empty())
  {
    cout << "Cannot open image!" << endl;
    return -1;
  }

  imshow("image", im);
  waitKey(0);

  return 0;
}