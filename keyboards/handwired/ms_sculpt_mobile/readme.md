# Microsoft Sculpt Mobile

This is a way to take a Microsoft ergonomic bluetooth keyboard, and make it 
into a hard-wired keyboard running QMK. 

The keyboard is known under several different names:
Mobile Bluetooth 5000, Mobile 6000, Sculpt mobile, and Asus rebranded.

I had a stack of them, since they're cheap on ebay, travel well, and are just ergo enough.

The ribbon cable is 1mm pitch, which is hard to hand solder. I bought a cheap set of 
"pitch adapter" boards https://www.amazon.com/Double-Sided-0-4mm-1-0-Adapter-60mmx38mm/dp/B00OK42118

Cut the original ribbon cable sockets off the bluetooth board using a razor, they're hard to desolder.
They're also allow the cable to be inserted on top or bottom.

If I was going to do it again, I'd make the MCU connection come out the top of the keyboard
and avoid the wires dangling out the bottom. 

As I was debugging the matrix, I started to get random failures. In desparation I tried a second MCU,
but had the same problems. It turns out that the ribbon cable connections can get worn. Shave a
half millimeter off the end of the ribbon cable & the errors go away.

My method for discovering the matrix was to set up a LAYOUT macro that included all pins.
See MATRIX_TESTING_LAYOUT if you need it. Then set up a keymap that has all printable symbols
in the first 4 rows. test each key & record output. Then switch the printable symbols to the
bottom 4 rows & repeat. This was enough to show the matrix.


The full original keymap for the Sculpt is 

|   | A  | B  | C  | D   | E   | F   | G    | H    | I    | J     | K    | L      | M    | N     | O    | P      | Q    | R   |
|:-:|:--:|:--:|:--:|:---:|:---:|:---:|:----:|:----:|:----:|:-----:|:----:|:------:|:----:|:-----:|:----:|:------:|:----:|:---:|
| 0 | b  | n  | m  | ,   | .   | /   |      |      |      | Caps  |      |        |      |       |      |        |      | Fn  |
| 1 | g  | h  | "  |     |     |     |      |      |      |       | Vol+ | Mute   | RCtl |       | Vol- | PgDn   | LCtl |     |
| 2 | 7  | 8  | 9  | 0   | Del |     | PgUp |      |      |       |      | RShift |      |       |      | LShift |      |     |
| 3 | p  | [  | ]  | \   |     |     |      |      |      |       | RAlt |        |      |       | LAlt |        |      |     |
| 4 | y  | u  | i  | o   |     |     |      |      |      |       |      |        |      | LGUI  |      |        |      |     |
| 5 | ~  | -  | += | j   | k   | l   | ;    | 5    | 6    | Bksp  | 1    | 2      | 3    | 4     | F4   | F5     | F6   |     |
| 6 | a  | s  | d  | q   | w   | e   | Up   | Left | Down | Right |      |        |      | Space | F1   | F2     | F3   | Tab |
| 7 | F7 | F8 | F9 | F10 | F11 | F12 |      | f    | r    | t     | z    | x      | c    |       | v    | Enter  | Esc  |     |

This works with 18 cols + 8  rows on a Teensy++, or ARM-based Teensy.

The Astar mini has all pins exposed , so you can do 18x8
If you want a speaker, LEDs, etc., you'll need to free up a pin.  I recommend joining columns
R and L to the same pin.

Building - add ASTAR=1 to the compile line or leave out for teensy2++

Make example for this keyboard (after setting up your build environment):

    make handwired/ms_sculpt_mobile:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
