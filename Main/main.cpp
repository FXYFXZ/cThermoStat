#include "main.h"
#include "OneWire.h"
#include "LCD.h"

/* Protos */
void LowLevelInit();
void Proc1Sec();
void Proc50ms();
void MeasureTemperatureProc();
void ThermoTatcicProc();

void ButtonProc(); // опрос кнопки


/* Locals */
const U8 MAX_TEMPERATURE = 0x2F;
const U8 MIN_TEMPERATURE = 20;
bool gl10ms = false;
#define TIMER_VALUE 0xFFFF-97

bool theTempIsValid = false;
U8 theTemperature = 0;
bool theButtonIsPressed = false;
LCD lcd;

bool theButtonPressed = false;
__eeprom TEEVars eevars = {
    0,
    28 // задатчик температуры
};


int main() {
  static U8 cnt50ms = 5;
  static U8 cntSec = 20;
  LowLevelInit();
  lcd.init();
  // Main Loop
    while(true) {
        if (gl10ms){ // 10 ms
            gl10ms = false;
            ButtonProc();
            if (--cnt50ms==0){  // 50 ms
                __watchdog_reset();
                cnt50ms = 5;
                Proc50ms();

                 if (--cntSec==0){  // 1s
                    cntSec = 20;
                    MeasureTemperatureProc();
                    Proc1Sec();

                 }
            }
        }
        __sleep();

    }
}


void Proc50ms(){
    lcd.drawAllProc(); // перерисовка 

    if (theButtonIsPressed) {
        theButtonIsPressed = false;
        if (++eevars.tZad > MAX_TEMPERATURE) eevars.tZad = MIN_TEMPERATURE;
    }
}

void Proc1Sec(){
    static bool secTgl = false;

    MeasureTemperatureProc();
    ThermoTatcicProc();

    lcd.printDec(MLT_C1, eevars.tZad);
    lcd.printChar(MLT_C3, CHR_GRAD);
   

    lcd.printDec(MLT_C5, theTemperature);
    lcd.printChar(MLT_C7, CHR_GRAD); 
    if (secTgl) {
        lcd.arr[MLT_C7] |= 0x10; // точка
    }
    secTgl = !secTgl; 


    if (BIT_TEST(PORTB, PB_BUZZ)) {
        lcd.arr[MLT_C9] = CHR_PG_HEAT_ON1 | CHR_PG_HEAT_ON2 | CHR_PG_HEAT_ON3; 
    }
    else {
        lcd.arr[MLT_C9] = 0;
    }
    lcd.arr[MLT_C10] = lcd.arr[MLT_C9];

}

// Тактика по температуре. Запускать при правильных показаниях
void ThermoTatcicProc(void){
    if ((!theTempIsValid)) {
        HEAT_OFF;
        return;
    }

    if (theTemperature >= eevars.tZad) {
        HEAT_OFF;
        BIT_CLR(PORTB, PB_LEDG2);
    }
    else {
        HEAT_ON;
        BIT_SET(PORTB, PB_LEDG2);
    }

}


void MeasureTemperatureProc(void){
    static bool mesOut = true;
    if (mesOut) {
        if (OW_DetectPresence()) {
             OW_SendByte(OW_1821_START_CONVERT_T); // star convert
        }
        else {
            theTempIsValid = false;
        }
    }
    else {
        if (OW_DetectPresence()) {
            OW_SendByte(OW_1821_READ_TEMPERATURE); // read Temperature
            theTemperature = OW_ReceiveByte();
            theTempIsValid = true;
        }
        else {
            theTempIsValid = false;
        }
    }
    mesOut= !mesOut;
}


void ButtonProc(){
    const U8 JITT_VALUE = 10;
    static U8 jitterIn; // на нажатие
    static U8 jitterOut; // на отпускание

    if (!theButtonIsPressed) {
        if (jitterOut) {
            if (!BUTTON_PRESSED) {
                if (--jitterOut==0) {
                    jitterIn = 0;
                }
            }
            else{
                jitterOut =JITT_VALUE;
            }
        }
        else{
            if (BUTTON_PRESSED) {
                if (++jitterIn >= JITT_VALUE) {
                    jitterIn = JITT_VALUE;
                    jitterOut =JITT_VALUE;
                    theButtonIsPressed = true;
                }
            }
            else {
                jitterIn = 0;
            }
        }
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

    _WDR();
    WDTCSR |= (1<<WDCE)|(1<<WDE);
    WDTCSR =  (1<<WDE)|(1<<WDP2)|(1<<WDP0); // 0.5 s

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




