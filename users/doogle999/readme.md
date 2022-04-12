Copyright 2018 <name> <email> @doogle999

Overview
========

This folder is just for some calculator code for my keyboards.

Making Your Keyboard Into A Calculator
--------------------------------------

If you'd like to make your keyboard into a calculator, you can do it with this userspace (hopefully!)

You can make a keymap for your keyboard of choice named doogle999 and then you can make it regularly.

You should make one layer that is just the functionality for your calculator, so it just has the keys you need (numbers, symbols, some letters for functions). It should also have END_CALC and CALC somewhere. END_CALC gets you out of calculator mode, and CALC evaluates the calculation.

On one of your other keymaps you should make a key that is TO(layer of calculator). This is how you will activate the calculator. You should also define the layer your calculator is on with the define CALC_LAYER in doogle999.h (this means that for all your keyboards, your calculator layer has to be the same layer).

You can change what characters coorespond to what operators and functions and you can add more functions in doogle999.h and doogle999.c, you can also change which characters are sued for which keys. However, as of now standard keys should be used for operations. By that I mean if you want your multiplication sign to be an x, you should change the CALC_CHAR_MUL to an x but you should keep your multiplication keycode on the keymap either as KC_8 (shifted) or KC_KP_ASTERISK. This might be changed in the future so there are custom keycodes so this is less of a pain and more intuitive.

You can look at my dz60 keymap doogle999 for an example.

Issues
------
Unfortunately the chip onboard my dz60 only does single precision floating point numbers, but I have everything set up as double so if your chip supports doubles it should work for you.

This Was Here When I Made The ReadMe
------------------------------------

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