#include <opencv2/opencv.hpp>
#include <iostream>
#include "Sharpen.h"
#include "Enhance.h"
#include "blacknwhite.h"
#include "thresholding.h"

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

	while (1)
	{
		cout << "\nChoose what to do with image\n";
		cout << "1. Show image\n";
		cout << "2. Sharpen image\n";
		cout << "3. Enhance image using histogram equalization\n";
		cout << "4. Make image black and white\n";
		cout << "5. Binary threshold the image with a slider (press Escape to finish)\n";
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
				
		case 0:	 imwrite("output.jpg", img_save);
				cout << "Saved to output.jpg in working directory\n";
				break;

		default:  cout << "Invalid input\n";
				break;
		}
	}

	return 0;
}
