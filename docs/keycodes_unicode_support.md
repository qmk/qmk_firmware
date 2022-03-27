|Key                   |Aliases  |Description                                                     |
|----------------------|---------|----------------------------------------------------------------|
|`UC(c)`               |         |Send Unicode code point `c`, up to `0x7FFF`                     |
|`X(i)`                |         |Send Unicode code point at index `i` in `unicode_map`           |
|`XP(i, j)`            |         |Send Unicode code point at index `i`, or `j` if Shift/Caps is on|
|`UNICODE_MODE_FORWARD`|`UC_MOD` |Cycle through selected input modes                              |
|`UNICODE_MODE_REVERSE`|`UC_RMOD`|Cycle through selected input modes in reverse                   |
|`UNICODE_MODE_MAC`    |`UC_M_MA`|Switch to macOS input                                           |
|`UNICODE_MODE_LNX`    |`UC_M_LN`|Switch to Linux input                                           |
|`UNICODE_MODE_WIN`    |`UC_M_WI`|Switch to Windows input                                         |
|`UNICODE_MODE_BSD`    |`UC_M_BS`|Switch to BSD input (not implemented)                           |
|`UNICODE_MODE_WINC`   |`UC_M_WC`|Switch to Windows input using WinCompose                        |