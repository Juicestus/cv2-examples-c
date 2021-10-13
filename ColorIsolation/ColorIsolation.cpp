// (c) Justus Languell, 2021
// but much later

#include <iostream>
#include <string>
#include <cstdlib>

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

const std::string windowName = "Realtime Videostream Canny Edge Detection";

int main(int argc, char **argv) {
    int cameraDevice = 0;
	cv::VideoCapture capture;
    capture.open(cameraDevice);
    if (!capture.isOpened()) 
        std::printf("[ERROR] Cannot open video capture!\n");
    
    cv::Mat frame;
    while (capture.read(frame)) {
        if (frame.empty()) {
            printf("[ERROR] Frame is empty!\n");
            break;
        }

        // Process
        
        cv::imshow(windowName, frame);
        if (cv::waitKey(10) == 27) break;
    }
}





