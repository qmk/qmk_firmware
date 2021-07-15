#pragma once

#include "protocol.h"

// Struct defining an LED and its RGB color components
// Compatible with Shine firmware.
typedef union {
    struct {
        /* Little endian ordering to match uint32_t */
        uint8_t blue, green, red;
        /* Used in mask; nonzero means - use color from mask. */
        uint8_t alpha;
    } p; /* parts */
    /* Parts vector access: 0 - blue, 1 - green, 2 - red */
    uint8_t pv[4];
    /* 0xrgb in mem is b g r a */
    uint32_t rgb;
} annepro2Led_t;

#define ROWCOL2IDX(row, col) (NUM_COLUMN * (row) + (col))
#define NUM_COLUMN 14
#define NUM_ROW 5
#define KEY_COUNT 70

/* Local copy of ledMask, used to override colors on the board */
extern annepro2Led_t ledMask[KEY_COUNT];

/* Handle incoming messages */
extern void ledCommandCallback(const message_t *msg);

void annepro2SetIAP(void);
void annepro2LedDisable(void);
void annepro2LedEnable(void);
void annepro2LedSetProfile(uint8_t prof);
void annepro2LedGetStatus(void);
void annepro2LedNextProfile(void);
void annepro2LedPrevProfile(void);
void annepro2LedNextIntensity(void);
void annepro2LedNextAnimationSpeed(void);
void annepro2LedForwardKeypress(uint8_t row, uint8_t col);

/* Set single key to a given color; alpha controls which is displayed */
void annepro2LedMaskSetKey(uint8_t row, uint8_t col, annepro2Led_t color);
/* Push a whole local row to the shine */
void annepro2LedMaskSetRow(uint8_t row);
/* Synchronize all rows */
void annepro2LedMaskSetAll(void);

/* Set all keys to a given color */
void annepro2LedMaskSetMono(annepro2Led_t color);

/* Blink given key `count` times by masking it with a `color`. Blink takes `hundredths` of a second */
void annepro2LedBlink(uint8_t row, uint8_t col, annepro2Led_t color, uint8_t count, uint8_t hundredths);

/* Kept for compatibility, but implemented using masks */
void annepro2LedSetForegroundColor(uint8_t red, uint8_t green, uint8_t blue);
void annepro2LedResetForegroundColor(void);

typedef struct {
    uint8_t amountOfProfiles;
    uint8_t currentProfile;
    uint8_t matrixEnabled;
    uint8_t isReactive;
    uint8_t ledIntensity;
    uint8_t errors;
} annepro2LedStatus_t;

extern annepro2LedStatus_t annepro2LedStatus;
