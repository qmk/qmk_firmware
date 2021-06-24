# Building

## Before building

If you have added a new keyboard, or changed layout macros, then please run: ```python generate_layout.py >  kbd_defs.cpp```

## Building on Linux for Linux

### Option 1: Building on local system

1) Install qt5 development packages
2) Install hidapi development packages
3) Optionally: make sure your preferred backend is selected in util.pro:
   ```
   LIBS += -lhidapi-libusb
   #LIBS += -lhidapi-hidraw
   ```
4) ```qmake-qt5 util.pro```  (or ```qmake util.pro```. NOTE: you must run the QT5 version of qmake, if you have both QT4 and QT5 installed)
5) ```make clean && make -j```
6) Optionally: add the following rules to ```/etc/udev/rules.d/my_preferred_filename.rules```
   ```
   SUBSYSTEMS=="usb", ATTRS{idVendor}=="0481", ATTRS{idProduct}=="0002", MODE:="0666"
   ```
   And then restart udev
7) ```./util``` Or ```sudo ./util``` (if you have not set up udev)

### Option 2: Build with docker

In case you have trouble with dependencies.

1) ```docker build -t utilbuilder .```
2) ```docker run -it --rm  -e DISPLAY=$DISPLAY -v $HOME/.Xauthority:/root/.Xauthority --net=host -v `pwd`/../../:/xwhatsit -v /dev:/dev --privileged -w /xwhatsit/util/util utilbuilder /bin/bash```
   a) ```qmake util.pro```
   b) ```make clean && make -j```
   c) ```exit```
3) ```docker run -it --rm  -e DISPLAY=$DISPLAY -v $HOME/.Xauthority:/root/.Xauthority --net=host -v `pwd`/../../:/xwhatsit -v /dev:/dev --privileged -w /xwhatsit/util/util utilbuilder ./util```

(You can also try running directly on the local machine, if you have Qt and hidapi libraries installed)

## Building on Linux for Windows

Please see ../windows_crosscompile/README.md

## Building on Windows for Windows

This has not been tested yet. You may need to tweak util.pro for this to work. If you get it working please update this section.

## Building on MacOS for MacOS

1) Install Homebrew, see http://brew.sh
2) ```brew install qt5```
3) ```brew install hidapi```
4) Probably Optional (but haven't tried without yet): ```brew install qt-creator```
5) Change directory to where util.pro lives.
6) ```/usr/local/opt/qt5/bin/qmake util.pro```
7) ```make```
8) Run it: ```./util.app/Contents/MacOS/util```
9) Create .dmg package: ```/usr/local/opt/qt5/bin/macdeployqt util.app -dmg util```

# License

All of the files in this folder are licensed under the GNU GPLv2 (or at your option any later version) license, except when otherwise specified.
