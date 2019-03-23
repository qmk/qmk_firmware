# Idle RGB Lighting Timeout

Idle RGB Lighting Timeout is a feature that allows you to turn your keyboard underglow off after a fifteen minutes. This is independent of the your PC's power settings.

## Usage
For the idle timeout to take effect, you need to set `IDLE_RGBLIGHT_ENABLE = yes` in your `rules.mk`, eg.:
```
IDLE_RGBLIGHT_ENABLE = yes
```

Now when using your keyboard, the underglow will turn off after 15 minutes. This works with all existing lighting effects.

## Configuration
You may change the timeout (in minutes) by setting `#define IDLE_RGBLIGHT_TIMEOUT 15` in your `config.h` fil, eg.:

```
#define IDLE_RGBLIGHT_TIMEOUT 15
```
