#ifndef __EEPROM_H__
#define __EEPROM_H__

#include <reg52.h>
#include <stdio.h>
#include "serial.h"

#define WREN 0x06 // 写入使能指令(WREN)
#define WRDI 0x04 // 写入禁止指令(WRDI)
#define WRSR 0x01 // 写入状态寄存器指令(WRSR)
#define RDSR 0x05 // 读取状态寄存器指令(RDSR)
#define WRITE 0x02 // 写入存储器指令(WRITE)
#define READ 0x03 // 读取存储器指令(READ)
                    
#define STATUS_REG 0x00 // 要写入到状态寄存器的值 
#define MAX_POLL 0x99 // 最大查询次数m number of

//x5045和51的连接方法
sbit CS = P2^4; 
sbit SO = P2^5;
sbit SI = P2^6;
sbit SCK = P2^7; 

//定义寄存器指令
void outbyte(unsigned char);
unsigned char inbyte();
void wren_cmd();
void wrdi_cmd();
unsigned char rdsr_cmd();
void wip_poll();
void wrsr_cmd();
void byte_write(unsigned int, unsigned char);
unsigned char byte_read(unsigned int);
void comwrite(uchar com);   //写指令函数
void datwrite(uchar dat);   //写数据函数
void init_serialcomm(void);
void send_char_com(unsigned int);
 

#endif
