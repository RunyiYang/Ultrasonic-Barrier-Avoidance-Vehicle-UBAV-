#ifndef __EEPROM_H__
#define __EEPROM_H__

#include <reg52.h>
#include <stdio.h>
#include "serial.h"

#define WREN 0x06 // д��ʹ��ָ��(WREN)
#define WRDI 0x04 // д���ָֹ��(WRDI)
#define WRSR 0x01 // д��״̬�Ĵ���ָ��(WRSR)
#define RDSR 0x05 // ��ȡ״̬�Ĵ���ָ��(RDSR)
#define WRITE 0x02 // д��洢��ָ��(WRITE)
#define READ 0x03 // ��ȡ�洢��ָ��(READ)
                    
#define STATUS_REG 0x00 // Ҫд�뵽״̬�Ĵ�����ֵ 
#define MAX_POLL 0x99 // ����ѯ����m number of

//x5045��51�����ӷ���
sbit CS = P2^4; 
sbit SO = P2^5;
sbit SI = P2^6;
sbit SCK = P2^7; 

//����Ĵ���ָ��
void outbyte(unsigned char);
unsigned char inbyte();
void wren_cmd();
void wrdi_cmd();
unsigned char rdsr_cmd();
void wip_poll();
void wrsr_cmd();
void byte_write(unsigned int, unsigned char);
unsigned char byte_read(unsigned int);
void comwrite(uchar com);   //дָ���
void datwrite(uchar dat);   //д���ݺ���
void init_serialcomm(void);
void send_char_com(unsigned int);
 

#endif
