#include <reg52.h>
#include <stdio.h>  // 打印字符串需要调用 stdio.h 库
#include <intrins.h>
#include "eeprom.h"
#include "lcd.h"
#include "chao.h"


unsigned char code table[]={"0123456789"};
extern uchar receive_data[10];
//extern long int distance_set;

void lcd_init()   //LCD1602初始化
{
	comwrite(0x38);   //设置16*2显示，8位数据端口
	comwrite(0x0c);   //打开显示屏不打开光标
	comwrite(0x06);   //显示地址递增，写入一个数据之后，显示位置右移
	comwrite(0x01);   //清屏
}

void disp_state()   //显示固定字符
{
	comwrite(0x80);   //设定输入位置
	datwrite('S');         //输入用''，不可以用""
	datwrite('t');
	datwrite('a');
	datwrite('t');
	datwrite('e');
	datwrite(':');
	datwrite(receive_data[0]);
	
	comwrite(0x80+0x07);	
	datwrite(' ');
	datwrite('S');
	datwrite('p');
	datwrite('e');
	datwrite('e');
	datwrite('d');
	datwrite(':');
	datwrite(receive_data[1]);
}
	
void disp_distance(){
	comwrite(0x80+0x40);   //设定输入位置
	datwrite('d');         //输入用''，不可以用""
	datwrite('i');
	datwrite('s');
	datwrite('t');
	datwrite('a');
	datwrite('n');
	datwrite('c');
	datwrite('e');
	datwrite(':');
	comwrite(0x80+0x4c);    //设定输入位置
	datwrite('.');
	comwrite(0x80+0x4e);    //设定输入位置
	datwrite('c');
	datwrite('m');
}

void echodisplay(uint x)   //显示距离函数
{
	uchar q,b,s,g;
	q=x/1000;            //将测量函数测得的distance分为个位，十位，百位，千位
	b=(x/100)%10;
	s=(x/10)%10;
	g=x%10;
	
	receive_data[2] = q + 0x30;
	receive_data[3] = b + 0x30;
	receive_data[4] = s + 0x30;
	receive_data[5] = g + 0x30;
	
	comwrite(0x80+0x49);    //设定输出位置
	datwrite(table[q]);     //写入数据
	datwrite(table[b]);
	datwrite(table[s]);
	comwrite(0x80+0x4d);    //设定输入位置
	datwrite(table[g]);     //写入数据
}

void display(){				//距离大于设定值，显示"NO obctacles"
	comwrite(0x80+0x40);   //设定输入位置
	datwrite('N');
	datwrite('0');
	datwrite(' ');
	datwrite('o');
	datwrite('b');
	datwrite('s');
	datwrite('t');
	datwrite('a');
	datwrite('c');
	datwrite('l');
	datwrite('e');
	datwrite('s');
	datwrite(' ');
	datwrite(' ');
	datwrite(' ');
	datwrite(' ');
}

void lcd_show(long int distance,long int distance_set) 
	{
			if(distance >= distance_set){
				disp_state();
				display();
				receive_data[2] = '$';
				measure_init();//再次初始化测距模块
				delayt(50);//测量间隔50ms
			}
			else{
				disp_state();
				disp_distance();     //显示固定字符
				
				echodisplay(distance);//显示距离distance
				measure_init();//再次初始化测距模块
				delayt(50);//测量间隔50ms
			}
}
