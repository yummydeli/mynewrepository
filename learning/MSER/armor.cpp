//
// Created by ming on 2019/10/22.
//
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <math.h>
using namespace std;
using namespace cv;



int main()
{
    cv::Mat src_img ;
    src_img = imread("/home/ming/git_yummy/mynewrepository/learning/MSER/test.jpeg");
    imshow("原始图",src_img);


    if(src_img.empty())
    {
        cout<<"open failed"<<endl;
        return -1;
    }

    int LowH =60;
    int LowS=120;
    int LowV =245;

    int HighH = 120;
    int HighS = 255;
    int HighV =255;


    Mat hsvimg;
    cvtColor(src_img,hsvimg,COLOR_BGR2HSV);

    vector<Mat> hsvsplit;

    split(hsvimg,hsvsplit);
    equalizeHist(hsvsplit[2],hsvsplit[2]);
    merge(hsvsplit,hsvimg);


    Mat thresholdimg;
    inRange(hsvimg,Scalar(LowH,LowS,LowV),Scalar(HighH,HighS,HighV),thresholdimg);

    imshow("二值化后的图片",thresholdimg);


    while(1)
    {
        int key=cv::waitKey(10);
        if (key==27)
        {
            break;
        }
    }
    return(0);
}

