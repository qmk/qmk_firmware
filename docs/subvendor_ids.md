# Vendor, Subvendor, Product, Project IDs in QMK

    #define VENDOR_ID  0x03A8
                         ^ 
                         + QMK's self-assigned Vendor ID
    
    #define PRODUCT_ID 0x0000
                         ^  ^ 
                         |  + Project ID
                         + Subvendor ID

There are many projects using QMK that aren't large enough where it would make sense to obtain a Vendor ID of their own, and [the USB-IF isn't interested in others transferring a VID to communities like ours](http://www.arachnidlabs.com/blog/2013/10/18/usb-if-no-vid-for-open-source/), so QMK uses the unassigned Vendor ID `0x03A8` for all Vendors/Makers/Companies (Subvendors for clarification) that aren't interested in obtaining their own, and maintains a master list (`subvendor_ids.txt`) in the repo to ensure unique values for each project. 

Subvendor IDs in QMK are a bitmask of the `PRODUCT_ID`: `0xFFE0` - this leaves 5 bits for the Project ID (0x001F bitmask), of which each Subvendor can have 32. If the Project ID is larger than 15, add 1 to the Subvendor ID (`0xFA4 -> 0xFA5`) - all Subvendor IDs are even (in hex) to allow this. All Subvendor IDs are randomly generated.

## Using other values

It's not recommended using custom Vendor IDs, but some projects may have obtained their own, and are welcome to use them in QMK, but only with permission of the project's creator (the owner of the Vendor ID).

## Creating a new Subvendor ID

To generate a new valid, random ID, run this bash script from the root qmk_firmware folder by substituting `<subvendor>` with your company/vendor name (leave the quotes):

    util/new_subvendor_id.sh "<subvendor>"

This script will output your ID, and automatically append it to the list below as well as the master list (`subvendor_ids.txt`).

# Currently used Subvendor IDs:

 * 0x5A6: OLKB
