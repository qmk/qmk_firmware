# GH60 Rev C

![gh60 Rev C PCB](https://i.imgur.com/FejpoNF.jpg)

A common 60% PCB.

Keyboard Maintainer: QMK Community  
Hardware Supported: GH60 rev. B and rev. C  
Hardware Availability: http://blog.komar.be/projects/gh60-programmable-keyboard/

Make example for this keyboard (after setting up your build environment):

    make gh60/revc:default

**Note:** This GH60 firmware will not be compatible with the GH60 Satan PCB. Conversely, the GH60 Satan firmware will not be compatible with this PCB. Please ensure you have the correct firmware/pcb combination before flashing. 

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## GH60 Hardware Information

    /* Column pin configuration
    * col: 0   1   2   3   4   5   6   7   8   9   10  11  12  13
    * pin: F0  F1  E6  C7  C6  B6  D4  B1  B7  B5  B4  D7  D6  B3  (Rev.C)
    */
     
    /* Row pin configuration
    * row: 0   1   2   3   4
    * pin: D0  D1  D2  D3  D5
    */
     
    GPIO pads
    0 F7 WASD LEDs
    1 F6 ESC LED
    2 F5 FN LED
    3 F4 POKER Arrow LEDs
     
    B2 Capslock LED
    B0 not connected
	
Functions to controls LED clusters
	
    gh60_caps_led_on()
    gh60_poker_leds_on()
    gh60_fn_led_on()
    gh60_esc_led_on()
    gh60_wasd_leds_on()
    
    gh60_caps_led_off()
    gh60_poker_leds_off()
    gh60_fn_led_off()
    gh60_esc_led_off()
    gh60_wasd_leds_off()
