#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
/*
    Mat image = imread("/home/ming/test.jpg");
    imshow("123",image);
    waitKey(0);
    return 0;*/

   auto mat = imread(
           "/home/ming/test.jpg",
           cv::IMREAD_GRAYSCALE/*IMPORTANT IF THRESHOLDING*/
   );
   resize(mat,mat,{500, 400});//zoom in
   imshow("test",mat);
   threshold(mat,mat,100,255,cv::THRESH_BINARY);
   imshow("test2",mat);
   std::cout<< sizeof(char)<<std::endl;
   waitKey();
  //std::cout << "Hello, World!" << std::endl;

   return 0;

/*测试*/
//constexpr char a[]="/home/ming/test.jpg";
//auto mat = cv::imread(a);
//auto gray = cv::imread(a,cv::IMREAD_GRAYSCALE);
//cv::imwrite("test2.jpg",mat);

}