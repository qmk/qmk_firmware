# A Colemak keymap for the Redox keyboard

----
![jeherve-redox-layout-5](https://user-images.githubusercontent.com/426388/116534030-56f67600-a8e2-11eb-9bf3-3ce5362d717a.png)

----

This keymap is **a work in progress**, and is meant to be used on macOS, with the "Unicode Hex Input" keyboard input.

![macOS keyboard input setting](https://user-images.githubusercontent.com/426388/43962498-1ee9e3fc-9cb8-11e8-88e3-dbb068ec5c67.png)

I may change a lot of the keys over the next few months, and will update this repo when I do so.

[View on KLE](http://www.keyboard-layout-editor.com/#/gists/3d5368842d87a8462c8f95d4382c4a19)

## Layers

My keymap uses 5 layers:

1. The default base layer, using [Colemak](https://colemak.com/).
2. A Symbol layer, so all symbols can be accessed from the home row. (top right legends)
3. A Navigation / Media layer, with both sound control and arrows on the home row. (bottom right legends)
4. An international / Emoji layer so I can type accented characters commonly used in France and in Hungary, as well as a few Emoji I often use. (top center legends)
5. A keyboard control layer, not pictured above, allowing me to control the LED lighting as well as the keyboard debug functions.

## Changelog

- 2021.04.29
	- Update code to replace deprecated code.
	- Fix non-breaking space key.
- 2018.12.20
	- 2 new Macro keys, to invoke [Alfred](https://www.alfredapp.com/) and [1Password](https://1password.com/).
	- No more Right Command key or Expose key, I didn't use those much.
	- Updates to use newer QMK function to call ¯\_(ツ)_/¯
	- Fix: you can now move back to the base layer when double tapping the thumb keys to switch to the Nav layer. 👍
- 2018.09.06
	- Initial submission to QMK. It's alive! ⌨️

## Credits

- Redox keyboard design by [Mattia Dal Ben](https://github.com/mattdibi/redox-keyboard).
- This keymap is based off the default keymap for the Redox keyboard, available [here](https://github.com/qmk/qmk_firmware/tree/master/keyboards/redox) and also build by Mattia Dal Ben (thank you!).
- This layout uses [QMK keyboard controller firmware](https://github.com/qmk/qmk_firmware/).

I've also read posts by [Gergely Nagy](https://asylum.madhouse-project.org/blog/2016/10/15/multi-purpose-keys/), [Rebecca Le](https://sevenseacat.net/posts/2018/unicode-in-qmk-on-osx/), and [Justin Rogers](https://implementsblog.com/2016/10/16/my-ergodox-ezs-custom-layout/#comments) for inspiration.
