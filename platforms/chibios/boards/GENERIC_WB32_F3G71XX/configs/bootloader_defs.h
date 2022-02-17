/* Address for jumping to bootloader on WB32 chips. */
/* It is chip dependent, the correct number can be looked up here:
 * http://www.westberrytech.com/down/mcu/data/WB32F3G71xx_rm.pdf
 */
#ifndef WB32_BOOTLOADER_ADDRESS
#    undef STM32_BOOTLOADER_ADDRESS
#    define WB32_BOOTLOADER_ADDRESS 0x1FFFE000
#    define STM32_BOOTLOADER_ADDRESS WB32_BOOTLOADER_ADDRESS
#else
#    undef STM32_BOOTLOADER_ADDRESS
#    define STM32_BOOTLOADER_ADDRESS WB32_BOOTLOADER_ADDRESS
#endif
