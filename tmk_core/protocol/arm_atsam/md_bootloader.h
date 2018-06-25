#ifndef _MD_BOOTLOADER_H_
#define _MD_BOOTLOADER_H_

extern uint32_t _srom;
extern uint32_t _lrom;
extern uint32_t _erom;

#define BOOTLOADER_SERIAL_MAX_SIZE 20   //DO NOT MODIFY!

#ifdef MD_BOOTLOADER

#define MCU_HZ 48000000
#define I2C_HZ 0 //Not used

#endif //MD_BOOTLOADER

#endif //_MD_BOOTLOADER_H_

