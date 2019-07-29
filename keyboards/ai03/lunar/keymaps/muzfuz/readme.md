# muzfuz's keymap for Lunar

```shell
make ai03/lunar:muzfuz:dfu
dfu-programmer atmega32u4 erase --force && \
dfu-programmer atmega32u4 flash .build/ai03_lunar_muzfuz.hex && \
dfu-programmer atmega32u4 reset
```
