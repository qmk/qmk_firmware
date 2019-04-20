# dfu-programmer atmega32u4 erase --force
# dfu-programmer atmega32u4 flash /path/to/firmware.hex
# dfu-programmer atmega32u4 reset

make dz60:billiams
dfu-programmer atmega32u4 erase --force && \
dfu-programmer atmega32u4 flash .build/dz60_billiams.hex && \
dfu-programmer atmega32u4 reset