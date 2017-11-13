#!/bin/bash

if [[ $0 != *"util"* ]]; then
    echo "Please run from the root qmk_firmware folder"
    exit 1
fi

if [ -z "$1" ]; then
    echo "Need a subvendor"
    echo "usage: $0 <subvendor>"
    exit 1
fi

function generate_random() {
    subvendor_id=`printf '0x%X%X%X' $(( ( RANDOM % 16 ) )) $(( ( RANDOM % 16 ) )) $(( ( RANDOM % 8 ) * 2 ))`
}

function find_existing() {
    existing=`grep "${subvendor_id}" subvendor_ids.txt`
}

while : ; do
    generate_random
    find_existing
    (( -z "$existing" )) || break
done

echo ${subvendor_id}: ${1} >> subvendor_ids.txt
echo " * ${subvendor_id}: ${1}" >> docs/subvendor_ids.md
echo "The Subvendor ID ${subvendor_id} is now associated with \"${1}\", and has been added to the list"
echo "Add your Project ID (0x0-0xF) to the end and use it in your config.h:"
echo 
echo "  #define VENDOR_ID  0x03A8"
echo "  #define PRODUCT_ID ${subvendor_id}0"
echo