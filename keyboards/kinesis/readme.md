# Firmware for the Kinesis Advantage/Contoured keyboard

There are at least three different ways to replace the controller in this keyboard.

1. The **stapelberg** folder contains the docs and configuration for using Teensy based controller created by Michael Stapelberg.

2. The **alvicstep** folder contains docs and configuration for directly wiring a Teensy2++ to the existing controller board. This follows the pinouts described in https://github.com/alvicstep/tmk_keyboard, which is where the name comes from. 

3. The **kintwin** folder contains the docs and configuration for using BlackPill based controller.

## Keymaps
All 3 hardware solutions should work with the same keymaps

## Switch Modifications
In addition to the drop-in replacements of the stock controller above, the folder **"keyboards\kin80"** contains the files to support 80 switch modification of the keyboard, compared to origial 86. Kin80 keymaps are not compatible with keymaps that are located inside of **kinesis** folder.