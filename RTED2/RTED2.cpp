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

cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eyes_cascade;

const std::string face_cascade_name = cv::samples::findFile("data/haarcascades/haarcascade_frontalface_alt.xml");
const std::string eyes_cascade_name = cv::samples::findFile("data/haarcascades/haarcascade_eye_tree_eyeglasses.xml");

cv::Mat faceDetect(cv::Mat frame)
{
	cv::Mat frameGray;

	cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY );
    equalizeHist(frameGray, frameGray);

    std::vector<cv::Rect> faces;

	face_cascade.detectMultiScale(frameGray, faces);
	
    for (int i=0; i < faces.size(); i++)
    {
		int widthd = faces[i].width / 2;
		int heightd = faces[i].width / 2;

		int centerx = faces[i].x + widthd;
		int centery = faces[i].y + heightd;

		cv::Point center(centerx, centery);

		cv::ellipse( 
				frame, 
				center, 
				cv::Size(heightd, heightd), 
				0, 
				0, 
				360, 
				cv::Scalar(255, 0, 255), 
				4);

		cv::Mat faceROI = frameGray(faces[i]);

		/*
        std::vector<cv::Rect> eyes;

        eyes_cascade.detectMultiScale( faceROI, eyes );
        for ( size_t j = 0; j < eyes.size(); j++ )
        {
			cv::Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
			cv::circle( frame, eye_center, radius, cv::Scalar( 255, 0, 0 ), 4 );
        }
		*/
	}
	return frame;
}


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

	face_cascade.load(face_cascade_name);
	eyes_cascade.load(eyes_cascade_name);

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

		cv::Mat eframe = processCanny(frame, t1, t2);

		cv::imshow("Detect Edges", eframe);

		cv::Mat fframe = faceDetect(frame);

		cv::imshow("Detect Faces", fframe);



		

        if (cv::waitKey(10) == 27)
        {
            break;
        }
   }

    return 0;
} 
