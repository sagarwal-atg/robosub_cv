//
//  pathmarker.hpp
//  openLOL
//
//  Created by Shubhankar Agarwal on 6/20/16.
//  Copyright © 2016 Shubhankar Agarwal. All rights reserved.
//

#ifndef pathmarker_hpp
#define pathmarker_hpp

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
void path_marker( Mat final_image , double yawI , vector<Point2i> cent_i , vector<double> area1 ,  int thresh, int max_thresh , RNG rng , int g);
//void drawinglogistics();


#endif /* pathmarker_hpp */