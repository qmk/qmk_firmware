# Framework Laptop 16 – ANSI Keyboard Layout Data

This repository contains empirically derived keyboard layout data for the **Framework Laptop 16 (ANSI keyboard module)**.

The goal of this submission is to provide a clear, verifiable source-of-truth mapping between physical key geometry and the keyboard’s scan matrix, suitable for upstream tooling, firmware, or layout generation.

---

## Files

### `keyboard.json`

This is the **primary submission file**.

It conforms to the expected keyboard layout schema and includes:
- Physical key geometry (`x`, `y`, `w`)
- Logical matrix coordinates (`matrix: [row, col]`)
- Overall matrix dimensions

This file is intended for direct consumption by existing tooling or for generation of downstream, consumer-facing artifacts.

---

###

It contains:
- Raw electrical scan coordinates (`KSO`, `KSI`) observed during live keypress testing
- One entry per physical key
- No geometry or layout assumptions

The electrical data was captured empirically by pressing individual keys and recording their reported scan positions. It is provided to help validate the logical matrix mapping or assist reconstruction in the absence of schematics.

This data is optional for consumers, but may be useful for maintainers or firmware developers:

{
  "name": "Framework Laptop 16",
  "layout": "ANSI",
  "source": "empirical scan data",
  "notes": "KSO/KSI values observed from live keypress scan output; one key pressed at a time.",
  "electricalEvidence": [
    { "key": "Esc", "kso": 5, "ksi": 7 },
    { "key": "F1", "kso": 5, "ksi": 3 },
    { "key": "F2", "kso": 5, "ksi": 2 },
    { "key": "F3", "kso": 4, "ksi": 6 },
    { "key": "F4", "kso": 4, "ksi": 3 },
    { "key": "F5", "kso": 10, "ksi": 4 },
    { "key": "F6", "kso": 10, "ksi": 3 },
    { "key": "F7", "kso": 10, "ksi": 2 },
    { "key": "F8", "kso": 15, "ksi": 1 },
    { "key": "F9", "kso": 11, "ksi": 3 },
    { "key": "F10", "kso": 8, "ksi": 4 },
    { "key": "F11", "kso": 8, "ksi": 6 },
    { "key": "F12", "kso": 13, "ksi": 3 },
    { "key": "Del", "kso": 1, "ksi": 0 },

    { "key": "`", "kso": 2, "ksi": 4 },
    { "key": "1", "kso": 2, "ksi": 5 },
    { "key": "2", "kso": 5, "ksi": 5 },
    { "key": "3", "kso": 4, "ksi": 5 },
    { "key": "4", "kso": 6, "ksi": 5 },
    { "key": "5", "kso": 6, "ksi": 4 },
    { "key": "6", "kso": 7, "ksi": 4 },
    { "key": "7", "kso": 7, "ksi": 5 },
    { "key": "8", "kso": 10, "ksi": 5 },
    { "key": "9", "kso": 8, "ksi": 5 },
    { "key": "0", "kso": 13, "ksi": 4 },
    { "key": "-", "kso": 13, "ksi": 2 },
    { "key": "=", "kso": 14, "ksi": 4 },
    { "key": "Backspace", "kso": 14, "ksi": 5 },

    { "key": "Tab", "kso": 2, "ksi": 3 },
    { "key": "Q", "kso": 2, "ksi": 0 },
    { "key": "W", "kso": 5, "ksi": 6 },
    { "key": "E", "kso": 4, "ksi": 2 },
    { "key": "R", "kso": 6, "ksi": 6 },
    { "key": "T", "kso": 6, "ksi": 3 },
    { "key": "Y", "kso": 7, "ksi": 3 },
    { "key": "U", "kso": 7, "ksi": 6 },
    { "key": "I", "kso": 10, "ksi": 6 },
    { "key": "O", "kso": 8, "ksi": 3 },
    { "key": "P", "kso": 13, "ksi": 5 },
    { "key": "[", "kso": 13, "ksi": 6 },
    { "key": "]", "kso": 14, "ksi": 6 },
    { "key": "\\", "kso": 8, "ksi": 2 },

    { "key": "CapsLock", "kso": 4, "ksi": 4 },
    { "key": "A", "kso": 2, "ksi": 7 },
    { "key": "S", "kso": 5, "ksi": 4 },
    { "key": "D", "kso": 14, "ksi": 7 },
    { "key": "F", "kso": 6, "ksi": 7 },
    { "key": "G", "kso": 6, "ksi": 2 },
    { "key": "H", "kso": 7, "ksi": 2 },
    { "key": "J", "kso": 7, "ksi": 7 },
    { "key": "K", "kso": 10, "ksi": 7 },
    { "key": "L", "kso": 8, "ksi": 7 },
    { "key": ";", "kso": 13, "ksi": 7 },
    { "key": "'", "kso": 14, "ksi": 0 },
    { "key": "Enter", "kso": 14, "ksi": 1 },

    { "key": "LeftShift", "kso": 9, "ksi": 1 },
    { "key": "Z", "kso": 5, "ksi": 1 },
    { "key": "X", "kso": 5, "ksi": 0 },
    { "key": "C", "kso": 0, "ksi": 0 },
    { "key": "V", "kso": 6, "ksi": 0 },
    { "key": "B", "kso": 6, "ksi": 1 },
    { "key": "N", "kso": 7, "ksi": 1 },
    { "key": "M", "kso": 7, "ksi": 0 },
    { "key": ",", "kso": 10, "ksi": 0 },
    { "key": ".", "kso": 8, "ksi": 0 },
    { "key": "/", "kso": 13, "ksi": 0 },
    { "key": "RightShift", "kso": 9, "ksi": 0 },

    { "key": "Ctrl_L", "kso": 12, "ksi": 1 },
    { "key": "Fn", "kso": 2, "ksi": 2 },
    { "key": "Win", "kso": 1, "ksi": 3 },
    { "key": "Alt_L", "kso": 3, "ksi": 1 },
    { "key": "Space", "kso": 4, "ksi": 1 },
    { "key": "Alt_R", "kso": 3, "ksi": 0 },
    { "key": "Ctrl_R", "kso": 12, "ksi": 0 },

    { "key": "Up", "kso": 13, "ksi": 1 },
    { "key": "Left", "kso": 11, "ksi": 6 },
    { "key": "Down", "kso": 8, "ksi": 1 },
    { "key": "Right", "kso": 15, "ksi": 2 }
  ]
}

---

## Methodology (Summary)

- Each key was pressed individually on a Framework Laptop 16.
- Reported scan coordinates were recorded per key.
- Keys were mapped to physical positions based on measured geometry.
- Logical matrix rows/columns were derived from the observed scan behavior.

No assumptions were made about internal routing beyond what was observable from scan output.

---

## Notes

- The layout reflects the ANSI keyboard module.
- Geometry units are in standard keyboard units (`u`).
- Downstream projects are free to project or transform this data into other formats as needed.

---

## License

This data is provided for integration and validation purposes.  
Refer to the parent project or repository for applicable licensing terms.
