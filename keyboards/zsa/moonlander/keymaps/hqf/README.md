# Moonlander AZERTY Keymap for Developers

A feature-rich AZERTY keymap for the ZSA Moonlander keyboard, optimized for
development work across different operating systems, with special
optimizations for Linux.

## Layout Overview

```
Base Layer (L0)
┌───────┬───────┬───────┬───────┬───────┬───────┬───────┐   ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┐
│  Esc  │   1   │   2   │   3   │   4   │   5   │  L5   │   │ PScr  │   6   │   7   │   8   │   9   │   0   │ Bksp  │
├───────┼───────┼───────┼───────┼───────┼───────┼───────┤   ├───────┼───────┼───────┼───────┼───────┼───────┼───────┤
│  Tab  │   A   │   Z   │   E   │   R   │   T   │  Del  │   │ Bksp  │   Y   │   U   │   I   │   O   │   P   │   ^   │
├───────┼───────┼───────┼───────┼───────┼───────┼───────┤   ├───────┼───────┼───────┼───────┼───────┼───────┼───────┤
│ Bksp  │   Q   │   S   │   D   │   F   │   G   │  Del  │   │ RShft │   H   │   J   │   K   │   L   │   M   │ Enter │
├───────┼───────┼───────┼───────┼───────┼───────┴───────┘   └───────┴───────┼───────┼───────┼───────┼───────┼───────┤
│ LShft │   W   │   X   │   C   │   V   │   B   │                   │   N   │   ,   │   ;   │   :   │   !   │ RShft │
└───────┴───────┴───────┴───────┴───────┘                                   └───────┴───────┴───────┴───────┴───────┘
```

## Features

### Multi-Layer System
- **L0**: Base AZERTY layout optimized for typing
- **L1**: Development symbols & navigation shortcuts
- **L2**: Numpad & French accented characters
- **L3**: Enhanced copy/paste & OS-specific shortcuts
- **L4**: RGB controls & lighting customization
- **L5**: Sound effects & audio feedback
- **L6**: Gaming optimizations & Rapid Fire mode

### Advanced Features

#### Tap Dance Layer Switching
- Single tap: Toggle RGB control layer (L4)
- Double tap: Toggle Gaming mode (L6)
- Triple tap: Special sound effect

#### Gaming Optimizations
- Rapid Fire support for mouse buttons and spacebar
- Configurable repeat rates
- Quick access to gaming-specific macros

#### Audio Feedback System
- Distinct sounds for layer changes
- Action confirmations
- Customizable sound effects (40 built-in options)

#### Development Tools
- HTML tag completion
- Special character shortcuts
- Git-friendly configuration system

## Installation

1. Clone QMK Firmware:
```bash
git clone https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
```

2. Create your keymap:
```bash
cp -r keyboards/zsa/moonlander/keymaps/hqf keyboards/zsa/moonlander/keymaps/[your_name]
```

3. Customize config.local.h:
```c
#define SIGNATURE_1 "Your Name - Role"
#define SIGNATURE_2 "Your Name - Role\nhttps://your-website.com"
#define EMAIL_1 "your@email.com"
#define EMAIL_2 "your@work-email.com"
```

4. Build and flash:
```bash
qmk compile -kb zsa/moonlander -km [your_name]
qmk flash -kb zsa/moonlander -km [your_name]
```

## Customization

### Local Configuration
Create `config.local.h` for personal settings (git-ignored):
- Email signatures
- Professional templates
- Custom shortcuts
- Sound preferences

### RGB Customization
- 9 built-in animation modes
- Adjustable brightness and speed
- Per-layer color schemes

### Audio Configuration
- 40 built-in sound effects
- Layer change sounds
- Action confirmation tones
- Custom melody support

## Compatibility

Tested on:
- Linux (Primary support)
- Windows 10/11
- macOS

## Contributing

1. Fork the repository
2. Create your feature branch
3. Test thoroughly
4. Submit a pull request

## Support

- [QMK Documentation](https://docs.qmk.fm/)
- [ZSA Moonlander Documentation](https://www.zsa.io/moonlander/)
- [Issue Tracker](https://github.com/qmk/qmk_firmware/issues)

## License

This project is licensed under the GPL-2.0 License - see [QMK's licensing](https://qmk.fm/license/) for details.
