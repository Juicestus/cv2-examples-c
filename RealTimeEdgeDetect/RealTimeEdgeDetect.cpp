/*
 * Realtime Videostream Canny Edge Detection
 * by Justus Languell, 2021
 */

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

#include <iostream>
#include <string>
#include <cstdlib>

//using namespace std;
//using namespace cv;

const std::string windowName = "Realtime Videostream Canny Edge Detection";

cv::Mat processCanny(cv::Mat frame, int t1, int t2)
{
	cv::Mat contours;
	cv::Mat grayImage;

	std::vector<cv::Mat> channels;
	cv::Mat hsv;
	cv::cvtColor(frame, hsv, cv::COLOR_RGB2HSV);
	cv::split(hsv, channels);
	grayImage = channels[0];

	cv::Canny(frame, contours, t1, t2);

	return contours;
}


int main(int argc, const char** argv)
{
	int t1 = atoi(argv[1]);
	int t2 = atoi(argv[2]);

    int cameraDevice = 0;

	cv::VideoCapture capture;

    capture.open(cameraDevice);

    if (!capture.isOpened())
    {
		std::cout << "[ERROR] Cannot open video capture!\n";
        return -1;
    }

	cv::Mat frame;

    while (capture.read(frame))
    {
        if (frame.empty())
        {
			std::cout << "[ERROR] Frame is empty!\n";
            break;
        }

		cv::Mat pframe = processCanny(frame, t1, t2);

		cv::imshow(windowName, pframe);

        if (cv::waitKey(10) == 27)
        {
            break;
        }
   }

    return 0;
} 
