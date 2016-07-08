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
#include "bouydetection.hpp"
#include "pathmarker.hpp"
#include "allbouy.hpp"


using namespace std;
using namespace cv;

double yawI = 0;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);


/// Global variables
Mat src, detect_r , detect_g , detect_y ; //, final_image;
vector<Point2i> cent_i(1);
vector<double> area1;


int main( int argc, char** argv )

{
    
    //Bouy_Ramming
    //underwatertest
    //Front/Image651.png
    cout<<"Time at starting is 0 sec"<<endl;
    
    string filename = "/Users/Somi/Desktop/_Recordings_/Front/Image651.png";
    
    src = imread(filename);
    
    
    if(! src.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    struct timeval tv0,tv1;
    gettimeofday(&tv0 , 0);
    

    
    detect_r = src.clone();
    detect_g = src.clone();
    detect_y = src.clone();
    
    imshow("w", src);
    
    Size s = src.size();
    
    
    
    vector<vector<Point> > contours;
    
    
    gettimeofday(&tv1,0);
    long elap = (tv1.tv_sec - tv0.tv_sec ) * 100000  + tv1.tv_usec - tv0.tv_usec;
    
    cout<<"Time after initial thresholding : " << elap/1000.0f <<"millisec"<<endl;
    
    // red 150 , 100 , 150
    // green <  140 , 160 , 160
    
    int framecounter = 0 ;
    
    Mat final_image = Mat::zeros( src.size(), CV_8UC3 );

    
 //   imshow("detect_r", detect_r);
    /////////////////////////////////////////////////////////////////////////////////////////////
    int color_bouy = filter_image(detect_r ,src, s.height, s.width, cent_i , 150  , 100 , 150 );
    
    fastNlMeansDenoising(detect_r , detect_r , 100, 3, 31);
    imshow( "Display red", detect_r );

    
   vector<Point> red_vec = all_bouy(detect_r , final_image,   yawI ,  cent_i , area1 ,  thresh , max_thresh , rng ,  framecounter   , contours , 0);
    cout<<"red completed"<<endl;
    imshow( "after red completed" , final_image);
    
    /////////////////////////////////////////////////////////////////////////////////////////////
 //    imshow("detect_g", detect_g);
        int color_bouy2 = filter_image_green(detect_g ,src, s.height, s.width, cent_i , 140  , 150 , 150 );
    
        fastNlMeansDenoising(detect_g,detect_g , 100, 3, 31);
        imshow( "Display green", detect_g );
    
    vector<Point> green_vec = all_bouy(detect_g ,final_image,  yawI ,  cent_i , area1 ,  thresh , max_thresh , rng ,  framecounter   , contours , 1);
    cout<<"green completed"<<endl;
    imshow( "after green completed" , final_image);


    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
//     imshow("detect_y", detect_y);
        int color_bouy3 = filter_image(detect_y ,src, s.height, s.width, cent_i , 150  , 180 , 150 );
    

    
        fastNlMeansDenoising(detect_y,detect_y , 100, 3, 31);
       imshow( "Display yellow", detect_y );
    
    vector<Point> yellow_vec = all_bouy(detect_y , final_image,   yawI ,  cent_i , area1 ,  thresh , max_thresh , rng ,  framecounter   , contours , 2);
    cout<<"yellow completed"<<endl;
    imshow( "after yellow completed" , final_image);
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    
    for (int k = 0; k < contours.size(); k++) {
        cout<<"contour everything:" << contours[k]<<endl;
    }
 //   drawcontours( final_image  , contours ,  color_bouy , red_vec , green_vec , yellow_vec );
    
   //   waitKey();
    
//imshow( "after denoising" , final_image);
    
    waitKey();
    
}



