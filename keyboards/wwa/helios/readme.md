# helios

![helios](https://imgur.com/a/mXWRgCt)

First model of the Argentinian based keyboard manufacturer WWA

* Keyboard Maintainer: [spacehangover](https://github.com/spacehangover)
* Hardware Supported: RP2040 Handwired
* Hardware Availability: https://www.amazon.com/dp/B08ZSKMJJD/ref=sspa_dk_detail_6?psc=1&pd_rd_i=B08ZSKMJJD&pd_rd_w=K8K1X&content-id=amzn1.sym.08ba9b95-1385-44b0-b652-c46acdff309c&pf_rd_p=08ba9b95-1385-44b0-b652-c46acdff309c&pf_rd_r=3W158XFKMFJTGARYNNT6&pd_rd_wg=ADHNt&pd_rd_r=7e2afce9-17d9-46a7-b196-5be2ab375f40&s=pc&sp_csd=d2lkZ2V0TmFtZT1zcF9kZXRhaWxfdGhlbWF0aWM&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEyQTU4SElNN0VVNVdXJmVuY3J5cHRlZElkPUEwNTA3MTMwMlZDSDVMVEQwQ0ZPTSZlbmNyeXB0ZWRBZElkPUEwMDgzMTI4MUE4UkxCWEpCTVk5ViZ3aWRnZXROYW1lPXNwX2RldGFpbF90aGVtYXRpYyZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=

Make example for this keyboard (after setting up your build environment):

    make helios:default

Flashing example for this keyboard:

    make helios:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
