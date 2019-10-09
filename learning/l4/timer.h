//
// Created by ming on 2019/10/7.
//
/*
#ifndef UNTITLED_TIMER_H
#define UNTITLED_TIMER_H


class timer {



};


#endif //UNTITLED_TIMER_H
*/

#pragma once

#include <chrono>
#include <iostream>
using namespace std;
namespace sp
{
   class timer
   {
   public :
        using clk_t=std::chrono::high_resolution_clock;
       timer(){
           m_tp = clk_t::now();
       }
       void reset()
       {
           m_tp=clk_t::now();
       }
       double get_milli() //ms
       {
           return std::chrono::duration<double,std::milli>(clk_t::now() - m_tp).count();
       }
//       template <typename T = std::milli>
       double get() //ms
       {
           return std::chrono::duration<double,std::milli>(clk_t::now() - m_tp).count();
       }
   private:
       clk_t::time_point m_tp;
   };

}