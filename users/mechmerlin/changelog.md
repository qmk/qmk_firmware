# Changelog
All notable changes to my userspace will be documented in this file.

## [0.2.2] - 2019-04-22
### Fixed
- `config.h` usage of turning on `RGBLIGHT_ENABLE` when it is not enabled on boards other than my two clueboards were causing issues with boards that didn't have RGB underglow on it. 

## [0.2.1] - 2019-03-01
### Fixed
- `config.h` usage of `#ifdef RGBLIGHT_ENABLE` caused problems for other of my boards that had `RGBLIGHT_ENABLE`.  

## [0.2.0] - 2019-02-27
### Changed
- Moved `AUDIO_CLICKY` from community layout `66_ansi` into user space. 

## [0.1.1] - 2018-10-26
### Added
- Added a changelog, aka THIS VERY FILE! 
- Added `config.h` to userspace for `RGBLIGHT_SLEEP` feature. 

### Changed
- Spruced up the readme file to better explain the things I use in my keymap for would be keymap snoopers. Also useful as an example when people ask. 
- Use `CTL_T` instead of `MT` for my custom `KC_CTCP` keycode as it was causing issues on some boards. 

## [0.1.0] - 2018-08-31
Initial usage of userspaces!
