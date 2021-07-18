Default layout but with a tetris game
=====================================
Tetris works by outputting key-presses to make ascii-art in a regular text editor.
It reads key presses to rotate and move the bricks like a regular tetris game.

Example
=======
![tetris](https://raw.githubusercontent.com/danamlund/meckb_tetris/master/tetris.gif)

Usage
=====
1) Open a default text editor
2) Press the tetris button (Fn + t)
3) Play tetris

It makes ascii-art by sending keycodes: left, right, up, down, qwerty characters, and numbers.

Problems
========
Drawing ascii-art is too slow to make a pleasant playing experience.
While drawing ascii-art, the keyboard does not record key-presses, so its pretty unresponsive.

Adds 5000 bytes to the hex file.

Implement in other keyboards
============================
 - Copy-paste the files tetris_text.c and tetrix_text.h to your keymap folder.
 - Add/update your-keyboard/your-keymap/Makefile to include ``SRC = tetris_text.c``
 - Copy-paste the tetris-related code from this keymap.c to yours.
 - Set a key to trigger F(1) to start tetris mode.
 - Its also a good idea to set a key to stop tetris, here its escape.

You can find a simple tetris keyboard definition at <https://github.com/danamlund/meckb_tetris/>
