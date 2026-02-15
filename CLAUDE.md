# QMK Firmware Project Notes

## Build Environment

Before running any `qmk` commands, source the virtual environment:

```bash
source .venv/bin/activate
```

Then you can build firmware with:
```bash
qmk compile -kb cheapino -km default
```

## Documentation

When researching QMK features, check **docs.qmk.fm** first before searching source code:

- https://docs.qmk.fm/#/tap_hold - tap-hold configuration
- https://docs.qmk.fm/#/feature_caps_word - caps word
- https://docs.qmk.fm/#/keycodes - keycodes reference

Use source code for verifying defaults, implementation details, or when docs are unclear.

## GitHub Actions

The repo is a fork at `dansteeves68/qmk_firmware` on branch `dansteeves/cheapinov2`.

Useful commands:

```bash
gh workflow list -R dansteeves68/qmk_firmware
gh run list -R dansteeves68/qmk_firmware -w "Build Cheapino Firmware" --limit 1
gh run view <run-id> -R dansteeves68/qmk_firmware --log-failed
gh run watch -R dansteeves68/qmk_firmware
```
