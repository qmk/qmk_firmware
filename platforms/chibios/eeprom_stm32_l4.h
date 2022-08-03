/*
 * This software is experimental and a work in progress.
 * Under no circumstances should these files be used in relation to any critical system(s).
 * Use of these files is at your own risk.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This files are free to use from http://engsta.com/stm32-flash-memory-eeprom-emulator/ by
 * Artur F.
 *
 * Modifications for QMK and STM32L432 by lalalademaxiya1 & lokher
 *
 * To add a new MCU, please provide the flash page size and the total flash size in Kb.
 * The number of available pages must be at least two. Only one page for the total EEPROM size.
 * It is recommend to set the number of log page to 3~5 times of data page for better wear leveling.
 *
 */

#pragma once

typedef unsigned long long uint64_t;

uint16_t EEPROM_Init(void);
void     EEPROM_Erase(void);
uint8_t  EEPROM_WriteDataByte(uint16_t Address, uint8_t DataByte);
uint8_t  EEPROM_WriteDataWord(uint16_t Address, uint16_t DataWord);
uint8_t  EEPROM_WriteDataDWord(uint16_t Address, uint32_t DataDWord);
uint8_t  EEPROM_ReadDataByte(uint16_t Address);
uint16_t EEPROM_ReadDataWord(uint16_t Address);
