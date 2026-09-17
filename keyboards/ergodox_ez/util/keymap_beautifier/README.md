# keymap_beautifier.py

## About
This Python 3 script, by [Tsan-Kuang Lee](https://github.com/tsankuanglee) takes the keymap.c downloaded from [ErgoDox EZ Configurator](https://configure.ergodox-ez.com/) and beautifies it for easier customization, allowing one to quickly draft a layout to build upon.

## Features
For example, the original `keymap.c` looks like

```
[0] = LAYOUT_ergodox(KC_EQUAL,KC_1,KC_2,KC_3,KC_4,KC_5,LCTL(KC_MINUS),KC_DELETE,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_LBRC,KC_BSPC,KC_A,KC_S,KC_D,KC_F,KC_G,SC_LSPO,CTL_T(KC_Z),KC_X,KC_C,KC_V,KC_B,HYPR_T(KC_NO),LT(1,KC_GRAVE),KC_QUOTE,LALT(KC_LSFT),KC_LEFT,KC_RIGHT,ALT_T(KC_APPLICATION),KC_LGUI,KC_HOME,KC_SPACE,KC_UNDS,KC_END,LCTL(KC_EQUAL),KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINUS,KC_RBRC,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSLS,KC_H,ALT_T(KC_J),KC_K,KC_L,LT(2,KC_SCLN),GUI_T(KC_QUOTE),MEH_T(KC_NO),KC_N,KC_M,KC_COMMA,KC_DOT,CTL_T(KC_SLASH),SC_RSPC,KC_UP,KC_DOWN,KC_LBRC,KC_RBRC,TT(1),KC_LALT,CTL_T(KC_ESCAPE),KC_PGUP,KC_PGDN,LT(1,KC_TAB),KC_ENTER),
```

The beautifier parses it and outputs:

```
[0] = LAYOUT_ergodox(
// left hand

KC_EQUAL      , KC_1       , KC_2           , KC_3   , KC_4    , KC_5, LCTL(KC_MINUS),
KC_DELETE     , KC_Q       , KC_W           , KC_E   , KC_R    , KC_T, KC_LBRC   ,
KC_BSPC       , KC_A       , KC_S           , KC_D   , KC_F    , KC_G,
SC_LSPO       , CTL_T(KC_Z), KC_X           , KC_C   , KC_V    , KC_B, HYPR_T(KC_NO)  ,
LT(1,KC_GRAVE), KC_QUOTE   , LALT(KC_LSFT)  , KC_LEFT, KC_RIGHT,

// left thumb

          ALT_T(KC_APPLICATION), KC_LGUI,
                                 KC_HOME,
KC_SPACE, KC_UNDS              , KC_END ,

// right hand

LCTL(KC_EQUAL), KC_6, KC_7       , KC_8    , KC_9       , KC_0           , KC_MINUS       ,
KC_RBRC       , KC_Y, KC_U       , KC_I    , KC_O       , KC_P           , KC_BSLS        ,
                KC_H, ALT_T(KC_J), KC_K    , KC_L       , LT(2,KC_SCLN)  , GUI_T(KC_QUOTE),
MEH_T(KC_NO)  , KC_N, KC_M       , KC_COMMA, KC_DOT     , CTL_T(KC_SLASH), SC_RSPC        ,
                      KC_UP      , KC_DOWN , KC_LBRC,     KC_RBRC        , TT(1)          ,

// right thumb

KC_LALT  , CTL_T(KC_ESCAPE),
KC_PGUP  ,
KC_PGDN, LT(1,KC_TAB)    , KC_ENTER
)
```

Optionally, it can also render [LAYOUT_ergodox_pretty](https://github.com/qmk/qmk_firmware/blob/ee700b2e831067bdb7584425569b61bc6329247b/keyboards/ergodox_ez/keymaps/bpruitt-goddard/keymap.c#L49-L57):
```
[0] = LAYOUT_ergodox_pretty(
  KC_ESCAPE,        KC_1,     KC_2,    KC_3,     KC_4,           KC_5,          QK_LEAD,      QK_LEAD, KC_6          , KC_7            , KC_8            , KC_9               , KC_0              , KC_BSPC             ,
     KC_TAB,        KC_Q,     KC_W,    KC_E,     KC_R,           KC_T,          KC_HYPR,      KC_HYPR, KC_Y          , KC_U            , KC_I            , KC_O               , KC_P              , KC_BSLS             ,
   KC_LCTL,         KC_A,     KC_S,    KC_D,     KC_F,           KC_G,                                 KC_H          , KC_J            , KC_K            , KC_L               , KC_SCLN           , KC_QUOTE            ,
  KC_LSFT,          KC_Z,     KC_X,    KC_C,     KC_V,           KC_B,           SH_MON,      SH_MON , KC_N          , KC_M            , KC_COMMA        , KC_DOT             , KC_SLASH          , KC_RSFT             ,
LT(6,KC_NO), LT(7,KC_NO), KC_LCTL,  KC_LGUI,  KC_LALT,                                                                 ALGR_T(KC_MINUS), RGUI_T(KC_EQUAL), RCTL_T(KC_LBRC),     LT(10,KC_RBRC),     LT(6,KC_APPLICATION),

                                                       LT(6,KC_GRAVE),     MEH_T(KC_NO),      KC_LEFT, KC_RIGHT      ,
                                                                       LT(10,KC_DELETE),      KC_UP  ,
                                             KC_SPACE, LT(8,KC_ENTER),  LT(7,KC_BSPC),        KC_DOWN, LT(7,KC_SPACE), LT(8,KC_ENTER)
)
```

We can also align everythng t othe left (easier editing in my opinon):
```
[0] = LAYOUT_ergodox_pretty(
KC_ESCAPE  , KC_1       , KC_2    , KC_3   , KC_4    , KC_5          , QK_LEAD         ,      QK_LEAD, KC_6          , KC_7            , KC_8            , KC_9               , KC_0              , KC_BSPC             ,
KC_TAB     , KC_Q       , KC_W    , KC_E   , KC_R    , KC_T          , KC_HYPR         ,      KC_HYPR, KC_Y          , KC_U            , KC_I            , KC_O               , KC_P              , KC_BSLS             ,
KC_LCTL    , KC_A       , KC_S    , KC_D   , KC_F    , KC_G          ,                                 KC_H          , KC_J            , KC_K            , KC_L               , KC_SCLN           , KC_QUOTE            ,
KC_LSFT    , KC_Z       , KC_X    , KC_C   , KC_V    , KC_B          , SH_MON          ,      SH_MON , KC_N          , KC_M            , KC_COMMA        , KC_DOT             , KC_SLASH          , KC_RSFT             ,
LT(6,KC_NO), LT(7,KC_NO), KC_LCTL , KC_LGUI, KC_LALT ,                                                                 ALGR_T(KC_MINUS), RGUI_T(KC_EQUAL), RCTL_T(KC_LBRC),     LT(10,KC_RBRC),     LT(6,KC_APPLICATION),

                                                       LT(6,KC_GRAVE), MEH_T(KC_NO)    ,      KC_LEFT, KC_RIGHT      ,
                                                                       LT(10,KC_DELETE),      KC_UP  ,
                                             KC_SPACE, LT(8,KC_ENTER), LT(7,KC_BSPC)   ,      KC_DOWN, LT(7,KC_SPACE), LT(8,KC_ENTER)
)
```

## Usage

### With docker
This is the cleaner way. `Docker` is the only requirement. The program executes within a container that has all dependencies installed.

First build the images. (Run once)
```
cd QMK_GIT_REPO_dir/keyboards/ergodox_ez/util/keymap_beautifier
docker build -t keymapbeautifier:1.0 .
```
Run it
```
cd QMK_GIT_REPO_dir/keyboards/ergodox_ez/util/keymap_beautifier
cp PATH_TO_YOUR_C_SOURCE_FILE.c input.c
./docker_run.sh input.c -p -c -o output.c
```
The prettified file is written to `output.c`. See the section Tweaks for non-default settings.

### Without docker
Requirements:
* python3 (tested on 3.7.4)
* python module `pycparser` installed (with `pip install pycparser`)

To run:
```
cd QMK_GIT_REPO_dir/keyboards/ergodox_ez/util/keymap_beautifier
cp PATH_TO_YOUR_C_SOURCE_FILE.c input.c
./KeymapBeautifier.py input.c -p -c -o output.c
```
The prettified file is written to `output.c`. See the section Tweaks for non-default settings.

## Tweaks
```
usage: KeymapBeautifier.py [-h] [-o OUTPUT_FILENAME] [-p] [-c] input_filename

Beautify keymap.c downloaded from ErgoDox-Ez Configurator for easier
customization.

positional arguments:
  input_filename        input file: c source code file that has the layer
                        keymaps

optional arguments:
  -h, --help            show this help message and exit
  -o OUTPUT_FILENAME, --output-filename OUTPUT_FILENAME
                        output file: beautified c filename. If not given,
                        output to STDOUT.
  -p, --pretty-output-layout
                        use LAYOUT_ergodox_pretty for output instead of
                        LAYOUT_ergodox
  -c, --justify-toward-center
                        for LAYOUT_ergodox_pretty, align right for the left
                        half, and align left for the right half. Default is
                        align left for both halves.
```
For example,
```
./docker_run.sh input.c -p -c -o output.c
# or if you don't want to use docker:
#./KeymapBeautifier.py input.c -p -c -o output.c
```
will read `input.c`, and produce `output.c` with LAYOUT_ergodox_pretty, and have the key symbols gravitating toward the center.

