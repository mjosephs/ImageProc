#include "thresholding.h"

cv::Mat gray, dst;
int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
const char* trackbar_value = "Value: ";
int const max_BINval = 255;

void threshFunc(int, void*);

cv::Mat thresholding(cv::Mat img){
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::namedWindow("Thresholding", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar(trackbar_value, "Thresholding", &threshold_value, max_value, threshFunc);

    threshFunc(0, 0);

    for(;;){
        char c = (char)cv::waitKey(20);
        if (c == 27){
            cv::destroyAllWindows();
            return dst;
            break;
        }
    }
}

void threshFunc(int, void*){
    cv::threshold(gray, dst, threshold_value, max_BINval, threshold_type);
    imshow("Thresholding", dst);
}



