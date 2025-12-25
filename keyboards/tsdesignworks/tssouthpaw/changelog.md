# Changelog

All notable changes to the TS Southpaw keyboard firmware will be documented in this file.

## [2.0.0] - December 2025

### Major Changes
- **BREAKING**: Removed entire work timer system
- Streamlined firmware focused on core RGB functionality and keyboard features
- Cleaned up codebase by removing all duplicate files

### Added
- **FN+E Toggle**: Added keyboard shortcut to enable/disable ESC ripple effect
- New custom keycode `KC_ESC_TOG` for toggling ESC ripple effect
- Firmware version definition in config.h
- Comprehensive changelog documentation

### Removed
- Work timer functionality (all timer types: 30MIN, 1HR, 4HR, 8HR, 10HR)
- Work timer EEPROM persistence
- Work timer LED progress indicators on F1-F12
- Work timer wake-from-sleep notifications
- Work timer custom keycodes: `KC_WRKTMR`, `KC_WRKPAU`, `KC_30MIN`, `KC_1HR`, `KC_4HR`, `KC_8HR`, `KC_10HR`
- Duplicate files:
  - `work_timer.c` (root level)
  - `work_timer.h` (root level)
  - `rgb_effects/work_timer.c`
  - `rgb_effects/work_timer.h`
  - `rgb_effects.c` (root level - duplicate)
  - `rgb_effects.h` (root level - duplicate)
- Work timer LED range definitions from config.h
- Work timer EEPROM address definitions
- Work timer notification brightness settings
- RGB_MATRIX_MINIMUM_BRIGHTNESS setting (no longer needed)

### Changed
- Firmware version updated from 0.0.2 to 2.0.0
- ESC ripple effect now has enable/disable state (enabled by default)
- Simplified `tssouthpaw.c` - removed all work timer integration
- Updated `rules.mk` to only compile `rgb_effects/rgb_effects.c`
- Reorganized FN layer - removed work timer keys, added ESC toggle on E key
- Updated README.md with version 2.0 documentation
- Simplified config.h - removed work timer configuration
- Cleaned up power management functions (no work timer wake logic)

### Improved
- Code organization - single source of truth for RGB effects
- Build times - less code to compile
- Memory usage - removed unused work timer state tracking
- Documentation - clearer focus on available features

### Technical Details
- Device version in keyboard.json: 2.0.0
- RGB effects consolidated to `rgb_effects/` directory only
- All work timer references removed from codebase
- Cleaner include structure

### Migration Notes
If upgrading from version 1.x:
1. All work timer functionality will be removed
2. Work timer keybindings will no longer function
3. EEPROM work timer data will be ignored (but not erased)
4. FN layer layout has changed - work timer keys replaced
5. ESC ripple effect now toggleable with FN+E

---

## [1.x] - Previous Version

### Features (Historical Reference)
- Work timer system with multiple duration options
- Work timer EEPROM persistence
- Visual work timer progress on F1-F12 LEDs
- Wake-from-sleep for timer notifications
- ESC ripple effect (always on)
- RGB matrix effects
- Caps Lock, Num Lock, and Mic Mute indicators
- Arrow key highlighting
- Dynamic macros
- Caps Word functionality
