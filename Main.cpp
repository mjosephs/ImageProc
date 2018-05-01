#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main() {
	Mat img = imread("lena.jpg");
	Mat out;
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

	//filter2D(img, out, img.depth(), kernel);

	namedWindow("image", WINDOW_NORMAL);
	imshow("image", img);

	//namedWindow("image_out", WINDOW_NORMAL);
	//imshow("image", out);

	waitKey(0);


	return 0;
}	