//
//  allbouy.hpp
//  openLOL
//
//  Created by Shubhankar Agarwal on 6/25/16.
//  Copyright © 2016 Shubhankar Agarwal. All rights reserved.
//

#ifndef allbouy_hpp
#define allbouy_hpp

#include <stdio.h>

#include "opencv2/imgproc/imgproc.hpp"


using namespace std;
using namespace cv;

/// Function header
vector<Point>   all_bouy( Mat detect , Mat final_image , double yawI , vector<Point2i> cent_i , vector<double> area1 ,  int thresh, int max_thresh , RNG rng , int g , vector<vector<Point> > contours , int color);
void drawcontours(Mat final_image  , vector<vector<Point> > contours , int color_bouy , vector<Point> contour_r , vector<Point> contour_g , vector<Point> contour_y );

#endif /* allbouy_hpp */
