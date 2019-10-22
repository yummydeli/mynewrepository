//
// Created by ming on 2019/10/16.
//

#ifndef OPENCV_TEST_RGBVALUE_H
#define OPENCV_TEST_RGBVALUE_H

#endif //OPENCV_TEST_RGBVALUE_H
#include<opencv2/opencv.hpp>
#include<iostream>
#include <math.h>
#include <opencv2/tracking.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <vector>
using namespace std;
using namespace cv;
/*
float GRAY_value(Mat src)
{
    Mat dst,gray_src;
    int sumb,sumg,sumr;
    sumb=0;
    sumg=0;
    sumr=0;
//    src = imread("/home/ming/git_yummy/mynewrepository/learning/MSER/test.jpeg");
    if (src.empty()) {
        cout << "could not load image..." << endl;
        return {-1};
    }
    cvtColor(src, gray_src, CV_BGR2GRAY);
    namedWindow("input", CV_WINDOW_AUTOSIZE);
    imshow("input",src);
    //namedWindow("output", CV_WINDOW_AUTOSIZE);
    //imshow("output", gray_src);
    //int height = gray_src.rows;
    //int width = gray_src.cols;


    //三通道
    dst.create(src.size(), src.type());

    float height =src.rows;
    float width = src.cols;
    float nc = src.channels();
//    float maxavr=-1;
//    float avr=0;
    int b1 = src.at<Vec3b>(height/2, width/2)[0];
    int g1 = src.at<Vec3b>(height/2, width/2)[1];
    int r1 = src.at<Vec3b>(height/2, width/2)[2];
    float avr=(b1+g1+r1/3);


//    for (int row = 0; row < height; row++) {
//        for (int col = 0; col < width; col++) {
//            if (nc == 1) {
//                int gray = gray_src.at<uchar>(row, col);
//                gray_src.at<uchar>(row, col) = 255 - gray;
//            }
//            else if (nc == 3) {
//
//                    int b = src.at<Vec3b>(row, col)[0];
//                    int g = src.at<Vec3b>(row, col)[1];
//                    int r = src.at<Vec3b>(row, col)[2];
//                    avr+=(b+g+r)/3;
//
////                dst.at<Vec3b>(row, col)[0] = 255 - b;
////                dst.at<Vec3b>(row, col)[1] = 255 - g;
////                dst.at<Vec3b>(row, col)[2] = 255 - r;
//            }
//        }
//    }



    return avr;
*/

/*对角线识别*/
int GRAY_value(Mat src)
{
    cv::Scalar scalarRect = cv::mean(src);
    int allPixel=src.rows*src.cols*scalarRect[0];
    int crossLinePixel=0;
    int crossLineNum=0;
    double k =(double)src.cols/src.rows;
    for(int n=0,m=0;n<src.rows;n++)
    {
        cv::Point point(m=n*k,n);
        crossLinePixel+=src.at<uchar>(m,n);
        crossLineNum++;
    }
    int brightnessAver=crossLinePixel/crossLineNum;
    return brightnessAver;

}