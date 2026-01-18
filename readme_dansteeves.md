# QMK Firmware Build Plan for Cheapino v2

## Overview

Build custom QMK firmware for a Cheapino v2 split keyboard using uv for Python environment
management and tompi's QMK fork.

## Prerequisites

- GitHub CLI (`gh`) authenticated
- `uv` installed
- USB-C cable for flashing

---

## Phase 1: Repository Setup

### 1.1 Fork and Clone QMK Firmware

```bash
cd /Users/dan/code/

# Fork the official qmk_firmware repo to your GitHub account
gh repo fork qmk/qmk_firmware --clone

# This creates /Users/dan/code/qmk_firmware
cd qmk_firmware
```

### 1.2 Add Cheapino Remote and Checkout v2 Branch

```bash
# Add tompi's fork as a remote
git remote add tompi https://github.com/tompi/qmk_firmware

# Fetch the Cheapino v2 branch
git fetch tompi cheapinov2
```

### 1.3 Create Your Working Branch

```bash
# Create a new branch based on tompi's cheapinov2 (so you can commit/push)
git checkout -b dansteeves/cheapinov2 tompi/cheapinov2

# Push to your fork to set up tracking
git push -u origin dansteeves/cheapinov2
```

---

## Phase 2: Python Environment with uv

### 2.1 Initialize uv Project

```bash
cd /Users/dan/code/qmk_firmware

# Initialize a new uv project (in parent of qmk_firmware)
uv init --name dansteeves-cheapino

# Add qmk as a dependency
uv add --dev qmk

# Activate the virtual environment
source .venv/bin/activate
```

### 2.2 Configure QMK to Use Your Fork

```bash
# Set QMK home to your cloned fork
qmk config user.qmk_home=/Users/dan/code/qmk_firmware

# Run QMK setup (will use existing clone, answer 'n' to re-clone prompt)
qmk setup -H /Users/dan/code/qmk_firmware
```

---

## Phase 3: Build Firmware

### 3.1 Verify Setup

```bash
# Check QMK environment
qmk doctor

# List available keyboards (should include cheapino)
qmk list-keyboards | grep cheapino

# Get keyboard info
qmk info -kb cheapino
```

### 3.2 Build Default Firmware

```bash
# Build the default keymap
qmk compile -kb cheapino -km default
```

Output: `cheapino_default.uf2` in the qmk_firmware root

---

## Phase 4: Flash Firmware

### 4.1 Flash to Keyboard

```bash
# Compile and flash (will wait for DFU mode)
qmk flash -kb cheapino -km default
```

### 4.2 Enter DFU Mode

1. Hold the **BOOT** button on the RP2040-Zero
2. Press the **RESET** button (or plug in USB while holding BOOT)
3. A USB drive will appear
4. QMK will automatically flash the firmware

---

## Phase 5: Custom Keymap Development (Edit-Build-Test Cycle)

### 5.1 Create Custom Keymap

```bash
cd /Users/dan/code/keyboard/qmk_firmware

# Copy default keymap as starting point
cp -r keyboards/cheapino/keymaps/default keyboards/cheapino/keymaps/dan
```

### 5.2 Edit Keymap

Option A: Edit `keyboards/cheapino/keymaps/dan/keymap.c` directly

Option B: Use QMK Configurator

1. Upload `keymap.json` to https://config.qmk.fm/
2. Configure layers (up to 15)
3. Download and replace `keymap.json`

### 5.3 Build-Test-Iterate Loop

```bash
# Build custom keymap
qmk compile -kb cheapino -km dan

# Flash when ready
qmk flash -kb cheapino -km dan
```

### 5.4 Encoder Customization

For rotary encoder, edit: `qmk_firmware/keyboards/cheapino/encoder.c`

---

## Directory Structure After Setup

```
/Users/dan/code/keyboard/
├── pyproject.toml                 # uv project config
├── .venv/                         # Virtual environment
├── .python-version
└── qmk_firmware/                  # QMK firmware (forked, on cheapinov2 branch)
    └── keyboards/cheapino/
        ├── keymaps/
        │   ├── default/
        │   └── dan/               # Your custom keymap
        └── encoder.c              # Encoder configuration
```

---

## Verification Steps

1. `qmk doctor` passes all checks
2. `qmk compile -kb cheapino -km default` produces `.uf2` file
3. Keyboard responds after flashing
4. Custom keymap changes take effect

---

## Troubleshooting

- **QMK doctor fails**: Run `qmk setup` again
- **Keyboard not found**: Ensure on `tompi/cheapinov2` branch
- **Flash fails**: Verify DFU mode (USB drive should appear)
- **Encoder not working**: Check `encoder.c` configuration
