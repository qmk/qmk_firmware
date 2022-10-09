# Overview

This layout uses a mirror variant of Balance 12, created by Sasha Viminitz. See [this page](https://mathematicalmulticore.wordpress.com/the-keyboard-layout-project/) 
for more information.

## To build

```
make niu_mini:yttyx
```

## To flash (example)

```
sudo dfu-programmer atmega32u4 erase
sudo dfu-programmer atmega32u4 flash niu_mini_yttyx.hex --debug 6
sudo dfu-programmer atmega32u4 launch
```

## Layers

### Balance 12 base (BA) layer
![Base layer](https://i.imgur.com/I0TkIHT.png)

### Numeric/Punctuation (NP) layer
![Numeric/Punctuation layer](https://i.imgur.com/GgZ0PCq.png)

### Function/Cursor (FC) layer
![Function/Cursor layer](https://i.imgur.com/zcVID2d.png)

### Plover (PL) layer
![Plover layer](https://i.imgur.com/RikOGXe.png)
