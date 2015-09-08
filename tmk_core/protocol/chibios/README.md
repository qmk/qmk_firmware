## USB stack implementation using ChibiOS

### Notes

- To use, unpack or symlink ChibiOS here, to `chibios`.
- For gcc options, inspect `chibios.mk`. For instance, I enabled `-Wno-missing-field-initializers`, because TMK common bits generated a lot of hits on that.
Also pay attention to `-O0` (enabled for debugging); for deployment use `-O2`.
- USB string descriptors are a mess. I did not find a way to cleanly generate the right structures from actual strings, so the definitions in individual keyboards' `config.h` are ugly as heck.
- There are some random constants left so far, e.g. 5ms sleep between calling `keyboard_task` in `main.c`. There should be no such in `usb_main.c`. Everything is based on timers/interrupts/kernel scheduling (well except `keyboard_task`), so no periodically called things (again, except `keyboard_task`, which is just how TMK is designed).
- It is easy to add some code for testing (e.g. blink LED, do stuff on button press, etc...) - just create another thread in `main.c`, it will run independently of the keyboard business.
- Jumping to bootloader works, but it is not entirely pleasant, since it is very much MCU dependent. So, one needs to dig out the right address to jump to, and pass it to the compiler in the `Makefile`. Also, a patch to upstream ChibiOS is needed (supplied), because it `ResetHandler` needs adjusting.
- The USB stack works pretty completely; however there are bits of other TMK stuff that are not done yet:

### Immediate todo

- suspend
- sleep led

### Missing / not working (TMK vs ChibiOS bits)

- eeprom / bootmagic (will be chip dependent)

### Tried with

- ChibiOS 3.0.1 and ST F072RB DISCOVERY board.
- Need to test on other STM32 chips (F3, F4) to make it as much chip-independent as possible.
