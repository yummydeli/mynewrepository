
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
//	VideoCapture capture("/dev/v4l/by-path/pci-0000:00:14.0-usb-0:2:1.0-video-index0");
//	namedWindow("hhh",WINDOW_AUTOSIZE);
//	while(true)
//	{
//		Mat frame;
//		capture>>frame;
//		imshow("hhh",frame);
//		waitKey(30);
//	}

    VideoCapture inputVideo;
    VideoWriter outputVideo;
    Mat f;
    Mat frame;

    inputVideo.open("/dev/v4l/by-path/pci-0000:00:14.0-usb-0:2:1.0-video-index0");// 打开1号摄像头
    outputVideo.open(String("temp.mp4"), VideoWriter::fourcc('M', 'J', 'P', 'G'), inputVideo.get(cv::CAP_PROP_FPS)/2, Size(640, 480));// 配置输出视频文件


    while (1) {
        inputVideo >> frame;
        Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
        cameraMatrix.at<double>(0, 0) = 476.5783;
        cameraMatrix.at<double>(0, 1) = 0.0569;
        cameraMatrix.at<double>(0, 2) = 332.0945;
        cameraMatrix.at<double>(1, 1) = 476.4424;
        cameraMatrix.at<double>(1, 2) = 240.4092;

        Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
        distCoeffs.at<double>(0, 0) = -0.4087;
        distCoeffs.at<double>(1, 0) = 0.1737;
        distCoeffs.at<double>(2, 0) = -0.8538e-03;
        distCoeffs.at<double>(3, 0) = -0.0152e-03;
        distCoeffs.at<double>(4, 0) = 0;

        Mat view, rview, map1, map2;
        Size imageSize;
        imageSize = frame.size();
        initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(),
                                getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0),
                                imageSize, CV_16SC2, map1, map2);
        inputVideo >> f;
        remap(frame, f, map1, map2, INTER_LINEAR);

        outputVideo.write(f);// 将该帧写入视频文件
        imshow("Recording...", f);// 展示图片
        if (waitKey(10) == ' ')  break; // 等待250ms，期间如果有按下空格，则执行break
    }

    destroyWindow("Recording...");// 在释放cap之前，要销毁所有的显示图像窗口
    inputVideo.release();
    outputVideo.release();






	return 0;
}
