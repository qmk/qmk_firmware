# p3lim's b.face layout

![](https://user-images.githubusercontent.com/26496/61170794-bf8a2c80-a56e-11e9-893f-f1766e7a9a04.png)

My layout using the winkeyless b.face X2 PCB.

### Building & Flashing

- Set up QMK
	- `pip install --user qmk`
	- `qmk setup`
- Add udev rules if on Linux
	- Follow the docs: <https://docs.qmk.fm/#/faq_build?id=linux-udev-rules>
- Build and flash
	- `qmk flash -kb winkeyless/bface -km p3lim`
- Hold bottom-left key while connecting to put in flashing mode

### Layout notes

The keys indicated with a gray color in the image above was not supported by the layout so a custom matrix was made.
The two additional keys were on pins 22+41 and 22+42, C3+B1 and C3+B2, which is mapped to col 10 row 1 and col 10 row 2 in the matrix.
