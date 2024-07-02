## Dactyl Generator

- Presets
    - Manuform: Original
- Keys:
    - Thumb Key Cluster: 6 (Default)
    - Number of Columns: 5
    - Number of Rows: 4
    - Last Row Key Count: Two (Default Dactyl Manuform)
    - Inner Index Finger's Column: Normal
    
## LAYOUT_legacy

Pre-2023 revamp, the 4x5 variant used a corne/crkbd wiring sequence. As wiring and pin definitions have been uniformed across variants and for backward compatibility purposes, a "legacy" layout with the corne/crkbd style wiring is available.

Compile example:

    qmk compile -kb handwired/dactyl_manuform/4x5 -km default -e FORCE_LAYOUT=LAYOUT_legacy

Flash example:

    qmk flash -kb handwired/dactyl_manuform/4x5 -km default -e FORCE_LAYOUT=LAYOUT_legacy
