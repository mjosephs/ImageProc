#include "Sharpen.h"

//To use this in Main.cpp, include "Sharpen.h" at the top and call sharpen(img) in Main.cpp
cv::Mat sharpen(cv::Mat img) {
	cv::Mat img_out;

	cv::Mat kernel = (cv::Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(img, img_out, img.depth(), kernel);

	//moved this to a general function in main
	/*
	cv::namedWindow("Image Out", cv::WINDOW_AUTOSIZE);
	imshow("Image Out", img_out);
	cv::waitKey(0);
	cv::destroyWindow("Image Out");
	*/ 

	return img_out;
}