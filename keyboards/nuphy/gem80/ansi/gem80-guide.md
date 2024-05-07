# Gem80 Mappings Guide

## Connectivity

The physical switch on the board should be on _wireless_ mode position.

`Fn + 1` - Bluetooth 1<br />
`Fn + 2` - Bluetooth 2<br />
`Fn + 3` - Bluetooth 3<br />
`Fn + 4` - RF (2.4 GHz mode)

## Battery

`Fn + \` - toggle permanent battery display on/off (top left light)

**Battery percentage boundaries:**

- 0-20 <span style="color: red">red</span>
- 20-40 <span style="color: orange">orange</span>
- 40-60 <span style="color: #bda50d">yellow</span>
- 60-80 <span style="color: blue">blue-purpleish</span>
- 80-100 <span style="color: green">green</span>

## Sleep Mode

When a mode is toggled on/off, the top left light blinks three times accordingly:

<span style="color: green">Green</span> = on <br/>
<span style="color: red">Red</span> = off

`Fn + P` - toggle USB sleep on/off<br/>
`Fn + ]` - toggle sleep on/off (when off, USB sleep is also off)

Sleep timeout value can be displayed on the board itself. The values are represented as `Esc - F9` for 10s digits and `1-0` for single digits, where Esc is treated as 0. Default value is 5 minutes.

Examples:

- `Esc` and `5` is 5 minutes (or 05 to be more precise)
- `F1` and `2` is 12 minutes
- `F3` and `0` is 30 minutes

`Fn + S` - toggle display on/off for sleep timeout value. The keys, representing the value, will light up in <span style="color: cyan">cyan blue color</span>.<br/>
`Fn + A` - decrease timeout by 1 minute<br/>
`Fn + D` - increase timeout by 1 minute

## Debounce Value

You can control the debounce value of the keypresses. This will help remove/decrease double inputs. Since this is something that depends on many factors like - switches, keycaps, personal typing style etc. there is no single value that is good for all people. Adjust to your liking. You can control debounce _press_ and _release_ values.

Debounce values can be displayed on the board itself. The values are represented as `Esc - F9` for 10s digits and 1-0 for single digits, where Esc is treated as 0.

Default values for both press and release are 5ms.

Examples for value:

- `Esc` and `5` is 5ms (or 05 to be more precise)
- `F1` and `2` is 12ms
- `F3` and `0` is 30ms

### Press Debounce

`Fn + Home` - toggle display on/off for press debounce value. The keys, representing the value, will light up in <span style="color: green">green color</span>.<br/>
`Fn + Ins` - decrease debounce by 1ms<br/>
`Fn + Page Up` - increase debounce by 1ms

### Release Debounce

`Fn + End` - toggle display on/off for release debounce value. The keys, representing the value, will light up in <span style="color: red">red color</span>.<br/>
`Fn + Del` - decrease debounce by 1ms<br/>
`Fn + Page Down` - increase debounce by 1ms

## RGB Effects

### Board Effects

`Fn + Up` - increase brightness<br/>
`Fn + Down` - decrease brightness<br/>
`Fn + Left` - change RGB effect<br/>
`Fn + Right` - change color for current effect<br/>

`Fn + ,`(the `<` key) - decrease effect speed<br/>
`Fn + .`(the `>` key) - increase effect speed

### Top Light Effects

`Fn + M + Up` - increase brightness<br/>
`Fn + M + Down` - decrease brightness<br/>
`Fn + M + Left` - change RGB effect<br/>
`Fn + M + Right` - change color for current effect<br/>

`Fn + M + ,`(the `<` key) - decrease effect speed<br/>
`Fn + M + .`(the `>` key) - increase effect speed

### Gem Nameplate Effects

`Fn + N + Up` - increase brightness<br/>
`Fn + N + Down` - decrease brightness<br/>
`Fn + N + Left` - change RGB effect<br/>
`Fn + N + Right` - change color for current effect<br/>

`Fn + N + ,`(the `<` key) - decrease effect speed<br/>
`Fn + N + .`(the `>` key) - increase effect speed<br/>

## Miscellaneous

`Fn + [` - hold for 3 seconds for factory reset

`Fn + Caps` - cycle between caps lock indication modes. The variants are:

- top light only - lights in blue when caps lock is on
- caps key only - lights in blue when caps lock is on
- caps key and top light are blue when caps lock is on
- off (no indication for caps lock)

The default mode is **top light only**.
