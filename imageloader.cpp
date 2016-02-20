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
    Mat gray;
    while(1){
        cout<<"again"<<endl;
        sprintf(imageName,"/Users/Somi/Desktop/_Recordings_/Front/Image%d.png",i);
        Mat src= imread(imageName,1);
        double j =0;
        while ( j < 1000000) {
            j++;
        }

        if(!src.data ){
            cout<<"NO image found!"<<endl;
            return 0;
            break;
        }

        //cvtColor(src,gray,CV_BGR2GRAY);
        //sprintf(imageDest,"/Users/Somi/Desktop/_Recordings_/convertimage/image_g%d.png",i);
        //imwrite(imageDest, gray);

      imshow( "Display window", src );
       cout<<imageName<<endl;
       //cout<<imageName<<endl;

       // cout<<i<<endl;
        i++;
     waitKey(200);

    }

    return 0;
}
