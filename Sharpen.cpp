#include "Sharpen.h"

//To use this in Main.cpp, include "Sharpen.h" at the top and call sharpen(img) in Main.cpp
cv::Mat sharpen(cv::Mat img) {
	cv::Mat img_out;

	//Example frmo: https://docs.opencv.org/master/d7/d37/tutorial_mat_mask_operations.html
	cv::Mat kernel = (cv::Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(img, img_out, img.depth(), kernel);

	return img_out;
}