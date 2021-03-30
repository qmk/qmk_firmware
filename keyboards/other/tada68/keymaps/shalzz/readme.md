# Shalzz's Unix layout

This layout is based on the Unix Layout with a few changes.

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
      Fn    + LShift = (
      Fn    + RShift = )

 Fn Layer
,----------------------------------------------------------------.
|   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |PRSC|
|----------------------------------------------------------------|
|     |   |Up |   |   |   |   |   |   |   |   |   |   |     |Ins |
|----------------------------------------------------------------|
|      |<- |Dn | ->|   |   |<- |Dn |Up | ->|   |   |        |Hme |
|----------------------------------------------------------------|
|    (   |   |   |Bl-|BL |BL+|   |   |VU-|VU+|MUT|   )  |   |End |
|----------------------------------------------------------------|
|    |    |    |                       |   |   |    |   |   |    |
`----------------------------------------------------------------'

```

The changes that were applied over the Unix layout:

* Left and Right Shift when pressed alone emit `(` and `)` respectively. Hold shift for normal behaviour.
* Fn + Left and Right Shift also act as actual `(` and `)` keys respectively.
* Changed PrintSc to `Fn+``
* Fixed Holding down space activating the function layer instead of the lower layer.
