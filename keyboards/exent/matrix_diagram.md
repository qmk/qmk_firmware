# Matrix Diagram for Exent

```
                                                    ┌───────┐
                                       2u Backspace │0D     │
                                                    └───────┘
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
│00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0A │0B │0C │0D │6D │53 │
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤      ┌─────┐
│10   │11 │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │1D   │52 │      │     │
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤   ┌──┴┐2C  │ ISO Enter
│20    │21 │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C      │51 │   │1D │    │
├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤   └───┴────┘
│30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3C    │3D │50 │
├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
│40  │41  │42  │45                      │47 │48 │49 │4A │4B │4C │
└────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
┌────────┐
│30      │ 2.25u LShift
└────────┘
               ┌──────────┬────┬────────┐
               │44        │45  │46      │ Split Spacebar (Right Offset)
               └──────────┴────┴────────┘
               ┌────────┬────┬──────────┐
               │44      │45  │46        │ Split Spacebar (Left Offset)
               └────────┴────┴──────────┘
┌─────┬─────┬───────────────────────────┬─────┬─────┬───┬───┬───┐
│40   │41   │45                         │47   │48   │4A │4B │4C │ WKL
└─────┴─────┴───────────────────────────┴─────┴─────┴───┴───┴───┘
```