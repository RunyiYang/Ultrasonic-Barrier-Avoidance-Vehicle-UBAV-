#include <reg52.h>
#include "motor.h"
#include "serial.h"

unsigned int dis_count = 0;		  //计数

unsigned char tmp, dat, flat;	 
unsigned int num, c = 0;
unsigned int speed = 0;
extern uchar receive_data[10];
extern uint n;
char get_speed, model = 's', get_beep;
	


void delay_us(unsigned int aa)
{
	while(aa--);
}


void motor(void)
{
	get_speed = receive_data[1];
	if(get_speed == 'L')	//低速
		speed = 40;
	if(get_speed == 'M')	//中速
		speed = 75;
	if(get_speed == 'H')	//高速
		speed = 100;
		
	model = receive_data[0];
	if(model == 'f')	//前进
		forward(speed);
	if(model == 'l')	//左转
		left(speed);
	if(model == 'r')
		right(speed);
	if(model == 'b')
		back(speed);
	if(model == 's')
		stop();


}


void command(){
	
	if( key_auto == 0)		//key_auto被按下时，后退，超声波避障模式
	{
		delay(5);		  //消抖
		if(key_auto == 0)	   //确认按键被按下
		{
			while(!key_auto)	 //按键松开检测
				;
			n = 1;			 //n赋值为1，超声波避障模式
		}		
	}

	if(key_mannual == 0)		//key_mannual被按下时，控制模式
	{
		delay(5);				//消抖
		if(key_mannual == 0)			//确认按键被按下
		{
			while(!key_mannual)		//按键松开检测
				;
			n = 0;			   //n赋值为2，控制模式
		}				
	}
}





void left(unsigned int pwm)
{
	enA = 1;
	enB = 1;
	in1 = 1;
	in2 = 0;
	in3 = 0;
	in4 = 1;
	delay_us( pwm );
	
	enA = 1;
	enB = 1;
	in1 = 0;
	in2 = 0;
	in3 = 0;
	in4 = 0;
	delay_us( 100 - pwm ); 
}
void l(void)
{
	enA = 1;
	enB = 1;
	in1 = 1;
	in2 = 0;
	in3 = 0;
	in4 = 1;
}


void right(unsigned int pwm)
{
	enA = 1;
	enB = 1;
	in1 = 0;
	in2 = 1;
	in3 = 1;
	in4 = 0;
	delay_us( pwm );
	
	enA = 1;
	enB = 1;
	in1 = 0;
	in2 = 0;
	in3 = 0;
	in4 = 0;
	delay_us( 100 - pwm ); 
}
void r(void)
{
	enA = 1;
	enB = 1;
	in1 = 0;
	in2 = 1;
	in3 = 1;
	in4 = 0;
	
}

//小车后退
void back(unsigned int pwm)
{
	enA = 1;
	enB = 1;
	in1 = 1;
	in2 = 0;
	in3 = 1;
	in4 = 0;
	delay_us( pwm );
	
	enA = 1;
	enB = 1;
	in1 = 0;
	in2 = 0;
	in3 = 0;
	in4 = 0;
	delay_us( 100 - pwm ); 
}
void b(void)
{
	enA = 1;
	enB = 1;
	in1 = 1;
	in2 = 0;
	in3 = 1;
	in4 = 0;
}

//小车前进
void forward1(unsigned int pwm)
{
	enA = 1;
	enB = 1;
	in1 = 0;
	in2 = 1;
	in3 = 0;
	in4 = 1;
	delay_us( 101*pwm );
	
	enA = 1;
	enB = 1;
	in1 = 0;
	in2 = 0;
	in3 = 0;
	in4 = 0;
	delay_us( 100- pwm ); 
}
void forward(unsigned int pwm)
{
	enA = 1;
	enB = 1;
	in1 = 0;
	in2 = 1;
	in3 = 0;
	in4 = 1;
	delay_us( pwm );
	
	enA = 1;
	enB = 1;
	in1 = 0;
	in2 = 0;
	in3 = 0;
	in4 = 0;
	delay_us( 100- pwm ); 
}
void f(void)
{
	enA = 1;
	enB = 1;
	in1 = 0;
	in2 = 1;
	in3 = 0;
	in4 = 1;
}

//小车停止
void stop(void)
{
	enA = 1;
	enB = 1;
	in1 = 0;
	in2 = 0;
	in3 = 0;
	in4 = 0;
}




