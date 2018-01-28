# The default keymap for meira

Built for the promicro with (don't expect this to work for you unaltered!):
```
make meira/promicro:grahampheath
avrdude -p atmega32u4 -P /dev/tty.usbmodem14141 -c avr109 -U flash:w:meira_promicro_grahampheath.hex
```

