/*
 * I wrote this one
 */
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void display(Mat frame)
{
	imshow("Video Stream", frame);
}

int main(int argc, const char** argv)
{
	int cameraDevice = 0;
	VideoCapture capture;

	capture.open(cameraDevice);
	
	if (!capture.isOpened())
	{
		cout << "[ERROR] Cannot open video capture!\n";
		return -1;
	}

	Mat frame;
	while (capture.read(frame))
	{
		if (frame.empty())
		{
			cout << "[ERROR] Frame is empty!\n";
			break;
		}
	
		display(frame);

		if (waitKey(10) == 27)
		{
			break;
		}
	}

	return 0;
}
