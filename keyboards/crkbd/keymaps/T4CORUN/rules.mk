# Settings to add/override what is in both

#baseline
USER_NAME := T4CORUN
OLED_DRIVER = SSD1306

#override userspace
# $Repo\qmk_firmware\users\T4CORUN\rules.mk
GAMELAYER_ENABLE = yes
OLED_ENABLE = yes
DYNAMIC_MACRO_ENABLE = no
KEYLOG_ENABLE = yes

#override 
# $qmk_firmware\keyboards\crkbd\rev1\rules.mk
# $qmk_firmware\keyboards\crkbd\rules.mk
RGB_MATRIX_ENABLE = yes
NKRO_ENABLE = no