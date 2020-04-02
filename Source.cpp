#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <stdio.h>
#include "opencv2/opencv.hpp"

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
    
    cout << "Group 2 Blob Statistics" << endl;

    Mat video;
    namedWindow("video", 1);
    for (;;)
    {
        Mat frame;
        //vector<Vec4i> hierarchy;
        cap >> frame; // get a new frame from camera
        flip(frame, frame, 1);
        cvtColor(frame, video, COLOR_BGR2HSV);				//convert to hsv (opencv stores image in bgr not rgb)
        GaussianBlur(video, video, Size(7, 7), 1.5, 1.5);		//smooth out the image, might be unnecessary becasue webcam quality is ok

        //Mat video1, video2;
        inRange(video, Scalar(80, 90, 90), Scalar(100, 240, 240), video);  //adjusted for blue

        // These lines are needed if looking for red colour as the 'H' value wraps around
        //inRange(video, Scalar(170, 150, 150), Scalar(180, 230, 230), video2);  //adjust for...
        //Mat video = video1 | video2;
        
            //Clean up image
            //erode(video, video, 3);
            //dilate(video, video, 3);
            morphologyEx(video, video, MORPH_OPEN, 11);			//adjust morph technique for best results	
            morphologyEx(video, video, MORPH_CLOSE, 11);			//adjust morph technique for best results	
             
        Canny(video, video, 300, 3);        
        //findContours(video, video, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

        //Finding Centroid
        Moments m = moments(video, true);					
        Point p(m.m10 / m.m00, m.m01 / m.m00);
        drawMarker(video, p, Scalar(128, 0, 0), MARKER_CROSS, 20, 1, 8);


 
        cout << "Centroid (x,y) = \t(" << m.m10 / m.m00 << ", " << m.m01 / m.m00 << ")" << endl;
        imshow("video", video);
        if (waitKey(16) >= 0) {
            //cout << "inside waitkey" << endl;     //for debugging purposes
            break;
        }
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
