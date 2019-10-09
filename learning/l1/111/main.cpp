
//#include "iostream"

//using namespace std;

//int main()
//{
 //   cout<<100<<endl;

 //   return 0;
//}
//test.cpp源文件
#include<opencv2/opencv.hpp>
#include<iostream>
 
using namespace std;
using namespace cv;
 
int main(int argc,char **argv)
{
	VideoCapture capture(0);
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
