# Gherkin Layout

It is used as a game pad, and key layout is inspired by spare keys I had lying around.
The firmware is very simple, and only includes one layer keymap, and RGB effects.

Builds fine as of 2019-12-17

# Flashing

Run `make 40percentclub/gherkin:bbaserdem:avrdude`

The following commands are commands I used before;
```
make gherkin:bbaserdem
sudo avrdude -p atmgea34u4 -P `ls /dev/ttyACM*` -c avr109 -U flash:.build/gherkin_bbaserdem.hex
```

