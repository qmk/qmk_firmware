# STM32 Nucleo-F446 onekey

To trigger keypress, short together pins *A0* and *A1*. Note that the pin numbering is relative to the MCU, so that A0 and A1 refer to PA0 and PA1 on the MCU (which are also labelled A0 and A1 on the board, but this isn't true for the other PAx pins). 

You'll also need to connect `VIN`, `GND`, USB `D+` to `PA12`/`D2`, and USB `D-` to `PA11`/`D10`.
