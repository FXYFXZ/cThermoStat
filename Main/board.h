// Определения кристалла
#include <iom48.h>   // Определения относящиеся к кристаллу

//-------------------------------------
//PINS DEFINITIONS  Порты ввода/вывода
//-------------------------------------

#define BOARD_MCK 10000000


//  PORTB
#define dirb (0<<PB7)+(0<<PB6)+(0<<PB5)+(1<<PB4)+(0<<PB3)+(1<<PB2)+(1<<PB1)+(1<<PB0) // 1-out, 0-in
#define opb  (0<<PB7)+(0<<PB6)+(0<<PB5)+(0<<PB4)+(0<<PB3)+(0<<PB2)+(0<<PB1)+(0<<PB0) // 1-pull up on, 0-Z
#define PB_LEDG2  PB0  // O: LED Green 2
#define PB_485TXE PB1  // O:
#define PB_LEDR4  PB2  // O: LED Red 4
#define PB_BUZZ   PB3  // O:
#define PB_LEDY1  PB4  // O:
#define PB_5      PB5  // O:
#define PB_6      PB6  // NC- Osc
#define PB_7      PB7  // NC- Osc

//  PORTC
#define dirc (0<<PC6)+(0<<PC5)+(0<<PC4)+(0<<PC3)+(0<<PC2)+(0<<PC1)+(0<<PC0) // 1-out, 0-in
#define opc  (0<<PC6)+(1<<PC5)+(1<<PC4)+(1<<PC3)+(1<<PC2)+(1<<PC1)+(1<<PC0) // 1-pull up on, 0-Z
#define PC_BUTTON   PC0       // O:
#define PC_J1       PC1       // O:
#define PC_J2       PC2       // O:
#define PC_J3       PC3       // O:
#define PC_SDA      PC4       // I:  J4
#define PC_SCL      PC5       // I:  J5
#define PC_RESET    PC6       // I: RESET

// PORTD
#define dird (1<<PD7)+(1<<PD6)+(0<<PD5)+(1<<PD4)+(1<<PD3)+(1<<PD2)+(0<<PD1)+(0<<PD0) // 1-out, 0-in
#define opd  (0<<PD7)+(0<<PD6)+(0<<PD5)+(0<<PD4)+(0<<PD3)+(0<<PD2)+(0<<PD1)+(0<<PD0) // 1-pull up on, 0-Z
#define PD_0        PD0       // I:
#define PD_1        PD1       // O:
#define PD_LEDR1    PD2       // O:
#define PD_LEDR5    PD3       // O:
#define PD_LEDR2    PD4       // I:
#define PD_TM       PD5       // O: TM
#define PD_LEDG1    PD6       // O:
#define PD_LEDR3    PD7       // X:

// Включение, выключение нагрева
#define HEAT_ON  BIT_SET(PORTB, PB_LEDY1)
#define HEAT_OFF BIT_CLR(PORTB, PB_LEDY1)

#define J1 (BIT_TEST(PINC, PC_J1)==0)
#define J2 (BIT_TEST(PINC, PC_J2)==0)

#define BUTTON_PRESSED (BIT_TEST(PINC, PC_BUTTON)==0)
