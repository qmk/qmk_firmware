qmk compile -kb planck/light -km odzlightreader
dfu-programmer at90usb1286 erase && dfu-programmer at90usb1286  flash .build/planck_light_odzlightreader.hex
