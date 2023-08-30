#include <reg52.h>
#include <stdio.h>
#include "chao.h"
#include "serial.h"

unsigned char count;       
long int distance;

void trigger()   //������ģ�鴥������
{
	trig=1;      //�򿪳����������˿�
	delay(2);
	trig=0;      //�رճ����������˿�
}

void measure_init()  //����������ʼ��
{
	trig=0;   //�����˿ڵ͵�ƽ
	echo=0;   //���ն˿ڵ͵�ƽ
	count=0;  
}

void measure()    //��ຯ��
{
	uchar a;
	uint b,c;
	TR0=1;   //�򿪶�ʱ��
	while(echo)   //�����������մ�ʱ��ʱ
	{
		;
	}
	TR0=0;   //�رն�ʱ��
	a=TL0;   //a��b�ֱ����жϺ����߰�λ�͵ڰ�λ��ʱ�����ֵ
	b=TH0;
	c=(b<<8)+a;  //�߰�λ���ư�λ֮����Ͱ�λ���ӷ�����
	c=c-0xfc66;  //��ȥ��ʼֵ�߰�λ�͵Ͱ�λ
	distance=c+1000*count;  //�ܵ�ʱ��,��λ�Ǧ�s
	TL0=0x66;    //����װ���ʼֵ
	TH0=0xfc;
	delayt(30);
	distance=3453*distance/20000; //������룬��λ��cm
}

//�������ԭ��:����t ��s,distance=t*0.34(����340m/s=0.34cm/��s)/2  

