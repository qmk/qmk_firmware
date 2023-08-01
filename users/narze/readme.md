# narze's layout

## (S)uper (D)uper Mode

Inspired by [jasonrudolph](https://github.com/jasonrudolph/keyboard#super-duper-mode), with some extensions such as backspace & forward delete. The idea is to make another useful layer available on the home row.

To use, press `S+D` simultaneously and hold, then...
- `H/J/K/L` for Vim-like movement
- `I/O` to move between browser tabs
- `A` for `Option (Alt)`
- `F` for `Backspace`
- `;` for `Delete`
- `A` with `H/L` to move to previous/next word
- `A` with `G/;` to delete to previous/next word
- Available for all layouts (but plover) using physical S & D keys position in qwerty
- `Spacebar` for `Shift` (it's easier when already holding A with your pinky)
- Disable with `Raise+Lower+M`
- You can edit or add more useful keys in SUPERDUPER layer
- It can be activated by holding `/` as well, but it's slower since `LT()` uses `TAPPING_TERM` of 200ms but `S+D` uses `COMBO_TERM` of only 20ms (Can be changed within config.h)

The implementation will vary and some keys are not available in some of my layouts, please refer to `_SUPERDUPER` layer in each of my `keymap.c` files.

# LICENSE
Copyright 2019 Manassarn Manoonchai manassarn@gmail.com @narze

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
