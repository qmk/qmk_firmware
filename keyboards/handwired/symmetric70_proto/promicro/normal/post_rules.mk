KEYBOARD_BOOST_post_rules_MK := $(dir $(lastword $(MAKEFILE_LIST)))../boost/post_rules.mk
include $(strip $(KEYBOARD_BOOST_post_rules_MK))
