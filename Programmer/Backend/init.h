#ifndef __INIT_H__
#define __INIT_H__
#include <reg52.h>

sbit rs=P1^0;     //数据指令控制口 
sbit rw=P1^1;     //读写控制口    
sbit en=P1^2;     //使能端

sbit key_up = P3^7;
sbit key_down = P3^6;

extern bit flag1;



#endif
