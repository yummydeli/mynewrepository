//
// Created by ming on 2019/10/22.
//



//	VideoCapture capture("/dev/v4l/by-path/pci-0000:00:14.0-usb-0:2:1.0-video-index0");
//	namedWindow("hhh",WINDOW_AUTOSIZE);
//	while(true)
//	{
//		Mat frame;
//		capture>>frame;
//		imshow("hhh",frame);
//		waitKey(30);
//	}

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>

    using namespace cv;
    using namespace std;
/*
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
*/


    int main()
    {
        VideoCapture cap;
        VideoWriter outputVideo;
        Mat frame;

        cap.open("/dev/v4l/by-path/pci-0000:00:14.0-usb-0:2:1.0-video-index0");// 打开1号摄像头
        outputVideo.open(String("temp.mp4"), VideoWriter::fourcc('M', 'J', 'P', 'G'), cap.get(cv::CAP_PROP_FPS), Size(640, 480));// 配置输出视频文件
        while (1) {
            cap >> frame;
            outputVideo.write(frame);// 将该帧写入视频文件
            imshow("Recording...", frame);// 展示图片
            if (waitKey(10) == ' ')  break; // 等待250ms，期间如果有按下空格，则执行break
        }

        destroyWindow("Recording...");// 在释放cap之前，要销毁所有的显示图像窗口
        cap.release();
        outputVideo.release();

        return 0;
    }
