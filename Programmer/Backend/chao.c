#include <reg52.h>
#include <stdio.h>
#include "chao.h"
#include "serial.h"

unsigned char count;       
long int distance;

void trigger()   //超声波模块触发函数
{
	trig=1;      //打开超声波触发端口
	delay(2);
	trig=0;      //关闭超声波触发端口
}

void measure_init()  //测量函数初始化
{
	trig=0;   //触发端口低电平
	echo=0;   //接收端口低电平
	count=0;  
}

void measure()    //测距函数
{
	uchar a;
	uint b,c;
	TR0=1;   //打开定时器
	while(echo)   //当超声波接收打开时计时
	{
		;
	}
	TR0=0;   //关闭定时器
	a=TL0;   //a，b分别赋予中断函数高八位和第八位计时后的数值
	b=TH0;
	c=(b<<8)+a;  //高八位左移八位之后与低八位做加法运算
	c=c-0xfc66;  //减去初始值高八位和低八位
	distance=c+1000*count;  //总的时间,单位是μs
	TL0=0x66;    //重新装入初始值
	TH0=0xfc;
	delayt(30);
	distance=3453*distance/20000; //计算距离，单位是cm
}

//距离计算原理:所求t μs,distance=t*0.34(声速340m/s=0.34cm/μs)/2  

