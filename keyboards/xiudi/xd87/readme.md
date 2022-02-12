# XD87

![XD87](https://i.imgur.com/qVyOies.jpg)


- Keyboard Maintainer: [Alexander Fougner](https://github.com/fougner)  
- Hardware Supported: XD87 PCB v1.1  
- Hardware Availability:  
	- [KPrepublic.com](https://kprepublic.com/products/xd87-xd87-xd80-custom-mechanical-keyboard-kit80-supports-tkg-tools-support-underglow-rgb-pcb-programmed-gh80-kle)
	- [AliExpress](https://www.aliexpress.com/item/xd87-XD87-XD80-Custom-Mechanical-Keyboard-Kit80-Supports-TKG-TOOLS-Support-Underglow-RGB-PCB-programmed-gh80/32892540743.html)

Make example for this keyboard (after setting up your build environment):

    make xiudi/xd87:default

It also supports the tkl_ansi and tkl_iso community layouts:

	  # Build firmware with ANSI layout
	  make xiudi/xd87:default_tkl_ansi
	  # Build firmware with ISO layout
	  make xiudi/xd87:default_tkl_iso


The keyboard can be reset to bootloader by using bootmagic (top left key by default) or short out the small connector between the Delete and End keys.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).