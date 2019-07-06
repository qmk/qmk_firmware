# muzfuz Clueboard layout

```shell
make clueboard/66/rev3:muzfuz
dfu-programmer atmega32u4 erase --force && \
dfu-programmer atmega32u4 flash .build/clueboard_66_rev3_muzfuz.hex && \
dfu-programmer atmega32u4 reset
```
