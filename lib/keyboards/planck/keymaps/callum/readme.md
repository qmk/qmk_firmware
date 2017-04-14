# callum’s planck layout

This is a layout for the grid planck, built with a few ideals in mind:

- Consistent and minimal response times should be maintained. Keys that react differently depending on whether they are tapped or held, keys that react differently if they are double tapped, etc. should be avoided – they inevitably send their keycode later than a normal key – interrupting the immediate feedback from the screen. Therefore we restrict ourselves to chording as our only means of getting more than one symbol out of a single physical key.
- The hands should never need to leave the home position. The usual culprit for this is the arrow cluster, so the arrow cluster should be as close to home as possible.
- There should be two of every modifier (one on each side), otherwise certain long key combinations become hard to make.

We have five layers. A `BASE` layer, in colemak; a `MOVE` layer, with an arrow cluster and other movement keys; a `SYMB` layer, with numbers and symbols; a `FUNC` layer, with function keys and media keys; and a `MOUSE` layer, with mouse emulation. The `MOUSE` layer is activated by holding the Move and Symb keys simultaniously.

```
/* BASE
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Bksp |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Func | Ctrl |  Alt |  Cmd | Symb | Enter| Space| Move |  Cmd |  Alt | Ctrl | Func |
 * `-----------------------------------------------------------------------------------'
 */

/* MOVE
 * ,-----------------------------------------------------------------------------------.
 * |  Esc |      | Cmd-L|  Up  | Cmd-R|      |      | Cmd-L|  Up  | Cmd-R|      |  Esc |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Del | Caps | Left | Down | Right|      |      | Left | Down | Right| Caps |  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | Pg Up| Pg Dn|      |      | Pg Dn| Pg Up|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

/* SYMB
 * ,-----------------------------------------------------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   –  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Del |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   £  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   ~  |   `  |   +  |   =  |   |  |   \  |   [  |   ]  |   {  |   }  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

/* MOUSE
 * ,-----------------------------------------------------------------------------------.
 * |      |      | ACC-2| ACC-1| ACC-0|      |      | SW-L |  M-U | SW-R |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | MB-3 | MB-2 | MB-1 |      |      |  M-L |  M-D |  M-R |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | SW-D | SW-U |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

/* FUNC
 * ,-----------------------------------------------------------------------------------.
 * | Reset|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | Vol+ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F11 |  F12 |  F13 |  F14 |  F15 |  F16 |  F17 |  F18 |  F19 |  F20 | Vol- |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F21 |  F22 |  F23 |  F24 |      |      | Power|      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | Prev | Mute | Play | Next |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
 ```
