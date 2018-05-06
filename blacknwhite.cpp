#include "blacknwhite.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat blacknwhite(Mat img) {
	Mat gray = imread(img, CV_LOAD_IMAGE_GRAYSCALE);
	Mat colour = imread(img);
	Mat gray;
	cvtColor(colour, gray, CV_RGB2GRAY);
	return gray;
}
