#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

uchar tmp;

uint c=0, model;
uint speed = 35;

sbit led1=P1^0;		  //ָʾ��0
sbit led2=P1^1;			//ָʾ��1
sbit led3=P1^2;			//ָʾ��3
sbit led7=P1^7;			//ָʾ��3

sbit in1 = P0^0;
sbit in2 = P0^1;
sbit in3 = P0^2;
sbit in4 = P0^3;
sbit enA = P0^4;
sbit enB = P0^5;

void delay_ms(unsigned char c)   //��� 0us
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

//С����ת
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

//С����ת
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

//С������
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

//С��ǰ��
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

//С��ֹͣ
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
			case 1:model = 1;break;	//ǰ��
			case 2:model = 2;break;	//��ת
			case 3:model = 3;break;	//��ת
			case 4:model = 4;break;	//����
			case 5:model = 5;break;	//ֹͣ
			case 6:model = 6;break; //1��
			case 7:model = 7;break; //2��
			case 8:model = 8;break;	//3��
   }

}	
	  
void init();   //���ڳ�ʼ��
void send(uchar a);	//���ֽڷ��ͺ���
void ctrl(); //���մ�����

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

//		if(RI==1)                     // �Ƿ������ݵ���
//		{
//			RI = 0;
//			ctrl();
//		}       
//	}
//}

void init()	//���ڳ�ʼ��
 {
 		  ES=0;							//���ж�
		  SCON = 0x50;      // REN=1�����н���״̬�����ڹ���ģʽ1,
											  //10λUART��1λ��ʼλ��8λ����λ��1λֹͣλ������żУ�飩�������ʿɱ�

		  TMOD = 0x20;      // ��ʱ��1�����ڷ�ʽ2��8λ�Զ�����ģʽ, ���ڲ���������
      TH1=TL1=0xFD;     // ������9600 �����β��Բ��þ���Ϊ11.0592��
          
      PCON &= 0x7f;     // �����ʲ�����
      TR1 = 1;					//��ʱ��1��ʼ����������������
											  //���ͱ�־λ��0
		  TI=0;		//���ձ�־λ��0
		  RI=0;
		  
		  //EA=0;
	    ES=1;
 }
   
void send(unsigned char a)	//���ֽ����ݷ���
{							//ע�⣺����Ƭ��TXD��P3.1��������������������P3.1�˽��������衣���β�����Ҫ����������
	TI=0;	
	SBUF=a;
	while(TI==0);
	TI=0;

	if(c%2)					//����ָʾ�Ʊ�־��ÿ����һ�Σ��˵�������
		led7=1;
	else
		led7=0;
	c++;
} 

void ctrl()		            //���մ�����
{
	switch(tmp){
		case '1':
			send(tmp);
			break;					
		case '2':					 //�յ��ַ�2��ָʾ��1��
			send(tmp);
			break;
		case '3':				    //�յ��ַ�3��ָʾ��0��1��
			send(tmp);
			break;
		case '4':					//�յ��ַ�4��ָʾ��0��1��
			send(tmp);
			break;
		case '5':					//�յ��ַ�5��ָʾ��3��
			send(tmp);
			break;
		default:                   //��������ȫ��
			send(tmp);
	}
}
