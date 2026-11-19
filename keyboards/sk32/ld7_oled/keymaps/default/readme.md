# Default keymap (LD7_OLED)

A 7-key macropad (one GPIO per key) with a 7-LED WS2812 strip and a 128x32
SSD1306 OLED that shows the key-press rate and input latency.

```
Layer 0 (base)
.---------------.
| Z | X | C | V |
+---+---+---+---|
| A |Ctrl|Ent |
'---------------'
```

* `Z X C V A Ctrl Enter` — the seven directly wired keys.

## OLED

The 128x32 SSD1306 (I2C1, address 0x3C) displays two live metrics:

* **KEY/s** — average number of key triggers per second over the last 10 s.
* **LAT/ms** — latency (0.1 ms resolution) from the raw press edge to the HID
  report being sent.

The display updates only when a value changes (incremental rendering, no
continuous I2C traffic while idle).

## RGB matrix

The 7-LED WS2812 strip sits above the keys and is driven by the native SK32
SLED peripheral. `RGB_MATRIX_SOLID_COLOR` is the default mode, with the
`ENABLE_RGB_MATRIX_*` effects available from the factory configuration.

## OLED auto-detection

The same firmware runs on boards with or without the OLED fitted: on first
use the keymap pings the I2C bus and, if no SSD1306 answers, every OLED I2C
transfer is short-circuited so the keyboard enumerates normally even without
the display. The I2C bus runs at 400 kHz in fast mode.
