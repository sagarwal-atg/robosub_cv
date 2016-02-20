#include <iostream>
#include <stdio.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

int main( int argc, char** argv )

{
    char imageName[48];
   // char imageDest[57];
    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.

    int i = 0;
    
    //while(1){
        cout<<"again"<<endl;
        sprintf(imageName,"/Users/Somi/Desktop/_Recordings_/Front/Image299.png",i);
        Mat src= imread(imageName,1);
       // double j =0;
     //   while ( j < 1000000) {
        //    j++;
        //}
       
        if(!src.data ){
            cout<<"NO image found!"<<endl;
            return 0;
      //      break;
        }
    
        //cvtColor(src,gray,CV_BGR2GRAY);
        //sprintf(imageDest,"/Users/Somi/Desktop/_Recordings_/convertimage/image_g%d.png",i);
        //imwrite(imageDest, gray);
    
     // imshow( "Display window", src );
       cout<<imageName<<endl;
    
    
    
    
//    Mat M(720,1080, CV_8UC3, Scalar(0,255,255));
//    //cout << "M = " << endl << " " << M << endl << endl;
//    

    
    
    
    imshow("src window" , src);
    
    
    
    
    
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
    
    double alpha = 1.0;
    int beta = 1;
    
    Mat detect(s.height,s.width, CV_8UC3,Scalar(0,255,255));

    for(int col = 0; col < s.width ; col++){
        for(int row = 0; row < s.height ; row++){
        
        
    
        detect.template at<Vec3b>(row, col)[0] = saturate_cast<uchar>( alpha*( b[row][col] ) + beta );
        detect.template at<Vec3b>(row, col)[1] = saturate_cast<uchar>( alpha*( b[row][col] ) + beta );
        detect.template at<Vec3b>(row, col)[2] = r[row][col];
        
        //cout<<"row"<<row<<endl;
        //cout<<"col"<<col<<endl;
    
    }
}
    imshow( "Display window", detect );
    
     Mat gray(s.height,s.width, CV_8UC3,Scalar(0,255,255));
    
    
    
        //i++;
    waitKey();
        
   // }
    
    return 0;
}

