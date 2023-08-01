![Orthodeluxe Layout Image](https://i.imgur.com/xnq1gNj.png)

# Orthodeluxe layout for Planck keyboards

By Erik Bakker

## Main idea

I use a Planck keyboard as a daily driver since 2018. Over time, I improved the layout and added functionality to the firmware. The main idea was to easily access all keys and functions without moving my hands from the home position (when your fingers rest on ASDF and JKL;). I'd like to share this keyboard layout with you.

## Notes about left handedness

This keyboard layout is perfect for people that use the mouse with their left hand. I am right handed myself. But since a couple of years, I learned to use the mouse with my left hand. I started doing that to relieve strain in my right arm. But now, I really like a setup with the keyboard in the middle, a mouse on the left, and pen and paper on the right. For those that insist on using the mouse with their right hand, I plan to create an alternative layout called 'orthodeluxe-R'.

## Base layer

Apart from the basic QWERTY layout, the base layer features:

- A 2U space bar and 2 keys to switch layers. Rotate you keycaps 180 degrees for comfortable access.
- Shift keys in the lower left and lower right corners. You hit them with the sides of your hands.
- 2 sets of modifiers, symmetrically layed out in the bottom row. You can switch between MacOs and Windows layouts.
- In Windows layout, the Ctrl keys are located where you can easily reach it with your thumbs. Just like the command key on Apple keyboards.
- Symmetrical layout of the left and right sides of the keyboard. Row 1: Backspace and Delete, row 2: Escape and Enter, row 3: Left and right Tab.

## Numpad layer

The numpad layer contains a numpad and non-alphanumeric characters, like math operators, brackets and quotes. 

- Numpad, math operators and currency symbols are all operated by the right hand.
- All symbols that programmers need are operated by the left hand.
- Clicking a bracket key produces an opening bracket.
- Holding shift while clicking a bracket key produces a closing bracket.
- Double clicking a bracket key produces an opening and closing bracket with the cursor positioned in between.
- Double clicking the quote keys produces 2 quotes with the cursor positioned in between.
- The quote/apostrope is conveniently located at the S key, to easily type "It's everyone's favorite keyboard layout".

## Navigation layer

The navigation layer contains the cursor movement keys, keys F1-F12, and more:

- The cursor keys are in an 'inverted T' configuration at the most comfortable position for the right hand (IJKL).
- An 'App Switch' key to switch appslications, but smarter than just mapping Alt-Tab to that key.
- A Key to easily access Task View in Windows (or Mission Control in MacOs).
- Keys to switch virtual desktops in Windows (or spaces in MacOs).

## Additional layers

There are some additional layers for:

- accessing lesser used symbols and functions;
- switching between MacOs and Windows modes;
- access Cut, Copy and Paste shortcuts wirth the right hand, for people that use the mouse with their left hand.

## Bootmagic

This keymap supports Bootmagic Lite. Bootmagic configures the keyboard when initializing (starting up after connecting the USB cable). 
- hold key in upper left corner while plugging in the USB cable to enter the Bootloader for flashing.
- hold M key while plugging in the USB cable to use the keyboard in MacOs mode.
- hold W key while plugging in the USB cable to use the keyboard in Windows mode.


## Build

Owners of an older Planck (rev5 or older, those without a USB-C connector) need to disable audio in file 'rules .mk' before building. Otherwise the firmware size will be too large.
