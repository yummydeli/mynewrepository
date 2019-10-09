#include<opencv2/opencv.hpp>
#include<iostream>
 
using namespace std;
using namespace cv;
 
int main(int argc,char **argv)
{
	VideoCapture capture(0);//cv::videocapture cap(0)
    //cv::VideoCapture capture("test.avi");
	namedWindow("hhh");

	while(true)
	{	
		Mat frame;
		capture>>frame;
		imshow("hhh",frame);
		waitKey(30);
	}


	return 0;
}
