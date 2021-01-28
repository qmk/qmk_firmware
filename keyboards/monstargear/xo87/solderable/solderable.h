#define u8 uint8_t
#define u16 uint16_t

#pragma once

#include "quantum.h"

#define KEYLED_ROWS 6
#define KEYLED_COLS 16

#define XaxisMax 18
#define YaxisMax 6

#define RhythmLedColumMax 18

typedef struct{
	u8 onf;
	u8 hightLevel;
	u8 ColumHeight[RhythmLedColumMax];
}

RhythmLed_;

typedef struct{
	u8 r,g,b;
}

rgb_;
#define colorAGSize 10
#define colorBGSize RGBLED_NUM-10

typedef struct{
	rgb_ colorAG[colorAGSize];
    rgb_ colorBG[RGBLED_NUM-10];
}

backLedRgbG_;

#define Lseg0 E5
#define Lseg1 B4
#define Lseg2 B5
#define Lseg3 F0
#define Lseg4 C6
#define Lseg5 D5

#define Lcom0 C4
#define Lcom1 C2
#define Lcom2 C0
#define Lcom3 E0
#define Lcom4 D4
#define Lcom5 E4
#define Lcom6 B6
#define Lcom7 B2
#define Lcom8 F4
#define Lcom9 A0
#define Lcom10 F2
#define Lcom11 A4
#define Lcom12 F1
#define Lcom13 A7
#define Lcom14 D3
#define Lcom15 A3

extern void keyLedDriver(void);
extern void KeyLedCom(void);
u8 getKeyLedIndexForXY(u8 x,u8 y);

extern void ledCapsSet(bool onf);
extern void ledNumSet(bool onf);
extern void ledSollSet(bool onf);
void reflashLedState(void);
