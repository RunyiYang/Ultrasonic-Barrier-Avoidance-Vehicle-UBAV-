#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <reg52.h>
#include <stdio.h>  // 打印字符串需要调用 stdio.h 库

#define uint unsigned int
#define uchar unsigned char

//定义L298N端口
sbit in1 = P2^0;
sbit in2 = P2^1;
sbit in3 = P2^2;
sbit in4 = P2^3;
sbit enA = P1^0;
sbit enB = P1^7;

//定义微动开关端口
sbit key_mannual = P3^3;
sbit key_auto = P3^2;

//定义蜂鸣器
sbit beep = P1^5;

void motor(void);
void command(void);
void delay_us(unsigned int);
void forward(unsigned int);
void f(void);
void back(unsigned int);
void b(void);
void left(unsigned int);
void l(void);
void right(unsigned int);
void r(void);
void stop(void);
void forward1(unsigned int);


#endif
