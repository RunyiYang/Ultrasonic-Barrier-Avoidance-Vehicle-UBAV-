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
  {//�����жϺ��������ܺͷ�������ʱ������ش˺�����
      EA = 0;
      if(RI==1)     //�˾��жϲ���ʡ�ԣ�����������ʱҲ��ִ�д���䣬����ַ�������
      {
          RI=0;
          receive_data[bytes] = SBUF;//���յ�������
          bytes++;
      }    
      EA = 1;
  }

void T0_init()    //T0�жϳ�ʼ��
{
	TMOD=0x21;    //�����ʱ��0������ʽΪ1
	TL0=0x66;     //װ���ʼֵ
	TH0=0xfc;
	ET0=1;   //����ʱ��0�ж�
	EA=1;    //�����ж�
}

void T_0() interrupt 1   //��ʱ���жϺ���T0
{
	TF0=0;      //��ʱ������ж�
	TL0=0x66;   //�����ʼ����
	TH0=0xfc;
	count++;    //����һ���жϾͼ�һ
    if(count==18)  //����������18��ʱ��Լ1s
	{
		TR0=0;      //�رռ�ʱ���ж�0
		TL0=0x66;   //����װ���ʼֵ
		TH0=0xfc;
		count=0;    //��count����
	}
}


void main()    //������
{
	lcd_init();    //��ʼ��LCD
	T0_init();     //��ʼ��T0��ʱ��
	measure_init();//��ʼ������������ģ�� 
	distance_set = byte_read(1);//EEPROM
  bytes_old=0;
  uart_init();

	

	
	while(1)       //ѭ��
	{ 		
			bytes_old=0; //��bytes_old��bytes��Ϊ��ʼ��ֵ���ȴ�������һ�ַ���
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
				
				if(key_up == 0)		  	//����Χ���ӿ��ر�����
				{
					delay(5);				//����
					if(key_up == 0)			//ȷ�Ϸ�Χ���ӿ��ر�����
					{
						if(distance_set < 500){
							distance_set += 50;
						}
						else	distance_set = 500;
						
						byte_write(1, distance_set);
					}	
				}
			
				if(key_down == 0)		   //����Χ��С���ر�����
				{	
					delay(5);			//����
					if(key_down == 0)			//ȷ�Ϸ�Χ��С���ر�����
					{
						if(distance_set > 50){
							distance_set -= 50;
						}
						else	distance_set = 50;
						
						byte_write(1, distance_set);
					}		
				}
				if(receive_data[0] == '^')		  	//����Χ���ӿ��ر�����
				{
					if(distance_set < 500){
						distance_set += 50;
					}
					else	distance_set = 500;
					byte_write(1, distance_set);
				}
			
				if(receive_data[0] == '-')		   //����Χ��С���ر�����
				{	
						if(distance_set > 50){
							distance_set -= 50;
						}
						else	distance_set = 50;
						
						byte_write(1, distance_set);
				}
			
				trigger(); //�������������		
				while(echo==0)//�����ն�û�д򿪵�ʱ��������ѭ��
					{
						;
					}		
				measure();//��������distance
				
				
				if(distance > 0 && distance <= distance_set)		//����ȡ�ľ������0��С�ڵ���distance_setʱ
				{
					stop();
					delay(500);
					l();							  //����ת
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

