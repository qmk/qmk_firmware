# Vendor, Product, Project IDs in QMK

    #define VENDOR_ID  0x03A8
                         ^ 
                         + QMK's self-assigned Vendor ID
    
    #define PRODUCT_ID 0x0000
                         ^
                         + Project IDs

There are many projects using QMK that aren't large enough where it would make sense to obtain a Vendor ID of their own, and [the USB-IF isn't interested in others transferring a VID to communities like ours](http://www.arachnidlabs.com/blog/2013/10/18/usb-if-no-vid-for-open-source/), so QMK uses the unassigned Vendor ID `0x03A8` for all Vendors/Makers/Companies (Projects for clarification) that aren't interested in obtaining their own, and maintains a master list (`project_ids.txt`) in the repo to ensure unique values for each project. 

Project IDs are created from the first 4 digits of a SHA-256 hash of the main project location in QMK (e.g. `olkb/planck`), without the revision folder. If that ID exists in the list, the range is shifted down one digit (e.g. it would now selected digits 2 through 5).

## Using other values

It's not recommended using custom Vendor IDs, but some projects may have obtained their own, and are welcome to use them in QMK, but only with permission of the project's creator (the owner of the Vendor ID).
