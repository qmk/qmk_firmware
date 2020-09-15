# YD60

![YD60 PCB](https://ae01.alicdn.com/kf/HTB1PVQ2X_HuK1RkSndVq6xVwpXaO.jpg)

Customizable 60% PCB by [YMDK](https://www.aliexpress.com/item/32799437588.html?spm=a2g0o.productlist.0.0.32516526CmOyN0&algo_pvid=75c87083-03b0-4c57-b2cd-5bd76bd5c3c0&algo_expid=75c87083-03b0-4c57-b2cd-5bd76bd5c3c0-0&btsid=0bb0620316001191473194113ee1e5&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)

* Keyboard Maintainer: QMK Community
* Hardware Supported: YD60
* Hardware Availability: [YMDK on AliExpress](https://ymdk.aliexpress.com/store/429151?spm=2114.10010108.0.0.3ab23641lIkgzm)

Make example for this keyboard (after setting up your build environment):

```sh
make yd60:default	# default build
make yd60:via		# via build
```

The keyboard uses a DFU bootloader. To make a keymap and use dfu to flash it:

```sh
make yd60:default:flash        # builds and flashes the default keymap
make yd60:via:flash  # also builds and flashes the via hex
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
