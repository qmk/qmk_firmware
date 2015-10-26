# TMK Generic

* I'm not sure what the Magic + H does.
 Is this a menu that will pop up regardless of what platform and program is open? 

 Yes, this is sort of debugging.
 Use PJRC's [hid_listen](https://www.pjrc.com/teensy/hid_listen.html) to see debug messages.

# TMK/Ergodox specific

* I would like to configure my leds to indicate the active layer.
 I read that can be done, but I haven't seen an example for this firmware.
 Can someone please post an example or a link?

 TMK for Ergodox have support for seven (!) led's:
 - three on right
 - three on left (see http://geekhack.org/index.php?topic=22780.msg873819#msg873819 for more details)
 - Teensy onboard led as well

 Any of these leds can be used as layer indicator or NumLock/CapsLock/ScrollLock led.

 [Here is example](https://github.com/cub-uanic/tmk_keyboard/blob/cub_layout/keyboard/ergodox/matrix.c#L121-167)
 how you can assign some meaning to each led.
 In this code only left leds are used to show layers, but you can
 [change `led_set()`](https://github.com/cub-uanic/tmk_keyboard/blob/cub_layout/keyboard/ergodox/led.c)
 and do anything you want with all leds.

# Firmware

Q: Where to get binaries?
A:

Q: Where to get sources?
A:

Q: How to compile?
A:


# Layouts

description of layouts in base firmware binaries


# Things TO-DO

- [ ] Flash NumLock led only when "numpad" layer is active
- [ ] Command (in terms of IS_COMMAND) to switch to no-leds mode
- [ ] Increase count of ACTION keys
- [ ] Fix command_state() onboard led: it should flash only when kbd in some specific mode (CONSOLE || MOUSE)
- [ ] ergodox_blink_all_leds() should save current state of leds, and restore after blink. initial state of all leds == off
- [ ] add support for pseudo-backlight (reversed LEDs) + docs/photo
- [ ] command to debug all LEDs (on/off/blink)
- [ ] proper (in-core) implementation of DEBUG_MATRIX_SCAN_RATE (non-Ergodox specific)
- [ ] proper (in-core) support for per-layer fn_actions[]

