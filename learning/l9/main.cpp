#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture inputVideo("/dev/v4l/by-path/pci-0000:00:14.0-usb-0:2:1.0-video-index0");
    if (!inputVideo.isOpened())
    {
        cout << "Could not open the input video: " << endl;
        return -1;
    }
    Mat frame;
    Mat frameCalibration;

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


    while (1) //Show the image captured in the window and repeat
    {
        inputVideo >> frame;              // read
        if (frame.empty()) break;         // check if at end
        remap(frame, frameCalibration, map1, map2, INTER_LINEAR);
        imshow("Origianl", frame);
        imshow("Calibration", frameCalibration);
        char key = waitKey(1);
        if (key == 27 || key == 'q' || key == 'Q')break;
    }
    return 0;
}