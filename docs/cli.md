# QMK CLI {#qmk-cli}

## Overview {#overview}

The QMK CLI (command line interface) makes building and working with QMK keyboards easier. We have provided a number of commands to simplify and streamline tasks such as obtaining and compiling the QMK firmware, creating keymaps, and more.

### Installation {#installation}

The recommended way to install the QMK CLI and all necessary dependencies (toolchains, flashing utilities, udev rules on Linux) is to use the bootstrapper script:

```
curl -fsSL https://install.qmk.fm | sh
```

For more options, run:

```
curl -fsSL https://install.qmk.fm | sh -s -- --help
```

For detailed setup instructions, see [Setting Up Your QMK Environment](newbs_getting_started#set-up-your-environment).
