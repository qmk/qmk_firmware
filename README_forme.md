# Lulu (QMK + VIA) Custom Firmware Guide

## Overview

This guide explains how to customize a Boardsource Lulu keyboard with:

- VIA support
- Encoder support that works with VIA
- USB connection from either half
- OLED customization
- Docker-based QMK build environment

---

## Requirements

- Git
- Docker
- GitHub account
- Boardsource Lulu (RP2040)

---

## Repository Setup

### 1. Fork QMK

https://github.com/qmk/qmk_firmware

---

### 2. Clone your fork

```bash
git clone https://github.com/YOUR_USERNAME/qmk_firmware.git
cd qmk_firmware
```

---

### 3. Initialize submodules (IMPORTANT)

```bash
git submodule sync --recursive
git submodule update --init --recursive
```

---

### 4. Add upstream

```bash
git remote add upstream https://github.com/qmk/qmk_firmware.git
```

---

### 5. Create a working branch

```bash
git checkout -b lulu-via-custom
```

---

## Docker Setup

```bash
docker pull qmkfm/qmk_cli
```

```bash
docker run --rm -it \
  -v "$(pwd):/qmk_firmware" \
  -w /qmk_firmware \
  qmkfm/qmk_cli bash
```

---

## Verify Build

```bash
qmk compile -kb boardsource/lulu/rp2040 -km default
```

---

## VIA Keymap

If the `via` keymap does not exist yet, create it with:

```bash
qmk new-keymap -kb boardsource/lulu/rp2040 -km via
```

For this keyboard, keep the shared VIA keymap under:

```
keyboards/boardsource/lulu/keymaps/via/
```

Do not move it into `rp2040/keymaps/via/`.

When building `boardsource/lulu/rp2040`, QMK can use the parent keyboard keymap at `keyboards/boardsource/lulu/keymaps/via/`.

---

## Configuration

### VIA keymap rules.mk

File:

`keyboards/boardsource/lulu/keymaps/via/rules.mk`

```make
VIA_ENABLE = yes
ENCODER_MAP_ENABLE = yes
```

This is what enables VIA and exposes rotary turn events to VIA.

### RP2040 rules.mk

File:

`keyboards/boardsource/lulu/rp2040/rules.mk`

```make
SRC += lib/oled.c
```

Keep OLED source registration here at the keyboard level.

### config.h

File:

`keyboards/boardsource/lulu/rp2040/config.h`

```c
#pragma once
#define ENCODER_RESOLUTION 2
#define EE_HANDS
#define BOOTMAGIC_ROW_RIGHT 5
#define BOOTMAGIC_COLUMN_RIGHT 0
```

Notes:

- `EE_HANDS` stores left/right handedness in EEPROM.
- `BOOTMAGIC_ROW_RIGHT` and `BOOTMAGIC_COLUMN_RIGHT` make bootmagic work when the right half is the USB side.

---

## Build (Docker)

```bash
qmk compile -kb boardsource/lulu/rp2040 -km via
```

The output UF2 is:

```bash
boardsource_lulu_rp2040_via.uf2
```

---

## Flashing

### Enter Bootloader

Hold the bootmagic key while plugging in USB.

- Left half over USB: hold the left upper outer key (`Esc`)
- Right half over USB: hold the right upper outer key (<code>`</code>)

### Flash

- Copy `.uf2` to `RPI-RP2`
- Flash both halves

---

## EE_HANDS Setup For Docker

Do not use `uf2-split-left` or `uf2-split-right` inside Docker.

Those targets run the QMK flash step, which tries to auto-deploy to the RP2040 drive from inside the container.

Instead, build the handedness directly into the UF2 and then copy the file manually.

### Initialize left half

```bash
cd /qmk_firmware
make boardsource/lulu/rp2040:via OPT_DEFS="-DINIT_EE_HANDS_LEFT"
```

Then copy:

```bash
boardsource_lulu_rp2040_via.uf2
```

to the left half while it is mounted as `RPI-RP2`.

### Initialize right half

```bash
cd /qmk_firmware
make boardsource/lulu/rp2040:via OPT_DEFS="-DINIT_EE_HANDS_RIGHT"
```

Then copy the generated `boardsource_lulu_rp2040_via.uf2` to the right half.

### After initialization

After both halves have been initialized once, use the normal build again:

```bash
qmk compile -kb boardsource/lulu/rp2040 -km via
```

You do not need `MASTER=left` or `MASTER=right` for this setup.

### Important

- If one half behaves like the other side, its EEPROM handedness is wrong. Rebuild with the matching `INIT_EE_HANDS_LEFT` or `INIT_EE_HANDS_RIGHT` define and flash that half again.
- The output filename is the same for left and right builds, so copy or rename the UF2 before building the other side if needed.

---

## Verify

- VIA works
- Encoder rotation can be assigned in VIA
- Works from both USB sides
- OLED works

---

## Update from upstream

```bash
git fetch upstream
git checkout master
git merge upstream/master
git push origin master
```

# Crkbd

```
SKIP_FLASHING_SUPPORT=1 util/docker_build.sh crkbd/rev1:via
```
