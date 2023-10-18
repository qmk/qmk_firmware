# handwired/cheapwire

![handwired/cheapwire](https://github.com/cocolizo945/qmk_firmware/assets/81886929/4061c9e0-0de0-4f59-882a-e559f994c122)


*A short description of the keyboard/project*

* Keyboard Maintainer: [Eduardo Mendez](https://github.com/cocolizo945)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make handwired/cheapwire:default

Flashing example for this keyboard:

    make handwired/cheapwire:default:flash

Flashing example for this keyboard with via:

    qmk flash -kb handwired/cheapwire -km via

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## Cheapwire

The cheapwire takes as inspiration the [ScottoSplit](https://scottokeebs.com/blogs/keyboards/scottosplit-handwired-keyboard).
now is compatible with via and vial, the most atracctive quality from the cheapwire is the cost, approximately 15 - 20 usd

## BOM / Bill Of Materials
 * [42 diodes 1n4148](https://es.aliexpress.com/item/1005004333197874.html?spm=a2g0o.productlist.main.1.2ffa343fMMb7GU&algo_pvid=61d2bd8c-aa8a-444b-a2ff-7c45e0d8bf19&aem_p4p_detail=2023101721173317510947210490450000102777&algo_exp_id=61d2bd8c-aa8a-444b-a2ff-7c45e0d8bf19-0&pdp_npi=4%40dis%21MXN%216.25%215.88%21%21%210.34%21%21%40210321dc16976026539063889e0c2c%2112000028793174971%21sea%21MX%212814777900%21&curPageLogUid=isyOUlMKr3Fv&search_p4p_id=2023101721173317510947210490450000102777_1)
 * [42 switches](https://es.aliexpress.com/item/1005003134698091.html?spm=a2g0o.productlist.main.19.6233660a6Qhjau&algo_pvid=45852590-d735-4ebe-b210-d838e30d998b&aem_p4p_detail=202310172110561321914381303450003572098&algo_exp_id=45852590-d735-4ebe-b210-d838e30d998b-9&pdp_npi=4%40dis%21MXN%21260.59%21158.97%21%21%2114.18%21%21%402101e7f616976022560162651e52bd%2112000024279974426%21sea%21MX%212814777900%21&curPageLogUid=lQKwUZiWiyAd&search_p4p_id=202310172110561321914381303450003572098_10)   
 * [1 set of keycaps](https://es.aliexpress.com/item/1005004776662298.html?spm=a2g0o.productlist.main.17.15402efbqSpD8K&algo_pvid=d17cc1d2-7de2-4058-9220-654b1a6aae14&algo_exp_id=d17cc1d2-7de2-4058-9220-654b1a6aae14-8&pdp_npi=4%40dis%21MXN%21263.53%2112.31%21%21%2114.34%21%21%402101ea7116976026083433653e6a57%2112000030472647642%21sea%21MX%210%21AB&curPageLogUid=wbA4oMKghX8h)
 * [2 db25 female](https://es.aliexpress.com/item/1005004937486315.html?spm=a2g0o.productlist.main.47.4ece4b9f2rnCMQ&algo_pvid=c3d925fd-bacc-46f9-a054-c0348745af91&aem_p4p_detail=2023101721180810309015791214700000154861&algo_exp_id=c3d925fd-bacc-46f9-a054-c0348745af91-23&pdp_npi=4%40dis%21MXN%215.51%214.96%21%21%210.30%21%21%402103209b16976026885432920e79bd%2112000031082492991%21sea%21MX%212814777900%21&curPageLogUid=xY7xrXNgsDCQ&search_p4p_id=2023101721180810309015791214700000154861_24)
 * 2 db25 male
 * 2 db25 cover
 * coaxial cable aprox 1.5 mts
 *     {as non etical recomend used in this build, you can make some aliexpress accounts to use the newbie discount}

## pinout for rp pico[info.json](https://github.com/cocolizo945/qmk_firmware/files/12981521/info.json)

i found some problem when i make my pinout but i'll gonna explain it now using my wiring driagram and the info.json

    {
    "manufacturer": "Eduardo Mendez",
    "keyboard_name": "handwired/cheapwire",
    "maintainer": "cocolizo945",
    "bootloader": "rp2040",
    "diode_direction": "COL2ROW",
    "features": {
        "bootmagic": true,
        "command": false,
        "console": false,
        "extrakey": true,
        "mousekey": true,
        "nkro": true
    },
    "matrix_pins": {
        "cols": ["GP4", "GP5", "GP6", "GP7", "GP8", "GP9", "GP16", "GP17", "GP18", "GP19", "GP20", "GP21"],
        "rows": ["GP0", "GP1", "GP2", "GP3", "GP11", "GP12", "GP13", "GP14"]
    },
    "processor": "RP2040",
    "url": "",
    "usb": {
        "device_version": "1.0.0",
        "pid": "0x2416",
        "vid": "0x4351"
    },
    "layouts": {
        "LAYOUT_split_3x6_3": {
            "layout": [
                //row gp0
                {"matrix": [0, 0], "x": 0, "y": 0.75},
                {"matrix": [0, 1], "x": 1, "y": 0.5},
                {"matrix": [0, 2], "x": 2, "y": 0.25},
                {"matrix": [0, 3], "x": 3, "y": 0},
                {"matrix": [0, 4], "x": 4, "y": 0.25},
                {"matrix": [0, 5], "x": 5, "y": 0.5},

                //ro2 gp1
                {"matrix": [1, 11], "x": 0, "y": 1.75},
                {"matrix": [1, 10], "x": 1, "y": 1.5},
                {"matrix": [1, 9], "x": 2, "y": 1.25},
                {"matrix": [1, 8], "x": 3, "y": 1},
                {"matrix": [1, 7], "x": 4, "y": 1.25},
                {"matrix": [1, 6], "x": 5, "y": 1.5},

                //row gp2
                {"matrix": [2, 0], "x": 0, "y": 2.75},
                {"matrix": [2, 1], "x": 1, "y": 2.5},
                {"matrix": [2, 2], "x": 2, "y": 2.25},
                {"matrix": [2, 3], "x": 3, "y": 2},
                {"matrix": [2, 4], "x": 4, "y": 2.25},
                {"matrix": [2, 5], "x": 5, "y": 2.5},
                 
                //ro2 gp3
                {"matrix": [3, 11], "x": 0, "y": 1.75},
                {"matrix": [3, 10], "x": 1, "y": 1.5},
                {"matrix": [3, 9], "x": 2, "y": 1.25},
                {"matrix": [3, 8], "x": 3, "y": 1},
                {"matrix": [3, 7], "x": 4, "y": 1.25},
                {"matrix": [3, 6], "x": 5, "y": 1.5},
 

                //row gp11  
                {"matrix": [4, 0], "x": 0, "y": 0.75},
                {"matrix": [4, 1], "x": 1, "y": 0.5},
                {"matrix": [4, 2], "x": 2, "y": 0.25},
                {"matrix": [4, 3], "x": 3, "y": 0},
                {"matrix": [4, 4], "x": 4, "y": 0.25},
                {"matrix": [4, 5], "x": 5, "y": 0.5},

                //ro2 gp12
                {"matrix": [5, 11], "x": 0, "y": 1.75},
                {"matrix": [5, 10], "x": 1, "y": 1.5},
                {"matrix": [5, 9], "x": 2, "y": 1.25},
                {"matrix": [5, 8], "x": 3, "y": 1},
                {"matrix": [5, 7], "x": 4, "y": 1.25},
                {"matrix": [5, 6], "x": 5, "y": 1.5},

                //row gp13
                {"matrix": [6, 3], "x": 3, "y": 2},
                {"matrix": [6, 4], "x": 4, "y": 2.25},
                {"matrix": [6, 5], "x": 5, "y": 2.5},
                 
                // row gp14
                {"matrix": [7, 11], "x": 3.5, "y": 3.5},
                {"matrix": [7, 10], "x": 4.5, "y": 3.75},
                {"matrix": [7, 9], "x": 5.5, "y": 4}
            ]
        }
    }
    }


![PinOut](https://github.com/cocolizo945/qmk_firmware/assets/81886929/458a1571-f3af-4925-87d0-2e38bb76f8a5)
for some reason takes the matrix as a line but is corrected by wiring as is indicade in the pinout


## Matrix Wiring
There is the wiring but remember, both sides are independent from the other. is just a graphical guide if you are lost in the wiring
![Matrix wiring](https://github.com/cocolizo945/qmk_firmware/assets/81886929/c6b1ece0-cfaa-4f8a-aee9-fac3a4ad008c)

![wired](https://github.com/cocolizo945/qmk_firmware/assets/81886929/8ea87875-f0c0-4fe1-b23d-02942c8d2cb3)


## db25
well in is case there is not a fixed way to make the connection, so you are free to experiment in this case. :D




