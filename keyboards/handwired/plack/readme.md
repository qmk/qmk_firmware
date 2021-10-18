# Plack


Handwired version of Planck, currently support ProMicro.

![plack](https://user-images.githubusercontent.com/61080/137662875-ba40cf4b-7d50-4e9b-9d97-3353677ba9bb.jpg)


* Keyboard Maintainer: [Klesh Wong](https://github.com/klesh)
* Hardware Supported: ProMicro


Building Guide :
1. Wire up all switches like this
   ![soldering](https://user-images.githubusercontent.com/61080/137662877-d183f2ff-387a-44ee-a4fa-86e8c3fa0b8e.jpg)
2. Create your own keymap on [qmk configurator](https://config.qmk.fm)
3. Flash controller:
   - Windows/macOS: download compiled firmware from **qmk configurator** and flash with [qmk toolbox](https://github.com/qmk/qmk_toolbox)
   - Linux: download keymap json file from **qmk configurator** and flash with [qmk cli](https://github.com/qmk/qmk_cli): `sudo qmk flash path/to/your.json`
   notes: you can use planck keymap json file, just change the `layout` to `LAYOUT_plack_2x2u` (or `LAYOUT_plack` if you are using full 48 keys) and `keyboard` to `handwired/plack` and you are good to go


