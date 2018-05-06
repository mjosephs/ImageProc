#include "blacknwhite.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat blacknwhite(Mat img) {
	Mat gray;
	cvtColor(img, gray, CV_RGB2GRAY);
	return gray;
}
