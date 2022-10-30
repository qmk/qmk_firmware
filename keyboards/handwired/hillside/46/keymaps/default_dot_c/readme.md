# Default Hillside 46 Layout (in .c format)

This layout is for those who prefer defining their layout in a keymap.c,
  instead of graphically with a keymap.json.
It is the same as the [default keymap.json layout](https://github.com/qmk/qmk_firmware/blob/master/keyboards/handwired/hillside/46/keymaps/default),
  except for having only a QWERTY base layer.
  
The make and flash commands are

```
make handwired/hillside/46:default_dot_c
make handwired/hillside/46:default_doc_c:flash

```

It also serves as a simple, clean layout 
  to verify that the configuration and switches work.
Use the [QMK Configurator Tester](https://config.qmk.fm/#/test) 
 to see that the switches produce output.
All the keys should register on the layout tester 
  except for the caps word and the two layer keys.
The LEDs should glow a nice red.
If they do not, you may need to clear the persistent EEPROM settings with the
  EE_CLR key on the adjust layer,
  or enable them with the RGB_TOG key.
