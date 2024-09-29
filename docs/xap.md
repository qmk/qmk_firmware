# XAP

XAP (“extensible application protocol”) API intends to provide access to various QMK subsystems.

## Overview

```mermaid
%%{init: {'themeVariables': { 'fontSize': '24px'}}}%%
flowchart LR
    dev[QMK Device] <-- XAP --> host[Host Computer]
```

The intention is to provide access to QMK subsystems through a versioned and documented protocol. 

## Protocol Reference

[protocol_versions](xap_protocol.md ':include')

## Clients

TODO

## CLI

The QMK CLI provides a few XAP specific commands for diagnosis purposes.

### List Connected Devices
Simple
```
$ qmk xap --list
Ψ Available devices:
Ψ   7844:8450 KPrepublic XD84 Pro [API:0.2.0] LOCKED
```

Verbose
```
$ qmk --verbose xap --list
Ψ Available devices:
Ψ   7844:8450 KPrepublic XD84 Pro [API:0.2.0] LOCKED
    _id: 553831323538150A2113000000000000
    backlight.pin: F5
    bootloader: atmel-dfu
    community_layouts: 75_ansi, 75_iso
    debounce: 5
    diode_direction: COL2ROW
    features.audio: False
    features.backlight: True
    features.bootmagic: True
    features.command: False
    features.console: False
    features.extrakey: True
    features.mousekey: False
    features.nkro: True
    features.rgblight: True
    indicators.caps_lock: B2
    keyboard_folder: xiudi/xd84pro
    keyboard_name: XD84 Pro
    layouts: LAYOUT_75_ansi, LAYOUT_75_iso, LAYOUT_all
    maintainer: qmk
    manufacturer: KPrepublic
    matrix_pins.cols: B1, B3, B4, B5, B6, B7, C6, C7, D4, D6, D7, E6, F0, F1, F7
    matrix_pins.rows: D0, D1, D2, D3, D5, F4
    matrix_pins.unused: B0, E2
    matrix_size.cols: 15
    matrix_size.rows: 6
    mouse_key.enabled: False
    platform: unknown
    processor: atmega32u4
    processor_type: avr
    protocol: LUFA
    rgblight.animations.all: False
    rgblight.led_count: 12
    rgblight.pin: F6
    rgblight.sleep: False
    url: 
    usb.device_ver: 0x0001
    usb.device_version: 0.0.1
    usb.pid: 0x8450
    usb.vid: 0x7844
```

### Interactive shell
```
$ qmk xap -i
Ψ Connected to:7844:8450 KPrepublic XD84 Pro
Welcome to the XAP shell.  Type help or ? to list commands.

Ψ> help

Documented commands (type help <topic>):
========================================
EOF  about  exit  help  keycode  keymap  layer  listen  unlock

Ψ>
```
