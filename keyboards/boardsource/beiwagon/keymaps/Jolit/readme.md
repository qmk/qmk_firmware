# Jolit Beiwagon artsey.io

- Author: Victor Nguyen
- This is the [artsey.io](https://artsey.io/) left hand keymap but tweaked for 3x4 configuration. We will use the extra keys for dedicated functions like enter, shift, backspace, space.
- artsey.io version 0.81 was used at the time of creation of this keymap
- So I built this using the deprecated code for artsey qmk. I will leave this here because it ultimately worked
- QMK Compile Command:

    ```Makefile
    qmk compile -kb boardsource/beiwagon -km Jolit
    ```

- For now this code will be local and will not use a userspace like T4CORUN or another for Jolit.

---

## General Notes

- [artsey.io introduction video](https://www.youtube.com/watch?v=dicYf7OiS3Q&feature=youtu.be)
- [artsey.io github deprecated](https://github.com/artseyio/artsey-qmk)
- [artsey.io github](https://github.com/artseyio/qmk-artsey/)
- Default Shortcut guide
-[Shortcut guide deprecated](https://raw.githubusercontent.com/artseyio/artsey/main/layout%20diagrams/current.jpg)
-[Shortcut Guide](https://cdn.discordapp.com/attachments/775496087548723242/873686510656970853/current.jpg)

---

## Changelog

2022-02-27

- Created a beiwagon keymap for Jolit
- Copied the required files per the readme.md for both sides into the keymap in case we wanted to switch hands
- Translated the artsey.io layout to the macropad layout. Put the extra keys in the bottom row for thumb use
- I updated the T4CORUN userspace keymap to add some fine tuning for mousekeys
- I can't test it yet as we don't have the board but I compiled it and it fits on the MCU

2022-03-05

- Added LOWER, RAISE, and ADJUST layers. LOWER is the function layer. RAISE is RGB control. ADJUST is just in case
- Added new combos for the function keys. For example F1 and F2 give F9
- Added per key TAPPING TERM so she doesn't accidentally trigger LOWER and RAISE

--

## Think about/To Do

- What I notice was missing

	- Function Row (F1-F12). Could replace the mouse layer with function layer?
	- App. She does not use this
	- No controls for RGB

- 