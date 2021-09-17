This file contains my [split 3x10 + 3](../../../default/split_3x10_3) board layouts
Check out the [user readme](../../../../users/bbaserdem/README.md) for more info.

# Crkbd

Using a no 6th column crkbd (rev 2.1 choc) as a mobile keyboard.

This version uses ProMicro as controllers; can't have OLED and RGB at the same time.

## Build

Used to flash Pro Micro explicitly using the following line;

```
sudo avrdude -p atmgea34u4 -P "$(ls /dev/ttyACM*)" -c avr109 -D -U flash:w:.build/<keeb>.hex
```

But it does not work anymore in Archlinux.
