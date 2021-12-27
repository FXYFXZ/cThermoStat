#include "main.h"
//#include "OneWire.h"

extern "C" {
    bool OW_DetectPresence(void);// сброс и определение устройства на шине
    char OW_ReceiveByte(void); // прием байта с линии
}


/* Protos */
void LowLevelInit();
void SecondProc();
void Proc50ms();

/* Locals */
bool gl10ms = false;
#define TIMER_VALUE 0xFFFF-97

int main() {
  static U8 cnt50ms = 5;
  static U8 cntSec = 20;
  LowLevelInit();

    // Main Loop
    while(true) {
        if (gl10ms){ // 10 ms
            gl10ms = false;
            if (--cnt50ms==0){  // 50 ms
                cnt50ms = 5;
                Proc50ms();


                 if (--cntSec==0){  // 1s
                    cntSec = 20;
                    SecondProc();

                 }
            }
        }
    }
}


void Proc50ms(){
    BIT_XOR(PORTD, PD_LEDR1);

}


void SecondProc(){

    if (OW_DetectPresence()) {
        BIT_SET(PORTD, PD_LEDR5);
    }
    else {
        BIT_CLR(PORTD, PD_LEDR5);
    }







}




void Port_Setup (void){
    DDRB = dirb;
    PORTB = opb;

    DDRC = dirc;
    PORTC = opc;

    DDRD = dird;
    PORTD = opd;
}

void LowLevelInit(){
    __disable_interrupt();
    ACSR = (1<<ACD);   // Выключение аналогового компаратора
//  _WDR();
//  WDTCSR |= (1<<WDCE)|(1<<WDE);
//  WDTCSR =  (1<<WDE)|(1<<WDP2)|(1<<WDP0); // 0.5 s
    Port_Setup();

    EEAR = 0x00; // Установка регистра адреса EEPROM на нулевую ячейку
    EECR = 0x00;

    // Timers setup
    TCCR1B = (1<<CS12)+(0<<CS11)+(1<<CS10);  //
    TCNT1 = TIMER_VALUE;                     //
    TIMSK1 |= (1<<TOIE1);


    __enable_interrupt();
}


// прерывание системного таймера 10 ms
#pragma vector = TIMER1_OVF_vect
__interrupt void TIMER1_OVF_interrupt(void) {
    TCNT1 = TIMER_VALUE; // load for next interval
    gl10ms = true;
}


