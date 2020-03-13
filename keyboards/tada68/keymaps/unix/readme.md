# tracyde Unix layout

This layout is friendlier to those that spend the majority of their time in the *nix commandline.

```
 Base Layer
,----------------------------------------------------------------.
|Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
|----------------------------------------------------------------|
|Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
|----------------------------------------------------------------|
|CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
|----------------------------------------------------------------|
|Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
|----------------------------------------------------------------|
|Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
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
|    |    |    |                       |   |   |    |   |   |    |
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