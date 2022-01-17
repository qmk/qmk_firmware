# Firmware Code Generator for QMK

Since QMK currently doesn't support changing key layout etc via EPPROM, we need to flash the firmware everytime the layout changes. The firmware obviously is a binaries that needs to be compiled from source - and if we need to update the firmware we need to update the source. This is the code generator that is responsble for generating the necessary configuration in plain c.

## Getting Started

Run
```
gen/gen-config.sh gen-original
```
at `keyboards/chonkerkeys` to generate `config.c`. 

### Args

`gen-original` to generate the default firmware for original, `gen-max` for max, and `gen` for custom configuration. `gen` requires two more additional args: `FIRMWARE_VERSION` and `FIRMWARE_CONFIG`, specified via env var.

### Specifying output path

```
export FIRMWARE_CONFIG_OUTPUT=original/keymaps/default/config.c
gen/gen-config.sh gen-original
```

## JSON schema of FIRMWARE_CONFIG

**NOTE**: Do NOT use QMK's online configuration's schema as chonkerkeys has custom data.

### Schema of config

```
{
    "layers":<array of layer_type (in layer_type.h)>,
	"sizeOrdinals": <nested array of the size + ordinal (specified below) of each key, in each row, in each layer>,
	"keymaps": <nested array of the custom_keycodes (in keyconfig.h) of each key, in each row, in each layer>
}
```

#### Example

```
// default config of original
{
		"layers":["CH_ZOOM_WINDOWS", "CH_ZOOM_MACOS"],
		"sizeOrdinals": [
			[
				[1, 129, 0, 0],
				[65, 67, 0, 1]
			],
			[
				[1, 129, 0, 0],
				[65, 67, 0, 1]
			]
		],
		"keymaps": [
   			[
        		["CH_ZOOM_RAISE_HAND_TOGGLE", "CH_ZOOM_LEAVE_MEETING", "KC_NO", "KC_NO"],
        		["CH_ZOOM_MUTE_TOGGLE", "CH_ZOOM_VIDEO_TOGGLE", "KC_NO", "CH_ZOOM_SHARE_SCREEN_START_STOP_TOGGLE"]
    		],
    		[
        		["CH_ZOOM_RAISE_HAND_TOGGLE", "CH_ZOOM_LEAVE_MEETING", "KC_NO", "KC_NO"],
        		["CH_ZOOM_MUTE_TOGGLE", "CH_ZOOM_VIDEO_TOGGLE", "KC_NO", "CH_ZOOM_SHARE_SCREEN_START_STOP_TOGGLE"]
    		]
		]
}
```

### Size and Ordinal of Key

```
enum Size {
    Key1U = 0,
    Key1_5U,    // 1.5U
    Key3U
}

enum Ordinal {
    Empty = 0,   // a.k.a KC_NO
    Left,
    Top,
    Right,
    Bottom
}

uint8_t sizeOrdinal(Size size, Ordinal ordinal) {
    return (size << 6) & ordinal;
}
```

#### Example

- 1U + left slot: 0 & 1 = 1
- 1.5U + left slot: (1 << 6) & 1 = 64 & 1 = 65
- 1.5U + right slot: (1 << 6) & 3 = 64 & 3 = 67
- 3U + left slot: (2 << 6) & 1 = 128 & 1 = 129
