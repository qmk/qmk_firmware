|Key                     |Aliases                        |Description                            |Windows      |macOS        |Linux<sup>1</sup>|
|------------------------|-------------------------------|---------------------------------------|-------------|-------------|-----------------|
|`KC_SYSTEM_POWER`       |`KC_PWR`                       |System Power Down                      |✔            |✔<sup>3</sup>|✔                |
|`KC_SYSTEM_SLEEP`       |`KC_SLEP`                      |System Sleep                           |✔            |✔<sup>3</sup>|✔                |
|`KC_SYSTEM_WAKE`        |`KC_WAKE`                      |System Wake                            |             |✔<sup>3</sup>|✔                |
|`KC_AUDIO_MUTE`         |`KC_MUTE`                      |Mute                                   |✔            |✔            |✔                |
|`KC_AUDIO_VOL_UP`       |`KC_VOLU`                      |Volume Up                              |✔            |✔<sup>4</sup>|✔                |
|`KC_AUDIO_VOL_DOWN`     |`KC_VOLD`                      |Volume Down                            |✔            |✔<sup>4</sup>|✔                |
|`KC_MEDIA_NEXT_TRACK`   |`KC_MNXT`                      |Next Track                             |✔            |✔<sup>5</sup>|✔                |
|`KC_MEDIA_PREV_TRACK`   |`KC_MPRV`                      |Previous Track                         |✔            |✔<sup>5</sup>|✔                |
|`KC_MEDIA_STOP`         |`KC_MSTP`                      |Stop Track                             |✔            |             |✔                |
|`KC_MEDIA_PLAY_PAUSE`   |`KC_MPLY`                      |Play/Pause Track                       |✔            |✔            |✔                |
|`KC_MEDIA_SELECT`       |`KC_MSEL`                      |Launch Media Player                    |✔            |             |✔                |
|`KC_MEDIA_EJECT`        |`KC_EJCT`                      |Eject                                  |             |✔            |✔                |
|`KC_MAIL`               |                               |Launch Mail                            |✔            |             |✔                |
|`KC_CALCULATOR`         |`KC_CALC`                      |Launch Calculator                      |✔            |             |✔                |
|`KC_MY_COMPUTER`        |`KC_MYCM`                      |Launch My Computer                     |✔            |             |✔                |
|`KC_WWW_SEARCH`         |`KC_WSCH`                      |Browser Search                         |✔            |             |✔                |
|`KC_WWW_HOME`           |`KC_WHOM`                      |Browser Home                           |✔            |             |✔                |
|`KC_WWW_BACK`           |`KC_WBAK`                      |Browser Back                           |✔            |             |✔                |
|`KC_WWW_FORWARD`        |`KC_WFWD`                      |Browser Forward                        |✔            |             |✔                |
|`KC_WWW_STOP`           |`KC_WSTP`                      |Browser Stop                           |✔            |             |✔                |
|`KC_WWW_REFRESH`        |`KC_WREF`                      |Browser Refresh                        |✔            |             |✔                |
|`KC_WWW_FAVORITES`      |`KC_WFAV`                      |Browser Favorites                      |✔            |             |✔                |
|`KC_MEDIA_FAST_FORWARD` |`KC_MFFD`                      |Next Track                             |✔            |✔<sup>5</sup>|✔                |
|`KC_MEDIA_REWIND`       |`KC_MRWD`                      |Previous Track                         |✔<sup>6</sup>|✔<sup>5</sup>|✔                |
|`KC_BRIGHTNESS_UP`      |`KC_BRIU`                      |Brightness Up                          |✔            |✔            |✔                |
|`KC_BRIGHTNESS_DOWN`    |`KC_BRID`                      |Brightness Down                        |✔            |✔            |✔                |

<sup>1. The Linux kernel HID driver recognizes [nearly all keycodes](https://github.com/torvalds/linux/blob/master/drivers/hid/hid-input.c), but the default bindings depend on the DE/WM.</sup><br/>
<sup>2. Treated as F13-F15.</sup><br/>
<sup>3. Must be held for about three seconds, and will display a prompt instead.</sup><br/>
<sup>4. Holding Shift+Option allows for finer control of volume level.</sup><br/>
<sup>5. Skips the entire track in iTunes when tapped, seeks within the current track when held.</sup><br/>
<sup>6. WMP does not recognize the Rewind key, but both alter playback speed in VLC.</sup>