#include <opencv2/opencv.hpp>
#include <iostream>
#include "Sharpen.h"
#include "Enhance.h"
#include "blacknwhite.h"
#include "MedianFilter.h"
#include "thresholding.h"
#include "colorcorrection.h"

/*
Using OpenCV library found at https://opencv.org/

This a CLI based image processing toolbox implementing some basic processing techniques

Matthew Josephs
Renjie Zhou
Brian Jefferson
Sebastian Pokrywa
*/

using namespace std;
using namespace cv;

//general display image function
void displayImage(Mat mimg){
	cv::namedWindow("Image Out", cv::WINDOW_AUTOSIZE);
	imshow("Image Out", mimg);
	cv::waitKey(0);
	cv::destroyWindow("Image Out");
};

int main(int argc, char** argv) {
	Mat img = imread(argv[1]);
	int choice;
	Mat img_save;
	int filterSize = 0;

	while (1)
	{
		cout << "\nChoose what to do with image\n";
		cout << "1. Show image\n";
		cout << "2. Sharpen image\n";
		cout << "3. Enhance image using histogram equalization\n";
		cout << "4. Make image black and white\n";
		cout << "5. Globally threshold the image with a slider (press Escape to finish)\n";
		cout << "6. Variable Median Filter\n";
		cout << "7. Color correct image with brightness/contrast (Escape to finish)\n";
		cout << "0. Save modified image to disk\n";

		//making sure input is an int before continuing
		while (cout << "Input: " && !(cin >> choice))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nInvalid input, try again\n";
		}

		switch (choice)
		{
		case 1:	 displayImage(img);
				break;

		case 2:	 img_save = sharpen(img);
				displayImage(img_save);
				break;

		case 3:	 img_save = Enhance(img);
				displayImage(img_save);
				break;
			
		case 4: img_save = blacknwhite(img);
				displayImage(img_save);
				break;

		case 5: img_save = thresholding(img);
				break;

		case 6:	 
			cout << "Input filter size. Must be an odd number > 2" << endl;
			cin >> filterSize;
			while (filterSize < 3 || (filterSize % 2) == 0) {
				cout << "Invalid filter size. Try again." << endl;
				cin >> filterSize;
			}
			img_save = variableMedian(img, filterSize);
			displayImage(img_save);
			break;

		case 7: img_save = colorCorrection(img);
				break;
		
		case 0:	 imwrite("output.jpg", img_save);
				cout << "Saved to output.jpg in working directory\n";
				break;

		default:  cout << "Invalid input\n";
				break;
		}
	}

	return 0;
}
