# Plack40


Handwired version of Planck, currently support ProMicro.

* Keyboard Maintainer: [Klesh Wong](https://github.com/klesh)
* Hardware Supported: ProMicro


Building Guide :
1. Wire up all keys like this
   `photo to be attach`
2. Create your own keymap on [qmk configurator](https://config.qmk.fm) or follow [offical building guide](https://beta.docs.qmk.fm/tutorial/newbs_building_firmware)
3. Clone this repo and follow [qmk guide](https://docs.qmk.fm/#/newbs_getting_started) to setup qmk
4. Build and flash
   - Flash with json from qmk configurator: `sudo qmk flash path/to/your.json` (you can use planck json file, just change the `layout` to `LAYOUT_plack_2x2u` and `keyboard` to `handwired/plack` and you are good to go)
   - Flash with default keymap: `sudo qmk flash -kb handwired -km 2x2u` (not recommended, only to testing purpose)

