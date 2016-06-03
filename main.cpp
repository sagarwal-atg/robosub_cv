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

#define PI 3.14159265

using namespace std;
using namespace cv;




/// Global variables
Mat src, detect , final_image;
vector<Point2i> cent_i(1);

double area1[1000];

int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void*, int g );
void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour);
void MyLine( Mat img, Point start, Point end );

int main( int argc, char** argv )

{
    
   
    
    cout<<"Time at starting is 0 sec"<<endl;
    
    string filename = "/Users/Somi/Desktop/_Recordings_/Bouy_Ramming.mp4";
    VideoCapture capture(filename);
    Mat frame;
    
    if( !capture.isOpened() )
        cout<< "Error when reading steam_avi"<<endl;
    
    int framecounter = 0;
    
 
    for( ; ; )
    {
        struct timeval tv0,tv1;
        gettimeofday(&tv0 , 0);
        
        capture >> src;
        capture >> detect;
        if(src.empty())
            break;
   //  imshow("w", src);
        waitKey(20); // waits to display frame
    
    
//    
//    char imageName[48];
//    //char imageDest[57];
//    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
//
//    int i = 0;
//    
//    //while(1){
//        cout<<"again"<<endl;
//        sprintf(imageName,"/Users/Somi/Desktop/_Recordings_/Front/Image299.png",i);
//        
//        src= imread(imageName,1);
//    detect = imread(imageName,1);
//       // double j =0;
//     //   while ( j < 1000000) {
//        //    j++;
//        //}
//       
//        if(!src.data ){
//            cout<<"NO image found!"<<endl;
//            return 0;
//      //      break;
//        }
//    
//        //sprintf(imageDest,"/Users/Somi/Desktop/_Recordings_/convertimage/image_g%d.png",i);
//        //imwrite(imageDest, gray);
//    
//       cout<<imageName<<endl;
//    
//    
//    
/////////////////////////////////////////////////////////////////////////
      Size s = src.size();
    

    int r[s.height ][s.width], g[s.height ][s.width] ,b[s.height][s.width];
        
        
        
        
        cent_i[0].x= ( floor( s.width/2));
        cent_i[0].y = (floor( s.height/2));
        
        
        cout<<"Center of the picture: "<<cent_i[0]<<endl;
   
      //  cout<<s.width<<endl;
      // cout<<s.height<<endl;
    
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
    
   // cout<<"copy done"<<endl;
    
  //  double alpha = 1.0;
  //  int beta = 1;
    
   // Mat detect(s.height,s.width, CV_8UC3,Scalar(0,255,255));

    for(int col = 0; col < s.width ; col++){
        for(int row = 0; row < s.height ; row++){
        
            
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
    }
}
        gettimeofday(&tv1,0);
        long elap = (tv1.tv_sec - tv0.tv_sec ) * 100000  + tv1.tv_usec - tv0.tv_usec;
        
        cout<<"Time after initial thresholding : " << elap/1000.0f <<"millisec"<<endl;
        
      //  imshow( "Display window", detect );
         fastNlMeansDenoising(detect,final_image , 100, 3, 31);

  
        thresh_callback( 0, 0 , framecounter);
 
        waitKey(1);
 
        framecounter++;
        
             //  cout<<"Time after denoising and finding the target:"<<"sec"<<endl;
    
        
    }
       waitKey();
    
       return 0;
}

////////////////////////////////////////////////////////////////////////////


/** @function thresh_callback */
void thresh_callback(int, void* , int g)
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
   // vector<Rect> boundRect( contours.size() );
    vector<Point2f>center( contours.size() );
    vector<float>radius( contours.size() );
    
    for( int i = 0; i < contours.size(); i++ )
    { approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
       // boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
    }
    

    
    /// Draw polygonal contour + bonding rects + circles
    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       // drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
       //rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
        circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
        setLabel(drawing, "Target", contours[0]);    // Triangles
        
        
    }
    
    vector<Point2i> cent_k(1);
    vector<Point2i> cent_j(1);
    
    cent_k[0] = cent_i[0];
    cent_k[0].x = cent_i[0].x - 20;
    
    cent_j[0] = cent_i[0];
    cent_j[0].x = cent_i[0].x + 20;
    
    
       // Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        circle( drawing , cent_i[0] ,  5 , Scalar( 72, 209, 51 ) , 2, 8 , 0);
     //circle( drawing , cent_i[0] ,  2*5 , Scalar( 72, 209, 51 ) , 2, 8 , 0);
     //circle( drawing , cent_i[0] ,  4*5 , Scalar( 72, 209, 51 ) , 2, 8 , 0);
       MyLine(drawing , (cent_k[0] ), (cent_j[0]));
    
    cent_k[0] = cent_i[0];
    cent_k[0].y = cent_i[0].y - 20;
    
    cent_j[0] = cent_i[0];
    cent_j[0].y = cent_i[0].y + 20;
    
     MyLine(drawing , (cent_k[0] ), (cent_j[0]));
    
    int dist_x = center[0].x - cent_i[0].x;
    int dist_y = center[0].y - cent_i[0].y;
    
    
    cout<< " dist_x = " << dist_x << " dist_y =" << dist_y <<endl;
    
    int ang = atan2 (dist_y,dist_x) * 180 / PI;
    
    cout<< "The target is "<< -ang << " degrees from x-axis"<<endl;

   // string x = -ang;
    std::vector<cv::Point> c_print;
    
    Point temp;
    
    temp.x = 10;
    temp.y = 10;
    c_print.push_back(temp);
    
    temp.x = 100;
    temp.y = 10;
    c_print.push_back(temp);
    
    temp.x = 10;
    temp.y = 20;
    c_print.push_back(temp);
    temp.x = 100;
    temp.y = 20;
    c_print.push_back(temp);
    

    setLabel(drawing, "Property of Somi" , c_print);
    
    stringstream ang_s;
    ang_s<< -ang;
    string ang_s1 = ang_s.str();
    string s = "The angle of the target from x-axis is " + ang_s1;
    
    temp.x = 10;
    temp.y = 30;
    c_print.push_back(temp);
    
    temp.x = 100;
    temp.y = 30;
    c_print.push_back(temp);
    
    temp.x = 10;
    temp.y = 40;
    c_print.push_back(temp);
    temp.x = 100;
    temp.y = 40;
    c_print.push_back(temp);
    
    setLabel(drawing, s , c_print);
        
        
    
    int area = 0;
    
   
   for( int i = 0; i< contours.size(); i++ )
       area =  area + contourArea(contours[i]);
    cout<<"area = "<<area<<endl;
    cout<<endl;
    
    cout<< "frame no. = " << g << endl;
    
    area1[g+1] = area;
    
    
    
    
    if( g > 3)
    {
    if( (area1[g-2] + area1[g-1] + area1[g])/3 > area )
        cout<<" wrong direction "<<endl;
    else
        cout<<" right direction "<<endl;
    }
    
    
    /// Show in a window
   namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
 //  imshow( "Contours", drawing );
   
}



void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour)
{
    int fontface = cv::FONT_HERSHEY_SIMPLEX;
    double scale = 0.4;
    int thickness = 1;
    int baseline = 0;
    
    
    cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
    cv::Rect r = cv::boundingRect(contour);
    
    cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
    cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(0,0,0), CV_FILLED);
    cv::putText(im, label, pt, fontface, scale, CV_RGB(0, 100, 255), thickness, 8);
}


void MyLine( Mat img, Point start, Point end )
{
    int thickness = 2;
    int lineType = 8;
    line( img,
         start,
         end,
         Scalar( 72, 209, 51 ),
         thickness,
         lineType );
}


