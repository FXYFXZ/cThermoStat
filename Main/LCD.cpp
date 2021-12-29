#include "LCD.h"


#define A0_HIGH BIT_SET(PORTB, PB2)
#define A0_LOW  BIT_CLR(PORTB, PB2)
#define WR_HIGH BIT_SET(PORTB, PB0)
#define WR_LOW  BIT_CLR(PORTB, PB0)

#define MASK_DATA ((1<<PD2)|(1<<PD3)|(1<<PD4)|(1<<PD6))





// Знакогенератор
__flash char tblFonts[128] = {
//  0     1     2     3     4     5     6     7     8     9     A     B     С     D     E     F                  
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 0
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 1
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,  // 2
    0xEE, 0x60, 0x2F, 0x6D, 0xE1, 0xCD, 0xCF, 0x68, 0xEF, 0xED, 0xBE, 0xF8, 0xE8, 0x76, 0xF6, 0xB8,  // 3
    0x00, 0xEB, 0xC7, 0x8E, 0x67, 0x8F, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 4
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 5
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 6
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 7
};


void LCD::init(){
    setAddr(MLT_BLK);
    putNibble(0x01);
}



void LCD::printHex (TMLT_Cols myCol, U8 myVal){
    printNibble(myCol,myVal>>4);
    printNibble((TMLT_Cols)(myCol+1), myVal & 0xf);
}


void LCD::printNibble (TMLT_Cols myCol, U8 myVal){
    if (myVal > 0xF) return;
    char sym;
    if (myVal > 9) {
        sym = 'A'- 0xA + myVal;
    }
    else {
        sym = '0' + myVal;
    }
    printChar(myCol, sym);
}


void LCD::printChar(TMLT_Cols myCol, U8 myVal){
    arr[myCol] = tblFonts[myVal];
    _redraw = true;
}


// обновление экрана если есть изменения
void LCD::drawAllProc(){
    if (!_redraw) return;
    _redraw = false;
    setAddr(MLT_C1);
    for (U8 I = 0; I<MLT_COL_NUM; I++) {
        putData(arr[I]);
    }
}


void LCD::setAddr(U8 myAddr){
    A0_LOW;
    putNibble(myAddr);
    WR_HIGH;
    __delay_cycles(5);
    WR_LOW;  
    A0_HIGH;
    __delay_cycles(5);
}


void LCD::putData(U8 myData){
    A0_HIGH;
    putNibble(myData);
    WR_HIGH;
    __delay_cycles(5);
    WR_LOW;  
    putNibble(myData>>4);
    WR_HIGH;
    __delay_cycles(5);
    WR_LOW;  
}


// передать полубайт в шину
void LCD::putNibble(U8 myNibble){
    if (BIT_TEST(myNibble,0)) {
        BIT_SET(PORTD, PD6);
    }
    else{
        BIT_CLR(PORTD, PD6);
    }

    if (BIT_TEST(myNibble,1)) {
        BIT_SET(PORTD, PD4);
    }
    else{
        BIT_CLR(PORTD, PD4);
    }

    if (BIT_TEST(myNibble,2)) {
        BIT_SET(PORTD, PD3);
    }
    else{
        BIT_CLR(PORTD, PD3);
    }

    if (BIT_TEST(myNibble,3)) {
        BIT_SET(PORTD, PD2);
    }
    else{
        BIT_CLR(PORTD, PD2);
    }
}

