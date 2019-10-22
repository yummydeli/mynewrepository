//
// Created by ming on 2019/10/22.
//

//
// Created by ming on 2019/10/22.
//

//
// Created by ming on 2019/10/16.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <opencv2/tracking.hpp>
#include<math.h>
#include "RGBvalue.hpp"
namespace sp
{
    float iou(const cv::Rect& lhs,const cv::Rect& rhs)
    {
        const int lt_x = std::max(lhs.x                                                                                                 , rhs.x);
        const int lt_y = std::max(lhs.y, rhs.y);
        const int rd_x = std::min(lhs.x + lhs.width, rhs.x + rhs.width);
        const int rd_y = std::min(lhs.y + lhs.height, rhs.y + rhs.height);

        const int inner_w = std::max(0, rd_x - lt_x + 1);
        const int inner_h = std::max(0, rd_y - lt_y + 1);
        const int inner_area = inner_h * inner_w;

        return static_cast<float>(inner_area) / (lhs.area() + rhs.area() - inner_area);
    }
}

//长宽比识别
float area_justice(cv::Rect bb)
{
    float pro = static_cast<float>(bb.width) / static_cast<float>(bb.height);

    if (pro<0.9)
    {
//        std::cout<<pro<<std::endl;
        return 1;
    }
            else
        return 0;

}

//筛选亮度
namespace cv
{
    int Flip(Mat &img)
    {
        int counter[256]={0};
        int t,Thres=0;
        int s=0;
        int x=img.cols;
        int y=img.rows;
        for(int i=0;i<y;i++){
            int j=(y/x)*i;
            t=img.at<uchar>(j, i);
            counter[t]=counter[t]+1;
        }
        for(int i=0;i<=255;i++){
            s=s+counter[i];
        }
        s=s*0.15;
        for(int i=255;i>0;i--){
            s=s-counter[i];
            if(s<=0) {
                Thres=i;
                break;
            }
        }
        return Thres;
    }
}

//提取灯条


int main() {

    auto mat1 = cv::imread("/home/ming/git_yummy/mynewrepository/learning/MSER/test.jpeg");
//    auto mat2 = cv::imread("/home/ming/git_yummy/mynewrepository/learning/MSER/test.jpeg");
    auto mat2=mat1;
    auto mat = cv::imread("/home/ming/git_yummy/mynewrepository/learning/MSER/test.jpeg", cv::IMREAD_GRAYSCALE);
    Mat hsv;
    cvtColor(mat1,hsv,CV_RGB2HSV);
    cv::resize(mat,mat,{1280,720});
    cv::resize(mat1,mat1,{1280,720});
    cv::resize(mat2,mat2,{1280,720});
    auto mser = cv::MSER::create(5,60,200,0.1,.2,200,1.01,0.003,5);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Rect> bboxes;
    std::vector<cv::Rect> bboxes_new;
    std::vector<cv::Rect> bboxes_new2;
    std::vector<vector<int>> aa;
    cv::Mat imageROI2;

    mser->detectRegions(mat, contours, bboxes);
    std::cout<< bboxes.size()<<'\n';
    std::cin.get();
    std::vector<int> drawed_rects;
    drawed_rects.reserve(bboxes.size() / 4);
    //std::cout<< bboxes.front()<<std::endl;//
    int cnt = 0;
    int cnt_new=0;
    int cnt_new2=0;
    if (!bboxes.empty()) {
        ++cnt;
        cv::rectangle(mat1, bboxes.front(), {255, 0, 0});
        drawed_rects.push_back(0);
        bboxes_new.push_back(bboxes[0]);
    }

    constexpr float thresh = 0.355;
    for (int i = 1; i < bboxes.size(); ++i)
    {
        bool skip = false;
        for (auto &&index : drawed_rects)
            if (skip = (sp::iou(bboxes[i], bboxes[index]) > thresh))
                break;
        if (skip)
            continue;
//        cv::rectangle(mat1, bboxes[i], {255, 0, 0});
        bboxes_new.push_back(bboxes[i]);

        drawed_rects.push_back(i);
        ++cnt;
    }
    for(int i=0;i<bboxes_new.size();i++)
    {

        if(area_justice(bboxes_new[i]))
        {
//            std::cout<<i<<":"<<'\n';
            bboxes_new2.push_back(bboxes_new[i]);
//            cv::rectangle(mat2, bboxes_new[i], {0, 255, 0},1);
            cnt_new++;

        }
        else
        {
            continue;
        }
    }
    //筛选亮度

    for (int i=0;i<bboxes_new2.size();i++)
    {
        cv::Mat imageROI1=hsv(bboxes_new2[i]);
        cv::Mat imageROI2=mat(bboxes_new2[i]);
        if(Flip(imageROI2)<200)
            continue;

        cv::rectangle(mat2, bboxes_new2[i], {0, 255, 0},1);
        cnt_new2++;

    }
    for (int i=0;i<bboxes_new2.size();i++)
    {
        std::cout<<"bbnew2:"<<bboxes_new2[i]<<std::endl;
    }
//    std::cout<<cnt<<'\n';
    std::cout<<"cnt_new="<<cnt_new<<'\n';
    std::cout<<"boxes_num="<<cnt_new2<<'\n';
    std::cin.get();
//    cv::imwrite("ans.jpg",mat1);
    cv::imwrite("ans2.jpg",mat2);
    return 0;
}

