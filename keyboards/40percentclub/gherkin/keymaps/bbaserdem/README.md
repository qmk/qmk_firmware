# Gherkin Layout
This is my gherkin layout.
It is used as a game pad, and key layout is inspired by spare keys I had lying around.
The firmware is very simple, and only includes one layer keymap, and RGB effects.

# Flashing
The following command should be used from the main qmk directory.
```
make gherkin:bbaserdem
sudo avrdude -p atmgea34u4 -P `ls /dev/ttyACM*` -c avr109 -U flash:.build/gherkin_bbaserdem.hex
```
