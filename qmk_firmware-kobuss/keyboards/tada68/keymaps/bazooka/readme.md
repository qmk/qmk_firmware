# FireBazooka's TADA68 layout

This layout follows a layout very similiar to the default, but with added functionality settings.

* This layout will start with the basic layer and default function layer on start-up
* This means that that FN+Arrow Keys will have Page Up, Page Down, Home, & End on default
* Press FN+M to turn on Mouse Functionality (FN+Arrows Keys to move the mouse, FN+RShift for left click, & FN+Enter for right click)
* Pressing FN+M again will toggle the FN+Arrow Keys back to the default of PgUp, PgDn, Home, & End
* Press FN+I to change the Control, Windows, & Alt keys to a different configuration that I use for Mac (Win, Alt, Ctrl, _SPACE_, Ctrl, FN, Win)
* Pressing FN+I again will revert back to the default Ctrl, Win, Alt setting
* Pressing FN+Win will toggle the Windows Key Lock (Note: will not affect Win in the Mac Layer configuration)

Coding practices:
Using my limited C knowledge, I essentienally used flags to get certain functionality working (this probably isn't the way QMK should be used,
but I couldn't find/got lazy trying to find the functions used to toggle layers correctly). This means that I used a static unsigned 8-bit integer
called "keyboard_state" to check the current flags that are on and off currently for the keyboard.

Example:
keyboard_state = B00000101
+ The FN key is currently pressed down (bit 0)
+ The mouse layer is turned off (bit 1)
+ The Windows Key Lock is turned on (bit 2)

keyboard_state = B00000010
+ The FN key is currently NOT being pressed down (bit 0)
+ The mouse layer is turned on (bit 1)
+ The Windows Key Lock is turned off (bit 2)

This means that certain bitwise functions like CHECK_BIT(...) and SET_BIT(...) are used on "keyboard_state" to manipulate it.
