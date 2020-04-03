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

const double pi = 3.1415926535897;              //pi for use later

////////////////////////////////////////////////////////////////
// main - initialises OpenCV and captures an image and changes it
////////////////////////////////////////////////////////////////
int main()
{
    CvCapture* capture = 0;
    IplImage* processedImage = 0;

    cout << "Group 2 Blob Statistics" << endl << "Press 'q' to quit" << endl;

    // Initializes capturing video from camera
    capture = cvCaptureFromCAM(0);
    if (!capture) {
        fprintf(stderr, "Could not initialize capturing...\n");
        return -1;
    }


    // Creates window
    cvNamedWindow("Camera image", 1);

    // Camera image
    IplImage* frame = 0;


    // Grabs and returns a frame from camera
    frame = cvQueryFrame(capture);

    // Print details of image
    cout << "image width =" << frame->width << " height =" << frame->height;
    cout << " depth =" << frame->depth << " channels =" << frame->nChannels << endl;

    int height = frame->height;
    int width = frame->width;
    int m00 = 0;                   //m00
    int m01 = 0;              //m01
    int m10 = 0;              //m10
    int centre_x = 0;
    int centre_y = 0;
    int m11 = 0;                    //m11 = m01 * m10
    int m20 = 0;
    int m02 = 0;
    double mmoi = 0;                   //minimum moment of inertia

    do {
        // Grabs and returns a frame from camera
        frame = cvQueryFrame(capture);
        if (!frame) {
            break;
        }

        //reset values here
        m00 = 0;       
        m01 = 0;  
        m10 = 0;  
        m11 = 0;
        mmoi = 0;
        
        //stepping through the pixels
        for (int y = 0; y < frame->height; y++) {
            for (int x = 0; x < frame->width; x++) {
                // This is a pointer to the start of the current row.
                //  Note: The image is stored as a 1-D array which is mapped back
                //  into 2-space by multiplying the widthStep (the image width rounded to
                //  a "nice" value, eg a multiple of 4 or 8 depending on the OS and CPU)
                //  by the row number.
                uchar* row = (uchar*)(frame->imageData + frame->widthStep * y);     //pointer to row?

                int gray = (row[x * 3] + row[x * 3 + 1] + row[x * 3 + 2]) / 3;      // converting image to rgb by adding components and dividing by 3
                
                                                                                    
                // Thresholding
                if (gray > 250) {
                    row[x * 3] = 255;      
                    row[x * 3 + 1] = 255;
                    row[x * 3 + 2] = 255;
                    
                    m00++;
                    m01 = m01 + x;
                    m10 = m10 + y;
                    m11 = m01 * m10;
                    m20 = m01 ^ 2;
                    m02 = m10 ^ 2;

                }

                else {
                    row[x * 3] = 0;
                    row[x * 3 + 1] = 0;
                    row[x * 3 + 2] = 0;
                }

            }
        }

        if (m00 != 0) {
            centre_x = m01 / m00;
            centre_y = m10 / m00;

            mmoi = 0.5 * atan((2*(m00*m11 - m10*m01)/((m00*m20-m10^2)-(m00*m02-m01^2)))) * 180 / pi;

            //Output lines
            cout << "m00 (units)= \t" << m00;
            cout << "\tCentre of m00 (x,y)= \t(" << centre_x << ", " << centre_y << ")";
            cout << "\tMinimum Moment of Inertia = \t" << mmoi << endl;
        }
        
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