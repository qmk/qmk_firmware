# 键码概览

在定义新的[键映射](zh-cn/keymap.md)时须有合法的键定义，本文记录了可在 QMK 中使用的所有符号的键码。

本文仅作为资料索引，每一组按键都会链接到详细解释它们实际功能的文档页面中。

**（译注：由于部分键码需要准确详细的功能解释作为背景知识，并为了保证不存在翻译不同步的问题，本文中的部分表格不对“描述”部分进行翻译，请参阅各节的链接中的表格）**

## 基础键码 :id=basic-keycodes

参见：[基础键码](zh-cn/keycodes_basic.md)

|按键                     |别名                        |描述                            |Windows      |macOS        |Linux<sup>1</sup>|
|------------------------|-------------------------------|---------------------------------------|-------------|-------------|-----------------|
|`KC_NO`                 |`XXXXXXX`                      |忽略该键（空/NOOP）                      |*N/A*        |*N/A*        |*N/A*            |
|`KC_TRANSPARENT`        |`KC_TRNS`, `_______`           |使用该层以下的第一个非穿透键（KC_TRANSPARENT) |*N/A*        |*N/A*        |*N/A*            |
|`KC_A`                  |                               |`a` 及 `A`                            |✔            |✔            |✔                |
|`KC_B`                  |                               |`b` 及 `B`                            |✔            |✔            |✔                |
|`KC_C`                  |                               |`c` 及 `C`                            |✔            |✔            |✔                |
|`KC_D`                  |                               |`d` 及 `D`                            |✔            |✔            |✔                |
|`KC_E`                  |                               |`e` 及 `E`                            |✔            |✔            |✔                |
|`KC_F`                  |                               |`f` 及 `F`                            |✔            |✔            |✔                |
|`KC_G`                  |                               |`g` 及 `G`                            |✔            |✔            |✔                |
|`KC_H`                  |                               |`h` 及 `H`                            |✔            |✔            |✔                |
|`KC_I`                  |                               |`i` 及 `I`                            |✔            |✔            |✔                |
|`KC_J`                  |                               |`j` 及 `J`                            |✔            |✔            |✔                |
|`KC_K`                  |                               |`k` 及 `K`                            |✔            |✔            |✔                |
|`KC_L`                  |                               |`l` 及 `L`                            |✔            |✔            |✔                |
|`KC_M`                  |                               |`m` 及 `M`                            |✔            |✔            |✔                |
|`KC_N`                  |                               |`n` 及 `N`                            |✔            |✔            |✔                |
|`KC_O`                  |                               |`o` 及 `O`                            |✔            |✔            |✔                |
|`KC_P`                  |                               |`p` 及 `P`                            |✔            |✔            |✔                |
|`KC_Q`                  |                               |`q` 及 `Q`                            |✔            |✔            |✔                |
|`KC_R`                  |                               |`r` 及 `R`                            |✔            |✔            |✔                |
|`KC_S`                  |                               |`s` 及 `S`                            |✔            |✔            |✔                |
|`KC_T`                  |                               |`t` 及 `T`                            |✔            |✔            |✔                |
|`KC_U`                  |                               |`u` 及 `U`                            |✔            |✔            |✔                |
|`KC_V`                  |                               |`v` 及 `V`                            |✔            |✔            |✔                |
|`KC_W`                  |                               |`w` 及 `W`                            |✔            |✔            |✔                |
|`KC_X`                  |                               |`x` 及 `X`                            |✔            |✔            |✔                |
|`KC_Y`                  |                               |`y` 及 `Y`                            |✔            |✔            |✔                |
|`KC_Z`                  |                               |`z` 及 `Z`                            |✔            |✔            |✔                |
|`KC_1`                  |                               |`1` 及 `!`                            |✔            |✔            |✔                |
|`KC_2`                  |                               |`2` 及 `@`                            |✔            |✔            |✔                |
|`KC_3`                  |                               |`3` 及 `#`                            |✔            |✔            |✔                |
|`KC_4`                  |                               |`4` 及 `$`                            |✔            |✔            |✔                |
|`KC_5`                  |                               |`5` 及 `%`                            |✔            |✔            |✔                |
|`KC_6`                  |                               |`6` 及 `^`                            |✔            |✔            |✔                |
|`KC_7`                  |                               |`7` 及 `&`                            |✔            |✔            |✔                |
|`KC_8`                  |                               |`8` 及 `*`                            |✔            |✔            |✔                |
|`KC_9`                  |                               |`9` 及 `(`                            |✔            |✔            |✔                |
|`KC_0`                  |                               |`0` 及 `)`                            |✔            |✔            |✔                |
|`KC_ENTER`              |`KC_ENT`                       |回车（Enter）                          |✔            |✔            |✔                |
|`KC_ESCAPE`             |`KC_ESC`                       |Escape                                |✔            |✔            |✔                |
|`KC_BACKSPACE`          |`KC_BSPC`                      |删除（退格/Backspace）                  |✔            |✔            |✔                |
|`KC_TAB`                |                               |Tab                                   |✔            |✔            |✔                |
|`KC_SPACE`              |`KC_SPC`                       |空格                                  |✔            |✔            |✔                |
|`KC_MINUS`              |`KC_MINS`                      |`-` 及 `_`                            |✔            |✔            |✔                |
|`KC_EQUAL`              |`KC_EQL`                       |`=` 及 `+`                            |✔            |✔            |✔                |
|`KC_LEFT_BRACKET`       |`KC_LBRC`                      |`[` 及 `{`                            |✔            |✔            |✔                |
|`KC_RIGHT_BRACKET`      |`KC_RBRC`                      |`]` 及 `}`                            |✔            |✔            |✔                |
|`KC_BACKSLASH`          |`KC_BSLS`                      |`\` 及 `\|`                           |✔            |✔            |✔                |
|`KC_NONUS_HASH`         |`KC_NUHS`                      |非美国键盘的 `#` 及 `~`                 |✔            |✔            |✔                |
|`KC_SEMICOLON`          |`KC_SCLN`                      |`;` 及 `:`                            |✔            |✔            |✔                |
|`KC_QUOTE`              |`KC_QUOT`                      |`'` 及 `"`                            |✔            |✔            |✔                |
|`KC_GRAVE`              |`KC_GRV`                       |<code>&#96;</code> 及 `~`             |✔            |✔            |✔                |
|`KC_COMMA`              |`KC_COMM`                      |`,` 及 `<`                            |✔            |✔            |✔                |
|`KC_DOT`                |                               |`.` 及 `>`                            |✔            |✔            |✔                |
|`KC_SLASH`              |`KC_SLSH`                      |`/` 及 `?`                            |✔            |✔            |✔                |
|`KC_CAPS_LOCK`          |`KC_CAPS`                      |大写锁定（Caps Lock）                   |✔            |✔            |✔                |
|`KC_F1`                 |                               |F1                                     |✔            |✔            |✔                |
|`KC_F2`                 |                               |F2                                     |✔            |✔            |✔                |
|`KC_F3`                 |                               |F3                                     |✔            |✔            |✔                |
|`KC_F4`                 |                               |F4                                     |✔            |✔            |✔                |
|`KC_F5`                 |                               |F5                                     |✔            |✔            |✔                |
|`KC_F6`                 |                               |F6                                     |✔            |✔            |✔                |
|`KC_F7`                 |                               |F7                                     |✔            |✔            |✔                |
|`KC_F8`                 |                               |F8                                     |✔            |✔            |✔                |
|`KC_F9`                 |                               |F9                                     |✔            |✔            |✔                |
|`KC_F10`                |                               |F10                                    |✔            |✔            |✔                |
|`KC_F11`                |                               |F11                                    |✔            |✔            |✔                |
|`KC_F12`                |                               |F12                                    |✔            |✔            |✔                |
|`KC_PRINT_SCREEN`       |`KC_PSCR`                      |Print Screen                           |✔            |✔<sup>2</sup>|✔                |
|`KC_SCROLL_LOCK`        |`KC_SCRL`, `KC_BRMD`           |Scroll Lock, 降低亮度（macOS）           |✔            |✔<sup>2</sup>|✔                |
|`KC_PAUSE`              |`KC_PAUS`, `KC_BRK`, `KC_BRMU` |Pause, 提高亮度（macOS）                 |✔            |✔<sup>2</sup>|✔                |
|`KC_INSERT`             |`KC_INS`                       |Insert                                 |✔            |             |✔                |
|`KC_HOME`               |                               |Home                                   |✔            |✔            |✔                |
|`KC_PAGE_UP`            |`KC_PGUP`                      |Page Up                                |✔            |✔            |✔                |
|`KC_DELETE`             |`KC_DEL`                       |前向删除（Delete）                       |✔            |✔            |✔                |
|`KC_END`                |                               |End                                    |✔            |✔            |✔                |
|`KC_PAGE_DOWN`          |`KC_PGDN`                      |Page Down                              |✔            |✔            |✔                |
|`KC_RIGHT`              |`KC_RGHT`                      |右                                     |✔            |✔            |✔                |
|`KC_LEFT`               |                               |左                                     |✔            |✔            |✔                |
|`KC_DOWN`               |                               |下                                     |✔            |✔            |✔                |
|`KC_UP`                 |                               |上                                     |✔            |✔            |✔                |
|`KC_NUM_LOCK`           |`KC_NUM`                       |小键盘锁定                              |✔            |✔            |✔                |
|`KC_KP_SLASH`           |`KC_PSLS`                      |小键盘 `/`                             |✔            |✔            |✔                |
|`KC_KP_ASTERISK`        |`KC_PAST`                      |小键盘 `*`                             |✔            |✔            |✔                |
|`KC_KP_MINUS`           |`KC_PMNS`                      |小键盘 `-`                             |✔            |✔            |✔                |
|`KC_KP_PLUS`            |`KC_PPLS`                      |小键盘 `+`                             |✔            |✔            |✔                |
|`KC_KP_ENTER`           |`KC_PENT`                      |小键盘区回车                           |✔            |✔            |✔                |
|`KC_KP_1`               |`KC_P1`                        |小键盘 `1` 和 End                     |✔            |✔            |✔                |
|`KC_KP_2`               |`KC_P2`                        |小键盘 `2` 和 下                       |✔            |✔            |✔                |
|`KC_KP_3`               |`KC_P3`                        |小键盘 `3` 和 Page Down                |✔            |✔            |✔                |
|`KC_KP_4`               |`KC_P4`                        |小键盘 `4` 和 上                       |✔            |✔            |✔                |
|`KC_KP_5`               |`KC_P5`                        |小键盘 `5`                             |✔            |✔            |✔                |
|`KC_KP_6`               |`KC_P6`                        |小键盘 `6` 和 右                       |✔            |✔            |✔                |
|`KC_KP_7`               |`KC_P7`                        |小键盘 `7` 和 Home                     |✔            |✔            |✔                |
|`KC_KP_8`               |`KC_P8`                        |小键盘 `8` 和 上                       |✔            |✔            |✔                |
|`KC_KP_9`               |`KC_P9`                        |小键盘 `9` 和 Page Up                  |✔            |✔            |✔                |
|`KC_KP_0`               |`KC_P0`                        |小键盘 `0` 和 Insert                   |✔            |✔            |✔                |
|`KC_KP_DOT`             |`KC_PDOT`                      |小键盘 `.` 和 Delete                   |✔            |✔            |✔                |
|`KC_NONUS_BACKSLASH`    |`KC_NUBS`                      |非美国键盘的 `\` 及 `\|`                 |✔            |✔            |✔                |
|`KC_APPLICATION`        |`KC_APP`                       |应用键（Windows下的菜单键）              |✔            |             |✔                |
|`KC_KB_POWER`           |                               |电源键                                 |             |✔<sup>3</sup>|✔                |
|`KC_KP_EQUAL`           |`KC_PEQL`                      |小键盘 `=`                             |✔            |✔            |✔                |
|`KC_F13`                |                               |F13                                    |✔            |✔            |✔                |
|`KC_F14`                |                               |F14                                    |✔            |✔            |✔                |
|`KC_F15`                |                               |F15                                    |✔            |✔            |✔                |
|`KC_F16`                |                               |F16                                    |✔            |✔            |✔                |
|`KC_F17`                |                               |F17                                    |✔            |✔            |✔                |
|`KC_F18`                |                               |F18                                    |✔            |✔            |✔                |
|`KC_F19`                |                               |F19                                    |✔            |✔            |✔                |
|`KC_F20`                |                               |F20                                    |✔            |             |✔                |
|`KC_F21`                |                               |F21                                    |✔            |             |✔                |
|`KC_F22`                |                               |F22                                    |✔            |             |✔                |
|`KC_F23`                |                               |F23                                    |✔            |             |✔                |
|`KC_F24`                |                               |F24                                    |✔            |             |✔                |
|`KC_EXECUTE`            |`KC_EXEC`                      |Execute                                |             |             |✔                |
|`KC_HELP`               |                               |Help                                   |             |             |✔                |
|`KC_MENU`               |                               |Menu                                   |             |             |✔                |
|`KC_SELECT`             |`KC_SLCT`                      |Select                                 |             |             |✔                |
|`KC_STOP`               |                               |Stop                                   |             |             |✔                |
|`KC_AGAIN`              |`KC_AGIN`                      |Again                                  |             |             |✔                |
|`KC_UNDO`               |                               |Undo                                   |             |             |✔                |
|`KC_CUT`                |                               |剪切                                    |             |             |✔                |
|`KC_COPY`               |                               |复制                                   |             |             |✔                |
|`KC_PASTE`              |`KC_PSTE`                      |粘贴                                   |             |             |✔                |
|`KC_FIND`               |                               |查找                                   |             |             |✔                |
|`KC_KB_MUTE`            |                               |静音                                   |             |✔            |✔                |
|`KC_KB_VOLUME_UP`       |                               |音量加                                 |             |✔            |✔                |
|`KC_KB_VOLUME_DOWN`     |                               |音量减                                 |             |✔            |✔                |
|`KC_LOCKING_CAPS_LOCK`  |`KC_LCAP`                      |锁定 Caps Lock                         |✔            |✔            |                 |
|`KC_LOCKING_NUM_LOCK`   |`KC_LNUM`                      |锁定 Num Lock                         |✔            |✔            |                 |
|`KC_LOCKING_SCROLL_LOCK`|`KC_LSCR`                      |锁定 Scroll Lock                      |✔            |✔            |                 |
|`KC_KP_COMMA`           |`KC_PCMM`                      |小键盘 `,`                             |             |             |✔                |
|`KC_KP_EQUAL_AS400`     |                               |小键盘 `=` on AS/400 keyboards         |             |             |                 |
|`KC_INTERNATIONAL_1`    |`KC_INT1`                      |International 1                        |✔            |             |✔                |
|`KC_INTERNATIONAL_2`    |`KC_INT2`                      |International 2                        |✔            |             |✔                |
|`KC_INTERNATIONAL_3`    |`KC_INT3`                      |International 3                        |✔            |             |✔                |
|`KC_INTERNATIONAL_4`    |`KC_INT4`                      |International 4                        |✔            |             |✔                |
|`KC_INTERNATIONAL_5`    |`KC_INT5`                      |International 5                        |✔            |             |✔                |
|`KC_INTERNATIONAL_6`    |`KC_INT6`                      |International 6                        |             |             |✔                |
|`KC_INTERNATIONAL_7`    |`KC_INT7`                      |International 7                        |             |             |                 |
|`KC_INTERNATIONAL_8`    |`KC_INT8`                      |International 8                        |             |             |                 |
|`KC_INTERNATIONAL_9`    |`KC_INT9`                      |International 9                        |             |             |                 |
|`KC_LANGUAGE_1`         |`KC_LNG1`                      |Language 1                             |             |             |✔                |
|`KC_LANGUAGE_2`         |`KC_LNG2`                      |Language 2                             |             |             |✔                |
|`KC_LANGUAGE_3`         |`KC_LNG3`                      |Language 3                             |             |             |✔                |
|`KC_LANGUAGE_4`         |`KC_LNG4`                      |Language 4                             |             |             |✔                |
|`KC_LANGUAGE_5`         |`KC_LNG5`                      |Language 5                             |             |             |✔                |
|`KC_LANGUAGE_6`         |`KC_LNG6`                      |Language 6                             |             |             |                 |
|`KC_LANGUAGE_7`         |`KC_LNG7`                      |Language 7                             |             |             |                 |
|`KC_LANGUAGE_8`         |`KC_LNG8`                      |Language 8                             |             |             |                 |
|`KC_LANGUAGE_9`         |`KC_LNG9`                      |Language 9                             |             |             |                 |
|`KC_ALTERNATE_ERASE`    |`KC_ERAS`                      |Alternate Erase                        |             |             |                 |
|`KC_SYSTEM_REQUEST`     |`KC_SYRQ`                      |SysReq/Attention                       |             |             |                 |
|`KC_CANCEL`             |`KC_CNCL`                      |Cancel                                 |             |             |                 |
|`KC_CLEAR`              |`KC_CLR`                       |Clear                                  |             |             |✔                |
|`KC_PRIOR`              |`KC_PRIR`                      |Prior                                  |             |             |                 |
|`KC_RETURN`             |`KC_RETN`                      |Return                                 |             |             |                 |
|`KC_SEPARATOR`          |`KC_SEPR`                      |Separator                              |             |             |                 |
|`KC_OUT`                |                               |Out                                    |             |             |                 |
|`KC_OPER`               |                               |Oper                                   |             |             |                 |
|`KC_CLEAR_AGAIN`        |`KC_CLAG`                      |Clear/Again                            |             |             |                 |
|`KC_CRSEL`              |`KC_CRSL`                      |CrSel/Props                            |             |             |                 |
|`KC_EXSEL`              |`KC_EXSL`                      |ExSel                                  |             |             |                 |
|`KC_LEFT_CTRL`          |`KC_LCTL`                      |左 Control                             |✔            |✔            |✔                |
|`KC_LEFT_SHIFT`         |`KC_LSFT`                      |左 Shift                               |✔            |✔            |✔                |
|`KC_LEFT_ALT`           |`KC_LALT`, `KC_LOPT`           |左 Alt (Option)                        |✔            |✔            |✔                |
|`KC_LEFT_GUI`           |`KC_LGUI`, `KC_LCMD`, `KC_LWIN`|左 GUI (Windows/Command/Meta 键)       |✔            |✔            |✔                |
|`KC_RIGHT_CTRL`         |`KC_RCTL`                      |右 Control                             |✔            |✔            |✔                |
|`KC_RIGHT_SHIFT`        |`KC_RSFT`                      |右 Shift                               |✔            |✔            |✔                |
|`KC_RIGHT_ALT`          |`KC_RALT`, `KC_ROPT`, `KC_ALGR`|右 Alt (Option/AltGr)                  |✔            |✔            |✔                |
|`KC_RIGHT_GUI`          |`KC_RGUI`, `KC_RCMD`, `KC_RWIN`|右 GUI (Windows/Command/Meta 键)        |✔            |✔            |✔                |
|`KC_SYSTEM_POWER`       |`KC_PWR`                       |关机                                   |✔            |✔<sup>3</sup>|✔                |
|`KC_SYSTEM_SLEEP`       |`KC_SLEP`                      |睡眠                                   |✔            |✔<sup>3</sup>|✔                |
|`KC_SYSTEM_WAKE`        |`KC_WAKE`                      |唤醒                                   |             |✔<sup>3</sup>|✔                |
|`KC_AUDIO_MUTE`         |`KC_MUTE`                      |静音                                   |✔            |✔            |✔                |
|`KC_AUDIO_VOL_UP`       |`KC_VOLU`                      |音量加                                 |✔            |✔<sup>4</sup>|✔                |
|`KC_AUDIO_VOL_DOWN`     |`KC_VOLD`                      |音量减                                 |✔            |✔<sup>4</sup>|✔                |
|`KC_MEDIA_NEXT_TRACK`   |`KC_MNXT`                      |下一首                                 |✔            |✔<sup>5</sup>|✔                |
|`KC_MEDIA_PREV_TRACK`   |`KC_MPRV`                      |上一首                                 |✔            |✔<sup>5</sup>|✔                |
|`KC_MEDIA_STOP`         |`KC_MSTP`                      |取消播放                                |✔            |             |✔                |
|`KC_MEDIA_PLAY_PAUSE`   |`KC_MPLY`                      |开始/暂停播放                           |✔            |✔            |✔                |
|`KC_MEDIA_SELECT`       |`KC_MSEL`                      |打开多媒体播放器                         |✔            |             |✔                |
|`KC_MEDIA_EJECT`        |`KC_EJCT`                      |弹出（媒介，如光盘）                      |             |✔            |✔                |
|`KC_MAIL`               |                               |打开邮箱                                |✔            |             |✔                |
|`KC_CALCULATOR`         |`KC_CALC`                      |打开计算器                              |✔            |             |✔                |
|`KC_MY_COMPUTER`        |`KC_MYCM`                      |打开“我的电脑”                          |✔            |             |✔                |
|`KC_WWW_SEARCH`         |`KC_WSCH`                      |浏览器中搜索                            |✔            |             |✔                |
|`KC_WWW_HOME`           |`KC_WHOM`                      |浏览器首页                              |✔            |             |✔                |
|`KC_WWW_BACK`           |`KC_WBAK`                      |浏览器后退                               |✔            |             |✔                |
|`KC_WWW_FORWARD`        |`KC_WFWD`                      |浏览器前进                              |✔            |             |✔                |
|`KC_WWW_STOP`           |`KC_WSTP`                      |浏览器取消                              |✔            |             |✔                |
|`KC_WWW_REFRESH`        |`KC_WREF`                      |浏览器刷新                              |✔            |             |✔                |
|`KC_WWW_FAVORITES`      |`KC_WFAV`                      |浏览器收藏夹                            |✔            |             |✔                |
|`KC_MEDIA_FAST_FORWARD` |`KC_MFFD`                      |（多媒体）快进                           |✔            |✔<sup>5</sup>|✔                |
|`KC_MEDIA_REWIND`       |`KC_MRWD`                      |（多媒体）后退                           |✔<sup>6</sup>|✔<sup>5</sup>|✔                |
|`KC_BRIGHTNESS_UP`      |`KC_BRIU`                      |亮度加                                  |✔            |✔            |✔                |
|`KC_BRIGHTNESS_DOWN`    |`KC_BRID`                      |亮度减                                 |✔            |✔            |✔                |

<sup>1. Linux 内核中的 HID 驱动可以识别 [几乎所有的键码](https://github.com/torvalds/linux/blob/master/drivers/hid/hid-input.c), 但默认的绑定操作取决于各DE/WM（桌面环境/窗口管理器）。</sup><br/>
<sup>2. 可视作 F13-F15。</sup><br/>
<sup>3. 须按住约3秒，之后会弹出确认提示。</sup><br/>
<sup>4. 按住 Shift+Option 可以更好地控制音量。</sup><br/>
<sup>5. 在 iTunes 中点击可以跳过整个音轨，按住可以在当前音轨快进。</sup><br/>
<sup>6. WMP 无法识别后退键。另外，快进及后退键都可以调整 VLC 的播放速度。</sup>

## 量子键码 :id=quantum-keycodes

参见：[量子键码](zh-cn/quantum_keycodes.md#qmk-keycodes)

|键            |别名      |描述                                                   |
|--------------|---------|-------------------------------------------------------|
|`RESET`       |         |使键盘进入可以进行刷写的 bootloader mode                  |
|`DEBUG`       |         |调试模式开关                                             |
|`EEPROM_RESET`|`EEP_RST`|重置键盘的 EEPROM 存储器（非易失存储器）                   |

## 音频键 :id=audio-keys

参见[音频](zh-cn/feature_audio.md)

|键              |别名      |描述                              |
|----------------|---------|----------------------------------|
|`AU_ON`         |         |启用音频                           |
|`AU_OFF`        |         |禁用音频                           |
|`AU_TOG`        |         |切换音频启停状态                    |
|`CLICKY_TOGGLE` |`CK_TOGG`|开关敲击声模式                      |
|`CLICKY_UP`     |`CK_UP`  |提高敲击声频率                      |
|`CLICKY_DOWN`   |`CK_DOWN`|降低敲击声频率                      |
|`CLICKY_RESET`  |`CK_RST` |重置敲击声频率                      |
|`MU_ON`         |         |打开音乐模式                       |
|`MU_OFF`        |         |关闭音乐模式                        |
|`MU_TOG`        |         |开关音乐模式                        |
|`MU_MOD`        |         |循环切换音乐模式                    |

## 背光 :id=backlighting

参见：[背光](zh-cn/feature_backlight.md)

|键       |描述                                       |
|---------|------------------------------------------|
|`BL_TOGG`|背光开关                                   |
|`BL_STEP`|循环切换背光强度                            |
|`BL_ON`  |背光亮度至最大                              |
|`BL_OFF` |关闭背光                                   |
|`BL_INC` |提高背光亮度                                |
|`BL_DEC` |降低背光亮度                                |
|`BL_BRTG`|开关背光呼吸功能                            |

## 蓝牙 :id=bluetooth

参见：[蓝牙](zh-cn/feature_bluetooth.md)

|键        |描述                                           |
|----------|----------------------------------------------|
|`OUT_AUTO`|自动在 USB 及蓝牙间切换                          |
|`OUT_USB` |仅 USB                                         |
|`OUT_BT`  |仅蓝牙                                         |

## 动态宏 :id=dynamic-macros

参见：[动态宏](zh-cn/feature_dynamic_macros.md)

|键               |别名      |描述                                              |
|-----------------|---------|--------------------------------------------------|
|`DYN_REC_START1` |`DM_REC1`|开始录制1号宏                                       |
|`DYN_REC_START2` |`DM_REC2`|开始录制2号宏                                       |
|`DYN_MACRO_PLAY1`|`DM_PLY1`|重放1号宏                                          |
|`DYN_MACRO_PLAY2`|`DM_PLY2`|重放2号宏                                          |
|`DYN_REC_STOP`   |`DM_RSTP`|结束录制当前在录制的宏                               |

## Grave Escape :id=grave-escape

参见：[Grave Escape](zh-cn/feature_grave_esc.md)

|键         |别名       |描述                                                              |
|-----------|---------|------------------------------------------------------------------|
|`GRAVE_ESC`|`KC_GESC`|点击时为Escape，按住Shift或GUI时点击为 <code>&#96;</code>             |

## 按键保持 :id=key-lock

参见：[按键保持](zh-cn/feature_key_lock.md)

|键      |描述                                                            |
|---------|--------------------------------------------------------------|
|`KC_LOCK`|将保持下一个点击的键为按下状态，指导再次点击该键                     |

## 层切换 :id=layer-switching

参见：[层切换](zh-cn/feature_layers.md#switching-and-toggling-layers)

|键             |描述                                                                                 |
|----------------|----------------------------------------------------------------------------------|
|`DF(layer)`     |设置基础（默认）层                                                                   |
|`MO(layer)`     |按住时临时启用 `layer` 层（目标层中该键必须是 `KC_TRNS`）                               |
|`OSL(layer)`    |临时启用 `layer` 层直到下一个键点击完毕。具体参见 [粘滞键](zh-cn/one_shot_keys.md)       |
|`LM(layer, mod)`|临时启用 `layer` 层（类似 MO）并激活 `mod` 状态，其中 `mod` 为 mods 位信息（mods_bit）。Mods 功能可以参见[这里](zh-cn/mod_tap.md)。示例：`LM(LAYER_1, MOD_LALT)`|
|`LT(layer, kc)` |按住时启用 `layer` 层，点击时为 `kc`                                                 |
|`TG(layer)`     |启用或禁用 `layer` 层                                                              |
|`TO(layer)`     |启用 `layer` 层及默认层，禁用其它所有层                                               |
|`TT(layer)`     |通常类似于 MO，但多次点击后将启用 `layer` 层                                          |

## 前导键 :id=leader-key

参见：[前导键](zh-cn/feature_leader_key.md)

|键       |描述                     |
|---------|------------------------|
|`KC_LEAD`|开始一段前导序列          |

## Magic 键码 :id=magic-keycodes

参见：[Magic键码](zh-cn/keycodes_magic.md)

|键                                |别名       |描述                                                                      |
|----------------------------------|---------|--------------------------------------------------------------------------|
|`MAGIC_SWAP_CONTROL_CAPSLOCK`     |`CL_SWAP`|Swap Caps Lock and Left Control                                           |
|`MAGIC_UNSWAP_CONTROL_CAPSLOCK`   |`CL_NORM`|Unswap Caps Lock and Left Control                                         |
|`MAGIC_TOGGLE_CONTROL_CAPSLOCK`   |`CL_TOGG`|Toggle Caps Lock and Left Control swap                                    |
|`MAGIC_CAPSLOCK_TO_CONTROL`       |`CL_CTRL`|Treat Caps Lock as Control                                                |
|`MAGIC_UNCAPSLOCK_TO_CONTROL`     |`CL_CAPS`|Stop treating Caps Lock as Control                                        |
|`MAGIC_SWAP_LCTL_LGUI`            |`LCG_SWP`|Swap Left Control and GUI                                                 |
|`MAGIC_UNSWAP_LCTL_LGUI`          |`LCG_NRM`|Unswap Left Control and GUI                                               |
|`MAGIC_SWAP_RCTL_RGUI`            |`RCG_SWP`|Swap Right Control and GUI                                                |
|`MAGIC_UNSWAP_RCTL_RGUI`          |`RCG_NRM`|Unswap Right Control and GUI                                              |
|`MAGIC_SWAP_CTL_GUI`              |`CG_SWAP`|Swap Control and GUI on both sides                                        |
|`MAGIC_UNSWAP_CTL_GUI`            |`CG_NORM`|Unswap Control and GUI on both sides                                      |
|`MAGIC_TOGGLE_CTL_GUI`            |`CG_TOGG`|Toggle Control and GUI swap on both sides                                 |
|`MAGIC_SWAP_LALT_LGUI`            |`LAG_SWP`|Swap Left Alt and GUI                                                     |
|`MAGIC_UNSWAP_LALT_LGUI`          |`LAG_NRM`|Unswap Left Alt and GUI                                                   |
|`MAGIC_SWAP_RALT_RGUI`            |`RAG_SWP`|Swap Right Alt and GUI                                                    |
|`MAGIC_UNSWAP_RALT_RGUI`          |`RAG_NRM`|Unswap Right Alt and GUI                                                  |
|`MAGIC_SWAP_ALT_GUI`              |`AG_SWAP`|Swap Alt and GUI on both sides                                            |
|`MAGIC_UNSWAP_ALT_GUI`            |`AG_NORM`|Unswap Alt and GUI on both sides                                          |
|`MAGIC_TOGGLE_ALT_GUI`            |`AG_TOGG`|Toggle Alt and GUI swap on both sides                                     |
|`MAGIC_NO_GUI`                    |`GUI_OFF`|Disable the GUI keys                                                      |
|`MAGIC_UNNO_GUI`                  |`GUI_ON` |Enable the GUI keys                                                       |
|`MAGIC_TOGGLE_GUI`                |`GUI_TOG`|Toggles the status of the GUI keys                                        |
|`MAGIC_SWAP_GRAVE_ESC`            |`GE_SWAP`|Swap <code>&#96;</code> and Escape                                        |
|`MAGIC_UNSWAP_GRAVE_ESC`          |`GE_NORM`|Unswap <code>&#96;</code> and Escape                                      |
|`MAGIC_SWAP_BACKSLASH_BACKSPACE`  |`BS_SWAP`|Swap `\` and Backspace                                                    |
|`MAGIC_UNSWAP_BACKSLASH_BACKSPACE`|`BS_NORM`|Unswap `\` and Backspace                                                  |
|`MAGIC_HOST_NKRO`                 |`NK_ON`  |Enable N-key rollover                                                     |
|`MAGIC_UNHOST_NKRO`               |`NK_OFF` |Disable N-key rollover                                                    |
|`MAGIC_TOGGLE_NKRO`               |`NK_TOGG`|Toggle N-key rollover                                                     |
|`MAGIC_EE_HANDS_LEFT`             |`EH_LEFT`|Set the master half of a split keyboard as the left hand (for `EE_HANDS`) |
|`MAGIC_EE_HANDS_RIGHT`            |`EH_RGHT`|Set the master half of a split keyboard as the right hand (for `EE_HANDS`)|

## MIDI :id=midi

参见：[MIDI](zh-cn/feature_midi.md)

（译注：TODO。由于翻译者对乐理基础掌握不到位，为确保不出现错误，暂不翻译。欢迎有能力的同志贡献一份力量。professional translating is welcome）

|键          |别名       |描述                            |
|------------|---------|---------------------------------|
|`MI_ON`     |         |Turn MIDI on                     |
|`MI_OFF`    |         |Turn MIDI off                    |
|`MI_TOG`    |         |Toggle MIDI enabled              |
|`MI_C`      |         |C octave 0                       |
|`MI_Cs`     |`MI_Db`  |C♯/D♭ octave 0                   |
|`MI_D`      |         |D octave 0                       |
|`MI_Ds`     |`MI_Eb`  |D♯/E♭ octave 0                   |
|`MI_E`      |         |E octave 0                       |
|`MI_F`      |         |F octave 0                       |
|`MI_Fs`     |`MI_Gb`  |F♯/G♭ octave 0                   |
|`MI_G`      |         |G octave 0                       |
|`MI_Gs`     |`MI_Gs`  |G♯/A♭ octave 0                   |
|`MI_A`      |         |A octave 0                       |
|`MI_As`     |`MI_Bb`  |A♯/B♭ octave 0                   |
|`MI_B`      |         |B octave 0                       |
|`MI_C_1`    |         |C octave 1                       |
|`MI_Cs_1`   |`MI_Db_1`|C♯/D♭ octave 1                   |
|`MI_D_1`    |         |D octave 1                       |
|`MI_Ds_1`   |`MI_Eb_1`|D♯/E♭ octave 1                   |
|`MI_E_1`    |         |E octave 1                       |
|`MI_F_1`    |         |F octave 1                       |
|`MI_Fs_1`   |`MI_Gb_1`|F♯/G♭ octave 1                   |
|`MI_G_1`    |         |G octave 1                       |
|`MI_Gs_1`   |`MI_Ab_1`|G♯/A♭ octave 1                   |
|`MI_A_1`    |         |A octave 1                       |
|`MI_As_1`   |`MI_Bb_1`|A♯/B♭ octave 1                   |
|`MI_B_1`    |         |B octave 1                       |
|`MI_C_2`    |         |C octave 2                       |
|`MI_Cs_2`   |`MI_Db_2`|C♯/D♭ octave 2                   |
|`MI_D_2`    |         |D octave 2                       |
|`MI_Ds_2`   |`MI_Eb_2`|D♯/E♭ octave 2                   |
|`MI_E_2`    |         |E octave 2                       |
|`MI_F_2`    |         |F octave 2                       |
|`MI_Fs_2`   |`MI_Gb_2`|F♯/G♭ octave 2                   |
|`MI_G_2`    |         |G octave 2                       |
|`MI_Gs_2`   |`MI_Ab_2`|G♯/A♭ octave 2                   |
|`MI_A_2`    |         |A octave 2                       |
|`MI_As_2`   |`MI_Bb_2`|A♯/B♭ octave 2                   |
|`MI_B_2`    |         |B octave 2                       |
|`MI_C_3`    |         |C octave 3                       |
|`MI_Cs_3`   |`MI_Db_3`|C♯/D♭ octave 3                   |
|`MI_D_3`    |         |D octave 3                       |
|`MI_Ds_3`   |`MI_Eb_3`|D♯/E♭ octave 3                   |
|`MI_E_3`    |         |E octave 3                       |
|`MI_F_3`    |         |F octave 3                       |
|`MI_Fs_3`   |`MI_Gb_3`|F♯/G♭ octave 3                   |
|`MI_G_3`    |         |G octave 3                       |
|`MI_Gs_3`   |`MI_Ab_3`|G♯/A♭ octave 3                   |
|`MI_A_3`    |         |A octave 3                       |
|`MI_As_3`   |`MI_Bb_3`|A♯/B♭ octave 3                   |
|`MI_B_3`    |         |B octave 3                       |
|`MI_C_4`    |         |C octave 4                       |
|`MI_Cs_4`   |`MI_Db_4`|C♯/D♭ octave 4                   |
|`MI_D_4`    |         |D octave 4                       |
|`MI_Ds_4`   |`MI_Eb_4`|D♯/E♭ octave 4                   |
|`MI_E_4`    |         |E octave 4                       |
|`MI_F_4`    |         |F octave 4                       |
|`MI_Fs_4`   |`MI_Gb_4`|F♯/G♭ octave 4                   |
|`MI_G_4`    |         |G octave 4                       |
|`MI_Gs_4`   |`MI_Ab_4`|G♯/A♭ octave 4                   |
|`MI_A_4`    |         |A octave 4                       |
|`MI_As_4`   |`MI_Bb_4`|A♯/B♭ octave 4                   |
|`MI_B_4`    |         |B octave 4                       |
|`MI_C_5`    |         |C octave 5                       |
|`MI_Cs_5`   |`MI_Db_5`|C♯/D♭ octave 5                   |
|`MI_D_5`    |         |D octave 5                       |
|`MI_Ds_5`   |`MI_Eb_5`|D♯/E♭ octave 5                   |
|`MI_E_5`    |         |E octave 5                       |
|`MI_F_5`    |         |F octave 5                       |
|`MI_Fs_5`   |`MI_Gb_5`|F♯/G♭ octave 5                   |
|`MI_G_5`    |         |G octave 5                       |
|`MI_Gs_5`   |`MI_Ab_5`|G♯/A♭ octave 5                   |
|`MI_A_5`    |         |A octave 5                       |
|`MI_As_5`   |`MI_Bb_5`|A♯/B♭ octave 5                   |
|`MI_B_5`    |         |B octave 5                       |
|`MI_OCT_N2` |         |Set octave to -2                 |
|`MI_OCT_N1` |         |Set octave to -1                 |
|`MI_OCT_0`  |         |Set octave to 0                  |
|`MI_OCT_1`  |         |Set octave to 1                  |
|`MI_OCT_2`  |         |Set octave to 2                  |
|`MI_OCT_3`  |         |Set octave to 3                  |
|`MI_OCT_4`  |         |Set octave to 4                  |
|`MI_OCT_5`  |         |Set octave to 5                  |
|`MI_OCT_6`  |         |Set octave to 6                  |
|`MI_OCT_7`  |         |Set octave to 7                  |
|`MI_OCTD`   |         |Move down an octave              |
|`MI_OCTU`   |         |Move up an octave                |
|`MI_TRNS_N6`|         |Set transposition to -6 semitones|
|`MI_TRNS_N5`|         |Set transposition to -5 semitones|
|`MI_TRNS_N4`|         |Set transposition to -4 semitones|
|`MI_TRNS_N3`|         |Set transposition to -3 semitones|
|`MI_TRNS_N2`|         |Set transposition to -2 semitones|
|`MI_TRNS_N1`|         |Set transposition to -1 semitone |
|`MI_TRNS_0` |         |No transposition                 |
|`MI_TRNS_1` |         |Set transposition to +1 semitone |
|`MI_TRNS_2` |         |Set transposition to +2 semitones|
|`MI_TRNS_3` |         |Set transposition to +3 semitones|
|`MI_TRNS_4` |         |Set transposition to +4 semitones|
|`MI_TRNS_5` |         |Set transposition to +5 semitones|
|`MI_TRNS_6` |         |Set transposition to +6 semitones|
|`MI_TRNSD`  |         |Decrease transposition           |
|`MI_TRNSU`  |         |Increase transposition           |
|`MI_VEL_0`  |         |Set velocity to 0                |
|`MI_VEL_1`  |         |Set velocity to 12               |
|`MI_VEL_2`  |         |Set velocity to 25               |
|`MI_VEL_3`  |         |Set velocity to 38               |
|`MI_VEL_4`  |         |Set velocity to 51               |
|`MI_VEL_5`  |         |Set velocity to 64               |
|`MI_VEL_6`  |         |Set velocity to 76               |
|`MI_VEL_7`  |         |Set velocity to 89               |
|`MI_VEL_8`  |         |Set velocity to 102              |
|`MI_VEL_9`  |         |Set velocity to 114              |
|`MI_VEL_10` |         |Set velocity to 127              |
|`MI_VELD`   |         |Decrease velocity                |
|`MI_VELU`   |         |Increase velocity                |
|`MI_CH1`    |         |Set channel to 1                 |
|`MI_CH2`    |         |Set channel to 2                 |
|`MI_CH3`    |         |Set channel to 3                 |
|`MI_CH4`    |         |Set channel to 4                 |
|`MI_CH5`    |         |Set channel to 5                 |
|`MI_CH6`    |         |Set channel to 6                 |
|`MI_CH7`    |         |Set channel to 7                 |
|`MI_CH8`    |         |Set channel to 8                 |
|`MI_CH9`    |         |Set channel to 9                 |
|`MI_CH10`   |         |Set channel to 10                |
|`MI_CH11`   |         |Set channel to 11                |
|`MI_CH12`   |         |Set channel to 12                |
|`MI_CH13`   |         |Set channel to 13                |
|`MI_CH14`   |         |Set channel to 14                |
|`MI_CH15`   |         |Set channel to 15                |
|`MI_CH16`   |         |Set channel to 16                |
|`MI_CHD`    |         |Decrease channel                 |
|`MI_CHU`    |         |Increase channel                 |
|`MI_ALLOFF` |         |Stop all notes                   |
|`MI_SUS`    |         |Sustain                          |
|`MI_PORT`   |         |Portmento                        |
|`MI_SOST`   |         |Sostenuto                        |
|`MI_SOFT`   |         |Soft Pedal                       |
|`MI_LEG`    |         |Legato                           |
|`MI_MOD`    |         |Modulation                       |
|`MI_MODSD`  |         |Decrease modulation speed        |
|`MI_MODSU`  |         |Increase modulation speed        |
|`MI_BENDD`  |         |Bend pitch down                  |
|`MI_BENDU`  |         |Bend pitch up                    |

## 鼠标键 :id=mouse-keys

参见：[鼠标键](zh-cn/feature_mouse_keys.md)

|键              |别名       |描述                       |
|----------------|---------|---------------------------|
|`KC_MS_UP`      |`KC_MS_U`|鼠标指针上移                 |
|`KC_MS_DOWN`    |`KC_MS_D`|鼠标指针下移                 |
|`KC_MS_LEFT`    |`KC_MS_L`|鼠标指针左移                 |
|`KC_MS_RIGHT`   |`KC_MS_R`|鼠标指针右移                 |
|`KC_MS_BTN1`    |`KC_BTN1`|鼠标键1                     |
|`KC_MS_BTN2`    |`KC_BTN2`|鼠标键2                     |
|`KC_MS_BTN3`    |`KC_BTN3`|鼠标键3                     |
|`KC_MS_BTN4`    |`KC_BTN4`|鼠标键4                     |
|`KC_MS_BTN5`    |`KC_BTN5`|鼠标键5                     |
|`KC_MS_WH_UP`   |`KC_WH_U`|鼠标滚轮向上                 |
|`KC_MS_WH_DOWN` |`KC_WH_D`|鼠标滚轮向下                 |
|`KC_MS_WH_LEFT` |`KC_WH_L`|鼠标滚轮向左                 |
|`KC_MS_WH_RIGHT`|`KC_WH_R`|鼠标滚轮向右                 |
|`KC_MS_ACCEL0`  |`KC_ACL0`|设置鼠标加速度为 0           |
|`KC_MS_ACCEL1`  |`KC_ACL1`|设置鼠标加速度为 1           |
|`KC_MS_ACCEL2`  |`KC_ACL2`|设置鼠标加速度为 2           |

## 修饰键 :id=modifiers

参见：[修饰键](zh-cn/feature_advanced_keycodes.md#modifier-keys)

|键        |别名                                |描述                                                 |
|----------|----------------------------------|------------------------------------------------------|
|`LCTL(kc)`|`C(kc)`                           |左Control + `kc`                                      |
|`LSFT(kc)`|`S(kc)`                           |左Shift + `kc`                                        |
|`LALT(kc)`|`A(kc)`, `LOPT(kc)`               |左Alt + `kc`                                          |
|`LGUI(kc)`|`G(kc)`, `LCMD(kc)`, `LWIN(kc)`   |左GUI + `kc`                                          |
|`RCTL(kc)`|                                  |右Control + `kc`                                      |
|`RSFT(kc)`|                                  |右Shift + `kc`                                        |
|`RALT(kc)`|`ROPT(kc)`, `ALGR(kc)`            |右Alt (AltGr) + `kc`                                  |
|`RGUI(kc)`|`RCMD(kc)`, `LWIN(kc)`            |右GUI + `kc`                                          |
|`LSG(kc)` |`SGUI(kc)`, `SCMD(kc)`, `SWIN(kc)`|左Shift + 左GUI + `kc`                                |
|`LAG(kc)` |                                  |左Alt + 左GUI + `kc`                                  |
|`RSG(kc)` |                                  |右Shift + 右 GUI + `kc`                               |
|`RAG(kc)` |                                  |右Alt + 右 GUI + `kc`                                 |
|`LCA(kc)` |                                  |左Control + Alt + `kc`                                |
|`LSA(kc)` |                                  |左Shift + 左Alt + `kc`                                |
|`RSA(kc)` |`SAGR(kc)`                        |右Shift + 右 Alt (AltGr) + `kc`                       |
|`RCS(kc)` |                                  |右Control + 右 Shift + `kc`                           |
|`LCAG(kc)`|                                  |左Control, Alt + GUI + `kc`                           |
|`MEH(kc)` |                                  |左Control, Shift + Alt + `kc`                         |
|`HYPR(kc)`|                                  |左Control, Shift, Alt + GUI + `kc`                    |
|`KC_MEH`  |                                  |左Control, Shift + Alt                                |
|`KC_HYPR` |                                  |左Control, Shift, Alt + GUI                           |

## Mod-Tap 键 :id=mod-tap-keys

参见：[Mod-Tap](zh-cn/mod_tap.md)

|键           |别名                                                               |描述                                                             |
|-------------|-----------------------------------------------------------------|--------------------------------------------------------------|
|`MT(mod, kc)`|                                                                 |`mod` when held, `kc` when tapped                             |
|`LCTL_T(kc)` |`CTL_T(kc)`                                                      |Left Control when held, `kc` when tapped                      |
|`LSFT_T(kc)` |`SFT_T(kc)`                                                      |Left Shift when held, `kc` when tapped                        |
|`LALT_T(kc)` |`LOPT_T(kc)`, `ALT_T(kc)`, `OPT_T(kc)`                           |Left Alt when held, `kc` when tapped                          |
|`LGUI_T(kc)` |`LCMD_T(kc)`, `LWIN_T(kc)`, `GUI_T(kc)`, `CMD_T(kc)`, `WIN_T(kc)`|Left GUI when held, `kc` when tapped                          |
|`RCTL_T(kc)` |                                                                 |Right Control when held, `kc` when tapped                     |
|`RSFT_T(kc)` |                                                                 |Right Shift when held, `kc` when tapped                       |
|`RALT_T(kc)` |`ROPT_T(kc)`, `ALGR_T(kc)`                                       |Right Alt (AltGr) when held, `kc` when tapped                 |
|`RGUI_T(kc)` |`RCMD_T(kc)`, `RWIN_T(kc)`                                       |Right GUI when held, `kc` when tapped                         |
|`LSG_T(kc)`  |`SGUI_T(kc)`, `SCMD_T(kc)`, `SWIN_T(kc)`                         |Left Shift and GUI when held, `kc` when tapped                |
|`LAG_T(kc)`  |                                                                 |Left Alt and GUI when held, `kc` when tapped                  |
|`RSG_T(kc)`  |                                                                 |Right Shift and GUI when held, `kc` when tapped               |
|`RAG_T(kc)`  |                                                                 |Right Alt and GUI when held, `kc` when tapped                 |
|`LCA_T(kc)`  |                                                                 |Left Control and Alt when held, `kc` when tapped              |
|`LSA_T(kc)`  |                                                                 |Left Shift and Left Alt when held, `kc` when tapped           |
|`RSA_T(kc)`  |`SAGR_T(kc)`                                                     |Right Shift and Right Alt (AltGr) when held, `kc` when tapped |
|`RCS_T(kc)`  |                                                                 |Right Control and Right Shift when held, `kc` when tapped     |
|`LCAG_T(kc)` |                                                                 |Left Control, Alt and GUI when held, `kc` when tapped         |
|`RCAG_T(kc)` |                                                                 |Right Control, Alt and GUI when held, `kc` when tapped        |
|`C_S_T(kc)`  |                                                                 |Left Control and Shift when held, `kc` when tapped            |
|`MEH_T(kc)`  |                                                                 |Left Control, Shift and Alt when held, `kc` when tapped       |
|`HYPR_T(kc)` |`ALL_T(kc)`                                                      |Left Control, Shift, Alt and GUI when held, `kc` when tapped - more info [here](https://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)|

## Tapping Term 键 :id=tapping-term-keys

参见：[动态 Tapping Term](zh-cn/tap_hold#dynamic-tapping-term)

| Key         | Description                                                                                                            |
|-------------|------------------------------------------------------------------------------------------------------------------------|
| `DT_PRNT`   | "Dynamic Tapping Term Print": Types the current tapping term, in milliseconds                                          |
| `DT_UP`     | "Dynamic Tapping Term Up": Increases the current tapping term by `DYNAMIC_TAPPING_TERM_INCREMENT`ms (5ms by default)   |
| `DT_DOWN`   | "Dynamic Tapping Term Down": Decreases the current tapping term by `DYNAMIC_TAPPING_TERM_INCREMENT`ms (5ms by default) |

## RGB 灯光 :id=rgb-lighting

参见：[RGB 灯光](zh-cn/feature_rgblight.md)

|键                 |别名        |描述                                                               |
|-------------------|----------|--------------------------------------------------------------------|
|`RGB_TOG`          |          |开关RGB灯光                                                          |
|`RGB_MODE_FORWARD` |`RGB_MOD` |循环切换灯光模式，按下Shift时将反向循环                                  |
|`RGB_MODE_REVERSE` |`RGB_RMOD`|反向循环切换灯光模式，按下Shift时将正向循环                              |
|`RGB_HUI`          |          |增加色调值（hue），按下Shift时为降低                                    |
|`RGB_HUD`          |          |降低色调值，按下Shift时为增加                                          |
|`RGB_SAI`          |          |增加饱和度（saturation），按下Shift时为降低                             |
|`RGB_SAD`          |          |降低饱和度，按下Shift时为增加                                          |
|`RGB_VAI`          |          |增加亮度（brightness），按下Shift时为降低                               |
|`RGB_VAD`          |          |降低亮度，按下Shift时为增加                                            |
|`RGB_MODE_PLAIN`   |`RGB_M_P `|静态模式（无动态效果）                                                 |
|`RGB_MODE_BREATHE` |`RGB_M_B` |呼吸模式                                                             |
|`RGB_MODE_RAINBOW` |`RGB_M_R` |彩虹动态效果模式                                                      |
|`RGB_MODE_SWIRL`   |`RGB_M_SW`|盘旋动态效果模式                                                      |
|`RGB_MODE_SNAKE`   |`RGB_M_SN`|贪吃蛇动态效果模式                                                    |
|`RGB_MODE_KNIGHT`  |`RGB_M_K` |“骑士”动态效果模式                                                    |
|`RGB_MODE_XMAS`    |`RGB_M_X` |圣诞动态效果模式                                                      |
|`RGB_MODE_GRADIENT`|`RGB_M_G` |固定渐变动态效果模式                                                  |
|`RGB_MODE_RGBTEST` |`RGB_M_T` |红绿蓝颜色测试模式                                                    |

## RGB 矩阵灯光 :id=rgb-matrix-lighting

参见：[RGB矩阵灯光](zh-cn/feature_rgb_matrix.md)

|键                 |别名        |描述                                                                                 |
|-------------------|----------|--------------------------------------------------------------------------------------|
|`RGB_TOG`          |          |开关RGB矩阵灯光                                                                         |
|`RGB_MODE_FORWARD` |`RGB_MOD` |循环切换灯光模式，按下Shift时将反向循环                                                    |
|`RGB_MODE_REVERSE` |`RGB_RMOD`|反向循环切换灯光模式，按下Shift时将正向循环                                                 |
|`RGB_HUI`          |          |增加色调值（hue），按下Shift时为降低                                                      |
|`RGB_HUD`          |          |降低色调值，按下Shift时为增加                                                             |
|`RGB_SAI`          |          |增加饱和度（saturation），按下Shift时为降低                                               |
|`RGB_SAD`          |          |降低饱和度，按下Shift时为增加                                                             |
|`RGB_VAI`          |          |增加亮度（brightness），按下Shift时为降低                                                 |
|`RGB_VAD`          |          |降低亮度，按下Shift时为增加                                                              |
|`RGB_SPI`          |          |加快动态效果速度（暂不支持存储到eeprom），按下Shift时为降低                                  |
|`RGB_SPD`          |          |降低动态效果速度（暂不支持存储到eeprom），按下Shift时为加快                                  |

## 热敏打印机 :id=thermal-printer

参见：[热敏打印机](zh-cn/feature_thermal_printer.md)

|键        |描述                                       |
|-----------|----------------------------------------|
|`PRINT_ON` |开始打印用户所有的输入                     |
|`PRINT_OFF`|停止打印                                 |

## US ANSI 上档符号 :id=us-ansi-shifted-symbols

参见：[US ANSI 上档符号](zh-cn/keycodes_us_ansi_shifted.md)

|键                      |别名                 |描述          |
|------------------------|-------------------|-----------|
|`KC_TILDE`              |`KC_TILD`          |`~`        |
|`KC_EXCLAIM`            |`KC_EXLM`          |`!`        |
|`KC_AT`                 |                   |`@`        |
|`KC_HASH`               |                   |`#`        |
|`KC_DOLLAR`             |`KC_DLR`           |`$`        |
|`KC_PERCENT`            |`KC_PERC`          |`%`        |
|`KC_CIRCUMFLEX`         |`KC_CIRC`          |`^`        |
|`KC_AMPERSAND`          |`KC_AMPR`          |`&`        |
|`KC_ASTERISK`           |`KC_ASTR`          |`*`        |
|`KC_LEFT_PAREN`         |`KC_LPRN`          |`(`        |
|`KC_RIGHT_PAREN`        |`KC_RPRN`          |`)`        |
|`KC_UNDERSCORE`         |`KC_UNDS`          |`_`        |
|`KC_PLUS`               |                   |`+`        |
|`KC_LEFT_CURLY_BRACE`   |`KC_LCBR`          |`{`        |
|`KC_RIGHT_CURLY_BRACE`  |`KC_RCBR`          |`}`        |
|`KC_PIPE`               |                   |`\|`       |
|`KC_COLON`              |`KC_COLN`          |`:`        |
|`KC_DOUBLE_QUOTE`       |`KC_DQUO`, `KC_DQT`|`"`        |
|`KC_LEFT_ANGLE_BRACKET` |`KC_LABK`, `KC_LT` |`<`        |
|`KC_RIGHT_ANGLE_BRACKET`|`KC_RABK`, `KC_GT` |`>`        |
|`KC_QUESTION`           |`KC_QUES`          |`?`        |

