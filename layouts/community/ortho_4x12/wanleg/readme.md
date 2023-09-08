# Let's Split Flashing  
(More information at `qmk_firmware/layouts/community/ortho_3x10/wanleg/readme.md`)
## Make the QMK DFU .hex
`make lets_split/rev2:wanleg:production dfu=qmk` 

## Burning EEPROM settings and Firmware
Navigate to the directory with your .hex file and the `eeprom-lefthand.eep` and `eeprom-righthand.eep` files in it.  
**Burn Left Side With QMK DFU and Firmware**  
`avrdude -b 19200 -c avrisp -p m32u4 -v -e -U lock:w:0x3F:m -U efuse:w:0xC3:m -U hfuse:w:0xD9:m -U lfuse:w:0x5E:m -U eeprom:w:eeprom-lefthand.eep -P comPORT -U flash:w:YOUR_production.hex:a`  

**Burn Right Side With QMK DFU and Firmware**  
`avrdude -b 19200 -c avrisp -p m32u4 -v -e -U lock:w:0x3F:m -U efuse:w:0xC3:m -U hfuse:w:0xD9:m -U lfuse:w:0x5E:m -U eeprom:w:eeprom-righthand.eep -P comPORT -U flash:w:YOUR_production.hex:a`  

Change `comPORT` to whatever port is used by the Arduino (e.g. `com11` in Windows or `/dev/ttyACM0` in Linux). Use Device Manager in Windows to find the port being used. Use `ls /dev/tty*` in Linux. Change `YOUR_production.hex` to whatever you've created in the previous step.

## Using QMK DFU  
Once QMK DFU is burned to your ProMicro, you can then flash subsequent hex files with
`make lets_split/rev2:<keymap>:dfu dfu=qmk`  
The `dfu=qmk` conditional will set `BOOTLOADER = qmk-dfu` instead of `BOOTLOADER = caterina`  

# Let's Split LEDs  
In `qmk_firmware/keyboards/lets_split/rev2/rev2.c`, replace contents with 
```  
#include "lets_split.h"

void matrix_init_kb(void) {

    // // green led on
    // DDRD |= (1<<5);
    // PORTD &= ~(1<<5);

    // // orange led on
    // DDRB |= (1<<0);
    // PORTB &= ~(1<<0);
	
	//turn off LEDs on ProMicro
   DDRD &= ~(1<<5);
   PORTD &= ~(1<<5);

   DDRB &= ~(1<<0);
   PORTB &= ~(1<<0);

	matrix_init_user();
};
```  
to turn off LEDs
