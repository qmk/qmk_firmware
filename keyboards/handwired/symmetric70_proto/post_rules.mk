KEYBOARD_LOCAL_OPTIONS_MK := $(dir $(lastword $(MAKEFILE_LIST)))local_options.mk
KEYBOARD_LOCAL_FEATURES_MK := $(dir $(lastword $(MAKEFILE_LIST)))local_features.mk

include $(strip $(KEYBOARD_LOCAL_OPTIONS_MK))
include $(strip $(KEYBOARD_LOCAL_FEATURES_MK))
