
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace cv;

cv::Mat frame, frameHSV, frameThreshold, ellipse;
cv::Scalar lowerBound, upperBound;

const char* window_name = "Edge Map";

static void colorIsolation(int, void*)
{
    blur( src_gray, detected_edges, Size(3,3) );
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
    dst = Scalar::all(0);
    src.copyTo( dst, detected_edges);
    imshow( window_name, dst );
}

int main( int argc, char** argv )
{
    ellipse = getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));

  namedWindow( window_name, WINDOW_AUTOSIZE );
  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, colorIsolation );

    cv::createTrackbar("[Hue] Lower bound", "Control", &lowerBoundHue, upperBoundHue);
    cv::createTrackbar("[Hue] Upper bound", "Control", &upperBoundHue, upperBoundHue);
    cv::createTrackbar("[Saturation] Lower bound", "Control", &lowerBoundHue, upperBoundHue);
    cv::createTrackbar("[Saturation] Upper bound", "Control", &upperBoundHue, upperBoundHue);
    cv::createTrackbar("[Value] Lower bound", "Control", &lowerBoundHue, upperBoundHue);
    cv::createTrackbar("[Value] Upper bound", "Control", &upperBoundHue, upperBoundHue);

  CannyThreshold(0, 0);
  waitKey(0);
  return 0;
}
