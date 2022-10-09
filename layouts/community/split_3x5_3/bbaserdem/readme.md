This folder contains my [split\_3x5\_3](../../../default/split_3x5_3) board layouts
Check out the [user readme](../../../../users/bbaserdem/readme.md) for more info.

# Crkbd

Using a no 6th column crkbd (rev 2.1 choc) as a mobile keyboard.

This version uses ProMicro as controllers; can't have OLED and RGB at the same time.

## Build

QMK cli commands no longer works with Archlinux (2021 Sep.) on my PC for flashing promicro.
In the past; I used to flash Pro Micro explicitly using the following line, for referance.

```
sudo avrdude -p atmgea34u4 -P "$(ls /dev/ttyACM*)" -c avr109 -D -U flash:w:<hexfile>.hex
```

