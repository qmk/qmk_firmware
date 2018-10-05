# ARM Debugging usign Eclipse

This page describes how to setup debugging for ARM MCUs using an SWD adapter and open-source/free tools. In this guide we will install GNU MCU Eclipse IDE for C/C++ Developers and OpenOCD together with all the necessary dependencies.

This guide is catered towards advance users and assumes you can compile an ARM compatible keyboard on your machine using the MAKE flow.

## Installing the software

The main objective here is to get the MCU Eclipse IDE correcly installed on our machine. The necesarry instructions are derived from [this](https://gnu-mcu-eclipse.github.io/install/) install guide.

### The xPack Manager

This tool is a software package manager and it is used to help us get the necesarry depencencies.

XPM runs using Node.js so grab that form [here](https://nodejs.org/en/). After installation, open a terminal and type `npm -v`. A reply with the version number means that the instalation was successful.

XPM instalation instructions can be found [here](https://www.npmjs.com/package/xpm) and are OS specific. Entering `xpm --version` to your terminal should return the software version.

### The ARM Toolchain

Using XPM it is very easy to install the ARM toolchain. Enter the command `xpm install --global @gnu-mcu-eclipse/arm-none-eabi-gcc`.

### Windows build tools

If you are using windows you need to install this!

`xpm install --global @gnu-mcu-eclipse/windows-build-tools`

### Programer/Debugger Drivers

Now its the time to install your programer's drivers. This tutorial was made using an ST-Link v2 which you can get from almost anywhere.
If you have an ST-Link the drivers can be found [here](https://www.st.com/en/development-tools/stsw-link009.html) otherwise consult the manufuturer of your tool.

### OpenOCD

This dependency allows SWD access from GDB and it is essential for debugging. Run `xpm install --global @gnu-mcu-eclipse/openocd`.

### Java

Java is needed by Eclipse so please download it from [here](https://www.oracle.com/technetwork/java/javase/downloads/index.html).

### GNU MCU Eclipse IDE

Now its finally time to install the IDE. Use the Release page [here](https://github.com/gnu-mcu-eclipse/org.eclipse.epp.packages/releases/) to get the latest version.

## Configuring Eclipse

Open up the Eclipse IDE we just downloaded. To import our QMK directory select File -> Import -> C/C++ -> Existing code as Makefile Project. Select next and use Browse to select your QMK folder. In the tool-chain list select ARM Cross GCC and select Finish.

Now you can see the QMK folder on the left hand side. Right click it and select Properties. On the left hand side, expand MCU and select ARM Toolchain Paths. Press xPack and OK. Repeat for OpenOCD Path  and if you are on windows for Build Tool Path. Select Apply and Close.

Now its time to install the necessary MCU packages. Go to Packs perspective by selecting Window -> Open Perspective -> Others -> Packs. Now select the yellow refresh symbol next to the Packs tab. This will take a long time as it is requesting the MCU definitions from various places. If some of the links fail you can probably select Ignore.

When this finishes you must find the MCU which we will be building/debugging for. In this example I will be using the STM32F3 series MCUs. On the left, select STMicroelectonics -> STM32F3 Series. On the middle window we can see the pack. Right click and select Install. Once that is done we can go back to the default perspective, Window -> Open Perspective -> Others -> C/C++.

We need to let eclipse know the device we intent to build QMK on. Right click on the QMK folder -> Properties -> C/C++ Build -> Settings. Select the Devices tab and under devices select the appropriate variant of your MCU. For my example it is STM32F303CC

While we are here let's setup the build command as well. Select C/C++ Build and then the Behavior tab. On the build command, replace `all` with your necessary make command. For example for a rev6 Planck with the default keymap this would be `planck/rev6:default`. Select Apply and Close.

## Building

If you have setup everything correctly pressing the hammer button should build the firmware for you and a .bin file should appear.

## Debugging

### Connecting the Debugger

ARM MCUs use the Single Wire Debug (SWD) protocol which comprises of the clock (SWCLK) signal and the data (SWDIO) signal. Connecting this two wires and ground should be enough to allow full manipulation of the MCU. Here we assume that the keyboard will be powered though USB. The RESET signal is not necessary as we can manually assert it using the reset button. For a more advance setup, the SWO signal can be used which pipes printf and scanf asynchronously to the host but for our setup we will ignore it.

NOTE: Make sure the SWCLK and SWDIO pins are not used in the matrix of your keyboard. If they are you can temporarily switch them for some other pins.

### Configuring the Debugger

Right click on your QMK folder, select Debug As -> Debug Configuration. Here double click on GDB OpenOCD Debugging. Select the debugger tab and enter the configuration necessary for your MCU. This might take some fiddling and googleing to find out. The default script for the STM32F3 is called stm32f3discovery.cfg. To let OpenOCD know, in the Config options enter `-f board/stm32f3discovery.cfg`.

NOTE: In my case this configuration script requires editing to disable the reset assertion. The locations of the scripts can be found in the actual executable field usually under the path `openocd/version/.content/scripts/board`. Here I edited `reset_config srst_only` to `reset_config none`.

Select Apply and Close.

### Running the Debugger.

Reset your keyboard.

Press the bug icon and if all goes well you should soon find yourself in the debug perspective. Here the program counter will pause at the beginning of the main function and way for you to press Play. Most of the features of all debuggers work on ARM MCUs but for exact details google is your friend!


Happy debugging!