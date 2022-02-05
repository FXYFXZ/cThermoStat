#ifndef __LCD_H_INCL__
#define __LCD_H_INCL__

#include "main.h"
#include <string.h>

// Индикатор МЭЛТ MT?10T7, MT?10T8, MT?10T9


#define MLT_COL_NUM 10


enum {
    CHR_GRAD = '&', // градусы
    CHR_PG_POINT = 0x10,
    CHR_PG_HEAT_ON1 = 0x04,
    CHR_PG_HEAT_ON2 = 0x01,
    CHR_PG_HEAT_ON3 = 0x08,
};


// колонки
typedef enum {
    MLT_C1,
    MLT_C2,
    MLT_C3,
    MLT_C4,
    MLT_C5,
    MLT_C6,
    MLT_C7,
    MLT_C8,
    MLT_C9,
    MLT_C10,
    MLT_BLK = 0xF,
} TMLT_Cols;


class LCD {
public:
    LCD(); // Constructor
    U8 arr[MLT_COL_NUM]; // screen memory
    void drawAllProc();
    void init();
    void Clear();

    void printHex (TMLT_Cols myCol, U8 myVal);
    void printDec (TMLT_Cols myCol, U8 myVal);
    void printNibble (TMLT_Cols myCol, U8 myVal);
    void printChar(TMLT_Cols myCol, U8 myVal);

private:
    void setAddr(U8);
    void putData(U8);
    void putNibble(U8);
    bool _redraw;
};

// Constructor implementation
inline LCD::LCD() {
    Clear();
}

inline void LCD::Clear(){
    memset(arr, 0, MLT_COL_NUM);
    _redraw = true;
}


#endif // __LCD_H_INCL__
