# Lulu (QMK + VIA) Custom Firmware Guide

## Overview

This guide explains how to customize a Boardsource Lulu keyboard with:

- VIA support
- Encoder resolution fix
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

## Create VIA Keymap

```bash
qmk new-keymap -kb boardsource/lulu/rp2040 -km via
```

### IMPORTANT: Move keymap to rp2040 directory

By default, QMK creates:

```
keyboards/boardsource/lulu/keymaps/via/
```

Move it to:

```
keyboards/boardsource/lulu/rp2040/keymaps/via/
```

Command:

```bash
mkdir -p keyboards/boardsource/lulu/rp2040/keymaps
mv keyboards/boardsource/lulu/keymaps/via keyboards/boardsource/lulu/rp2040/keymaps/
```

---

## Configuration

### rules.mk

```make
VIA_ENABLE = yes
ENCODER_MAP_ENABLE = yes
OLED_ENABLE = yes
```

### config.h

```c
#pragma once
#define EE_HANDS
#define ENCODER_RESOLUTION 2
```

---

## Build (Docker)

```bash
qmk compile -kb boardsource/lulu/rp2040 -km via
```

---

## Flashing

### Enter Bootloader

Hold outermost top key while plugging USB.

### Flash

- Copy `.uf2` to `RPI-RP2`
- Flash both halves

---

## EE_HANDS Setup

### Build

```bash
qmk compile -kb boardsource/lulu/rp2040 -km via -bl uf2-split-left
qmk compile -kb boardsource/lulu/rp2040 -km via -bl uf2-split-right
```

### Flash

- Left → copy left `.uf2`
- Right → copy right `.uf2`

---

## Verify

- VIA works
- Encoder fixed
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
