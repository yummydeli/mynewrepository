#include <opencv2/highgui/highgui.hpp>   
    #include <opencv2/imgproc/imgproc.hpp>   
    #include <opencv2/core/core.hpp>  
      
    using namespace cv;  
      
    int main(int argc, char** argv)  
    {  
      
        VideoCapture cap("test.mp4");  
        if (!cap.isOpened())  
        {  
            return -1;  
        }  
        Mat frame;  
        while (1)  
        {  
            cap >> frame;  
            if (frame.empty()) break;  
            imshow("当前视频", frame);  
            if (waitKey(30) >= 0)  
                break;  
        }  
        return 0;  
    }  

