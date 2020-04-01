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

using namespace std;
using namespace cv;
/*
////////////////////////////////////////////////////////////////
// main - initialises OpenCV and captures an image and changes it
////////////////////////////////////////////////////////////////
int main()
{

    CvCapture* capture = 0;
    IplImage* processedImage = 0;

    cout << "Andy's USB camera program" << endl << "Press 'q' to quit" << endl;

    // Initializes capturing video from camera
    capture = cvCaptureFromCAM(0);
    if (!capture) {
        fprintf(stderr, "Could not initialize capturing...\n");
        return -1;
    }


    // Creates window
    namedWindow("Camera image", 1);

    // Camera image
    IplImage* frame = 0;

    // Grabs and returns a frame from camera
    frame = cvQueryFrame(capture);

    // Print details of image
    cout << "image width =" << frame->width << " height =" << frame->height;
    cout << " depth =" << frame->depth << " channels =" << frame->nChannels << endl;

    do {
        // Grabs and returns a frame from camera
        frame = cvQueryFrame(capture);
        if (!frame) {
            break;
        }

        //// Convert half of the image to gray
        //for (int y = 0; y < frame->height / 2; y++) {
        //    for (int x = 0; x < frame->width; x++) {
        //        // This is a pointer to the start of the current row.
        //        //  Note: The image is stored as a 1-D array which is mapped back
        //        //  into 2-space by multiplying the widthStep (the image width rounded to
        //        //  a "nice" value, eg a multiple of 4 or 8 depending on the OS and CPU)
        //        //  by the row number.
        //        uchar* row = (uchar*)(frame->imageData + frame->widthStep * y);

        //        int gray = (row[x * 3] + row[x * 3 + 1] + row[x * 3 + 2]) / 3;

        //        row[x * 3] = gray;
        //        row[x * 3 + 1] = gray;
        //        row[x * 3 + 2] = gray;
        //    }
        //}


        // Shows the resulting image in the window
        cvShowImage("Camera image", frame);

    } while ('q' != cvWaitKey(10));

    //tidy up

    // Releases the CvCapture structure
    cvReleaseCapture(&capture);
    // Destroys all the HighGUI windows
    cvDestroyAllWindows();

    return 0;

} //end of main 


*/
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

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
        //flip(frame, frame, 0);
        cvtColor(frame, video, COLOR_RGB2HSV);				//convert to hsv
        GaussianBlur(video, video, Size(7, 7), 1.5, 1.5);		//smooth out the image

        
        inRange(video, Scalar(50, 50, 50), Scalar(80, 230, 230), video);  //adjust for green colour of cone
        /*
        morphologyEx(video, video, MORPH_OPEN, 11);			//adjust morph technique for best results	

        Moments m = moments(video, true);					//find centroid of cone
        Point p(m.m10 / m.m00, m.m01 / m.m00);

        circle(video, p, 5, Scalar(128, 0, 0), -1);
        */
        imshow("video", video);
        if((char)waitKey(10) == 27) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
