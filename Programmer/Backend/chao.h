#ifndef __CHAO_H__
#define __CHAO_H__

#include <reg52.h>


#define uint unsigned int
#define uchar unsigned char

sbit trig=P1^3;   //��������������  
sbit echo=P1^6;   //��������������  



void measure();    		//��ຯ��
void trigger();  	 		//������ģ�鴥������
void measure_init();  //����������ʼ��



#endif
