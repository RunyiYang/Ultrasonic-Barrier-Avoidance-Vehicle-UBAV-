#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <reg52.h>
#include <string.h>        //字符串处理函数包
#include <intrins.h>
  
#define uchar unsigned char    // 宏定义  51单片机内存资源有限
#define uint  unsigned int    //需考虑内存资源问题，故使用无符号类型
      

 
void uart_init();
void Delay_1ms(uint i);
void SendChar(uchar character);
void SendString(uchar *p); 
void delay(uint n);  //延时函数
void delayt(uint x);  //延时函数


#endif
