![Cheat sheet of gunp layout for Planck keyboards](https://drive.google.com/uc?export=view&id=1INtnZhzoHpPkZ2kueP1K0Dpr6T1spr4m)

# gunp layout for Planck keyboards

* Layout Maintainer: [Gun Pinyo](https://github.com/gunpinyo)

This is my personal layout for Planck keyboards. Almost all of important
information is already in the picture of the cheat sheet above. There is also a
text-version of this cheat sheet at the end of this readme file. If both of them
are not the same, then please trust the text-version more because the picture is
just a screenshot of the text.

The base layer is `LY-0000`. Next, we custom keycodes called `FuncA`, `FuncB`,
`FuncC`, and `FuncD` (`FuncX` for short) which will switch to layout `LY-ABCD`
depending on the binary state of each `FuncX` where the corresponded binary
digit is a boolean "keycode `FuncX` is currently being pressed". This mechanism
allows us to access up to 16 different layers, however, only some of them have
been used. A layer matches regex `LY-....` is currently used if and only if the
cheat sheet mentions it.

Once each of these non-based layers activates (by a combination of `FuncX`
keycodes):
  - the left-half (rows 0-3, columns 0-5) will switch according to its
    individual keymap on cheat sheet,
  - the right-half (rows 0-3, columns 6-11) will switch to the `RIGHT-HALF`
    keymap such that keycodes that matches the regex `(L....|Thai[ABC])` are
    disabled and (partially) being replaced by `FuncX` keycodes on the same
    position of the base layer and keycodes in binary numbers there are
    disabled.

Another keycode in the base layer is `Stick`. When it is press, the rules of
keyboard change into persistent mode. Here, the right-half is exactly the
`RIGHT-HALF` keymap in the cheat sheet. Keycodes in left-half are all no-op
initially and can be changed to other layers by tapping on the corresponded
keycodes `(L....|Thai[ABC])`. To switch back to the normal rules governed by
`FuncX` press a `Relax` keycode.

Remark:
  - Layers `LY-Thai[ABC]` are only accessible via persistent mode.
  - This layout doesn't employ any transparent keycode, therefore, empty
    keycodes (including dummy keycodes `XXX`) are all no-op.
  - Prefixes `S-`, `C-`, `A-`, and `G-` are combinators for `sft-🠜`, `ctl-🠜`,
    `alt-🠜`, and `gui-🠜`, respectively.
  - All keycodes that starts with a capital letter are custom keycodes. Except
    single letters which stand for their alphabet.
  - There is a conflict with dynamic macro (QMK's feature) with my layer
    switching mechanisms, so I disable it but keep its keycodes there for later
    implementation.

```
  {H| "LY-0000": base-layer -- "`[🠝]` here becomes `FuncD` in other layers" |H}   {H| "RIGHT-HALF":  "when `Stick` is on" |H}
  {8| pgup|  Q  |  W  |  F  |  P  |  G  |  J  |  L  |  U  |  Y  |  K  | tab |8}   {8| L0110| [🠜] |bkspc| [🠞] | XXX | XXX  |8}
  {8| pgdn|  A  |  R  |  S  |  T  |  D  |  H  |  N  |  E  |  I  |  O  |Stick|8}   {8| L1111|ThaiA|ThaiB|ThaiC| XXX | XXX  |8}
  {8|sft-🠜|  Z  |  X  |  C  |  V  |  B  |  M  |FuncA|FuncB|FuncC| [🠝] |sft-🠞|8}   {8| L0100|L1000|L1010|L0010|Relax|sft-🠞 |8}
  {8|ctl-🠜|alt-🠜|gui-🠜| esc |bkspc|enter|FuncD|space|print| [🠜] | [🠟] | [🠞] |8}   {8| Relax|space|enter|gui-🠞|alt-🠞|ctl-🠞 |8}

  {H| "LY-0100": "col0 as no-op" |H}   {H|  "LY-1101" -- "Email: gunpinyo@gmail.com"  |H}   {x|  "LY-0110" -- "gunpinyo"  |x}
  {8| C-G  home  [🠝]  end  C-[🠝] |8}   {8| Sandbox XXX AudTog KeyLock RgbTog QmkReset |8}   {✜| S-f7 S-f8  f7 f8 f9  S-f9 |✜}
  {8| pgup  [🠜]  [🠟]  [🠞]  C-[🠟] |8}   {8| wake  caplock MyName Email RgbMod QmkDebug |8}   {✜| S-f4 S-f5  f4 f5 f6  S-f6 |✜}
  {8| pgdn  C-S  C-A  C-Z  SC-Z  |8}   {8| sleep numlock DmRec1 DmPlay1 XXX QmkEepRst |8}   {✜| S-f1 S-f2  f1 f2 f3  S-f3 |✜}
  {8|     C-[🠜]  C-F  C-[🠞]      |8}   {8| power scrlock DmRec2 DmPlay2 DmStop insert |8}   {✜|S-f10 S-f11 f10f11f12 S-f12|✜}

  {8|    "LY-1000"    |8}   {8|    "LY-1010"    |8}   {8|    "LY-0010"    |8}   {H| "LY-1111" - "powered by QMK firmware" |H}
  {H|  %  ?  !  `     |H}   {H|  #  7  8  9     |H}   {H|  &  |  ~  ^     |H}   {8| msAC1 msAC0  scr-🠜 mov-🠝 scr-🠞  scr-🠝 |8}
  {H|  @  ,  .  '  =  |H}   {H|  *  4  5  6  +  |H}   {H|  {  [  (  <  /  |H}   {8| msAC2  XXX   mov-🠜 mov-🠟 mov-🠞  scr-🠟 |8}
  {H|  $  ;  : \"  _  |H}   {H|  0  1  2  3  -  |H}   {H|  }  ]  )  >  \  |H}   {8| mPrev btn-🠝  mRWD  mPlay mFFD   btn-✜ |8}
                                                                                {8| mNext btn-🠟  pause mStop btn-🠜  btn-🠞 |8}
  1. evdev pc105 (US: qwerty, TH: kedmanee)    5. "LY-1110" is `G-`+"LY-0110"
  2. `G-space` is used to switch XKB layout    6. "LY-1100" is `S-`+"LY-0100" except [C-S, C-A, C-Z, SC-Z, C-F] which become
  3. when `Stick` is off, layer switchers other than `FuncX` are disabled       [C-X, C-C, C-V,  C-L, C-R] respectively
  4. ["LY-1000", "LY-1010", "LY-0010"] omit col0 and row3, but they have all `mod-🠜` from the base-layer, the rest are no-op

  {H| "LY-0001" -- "`mod#🠜` is oneshot-mod" |H}   {8|    "LY-ThaiA"   |8}   {8|    "LY-ThaiB"   |8}   {8|    "LY-ThaiC"   |8}
  {8|  C-H C-0  SC-pgup bri-🠝 SC-pgdn vol-🠝 |8}   {H|  ฌ ‍‍‍ฅ ‍ค  ม ฤ ฦ  |H}   {H|  ์ ‍‍‍‍‍็  ่  ้  ๊  ๋  |H}   {H|  ภ ‍‍ฃ ‍ข  ฮ ‍‍‍ฎ ‍‍ฏ  |H}
  {8| SC-T C-[+] C-pgup bri-🠟  C-pgdn vol-🠟 |8}   {H|  ณ ‍ว ‍‍‍‍‍ง  ‍น ‍‍ร ‍ล  |H}   {H|  โ ‍แ ‍‍‍‍‍‍‍‍‍‍‍เ ‍‍‍‍‍‍‍‍‍‍‍‍‍า ‍‍‍‍‍‍‍‍‍‍‍‍‍ั ‍‍‍‍‍‍‍‍ะ  |H}   {H|  ถ ‍‍‍‍จ ‍‍‍ก  อ ‍‍‍ด ‍‍ต  |H}
  {8| sft#🠜 C-[-]  A-[🠜]  C-T  A-[🠞]  vol-✜ |8}   {H|  ญ ‍‍ธ ‍‍‍ท  ย ช‍‍‍‍‍‍‍‍‍‍‍‍‍ซ  |H}   {H|  ใ ‍‍‍ไ ‍‍‍‍‍‍‍‍‍‍‍‍ิ ‍‍‍‍‍‍ี ‍‍‍‍‍‍‍‍‍‍‍ึ ‍‍‍‍‍ื  |H}   {H|  ศ ‍ษ ‍‍ส  ห ‍บ ป  |H}
  {8| ctl#🠜 alt#🠜  gui#🠜  C-W  delete  menu |8}   {H|  ฒ ฆ ฑ ‍‍‍‍‍‍‍‍‍‍ฬ พ‍‍‍‍‍‍‍‍‍‍‍ฟ  |H}   {H|  ‍‍‍‍ๅ ‍‍‍‍‍‍‍ฺ  ํ  ำ  ุ ‍‍‍‍‍‍‍‍‍‍ู  |H}   {H|  ฯ ‍‍ๆ ‍‍‍‍ฐ  ฉ ‍‍‍ผ ‍ฝ  |H}
```
