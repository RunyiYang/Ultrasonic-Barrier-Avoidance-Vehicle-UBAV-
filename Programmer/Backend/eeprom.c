#include <reg52.h>
#include <stdio.h>
#include "eeprom.h"
#include <string.h>
#include "init.h"

//定义寄存器指令
void outbyte(unsigned char write_data)
{
     unsigned char i; 
      for(i = 0; i < 8; i++)
     {
      SCK = 0;
      SI = (bit)(write_data & 0x80); //传送一个位到SI
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
	outbyte(WREN); //传送写入使能指令
	CS = 1;
}

void wrdi_cmd()
{
	CS = 0;
	outbyte(WRDI); //传送写入禁止指令
	CS = 1;
}

unsigned char rdsr_cmd()
{
	unsigned char status;
	CS = 0;
	outbyte(RDSR);  //传送状态寄存器读取指令
	status = inbyte();  //读取状态寄存
	CS = 1;
	return status;
}

void wip_poll()
{
	unsigned char i; // 设置最大的查询次数
	// 如果WIP位为‘1’并且未达到最大查询次数，则继续查询
	// 如果WIP位为‘0’，则写入周期完成，返回
	for(i = 0; i < MAX_POLL; i++)
	{
		if(rdsr_cmd() & 0x01) // 读取状态寄存器
		{
			continue;
		}
		return;
	}
}
void wrsr_cmd()
{
	CS = 0;
	outbyte(WRSR); // 传送状态寄存器写入指令
	outbyte(STATUS_REG); // 传送要写入的数据
	CS = 1;
	wip_poll(); // 检测写入进度
}
void byte_write(unsigned int addr, unsigned char dat)
{
	wren_cmd();
	CS = 0;
	outbyte(WRITE); // 传送写入指令和地址最高位‘0’
	outbyte(addr); // 传送地址低字节
	outbyte(dat); // 传送数据字节

	CS = 1;
	wip_poll(); // 检测写入进度
}

unsigned char byte_read(unsigned int addr)
{
	unsigned char read_data;
	CS = 0;
	
	if(addr & 0x100)
		outbyte(READ | 0x08); // 传送读取指令和地址最高位‘1’
	else
		outbyte(READ); // 传送读取指令和地址最高位‘0’

	outbyte(addr); // 传送地址低字节
	read_data = inbyte(); // 读取字节
	CS = 1;
	
	return read_data;
}



void comwrite(uchar com)   //写指令函数
{
	rs=0;   //选择指令寄存器
	rw=0;   //选择写
	P0=com; //输入指令
	delay(5);
	en=1;  //使能端打开
	en=0;  //使能端关闭
}

void datwrite(uchar dat)   //写数据函数
{
	rs=1;    //选择数据寄存器
	rw=0;    //选择写
	P0=dat;  //输入数据
	delay(5);
	en=1;    //使能端打开
	en=0;    //使能端关闭
}


