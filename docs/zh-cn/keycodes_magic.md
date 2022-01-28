# Magic 键码 :id=magic-keycodes

**Magic 键码** 以 `MAGIC_` 为前缀，在初始化键盘后，允许你访问被弃用的 Bootmagic 特性的功能。为了使用这些键码，可以在 keymap 中指定，就像其他键码那样。

| 键                                 | 别名      | 描述                                        |
| ---------------------------------- | --------- | ------------------------------------------- |
| `MAGIC_SWAP_CONTROL_CAPSLOCK`      | `CL_SWAP` | 交换 Caps Lock 和左 Control                 |
| `MAGIC_UNSWAP_CONTROL_CAPSLOCK`    | `CL_NORM` | 不交换 Caps Lock 和左 Control               |
| `MAGIC_CAPSLOCK_TO_CONTROL`        | `CL_CTRL` | 将 Caps Lock 作为 Control                   |
| `MAGIC_UNCAPSLOCK_TO_CONTROL`      | `CL_CAPS` | 停止将 Caps Lock 作为 Control               |
| `MAGIC_SWAP_LCTL_LGUI`             | `LCG_SWP` | 交换左 Control 和 GUI                       |
| `MAGIC_UNSWAP_LCTL_LGUI`           | `LCG_NRM` | 不交换左 Control 和 GUI                     |
| `MAGIC_SWAP_RCTL_RGUI`             | `RCG_SWP` | 交换右 Control 和 GUI                       |
| `MAGIC_UNSWAP_RCTL_RGUI`           | `RCG_NRM` | 不交换右 Control 和 GUI                     |
| `MAGIC_SWAP_CTL_GUI`               | `CG_SWAP` | 交换 Control 和 GUI，左右两边同时           |
| `MAGIC_UNSWAP_CTL_GUI`             | `CG_NORM` | 不交换 Control 和 GUI，左右两边同时         |
| `MAGIC_TOGGLE_CTL_GUI`             | `CG_TOGG` | 锁定交换 Control 和 GUI，左右两边同时       |
| `MAGIC_SWAP_LALT_LGUI`             | `LAG_SWP` | 交换左 Alt 和 GUI                           |
| `MAGIC_UNSWAP_LALT_LGUI`           | `LAG_NRM` | 不交换左 Alt 和 GUI                         |
| `MAGIC_SWAP_RALT_RGUI`             | `RAG_SWP` | 交换右 Alt 和 GUI                           |
| `MAGIC_UNSWAP_RALT_RGUI`           | `RAG_NRM` | 不交换右 Alt 和 GUI                         |
| `MAGIC_SWAP_ALT_GUI`               | `AG_SWAP` | 交换 Alt 和 GUI，左右两边同时               |
| `MAGIC_UNSWAP_ALT_GUI`             | `AG_NORM` | 不交换 Alt 和 GUI，左右两边同时             |
| `MAGIC_TOGGLE_ALT_GUI`             | `AG_TOGG` | 锁定交换 Alt 和 GUI，左右两边同时           |
| `MAGIC_NO_GUI`                     | `GUI_OFF` | 禁用 GUI 键                                 |
| `MAGIC_UNNO_GUI`                   | `GUI_ON`  | 启用 GUI 键                                 |
| `MAGIC_TOGGLE_GUI`                 | `GUI_TOG` | 锁定 GUI 键状态                             |
| `MAGIC_SWAP_GRAVE_ESC`             | `GE_SWAP` | 交换 <code>&#96;</code> 和 Escape           |
| `MAGIC_UNSWAP_GRAVE_ESC`           | `GE_NORM` | 不交换 <code>&#96;</code> 和 Escape         |
| `MAGIC_SWAP_BACKSLASH_BACKSPACE`   | `BS_SWAP` | 交换 `\` 和 Backspace                       |
| `MAGIC_UNSWAP_BACKSLASH_BACKSPACE` | `BS_NORM` | 不交换 `\` 和 Backspace                     |
| `MAGIC_HOST_NKRO`                  | `NK_ON`   | 启用全键无冲（N-key rollover）              |
| `MAGIC_UNHOST_NKRO`                | `NK_OFF`  | 禁用全键无冲（N-key rollover）              |
| `MAGIC_TOGGLE_NKRO`                | `NK_TOGG` | 锁定全键无冲（N-key rollover）              |
| `MAGIC_EE_HANDS_LEFT`              | `EH_LEFT` | 将拆分键盘的主控部分设置为左手 (`EE_HANDS`) |
| `MAGIC_EE_HANDS_RIGHT`             | `EH_RGHT` | 将拆分键盘的主控部分设置为右手 (`EE_HANDS`) |
