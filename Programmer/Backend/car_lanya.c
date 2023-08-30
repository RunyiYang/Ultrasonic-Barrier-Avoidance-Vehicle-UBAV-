#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

uchar tmp;

uint c=0, model;
uint speed = 35;

sbit led1=P1^0;		  //指示灯0
sbit led2=P1^1;			//指示灯1
sbit led3=P1^2;			//指示灯3
sbit led7=P1^7;			//指示灯3

sbit in1 = P0^0;
sbit in2 = P0^1;
sbit in3 = P0^2;
sbit in4 = P0^3;
sbit enA = P0^4;
sbit enB = P0^5;

void delay_ms(unsigned char c)   //误差 0us
{
    unsigned char a,b;
    for(;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
}

void delay_us(unsigned int aa)
{
	while(aa--);
}

//小车右转
void right(unsigned char pwm)
{
	enA = 1;
	in1 = 0;
	in2 = 1;
	in3 = 0;
	in4 = 0;
	delay_us( pwm );
	
	enA = 1;
	in1 = 0;
	in2 = 0;
	in3 = 0;
	in4 = 0;
	delay_us( 100 - pwm ); 
}

//小车左转
void left(unsigned char pwm)
{
	enA = 1;
	in1 = 0;
	in2 = 0;
	in3 = 1;
	in4 = 0;
	delay_us( pwm );
	
	enA = 1;
	in1 = 0;
	in2 = 0;
	in3 = 0;
	in4 = 0;
	delay_us( 100 - pwm ); 
}

//小车后退
void back(unsigned char pwm)
{
	//enA = 1;
	enB = 1;
	in1 = 1;
	in2 = 0;
	in3 = 1;
	in4 = 0;
	delay_us( pwm );
	
	enA = 1;
	in1 = 0;
	in2 = 0;
	in3 = 0;
	in4 = 0;
	delay_us( 100 - pwm ); 
}

//小车前进
void forward(unsigned char pwm)
{
	//enA = 1;
	enB = 1;
	in1 = 0;
	in2 = 1;
	in3 = 0;
	in4 = 1;
	delay_us( pwm );
	
	enA = 1;
	in1 = 0;
	in2 = 0;
	in3 = 0;
	in4 = 0;
	delay_us( 100 - pwm ); 
}

//小车停止
void stop(void)
{
	enB = 1;
	in1 = 0;
	in2 = 0;
	in3 = 0;
	in4 = 0;
}

void get_model(uchar value)
{		   
   uchar shu1,value1;
	value1=value-48;
	//bai=value1/16;
	shu1=value1%16;


   switch(shu1)
   {
			case 1:model = 1;break;	//前进
			case 2:model = 2;break;	//左转
			case 3:model = 3;break;	//右转
			case 4:model = 4;break;	//后退
			case 5:model = 5;break;	//停止
			case 6:model = 6;break; //1挡
			case 7:model = 7;break; //2挡
			case 8:model = 8;break;	//3挡
   }

}	
	  
void init();   //串口初始化
void send(uchar a);	//单字节发送函数
void ctrl(); //接收处理函数

//void main()
//{
//	init();
//	//uint speed = 35;
//    while(1)
//    {         
//		get_model(SBUF);

//		if(model == 1)
//			forward(speed);
//		if(model == 2)
//			left(speed);
//		if(model == 3)
//			right(speed);
//		if(model == 4)
//			back(speed);
//		if(model == 5)
//			stop();
//		if(model == 6)
//			speed = 35;
//		if(model == 7)
//			speed = 70;
//		if(model == 8)
//			speed = 100;

//		if(RI==1)                     // 是否有数据到来
//		{
//			RI = 0;
//			ctrl();
//		}       
//	}
//}

void init()	//串口初始化
 {
 		  ES=0;							//关中断
		  SCON = 0x50;      // REN=1允许串行接受状态，串口工作模式1,
											  //10位UART（1位起始位，8位数据位，1位停止位，无奇偶校验），波特率可变

		  TMOD = 0x20;      // 定时器1工作于方式2，8位自动重载模式, 用于产生波特率
      TH1=TL1=0xFD;     // 波特率9600 （本次测试采用晶振为11.0592）
          
      PCON &= 0x7f;     // 波特率不倍增
      TR1 = 1;					//定时器1开始工作，产生波特率
											  //发送标志位置0
		  TI=0;		//接收标志位置0
		  RI=0;
		  
		  //EA=0;
	    ES=1;
 }
   
void send(unsigned char a)	//单字节数据发送
{							//注意：若单片机TXD（P3.1）无上拉能力，必须在P3.1端接上拉电阻。本次测试需要接上拉电阻
	TI=0;	
	SBUF=a;
	while(TI==0);
	TI=0;

	if(c%2)					//发送指示灯标志，每接收一次，此灯亮灭交替
		led7=1;
	else
		led7=0;
	c++;
} 

void ctrl()		            //接收处理函数
{
	switch(tmp){
		case '1':
			send(tmp);
			break;					
		case '2':					 //收到字符2，指示灯1灭
			send(tmp);
			break;
		case '3':				    //收到字符3，指示灯0、1亮
			send(tmp);
			break;
		case '4':					//收到字符4，指示灯0、1灭
			send(tmp);
			break;
		case '5':					//收到字符5，指示灯3亮
			send(tmp);
			break;
		default:                   //其他，灯全灭
			send(tmp);
	}
}
