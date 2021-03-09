# The default Preonic layout - largely based on the Planck's
Even though RGBLIGHT and RGB_MATRIX are both enabled, the RGBLIGHT code only activates when the keyboard is put into reset mode, which causes no conflicts with the WS2812 driver. I couldn't figure out how to change the LED behavior within the `shutdown_user` function using RGB_MATRIX, but the code there for RGBLIGHT seems to work so that's what I used.

This is my first keymap being pushed, and it is actually a keymap for my brother's keyboard; I use a planck. Thank you!