//
// Created by ming on 2019/10/16.
//
#include "RGBvalue.hpp"

vector<int> RGB_value(Mat src)
{
    Mat src,dst,gray_src;
    int sumb,sumg,sumr;
    sumb=0;
    sumg=0;
    sumr=0;
//    src = imread("/home/ming/git_yummy/mynewrepository/learning/MSER/test.jpeg");
    if (src.empty()) {
        cout << "could not load image..." << endl;
        return -1;
    }
    cvtColor(src, gray_src, CV_BGR2GRAY);
    namedWindow("input", CV_WINDOW_AUTOSIZE);
    imshow("input",src);
    //namedWindow("output", CV_WINDOW_AUTOSIZE);
    //imshow("output", gray_src);
    //int height = gray_src.rows;
    //int width = gray_src.cols;

    //单通道
    /*for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int gray = gray_src.at<uchar>(row, col);
            gray_src.at<uchar>(row, col) = 255 - gray;
        }
    }*/

    //三通道
    dst.create(src.size(), src.type());

    int height =src.rows;
    int width = src.cols;
    int nc = src.channels();
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (nc == 1) {
                int gray = gray_src.at<uchar>(row, col);
                gray_src.at<uchar>(row, col) = 255 - gray;
            }
            else if (nc == 3) {
                int b = src.at<Vec3b>(row, col)[0];
                sumb=sumb+b;
                int g = src.at<Vec3b>(row, col)[1];
                sumg=sumg+g;
                int r = src.at<Vec3b>(row, col)[2];
                sumr=sumr+r;
//                dst.at<Vec3b>(row, col)[0] = 255 - b;
//                dst.at<Vec3b>(row, col)[1] = 255 - g;
//                dst.at<Vec3b>(row, col)[2] = 255 - r;
            }
        }
    }

    //bitwise_not(src, dst);
/*
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (nc == 1) {
                int gray = gray_src.at<uchar>(row, col);
                gray_src.at<uchar>(row, col) = 255 - gray;
            }
            else if (nc == 3) {
                int b = src.at<Vec3b>(row, col)[0];
                int g = src.at<Vec3b>(row, col)[1];
                int r = src.at<Vec3b>(row, col)[2];
                dst.at<Vec3b>(row, col)[0] = b;
                dst.at<Vec3b>(row, col)[1] = g;
                dst.at<Vec3b>(row, col)[2] = 0;
                gray_src.at < uchar >(row,col)= max(r, max(g, b) );
            }
        }
    }
*/
//    namedWindow("gray_invert", CV_WINDOW_AUTOSIZE);
//    imshow("gray_invert", dst);
//
//    namedWindow("output", CV_WINDOW_AUTOSIZE);
//    imshow("output", gray_src);
    vector<int> average;
    average.resize(3);
    average[0]=sumb/(height*width);
    average[1]=sumg/(height*width);
    average[2]=sumr/(height*width);

    cout<<"argb="<<sumb/(height*width)<<'\n';
    cout<<"argg="<<sumg/(height*width)<<'\n';
    cout<<"argr="<<sumr/(height*width)<<'\n';
//    waitKey(0);
    return average;

}