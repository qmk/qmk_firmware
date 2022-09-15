![no qmk?](https://user-images.githubusercontent.com/60044824/181124856-0ebe0cc9-4b91-4fa2-89df-4e0841a61b9d.png)


# Custom keymap for Sofle Keyboard, based on [Helltm](https://github.com/qmk/qmk_firmware/tree/master/keyboards/sofle/keymaps/helltm)

Features:

- Symmetric modifiers (CMD/Super, Alt/Opt, Ctrl, Shift)
- Various modes, can be switched (using Adjust layer and the selected one is stored in EEPROM).
- Modes for Qwerty and Colemak support
- Modes for Mac vs Linux/Win support -> different order of modifiers and different action shortcuts on the "UPPER" layer. Designed to simplify transtions when switching between operating systems often.
- The OLED on master half shows selected mode and caps lock state and is rotated.
- Left encoder controls volume up/down/mute. Right encoder PREV/NEXT media controls.
- Keyboard lock, change to the adjust layer (up and down pressed at the same time) and press the left shift to lock/unlock, current lock state is displayed on oled
- Apple logo for Mac mode, Fedora Silverblue logo for Linux/Win mode, Lock icon for locked
- Fixed flickering on main OLED
- Gaming layout, switches space to the left half of the keyboard and raises the most left column up by one key

#Luna, the keyboard pet

Features:
- Luna reacts to your wpm counter
    - under 10 wpm she sits
    - between 10 and 40 wpm she walks
    - over 40 wpm she runs
- She will move sneakily if you hold down Ctrl
- Will bark at people on the internet if you activate Caps Lock!
- Luna jumps every time you hit Space
