# 5x5

![5x5](https://3.bp.blogspot.com/-bKOfUyMtdrE/WqGA_03kGZI/AAAAAAACPtY/DsHDTQS0IlMD3ie8HHlf1ATRUAwpZdcSgCLcBGAs/s1600/c.jpg)  
===  

## Modular Keypad/Keyboard  
The basic unit is a 5x5 matrix with 25 keys. Up to 3 of these can be connected to each other side by side.  
5x5, 5x10, and 5x15 matrices are possible.  
There are pads for header pins on each side that complete the circuits from board to board. These can be permanently connected with solder bridges or temporarily with pin headers and shunt jumpers.  
**_All configurations are powered by a SINGLE Arduino Micro or clone (NOT a Pro Micro)._**  

* [The original TMK firmware](https://github.com/di0ib/tmk_keyboard/tree/master/keyboard/5x5)

Keyboard Maintainer: QMK Community  
Hardware Supported: 5x5 PCB   
Hardware Availability: [5x5 project on 40% Keyboards](http://www.40percent.club/2018/04/5x5.html)  

Make example for this keyboard (after setting up your build environment):

    make 40percentclub/5x5:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

First pass at adding support for the 4x4 keyboard. Compiles but completely untested. Intended to kick-start development.  

### Swap Hands Setup

The current swap hands array in 5x5.c is for the maximum 3 board setup (5x15). If you're using less than 3 boards and have swap hands enabled, you may get behaviour different from what you're expecting.

### Standard Configuration
Assume you have the following keymap and have 3 boards connected together.
```
  .--------------------------------------------------------------------------------------------------------------------------------------.
  |swaphand| 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | ESC    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | BACKSP |   7    |   8    |   9    |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | TAB    | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      |   4    |   5    |   6    |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | SHIFT  | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | ENT/SFT|   1    |   2    |   3    |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | LCTRL  | LGUI   | ALT    | ALT    | NUM    | SHIFT  | SPACE  | DIR    | RGUI   | RALT   | DEL    | CTRL   |   0    |   0    |   .    |
  '--------------------------------------------------------------------------------------------------------------------------------------'
 ```
 Holding down `swaphand` + `a` will output `5`

 ### Two Board Configuration
 Now suppose you would like a 5x10 setup with the following keymap.
 ```
   .-----------------------------------------------------------------------------------------.
   |swaphand| 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      |
   |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      |
   |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      |
   |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      |
   |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   | LGUI   | ALT    | ALT    | NUM    | SHIFT  | SPACE  | DIR    | RGUI   | RALT   | DEL    |
   '-----------------------------------------------------------------------------------------'
  ```
 Holding down `swaphand` + `a` will output nothing, because the default swap hands array is calling for a key that doesn't exist in this keymap (i.e. a key 5 columns to the right of the semicolon).  
 For `swaphand` + `a` to output `;`, the swap hand array would need to be changed to this:
 ```
 const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
   {{9, 0}, {8, 0}, {7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
   {{9, 1}, {8, 1}, {7, 1}, {6, 1}, {5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}},
   {{9, 2}, {8, 2}, {7, 2}, {6, 2}, {5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}},
   {{9, 3}, {8, 3}, {7, 3}, {6, 3}, {5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}},
   {{9, 4}, {8, 4}, {7, 4}, {6, 4}, {5, 4}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 4}},
 };
 ```
### Single Board Configuration
Now let's say you have the same 5x10 keymap as in the previous example, but changed the swap hand array to this:
```
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
  {{4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}},
  {{4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}},
  {{4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}},
  {{4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 4}},
};
```
Holding down `swaphand` + `a` will output `g`  
Holding down `swaphand` + `s` will output `f`  
Holding down `swaphand` + `d` will output `d` (middle of the array, so it "swaps" with itself, yielding no change in output)    
Holding down `swaphand` + `f` will output `s`  
Holding down `swaphand` + `g` will output `a`  
Holding down `swaphand` + `h` will output `h` (outside of the array, so nothing to swap with)  
Holding down `swaphand` + `j` will output `j` (same reason as with `h`)

---
It should be apparent that you can type all of the 5x10 example keymap with only a single board if you enable swap-hands.  
The `q` `w` `e` `r` `t` side can be typed without any modifiers, and the `y` `u` `i` `o` `p` side can be accessed with swap-hands.
But what if you wanted the `y` `u` `i` `o` `p` side to be typed without modifiers and the `q` `w` `e` `r` `t` side to be accessed with swap-hands?  

One solution is to modify your keymap to something like this (with 5x10 swap hands array):
```
  .-----------------------------------------------------------------------------------------.
  |swaphand| 5      | 6      | 7      | 8      | 9      | 1      | 2      | 3      | 4      |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | Y      | U      | I      | O      | P      | Q      | W      | E      | R      | T      |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | H      | J      | K      | L      | ;      | A      | S      | D      | F      | G      |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | N      | M      | ,      | .      | /      | Z      | X      | C      | V      | B      |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | SPACE  | DIR    | RGUI   | RALT   | DEL    | LGUI   | ALT    | ALT    | NUM    | SHIFT  |
  '-----------------------------------------------------------------------------------------'
 ```
