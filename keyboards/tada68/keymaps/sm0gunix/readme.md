```
 ________  _____ ______   ________  ________  ________           _________  ________  ________  ________  ________  ________     
|\   ____\|\   _ \  _   \|\   __  \|\   ____\|\   ____\         |\___   ___\\   __  \|\   ___ \|\   __  \|\   ____\|\   __  \    
\ \  \___|\ \  \\\__\ \  \ \  \|\  \ \  \___|\ \  \___|_        \|___ \  \_\ \  \|\  \ \  \_|\ \ \  \|\  \ \  \___|\ \  \|\  \   
 \ \_____  \ \  \\|__| \  \ \  \\\  \ \  \  __\ \_____  \            \ \  \ \ \   __  \ \  \ \\ \ \   __  \ \  \____\ \   __  \  
  \|____|\  \ \  \    \ \  \ \  \\\  \ \  \|\  \|____|\  \            \ \  \ \ \  \ \  \ \  \_\\ \ \  \ \  \ \  ___  \ \  \|\  \ 
    ____\_\  \ \__\    \ \__\ \_______\ \_______\____\_\  \            \ \__\ \ \__\ \__\ \_______\ \__\ \__\ \_______\ \_______\
   |\_________\|__|     \|__|\|_______|\|_______|\_________\            \|__|  \|__|\|__|\|_______|\|__|\|__|\|_______|\|_______|
   \|_________|                                 \|_________|                                                                     

```

This layout is friendlier to those that spend the majority of their time in the *nix commandline. 
Stolen from tracyde's Unix layout, with a few personal tweaks. 

```
 Base Layer
 ,----------------------------------------------------------------.
 |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|   \   |~ ` |
 |----------------------------------------------------------------|
 |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Bksp |Del |
 |----------------------------------------------------------------|
 |Ctrl   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
 |----------------------------------------------------------------|
 |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
 |----------------------------------------------------------------|
 |CAPS|Win |Alt |        Space          |FN| Ctrl|Alt|Lef|Dow|Rig |
 `----------------------------------------------------------------'
Note: Shift + Esc = ~
      Win   + Esc = `
      Hold  + RShift = (
      Hold  + LShift = )


 Fn Layer
,----------------------------------------------------------------.
|   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |    |
|----------------------------------------------------------------|
|     |   |Up |   |   |   |   |   |   |   |   |   |   |     |Ins |
|----------------------------------------------------------------|
|      |<- |Dn | ->|   |   |<- |Dn |Up | ->|   |   |        |Hme |
|----------------------------------------------------------------|
|        |   |   |Bl-|BL |BL+|   |   |VU-|VU+|MUT|      |   |End |
|----------------------------------------------------------------|
|    |    |    |                       |   |   |    |Prv|P/P|Nxt |
`----------------------------------------------------------------'

```

The changes that were applied over default layout:

* Left and Right Shift when pressed alone emit `(` and `)` respectively. Press the opposite Shift to cancel.
* Leds go into breath animation when USB suspends (because why not).
* Holding down space activates the lower layer.
* Changed Home and End to `Fn+PgUpPgDn`
* Changed Insert to `Fn+Del`
* Removed mouse movement.
* Changed volume controls to `Fn+,./` (this makes volume controls make more sense `<` `>` act as you think they should)
* Added arrow cluster as Fn+hjkl (vim users rejoice)
* 'Grave-Escape' the escape key. This will allow the Esc key to function like Esc when pressed but act like the Grave key when pressed along with GUI or Shift keys. This allows you to use the Apple hotkey of CMD + ~ to switch between windows of the same app. In my config.h file I implemented the override 'GRAVE_ESC_ALT_OVERRIDE'. This will force ESC to be registered when hitting ALT. This preserves the Apple hotkey Cmd+Opt+Esc.
