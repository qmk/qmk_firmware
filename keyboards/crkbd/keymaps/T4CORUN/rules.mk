# Settings to add/override what is in both

#baseline
USER_NAME := T4CORUN
OLED_DRIVER = SSD1306

#override userspace
# $Repo\qmk_firmware\users\T4CORUN\rules.mk
DYNAMIC_MACRO_ENABLE = no
ONESHOT_ENABLE = yes
TAPHOLD_ENABLE = yes
COMBO_ENABLE = yes

#override 
# $qmk_firmware\keyboards\crkbd\rev1\rules.mk
# $qmk_firmware\keyboards\crkbd\rules.mk
# $qmk_firmware\keyboards\crkbd\info.json
RGB_MATRIX_ENABLE = no
RGBLIGHT_ENABLE = no