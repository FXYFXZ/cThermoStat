#ifndef MAIN_H
#define MAIN_H

#include "board.h"
#include "ina90.h"
//#include "stdBool.h"
#include "FlnCMac.h"



typedef struct {
    U8 empty;
    U8 tZad; // Заданная температура
} TEEVars;


// export main
void UTIL_WaitTimeInUs(unsigned long mck, unsigned int time_us);


#endif
