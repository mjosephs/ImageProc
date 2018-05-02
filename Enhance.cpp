#include <opencv2/opencv.hpp>
#include <iostream>
#include "Enhance.h"

using namespace std;
using namespace cv;

void Enhance(Mat img) {
	if (img.channels() >= 3) {
		Mat ycrcb;
		cvtColor(img, ycrcb, CV_BGR2YCrCb);

		vector<Mat> channels;
		split(ycrcb, channels);

		equalizeHist(channels[0], channels[0]);

		Mat result;
		merge(channels, ycrcb);

		cvtColor(ycrcb, result, CV_YCrCb2BGR);
	}

	namedWindow("image", WINDOW_NORMAL);
	imshow("image", img);
	waitKey(0);
	destroyWindow("image");
}