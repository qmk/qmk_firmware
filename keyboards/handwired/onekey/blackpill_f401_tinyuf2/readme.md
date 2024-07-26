# F401 Blackpill onekey

* Supported Hardware: STM32F401CCU6 WeAct v1.3

To trigger keypress, short together pins *B0* and *A7*.

This variant requires the TinyUF2 bootloader to be installed. This can be downloaded from the [tinyuf2 releases page](https://github.com/adafruit/tinyuf2/releases). The F401 blackpill binary works for both F401- and F411-based blackpill devices.

Double-tap reset to enter bootloader mode. Copy the built uf2 file to the device by dragging the file to the new USB disk.
