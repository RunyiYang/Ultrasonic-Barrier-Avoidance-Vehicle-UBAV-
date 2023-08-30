#include <reg52.h>
#include <stdio.h>
#include "eeprom.h"
#include <string.h>
#include "init.h"

//����Ĵ���ָ��
void outbyte(unsigned char write_data)
{
     unsigned char i; 
      for(i = 0; i < 8; i++)
     {
      SCK = 0;
      SI = (bit)(write_data & 0x80); //����һ��λ��SI
     write_data <<= 1; 
      SCK = 1; 
     }
      SI = 0; 
} 
unsigned char inbyte()
{
     unsigned char i;
     unsigned char read_data=0;
for(i = 0; i < 8; i++)
     {
        SCK = 0;
        read_data <<= 1;
        SCK = 1;
        read_data |= (unsigned char)SO; 
     }
     return read_data;
}

void wren_cmd()
{
	CS = 0;
	outbyte(WREN); //����д��ʹ��ָ��
	CS = 1;
}

void wrdi_cmd()
{
	CS = 0;
	outbyte(WRDI); //����д���ָֹ��
	CS = 1;
}

unsigned char rdsr_cmd()
{
	unsigned char status;
	CS = 0;
	outbyte(RDSR);  //����״̬�Ĵ�����ȡָ��
	status = inbyte();  //��ȡ״̬�Ĵ�
	CS = 1;
	return status;
}

void wip_poll()
{
	unsigned char i; // �������Ĳ�ѯ����
	// ���WIPλΪ��1������δ�ﵽ����ѯ�������������ѯ
	// ���WIPλΪ��0������д��������ɣ�����
	for(i = 0; i < MAX_POLL; i++)
	{
		if(rdsr_cmd() & 0x01) // ��ȡ״̬�Ĵ���
		{
			continue;
		}
		return;
	}
}
void wrsr_cmd()
{
	CS = 0;
	outbyte(WRSR); // ����״̬�Ĵ���д��ָ��
	outbyte(STATUS_REG); // ����Ҫд�������
	CS = 1;
	wip_poll(); // ���д�����
}
void byte_write(unsigned int addr, unsigned char dat)
{
	wren_cmd();
	CS = 0;
	outbyte(WRITE); // ����д��ָ��͵�ַ���λ��0��
	outbyte(addr); // ���͵�ַ���ֽ�
	outbyte(dat); // ���������ֽ�

	CS = 1;
	wip_poll(); // ���д�����
}

unsigned char byte_read(unsigned int addr)
{
	unsigned char read_data;
	CS = 0;
	
	if(addr & 0x100)
		outbyte(READ | 0x08); // ���Ͷ�ȡָ��͵�ַ���λ��1��
	else
		outbyte(READ); // ���Ͷ�ȡָ��͵�ַ���λ��0��

	outbyte(addr); // ���͵�ַ���ֽ�
	read_data = inbyte(); // ��ȡ�ֽ�
	CS = 1;
	
	return read_data;
}



void comwrite(uchar com)   //дָ���
{
	rs=0;   //ѡ��ָ��Ĵ���
	rw=0;   //ѡ��д
	P0=com; //����ָ��
	delay(5);
	en=1;  //ʹ�ܶ˴�
	en=0;  //ʹ�ܶ˹ر�
}

void datwrite(uchar dat)   //д���ݺ���
{
	rs=1;    //ѡ�����ݼĴ���
	rw=0;    //ѡ��д
	P0=dat;  //��������
	delay(5);
	en=1;    //ʹ�ܶ˴�
	en=0;    //ʹ�ܶ˹ر�
}


