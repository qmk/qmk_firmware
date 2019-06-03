# ErgoDox EZ Svorak A5 

This layout is supposed to be an implementation of the [Svorak A5
layout](http://aoeu.info/s/dvorak/svorak). Unfortunately, the Ergodox EZ lacks
one column for the right hand, why the three buttons furthest to the right, on
the right half, are missing. I have tried to move them around and have yet to
find a perfect position for them.


## Note

The keyboard assumes that the operating system interprets your keyboard as
Swedish. If you get weird issues (like, most letters work, but not all special
characters) please make sure your operating system uses a Swedish keyboard
layout.


## Flashing

In order to compile and flash your Ergodox EZ, invoke the following at the root
of the repository.

`make ergodox_ez:dvorak_svorak_a5:teensy`

I haven't gotten the above to work on Windows. Instead I use
[Msys2](https://www.msys2.org/) to compile the .hex-file (`make ergodox_ez:dvorak_svorak_a5`)
and [Teensy Loader](https://www.pjrc.com/teensy/loader_win10.html) to flash the
board.


## Changelog

* 2018-08-09
  * Initial release
* 2018-08-10
  * Make special characters work in Windows
  * Add QWERTY layer

# Author
Erik Thorsell
erikthorsell @ github and twitter

