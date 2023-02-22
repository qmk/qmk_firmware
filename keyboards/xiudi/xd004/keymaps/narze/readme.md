# narze Keymap for XD004 PCB

(Key 1 is on the opposite of USB port side, so I flip the keys to make usb port be on the left)

- Key 1 : Hyper + F2
- Key 2 : Hyper + F1
- Key 3 : Ctrl + B (Microphone : Toggle mute)
- Key 4 : Ctrl + X (Microphone : Push to talk)

## Build & Flash

- Put this board in DFU : bridge the last two pins (#5 & 6) of the 6-pin "J2" header on the opposite edge of the board to the USB port.
- `make xd004/v1:narze:flash` or `qmk flash -kb xd004/v1 -km narze`
