#include <reg52.h>
#include <intrins.h>
#include "init.h"
#include "serial.h"
#include "eeprom.h"
#include "lcd.h"
#include "chao.h"
#include "motor.h"
#include <stdio.h>

long int distance_set;
uchar receive_data[10]={'s','L','0','0','0','0','0','0','\n','#'};
uint bytes=0, n = 0;
uint bytes_old;
int show_flag=0;
int i;

extern unsigned char count;       
extern long int distance;
long int distance_buf;

void Com_Int(void) interrupt 4
  {//串口中断函数（接受和发送数据时都会调回此函数）
      EA = 0;
      if(RI==1)     //此句判断不能省略，否则发送数据时也会执行此语句，造成字符串错误
      {
          RI=0;
          receive_data[bytes] = SBUF;//接收到的数据
          bytes++;
      }    
      EA = 1;
  }

void T0_init()    //T0中断初始化
{
	TMOD=0x21;    //定义计时器0工作方式为1
	TL0=0x66;     //装入初始值
	TH0=0xfc;
	ET0=1;   //开定时器0中断
	EA=1;    //开总中断
}

void T_0() interrupt 1   //计时器中断函数T0
{
	TF0=0;      //计时器溢出中断
	TL0=0x66;   //填入初始数据
	TH0=0xfc;
	count++;    //产生一次中断就加一
    if(count==18)  //当计数到达18的时候，约1s
	{
		TR0=0;      //关闭计时器中断0
		TL0=0x66;   //重新装入初始值
		TH0=0xfc;
		count=0;    //把count清零
	}
}


void main()    //主函数
{
	lcd_init();    //初始化LCD
	T0_init();     //初始化T0计时器
	measure_init();//初始化超声波测量模块 
	distance_set = byte_read(1);//EEPROM
  bytes_old=0;
  uart_init();

	

	
	while(1)       //循环
	{ 		
			bytes_old=0; //将bytes_old、bytes置为初始化值，等待接收下一字符串
			bytes=0;
			command();
			
			if(n)
			{
				show_flag=!show_flag; 
	
				if(show_flag==0){
					lcd_show(distance,distance_set);
				}
				else{
				motor();
				
				if(key_up == 0)		  	//若范围增加开关被按下
				{
					delay(5);				//消抖
					if(key_up == 0)			//确认范围增加开关被按下
					{
						if(distance_set < 500){
							distance_set += 50;
						}
						else	distance_set = 500;
						
						byte_write(1, distance_set);
					}	
				}
			
				if(key_down == 0)		   //若范围减小开关被按下
				{	
					delay(5);			//消抖
					if(key_down == 0)			//确认范围减小开关被按下
					{
						if(distance_set > 50){
							distance_set -= 50;
						}
						else	distance_set = 50;
						
						byte_write(1, distance_set);
					}		
				}
				if(receive_data[0] == '^')		  	//若范围增加开关被按下
				{
					if(distance_set < 500){
						distance_set += 50;
					}
					else	distance_set = 500;
					byte_write(1, distance_set);
				}
			
				if(receive_data[0] == '-')		   //若范围减小开关被按下
				{	
						if(distance_set > 50){
							distance_set -= 50;
						}
						else	distance_set = 50;
						
						byte_write(1, distance_set);
				}
			
				trigger(); //触发超声波测距		
				while(echo==0)//当接收端没有打开的时候在这里循环
					{
						;
					}		
				measure();//测量距离distance
				
				
				if(distance > 0 && distance <= distance_set)		//若获取的距离大于0且小于等于distance_set时
				{
					stop();
					delay(500);
					l();							  //先左转
					receive_data[0] = 'l';
					receive_data[6]=distance_set/100+0x30;
					receive_data[7]=distance_set/10%10+0x30;
					SendString(receive_data);
					lcd_show(distance,distance_set);
					delay(12);
					stop();
					delay(400);
					f();							  //forward
					receive_data[0] = 'f';
					receive_data[6]=distance_set/100+0x30;
					receive_data[7]=distance_set/10%10+0x30;
					SendString(receive_data);
					lcd_show(distance,distance_set);
					delay(30);
					stop();
					delay(400);
					r();							  //right
					receive_data[0] = 'r';
					receive_data[6]=distance_set/100+0x30;
					receive_data[7]=distance_set/10%10+0x30;
					SendString(receive_data);
					lcd_show(distance,distance_set);
					delay(10);
					stop();
					delay(400);
				}			
				else{
					forward1(100);
					receive_data[0] = 'f';
					receive_data[1]='M';
					receive_data[6]=distance_set/100+0x30;
					receive_data[7]=distance_set/10%10+0x30;
					SendString(receive_data);
					lcd_show(distance,distance_set);

				}			

			}
		}
			else{
				motor();
			}

	}
}

