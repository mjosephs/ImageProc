#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat img = imread(argv[1]);
	int choice;

	while(1)
	{
		cout << "Choose what to do with image\n";
		cout << "1. Show imag\n";

		//making sure input is an int before continuing
		while(cout << "Input: " && !(cin >> choice))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nInvalid input, try again\n";
		}

		switch (choice)
		{
			case 1 	:	namedWindow("Image Show", WINDOW_AUTOSIZE);
					 	imshow("Image Show", img);
						waitKey(0);
						destroyWindow("Image Show");
						break;

			default : 	cout << "Invalid input\n";
						break;
		}
	}
	
	return 0;
}