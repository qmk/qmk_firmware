#Planck Advanced (but not too advanced) `cygwin` Users Guide
If you are a user of the [cygwin environment](https://cygwin.com) in Windows and want the freedom to use the latest tools available, then this is the guide for you. If compiling your own copy of the latest and greatest Gnu C Compiler makes you super happy, then this is the guide for you. If the command line make you smile, then this is the guide for you.

This guide was written step by step as I went through the process on a `Windows 10` `x86_64` and a `Windows 7` `amd k10` based system.  This should be generally applicable to to any `Windows` environment with `cygwin`.

#####Do not skip steps. Do not move past a step until the previous step finishes successfully.

Based on [avr-libc installation guide](http://www.nongnu.org/avr-libc/user-manual/install_tools.html)

##Get the Required Packages
Download the `cygwin` setup ([x86_64](https://cygwin.com/setup-x86_64.exe)) and install the default system plus the following if they are not already selected:
- devel/git
- devel/gcc-core
- devel/gcc-g++
- devel/flex
- devel/bison
- devel/make
- devel/texinfo
- devel/gettext-devel
- devel/automake
- devel/autoconfig
- devel/libtool
- text/gettext
- libs/libgcc1
- interpreters/m4
- web/wget
- archive/unzip

The following sources will be required:
- [gmp](https://gmplib.org/) (6.1.0)
- [mpfr](http://www.mpfr.org/) (3.1.4)
- [mpc](http://www.multiprecision.org/) (1.0.3) 
- [binutils](https://www.sourceware.org/binutils/) (2.26)
- [gcc](https://gcc.gnu.org/) (5.3.0)
- [avr-libc](http://www.nongnu.org/avr-libc/) (2.0.0)

The `dfu-programmer` will be required to flash the new firmware 
- [dfu-programmer](https://dfu-programmer.github.io/) (0.7.2)

The set of commands below will create a directory (`~/local/avr`) for the sources you compile to be installed on the machine and a directory (`~/src`) for these source files to be stored. The commands then download the sources of the needed packages and unpack them. Note: the expand commands are different depending on if the packages are offered as a `bz2` or `gz` archive
```
$ mkdir ~/local
$ mkdir ~/local/avr
$ mkdir ~/src
$ cd ~/src
$ wget https://gmplib.org/download/gmp/gmp-6.1.0.tar.bz2
$ wget http://www.mpfr.org/mpfr-3.1.4/mpfr-3.1.4.tar.bz2
$ wget ftp://ftp.gnu.org/gnu/mpc/mpc-1.0.3.tar.gz
$ wget http://ftp.gnu.org/gnu/binutils/binutils-2.26.tar.gz
$ wget http://mirror0.babylon.network/gcc/releases/gcc-5.3.0/gcc-5.3.0.tar.gz
$ wget http://download.savannah.gnu.org/releases/avr-libc/avr-libc-2.0.0.tar.bz2
$ tar -xjf gmp-6.1.0.tar.bz2
$ tar -xjf mpfr-3.1.4.tar.bz2
$ tar -zxf mpc-1.0.3.tar.gz
$ tar -zxf binutils-2.26.tar.gz
$ tar -zxf gcc-5.3.0.tar.gz
$ tar -xjf avr-libc-2.0.0.tar.bz2 
```

##Setup the Build Environment
These commands will set up the install directory and the `PATH` variable, which will allow you to access your installed packages.  Note: if you close the `cygwin` terminal window, you will need to rerun these commands, they are not permanent.
```
$ PREFIX=$HOME/local/avr
$ export PREFIX
$ PATH=/usr/local/bin:/usr/local/lib:/usr/local/include:/bin:/lib:/cygdrive/c/WINDOWS/system32:/cygdrive/c/WINDOWS
$ PATH=$PATH:$PREFIX/bin:$PREFIX/lib
$ export PATH
```

##The `gcc` Required Math Library Packages
The following packages are required to be complied and installed in order to compile `gcc`.  They are not sufficiently available through the `cygwin` package system, so we have to make them ourselves.  They must be complied in this order because each one depends on the previous. Verfiy that for each package, `make check` returns all passing and no fails.

###Build and Install `gmp`
```
$ cd ~/src/gmp-6.1.0
$ ./configure --enable-static --disable-shared
$ make
$ make check
$ make install
```

###Build and Install `mpfr`
```
$ cd ~/src/mpfr-3.1.4
$ ./configure --with-gmp-build=../gmp-6.1.0 --enable-static --disable-shared
$ make
$ make check
$ make install
```

###Build and Install `mpc`
```
$ cd ~/src/mpc-1.0.3
$ ./configure --with-gmp=/usr/local --with-mpfr=/usr/local --enable-static --disable-shared
$ make
$ make check
$ make install
```

##OPTIONAL Part
You can build and install a brand new `gcc` or you can use the one supplied by `cygwin`.  This will take about 4-5 hours to compile (It is a "native build", so it does the entire build **3 times**. This takes a long while).

###Build and Install `gcc` for Your Machine  
```
$ cd ~/src/gcc-5.3.0
$ mkdir obj-local
$ cd obj-local
$ ../configure --enable-languages=c,c++ --with-gmp=/usr/local --with-mpfr=/usr/local --with-mpc=/usr/local --enable-static --disable-shared
$ make
$ make install
```
##End OPTIONAL Part

###Build and Install `binutils` for Your Machine
```
$ cd ~/src/binutils-2.26
$ mkdir obj-local
$ cd obj-local
$ ../configure
$ make
$ make install
```

##Buliding `binutils`, `gcc`, and `avr-libc` for the AVR system
Now we can make the critical stuff for compiling our firmware: `binutils`, `gcc`, and `avr-libc` for the AVR architecture.  These allow us to build and manipulate the firmware for the keyboard.

###Build `binutils` for AVR
If you plan to build and install `avr-gdb` also, use the `gdb` install at the end of this guide as it also builds the `binutils`
```
$ cd ~/src/binutils-2.26
$ mkdir obj-avr
$ cd obj-avr
$ ../configure --prefix=$PREFIX --target=avr --disable-nls
$ make
$ make install
```

###Build `gcc` for AVR
```
$ cd ~/src/gcc-5.3.0
$ mkdir obj-avr
$ cd obj-avr
$ ../configure --prefix=$PREFIX --target=avr --enable-languages=c,c++ --with-gmp=/usr/local --with-mpfr=/usr/local --with-mpc=/usr/local --enable-static --disable-shared --disable-nls --disable-libssp --with-dwarf2
$ make
$ make install
```

###Build `avr-libc` for AVR
For building the `avr-libc`, we have to specify the host build system.  In my case it is `x86_64-unknown-cygwin`. You can look for build system type in the `gcc` configure notes for the proper `--build` specification to pass when you configure `avr-libc`.
```
$ cd ~/src/avr-libc-2.0.0
$ ./configure --prefix=$PREFIX --build=x86_64-unknown-cygwin --host=avr
$ make
$ make install
```

##Building 'dfu-programmer' for flashing the firmware via USB and installing the drivers
We can either build our own, or use the precomplied binaries.  The precompiled binaries don't play well with `cygwin` so it is better to build them ourselves.  The procedure for the precompiled binaries is included at the end of this guide.

### Build and Install the `libusb`
The `dfu-programmer` requires `libusb` so that it can interact with the USB system. These repos must be bootstrapped in order to create an appropriate `./configure` and `Makefile` for your system.
```
$ cd ~/src
$ git clone https://github.com/libusb/libusb.git
$ cd libusb
$ ./bootstrap.sh
$ ./configure
$ make
$ make install
```

### Build and Install the `dfu-programmer`
```
$ cd ~/src
$ git clone https://github.com/dfu-programmer/dfu-programmer.git
$ cd dfu-programmer
$ ./bootstrap.sh
$ ./configure
$ make
$ make install
```

Verify the installation with:
```
$ which dfu-programmer
/usr/local/bin/dfu-programmer

$ dfu-programmer
dfu-programmer 0.7.2
https://github.com/dfu-programmer/dfu-programmer
Type 'dfu-programmer --help'    for a list of commands
     'dfu-programmer --targets' to list supported target devices
```
If you are not getting the above result, you will not be able to flash the firmware! 

###Install the USB drivers
The drivers are included in the windows binary version of [`dfu-programmer` 0.7.2](http://iweb.dl.sourceforge.net/project/dfu-programmer/dfu-programmer/0.7.2/dfu-programmer-win-0.7.2.zip).
```
$ cd ~/src
$ wget http://iweb.dl.sourceforge.net/project/dfu-programmer/dfu-programmer/0.7.2/dfu-programmer-win-0.7.2.zip
$ unzip dfu-programmer-win-0.7.2.zip -d dfu-programmer-win-0.7.2
```

or

The official drivers are found in [Atmel's `FLIP` installer](http://www.atmel.com/images/Flip%20Installer%20-%203.4.7.112.exe). Download and then install `FLIP`. Upon installation, the drivers will be found in `C:\Program Files (x86)\Atmel\Flip 3.4.7\usb`.

Then, from an **administrator-privileged** `Windows` terminal, run the following command (adjust the path for username, etc. as necessary) and accept the prompt that pops up:
```
C:\> pnputil -i -a C:\cygwin64\home\Kevin\src\dfu-programmer-win-0.7.2\dfu-prog-usb-1.2.2\atmel_usb_dfu.inf
or
C:\> pnputil -i -a "C:\Program Files (x86)\Atmel\Flip 3.4.7\usb\atmel_usb_dfu.inf"
```

This should be the result:
```
Microsoft PnP Utility

Processing inf :            atmel_usb_dfu.inf
Successfully installed the driver on a device on the system.
Driver package added successfully.
Published name :            oem104.inf


Total attempted:              1
Number successfully imported: 1
```

Alternatively, the `Windows` driver can be installed when prompted by `Windows` when the keyboard is attached. Do not let `Windows` search for a driver; specify the path to search for a driver and point it to the `atmel_usb_dfu.inf` file.

##Building and Flashing the Planck firmware!
If you did everything else right. This part should be a snap! Grab the latest sources from `github`, make the Plank firmware, then flash it.

###Build Planck and Load the Firmware
```
$ cd ~/src
$ git clone https://github.com/qmk/qmk_firmware.git
$ cd qmk_firmware/keyboards/planck
$ make
```

Make sure there are no errors.  You should end up with this or something similar:
```
Creating load file for Flash: planck.hex
avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature planck.elf planck.hex

Creating load file for EEPROM: planck.eep
avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" \
--change-section-lma .eeprom=0 --no-change-warnings -O ihex planck.elf planck.eep || exit 0

Creating Extended Listing: planck.lss
avr-objdump -h -S -z planck.elf > planck.lss

Creating Symbol Table: planck.sym
avr-nm -n planck.elf > planck.sym

Size after:
   text    data     bss     dec     hex filename
  18602      82     155   18839    4997 planck.elf

-------- end --------
```

If you do not get the above, you **did not** build the firmware, and you will have nothing to flash.  If you have the fresh clone from `github`, it was probably something gone wrong in this install process, go check and see what didn't work and threw errors or what steps you might have missed.

But if everything went OK, you are ready to flash! Press the reset button on the bottom of the Planck, wait two seconds, then:
```
$ make dfu
```
.
.
.
profit!!!





##extra bits...

###Installing Precompiled `dfu-programmer` Binaries (not recommended for `cygwin`)
To install the `dfu-programmer` from the binaries, we must get if from [the `dfu-programmer` website](https://dfu-programmer.github.io/) ([0.7.2](http://iweb.dl.sourceforge.net/project/dfu-programmer/dfu-programmer/0.7.2/dfu-programmer-win-0.7.2.zip)).

Copy this file into your `cygwin` home\src directory.  (For me, it is `C:\cygwin64\home\Kevin\src`), extract the files, move `dfu-programmer.exe` to `~/local/avr/bin`. Most obnoxiously, the `libusb0_x86.dll` and `libusb0.sys` need to be moved from  `./dfu-prog-usb-1.2.2/x86/` to a directory in the `Windows` `PATH` and the `cygwin` `PATH`. This is because the `dfu-programmer` binary is `mingw` based, not `cygwin` based, so the `dlls` do not cooperate. I achieved acceptable pathing by moving the files to  `C:\cygwin64\home\Kevin\local\avr\bin` Then, in a `WINDOWS` command prompt running (Adjusting your path for username, etc. as needed):
```
C:\> set PATH=%PATH%;C:\cygwin64\home\Kevin\local\avr\bin
```

Then, rename `libusb0_x86.dll` to `libusb0.dll`.
 
You can tell that you were successful by trying to execute 'dfu-programmer' from the 'cygwin' prompt:
```
$ which dfu-programmer
/home/Kevin/local/avr/bin/dfu-programmer

$ dfu-programmer
dfu-programmer 0.7.2
https://github.com/dfu-programmer/dfu-programmer
Type 'dfu-programmer --help'    for a list of commands
     'dfu-programmer --targets' to list supported target devices
```

If you are not getting the above result, you will not be able to flash the firmware! 
- Try making sure your `PATH` variables are set correctly for both `Windows` and `cygwin`. 
- Make sure the `dll` is named correctly.
- Do not extract it with `cygwin`'s `unzip` as it does not set the executable permission. If you did it anyway, do `chmod +x dfu-programmer.exe`.
- Still have problems? Try building it instead.


##Debugging Tools

These tools are for debugging your firmware, etc. before flashing. Theoretically, it can save your memory from wearing out. However, these tool do not work 100% for the Planck firmware.

### `gdb` for AVR
`gdb` has a simulator for AVR but it does not support all instructions (like WDT), so it immediately crashes when running the Planck firmware (because `lufa.c` disables the WDT in the first few lines of execution). But it can still be useful in debugging example code and test cases, if you know how to use it.

```
$ cd ~/src
$ git clone git://sourceware.org/git/binutils-gdb.git
$ cd binutils-gdb
$ mkdir obj-avr
$ cd obj-avr
$ ../configure --prefix=$PREFIX --target=avr --build=x86_64-unknown-cygwin --with-gmp=/usr/local --with-mpfr=/usr/local --with-mpc=/usr/local --disable-nls --enable-static
$ make
$ make install
```

### `simulavr`
`simulavr` is an AVR simulator.  It runs the complied AVR elfs. `simulavr` does not support the `atmega32u4` device... it does `atmega32` but that is not good enough for the firmware (no PORTE and other things), so you cannot run the Planck firmware. I use it to simulate ideas I have for features in separate test projects.

This one is a major pain in the butt because it has a lot of dependencies and it is buggy.  I will do my best to explain it but... it was hard to figure out. A few things need to be changed in the 'Makefile' to make it work in `cygwin`.


```
$ cd ~/src
$ git clone https://github.com/Traumflug/simulavr.git
$ cd simulavr
$ ./bootstrap
$ ./configure --prefix=$PREFIX --enable-static --disable-tcl --disable-doxygen-doc
```
 Edit `src/Makefile.am` now so that `-no-undefined` is included (I did this by removing the SYS_MINGW conditional surrounding `libsim_la_LDFLAGS += -no-undefined` and  `libsimulavr_la_LDFLAGS += -no-undefined \ libsimulavr_la_LIBADD += $(TCL_LIB)`. Also, `$(EXEEXT)` is added after `kbdgentables` in two places.

```
$ make
$ make install
```


TODO:
- git repos for all sources
- command line magic for cygwin setup
- better options for `dfu-drivers`
