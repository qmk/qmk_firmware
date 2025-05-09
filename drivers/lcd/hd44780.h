/*
Copyright 2022

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * \file
 *
 * \defgroup hd44780 HD44780 Character LCD Driver
 * \{
 */

/*
 * HD44780 instructions
 * https://www.sparkfun.com/datasheets/LCD/HD44780.pdf
 * Table 6 (p24)
 */
// Clear display
#define HD44780_CMD_CLEAR_DISPLAY 0x01
// Return home
#define HD44780_CMD_RETURN_HOME 0x02
// Entry mode set
#define HD44780_CMD_ENTRY_MODE 0x04
#define HD44780_ENTRY_MODE_INC 0x02   // I/D
#define HD44780_ENTRY_MODE_SHIFT 0x01 // S
// Display on/off control
#define HD44780_CMD_DISPLAY 0x08
#define HD44780_DISPLAY_ON 0x04     // D
#define HD44780_DISPLAY_CURSOR 0x02 // C
#define HD44780_DISPLAY_BLINK 0x01  // B
// Cursor or display shift
#define HD44780_CMD_MOVE 0x10
#define HD44780_MOVE_DISPLAY 0x08 // S/C
#define HD44780_MOVE_RIGHT 0x04   // R/L
// Function set
#define HD44780_CMD_FUNCTION 0x20
#define HD44780_FUNCTION_8_BIT 0x10     // DL
#define HD44780_FUNCTION_2_LINES 0x08   // N
#define HD44780_FUNCTION_5X10_DOTS 0x04 // F
// Set CGRAM address
#define HD44780_CMD_SET_CGRAM_ADDRESS 0x40
// Set DDRAM address
#define HD44780_CMD_SET_DDRAM_ADDRESS 0x80

// Bitmask for busy flag when reading
#define HD44780_BUSY_FLAG 0x80

/**
 * \brief Write a byte to the display.
 *
 * \param data The byte to send to the display.
 * \param isData Whether the byte is an instruction or character data.
 */
void hd44780_write(uint8_t data, bool isData);

/**
 * \brief Read a byte from the display.
 *
 * \param isData Whether to read the current cursor position, or the character at the cursor.
 *
 * \return If `isData` is `true`, the returned byte will be the character at the current DDRAM address. Otherwise, it will be the current DDRAM address and the busy flag.
 */
uint8_t hd44780_read(bool isData);

/**
 * \brief Indicates whether the display is currently processing, and cannot accept instructions.
 *
 * \return `true` if the display is busy.
 */
bool hd44780_busy(void);

/**
 * \brief Send a command to the display. Refer to the datasheet for the valid commands.
 *
 * This function waits for the display to clear the busy flag before sending the command.
 *
 * \param command The command to send.
 */
void hd44780_command(uint8_t command);

/**
 * \brief Send a byte of data to the display.
 *
 * This function waits for the display to clear the busy flag before sending the data.
 *
 * \param data The byte of data to send.
 */
void hd44780_data(uint8_t data);

/**
 * \brief Clear the display.
 *
 * This function is called on init.
 */
void hd44780_clear(void);

/**
 * \brief Move the cursor to the home position.
 *
 * This function is called on init.
 */
void hd44780_home(void);

/**
 * \brief Turn the display on, and/or set the cursor position.
 *
 * This function is called on init.
 *
 * \param cursor Whether to show the cursor.
 * \param blink Whether to blink the cursor, if shown.
 */
void hd44780_on(bool cursor, bool blink);

/**
 * \brief Turn the display off.
 */
void hd44780_off(void);

/**
 * \brief Set the CGRAM address.
 *
 * This function is used when defining custom characters.
 *
 * \param address The CGRAM address to move to, from `0x00` to `0x3F`.
 */
void hd44780_set_cgram_address(uint8_t address);

/**
 * \brief Set the DDRAM address.
 *
 * This function is used when printing characters to the display, and setting the cursor.
 *
 * \param address The DDRAM address to move to, from `0x00` to `0x7F`.
 */
void hd44780_set_ddram_address(uint8_t address);

/**
 * \brief Initialize the display.
 *
 * This function should be called only once, before any of the other functions can be called.
 *
 * \param cursor Whether to show the cursor.
 * \param blink Whether to blink the cursor, if shown.
 */
void hd44780_init(bool cursor, bool blink);

/**
 * \brief Move the cursor to the specified position on the display.
 *
 * \param col The column number to move to, from 0 to 15 on 16x2 displays.
 * \param line The line number to move to, either 0 or 1 on 16x2 displays.
 */
void hd44780_set_cursor(uint8_t col, uint8_t line);

/**
 * \brief Define a custom character.
 *
 * \param index The index of the custom character to define, from 0 to 7.
 * \param data An array of 8 bytes containing the 5-bit row data of the character, where the first byte is the topmost row, and the least significant bit of each byte is the rightmost column.
 */
void hd44780_define_char(uint8_t index, uint8_t *data);

/**
 * \brief Print a character to the display. The newline character will move the cursor to the start of the next line.
 *
 * The exact character shown may depend on the ROM code of your particular display - refer to the datasheet for the full character set.
 *
 * \param c The character to print.
 */
void hd44780_putc(char c);

/**
 * \brief Print a string of characters to the display.
 *
 * \param s The string to print.
 */
void hd44780_puts(const char *s);

#if defined(__AVR__) || defined(__DOXYGEN__)
/**
 * \brief Define a custom character from PROGMEM.
 *
 * On ARM devices, this function is simply an alias of hd44780_define_char().
 *
 * \param index The index of the custom character to define, from 0 to 7.
 * \param data A PROGMEM array of 8 bytes containing the 5-bit row data of the character, where the first byte is the topmost row, and the least significant bit of each byte is the rightmost column.
 */
void hd44780_define_char_P(uint8_t index, const uint8_t *data);

/**
 * \brief Print a string of characters from PROGMEM to the display.
 *
 * On ARM devices, this function is simply an alias of hd44780_puts().
 *
 * \param s The PROGMEM string to print.
 */
void hd44780_puts_P(const char *s);
#else
#    define hd44780_define_char_P(index, data) hd44780_define_char(index, data)
#    define hd44780_puts_P(s) hd44780_puts(s)
#endif

/** \} */
