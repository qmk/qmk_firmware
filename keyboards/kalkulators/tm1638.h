#pragma once

extern const unsigned char * pFontSevenSegptr;

#define TextAlignment "TMAlignTextRight"

#define TM_ACTIVATE 0x8F /**<  Start up device */
#define TM_BUTTONS_MODE 0x42 /**<  Buttons mode */
#define TM_WRITE_LOC 0x44 /**<  Write to a memory location */
#define TM_WRITE_INC 0x40 /**<  Incremental write */
#define TM_SEG_ADR 0xC0  /**<  leftmost segment Address C0 C2 C4 C6 C8 CA CC CE */
#define TM_LEDS_ADR 0xC1  /**<  Leftmost LED address C1 C3 C5 C7 C9 CB CD CF */
#define TM_BRIGHT_ADR 0x88 /**<  Brightness address */
#define TM_BRIGHT_MASK 0x07 /**<  Brightness mask  */
#define TM_DEFAULT_BRIGHTNESS 0x02 /**< Brightness can be 0x00 to 0x07 , 0x00 is least bright */
#define TM_DISPLAY_SIZE 8 /**< Size of display in digits */

#define TM_ASCII_OFFSET 32 /**<  ASCII table offset to jump over first missing 32 chars */
#define TM_HEX_OFFSET   16 /**<  ASCII table offset to reach the number position */
#define TM_DOT_MASK_DEC    128 /**<  0x80 Mask to  switch on decimal point in seven segement  */

#define TM_RED_LED 0x02      /**<  Turn LED red color Model 3 only */
#define TM_GREEN_LED 0x01 /**<  Turn LED green color Model 3 only */
#define TM_OFF_LED 0x00     /**<  Switch off LED  */

void displayBegin(void);
void reset(void);  
void brightness(uint8_t brightness);
void sendCommand(uint8_t value);
void sendData(uint8_t data);
void shiftOut(uint8_t val);
void display7Seg(uint8_t position, uint8_t value);
void displayASCIIwDot(uint8_t position, uint8_t ascii);
void displayASCII(uint8_t position, uint8_t ascii);
void displayText(const char *text);
void displayTextRight(const char *text);
void displayTextRightFloat(const char *text);
void displayIntNum(unsigned long number, bool leadingZeros);
void displayHex(uint8_t position, uint8_t hex);
void DisplayDecNumNibble(uint16_t  numberUpper, uint16_t numberLower, bool leadingZeros);
