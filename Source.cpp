#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat histEqualization(const Mat& inputImage) {
	if (inputImage.channels() >= 3) {
		Mat ycrcb;
		cvtColor(inputImage, ycrcb, CV_BGR2YCrCb);

		vector<Mat> channels;
		split(ycrcb, channels);

		equalizeHist(channels[0], channels[0]);

		Mat result;
		merge(channels, ycrcb);

		cvtColor(ycrcb, result, CV_YCrCb2BGR);
		return result;
	}

	return Mat();
}
int main() {
	Mat img = imread("lena.jpg");
	Mat img1 = imread("lena.jpg");

	histEqualization(img1);
	namedWindow("image", WINDOW_NORMAL);
	namedWindow("image1", WINDOW_NORMAL);
	imshow("image", img);
	imshow("image1", img1);
	waitKey(0);
	return 0;
}