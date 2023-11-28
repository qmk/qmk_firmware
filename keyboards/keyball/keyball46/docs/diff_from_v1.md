# Differences from V1

* `KEYBALL_SCROLL_DIVIDER` - deleted

  V2 is able to change scroll divider dynamically by keycodes:

  * `SCRL_DVI` - increment scroll divider (maximum 7)
  * `SCRL_DVD` - decrement scroll divider (mininum 1)

  The effect of scroll divider is changed.
  It is applied as `1 / (2 ^ (n-1))`.
  Therefore, its divider will be like this table:

  Value | Divider
  -----:|-------:
  1     | 1 / 1
  2     | 1 / 2
  3     | 1 / 4
  4     | 1 / 8
  5     | 1 / 16
  6     | 1 / 32
  7     | 1 / 64

  Default is 4, it can be changed by defining `KEYBALL_SCROLL_DIV_DEFAULT` in your config.h

* `KEYBALL_POINTER_DIVIDER` - deleted

  V2 controls resolution (CPI) of optical sensor PMW3360DM directly.
  The minimum is 100, and the maximum is 12000, with 100 step.

  CPI can be changed by keycodes:

  * `CPI_I1K`  - increase 1000 CPI 
  * `CPI_I100` - increase 100 CPI
  * `CPI_D100` - decrease 100 CPI
  * `CPI_D1K`  - decrease 1000 CPI

  Default is 500, it can be changed by defiing `KEYBALL_CPI_DEFAULT` in your
  config.h

* `void keyball_process_trackball_default()` API - deleted

* `void keyball_process_trackball_user()` overridable function - deleted

* `TRACKBALL_MAX_NUMBER` constant - deleted

* `TRACKBALL_SAMPLE_COUNT` - deleted

  V2 controls resolution (CPI) of optical sensor PMW3360DM directly.
