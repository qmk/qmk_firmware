# Copyright 2023  EricaLina
# This makefile has status and help, use:
# make status
# make help

# This Makefile prints lots of more readable stuff,
# no need to see every echo.
.SILENT:

user-space := ericgebhart
keyboards-home := ../../keyboards

############################################################
# Keyboards that are part of the qmk_firmware
############################################################
## The list of keyboard paths to put keymap stubs in.
## See below for keyboards that are not defined as part of the qmk_firmware
user-keyboard-maps := ergodox_ez xiudi/xd75 keebio/viterbi crkbd \
	montsinger/rebound/rev4 kinesis splitkb/kyria            \
	ferris planck

############################################################
# Keyboards that are _NOT_ part of the qmk_firmware
############################################################
# For repos that contain just a qmk keyboard definition.
# add keyboard name to list, define name-repo.
# These will be cloned directly into the keyboards/ directory.
keyboards := hummingbird
hummingbird-repo := https://github.com/kilipan/hummingbird_qmk

# For keyboards that  are defined as part of a full qmk_firmware repo.
# We will clone them and extract the keyboard into this QMK_firmware.
# add keyboard name to list, define name-repo.
extract-keyboards := svalboard
svalboard-repo := https://github.com/morganvenable/qmk_firmware

############################################################
#  Target Rules
############################################################
# test if target replaces inside a variable name. It does.
testit-repo := someplace-far-far-away
testit:
	printf "$($@-repo)"

# handy diagnostic rule.
# make print-VARIABLE ie. make print-profiles, make print-emacs-home
print-%  : ; @echo $* = $($*)

$(user-keyboard-maps):
	printf "\n-----------------------------------------------------\n"
	printf "Adding $(user-space) keymap for $@ \n"
	mkdir -p $(keyboards-home)/$(@)/keymaps/$(user-space)
	echo  '/* see users/$(user-space) */' > $(keyboards-home)/$(@)/keymaps/$(user-space)/keymap.c


# install the easy, sparce, external to qmk keyboard definitions
# make hummingbird ...
$(keyboards):
	printf "\n-----------------------------------------------------\n"
	printf "Adding keyboard definition for $@ \n"
	git clone $($@-repo) ../../keyboards/$@
	printf "\n-----------------------------------------------------\n\n"
	printf "Adding $(user-space) keymap for $@ \n"
	mkdir -p $(keyboards-home)/$(@)/keymaps/$(user-space)
	echo  '/* see users/$(user-space) */' > $(keyboards-home)/$(@)/keymaps/$(user-space)/keymap.c
	printf "\n-----------------------------------------------------\n"


# install the svalboard keyboard definition
$(extract-keyboards):
	printf "\n-----------------------------------------------------\n"
	printf "Cloning into temporary QMK\n"
	git clone $($@-repo) tmp_qmk
	printf "Extracting keyboard definition for $@ \n"
	cp -r tmp_qmk/keyboards/$@  ../../keyboards/
	printf "Removing temporary QMK\n"
	rm -rf tmp_qmk
	printf "\n-----------------------------------------------------\n"
	printf "Adding $(user-space) keymap for $@ \n"
	mkdir -p $(keyboards-home)/$(@)/keymaps/$(user-space)
	echo  '/* see users/$(user-space) */' > $(keyboards-home)/$(@)/keymaps/$(user-space)/keymap.c
	printf "\n-----------------------------------------------------\n\n"

# install all keymap stubs for the user space.
install-keymaps: $(user-keyboard-maps)
install-keyboards: $(keyboards) $(extract-keyboards)
install-all: $(keyboards) $(extract-keyboards) $(user-keyboard-maps)

status:
	printf "\n-----------------------------------------------------\n"
	printf "Status:\n"
	printf "User Space:  $(user-space)"
	printf "\n-----------------------------------------------------\n"
	printf "\nSupported keyboard maps:\n"
	printf "$(user-keyboard-maps)\n"
	printf "\nAny of these may be used as a make target to install a keymap.\n"
	printf "\nAll of them may be installed with:\n make install-keymaps\n"

	printf "\n-----------------------------------------------------\n"
	printf "Keyboard definitions external to QMK:\n"
	printf "These are repos with just the keyboard definition as it exists"
	printf " in the keyboard directory in QMK.\n\n"
	printf "\nAny of these may be used as a make target to install a keyboard and map.\n"
	printf "Keyboards: \n"
	printf $(keyboards)

	printf "\n\nThese keyboards are part of a full qmk repo and will be extracted"
	printf "into this install.\n"
	printf "Keyboards which must be extracted: \n"
	printf $(extract-keyboards)
	printf "\n\nAll of these may be installed with:\n make install-keyboards\n"

	printf "\n-----------------------------------------------------\n"

help: status
	printf "\nPurpose:\n"
	printf "This Makeflie exists only to create empty keymap stubs for this"
	printf "user space:  $(user-space)\n\n"

	printf "This user space only requires an empty keymap.c placeholder under"
	printf "the keyboard/keymaps directory for the keyboards it supports.\n\n"
	printf "All of them may be installed with:\n make install-keymaps\n"

	printf "keyboard definitions.\n"
	printf "Use:\n\n"
	printf "make ferris\n"
	printf "make crkbd\n"
	printf "make splitkb/kyria\n"

	printf "\n\nTo install all keymaps for QMK keyboards:\n"
	printf "\nmake install-keymaps\n"

	printf "Additionally it may install keyboard definitions from outside of QMK\n"
	printf "\nmake hummingbird\n"
	printf "\nmake svalboard\n"

	printf "\n\nTo install all keyboards known by this makefile use:\n"
	printf "\nmake install-keyboards\n"

	printf "\n\nTo install everything.\n"
	printf "\nmake install-all\n"

	printf "\n-----------------------------------------------------\n"
	printf "Configure the keyboard in config.org if you are an emacs/org user.\n"
	printf "Tangling config.org will generate config.h and rules.mk.\n"
	printf "Otherwise edit config.h and rules.mk\n\n"
	printf "\n-----------------------------------------------------\n"
	printf "Building:\n\n"
	printf "Change directories to the root of qmk and build qmk how you like.\n\n"
	printf "Optionally use the qmk command to build.\n\n"

	printf "Example QMK build commands:\n\n"
	printf "make splitkb/kyria/rev2:$(user-space):flash -e CONVERT_TO=liatris\n\n"
	printf "make crkbd:$(user-space):flash \n\n"
	printf "make kinesis:$(user-space):flash \n\n"
	printf "\n-----------------------------------------------------\n"