## 粘滞键 :id=one-shot-keys

参见：[粘滞键](zh-cn/one_shot_keys.md)

|键         |描述                                 |
|------------|----------------------------------|
|`OSM(mod)`  |对下一个键附带 `mod` 键             |
|`OSL(layer)`|下一个键临时被切换到 `layer` 层      |
|`OS_ON`     |启用粘滞键                         |
|`OS_OFF`    |停用粘滞键                         |
|`OS_TOGG`   |启停粘滞键功能                      |

## 可编程按键支援 :id=programmable-button

参见：[可编程按键](feature_programmable_button.md)

|键                     |描述                    |
|------------------------|----------------------|
|`PROGRAMMABLE_BUTTON_1` |可编程键 1             |
|`PROGRAMMABLE_BUTTON_2` |可编程键 2             |
|`PROGRAMMABLE_BUTTON_3` |可编程键 3             |
|`PROGRAMMABLE_BUTTON_4` |可编程键 4             |
|`PROGRAMMABLE_BUTTON_5` |可编程键 5             |
|`PROGRAMMABLE_BUTTON_6` |可编程键 6             |
|`PROGRAMMABLE_BUTTON_7` |可编程键 7             |
|`PROGRAMMABLE_BUTTON_8` |可编程键 8             |
|`PROGRAMMABLE_BUTTON_9` |可编程键 9             |
|`PROGRAMMABLE_BUTTON_10`|可编程键 10            |
|`PROGRAMMABLE_BUTTON_11`|可编程键 11            |
|`PROGRAMMABLE_BUTTON_12`|可编程键 12            |
|`PROGRAMMABLE_BUTTON_13`|可编程键 13            |
|`PROGRAMMABLE_BUTTON_14`|可编程键 14            |
|`PROGRAMMABLE_BUTTON_15`|可编程键 15            |
|`PROGRAMMABLE_BUTTON_16`|可编程键 16            |
|`PROGRAMMABLE_BUTTON_17`|可编程键 17            |
|`PROGRAMMABLE_BUTTON_18`|可编程键 18            |
|`PROGRAMMABLE_BUTTON_19`|可编程键 19            |
|`PROGRAMMABLE_BUTTON_20`|可编程键 20            |
|`PROGRAMMABLE_BUTTON_21`|可编程键 21            |
|`PROGRAMMABLE_BUTTON_22`|可编程键 22            |
|`PROGRAMMABLE_BUTTON_23`|可编程键 23            |
|`PROGRAMMABLE_BUTTON_24`|可编程键 24            |
|`PROGRAMMABLE_BUTTON_25`|可编程键 25            |
|`PROGRAMMABLE_BUTTON_26`|可编程键 26            |
|`PROGRAMMABLE_BUTTON_27`|可编程键 27            |
|`PROGRAMMABLE_BUTTON_28`|可编程键 28            |
|`PROGRAMMABLE_BUTTON_29`|可编程键 29            |
|`PROGRAMMABLE_BUTTON_30`|可编程键 30            |
|`PROGRAMMABLE_BUTTON_31`|可编程键 31            |
|`PROGRAMMABLE_BUTTON_32`|可编程键 32            |
|`PB_1` 到 `PB_32`        |相应的键映射的别名     |

