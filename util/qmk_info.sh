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
	grep -oP '^[[:blank:]]*#.*PRODUCT\_ID[\s\t]*\K([0-9A-Za-z]+)'
}

if [ -f $ROOT/keyboards/$1/config.h ]; then
	if cat $ROOT/keyboards/$1/config.h | get_vendor_id > /dev/null; then
		VENDOR=$(cat $ROOT/keyboards/$1/config.h | get_vendor_id)
	fi
	if cat $ROOT/keyboards/$1/config.h | get_product_id > /dev/null; then
		PRODUCT=$(cat $ROOT/keyboards/$1/config.h | get_product_id)
	fi
fi

if [ -z "$3" ]; then
	if [ -f $ROOT/keyboards/$1/$3/config.h ]; then
		if cat $ROOT/keyboards/$1/$3/config.h | get_vendor_id > /dev/null; then
			VENDOR=$(cat $ROOT/keyboards/$1/$3/config.h | get_vendor_id)
		fi
		if cat $ROOT/keyboards/$1/$3/config.h | get_product_id > /dev/null; then
			PRODUCT=$(cat $ROOT/keyboards/$1/$3/config.h | get_product_id)
		fi
	fi
	if [ -f $ROOT/keyboards/$1/$3/keymaps/$2/config.h ]; then
		if cat $ROOT/keyboards/$1/$3/keymaps/$2/config.h | get_vendor_id > /dev/null; then
			VENDOR=$(cat $ROOT/keyboards/$1/$3/keymaps/$2/config.h | get_vendor_id)
		fi
		if cat $ROOT/keyboards/$1/$3/keymaps/$2/config.h | get_product_id > /dev/null; then
			PRODUCT=$(cat $ROOT/keyboards/$1/$3/keymaps/$2/config.h | get_product_id)
		fi
	fi
else
	if [ -f $ROOT/keyboards/$1/keymaps/$2/config.h ]; then
		if cat $ROOT/keyboards/$1/keymaps/$2/config.h | get_vendor_id > /dev/null; then
			VENDOR=$(cat $ROOT/keyboards/$1/keymaps/$2/config.h | get_vendor_id)
		fi
		if cat $ROOT/keyboards/$1/keymaps/$2/config.h | get_product_id > /dev/null; then
			PRODUCT=$(cat $ROOT/keyboards/$1/keymaps/$2/config.h | get_product_id)
		fi
	fi
fi

echo "{"
echo " \"vendor\": $VENDOR,"
echo " \"product_id\": $PRODUCT,"
echo "}"