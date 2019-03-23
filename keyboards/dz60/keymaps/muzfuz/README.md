# muzfuz DZ60 layout

```shell
make dz60:muzfuz
dfu-programmer atmega32u4 erase --force && \
dfu-programmer atmega32u4 flash .build/dz60_muzfuz_v2.hex && \
dfu-programmer atmega32u4 reset
```
