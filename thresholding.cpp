#include "thresholding.h"
#include<vector>
#include<numeric>

cv::Mat gray;
cv::Mat rslt;
int threshold_value = 128;
int const max_value = 255;
const char* trackbar_value = "Value: ";
int const max_BINval = 255;

void threshFunc(int, void*);

cv::Mat thresholding(cv::Mat img){
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    rslt = gray.clone();
    cv::namedWindow("Thresholding", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar(trackbar_value, "Thresholding", &threshold_value, max_value, threshFunc);

    threshFunc(0, 0);

    for(;;){
        char c = (char)cv::waitKey(20);
        if (c == 27){
            cv::destroyAllWindows();
            return rslt;
            break;
        }
    }
}

void threshFunc(int, void*){
    int T = threshold_value;
    int T_prev = 0;
    int a = 5;
    std::vector<int> u1;
	float average1 = 0;
	std::vector<int> u2;
	float average2 = 0;
    //cv::threshold(gray, dst, threshold_value, max_BINval, threshold_type);
    while ( !((abs(T-T_prev)) < a) ){
		T_prev = T;
		for (int y = 0; y<gray.rows; y++)
			for (int x=0; x<gray.cols; x++)
	    	{	
				//sorting pixels into two vectors based on T value
				if (gray.at<uchar>(y,x) > T){
					u1.push_back(gray.at<uchar>(y,x));
				}else{
					u2.push_back(gray.at<uchar>(y,x));
				}
			}
		average1 = std::accumulate(u1.begin(), u1.end(), 0.0)/u1.size();
		average2 = std::accumulate(u2.begin(), u2.end(), 0.0)/u2.size();
		T = int(0.5*(average1 + average2));
	}
	for (int y=0; y<gray.rows; y++)
		for (int x=0; x<gray.cols; x++)
	    {
			if (gray.at<uchar>(y,x) >= T){
				rslt.at<uchar>(y,x) = 255;
			}else{
				rslt.at<uchar>(y,x) = 0;
			}
		}
    
    cv::imshow("Thresholding", rslt);
}



