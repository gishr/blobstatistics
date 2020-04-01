////////////////////////////////////////////////////////////////
// Skeleton program for TRC3500
// Grabs images from a USB camera using OpenCV
// Written by Andy Russell 09th February 2006
// Modified by Michael Curtis 2011-2012 - updated for newer OpenCV
/////////////////////////////////////////////////////////////////

#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <stdio.h>
//#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if (!cap.isOpened())  // check if we succeeded
    {
        cout << "camera failed" << endl;
        return -1;
    }


    Mat video;
    namedWindow("video", 1);
    for (;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        flip(frame, frame, 1);
        cvtColor(frame, video, COLOR_RGB2GRAY);				//convert to hsv
        GaussianBlur(video, video, Size(7, 7), 1.5, 1.5);		//smooth out the image, might be unnecessary becasue webcam quality is ok
        threshold(video, video, 150, 250, THRESH_BINARY);

        //Mat video1, video2;
        //inRange(video, Scalar(30, 100, 100), Scalar(60, 180, 150), video);  //adjusted for green woolie's bag in dark bedroom with lamp

        // These lines are needed if looking for red colour as the 'H' value wraps around
        //inRange(video, Scalar(170, 70, 50), Scalar(180, 255, 255), video2);  //adjust for...
        //Mat video = video1 | video2;
        
        //morphologyEx(video, video, MORPH_OPEN, 11);			//adjust morph technique for best results
        //morphologyEx(video, video, MORPH_CLOSE, 11);
        //
        //Moments m = moments(video, true);					//find centroid of cone
        //Point p(m.m10 / m.m00, m.m01 / m.m00);
        //cout << "Moments = " << m.m10 << endl;

        //circle(video, p, 5, Scalar(128, 0, 0), -1);
        //
        imshow("video", video);
        if (waitKey(16) >= 0) {
            cout << "inside waitkey" << endl;
            break;
        }
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
