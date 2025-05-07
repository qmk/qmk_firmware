# Include custom features
SRC += rgb_effects/rgb_effects.c rgb_effects/work_timer.c

# MCU name
MCU = RP2040

# Platform specification
PLATFORM = CHIBIOS

# Features not in info.json
DYNAMIC_MACRO_ENABLE = yes
KEY_LOCK_ENABLE = yes

# Disabled features to save space
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
MUSIC_ENABLE = no
LEADER_ENABLE = no
MIDI_ENABLE = no
BLUETOOTH_ENABLE = no
AUDIO_ENABLE = no