## Space Cadet :id=space-cadet

参见：[Space Cadet](zh-cn/feature_space_cadet.md)

|键        |描述                                       |
|-----------|----------------------------------------|
|`KC_LCPO`  |Left Control when held, `(` when tapped |
|`KC_RCPC`  |Right Control when held, `)` when tapped|
|`KC_LSPO`  |Left Shift when held, `(` when tapped   |
|`KC_RSPC`  |Right Shift when held, `)` when tapped  |
|`KC_LAPO`  |Left Alt when held, `(` when tapped     |
|`KC_RAPC`  |Right Alt when held, `)` when tapped    |
|`KC_SFTENT`|Right Shift when held, Enter when tapped|

## 换手 :id=swap-hands

参见：[换手](zh-cn/feature_swap_hands.md)

|键        |描述                                                                        |
|-----------|-------------------------------------------------------------------------|
|`SH_T(key)`|Sends `key` with a tap; momentary swap when held.                        |
|`SW_ON`    |Turns on swapping and leaves it on.                                      |
|`SW_OFF`   |Turn off swapping and leaves it off. Good for returning to a known state.|
|`SH_MON`   |Swaps hands when pressed, returns to normal when released (momentary).   |
|`SH_MOFF`  |Momentarily turns off swap.                                              |
|`SH_TG`    |Toggles swap on and off with every key press.                            |
|`SH_TT`    |Toggles with a tap; momentary when held.                                 |
|`SH_OS`    |One shot swap hands: toggle while pressed or until next key press.       |

