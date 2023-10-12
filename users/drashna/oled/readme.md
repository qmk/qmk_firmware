# OLED Display

To disable the pre genrated oled display, add `CUSTOM_OLED_DRIVER = no` to your `rules.mk`.

<!-- to do: add all the stuff -->
## OLED Font

My font file has multiple fonts and multiple logs integrated into the one file.  And it uses the full 255 possible characters. 

In addition to the default font and logos: 

```c
#    define OLED_FONT_5X5
#    define OLED_FONT_AZTECH
#    define OLED_FONT_BMPLAIN
#    define OLED_FONT_CRACKERS
#    define OLED_FONT_EIN
#    define OLED_FONT_HISKYF21
#    define OLED_FONT_SQUASH
#    define OLED_FONT_SUPER_DIGG
#    define OLED_FONT_ZXPIX
```

```c
#    define OLED_LOGO_CORNE
#    define OLED_LOGO_GMK_BAD
#    define OLED_LOGO_GOTHAM
#    define OLED_LOGO_HUE_MANITEE
#    define OLED_LOGO_LOOSE
#    define OLED_LOGO_SETS3N
#    define OLED_LOGO_SKEEB
```

Additionally, the font file allows for external oled font files, instead.  This allows for additional files that cannot be hosted in the QMK Repo. 

## Display

A picture is worth a thousand words.  So here are two: 

![Right](https://i.imgur.com/4XFOVKBl.jpg)

![Left](https://i.imgur.com/W5RX4pAl.jpg)
