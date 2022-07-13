# Raspberry Pi 2040 onekey

To trigger keypress, short together pins *GP4* and *GP5*.

Double-tap reset to enter bootloader mode. Copy the built uf2 file to the device by dragging the file to the new USB disk.

## compile with
`qmk compile -kb handwired/fpad/rp2040 -km test`
