# Kimiko rev2 default keymap

A split keyboard with 4x6 vertically staggered keys and thumb keys.

- 60 Per key RGB led's (SK6812 Mini-E)
	- RGB Matrix is enabled as default in rules.mk
	- the effects can be configured in config.h 
	- The image below shows the positioning of switches and led as defined in the info.json. Text in the boxes:<br /> 
		- Layout Label<br /> 
		- Matrix Position<br /> 
		- LED flag for type of switch<br /> 
<img src="https://github.com/Ex3c4Def/dev_images/blob/main/kimiko_rev2_layout_position_matrix.png" width="800" />

	
- Support for 1 rotary encoder per side (two possible positions)  
  
- Support for 1 pointing device (two possible positions)  
	- Pimoroni Trackball is enabled as default in rules.mk  
	- can be configured in config.h, e.g. for roation at different mounting position  
	- RGB lightning can be used for layer indication, but the Pimoroni Trackballmust be on the master side for this  
  	
- Support for 1 OLED display per side  
	- 128x32 or 128x64 are supported  
	- with 1 OLED on each side, they have to be the same  
	- default configuration for 128x32 OLED  
	- 128x64 OLED can be set with #define OLED_DISPLAY_128X64 in config.h (already prepared)  
<br />  

* Keyboard Maintainer: [BenRoe](https://github.com/BenRoe/) [@keycapsss](https://twitter.com/keycapsss)
* Hardware Supported: Pro Micro 5V/16Mhz and compatible
* Hardware Availability: [keycapsss.com](https://keycapsss.com)
Make firmware .hex for this keyboard (after setting up your build environment):

    make keycapsss/kimiko:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
<br />
<br />  

* For debugging:
	- positioning of switches and led as defined in the info.json. Text in the boxes::<br />   
		- Layout Label<br />   
		- switch number in schematic<br />   
		- led number in schematic<br />   
		- led flag for type of switch<br /> 
<img src="https://github.com/Ex3c4Def/dev_images/blob/main/kimiko_rev2_layout_position_schematic.png" width="800" />
<br /> 
<br /> 
