Lightsaber keyboard firmware
======================
Korean custom keyboard designed by Duck.

*Note that this is not the official firmware*

Supported models
----------------
All pcb options are supported.


Build
-----
Move to this directory then just run `make` like:

    $ make -f Makefile.[pjrc|lufa]

Use `Makefile.pjrc` if you want to use PJRC stack or use `Makefile.lufa` for LUFA stack.


Bootloader
---------
The PCB is hardwired to run the bootloader if the key at the `one above backspace` position is held down when connecting the keyboard.

It is still possible to use Boot Magic and Command to access the bootloader though.

