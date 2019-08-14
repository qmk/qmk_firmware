![Chris DZ60](https://i.imgur.com/EfrF09S.png)

# Chris' DZ60 Layout

This is a custom keymap for the layout of the DZ60.

``` bash
#From the qmk_firware directory run
make dz60:chrisae9
dfu-programmer atmega32u4 erase --force && \
dfu-programmer atmega32u4 flash dz60_chrisae9.hex && \
dfu-programmer atmega32u4 reset
```
