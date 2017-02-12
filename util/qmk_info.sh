#!/bin/bash
# 1: KEYBOARD
# 2: KEYMAP
# 3: SUBPROJECT

ROOT=.

function get_vendor_id () {
	grep -oP '^[[:blank:]]*#.*VENDOR\_ID[\s\t]*\K([0-9A-Za-z]+)'
}
function get_product_id () {
	grep -oP '^[[:blank:]]*#.*PRODUCT\_ID[\s\t]*\K([0-9A-Za-z]+)'
}
function get_device_ver () {
	grep -oP '^[[:blank:]]*#.*DEVICE\_VER[\s\t]*\K([0-9A-Za-z]+)'
}

KEYBOARD_CONFIG=$ROOT/keyboards/$1/config.h
if [ -f $KEYBOARD_CONFIG ]; then
	if cat $KEYBOARD_CONFIG | get_vendor_id > /dev/null; then
		VENDOR_ID=$(cat $KEYBOARD_CONFIG | get_vendor_id)
	fi
	if cat $KEYBOARD_CONFIG | get_product_id > /dev/null; then
		PRODUCT_ID=$(cat $KEYBOARD_CONFIG | get_product_id)
	fi
	if cat $KEYBOARD_CONFIG | get_device_ver > /dev/null; then
		DEVICE_VER=$(cat $KEYBOARD_CONFIG | get_device_ver)
	fi
fi

if [ ! -z "$3" ]; then
	SUBPROJECT_CONFIG=$ROOT/keyboards/$1/$3/config.h
	if [ -f $SUBPROJECT_CONFIG ]; then
		if cat $SUBPROJECT_CONFIG | get_vendor_id > /dev/null; then
			VENDOR_ID=$(cat $SUBPROJECT_CONFIG | get_vendor_id)
		fi
		if cat $SUBPROJECT_CONFIG | get_product_id > /dev/null; then
			PRODUCT_ID=$(cat $SUBPROJECT_CONFIG | get_product_id)
		fi
		if cat $SUBPROJECT_CONFIG | get_device_ver > /dev/null; then
			DEVICE_VER=$(cat $SUBPROJECT_CONFIG | get_device_ver)
		fi
	fi
fi

KEYMAP_CONFIG=$ROOT/keyboards/$1/keymaps/$2/config.h
if [ -f $KEYMAP_CONFIG ]; then
	if cat $KEYMAP_CONFIG | get_vendor_id > /dev/null; then
		VENDOR_ID=$(cat $KEYMAP_CONFIG | get_vendor_id)
	fi
	if cat $KEYMAP_CONFIG | get_product_id > /dev/null; then
		PRODUCT_ID=$(cat $KEYMAP_CONFIG | get_product_id)
	fi
	if cat $KEYMAP_CONFIG | get_device_ver > /dev/null; then
		DEVICE_VER=$(cat $KEYMAP_CONFIG | get_device_ver)
	fi
fi

echo "{"
echo " \"keyboard\": \"$1\","
echo " \"keymap\": \"$2\","
if [ ! -z "$3" ]; then
	echo " \"subproject\": \"$3\","
fi
echo " \"vendor_id\": $VENDOR_ID,"
echo " \"product_id\": $PRODUCT_ID,"
echo " \"device_ver\": $DEVICE_VER,"
echo "}"