#include "main.h"


/* Protos */
void LowLevelInit();



int main() {
  LowLevelInit();
  while(true);
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

    __enable_interrupt();
}


