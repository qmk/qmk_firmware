# Matrix Diagram for Kibou Harbour

According to the GB runner, the PCB supports ISO layout, but the
supplied plate does not.[^1][^2]

Product renders and GB runner comments both show support for split
Backspace,[^3] but no switch matrix data is currently available.

\- @noroadsleft, 23 June, 2023

```
                                                    ┌───────┐
                                       2u Backspace │??     │
                                                    └───────┘
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
│00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0A │0B │0C │0D │0E │0F │
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤      ┌─────┐
│10   │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │1D │1E   │1F │      │     │
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤   ┌──┴┐??  │ ISO Enter
│20    │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C │2E      │2F │   │?? │    │
├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤   └───┴────┘
│30  │?? │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3D    │3E │3F │
├────┴┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬─┬───┼───┼───┤
│40   │42 │43   │47                         │4B   │ │4D │4E │4F │
└─────┴───┴─────┴───────────────────────────┴─────┘ └───┴───┴───┘
┌────────┐
│30      │ 2.25u LShift
└────────┘
┌─────┬──┬─────┬───────────────────────────┬─────┐
│40   │  │43   │47                         │4B   │ Blocker WKL
└─────┘  └─────┴───────────────────────────┴─────┘
```

[^1]: [Geekhack Interest Check, Original Post](https://geekhack.org/index.php?topic=111146.msg3012509#msg3012509)
[^2]: [Reddit Interest Check](https://www.reddit.com/r/MechanicalKeyboards/comments/lgyv5p/ic_harbour_%E6%B8%AF%E5%8F%A3_a_65_gasket_mounted_board_designed/gmudnjb/)
[^3]: [Geekhack Interest Check, reply #102](https://geekhack.org/index.php?topic=111146.msg3022822#msg3022822)
