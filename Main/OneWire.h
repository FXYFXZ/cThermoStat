/*****************************************************************************
����: OneWire.h
Creted by PROTTOSS
Mail to PROTTOSS@mail.ru
������������ ���� ��� ������ ���������� DALLAS 1-Wire
09.01.2006
******************************************************************************/
#ifndef __ONEWIRE_H_
#define __ONEWIRE_H_

#include "stdBool.h"

// ����������� ������ ��� ���� 1-wire
#define OW_PORT PORTD
#define OW_DDR  DDRD
#define OW_PIN  PIND

//#define OW_BUS  PD3
//#define OW_BUS_MASK (1 << OW_BUS)

/*****************************************************************************  
��������� �������
*****************************************************************************/


void OW_SendByte(char data); // ������� ����� � �����
bool OW_DetectPresence(void);// ����� � ����������� ���������� �� ����
char OW_ReceiveByte(void); // ����� ����� � �����

/*****************************************************************************
����������� ��� ���������� DS1821
*****************************************************************************/
#define OW_1821_TH_LIMIT            99// ������ 125, �� ��� ��������� ������ >99
#define OW_1821_TL_LIMIT            55

/*****************************************************************************
������� ��� ���������� DS1821
*****************************************************************************/
#define OW_1821_READ_TEMPERATURE    0xAA// ������ ���������� ��������� �����������
#define OW_1821_WRITE_TH            0x01// ������ �������� ������� �����������
#define OW_1821_WRITE_TL            0x02// ������ ������� ������� ����������
#define OW_1821_READ_TH             0xA1// ������ �������� ������� �����������
#define OW_1821_READ_TL             0xA2// ������ ������� ������� ����������
#define OW_1821_WRITE_STATUS        0x0C// ������ ������������ � ������� ������������
#define OW_1821_READ_STATUS         0xAC// ������ ������������ �� �������� ������������
#define OW_1821_START_CONVERT_T     0xEE// ������������� ��������� �����������
#define OW_1821_STOP_CONVERT_T      0x22// ����������� ��������� �����������

#endif//__ONEWIRE_H_
