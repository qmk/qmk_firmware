# Custom Split Transport

To disable the customized split transport, add `CUSTOM_SPLIT_TRANSPORT_SYNC = no` to your `rules.mk`.

This syncs a number of additional settings, such as the keymap_config (magic settings), user eeprom configs, and misc firmware settings. 

Additionally, this supports a watchdog timer reset for the secondary split side. 

## User State Config 

The User states that it sync are: 

* Audio Enable status
* Audio Clicky states
* Unicode mode
* Pointing Device tap toggle status
* Swap Hands status
* Host Driver status

## Userspace Config

The userspace config states that are synced are: 

* RGB layer indication
* "is overwatch" status
* nuke switch
* Swapped numbers
* RGB Matrix idle animation
* Autocorrect enable status
