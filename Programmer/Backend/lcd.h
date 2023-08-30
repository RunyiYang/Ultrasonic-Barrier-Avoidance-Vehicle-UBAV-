#ifndef __LCD_H__
#define __LCD_H__

#include <reg52.h>
#include <stdio.h>  // ��ӡ�ַ�����Ҫ���� stdio.h ��

#define uint unsigned int
#define uchar unsigned char


void lcd_init();   					//LCD1602��ʼ��
void disp_state();   				//��ʾ�̶��ַ�
void echodisplay(uint x);   //��ʾ���뺯��
void display();							//��ʾ"NO obctacles"
void disp_distance();				//��ʾ����̶��ַ�
void lcd_show(long int,long int);//��������趨����ʾ��NO obctacles��������С���趨����ʾ����

#endif