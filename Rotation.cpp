#include <opencv2\opencv.hpp>
#include "Rotation.h"

using namespace std;
using namespace cv;

Mat Rotation(Mat img, double angle)
{
	Mat image_out;

	//center
	Point2f pt(img.cols / 2, img.rows / 2);
	Mat r = getRotationMatrix2D(pt, angle, 1.0);

	//affine transformation; preserves original proportions
	warpAffine(img, image_out, r, Size(img.cols, img.rows));
	return image_out;
}