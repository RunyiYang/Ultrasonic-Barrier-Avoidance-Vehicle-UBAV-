#include <reg52.h>
#include <stdio.h>  // ��ӡ�ַ�����Ҫ���� stdio.h ��
#include <intrins.h>
#include "eeprom.h"
#include "lcd.h"
#include "chao.h"


unsigned char code table[]={"0123456789"};
extern uchar receive_data[10];
//extern long int distance_set;

void lcd_init()   //LCD1602��ʼ��
{
	comwrite(0x38);   //����16*2��ʾ��8λ���ݶ˿�
	comwrite(0x0c);   //����ʾ�����򿪹��
	comwrite(0x06);   //��ʾ��ַ������д��һ������֮����ʾλ������
	comwrite(0x01);   //����
}

void disp_state()   //��ʾ�̶��ַ�
{
	comwrite(0x80);   //�趨����λ��
	datwrite('S');         //������''����������""
	datwrite('t');
	datwrite('a');
	datwrite('t');
	datwrite('e');
	datwrite(':');
	datwrite(receive_data[0]);
	
	comwrite(0x80+0x07);	
	datwrite(' ');
	datwrite('S');
	datwrite('p');
	datwrite('e');
	datwrite('e');
	datwrite('d');
	datwrite(':');
	datwrite(receive_data[1]);
}
	
void disp_distance(){
	comwrite(0x80+0x40);   //�趨����λ��
	datwrite('d');         //������''����������""
	datwrite('i');
	datwrite('s');
	datwrite('t');
	datwrite('a');
	datwrite('n');
	datwrite('c');
	datwrite('e');
	datwrite(':');
	comwrite(0x80+0x4c);    //�趨����λ��
	datwrite('.');
	comwrite(0x80+0x4e);    //�趨����λ��
	datwrite('c');
	datwrite('m');
}

void echodisplay(uint x)   //��ʾ���뺯��
{
	uchar q,b,s,g;
	q=x/1000;            //������������õ�distance��Ϊ��λ��ʮλ����λ��ǧλ
	b=(x/100)%10;
	s=(x/10)%10;
	g=x%10;
	
	receive_data[2] = q + 0x30;
	receive_data[3] = b + 0x30;
	receive_data[4] = s + 0x30;
	receive_data[5] = g + 0x30;
	
	comwrite(0x80+0x49);    //�趨���λ��
	datwrite(table[q]);     //д������
	datwrite(table[b]);
	datwrite(table[s]);
	comwrite(0x80+0x4d);    //�趨����λ��
	datwrite(table[g]);     //д������
}

void display(){				//��������趨ֵ����ʾ"NO obctacles"
	comwrite(0x80+0x40);   //�趨����λ��
	datwrite('N');
	datwrite('0');
	datwrite(' ');
	datwrite('o');
	datwrite('b');
	datwrite('s');
	datwrite('t');
	datwrite('a');
	datwrite('c');
	datwrite('l');
	datwrite('e');
	datwrite('s');
	datwrite(' ');
	datwrite(' ');
	datwrite(' ');
	datwrite(' ');
}

void lcd_show(long int distance,long int distance_set) 
	{
			if(distance >= distance_set){
				disp_state();
				display();
				receive_data[2] = '$';
				measure_init();//�ٴγ�ʼ�����ģ��
				delayt(50);//�������50ms
			}
			else{
				disp_state();
				disp_distance();     //��ʾ�̶��ַ�
				
				echodisplay(distance);//��ʾ����distance
				measure_init();//�ٴγ�ʼ�����ģ��
				delayt(50);//�������50ms
			}
}
