//
//  pathmarker.cpp
//  openLOL
//
//  Created by Shubhankar Agarwal on 6/20/16.
//  Copyright © 2016 Shubhankar Agarwal. All rights reserved.
//

#include "pathmarker.hpp"
#include "bouydetection.hpp"

void path_marker( Mat final_image , double yawI , vector<Point2i> cent_i , vector<double> area1 ,  int thresh, int max_thresh , RNG rng , int g)
{
    
    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    double l_area = 0;
    int l_c_i = 0;
    double ang = 0;
    
    /// Detect edges using Threshold
    threshold( final_image, threshold_output, thresh, 255, THRESH_BINARY );
    cvtColor(threshold_output, threshold_output, CV_BGR2GRAY);
    /// Find contours
    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    
    if( contours.size() > 0  )  {  /// checking if any countour is detected
        
        /// Approximate contours to polygons + get bounding rects and circles
        vector<vector<Point> > contours_poly( contours.size() );
         vector<Rect> boundRect( contours.size() );
        
        for( int i = 0; i < contours.size(); i++ )
        {   approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
          //  minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
        }
        
        //   double b = contourArea( contours[0],false);
        
        
        
        
        
        for( int i = 0; i< contours.size(); i++ ) // iterate through each contour.
        {
            double a = contourArea( contours_poly[i],false);  //  Find the area of contour
            if(a>l_area){
                l_area=a;
                l_c_i = i;                //Store the index of largest contour
            }
        }
        
        // minEnclosingCircle( (Mat)contours_poly[largest_contour_index], center[largest_contour_index], radius[largest_contour_index] );
        
        /// Draw  bonding rects
        Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
        
        
    
            Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
           
            rectangle( drawing, boundRect[l_c_i].tl(), boundRect[l_c_i].br(), color, 2, 8, 0 );
           
            setLabel(drawing, "Target", contours[0]);
            
  
        
        /////////////////////////////////////////////////////////////////////////////////////////
        
        /////////////////// putting the label //////////////////////////////////
        
        /////////////////////////////////////////////////////////////////////////////////////
        ///////  drawing the lines n the image //////////////////////////////////////////////
        
        
        int rec_top_w =  boundRect[l_c_i].tl().x + ( boundRect[l_c_i].br().x - boundRect[l_c_i].tl().x ) /2 ;
     //   int rec_bot_w = rec_top_w + (boundRect[l_c_i].br().y - boundRect[l_c_i].tl().y);
        
        {   std::vector<cv::Point> c_print;
            Point temp;
            
            temp.x = rec_top_w;
            temp.y = boundRect[l_c_i].tl().y;
            c_print.push_back(temp);
            
            temp.x = rec_top_w;
            temp.y = boundRect[l_c_i].br().y;
            c_print.push_back(temp);
            
            MyLine(drawing , (c_print[0] ), (c_print[1]));
            
            
            
            

        
        }
     //   cout << boundRect[l_c_i].br() << boundRect[l_c_i].tl() << endl;
     //   cout << boundRect[l_c_i]<< endl;

        
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