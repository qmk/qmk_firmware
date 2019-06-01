# Citadel keymap for pegasushoof

Designed for ISO-DE and similar ISO layouts. 

The central idea of this keymap is to avoid unergonomic key combos that force the user to either press
multiple keys with one hand or to use the left hand for right-sided keys. For instance, ISO-DE users
have to press `AltGr`+`7` to type _{_. The keymap allows ergonomic access to the right-sided keys of the
German AltGr-layer by turning `Caps Lock` into a hybrid Fn/AltGr-key. It can easily be adapted for other
ISO layouts.

The _Function_ layer also offers mouse emulation and function/media keys in the F-Row.

`Pause/Break` is used as a safe _close key_: A _single tap_ does nothing, a _double tap_ executes ALT+F4.

Named after the homonymous space station from _Mass Effect_. Made by [Daniel Rose](https://github.com/droseger/).

## [1] Layers  

### Layer 1 (Default)  
    .----.   .-------------------. .-------------------. .-------------------. .--------------.  
    |Esc |   |F1  |F2  |F3  |F4  | |F5  |F6  |F7  |F8  | |F9  |F10 |F11 |F12 | |PrSc|SLck|2Tp:|  
    |    |   |    |    |    |    | |    |    |    |    | |    |    |    |    | |SyRq|    |A+F4|  
    '----'   '-------------------' '-------------------' '-------------------' '--------------'  
    .------------------------------------------------------------------------. .--------------.  
    |°   |!   |"   |§   |$   |%   |&   |/   |(   |)   |=   |?   |`   |Backspa| |Ins |Home|PgUp|  
    |^   |1   |2  ²|3  ³|4   |5   |6   |7  {|8  [|9  ]|0  }|ß  \|´   |       | |    |    |    |  
    |------------------------------------------------------------------------| |--------------|  
    |Tab   |Q   |W   |E   |R   |T   |Z   |U   |I   |O   |P   |Ü   |*   |  E  | |Del |End |PgDn|  
    |      |    |    |   €|    |    |    |    |    |    |    |    |+  ~|  n  | |    |    |    |  
    |------------------------------------------------------------------\  t  | '--------------'  
    |Fn:    |A   |S   |D   |F   |G   |H   |J   |K   |L   |Ö   |Ä   |'   | e  |  
    |Layer 2|    |    |    |    |    |    |    |    |    |    |    |#   | r  |  
    |------------------------------------------------------------------------|      .----.  
    |Shift|>   |Y   |X   |C   |V   |B   |N   |M   |;   |:   |_   |Shift      |      |Up  |  
    |     |<  ¦|    |    |    |    |    |    |   µ|,   |.   |-   |           |      |    |  
    |------------------------------------------------------------------------| .--------------.  
    |Ctrl |Super|Alt  |                              |AltGr|Alt  |Fn:  |Ctrl | |Left|Down|Righ|  
    |     |     |     |                              |     |     |Lay 2|     | |    |    |    |  
    '------------------------------------------------------------------------' '--------------'  

### Layer 2 (Function)
    .----.   .-------------------. .-------------------. .-------------------. .--------------.  
    |Ctl+|   |My  |WWW:|Calc|Medi| |Mus:|Mus:|Mus:|Mus:| |Vol:|Vol:|Vol:|See:| |    |    |Paus|  
    |A+De|   |Comp|Home|    |Play| |Prev|Next|Paus|Stop| |Mute|Down|Up  |[3] | |    |    |Brea|  
    '----'   '-------------------' '-------------------' '-------------------' '--------------'  
    .------------------------------------------------------------------------. .--------------.  
    |    |    |    |    |    |    |    |    |    |    |    |    |    |       | |    |    |Mou:|  
    |    |    |    |    |    |    |    |{   |[   |]   |}   |\   |    |       | |    |    |WhUp|  
    |------------------------------------------------------------------------| |--------------|  
    |      |    |    |    |    |    |    |    |    |    |    |    |~   |     | |    |    |Mou:|  
    |      |    |    |    |    |    |    |    |    |    |    |    |    |     | |    |    |WhDn|  
    |------------------------------------------------------------------\     | '--------------'  
    |CapsLck|Mou:|Mou:|    |    |    |    |    |    |    |    |    |    |    |  
    |       |Fast|Slow|    |    |    |    |    |    |    |    |    |    |    |  
    |------------------------------------------------------------------------|      .----.  
    |     |    |    |    |    |    |    |    |µ   |    |    |    |           |      |Mou:|  
    |     |    |    |    |    |    |    |    |    |    |    |    |           |      |Up  |  
    |------------------------------------------------------------------------| .--------------.  
    |Mous:|Mous:|     |                              |     |Super|App  |     | |Mou:|Mou:|Mou:|  
    |Bttn2|Bttn1|     |                              |     |     |     |     | |Left|Down|Righ|  
    '------------------------------------------------------------------------' '--------------'  

Layer 3 exists solely to prevent users from accidentally activating boot mode: `R` is redefined
as `RESET` key [3].

## [2] How to build and install
1) Prerequisite: install the necessary [build tools](https://docs.qmk.fm/#/getting_started_build_tools)
such as [dfu-programmer](https://github.com/dfu-programmer/dfu-programmer).
   - You might need to [add udev rules](https://docs.qmk.fm/#/faq_build?id=can39t-program-on-linux) under Linux.
2) To test if the keymap compiles, simply run `make pegasushoof:citadel`
3) Enter the `qmk_firmware` root directory and run `make pegasushoof:citadel:dfu`
4) Reset controller to _Boot mode_ by pressing the `RESET` key or by using a magnet.

## [3] How to access Boot mode after install
Press `Fn+F12+R`
