// Определения кристалла
#include <iom48.h>   // Определения относящиеся к кристаллу

//-------------------------------------
//PINS DEFINITIONS  Порты ввода/вывода
//-------------------------------------

//  PORTB
#define dirb (0<<PB7)+(0<<PB6)+(0<<PB5)+(0<<PB4)+(0<<PB3)+(0<<PB2)+(0<<PB1)+(0<<PB0) // 1-out, 0-in
#define opb  (0<<PB7)+(0<<PB6)+(0<<PB5)+(0<<PB4)+(0<<PB3)+(0<<PB2)+(0<<PB1)+(0<<PB0) // 1-pull up on, 0-Z
#define PB_LED3   PB0  // O:
#define PB_LED2   PB1  // O:
#define PB_LED1   PB2  // O:
#define PB_LCD_A0 PB3  // O: LCD_A0
#define PB_LCDE   PB4  // O:
#define PB_LCDRW  PB5  // O:
#define PB_6      PB6  // NC- Osc
#define PB_7      PB7  // NC- Osc

//  PORTC
#define dirc (0<<PC6)+(0<<PC5)+(0<<PC4)+(0<<PC3)+(0<<PC2)+(0<<PC1)+(0<<PC0) // 1-out, 0-in
#define opc  (0<<PC6)+(0<<PC5)+(0<<PC4)+(0<<PC3)+(0<<PC2)+(0<<PC1)+(0<<PC0) // 1-pull up on, 0-Z
#define PC_LCD_DD4  PC0       // O: LCD DATA
#define PC_LCD_DD5  PC1       // O:
#define PC_LCD_DD6  PC2       // O:
#define PC_LCD_DD7  PC3       // O:
#define PC_SDA      PC4       // I:
#define PC_SCL      PC5       // I:
#define PC_RESET    PC6       // I: RESET

// PORTD
#define dird (0<<PD7)+(0<<PD6)+(0<<PD5)+(0<<PD4)+(0<<PD3)+(0<<PD2)+(0<<PD1)+(0<<PD0) // 1-out, 0-in
#define opd  (0<<PD7)+(0<<PD6)+(0<<PD5)+(0<<PD4)+(0<<PD3)+(0<<PD2)+(0<<PD1)+(0<<PD0) // 1-pull up on, 0-Z
#define PD_KEYB     PD0       // I: Вход последовательного порта
#define PD_TXD      PD1       // O: Выход последовательного порта
#define PD_LCD_ON   PD2       // O: Rs-485-TX Enable
#define PD_KEYA     PD3       // O:
#define PD_KEYC     PD4       // I:
#define PD_BUZZ     PD5       // O: Бузер
#define PD_LCDBL    PD6       // O: Подсветка LCD
#define PD_LED4     PD7       // X:

