# hyper7 - h7 v3.0

* Keyboard Maintainer: [bit-shifter](https://github.com/bit-shifter)
* KLE [layout](http://www.keyboard-layout-editor.com/#/gists/daf4d5f4f80466c4d7e5fa04a9b2b0b3)


## Setting the unicode input mode

Pressing the [Function]-[Mode] key combination will cycle through the configured input modes:

1. UC_LNX (default)
2. UC_MAC
3. UC_WIN

The input mode is not persisted

For additional information, see QMK's unicode (documentation)[https://docs.qmk.fm/#/feature_unicode]:


## Compiling the firmware

Make example for this keyboard (after setting up your build environment):

    make hyper7/h7/v3:default

QMK build command:

    qmk flash -kb hyper7/h7/v3 -km default -bl dfu

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
