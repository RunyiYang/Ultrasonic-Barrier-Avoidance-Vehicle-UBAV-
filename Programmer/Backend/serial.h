#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <reg52.h>
#include <string.h>        //�ַ�����������
#include <intrins.h>
  
#define uchar unsigned char    // �궨��  51��Ƭ���ڴ���Դ����
#define uint  unsigned int    //�迼���ڴ���Դ���⣬��ʹ���޷�������
      

 
void uart_init();
void Delay_1ms(uint i);
void SendChar(uchar character);
void SendString(uchar *p); 
void delay(uint n);  //��ʱ����
void delayt(uint x);  //��ʱ����


#endif
