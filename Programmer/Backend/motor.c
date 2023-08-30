#include <reg52.h>
#include "motor.h"
#include "serial.h"

unsigned int dis_count = 0;		  //����

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
	if(get_speed == 'L')	//����
		speed = 40;
	if(get_speed == 'M')	//����
		speed = 75;
	if(get_speed == 'H')	//����
		speed = 100;
		
	model = receive_data[0];
	if(model == 'f')	//ǰ��
		forward(speed);
	if(model == 'l')	//��ת
		left(speed);
	if(model == 'r')
		right(speed);
	if(model == 'b')
		back(speed);
	if(model == 's')
		stop();


}


void command(){
	
	if( key_auto == 0)		//key_auto������ʱ�����ˣ�����������ģʽ
	{
		delay(5);		  //����
		if(key_auto == 0)	   //ȷ�ϰ���������
		{
			while(!key_auto)	 //�����ɿ����
				;
			n = 1;			 //n��ֵΪ1������������ģʽ
		}		
	}

	if(key_mannual == 0)		//key_mannual������ʱ������ģʽ
	{
		delay(5);				//����
		if(key_mannual == 0)			//ȷ�ϰ���������
		{
			while(!key_mannual)		//�����ɿ����
				;
			n = 0;			   //n��ֵΪ2������ģʽ
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

//С������
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

//С��ǰ��
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

//С��ֹͣ
void stop(void)
{
	enA = 1;
	enB = 1;
	in1 = 0;
	in2 = 0;
	in3 = 0;
	in4 = 0;
}




