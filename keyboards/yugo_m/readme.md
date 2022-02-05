# Yugo-M - An STM32-based IBM Model M controller

A drop-in replacement controller PCB for IBM Model M keyboards. 
Currently available only for 101/102 key keyboards. 

* Keyboard Maintainer: [Nidzo Tomic](https://github.com/tomic1785)
* Hardware Supported: Yugo-M PCB
  * Rev 0.9b
  * Rev 1.1b

For more info visit the project repository: [Yugo-M-controller-project](https://github.com/tomic1785/Yugo-M-controller-project)



Note regarding 2022 matrix update:

The original author's firmware did not make several lesser-used membrane/matrix positions available to the controller. These are useful for JIS users and/or if you simply want to create a more unique layout. I've added all of the unused membrane positions to the firmware, except for an extremely seldom used one that sits in the left side of the space bar on some later membranes (I would have added it if I knew its matrix position, but I haven't mapped that out yet). The default mappings for these additional keys follow JIS conventions, except for the extra key on the bottom right corner of the numpad (lower half of vertical 2u Enter), which I've mapped to the LGUI key a.k.a. left Windows/Command key for now. Remap as you wish!

- an_achronism, February 2022