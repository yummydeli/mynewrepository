//
// Created by ming on 2019/10/17.
//
//
//#ifndef CLASSIFIER_CLASSIFIER_H
//#define CLASSIFIER_CLASSIFIER_H
//
//#endif //CLASSIFIER_CLASSIFIER_H

#pragma once

#include <string>
#include <vector>
#include <utility>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <dirent.h>            // POSIX.(As C++11 doesn't support filesystem)

namespace sp
{
    class template_classifier;
    using classifier=template_classifier;

    class template_classifier
    {
    public:
        using container_t=std::vector<cv::Mat>;

        //读取正负模板的路径并进入
        template_classifier(const std::string& loc)
        {
            if(loc.back() == '/' || loc.back() == '\\')
                create_templates(loc+"positive", loc+"negative");
            else
                create_templates(loc+"/positive", loc+"/negative");
        }
        //创建正、负模板类
        inline void create_templates(const std::string& g_loc, const std::string& b_loc)
        {
            container_t ret;
            good_templates = make_templates_(g_loc);
            bad_templates  = make_templates_(b_loc);
        }
        //求样本图片与模板进行匹配打分时得分最高的值
        inline int forward(cv::Mat mat) // noexcept
        {
            prepare_(mat);
            int match_id = 0;
            int now_belief;
            int max_belief = std::numeric_limits<int>::min();
            int id = 0;
            for(; id < good_templates.size(); id++)
            {
                now_belief = compare_(mat, good_templates[id]);
//	         std::cout << id << " p--- " << now_belief << '\n';
                if(max_belief < now_belief)
                {
                    max_belief = now_belief;

                    match_id = id;
//                std::cout << match_id << "pm --- " << max_belief << '\n';
                }
            }
            //先匹配正模板后匹配负模板，若正样本中与正模板匹配的打分低于阈值，则归为负样本，且不计入正模板匹配成功数
            if(max_belief < low_bound)
                return id;
            for(int i = 0; i < bad_templates.size(); ++id, ++i)
            {
                now_belief = compare_(mat, bad_templates[i]);
//	         std::cout << id << " n--- " << now_belief << '\n';

                if(max_belief < now_belief) // 直接返回
                {
//                std::cout << id << " nm--- " << now_belief << '\n';
                    return id;
                }

            }
            std::cout << match_id << '\n';
            return match_id;
        }
        //若一个正样本匹配正模板结束后最大分数始终比每次比较时的当前分数大，则接下来匹配负模板，此时返回的id数大于正模板数，即此样本与正模板不匹配

        inline bool boolean_forward(cv::Mat& mat)
        {
            return forward(mat) < good_templates.size();
        }
    public: // Default values.
        double      thre_proportion = 0.25; // 比例阈值，取直方图中thre_proportion位置亮的像素作为thre
        int         low_bound       = 700;
        cv::Size2i  fixed_sz        = {64, 64};
    private:
        // @@@ get_threshold: 按获取一个cv::Mat的阈值
        inline int         get_threshold_(cv::Mat& mat)
        {
            uint32_t iter_rows = mat.rows;
            uint32_t iter_cols = mat.cols;
            auto sum_pixel = iter_rows * iter_cols;
            if(mat.isContinuous())
            {
                iter_cols = sum_pixel;
                iter_rows = 1;
            }
            int histogram[256];
            memset(histogram, 0, sizeof(histogram));
            for (uint32_t i = 0; i < iter_rows; ++i)
            {
                const uchar* lhs = mat.ptr<uchar>(i);
                for (uint32_t j = 0; j < iter_cols; ++j)
                    ++histogram[*lhs++];
            }
            auto left = thre_proportion * sum_pixel;
            int i = 255;
            while((left -= histogram[i--]) > 0);
            return std::max(i, 0);
        }

        // @@@ prepare_
        inline void        prepare_(cv::Mat& mat)
        {
            // std::cout << dst_sz << std::endl;
            cv::resize(mat, mat, fixed_sz);
            cv::threshold(mat, mat, get_threshold_(mat), 1, cv::THRESH_BINARY);
        }
        // @@@ make_templates_
        inline container_t make_templates_(const std::string& where)
        {
            container_t ret;
            // std::cout << where.c_str() << std::endl;
            DIR* dir_ptr = opendir(where.c_str());//打开目录
            dirent* dptr;//存放要读取的地址
            while((dptr = readdir(dir_ptr)) != NULL)
            {
                if(dptr->d_name[0] == '.')//排除目录在中文件名为.的文件
                    continue;
                cv::Mat tem;
                if(where.back() == '/')//若文件名最后一个有/则按顺序读取目录中的文件
                    tem = cv::imread(where+dptr->d_name, cv::IMREAD_GRAYSCALE);
                else//若文件名最后一位无/则加上/以后在进行读取图片
                    tem = cv::imread(where+'/'+dptr->d_name, cv::IMREAD_GRAYSCALE);
                prepare_(tem);//对读取的每张图片进行预处理
                ret.push_back(tem);//将每个图片存入Mat类型的ret变量中
            }
            std::cout << "@@@ " << where << " ~ " << ret.size() << " file reading finished.\n";
            return ret;
        }
        // @@@ compare_
        inline int compare_(cv::Mat& tem, cv::Mat& true_sample)
        {
            uint32_t iter_rows = fixed_sz.height;
            uint32_t iter_cols = fixed_sz.width;
            auto sum_pixel = iter_rows * iter_cols;
            if(tem.isContinuous() && true_sample.isContinuous())
            {
                iter_cols = sum_pixel;
                iter_rows = 1;
            }
            int same_cnt = 0;
            for (uint32_t i = 0; i < iter_rows; ++i)
            {
                const uchar* lhs = tem.ptr<uchar>(i);
                const uchar* rhs = true_sample.ptr<uchar>(i);
                for (uint32_t j = 0; j < iter_cols; ++j)
                {
                    bool l = *lhs++, r = *rhs++;
                    if(l==0 && r==0)
                        continue;
                    if(l && r==1)
                    {
                        same_cnt+=3;
                    }
                    else
                        same_cnt-=2;
                }
            }
            return same_cnt;
        }
    private:
        container_t good_templates;
        container_t bad_templates;
    };
}

















