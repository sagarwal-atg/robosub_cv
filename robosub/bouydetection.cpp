//
//  bouydetection.cpp
//  openLOL
//
//  Created by Shubhankar Agarwal on 6/4/16.
//  Copyright © 2016 Shubhankar Agarwal. All rights reserved.
//

#include "bouydetection.hpp"


#define PI 3.14159265


int filter_image (  Mat detect, Mat src ,  int height , int width , vector<Point2i> cent_i , int red , int green , int blue)
{

    
     
    
    int r[height ][width], g[height ][width] ,b[height][width];
    
    
    
    
    cent_i[0].x= ( floor( width/2));
    cent_i[0].y = (floor( height/2));
    
    
    cout<<"Center of the picture: "<<cent_i[0]<<endl;
    
    //  cout<<s.width<<endl;
    // cout<<s.height<<endl;
    
    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){
            
            r[row][col] = 0;
            g[col][row] = 0;
            b[col][row] = 0;
        }
    }
    
    
    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){
            
            
            
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
    
    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){
            
            
            // WORKING PRETTY GOOD (120, 80, 140)
            // 120 , 100 , 150
            if( r[row][col] > red && g[row][col] > green && b[row][col] < blue)
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

    
    
    
    return 0;
}


int filter_image_green (  Mat detect, Mat src ,  int height , int width , vector<Point2i> cent_i , int red , int green , int blue)
{
    
    
    
    
    int r[height ][width], g[height ][width] ,b[height][width];
    
    
    
    
    cent_i[0].x= ( floor( width/2));
    cent_i[0].y = (floor( height/2));
    
    
    cout<<"Center of the picture: "<<cent_i[0]<<endl;
    
    //  cout<<s.width<<endl;
    // cout<<s.height<<endl;
    
    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){
            
            r[row][col] = 0;
            g[col][row] = 0;
            b[col][row] = 0;
        }
    }
    
    
    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){
            
            
            
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
    
    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){
            
            
            // WORKING PRETTY GOOD (120, 80, 140)
            // 120 , 100 , 150
            if( r[row][col] < red && g[row][col] > green && 250 > g[row][col] && b[row][col] < blue)
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
    
    
    
    
    return 0;
}





/** @function thresh_callback */
void thresh_callback( Mat final_image , double yawO , vector<Point2i> cent_i , vector<double> area1 ,  int thresh, int max_thresh , RNG rng , int g)
{
    Mat threshold_output;
    vector<vector<Point> > contours;

    vector<Vec4i> hierarchy;
    double largest_area = 0;
    int largest_contour_index = 0;
    double ang = 0;
    
    /// Detect edges using Threshold
    threshold( final_image, threshold_output, thresh, 255, THRESH_BINARY );
    cvtColor(threshold_output, threshold_output, CV_BGR2GRAY);
    /// Find contours
    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    
    if( contours.size() > 0  )  {  /// checking if any countour is detected
    
    /// Approximate contours to polygons + get bounding rects and circles
    vector<vector<Point> > contours_poly( contours.size() );
    // vector<Rect> boundRect( contours.size() );
    vector<Point2f>center( contours.size() );
    vector<float>radius( contours.size() );
    
    for( int i = 0; i < contours.size(); i++ )
    {   approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        // boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
    }
    
 //   double b = contourArea( contours[0],false);
    
  
    
   
    
    for( int i = 0; i< contours.size(); i++ ) // iterate through each contour.
    {
        double a = contourArea( contours[i],false);  //  Find the area of contour
        if(a>largest_area){
            largest_area=a;
            largest_contour_index = i;                //Store the index of largest contour
        }
    }
    
   // minEnclosingCircle( (Mat)contours_poly[largest_contour_index], center[largest_contour_index], radius[largest_contour_index] );
    
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
        
    
    
    //////////////////////////////////////////////////////////////////////////////////
    /////////// FInding the angle ////////////////////////////////////////////////////
 
    int dist_x = center[0].x - cent_i[0].x;
    int dist_y = center[0].y - cent_i[0].y;
        
    
    
        
        
    
    cout<< " dist_x = " << dist_x << " dist_y =" << dist_y <<endl;
    
    //int ang = atan2 (dist_y,dist_x) * 180 / PI;
    
     ang = atan2 ( (dist_x) , (dist_y)) * 180 / PI;
    
  //cout<< "The target is "<< (  90  -  (ang - 90 ) ) << " degrees from x-axis"<<endl;
    
      //  if( dist_x > 0 && )
    
    
   // yawO = yawO  - (-ang);
        
        yawO =  -ang - 180   ;

    cout<< "The output yaw is "<<yawO<<endl;
    
          int area = (int)largest_area;
          
    cout<<"area = "<<area<<endl;
    cout<<endl;
    
    cout<< "frame no. = " << g << endl;
    
    area1.push_back(area);
    
    if( g > 3)
    {
        if( (area1[g-2] + area1[g-1] + area1[g])/3 > area )
            cout<<" wrong direction "<<endl;
        else
            cout<<" right direction "<<endl;
    }
    
    
    
    /////////////////////////////////////////////////////////////////////////////////////////
    
    /////////////////// putting the label //////////////////////////////////
    
    /////////////////////////////////////////////////////////////////////////////////////
    ///////  drawing the lines n the image //////////////////////////////////////////////
    
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
    ////////////////////////////////////////////////////////////////////////////////
    
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
    /// Show in a window
    namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );
      }
}

////////////////////////////////////////////////////////////////////////////////////////





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

double hue(double r, double g, double b)
{
    double r_ = r / 255;
    double g_ = g / 255;
    double b_ = b / 255;
    
    double c_max = max(max(r_, g_), b_);
    double c_min = min(min(r_, g_), b_);
    
    double delta = c_max - c_min;
    
    if (delta == 0)
        return 0;
    else if (c_max == r_)
        return 60 * ((int)((g_ - b_) / delta) % 6);
    else if (c_max == g_)
        return 60 * (((b_ - r_) / delta) + 2);
    else
        return 60 * (((r_ - g_) / delta) + 4);
}

bool isRed(double hue)
{
    return hue < 30 || hue > 345;
}

bool isYellow(double hue)
{
    return hue > 30 && hue < 75;
}

bool isGreen(double hue)
{
    return hue > 75 && hue < 135;
}