# pete's mom Layout

Customized xd60 keymap based on yuuki's but a step sideways with Mac support. For Pete on his 40th

## Programming Instructions

Change the layout in `keymap.c` then run `make xiudi/xd60:petesmom`. The compiled file will be located in `.build/xiudi_xd60_petesmom.hex` relative to the project root. To flash it onto your keyboard, use whatever program works on your OS. I personally use `dfu-programmer`, and run:

* `sudo dfu-programmer atmega32u4 erase`
* `sudo dfu-programmer atmega32u4 flash .build/xiudi_xd60-petesmom.hex`
* `sudo dfu-programmer atmega32u4 start`

## Layout

See `keymap.c` for the details, but here are the important features:

| Key                        | Function                           |
| -------------------------- | ---------------------------------- |
| ESC | ESC when pressed alone but acts as ~ when pressed with Shift or LGUI down |
| FN + ESC | Grave |
| Right Shift | When tapped generates / |
| FN + HJKL | Arrow Keys |
| FN + C | ^ |
| FN + V | & |
| FN + , . RShift | Mac Vol - + Mute |
| FN + P [ ] \ | Mac Play/Pause, Prev Track, Next Track, Stop |
