#ifndef __INIT_H__
#define __INIT_H__
#include <reg52.h>

sbit rs=P1^0;     //����ָ����ƿ� 
sbit rw=P1^1;     //��д���ƿ�    
sbit en=P1^2;     //ʹ�ܶ�

sbit key_up = P3^7;
sbit key_down = P3^6;

extern bit flag1;



#endif
