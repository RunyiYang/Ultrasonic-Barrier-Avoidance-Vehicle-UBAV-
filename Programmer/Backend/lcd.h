#ifndef __LCD_H__
#define __LCD_H__

#include <reg52.h>
#include <stdio.h>  // 打印字符串需要调用 stdio.h 库

#define uint unsigned int
#define uchar unsigned char


void lcd_init();   					//LCD1602初始化
void disp_state();   				//显示固定字符
void echodisplay(uint x);   //显示距离函数
void display();							//显示"NO obctacles"
void disp_distance();				//显示距离固定字符
void lcd_show(long int,long int);//距离大于设定，显示“NO obctacles”；距离小于设定，显示距离

#endif