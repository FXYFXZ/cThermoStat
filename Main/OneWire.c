/****************************************************************************
����: OW.h
Creted by PROTTOSS
Mail to PROTTOSS@mail.ru
������ ���������� DALLAS 1-Wire
09.01.2006

!!! �������� !!!
����������� ���� OW_WIRE � ������ OW_PORT � PORTD ������ ���� �������,
� ����� OW_WIRE ������ ���� ��������� ������������� �������� ��������� 4,7���
*****************************************************************************/

#include "main.h"
#include "OneWire.h"


/*****************************************************************************
�������� Bit � ������������� Transfer Layer, ��������������� � AN126 �� Dallas Semicondactors
� � AN318 �� ATMEL
*****************************************************************************/
#define OW_DEL_A        6
#define OW_DEL_B        64
#define OW_DEL_C        60
#define OW_DEL_D        10
#define OW_DEL_E        9
#define OW_DEL_F        55
#define OW_DEL_G        0
#define OW_DEL_H        480
#define OW_DEL_I        70
#define OW_DEL_J        410
/*****************************************************************************
��������� �������
*****************************************************************************/


// external
void UTIL_WaitTimeInUs(unsigned long mck, unsigned int time_us);

void OW_Init(void);     // �������������
void OW_WriteBit1(void); // ������ �� ���� 1
void OW_WriteBit0(void); // ������ �� ���� 0
bool OW_ReadBit(void); // ������ ���� � ����

void OW_SendByte(char data); // ������� �����
bool OW_DetectPresence(void);// ����� � ����������� ���������� �� ����
char OW_ReceiveByte(void); // ����� ����� � �����


#define BUS_SET_0       BIT_SET(DDRD, PD_TM)
#define BUS_RELEASE     BIT_CLR(DDRD, PD_TM)
#define BUS_GETPIN      BIT_TEST(PIND,PD_TM)


/*****************************************************************************
������ �� ���� 1
���� ������ ���� ����������� � 0 �� ����� 1-15 ���
*****************************************************************************/
void OW_WriteBit1(void) {
    BUS_SET_0; // ������������� ���� � ����
    UTIL_WaitTimeInUs(BOARD_MCK,OW_DEL_A);// �������� A ���������� ���� � 0
    BUS_RELEASE;//  ����������� ����
    UTIL_WaitTimeInUs(BOARD_MCK,OW_DEL_B);// �������� B �� ��������� ���������
}

/*****************************************************************************
������ �� ���� 0
���� ������ ���� ����������� � 0 �� ����� 60-120 ���
*****************************************************************************/
void OW_WriteBit0(void) {
    BUS_SET_0;// ������������� ���� � ����
    UTIL_WaitTimeInUs(BOARD_MCK,OW_DEL_C);// �������� C ���������� ���� � 0
    BUS_RELEASE;//  ����������� ����
    UTIL_WaitTimeInUs(BOARD_MCK,OW_DEL_D);// �������� D �� ��������� ���������
}

/*****************************************************************************
������ ������ ����
���� ������ ���� ����������� � 0 �� ����� 1-15 ���. ����� �����, � �������
15 ��� ���������� ������ ���������� ���� � 0, ���� ��������� ������� 0, ����
��������� ������� 1, ���������� �� ������ ������� �������� �� ����
�����:  status �������� ��������� ���� (0 ��� 0 ��� �� 0 ��� 1)
******************************************************************************/
bool OW_ReadBit(void){
    bool status;
    BUS_SET_0;// ������������� ���� � ����
    // �������� A ���������� ���� � 0
    UTIL_WaitTimeInUs(BOARD_MCK,OW_DEL_A);
    BUS_RELEASE;//  ����������� ����

    // �������� E �� ��������� �������� ������� �� �����
    UTIL_WaitTimeInUs(BOARD_MCK,OW_DEL_E);

    // ������ ��������� ����
    status = BUS_GETPIN != 0;

    // �������� F �� ��������� ���������
    UTIL_WaitTimeInUs(BOARD_MCK,OW_DEL_F);

    return status;
}

/*****************************************************************************
������� ����� � ����������
*****************************************************************************/
void OW_SendByte(char data)
{   char count;

    // ��������� ������� ���
    count = 8;

    // ���� ������ ��� �� ����
    do
    {   //������� ��������� ��� ������� � ��������
        if(data & 0x01)
        {   OW_WriteBit1();
        }
        else
        {   OW_WriteBit0();
        }

        // �������� ������ ������ � ��������� ��������� �����
        data >>= 1;
    }
    while(--count);
}

/*****************************************************************************
����������� ���������� �� ����. ���������� ����, ������������� ���� � �������
�������� ������������ ����������
*****************************************************************************/
bool OW_DetectPresence(void)
{   bool status;
    // ���� ���� � ����, �� ������� ��� ��� �������
    if (BUS_GETPIN == 0) {
        return false;
    }

    BUS_SET_0;// ������������� ���� � ����
    // �������� H ���������� ���� � 0
    UTIL_WaitTimeInUs(BOARD_MCK,OW_DEL_H);
    //  ����������� ����
    BUS_RELEASE;

    // �������� I �� ��������� ���������
    UTIL_WaitTimeInUs(BOARD_MCK,OW_DEL_I);

    // ������ ��������� ����
    status = (BUS_GETPIN  == 0);

    // �������� J �� ��������� ���������
    UTIL_WaitTimeInUs(BOARD_MCK,OW_DEL_J);

    return status;
}

/*****************************************************************************
����� ����� �� ����������.
���������� �������� ����.
*****************************************************************************/
char OW_ReceiveByte(void)
{
    U8 count;
    U8 data;

    //��������� ������� ���
    count = 8;

    // ���� ������ ��� � ����
    do
    {   // �������� ������ ������
        data >>= 1;

        // ��������� ��� � ����� ������
        if(OW_ReadBit())
        {   data |= 0x80;
        }
    }
    while(--count);

    return data;
}

void UTIL_WaitTimeInUs(unsigned long mck, unsigned int time_us){
    while (time_us--) {
        __delay_cycles(10);
    }
}


