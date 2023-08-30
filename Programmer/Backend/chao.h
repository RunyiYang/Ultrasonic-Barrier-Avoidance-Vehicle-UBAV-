#ifndef __CHAO_H__
#define __CHAO_H__

#include <reg52.h>


#define uint unsigned int
#define uchar unsigned char

sbit trig=P1^3;   //超声波触发引脚  
sbit echo=P1^6;   //超声波接收引脚  



void measure();    		//测距函数
void trigger();  	 		//超声波模块触发函数
void measure_init();  //测量函数初始化



#endif
