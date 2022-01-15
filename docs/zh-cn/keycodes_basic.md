# 基础键码

基础键码表基于[HID 键盘/小型键盘使用手册 (0x07)](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf)，但不包括 `KC_NO`，`KC_TRNS` 以及 `0xA5-DF` 范围的键码。详细情况如下：

## 字母和数字

| 键     | 描述        |
| ------ | ----------- |
| `KC_A` | `a` 和 `A` |
| `KC_B` | `b` 和 `B` |
| `KC_C` | `c` 和 `C` |
| `KC_D` | `d` 和 `D` |
| `KC_E` | `e` 和 `E` |
| `KC_F` | `f` 和 `F` |
| `KC_G` | `g` 和 `G` |
| `KC_H` | `h` 和 `H` |
| `KC_I` | `i` 和 `I` |
| `KC_J` | `j` 和 `J` |
| `KC_K` | `k` 和 `K` |
| `KC_L` | `l` 和 `L` |
| `KC_M` | `m` 和 `M` |
| `KC_N` | `n` 和 `N` |
| `KC_O` | `o` 和 `O` |
| `KC_P` | `p` 和 `P` |
| `KC_Q` | `q` 和 `Q` |
| `KC_R` | `r` 和 `R` |
| `KC_S` | `s` 和 `S` |
| `KC_T` | `t` 和 `T` |
| `KC_U` | `u` 和 `U` |
| `KC_V` | `v` 和 `V` |
| `KC_W` | `w` 和 `W` |
| `KC_X` | `x` 和 `X` |
| `KC_Y` | `y` 和 `Y` |
| `KC_Z` | `z` 和 `Z` |
| `KC_1` | `1` 和 `!` |
| `KC_2` | `2` 和 `@` |
| `KC_3` | `3` 和 `#` |
| `KC_4` | `4` 和 `$` |
| `KC_5` | `5` 和 `%` |
| `KC_6` | `6` 和 `^` |
| `KC_7` | `7` 和 `&` |
| `KC_8` | `8` 和 `*` |
| `KC_9` | `9` 和 `(` |
| `KC_0` | `0` 和 `)` |

## 功能键

| 键       | 描述 |
| -------- | ---- |
| `KC_F1`  | F1   |
| `KC_F2`  | F2   |
| `KC_F3`  | F3   |
| `KC_F4`  | F4   |
| `KC_F5`  | F5   |
| `KC_F6`  | F6   |
| `KC_F7`  | F7   |
| `KC_F8`  | F8   |
| `KC_F9`  | F9   |
| `KC_F10` | F10  |
| `KC_F11` | F11  |
| `KC_F12` | F12  |
| `KC_F13` | F13  |
| `KC_F14` | F14  |
| `KC_F15` | F15  |
| `KC_F16` | F16  |
| `KC_F17` | F17  |
| `KC_F18` | F18  |
| `KC_F19` | F19  |
| `KC_F20` | F20  |
| `KC_F21` | F21  |
| `KC_F22` | F22  |
| `KC_F23` | F23  |
| `KC_F24` | F24  |

## 符号键

