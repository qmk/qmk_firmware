# baseline
USER_NAME := T4CORUN
SRC += muse.c

# override userspace
# $Repo\qmk_firmware\users\T4CORUN\rules.mk
GAMELAYER_ENABLE = yes

# override
# $qmk_firmware\keyboards\planck\rev6\rules.mk
COMMAND_ENABLE = no
ENCODER_ENABLE = no
DIP_SWITCH_ENABLE = no