## Unicode 支持 :id=unicode-support

参见：[Unicode 支持](zh-cn/feature_unicode.md)

|键                    |别名       |描述                                                           |
|----------------------|---------|----------------------------------------------------------------|
|`UC(c)`               |         |发送 Unicode 码点 `c`                                            |
|`X(i)`                |         |发送 `unicode_map` 表中索引为 `i` 的 Unicode 码点                  |
|`XP(i, j)`            |         |发送索引为 `i` 的 Unicode 码点，在Shift按下或Caps状态下，则发送 `j`   |
|`UNICODE_MODE_FORWARD`|`UC_MOD` |循环切换选中的输入模式                                             |
|`UNICODE_MODE_REVERSE`|`UC_RMOD`|反向循环切换选中的输入模式                                          |
|`UNICODE_MODE_MAC`    |`UC_M_MA`|切换到 macOS 输入模式                                             |
|`UNICODE_MODE_LNX`    |`UC_M_LN`|切换到 Linux 输入模式                                             |
|`UNICODE_MODE_WIN`    |`UC_M_WI`|切换到 Windows 输入模式                                           |
|`UNICODE_MODE_BSD`    |`UC_M_BS`|切换到 BSD 输入模式（暂未实现）                                     |
|`UNICODE_MODE_WINC`   |`UC_M_WC`|切换到 Windows 输入模式并使用 WinCompose                           |
