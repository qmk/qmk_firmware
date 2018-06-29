KBD75
===

Keyboard Maintainer: QMK Community  
Hardware Supported: KBD75 PCB rev 1 and 2 
Hardware Availability: https://kbdfans.myshopify.com/products/kbd75-keyboard-set?variant=35638534029

The KBD75 has two revisions. Revision 2 has a USB C port and allows a numpad layout. `.hex` files made
for KBD75 revision 1, will still work for revision 2. `.hex` files made for revision 2 (excluding the numpad)
will also still work on revision 1. Both revisions share the same switch matrix but have switch holes in 
different areas. 

Make example for this keyboard (after setting up your build environment):

    make kbd75/rev1:default
    make kbd75/rev2:default

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.
