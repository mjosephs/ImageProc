#include "MedianFilter.h"
#include <vector>
#include <algorithm> 

//Function is loosely based off of https://docs.opencv.org/master/d7/d37/tutorial_mat_mask_operations.html
cv::Mat variableMedian(cv::Mat img, int filterSize, bool avg) {
	cv::Mat img_out;
	//add as param: make sure to check before passing that it's %2 != 0;
	//int filterSize = 3;
	int boundary = filterSize / 2;
	std::vector<int> filterVals = { 0 };
	//bool avg = true;


	const int nChannels = img.channels();
	img_out.create(img.size(), img.type());
	std::vector<uchar *> rows;

	for (int j = boundary; j < img.rows - boundary; ++j)
	{
		const uchar* previous = img.ptr<uchar>(j - 1);
		const uchar* current = img.ptr<uchar>(j);
		const uchar* next = img.ptr<uchar>(j + 1);

		//Create array of uchars pointers here. So instead of curr prev and next, we'll have curr +- filterSize/2
		rows.clear();

		//Logic: Add curr to vector, then for(k =1; k <=boundary){ add row + k & row -k}
		rows.push_back(img.ptr<uchar>(j));

		for (int k = 1; k <= boundary; k++) {
			rows.push_back(img.ptr<uchar>(j - k));
			rows.push_back(img.ptr<uchar>(j + k));
		}

		uchar* output = img_out.ptr<uchar>(j);


		for (int i = nChannels; i < nChannels*(img.cols - boundary); ++i)
		{

			int *filterVals2;
			filterVals2 = (int*)malloc(filterSize*filterSize * sizeof(int));

			for (int k = 0; k < rows.size(); k++) {
				filterVals2[k] = rows[k][i];
				for (int l = 1; l <= boundary; l++) {
					filterVals2[(filterSize*l) + k] = rows[k][i - l * nChannels];
					filterVals2[10 + (filterSize*l) + k] = rows[k][i + l * nChannels];
				}

			}

			int avgTotal = 0, avgOutput = 0;
			if(!avg){
				///Sort the grid to find median
				int a = 0;
				for (int p = 0; p < filterSize*filterSize; ++p)
				{
					for (int q = p + 1; q < filterSize*filterSize; ++q)
					{
						if (filterVals2[p] > filterVals2[q])
						{
							a = filterVals2[p];
							filterVals2[p] = filterVals2[q];
							filterVals2[q] = a;
						}
					}
				}

				*output++ = cv::saturate_cast<uchar>(filterVals2[(filterSize*filterSize) / 2]);
				
			}
			else {
				int count = 0;
				for (int p = 0; p < filterSize*filterSize; ++p) {
					if (filterVals2[p] >= 0) {
						avgTotal += filterVals2[p];
						count++;
					}
					
					//std::cout << "Avg val: " << filterVals2[p] << std::endl;
				}
				avgOutput = avgTotal / (count);
				*output++ = cv::saturate_cast<uchar>(avgOutput);
			}

			free(filterVals2);
		}

		for (int p = 0; p < boundary; p++) {
			img_out.row(p).setTo(cv::Scalar(0));
			img_out.row(img_out.rows - (p + 1)).setTo(cv::Scalar(0));
			img_out.col(p).setTo(cv::Scalar(0));
			img_out.col(img_out.cols - (p + 1)).setTo(cv::Scalar(0));
		}

	}

	return img_out;
}

/*
cv::Mat median(cv::Mat img) {
	cv::Mat img_out;

	const int nChannels = img.channels();
	img_out.create(img.size(), img.type());

	for (int j = 1; j < img.rows - 1; ++j)
	{
		const uchar* previous = img.ptr<uchar>(j - 1);
		const uchar* current = img.ptr<uchar>(j);
		const uchar* next = img.ptr<uchar>(j + 1);

		uchar* output = img_out.ptr<uchar>(j);

		for (int i = nChannels; i < nChannels*(img.cols - 1); ++i)
		{
			int unsortedVals[9] = { 0 };
			//*output++ = cv::saturate_cast<uchar>(5 * current[i] - current[i - nChannels] - current[i + nChannels] - previous[i] - next[i]);
			
			unsortedVals[0] = current[i];
			unsortedVals[1] = current[i - nChannels];
			unsortedVals[2] = current[i + nChannels];
			unsortedVals[3] = previous[i];
			unsortedVals[4] = previous[i - nChannels];
			unsortedVals[5] = previous[i + nChannels];
			unsortedVals[6] = next[i];
			unsortedVals[7] = next[i - nChannels];
			unsortedVals[8] = next[i + nChannels];

			int a = 0;
			for (int p = 0; p < 9; ++p)
			{
				for (int q = p + 1; q < 9; ++q)
				{
					if (unsortedVals[p] > unsortedVals[q])
					{
						a = unsortedVals[p];
						unsortedVals[p] = unsortedVals[q];
						unsortedVals[q] = a;
					}
				}
			}
			*output++ = cv::saturate_cast<uchar>(unsortedVals[4]);
		}
		
		img_out.row(0).setTo(cv::Scalar(0));
		img_out.row(img_out.rows - 1).setTo(cv::Scalar(0));
		img_out.col(0).setTo(cv::Scalar(0));
		img_out.col(img_out.cols - 1).setTo(cv::Scalar(0));
		
	}

	return img_out;
}
*/