#include <reg52.h>
#include <string.h>        //�ַ�����������
#include <intrins.h>
#include "serial.h"
  
#define uint unsigned int
#define uchar unsigned char

extern uchar receive_data[8];
extern uint bytes;
extern uint bytes_old;

void delay(uint n)  //��ʱ����
{
	uint x,y;
		for(x=n;x>0;x--)
			for(y=114;y>0;y--);
}

void delayt(uint x)  //��ʱ����
{
    uchar j;
    while(x-- > 0)
    {
              for(j = 0;j < 125;j++)
        {
          ;
        }
    }
}
      
void uart_init()
 {//��ʼ�����ô���    
     SCON=0X50;        //����Ϊ������ʽ1,8λ���ݣ��ɱ䲨����
     TMOD=0X21;        //���ü�����������ʽ2
     PCON=0X00;        //�����ʲ��ӱ�
     TH1=0XFd;        //��������ʼֵ���ã�9600@11.0592MHz
     TL1=0XFd;
     TR1=1;            //�򿪼�����
     ES = 1;                 //�������ж�
     EA = 1;                 //�����ж�
 }

 void Delay_1ms(uint i)    //1ms��ʱ��ֱ�Ӹ��Ƽ���
 {//��ʱ�ӳ�����ʱʱ��Ϊ 1ms
   uint x,j;
   for(j=0;j<i;j++)
     for(x=0;x<=148;x++);
 }
 

 void SendChar(uchar character)  
 {//���͵����ַ�     
      SBUF=character;   //���͵����ַ�
      while(!TI);TI=0; //������ɱ�־ 
 }


 void  SendString(uchar String[]) 
  { //�����ַ���
       uchar *p=String;      
       while(*p!='#')               //��ָ��ָ��ĵ�ַΪ�գ�������ѭ��
     {                            
            SendChar(*p); //ָ���һ��Ĭ��ָ���׵�ַ        
         Delay_1ms(2);  //��ʱ������Ϊ��߷���׼ȷ��         
          p++;       
     }    
}

