#/bin/bash
# {
#     "version": 1,
#     "keyboard": {
#         "keys": [{
#             "id": 0,
#             "legend": "Tab",
#             "state": {
#                 "x": 0,
#                 "y": 0,
#                 "r": 0,
#                 "rx": 0,
#                 "ry": 0,
#                 "w": 1,
#                 "h": 1,
#                 "x2": 0,
#                 "y2": 0,
#                 "w2": 0,
#                 "h2": 0,
#                 "a": 7
#             },
#             "row": 0,
#             "col": 0,
#             "keycodes": [{
#                 "id": "KC_TAB",
#                 "fields": []
#             }]
#         }],
#         "controller": 1,
#         "bounds": {
#             "min": {
#                 "x": 0,
#                 "y": 0
#             },
#             "max": {
#                 "x": 12,
#                 "y": 4
#             }
#         },
#         "rows": 4,
#         "cols": 12,
#         "pins": {
#             "row": ["D0", "D5", "B5", "B6"],
#             "col": ["F1", "F0", "B0", "C7", "F4", "F5", "F6", "F7", "D4", "D6", "B4", "D7"],
#             "num": null,
#             "caps": null,
#             "scroll": null,
#             "compose": null,
#             "kana": null,
#             "led": "B7",
#             "rgb": null
#         },
#         "macros": {},
#         "quantum": "void matrix_init_user(void) {\n}\n\nvoid matrix_scan_user(void) {\n}\n\nbool process_record_user(uint16_t keycode, keyrecord_t *record) {\n\treturn true;\n}",
#         "settings": {
#             "diodeDirection": 0,
#             "name": "Planck Default",
#             "bootloaderSize": 2,
#             "rgbNum": 0,
#             "backlightLevels": 3
#         }
#     }
# }
keyboard=$1
subproject=$2
keymap=$(gcc -fpreprocessed -dD -E keyboards/$keyboard/default/keymap.c)
printf '{
    "version": 1,
    "keyboard": {