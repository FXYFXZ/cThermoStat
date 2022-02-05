#ifndef MAIN_H
#define MAIN_H

#include "board.h"
#include "ina90.h"
//#include "stdBool.h"
#include "FlnCMac.h"

#define CODE_VERSION_NUM 2 // номер версии прошивки

typedef struct {
    U8 tZad; // Заданная температура
} TEEVars;

typedef unsigned char TThermo;

// export main
void UTIL_WaitTimeInUs(unsigned long mck, unsigned int time_us);


#endif
