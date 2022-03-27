|Key                     |Aliases                        |Description                            |Windows      |macOS        |Linux<sup>1</sup>|
|------------------------|-------------------------------|---------------------------------------|-------------|-------------|-----------------|
|`KC_PRINT_SCREEN`       |`KC_PSCR`                      |Print Screen                           |✔            |✔<sup>2</sup>|✔                |
|`KC_PAUSE`              |`KC_PAUS`, `KC_BRK`, `KC_BRMU` |Pause, Brightness Up (macOS)           |✔            |✔<sup>2</sup>|✔                |
|`KC_INSERT`             |`KC_INS`                       |Insert                                 |✔            |             |✔                |
|`KC_HOME`               |                               |Home                                   |✔            |✔            |✔                |
|`KC_PAGE_UP`            |`KC_PGUP`                      |Page Up                                |✔            |✔            |✔                |
|`KC_DELETE`             |`KC_DEL`                       |Forward Delete                         |✔            |✔            |✔                |
|`KC_END`                |                               |End                                    |✔            |✔            |✔                |
|`KC_PAGE_DOWN`          |`KC_PGDN`                      |Page Down                              |✔            |✔            |✔                |
|`KC_RIGHT`              |`KC_RGHT`                      |Right Arrow                            |✔            |✔            |✔                |
|`KC_LEFT`               |                               |Left Arrow                             |✔            |✔            |✔                |
|`KC_DOWN`               |                               |Down Arrow                             |✔            |✔            |✔                |
|`KC_UP`                 |                               |Up Arrow                               |✔            |✔            |✔                |
|`KC_APPLICATION`        |`KC_APP`                       |Application (Windows Context Menu Key) |✔            |             |✔                |
|`KC_KB_POWER`           |                               |System Power                           |             |✔<sup>3</sup>|✔                |
|`KC_EXECUTE`            |`KC_EXEC`                      |Execute                                |             |             |✔                |
|`KC_HELP`               |                               |Help                                   |             |             |✔                |
|`KC_MENU`               |                               |Menu                                   |             |             |✔                |
|`KC_SELECT`             |`KC_SLCT`                      |Select                                 |             |             |✔                |
|`KC_STOP`               |                               |Stop                                   |             |             |✔                |
|`KC_AGAIN`              |`KC_AGIN`                      |Again                                  |             |             |✔                |
|`KC_UNDO`               |                               |Undo                                   |             |             |✔                |
|`KC_CUT`                |                               |Cut                                    |             |             |✔                |
|`KC_COPY`               |                               |Copy                                   |             |             |✔                |
|`KC_PASTE`              |`KC_PSTE`                      |Paste                                  |             |             |✔                |
|`KC_FIND`               |                               |Find                                   |             |             |✔                |
|`KC_KB_MUTE`            |                               |Mute                                   |             |✔            |✔                |
|`KC_KB_VOLUME_UP`       |                               |Volume Up                              |             |✔            |✔                |
|`KC_KB_VOLUME_DOWN`     |                               |Volume Down                            |             |✔            |✔                |
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

<sup>1. The Linux kernel HID driver recognizes [nearly all keycodes](https://github.com/torvalds/linux/blob/master/drivers/hid/hid-input.c), but the default bindings depend on the DE/WM.</sup><br/>
<sup>2. Treated as F13-F15.</sup><br/>
<sup>3. Must be held for about three seconds, and will display a prompt instead.</sup><br/>