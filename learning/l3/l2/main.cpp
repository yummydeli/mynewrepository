#include<opencv2/opencv.hpp>
#include<iostream>
 
using namespace std;
using namespace cv;
 
int main(int argc,char **argv)
{
	/*VideoCapture capture(0);//cv::videocapture cap(0)
	//namedWindow("hhh");
	while(true)
	{	
		Mat frame;
		capture>>frame;
		imshow("hhh",frame);
		waitKey(30);
	}*/


	cv::VideoCapture capture("/home/ming/test.avi");

        /*
            if(!capture.isOpened())
            {
                cout<<"no"<<endl;
                return -1;
            }
        */
    //bool bStatus = true;

    cv::Mat frame;
    while(1)
    {
        capture >> frame;
        if(frame.empty())
            break;
        cv::imshow("video",frame);

        char c=(char)waitKey(25);
        if(c==27)
            break;
    }
    capture.release();
    // Closes all the frames
    destroyAllWindows();
	return 0;


   /*
    Mat image = imread("/home/ming/test.jpg");
    imshow("123",image);
    waitKey(0);
    return 0;
*/
}
