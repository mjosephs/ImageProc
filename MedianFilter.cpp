#include "MedianFilter.h"

//Outline for this function @ https://docs.opencv.org/master/d7/d37/tutorial_mat_mask_operations.html
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