|键                 |别名  | 描述                      |
|--------------------|---------|-------------------------|
|`KC_ENTER`          |`KC_ENT` | 回车键（Return 、Enter）    |
|`KC_ESCAPE`         |`KC_ESC` | 退出键（Escape）             |
|`KC_BACKSPACE`      |`KC_BSPC`| 删除键或退格键（Delete 、Backspace） |
|`KC_TAB`            |         | 制表键（Tab）               |
|`KC_SPACE`          |`KC_SPC` | 空格键                |
|`KC_MINUS`          |`KC_MINS`| `-` 和 `_`               |
|`KC_EQUAL`          |`KC_EQL` | `=` 和 `+`               |
|`KC_LEFT_BRACKET`   |`KC_LBRC`| `[` 和 `{`               |
|`KC_RIGHT_BRACKET`  |`KC_RBRC`| `]` 和 `}`               |
|`KC_BACKSLASH`      |`KC_BSLS`| `\` 和 `\|`              |
|`KC_NONUS_HASH`     |`KC_NUHS`| 非美国键盘（Non-US） `#` 和 `~` |
|`KC_SEMICOLON`      |`KC_SCLN`| `;` 和 `:`               |
|`KC_QUOTE`          |`KC_QUOT`| `'` 和 `"`               |
|`KC_GRAVE`          |`KC_GRV` | <code>&#96;</code> 和 `~` |
|`KC_COMMA`          |`KC_COMM`| `,` 和 `<`               |
|`KC_DOT`            |         | `.` 和 `>`               |
|`KC_SLASH`          |`KC_SLSH`| `/` 和 `?`               |
|`KC_NONUS_BACKSLASH`|`KC_NUBS`| 非美国键盘（Non-US） `\` 和 `\|` |

## 锁定键

| 键                       | 别名                 | 描述                                               |
| ------------------------ | -------------------- | -------------------------------------------------- |
| `KC_CAPS_LOCK`           | `KC_CAPS`            | 大写锁定键（Caps Lock）                            |
| `KC_SCROLL_LOCK`         | `KC_SCRL`, `KC_BRMD` | 滚动锁定键（Scroll Lock, Brightness Down (macOS)） |
| `KC_NUM_LOCK`            | `KC_NUM`             | 数字锁定键（Keypad Num Lock and Clear）            |
| `KC_LOCKING_CAPS_LOCK`   | `KC_LCAP`            | 锁定 Caps Lock                                     |
| `KC_LOCKING_NUM_LOCK`    | `KC_LNUM`            | 锁定 Num Lock                                      |
| `KC_LOCKING_SCROLL_LOCK` | `KC_LSCR`            | 锁定 Scroll Lock                                   |

## 修饰键

| 键               | 别名                            | 描述                              |
| ---------------- | ------------------------------- | --------------------------------- |
| `KC_LEFT_CTRL`   | `KC_LCTL`                       | 左 Control                        |
| `KC_LEFT_SHIFT`  | `KC_LSFT`                       | 左 Shift                          |
| `KC_LEFT_ALT`    | `KC_LALT`, `KC_LOPT`            | 左 Alt (Option)                   |
| `KC_LEFT_GUI`    | `KC_LGUI`, `KC_LCMD`, `KC_LWIN` | 左 GUI (Windows/Command/Meta key) |
| `KC_RIGHT_CTRL`  | `KC_RCTL`                       | 右 Control                        |
| `KC_RIGHT_SHIFT` | `KC_RSFT`                       | 右 Shift                          |
| `KC_RIGHT_ALT`   | `KC_RALT`, `KC_ROPT`, `KC_ALGR` | 右 Alt (Option/AltGr)             |
| `KC_RIGHT_GUI`   | `KC_RGUI`, `KC_RCMD`, `KC_RWIN` | 右 GUI (Windows/Command/Meta key) |

## 国际化

|键                 |别名  |描述          |
|--------------------|---------|---------------------|
|`KC_INTERNATIONAL_1`|`KC_INT1`|日标 `\` 和 `_`      |
|`KC_INTERNATIONAL_2`|`KC_INT2`|日标 片假名/平假名|
|`KC_INTERNATIONAL_3`|`KC_INT3`|日标 `¥` 和 `\|`     |
|`KC_INTERNATIONAL_4`|`KC_INT4`|日标 変換 (Henkan)           |
|`KC_INTERNATIONAL_5`|`KC_INT5`|日标 無変換 (Muhenkan)         |
|`KC_INTERNATIONAL_6`|`KC_INT6`|日标 数字键盘 `,`       |
|`KC_INTERNATIONAL_7`|`KC_INT7`|国际 7      |
|`KC_INTERNATIONAL_8`|`KC_INT8`|国际 8      |
|`KC_INTERNATIONAL_9`|`KC_INT9`|国际 9      |
|`KC_LANGUAGE_1`     |`KC_LNG1`|韩语/英语       |
|`KC_LANGUAGE_2`     |`KC_LNG2`|韩语汉字                |
|`KC_LANGUAGE_3`     |`KC_LNG3`|日标 片假名         |
|`KC_LANGUAGE_4`     |`KC_LNG4`|日标 平假名         |
|`KC_LANGUAGE_5`     |`KC_LNG5`|日标 全角日文/半角日文  |
|`KC_LANGUAGE_6`     |`KC_LNG6`|语言 6           |
|`KC_LANGUAGE_7`     |`KC_LNG7`|语言 7           |
|`KC_LANGUAGE_8`     |`KC_LNG8`|语言 8           |
|`KC_LANGUAGE_9`     |`KC_LNG9`|语言 9           |

## 指令键

| 键                   | 别名                           | 描述                                      |
| -------------------- | ------------------------------ | ----------------------------------------- |
| `KC_PRINT_SCREEN`    | `KC_PSCR`                      | Print Screen键                            |
| `KC_PAUSE`           | `KC_PAUS`, `KC_BRK`, `KC_BRMU` | Pause键或Break键（Brightness Up (macOS)） |
| `KC_INSERT`          | `KC_INS`                       | Insert键                                  |
| `KC_HOME`            |                                | Home键                                    |
| `KC_PAGE_UP`         | `KC_PGUP`                      | Page Up键                                 |
| `KC_DELETE`          | `KC_DEL`                       | Delete键                                  |
| `KC_END`             |                                | End键                                     |
| `KC_PAGE_DOWN`       | `KC_PGDN`                      | Page Down键                               |
| `KC_RIGHT`           | `KC_RGHT`                      | 右方向键                                  |
| `KC_LEFT`            |                                | 左方向键                                  |
| `KC_DOWN`            |                                | 下方向键                                  |
| `KC_UP`              |                                | 上方向键                                  |
| `KC_APPLICATION`     | `KC_APP`                       | Application键 (Windows 中对应 Menu 键)    |
| `KC_KB_POWER`        |                                | 系统电源键                                |
| `KC_EXECUTE`         | `KC_EXEC`                      | Execute键                                 |
| `KC_HELP`            |                                | Help键                                    |
| `KC_MENU`            |                                | Menu键                                    |
| `KC_SELECT`          | `KC_SLCT`                      | Select键                                  |
| `KC_STOP`            |                                | Stop键                                    |
| `KC_AGAIN`           | `KC_AGIN`                      | Again键                                   |
| `KC_UNDO`            |                                | 撤销键                                    |
| `KC_CUT`             |                                | 剪切键                                    |
| `KC_COPY`            |                                | 复制键                                    |
| `KC_PASTE`           | `KC_PSTE`                      | 粘贴键                                    |
| `KC_FIND`            |                                | Find键                                    |
| `KC_KB_MUTE`         |                                | Mute键                                    |
| `KC_KB_VOLUME_UP`    |                                | 音量+                                     |
| `KC_KB_VOLUME_DOWN`  |                                | 音量-                                     |
| `KC_ALTERNATE_ERASE` | `KC_ERAS`                      | Alternate Erase键                         |
| `KC_SYSTEM_REQUEST`  | `KC_SYRQ`                      | SysReq/Attention键                        |
| `KC_CANCEL`          | `KC_CNCL`                      | Cancel键                                  |
| `KC_CLEAR`           | `KC_CLR`                       | Clear键                                   |
| `KC_PRIOR`           | `KC_PRIR`                      | Prior键                                   |
| `KC_RETURN`          | `KC_RETN`                      | Return键                                  |
| `KC_SEPARATOR`       | `KC_SEPR`                      | Separator键                               |
| `KC_OUT`             |                                | Out键                                     |
| `KC_OPER`            |                                | Oper键                                    |
| `KC_CLEAR_AGAIN`     | `KC_CLAG`                      | Clear/Again键                             |
| `KC_CRSEL`           | `KC_CRSL`                      | CrSel/Props键                             |
| `KC_EXSEL`           | `KC_EXSL`                      | ExSel键                                   |

## 媒体键

这些键码不在**键盘/小型键盘使用手册**的*使用（Usage）*章节中。`SYSTEM_` 前缀的键码在*通用台式机（Generic Desktop）*章节，其余部分在*用户（Consumer）*章节。

?> 部分键码在不同的系统中可能存在不同表现。例如，在macOS中， `KC_MEDIA_FAST_FORWARD`, `KC_MEDIA_REWIND`, `KC_MEDIA_NEXT_TRACK` 和 `KC_MEDIA_PREV_TRACK` 当你按住时在当前音轨中移动，但点击时会跳过整首歌。

| 键                      | 别名      | 描述            |
| ----------------------- | --------- | --------------- |
| `KC_SYSTEM_POWER`       | `KC_PWR`  | 电源键（Power） |
| `KC_SYSTEM_SLEEP`       | `KC_SLEP` | 睡眠键（Sleep） |
| `KC_SYSTEM_WAKE`        | `KC_WAKE` | 唤醒键（wake）  |
| `KC_AUDIO_MUTE`         | `KC_MUTE` | 静音            |
| `KC_AUDIO_VOL_UP`       | `KC_VOLU` | 音量+           |
| `KC_AUDIO_VOL_DOWN`     | `KC_VOLD` | 音量-           |
| `KC_MEDIA_NEXT_TRACK`   | `KC_MNXT` | 下一首          |
| `KC_MEDIA_PREV_TRACK`   | `KC_MPRV` | 上一首          |
| `KC_MEDIA_STOP`         | `KC_MSTP` | 停止            |
| `KC_MEDIA_PLAY_PAUSE`   | `KC_MPLY` | 启动/暂停       |
| `KC_MEDIA_SELECT`       | `KC_MSEL` | 启动媒体播放器  |
| `KC_MEDIA_EJECT`        | `KC_EJCT` | 弹出            |
| `KC_MAIL`               |           | 启动邮件        |
| `KC_CALCULATOR`         | `KC_CALC` | 启动计算器      |
| `KC_MY_COMPUTER`        | `KC_MYCM` | 启动我的电脑    |
| `KC_WWW_SEARCH`         | `KC_WSCH` | 浏览器查找      |
| `KC_WWW_HOME`           | `KC_WHOM` | 浏览器首页      |
| `KC_WWW_BACK`           | `KC_WBAK` | 浏览器回退      |
| `KC_WWW_FORWARD`        | `KC_WFWD` | 浏览器前进      |
| `KC_WWW_STOP`           | `KC_WSTP` | 浏览器停止      |
| `KC_WWW_REFRESH`        | `KC_WREF` | 浏览器刷新      |
| `KC_WWW_FAVORITES`      | `KC_WFAV` | 浏览器收藏夹    |
| `KC_MEDIA_FAST_FORWARD` | `KC_MFFD` | 下一首（快进）  |
| `KC_MEDIA_REWIND`       | `KC_MRWD` | 上一首（快退）  |
| `KC_BRIGHTNESS_UP`      | `KC_BRIU` | 亮度+           |
| `KC_BRIGHTNESS_DOWN`    | `KC_BRID` | 亮度-           |

## 数字键

| 键                  | 别名      | 描述                             |
| ------------------- | --------- | -------------------------------- |
| `KC_KP_SLASH`       | `KC_PSLS` | 数字键盘 `/`                     |
| `KC_KP_ASTERISK`    | `KC_PAST` | 数字键盘 `*`                     |
| `KC_KP_MINUS`       | `KC_PMNS` | 数字键盘 `-`                     |
| `KC_KP_PLUS`        | `KC_PPLS` | 数字键盘 `+`                     |
| `KC_KP_ENTER`       | `KC_PENT` | 数字键盘 Enter键                 |
| `KC_KP_1`           | `KC_P1`   | 数字键盘 `1` 和 End键            |
| `KC_KP_2`           | `KC_P2`   | 数字键盘 `2` 和 方向键下         |
| `KC_KP_3`           | `KC_P3`   | 数字键盘 `3` 和 向下翻页         |
| `KC_KP_4`           | `KC_P4`   | 数字键盘 `4` 和 方向键左         |
| `KC_KP_5`           | `KC_P5`   | 数字键盘 `5`                     |
| `KC_KP_6`           | `KC_P6`   | 数字键盘 `6` 和 方向键右         |
| `KC_KP_7`           | `KC_P7`   | 数字键盘 `7` 和 Home键           |
| `KC_KP_8`           | `KC_P8`   | 数字键盘 `8` 和 方向键上         |
| `KC_KP_9`           | `KC_P9`   | 数字键盘 `9` 和 向上翻页         |
| `KC_KP_0`           | `KC_P0`   | 数字键盘 `0` 和 Insert键         |
| `KC_KP_DOT`         | `KC_PDOT` | 数字键盘 `.` 和 Delete键         |
| `KC_KP_EQUAL`       | `KC_PEQL` | 数字键盘 `=`                     |
| `KC_KP_COMMA`       | `KC_PCMM` | 数字键盘 `,`                     |
| `KC_KP_EQUAL_AS400` |           | 数字键盘 `=` （AS/400 键盘使用） |

## 特殊键

除此之外，在 `0xA5-DF` 范围的键码用于内部实现。

| 键               | 别名                 | 描述                         |
| ---------------- | -------------------- | ---------------------------- |
| `KC_NO`          | `XXXXXXX`            | 忽略此键 (NOOP)              |
| `KC_TRANSPARENT` | `KC_TRNS`, `_______` | 使用当前层以下第一个非穿透键 |
