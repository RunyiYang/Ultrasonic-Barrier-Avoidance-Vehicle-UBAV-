#include <reg52.h>
#include <string.h>        //字符串处理函数包
#include <intrins.h>
#include "serial.h"
  
#define uint unsigned int
#define uchar unsigned char

extern uchar receive_data[8];
extern uint bytes;
extern uint bytes_old;

void delay(uint n)  //延时函数
{
	uint x,y;
		for(x=n;x>0;x--)
			for(y=114;y>0;y--);
}

void delayt(uint x)  //延时函数
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
 {//初始化配置串口    
     SCON=0X50;        //设置为工作方式1,8位数据，可变波特率
     TMOD=0X21;        //设置计数器工作方式2
     PCON=0X00;        //波特率不加倍
     TH1=0XFd;        //计数器初始值设置，9600@11.0592MHz
     TL1=0XFd;
     TR1=1;            //打开计数器
     ES = 1;                 //开串口中断
     EA = 1;                 //开总中断
 }

 void Delay_1ms(uint i)    //1ms延时，直接复制即可
 {//延时子程序，延时时间为 1ms
   uint x,j;
   for(j=0;j<i;j++)
     for(x=0;x<=148;x++);
 }
 

 void SendChar(uchar character)  
 {//发送单个字符     
      SBUF=character;   //发送单个字符
      while(!TI);TI=0; //发送完成标志 
 }


 void  SendString(uchar String[]) 
  { //发送字符串
       uchar *p=String;      
       while(*p!='#')               //若指针指向的地址为空，则跳出循环
     {                            
            SendChar(*p); //指针第一次默认指向首地址        
         Delay_1ms(2);  //延时，作用为提高发送准确度         
          p++;       
     }    
}

