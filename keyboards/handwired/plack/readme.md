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


Using VIA:
1. Build and Flash VIA firmware `qmk flash -kb handwired/plack -km via` (only for 2x2u layout)
2. Download and install [VIA](https://github.com/the-via/releases/releases/latest)
3. Launch VIA, Goto **SETTINGS**, Enable **Show Design Tab**
4. Click on newly appeared **DESIGN** tab, click **Load** button and select [vial.json](keymaps/via/vial.json) file
5. SWitch to **CONFIGURE** tab, you should be able to configure your keys now
