//
//  bouydetection.hpp
//  openLOL
//
//  Created by Shubhankar Agarwal on 6/4/16.
//  Copyright © 2016 Shubhankar Agarwal. All rights reserved.
//

#ifndef bouydetection_hpp
#define bouydetection_hpp

#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <sys/time.h>
#include <math.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/photo/photo.hpp"

using namespace std;
using namespace cv;

/// Function header
void thresh_callback( Mat final_image , double yawO , vector<Point2i> cent_i , vector<double> area1 ,  int thresh, int max_thresh , RNG rng , int g);
void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour );
int filter_image (  Mat detect, Mat src ,  int height , int width , vector<Point2i> cent_i , int red , int green , int blue);
int filter_image_green (  Mat detect, Mat src ,  int height , int width , vector<Point2i> cent_i , int red , int green , int blue);

void MyLine( Mat img, Point start, Point end );
//void drawinglogistics();


#endif /* bouydetection_hpp */
