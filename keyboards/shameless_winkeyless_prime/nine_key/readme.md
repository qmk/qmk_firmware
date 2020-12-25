# nine_key

* Keyboard Maintainer: QMK Community
* Hardware Supported: 9 key mini keyboards based on winkeyless.kr firmware with HIDBoot 
* Original Hardware Availability: <http://winkeyless.kr/product/b-mini-x2-pcb/>

This is RGB 9 key mini keyboard made by the likes of Chineese companies like Koolertron and Vaydeer.  This blatently rip off the poor dude at 
winkeyless.kr, stealing his firmware and cloning the guts of his hardware - heck, they even show up as a winkeyless.kr product when they
are plugged in:

[64448.671064] usb 5-6.1.4: Product: ps2avrGB
[64448.671065] usb 5-6.1.4: Manufacturer: winkeyless.kr

The prime in shameless_winkeyless_prime doesn't mean prime as in premium, top quality or even a number that is only
divisible by one and itself, but as in derivative of (prime notation for differentiation).


Here is a link to one of these shameless rip offs: 
https://www.amazon.de/-/en/Koolertron-one-hand-keyboard-mechanical-programmable/dp/B07VY2HKFZ

This code is all based on the Winkeyless B.mini, keymaps and numbers of keys have been adjusted.  Everything else is basically
the same.


Make example for this keyboard (after setting up your build environment):

    make shameless_winkeyless_prime/nine_key
    - or -
    qmk compile -kb shameless_winkeyless_prime/nine_key -km default

Flashing example for this keyboard ([after setting up the bootloadHID flashing environment](https://docs.qmk.fm/#/flashing_bootloadhid))

    qmk flash -kb shameless_winkeyless_prime/nine_key -km default

This firmware can be flashed onto the device once bootloadHID is in place.

**Activate booloadHID**: Hold down any key while plugging in the USB-C connector.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
