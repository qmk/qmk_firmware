# yhaliaw Planck layout

The layout for Planck by yhaliaw. 

Developed and tested on Planck Rev 6.1.

## Features

Leader sequences can be used to turn on layers without holding the key and reset the layers.
Leader sequences are triggered by key the series of key in quick succession.
See Base layer notes in Layout section.

Successful leader sequences will play the planck sound if sound is enabled.

The RGB underglow is linked to the layers and capslock.

## Keycodes

Most Keycodes are standard [QMK keycodes](https://docs.qmk.fm/#/keycodes).

### Custom Keycodes

The `RESET` key to start the bootloader is access by a leader sequence.
This is done to prevent a mispress.
See Adjust layer notes in Layout section.

The `Clear` key is used to clear the EEPROM of the keyboard.
This can be seen as resetting the state of the keyboard. 
Replug the keyboard to load in the resetted states.

## Layout
![yhaliaw planck layout](https://i.imgur.com/HvYva64.png)