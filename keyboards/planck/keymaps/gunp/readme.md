![Cheat sheet for gunpinyo layout for Planck](https://drive.google.com/uc?export=view&id=1INtnZhzoHpPkZ2kueP1K0Dpr6T1spr4m)

# gunpinyo layout for Planck

* Keymap Maintainer: [Gun Pinyo](https://github.com/gunpinyo)

This is a personal keymap for myself. Almost all of important information is in
the following picture of cheat sheet above; there is also the text-version of
this cheat sheet at the end of this readme file. Please note that this layout
doesn't employ any transparent keycode, therefore, empty keycodes (including
dummy keycodes `XXX`) are all no-op.

The base layer is `LY-0000`, most of keycodes in this layer is self-explained in
the cheat sheet. Next, we have custom keycodes called `funcA`, `funcB`,
`funcC`, and `funcD` (I will call each of them `funcX` for short) which will
switch layout to `LY-ABCD` depending the binary state of each keycode where the
corresponded binary digit is a boolean "keycode `funcX` is pressed".

This mechanism allows us to access up to 16 different layers, however, only 11
layers are currently used. Each used layer will have its name on the cheat sheet
together with its left-half keymap. Once, each of these layers activates (by a
combination of `funcX` keycodes):
  - the left-half (row0-row3 x col0-col5) will switch according to its
    individual keymap on cheat sheet,
  - the right-half (row0-row3 x col6-col11) will switch to `RIGHT-HALF` keymap
    that are overwritten by all of `funcX` on the same position of the base
    layer (5 positions in total, because `funcD` has 2 positions on top of
    keycode `reset`) and keycodes in binary numbers there are disabled.

Another keycode in the base layer is `stick`. When it is press, the rules of
keyboard change into persistent mode. Here, the right-half is exactly the
`RIG-HALF` keymap. The left-half initially all no-op and can be changed to other
layers by tapping on the corresponded obvious keycodes (including layers
`LY-thaiX` which is not accessible via `funcX`). To switch back to the normal
rules governed by `funcX` press a `reset` keycode.

```
  {H| "LY-0000": base-layer -- "`[🠝]` here becomes `funcD` in other layers" |H}   {8| "RIGHT-HALF":  "when `stick` is on" |8}
  {8| pgup|  Q  |  W  |  F  |  P  |  G  |  J  |  L  |  U  |  Y  |  K  | tab |8}   {H|  0110| [🠜] |bkspc| [🠞] | XXX | XXX  |H}
  {8| pgdn|  A  |  R  |  S  |  T  |  D  |  H  |  N  |  E  |  I  |  O  |stick|8}   {H|  1111|thaiA|thaiB|thaiC| XXX | XXX  |H}
  {8|sft-🠜|  Z  |  X  |  C  |  V  |  B  |  M  |funcA|funcB|funcC| [🠝] |sft-🠞|8}   {H|  0100| 1000| 1010| 0010|reset|sft-🠞 |H}
  {8|ctl-🠜|alt-🠜|gui-🠜| esc |bkspc|enter|funcD|space|print| [🠜] | [🠟] | [🠞] |8}   {H| reset|space|enter|gui-🠞|alt-🠞|ctl-🠞 |H}

  {H| "LY-0100": "col0 as no-op" |H}   {H|  "LY-1101" -- "email: gunpinyo@gmail.com"  |H}   {X|  "LY-0110" -- "gunpinyo"  |X}
  {8| C-G  home  [🠝]  end  C-[🠝] |8}   {8| aud-🠝 sandbox insert XXX  scrLock qmkReset |8}   {✜| S-f7 S-f8  f7 f8 f9  S-f9 |✜}
  {8| pgup  [🠜]  [🠟]  [🠞]  C-[🠟] |8}   {8| aud-🠟 rgbTog rgbMod email capLock qmkDebug |8}   {✜| S-f4 S-f5  f4 f5 f6  S-f6 |✜}
  {8| pgdn  C-S  C-A  C-Z  SC-Z  |8}   {8| sleep dmRec1 dmPlay1 wake numLock qmkKLock |8}   {✜| S-f1 S-f2  f1 f2 f3  S-f3 |✜}
  {8|     C-[🠜]  C-F  C-[🠞]      |8}   {8| power dmRec2 dmPlay2 dmStop XXX  qmkEepRst |8}   {✜|S-f10 S-f11 f10f11f12 S-f12|✜}

  {8|    "LY-1000"    |8}   {8|    "LY-1010"    |8}   {8|    "LY-0010"    |8}   {H| "LY-1111" - "powered by QMK firmware" |H}
  {H|  %  ?  !  `     |H}   {H|  #  7  8  9     |H}   {H|  &  |  ~  ^     |H}   {8| msAC1 msAC0  scr-🠜 mov-🠝 scr-🠞  scr-🠝 |8}
  {H|  @  ,  .  '  =  |H}   {H|  *  4  5  6  +  |H}   {H|  {  [  (  <  /  |H}   {8| msAC2  XXX   mov-🠜 mov-🠟 mov-🠞  scr-🠟 |8}
  {H|  $  ;  : \"  _  |H}   {H|  0  1  2  3  -  |H}   {H|  }  ]  )  >  \  |H}   {8| mPrev btn-🠝  mRWD  mPlay mFFD   btn-✜ |8}
                                                                                {8| mNext btn-🠟  pause mStop btn-🠜  btn-🠞 |8}
  1. PC105 (US: qwerty, TH: kedmanee)     5. "LY-1110" is `gui-🠜` + "LY-0110"
  2. use `G-space` to switch language     6. "LY-1100" is `sft-🠜` + "LY-0100" except [C-S, C-A, C-Z, SC-Z, C-F] which become
  3. when `stick` is off, layer switchers other than `func[ABCD]` are disabled       [C-X, C-C, C-V,  C-L, C-R] respectively
  4. ["LY-1000", "LY-1010", "LY-0010"] omit col0 and row3, but they have all `mod-🠜` from the base-layer, the rest are no-op

  {H| "LY-0001" -- "`mod#🠜` is oneshot-mod" |H}   {8|    "LY-thaiA"   |8}   {8|    "LY-thaiB"   |8}   {8|    "LY-thaiC"   |8}
  {8|  C-H C-0  SC-pgup bri-🠝 SC-pgdn vol-🠝 |8}   {H|  ฌ ‍‍‍ฅ ‍ค  ม ฤ ฦ  |H}   {H|  ์ ‍‍‍‍‍็  ่  ้  ๊  ๋  |H}   {H|  ภ ‍‍ฃ ‍ข  ฮ ‍‍‍ฎ ‍‍ฏ  |H}
  {8| SC-T C-[+] C-pgup bri-🠟  C-pgdn vol-🠟 |8}   {H|  ณ ‍ว ‍‍‍‍‍ง  ‍น ‍‍ร ‍ล  |H}   {H|  โ ‍แ ‍‍‍‍‍‍‍‍‍‍‍เ ‍‍‍‍‍‍‍‍‍‍‍‍‍า ‍‍‍‍‍‍‍‍‍‍‍‍‍ั ‍‍‍‍‍‍‍‍ะ  |H}   {H|  ถ ‍‍‍‍จ ‍‍‍ก  อ ‍‍‍ด ‍‍ต  |H}
  {8| sft#🠜 C-[-]  A-[🠜]  C-T  A-[🠞]  vol-✜ |8}   {H|  ญ ‍‍ธ ‍‍‍ท  ย ช‍‍‍‍‍‍‍‍‍‍‍‍‍ซ  |H}   {H|  ใ ‍‍‍ไ ‍‍‍‍‍‍‍‍‍‍‍‍ิ ‍‍‍‍‍‍ี ‍‍‍‍‍‍‍‍‍‍‍ึ ‍‍‍‍‍ื  |H}   {H|  ศ ‍ษ ‍‍ส  ห ‍บ ป  |H}
  {8| ctl#🠜 alt#🠜  gui#🠜  C-W  delete  menu |8}   {H|  ฒ ฆ ฑ ‍‍‍‍‍‍‍‍‍‍ฬ พ‍‍‍‍‍‍‍‍‍‍‍ฟ  |H}   {H|  ‍‍‍‍ๅ ‍‍‍‍‍‍‍ฺ  ํ  ำ  ุ ‍‍‍‍‍‍‍‍‍‍ู  |H}   {H|  ฯ ‍‍ๆ ‍‍‍‍ฐ  ฉ ‍‍‍ผ ‍ฝ  |H}
```
