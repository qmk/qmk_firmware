Copyright 2022 Tibo Loete, aka Mister Eel <mistermister1111@hotmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.

# Mister Eel Userspace
This is my userspace with all the implementations of things that don't need
to be in my keymap. As a way to prep for the inevitable second keyboard, 
and to keep things compartimentalised.  

## Unicode
I use the UCIS unicode feature of qmk, but ideally I wanted to use the
unicodemap feature as well. Since using both isn't possible, I created
custom keycodes for a few unicode character (most with both upper and 
lower case variants). Their implementation can be found in `unicode.c` 
in `bool process_record_unicodemap(uint16_t keycode, keyrecord_t *record);`.

The necessary UCIS things are also in `unicode.c`, and I have modified the 
start and end functions to switch to unicode hex input and back on MacOS. 
This requires that only 2 keyboard layouts are active on MacOS and by default
you are always on the standard (not unicode hex input) layout. This allows me
to retain the option based shortcuts in general use.

## Custom keycodes
`custom_keycodes.c` implements custom keycodes that I create for various reasons
and have the `CK_` prefix. In reality this means they are custom keycodes not
part of my unicode custom keycodes (or other self implemented things in the
future).

Most of these are made to have a single keycode to do various things that require
different shortcuts on MacOS and Windows (like option-backspace vs ctrl-backspace
to delete a word). These keycodes allow for a much cleaner keymap.

## Mac_win_parity
Extra things created to get better parity between MacOS and Windows (on the
keyboard side) are implemented here. 

For now that means shortcuts for locking, closing apps and app switchings with
ctrl on Windows instead of alt (this is combined with putting ctrl in the same
spot as command on MacOS)
