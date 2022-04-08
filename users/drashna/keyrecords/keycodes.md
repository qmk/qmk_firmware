
# Custom Keycodes

Keycodes are defined in the `process_record.h` file and need to be included in the keymap.c files, so that they can be used there. 

A bunch of macros are present and are only included on boards that are not the Ergodox EZ or Orthodox, as they are not needed for those boards. 

* `KC_MAKE` - outputs `qmk compile -kb (keyboard) -km (keymap)` and enter, to start compiling the currenct keyboard.  This uses generated variables to always use the current keyboard and keymap.  Will work with any keyboard and any keymap.
  * If you are holding shift, it will use `qmk flash` instead of `qmk compile`.
  * If `MAKE_BOOTLOADER` is defined, it will always use `qmk flash` instead of `qmk compile`.
* `DEFAULT_LAYER_1` ... `DEFAULT_LAYER_4` - This sets layer 0-3 as the default layer, and writes that to eeprom, and plays a chime. 
* `VRSN`, outputs the keyboard, keymap, commit and date info.  Eg:
  * `handwired/tractyl_manuform/5x6_right/f411/drashna @ 0.15.9-162-g087d08, Built on: 2021-12-19-21:10:26`
*  `KC_DIABLO_CLEAR` - clears the diablo tapdance status.
* `KC_CCCV` - Copy on hold, paste on tap.
* `KEYLOCK` - This unloads the host driver, and prevents any data from being sent to the host. Hitting it again loads the driver, back. 
* `REBOOT` - Uses watchdog timer on AVR, and `NVIC_SystemReset()` on ChibiOS to reset the board, without jumping to the bootloader.
* `EEP_RST` - Overrides the default behavior, disables EEPROM (which will trigger a reset on init), and reboots the keyboard as per `REBOOT` keycode. 
