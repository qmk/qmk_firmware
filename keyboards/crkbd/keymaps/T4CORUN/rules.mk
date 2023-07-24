# Settings to add/override what is in both

#baseline
USER_NAME := T4CORUN
OLED_DRIVER = SSD1306

#override userspace
# $Repo\qmk_firmware\users\T4CORUN\rules.mk
OLED_ENABLE = yes
DYNAMIC_MACRO_ENABLE = no
HOMEROWMOD_ENABLE = no
ONESHOT_ENABLE = yes
TAPHOLD_ENABLE = yes

#override 
# $qmk_firmware\keyboards\crkbd\rev1\rules.mk
# $qmk_firmware\keyboards\crkbd\rules.mk
RGB_MATRIX_ENABLE = yes
RGBLIGHT_ENABLE = no
NKRO_ENABLE = no