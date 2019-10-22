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
//颜色识别
int RGBjustice(vector<int> aa)
{
    if((aa[0]>=127&&aa[0]<=255 && aa[1]>=0&&aa[1]<=255 && aa[2]>=0&&aa[2]<=127) || (aa[0]>=0&&aa[0]<=255 && aa[1]>=0&&aa[1]<=255 && aa[2]>=127&&aa[2]<=255) || (aa[0]>=62&&aa[0]<=114 && aa[1]>=77&&aa[1]<=86 && aa[2]>=69&&aa[2]<=111))
    //if ((aa[0]>50&&aa[0]<=127 && aa[1]>=0&&aa[1]<=85 && aa[2]>=60&&aa[2]<=255) || (aa[0]>=40&&aa[0]<=255 && aa[1]>=0&&aa[1]<=255 && aa[2]>=127&&aa[2]<=255))
        return 1;

}
//长宽比识别
float area_justice(cv::Rect bb)
{
    float pro = static_cast<float>(bb.width) / static_cast<float>(bb.height);
//    std::cout<<pro<<std::endl;
    if (pro<1)
    {
//        std::cout<<pro<<std::endl;
        return 1;
    }
    else
        return 0;

}

void mark(std::string num)
{
    //创建空白图用于绘制文字
    cv::Mat image = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
    //设置蓝色背景
    image.setTo(cv::Scalar(100, 0, 0));

    //设置绘制文本的相关参数
    std::string text = num;
    int font_face = cv::FONT_HERSHEY_COMPLEX;
    double font_scale = 2;
    int thickness = 2;
    int baseline;
    //获取文本框的长宽
    cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);

    //将文本框居中绘制
    cv::Point origin;
    origin.x = image.cols / 2 - text_size.width / 2;
    origin.y = image.rows / 2 + text_size.height / 2;
    cv::putText(image, text, origin, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 8, 0);

    //显示绘制解果
    cv::imshow("image", image);
    cv::waitKey(0);
//    return 0;

}

int main() {

    auto mat1 = cv::imread("/home/ming/git_yummy/mynewrepository/learning/MSER/test.jpeg");
//    auto mat2 = cv::imread("/home/ming/git_yummy/mynewrepository/learning/MSER/test.jpeg");
    auto mat2=mat1;
    auto mat = cv::imread("/home/ming/git_yummy/mynewrepository/learning/MSER/test.jpeg", cv::IMREAD_GRAYSCALE);
    cv::resize(mat,mat,{1280,720});
    cv::resize(mat1,mat1,{1280,720});
    cv::resize(mat2,mat2,{1280,720});
    auto mser = cv::MSER::create(5,60,200,0.1,.2,200,1.01,0.003,5);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Rect> bboxes;
    std::vector<cv::Rect> bboxes_new;
    std::vector<cv::Rect> bboxes_new2;
    std::vector<vector<int>> aa;

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

    constexpr float thresh = 0.1;
    for (int i = 1; i < bboxes.size(); ++i)
    {
        bool skip = false;
        for (auto &&index : drawed_rects)
            if (skip = (sp::iou(bboxes[i], bboxes[index]) > thresh))
                break;
        if (skip)
            continue;
        cv::rectangle(mat1, bboxes[i], {255, 0, 0});
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
//            cv::rectangle(mat2, bboxes_new[i], {0, 0, 0});
            cnt_new++;

        }
        else
        {
            continue;
        }

    }

    for (int i=0;i<bboxes_new2.size();i++)
    {
//        std::cout<<bboxes_new2[i]<<std::endl;
        cv::Mat imageROI=mat2(bboxes_new2[i]);

        aa.push_back(RGB_value(imageROI));

        std::cout<<"b"<<i<<"="<<aa[i][0]<<","<<"g"<<i<<"="<<aa[i][1]<<","<<"r"<<i<<"="<<aa[i][2]<<std::endl;
       cv::putText(mat2,std::to_string(i),bboxes_new2[i].tl(),cv::FONT_HERSHEY_COMPLEX,0.5,(0,0,255),1);
        if(RGBjustice(aa[i]))
        {
            cv::rectangle(mat2, bboxes_new2[i], {255, 0, 0});
            cnt_new2++;
        }
//        std::cout<<"bbnew2:"<<bboxes_new2[i]<<std::endl;
//        cv::rectangle(mat2, bboxes_new2[i], {255, 0, 0});
    }
//    std::cout<<cnt<<'\n';
    std::cout<<"cnt_new="<<cnt_new<<'\n';
    std::cout<<"boxes_num="<<cnt_new2<<'\n';
    std::cin.get();
    cv::imwrite("ans.jpg",mat1);
    cv::imwrite("ans2.jpg",mat2);
    return 0;
}

