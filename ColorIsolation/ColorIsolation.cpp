/**
 * OpenCV Program to detect and identify the positions
 * of <color> objects.
 * 
 */

#include <iostream>
#include <string>
#include <cstdlib>

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

const std::string REAL_WINDOW = "[REAL]";
const std::string THRESHOLD_WINDOW = "[THRESHOLD]";

int main(int argc, char **argv) {
    int cameraDevice = 0;
	cv::VideoCapture capture;
    capture.open(cameraDevice);
    if (!capture.isOpened()) 
        std::printf("[ERROR] Cannot open video capture!\n");

    cv::Mat frame, frameHSV, frameThreshold, ellipse;
    cv::Scalar lowerBound, upperBound;

    ellipse = getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));

    while (capture.read(frame)) {
        if (frame.empty()) {
            printf("[ERROR] Frame is empty!\n");
            break;
        }

        cv::cvtColor(frame, frameHSV, cv::COLOR_BGR2HSV);

        lowerBound = cv::Scalar(20, 100, 100);
        upperBound = cv::Scalar(40, 255, 255);


        cv::inRange(frameHSV, lowerBound, upperBound, frameThreshold);

        cv::erode(frameThreshold, frameThreshold, ellipse);
        cv::dilate(frameThreshold, frameThreshold,ellipse);

        cv::dilate(frameThreshold, frameThreshold, ellipse);
        cv::erode(frameThreshold, frameThreshold, ellipse);

        cv::imshow("[REAL]", frame);
        cv::imshow("[THRESHOLD]", frameThreshold);

        if (cv::waitKey(10) == 27) break;
    }

    return 0;
}





