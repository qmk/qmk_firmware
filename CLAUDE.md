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
