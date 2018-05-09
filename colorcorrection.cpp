#include "colorcorrection.h"

bool check = false;
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

void modColor();
void briFunc(int, void*);
void conFunc(int, void*);
void rgbSet(int, void*);

cv::Mat colorCorrection(cv::Mat input){
    cv::namedWindow("Color Correction", cv::WINDOW_AUTOSIZE);
    img = input;
    result = cv::Mat::zeros(img.size(), img.type());

    cv::createTrackbar(bar_rgb, "Color Correction", &channels, 3, rgbSet);

    cv::createTrackbar(bar_bri, "Color Correction", &beta, 255, briFunc);
    cv::setTrackbarMin(bar_bri, "Color Correction", -255);

    //trackbar only takes int, have to divide alpha by 100, so actually contrast is from 0.0 to 3.0 not 0 to 300
    cv::createTrackbar(bar_con, "Color Correction", &alpha, 300, conFunc);
    cv::setTrackbarMin(bar_con, "Color Correction", 0);

    briFunc(0, 0);

    for(;;){
        char c = (char)cv::waitKey(20);
        if (c == 27){
            cv::destroyAllWindows();
            return result;
            break;
        }
    }
}

void modColor(){
    int alphaval = alpha;
    int betaval = beta;  
    if(channels < 3){
        for (int y = 0; y < img.rows; y++){
            for(int x = 0; x < img.cols; x++){
                result.at<cv::Vec3b>(y,x)[channels] = cv::saturate_cast<uchar>((alphaval/100.0) *(img.at<cv::Vec3b>(y,x)[channels]) + betaval);
            }
        }
    }else{
        for (int y = 0; y < img.rows; y++){
            for(int x = 0; x < img.cols; x++){
                for(int c = 0; c < 3; c++) {
                    result.at<cv::Vec3b>(y,x)[c] = cv::saturate_cast<uchar>((alphaval/100.0) *(img.at<cv::Vec3b>(y,x)[c]) + betaval);
                }
            }
        }
    }
    alpha_bgr[channels] = alphaval;
    beta_bgr[channels] = betaval;
}

//saves positions of trackbars per channel, sort of works 
//saving contrast breaks when you change brightness, unsure why
void rgbSet(int, void*){
    alpha = alpha_bgr[channels];
    beta = beta_bgr[channels];
    modColor();
    cv::setTrackbarPos(bar_bri, "Color Correction", beta);
    cv::setTrackbarPos(bar_con, "Color Correction", alpha);
    cv::imshow("Color Correction", result);
}

void briFunc(int, void*){
    modColor(); 
    cv::imshow("Color Correction", result);
}

void conFunc(int, void*){
    modColor();
    cv::imshow("Color Correction", result);
}