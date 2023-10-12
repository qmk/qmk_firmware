# nstickney's Ortholinear Layout
 
 > Familiar layout for users who regularly switch between Bastyl/Iris and standard QWERTY.

## Install

For instructions on building and installing this keymap, see the [docs](https://docs.qmk.fm/#/getting_started_make_guide).
Below is the command for me; it may be different for you.
Note that my Iris keyboard has an Elite-C on the left half and a ProMicro on the right half.

- Bastyl: `make hidtech/bastyl:nstickney:dfu`
- Iris
	- Elite-C: `make keebio/iris/rev2:nstickney:dfu`
	- ProMicro: `make keebio/iris/rev2:nstickney:avrdude`

## Usage

0. QWERTY `BASE` layer.
	* `/`, `\`, `[SPACE]`, `[ENTER]`, `-`, and `=` on the thumb clusters.
		* `[` and `]` added on Bastyl.
	* `CAPSLOCK` replaced by `ESC`; hold it down for `CTRL`.
		* `'` can also be held for `CTRL`.
	* [Space-Cadet Shift](https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_space_cadet) is enabled, so the `SHIFT` keys send `(` and `)` when tapped.
	* Hold down `/` or `=` for `ALT`.
	* Hold down `\` or `-` to access the functions layer.
	* Farthest thumb keys are `GUI` (left) and `MENU` (right).
		* Tapping `GUI` 2, 3, or 4 times will toggle `NUMLOCK`, `CAPSLOCK`, or `SCROLLLOCK`, respectively.
		* Tapping `MENU` 2 or 3 times will toggle the `NUMP` and `SYMB` layers, respectively.
0. Unicode-input symbols on `SYMB` layer. Based (loosely) on US-International layout.
0. `NUMP` layer has number pads on each hand. Number pad `7`-`8`-`9` align with QWERTY `7`-`8`-`9` on right hand.
0. Function, arrow, media, and miscellaneous keys on `FCTN` layer.
	* `F1` through `F10` on `1`-`10`. `F11` is on `GUI` and `F12` is on `MENU`.
	* Brackets (`[` and `]`) available on `U` and `I`; braces (`{` and `}`) on `O` and `P`.
	* Arrow keys on `ESDF` and `HJKL`; familiar for both Vim users and FPS gamers.
	* `W` is `HOME`; `R` is `END`. `T` is `PAGE UP` and `G` is `PAGE DOWN`.
	* Music controls on lower row of left hand.
	* Volume and screen brightness on lower row of right hand.
	* `PRINT SCREEN`, `PAUSE`, `SYSREQ`, `INSERT`, and `CLEAR` also mapped, as intelligently as possible.
	* `Q` toggles the RGB underglow (which changes color to indicate active layer).
	* `A` increases RGB underglow brightness (with `SHIFT`, decreases brightness).
	* `Y` is mapped to [`QK_LOCK`](https://beta.docs.qmk.fm/using-qmk/software-features/feature_key_lock).

## Contribute

If you are using this layout and think you've found a better way to do something, I'd appreciate an [issue](https://github.com/nstickney/qmk_firmware/issues), or better yet a [pull request](https://github.com/nstickney/qmk_firmware/pulls).

## License

Copyright &copy; 2016-2021 @nstickney. Released under [GPL-2.0](/LICENSE).
