# Finnish/Swedish iso Keymap for XIUDI's XD60 PCB

FI/SV iso Keymap for XD60.

## Keymap

### Base Layer

![Base layer](https://i.imgur.com/TrChS0N.png)

```json
["Esc","!\n1","\"\n2","#\n3","¤\n4","%\n5","&\n6","/\n7","(\n8",")\n9","=\n0","?\n+","`\n´","Fn",{w:1},"Back space"],
[{w:1.5},"Tab","Q","W","E","R","T","Y","U","I","O","P","Å","^\n¨",{x:0.25,w:1.25,h:2,w2:1.5,h2:1,x2:-0.25},"Enter"],
[{w:1.75},"Caps Lock","A","S","D","F","G","H","J","K","L","Ö","Ä","*\n'"],
[{w:1.25},"Shift","<\n>","Z","X","C","V","B","N","M",";\n,",":\n.",{w:1.75},"Shift","Up","_\n-"],
[{w:1.5},"Ctrl",{w:1},"Win",{w:1.25},"Alt",{a:7,w:6.25},"",{a:4,w:1},"AltGr",{w:1},"Ctrl",{w:1},"Left",{w:1},"Down","Right"]
```

### Function Layer

![Default Keymap layer 2](https://img.alicdn.com/imgextra/i1/1713761720/TB2K0gTalPxQeBjy1XcXXXHzVXa_!!1713761720.png)

## Build

To build the default keymap, simply run:

    make xiudi/xd60/rev2:finnish  # XD60 rev2
    make xiudi/xd60/rev3:finnish  # XD60 rev3
