#include "colorcorrection.h"

int alpha = 100;
int alpha_bgr[4] = {100, 100, 100, 100};
int beta = 0;
int beta_bgr[4] = {0, 0, 0, 0};
int channels = 3;
const char* bar_rgb = "Blue = 0\nGreen = 1\nRed = 2\nRGB = 3\n";
const char* bar_bri = "Brightness:";
const char* bar_con = "Contrast:";

cv::Mat img;
cv::Mat result;

void clrFunc(int, void*);
void rgbSet(int, void*);

cv::Mat colorCorrection(cv::Mat input){
    cv::namedWindow("Color Correction", cv::WINDOW_AUTOSIZE);
    img = input;
    result = cv::Mat::zeros(img.size(), img.type());

    cv::createTrackbar(bar_rgb, "Color Correction", &channels, 3, rgbSet);

    cv::createTrackbar(bar_bri, "Color Correction", &beta, 255, clrFunc);
    cv::setTrackbarMin(bar_bri, "Color Correction", -255);

    //trackbar only takes int, have to divide alpha by 100, so actually contrast is from 0.0 to 3.0 not 0 to 300
    cv::createTrackbar(bar_con, "Color Correction", &alpha, 300, clrFunc);
    cv::setTrackbarMin(bar_con, "Color Correction", 0);

    clrFunc(0, 0);

    for(;;){
        char c = (char)cv::waitKey(20);
        if (c == 27){
            cv::destroyAllWindows();
            return result;
            break;
        }
    }
}

//saves positions of trackbars per channel, sort of works 
//saving contrast breaks when you change brightness, unsure why
void rgbSet(int, void*){
   cv::setTrackbarPos(bar_bri, "Color Correction", beta_bgr[channels]);
   cv::setTrackbarPos(bar_con, "Color Correction", alpha_bgr[channels]);
}

void clrFunc(int, void*){

    //if rgb set to a channel, only perform operations on that channel
    if(channels < 3){

        for (int y = 0; y < img.rows; y++){
            for(int x = 0; x < img.cols; x++){
                result.at<cv::Vec3b>(y,x)[channels] = cv::saturate_cast<uchar>((alpha/100.0) *(img.at<cv::Vec3b>(y,x)[channels]) + beta);
            }
        }
        //used when channels get set to remember trackbar pos
        alpha_bgr[channels] = alpha;
        beta_bgr[channels] = beta;

    }else{
        for (int y = 0; y < img.rows; y++){
            for(int x = 0; x < img.cols; x++){
                for(int c = 0; c < 3; c++) {
                    result.at<cv::Vec3b>(y,x)[c] = cv::saturate_cast<uchar>((alpha/100.0) *(img.at<cv::Vec3b>(y,x)[c]) + beta);
                }
            }
        }
        alpha_bgr[3] = alpha;
        beta_bgr[3] = beta;

    }

    cv::imshow("Color Correction", result);
};