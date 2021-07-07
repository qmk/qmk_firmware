# Egstad's Idobo

## LEDs
By default, LEDs are enabled. There is a short bootup animation (`bootupAnimation()`) to indicate that the keyboard has powered up correctly.

On each keypress, the LEDs hue increases. This increase is determined the the `RGBLIGHT_HUE_STEP` value, which is assigned in `../config.h` (parent idobo directory). My local copy has this value set to `1`, so the incremental color shift is rather slow.


## Keeping up to date
To update your fork’s master, run the following, hitting the Enter key after each line:

```bash
git checkout master
git fetch upstream
git pull upstream master
git push origin master
```
