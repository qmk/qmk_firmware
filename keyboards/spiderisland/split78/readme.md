# SpiderIsland Split 78-key

![Board Photo](https://i.imgur.com/N3DjdGql.jpg)  
[Image Gallery](https://imgur.com/a/0AUY8Ng)

The 78 key split keyboard from [SpiderIsland on AliExpress](https://a.aliexpress.com/_dVJsSpR).
Out of the box it runs ps2avrGB firmware, like [`split75`](../../wheatfield/split75/README.md).
It is mistakenly called "87 key" on the AliExpress title and "104 key" (?!) in the caption inside the photo.

This port is based on the `split75` port which was mostly done by [Michael L. Walker](https://github.com/walkerstop).

* Keyboard Maintainer: [unrelenting.technology](https://github.com/unrelentingtech)
* Hardware Availability: https://a.aliexpress.com/_dVJsSpR

Make example for this keyboard (after setting up your build environment):

    make spiderisland/split78:default

Flashing example for this keyboard:

    make spiderisland/split78:default:flash

**Reset Key**: Hold down the key located at the leftmost position in the top row, commonly programmed as Escape while plugging in the keyboard.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
