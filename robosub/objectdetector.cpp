//
//  objectdetector.cpp
//  openLOL
//
//  Created by Shubhankar Agarwal on 2/21/16.
//  Copyright © 2016 Shubhankar Agarwal. All rights reserved.
//

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/// Global variables
Mat src, src_gray;

int maxCorners = 23;
int maxTrackbar = 100;

RNG rng(12345);
char* source_window = "Image";

/// Function header
void goodFeaturesToTrack_Demo( int, void* );

/**
 * @function main
 */
int main( int argc, char** argv )
{
    int i =0;
    char imageName[48];
    /// Load source image and convert it to gray
    sprintf(imageName,"/Users/Somi/Desktop/_Recordings_/convertimage/image_g0.png",i);
    src= imread(imageName,1);
    cvtColor( src, src_gray, CV_BGR2GRAY );
    
    /// Create Window
    namedWindow( source_window, CV_WINDOW_AUTOSIZE );
    
    /// Create Trackbar to set the number of corners
    createTrackbar( "Max  corners:", source_window, &maxCorners, maxTrackbar, goodFeaturesToTrack_Demo );
    
    imshow( source_window, src );
    
    goodFeaturesToTrack_Demo( 0, 0 );
    
    waitKey(0);
    return(0);
}

/**
 * @function goodFeaturesToTrack_Demo.cpp
 * @brief Apply Shi-Tomasi corner detector
 */
void goodFeaturesToTrack_Demo( int, void* )
{
    if( maxCorners < 1 ) { maxCorners = 1; }
    
    /// Parameters for Shi-Tomasi algorithm
    vector<Point2f> corners;
    double qualityLevel = 0.01;
    double minDistance = 10;
    int blockSize = 3;
    bool useHarrisDetector = false;
    double k = 0.04;
    
    /// Copy the source image
    Mat copy;
    copy = src.clone();
    
    /// Apply corner detection
    goodFeaturesToTrack( src_gray,
                        corners,
                        maxCorners,
                        qualityLevel,
                        minDistance,
                        Mat(),
                        blockSize,
                        useHarrisDetector,
                        k );
    
    
    /// Draw corners detected
    cout<<"** Number of corners detected: "<<corners.size()<<endl;
    int r = 4;
    for( int i = 0; i < corners.size(); i++ )
    { circle( copy, corners[i], r, Scalar(rng.uniform(0,255), rng.uniform(0,255),
                                          rng.uniform(0,255)), -1, 8, 0 ); }
    
    /// Show what you got
    namedWindow( source_window, CV_WINDOW_AUTOSIZE );
    imshow( source_window, copy );
}


