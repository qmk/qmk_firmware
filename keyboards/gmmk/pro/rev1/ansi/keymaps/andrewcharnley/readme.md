# Description
A keymap designed to be functional for development purposes - no flashing lights or gimmicks. PRTSC and DEL key in the top right corner.
Solid backlight that changes red if CAPS is on and reverts back afterwards. Brightness retained in both cases.
Backlight is disabled on suspend and restored upon wake-up.
The 'Windows' key is a second FN key. This makes it more natural to use the encoder wheel (good luck trying to do it with one hand).

Compile using `qmk compile -kb gmmk/pro/ansi -km andrewcharnley`

# Encoder
FN + Encoder scroll = media next/prev
FN + Encoder press = media pause
default encoder behavior = volume up/down

# Function Layer
FN + Up = increase brightness
FN + Down = decrease brightness
FN + Backslash = bootloader

