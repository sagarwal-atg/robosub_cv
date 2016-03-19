#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/photo/photo.hpp"

using namespace std;
using namespace cv;




/// Global variables
Mat src, detect , final_image;

int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void* );
void Erosion( int, void* );
void Dilation( int, void* );

int main( int argc, char** argv )

{
    char imageName[48];
    //char imageDest[57];
    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.

    int i = 0;
    
    //while(1){
        cout<<"again"<<endl;
        sprintf(imageName,"/Users/Somi/Desktop/_Recordings_/Front/Image297.png",i);
        
        src= imread(imageName,1);
    detect = imread(imageName,1);
       // double j =0;
     //   while ( j < 1000000) {
        //    j++;
        //}
       
        if(!src.data ){
            cout<<"NO image found!"<<endl;
            return 0;
      //      break;
        }
    
        //sprintf(imageDest,"/Users/Somi/Desktop/_Recordings_/convertimage/image_g%d.png",i);
        //imwrite(imageDest, gray);
    
       cout<<imageName<<endl;
    
    
    
/////////////////////////////////////////////////////////////////////////
      Size s = src.size();
    

    int r[s.height ][s.width], g[s.height ][s.width] ,b[s.height][s.width];
    
    cout<<s.width<<endl;
    cout<<s.height<<endl;
    
    for(int col = 0; col < s.width ; col++){
        for(int row = 0; row < s.height ; row++){
            
            r[row][col] = 0;
            g[col][row] = 0;
            b[col][row] = 0;
        }
    }
    
    
    for(int col = 0; col < s.width ; col++){
        for(int row = 0; row < s.height ; row++){
            
            
            
            b[row][col] = src.template at<Vec3b>(row,col)[0];
            g[row][col] = src.template at<Vec3b>(row,col)[1];
            r[row][col] = src.template at<Vec3b>(row,col)[2];
            
            
            
            
           // cout<<g[row][col]<<endl;
        }
    }
    
    cout<<"copy done"<<endl;
    
  //  double alpha = 1.0;
  //  int beta = 1;
    
   // Mat detect(s.height,s.width, CV_8UC3,Scalar(0,255,255));

    for(int col = 0; col < s.width ; col++){
        for(int row = 0; row < s.height ; row++){
        
      ///////////////////////////////////////////////////
      // converts into decent grayscale image
        //detect.template at<Vec3b>(row, col)[0] = saturate_cast<uchar>( alpha*( b[row][col] ) + beta );
        //detect.template at<Vec3b>(row, col)[1] = saturate_cast<uchar>( alpha*( b[row][col] ) + beta );
        //detect.template at<Vec3b>(row, col)[2] = r[row][col];
      /////////////////////////////////////////////////////////////
            
       
            /////////////////////////////////////////////////////////////////////////////
        // brightness coming from the sun makes it hard to detect the balloon, since brightness also
            
            // WORKING PRETTY GOOD (120, 80, 140)
            if( r[row][col] > 120 && g[row][col] > 100 && b[row][col] < 130)
            {
            
                detect.template at<Vec3b>(row, col)[0] = 255;
                detect.template at<Vec3b>(row, col)[1] = 255;
                detect.template at<Vec3b>(row, col)[2] = 255;
            }
            else
            {
                detect.template at<Vec3b>(row, col)[0] = 0;
                detect.template at<Vec3b>(row, col)[1] = 0;
                detect.template at<Vec3b>(row, col)[2] = 0;
                
            
            }
            
            
            
            
            ////////////////////////////////////////
            // converting to grayscale is also an option
       
    
    }
}
    imshow( "Display window", detect );
    

    
  //  cout << "Detect = " << endl << " " << detect << endl << endl;
    cout<<"conversion done"<<endl;
  
///////////////////////////////////////////////////////////////////
    
    
    
//    for(int col = 5; col < s.width - 5; col++){
//        for(int row = 5; row < s.height - 5 ; row++){
//            
//            if( detect.template at<Vec3b>(row, col)[2]   != 0)
//            {
//                int r = row , c = col;
//                int sum = 0;
//                int sum_r[]
//                
//                for(int j = r -5; j < (c+5) ; row++){
//                   for( int i = c -5; i < (c+5) ; col++){
//                    
//                        
//                        sum = sum + detect.template at<Vec3b>(i, j )[2];
//                    }
//                    sum_r = sum
//                }
//
//            }
//            
//            
//        }
//    }
    
/////////////////////////////////////////////////////////////////////

    
    /// Create Window

    
      cout<<"threshold window created"<<endl;
    
    fastNlMeansDenoising(detect,final_image , 100, 3, 31);

    createTrackbar( " Threshold:", "Source", &thresh, max_thresh, thresh_callback );
    thresh_callback( 0, 0 );
 
    waitKey();
        
 
    
    return 0;
}

////////////////////////////////////////////////////////////////////////////


/** @function thresh_callback */
void thresh_callback(int, void* )
{
    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    /// Detect edges using Threshold
    threshold( final_image, threshold_output, thresh, 255, THRESH_BINARY );
    cvtColor(threshold_output, threshold_output, CV_BGR2GRAY);
    /// Find contours
   findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    
    /// Approximate contours to polygons + get bounding rects and circles
    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );
    vector<Point2f>center( contours.size() );
    vector<float>radius( contours.size() );
    
    for( int i = 0; i < contours.size(); i++ )
    { approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
    }
    
    
    /// Draw polygonal contour + bonding rects + circles
    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        //drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
       // rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
        circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
    }
    
    /// Show in a window
    namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );
}


