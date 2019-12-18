# Planck Layout

My planck layouts.
Check out [user readme](../../../../users/bbaserdem/README.md) for more info.

Builds fine as of 2019-12-17 (all variants)

# Build

On archlinux, the package *arm-none-eabi-gcc* is too recent to compile ChibiOS.
To fix this; add to the environment `CFLAGS="-Wno-error=deprecated"`.

Get keyboard into reset mode, and then;

```
make planck/rev4:bbaserdem:flash
CFLAGS="-Wno-error=deprecated" make planck/rev6:bbaserdem:flash
make planck/light:bbaserdem:flash
```
