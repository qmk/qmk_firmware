# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

QMK (Quantum Mechanical Keyboard) Firmware is a powerful keyboard firmware that runs on many mechanical keyboards. It supports features like programmable layers, RGB lighting, rotary encoders, split keyboards, and much more.

## Development Commands

### Core Build Commands
- `make <keyboard>:<keymap>` - Compile firmware for a specific keyboard/keymap combination
- `make <keyboard>:<keymap>:flash` - Compile and flash firmware to the keyboard
- `make all:all` - Build all keyboards and keymaps (from project root)
- `make clean` - Clean build artifacts
- `make distclean` - Clean all build outputs including .hex/.bin files

### QMK CLI Commands
The project uses the `qmk` CLI tool extensively:
- `qmk compile -kb <keyboard> -km <keymap>` - Compile using QMK CLI
- `qmk flash -kb <keyboard> -km <keymap>` - Flash firmware using QMK CLI
- `qmk list-keyboards` - List all available keyboards
- `qmk list-keymaps -kb <keyboard>` - List available keymaps for a keyboard
- `qmk doctor` - Check QMK environment setup
- `qmk lint` - Check keyboard/keymap for common mistakes
- `qmk clean` - Clean build files

### Testing Commands
- `make test:all` - Run all tests
- `make test:<test_name>` - Run specific test
- `qmk pytest` - Run Python tests

### Development Utilities
- `qmk format-c` - Format C code
- `qmk format-python` - Format Python code
- `make format-core` - Format core C and Python code using Docker
- `make pytest` - Run pytest in Docker container

## Code Architecture

### High-Level Structure
- **quantum/** - Core QMK functionality and features
  - Main keyboard logic in `keyboard.c`
  - Key processing pipeline in `process_keycode/`
  - Feature implementations (RGB, audio, etc.)
- **keyboards/** - Individual keyboard definitions
  - Each keyboard has its own folder with `keyboard.json` or legacy files
  - Contains keyboard-specific code and keymap directories
- **platforms/** - Hardware platform abstraction layer
- **drivers/** - Hardware driver implementations
- **tmk_core/** - Low-level keyboard functionality inherited from TMK
- **builddefs/** - Build system makefiles
- **users/** - User-specific code that can be shared across keyboards

### Key Components
- **Matrix Scanning**: Detects key presses/releases (`matrix.c`, `matrix_common.c`)
- **Key Processing Pipeline**: Transforms matrix events into actions
  - `process_keycode/` contains modular key processing features
  - Features are processed in a specific order (tap dance, combos, etc.)
- **Action System**: Converts processed keys into keyboard actions
- **Features**: Modular functionality (RGB, audio, split keyboards, etc.)

### Keyboard Definition
- Modern keyboards use `keyboard.json` for configuration
- Legacy keyboards may use `config.h`, `rules.mk`, and `.h/.c` files
- Keymaps are defined in `keymaps/<name>/keymap.c` or `keymap.json`

### Build System
- Uses GNU Make with complex makefile system in `builddefs/`
- Supports multiple target platforms (AVR, ARM, etc.)
- QMK CLI provides higher-level interface to build system

## Common Development Patterns

### Adding a New Keyboard
1. Use `qmk new-keyboard` to generate base files
2. Define matrix configuration and pin assignments
3. Create default keymap
4. Test compilation and functionality

### Creating Custom Keymaps
1. Use `qmk new-keymap -kb <keyboard>` to create new keymap
2. Modify `keymap.c` or use `keymap.json` format
3. Enable features in `rules.mk` if needed
4. Test with `qmk compile` and `qmk flash`

### Working with Features
- Features are typically enabled in `rules.mk` with `FEATURE_ENABLE = yes`
- Feature configuration is done in `config.h`
- Feature-specific code goes in appropriate `process_keycode/` files

## Important Files to Know
- `keyboards/<keyboard>/keyboard.json` - Modern keyboard configuration
- `keyboards/<keyboard>/keymaps/<keymap>/keymap.c` - Keymap definition
- `keyboards/<keyboard>/keymaps/<keymap>/rules.mk` - Keymap build rules
- `quantum/quantum.h` - Main QMK header file
- `quantum/quantum_keycodes.h` - Key code definitions

## Development Constraints
- The only keyboard that matters is sofle_choc and the only keymap that matters is mhamrah
- All other keyboards and keymaps can be ignored
- When making edits or changes, only modify files in the:
  - `keyboards/sofle_choc` directory 
  - `keyboards/sofle_choc/keymaps/mhamrah` directory

## Personal Development Environment

### Primary Languages
- TypeScript
- Rust
- Go

### Development Tools
- Slack (primary communication)
- Outlook (email)
- Raycast (app and tab switching)
- Contexts (tab switching)
- Homerow (mouse alternative)

### Keyboard Layout Principles
- Never change the a-z character layout on the primary layer
- Other layers can be freely modified

## Hardware Specifications
- The display on the keyboard is 128x32 OLED
- There are two OLEDs, one on each side (master and slave)