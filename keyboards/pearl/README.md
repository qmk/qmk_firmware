# Pearl 40%

Pearl 40% is a keyboard designed by Koobaczech. It uses an Atmel
ATMEGA32A MCU.

## Compiling and flashing

These instructions are for building and flashing your Pearl 40% without
Bootmapper Client.

### Requirements

#### Windows

(to be written, help needed)

#### Mac

Apart from regular QMK and AVR dependencies you need to install
`bootloadHID`. You can install it with `homebrew` as follows:

    $ brew install --HEAD https://raw.githubusercontent.com/robertgzr/homebrew-tap/master/bootloadhid.rb

If you don't use `homebrew` you can try following the compiling
instructions defined below in the Linux section.

#### Linux

For Linux you require all regular QMK dependencies, but make sure you're
using `gcc-avr` version 4.9 or higher. 4.8 and lower do not contain the
proper definitions for ATMEGA32A MCUs and QMK will fail while attempting
to compile a HEX for Pearl 40%.

E.g. you cannot compile Pearl 40% HEX on a regular Ubuntu 14.04 as
`gcc-avr` version is maxed to 4.8 on it.

Additionally you need an operational `bootloadHID` binary.

You can install `bootloadHID` by taking the following steps:

    $ git clone https://github.com/robertgzr/bootloadHID ~/tmp/bootloadHIDsrc
    $ cd ~/tmp/bootloadHIDsrc/commandline
    $ make VENDORID=0x16c0 PRODUCTID=0x05DF # vid and pid for atmega32a
    $ chmod +x bootloadHID && cp bootloadHID /usr/bin/bootloadHID
    
Running `which bootloadHID` should return `/usr/bin/bootloadHID`.
    
### Compiling

Enter the QMK root directory and compile a keymap with the following
command:

    $ make pearl:<keymap>
    
where `<keymap>` is a layout directory under the `pearl` directory.

QMK should compile a HEX (called `pearl_<keymap>.hex`) for you, which
you can flash using `bootloadHID`.

### Flashing

To enable Pearl 40% bootloading mode, unplug the keyboard, then plug it
in while holding `Esc` at the same time (the top-leftmost switch on the
PCB, next to the USB connector). Once the board is in bootload mode,
issue the following command (you might require `sudo` to perform the
command):

    # assuming we're still in the QMK root dir where you compiled a HEX into
    $ bootloadHID -r ./pearl_<keymap>.hex

You should see something similar to

    > Page size = <value>
    > Device size = <value>; <value> remaining
    > Uploading <value> bytes starting at 0 (0x0)
    > <value> ... <current value>
    
where `<current value>` should be slowly increasing as the HEX is being
flashed to the board. If there is some warning about `resource busy` it
should still work OK.

Once done the board underglow should turn red and the new firmware has
been flashed. If you can't type on the board try plugging it in again
(without holding any keys to prevent accidentally setting it into
bootload mode again).
