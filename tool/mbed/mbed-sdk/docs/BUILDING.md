# Mbed SDK build script environment
## Introduction
Mbed test framework allows users to test their mbed devices’ applications, build mbed SDK library, re-run tests, run mbed SDK regression, add new tests and get all this results automatically. Everything is done on your machine so you have a full control over compilation, and tests you run.

It's is using Python 2.7 programming language to drive all tests so make sure Python 2.7 is installed on your system and included in your system PATH. To compile mbed SDK and tests you will need one or more supported compilers installed on your system.

To follow this short introduction you should already:
* Know what mbed SDK is in general.
* Know how to install Python 2.7, ARM target cross compilers.
* You have C/C++ programming experience and at least willingness to learn a bit about Python. 

## Test automation
Currently our simple test framework allows users to run tests on their machines (hosts) in a fully automated manner. All you need to do is to prepare two configuration files.

## Test automation limitations
Note that for tests which require connected external peripherals, for example Ethernet, SD flash cards, external EEPROM tests, loops etc. you need to:

* Modify test source code to match components' pin names to actual mbed board pins where peripheral is connected or
* Wire your board the same way test defines it.

## Prerequisites
mbed test suite and build scripts are Python 2.7 applications and require Python 2.7 runtime environment and [setuptools](https://pythonhosted.org/an_example_pypi_project/setuptools.html) to install dependencies.

What we need:
* Installed [Python 2.7](https://www.python.org/download/releases/2.7) programming language.
* Installed [setuptools](https://pythonhosted.org/an_example_pypi_project/setuptools.html#installing-setuptools-and-easy-install) 
* Optionally you can install [pip](https://pip.pypa.io/en/latest/installing.html) which is the PyPA recommended tool for installing Python packages from command line.

mbed SDK in its repo root directory specifies ```setup.py``` file which holds information about all packages which are dependencies for it. Bear in mind only few simple steps are required to install all dependencies.

First, clone mbed SDK repo and go to mbed SDk repo's directory:
```
$ git clone https://github.com/mbedmicro/mbed.git
$ cd mbed
```

Second, invoke ```setup.py``` so ```setuptools``` can install mbed SDK's dependencies (external Python modules required by mbed SDK):
```
$ python setup.py install
```
or 
```
$ sudo python setup.py install
```
when your system requires administrator rights to install new Python packages.

## Prerequisites (manual Python package dependency installation)
**Please only read this chapter if you had problems installing mbed SDK dependencies to Python packages**.

Below you can find the list of mbed SDK dependencies to Python modules with instructions how to install them manually.

You can skip this part if you've already install [Python 2.7](https://www.python.org/download/releases/2.7) and [setuptools](https://pythonhosted.org/an_example_pypi_project/setuptools.html) and successfully [installed all dependencies](#prerequisites).

* Please make sure you've installed [pip](https://pip.pypa.io/en/latest/installing.html) or [easy_install](https://pythonhosted.org/setuptools/easy_install.html#installing-easy-install) 
Note: Easy Install is a python module (easy_install) bundled with [setuptools](https://pythonhosted.org/an_example_pypi_project/setuptools.html#installing-setuptools-and-easy-install)  that lets you automatically download, build, install, and manage Python packages.

* Installed [pySerial](https://pypi.python.org/pypi/pyserial) module for Python 2.7.
pySerial can be installed from PyPI, either manually downloading the files and installing as described below or using:
```
$ pip install pyserial
```
or:
```
easy_install -U pyserial
```
* Installed [prettytable](https://code.google.com/p/prettytable/wiki/Installation) module for Python 2.7.
prettytable can be installed from PyPI, either manually downloading the files and installing as described below or using:
```
$ pip install prettytable
```
* Installed [IntelHex](https://pypi.python.org/pypi/IntelHex) module.
IntelHex may be downloaded from https://launchpad.net/intelhex/+download or http://www.bialix.com/intelhex/.
Assuming Python is properly installed on your platform, installation should just require running the following command from the root directory of the archive:
```
sudo python setup.py install
```
This will install the intelhex package into your system’s site-packages directory.  After that is done, any other Python scripts or modules should be able to import the package using:
```
$ python
Python 2.7.8 (default, Jun 30 2014, 16:03:49) [MSC v.1500 32 bit (Intel)] on win32
Type "help", "copyright", "credits" or "license" for more information.
>>> from intelhex import IntelHex
>>>
```
* You can check if you have correctly installed the above modules (or you already have them) by starting Python and importing both modules.
```
$ python
Python 2.7.8 (default, Jun 30 2014, 16:03:49) [MSC v.1500 32 bit (Intel)] on win32
Type "help", "copyright", "credits" or "license" for more information.
>>> import serial
>>> import prettytable
>>> from intelhex import IntelHex
>>>
```
* Installed Git open source distributed version control system.
* Installed at least one of the supported by Mbed SDK workspace tools compilers: 

Compiler               | Mbed SDK Abbreviation | Example Version
-----------------------|-----------------------|-----------
Keil ARM Compiler      | ARM, uARM             | ARM C/C++ Compiler, 5.03 [Build 117]
GCC ARM                | GCC_ARM               | gcc version 4.8.3 20131129 (release)
GCC CodeSourcery       | GCC_CS                | gcc version 4.8.1 (Sourcery CodeBench Lite 2013.11-24)
GCC CodeRed            | GCC_CR                | gcc version 4.6.2 20121016 (release)
IAR Embedded Workbench | IAR                   | IAR ANSI C/C++ Compiler V6.70.1.5641/W32 for ARM

* Mbed board. You can find list of supported platforms [here](https://mbed.org/platforms/).

### Getting Mbed SDK sources with test suite
So you have already installed Python (with required modules) together with at least one supported compiler you will use with your mbed board. Great!

Now let's go further and try to get Mbed SDK with test suite together. So let's clone latest Mbed SDK source code and configure path to our compiler(s) in next few steps.

* Open console and run command below to clone Mbed SDK repository hosted on [Github](https://github.com/mbedmicro/mbed).
```
$ git clone https://github.com/mbedmicro/mbed.git
Cloning into 'mbed'...
remote: Counting objects: 37221, done.
remote: Compressing objects: 100% (3/3), done.
remote: Total 37221 (delta 0), reused 0 (delta 0), pack-reused 37218
Receiving objects: 100% (37221/37221), 20.38 MiB | 511.00 KiB/s, done.
Resolving deltas: 100% (24455/24455), done.
Checking connectivity... done.
Checking out files: 100% (3994/3994), done.
```
* Now you can go to mbed directory you've just cloned and you can see root directory structure of our Mbed SDK library sources. Just type following commands:
```
$ cd mbed
$ ls
LICENSE  MANIFEST.in  README.md  libraries  setup.py  travis  workspace_tools
```
Directory structure we are interested in:
```
  mbed/workspace_tools/         - test suite scripts, build scripts etc.
  mbed/library/tests/           - mbed SDK tests,
  mbed/library/tests/mbed/      - tests for mbed SDK and peripherals tests,
  mbed/library/tests/net/echo/  - tests for Ethernet interface,
  mbed/library/tests/rtos/mbed/ - tests for RTOS. 
```

### Workspace tools
Workspace tools are set of Python scripts used off-line by Mbed SDK team to:
* Compile and build mbed SDK,
* Compile and build libraries included in mbed SDK repo like e.g. ETH (Ethernet), USB, RTOS or CMSIS,
* Compile, build and run mbed SDK tests,
* Run test regression locally and in CI server,
* Get library, target, test configuration (paths, parameters, names etc.).

### Configure workspace tools to work with your compilers
Before we can run our first test we need to configure our test environment a little!
Now we need to tell workspace tools where our compilers are.

* Please to go ```mbed/workspace_tools/``` directory and create empty file called ```private_settings.py```.
```
$ touch private_settings.py
```
* Populate this file the Python code below: 
```python
from os.path import join
 
# ARMCC
ARM_PATH = "C:/Work/toolchains/ARMCompiler_5.03_117_Windows"
ARM_BIN = join(ARM_PATH, "bin")
ARM_INC = join(ARM_PATH, "include")
ARM_LIB = join(ARM_PATH, "lib")
 
ARM_CPPLIB = join(ARM_LIB, "cpplib")
MY_ARM_CLIB = join(ARM_PATH, "lib", "microlib")
 
# GCC ARM
GCC_ARM_PATH = "C:/Work/toolchains/gcc_arm_4_8/4_8_2013q4/bin"
 
# GCC CodeSourcery
GCC_CS_PATH = "C:/Work/toolchains/Sourcery_CodeBench_Lite_for_ARM_EABI/bin"
 
# GCC CodeRed
GCC_CR_PATH = "C:/Work/toolchains/LPCXpresso_6.1.4_194/lpcxpresso/tools/bin"
 
# IAR
IAR_PATH = "C:/Work/toolchains/iar_6_5/arm"
 
SERVER_ADDRESS = "127.0.0.1"
LOCALHOST = "127.0.0.1"
 
# This is moved to separate JSON configuration file used by singletest.py
MUTs = {
}
```

Note: You need to provide the absolute path to your compiler(s) installed on your host machine. Replace corresponding variable values with paths to compilers installed in your system:
* ```ARM_PATH``` for armcc compiler.
* ```GCC_ARM_PATH``` for GCC ARM compiler.
* ```GCC_CS_PATH``` for GCC CodeSourcery compiler.
* ```GCC_CR_PATH``` for GCC CodeRed compiler.
* ```IAR_PATH``` for IAR compiler. 

If for example you do not use ```IAR``` compiler you do not have to modify anything. Workspace tools will use ```IAR_PATH`` variable only if you explicit ask for it from command line. So do not worry and replace only paths for your installed compilers.

Note: Because this is a Python script and ```ARM_PATH```, ```GCC_ARM_PATH```, ```GCC_CS_PATH```, ```GCC_CR_PATH```, ```IAR_PATH``` are Python string variables please use double backlash or single slash as path's directories delimiter to avoid incorrect path format. For example:
```python
ARM_PATH = "C:/Work/toolchains/ARMCompiler_5.03_117_Windows"
GCC_ARM_PATH = "C:/Work/toolchains/gcc_arm_4_8/4_8_2013q4/bin"
GCC_CS_PATH = "C:/Work/toolchains/Sourcery_CodeBench_Lite_for_ARM_EABI/bin"
GCC_CR_PATH = "C:/Work/toolchains/LPCXpresso_6.1.4_194/lpcxpresso/tools/bin"
IAR_PATH = "C:/Work/toolchains/iar_6_5/arm"
```

Note: Settings in ```private_settings.py``` will overwrite variables with default values in ```mbed/workspace_tools/settings.py``` file.

## Build Mbed SDK library from sources
Let's build mbed SDK library off-line from sources using your compiler. We've already cloned mbed SDK sources, we've also installed compilers and added their paths to ```private_settings.py```.
We now should be ready to use workspace tools script ```build.py``` to compile and build mbed SDK from sources.

We are still using console. You should be already in ```mbed/workspace_tools/``` directory if not go to ```mbed/workspace_tools/``` and type below command:
```
$ python build.py -m LPC1768 -t ARM
```
or if you want to take advantage from multi-threaded compilation please use option ```-j X``` where ```X``` is number of cores you want to use to compile mbed SDK. See below:
```
$ python build.py -m LPC1768 -t ARM -j 4
Building library CMSIS (LPC1768, ARM)
Copy: core_ca9.h
Copy: core_caFunc.h
...
Compile: us_ticker_api.c
Compile: wait_api.c
Library: mbed.ar
Creating archive 'C:\temp\x\mbed\build\mbed\TARGET_LPC1768\TOOLCHAIN_ARM_STD\mbed.ar'
Copy: board.o
Copy: retarget.o

Completed in: (42.58)s

Build successes:
  * ARM::LPC1768
```
Above command will build mbed SDK for [LPC1768](http://developer.mbed.org/platforms/mbed-LPC1768/) platform using ARM compiler.

Let's have a look at directory structure under ```mbed/build/```. We can see for ```LPC1768``` new directory ```TARGET_LPC1768``` was created. This directory contains all build primitives.
Directory ```mbed/TARGET_LPC1768/TOOLCHAIN_ARM_STD/``` conteins mbed SDK library ```mbed.ar```. This directory structure also stores all needed headers which you should use with ```mbed.ar``` when building your own software.
```
$ tree ./mbed/build/
Folder PATH listing
Volume serial number is 006C006F 6243:3EA9
./MBED/BUILD
+---mbed
    +---.temp
    ¦   +---TARGET_LPC1768
    ¦       +---TOOLCHAIN_ARM_STD
    ¦           +---TARGET_NXP
    ¦               +---TARGET_LPC176X
    ¦                   +---TOOLCHAIN_ARM_STD
    +---TARGET_LPC1768
        +---TARGET_NXP
        ¦   +---TARGET_LPC176X
        ¦       +---TARGET_MBED_LPC1768
        +---TOOLCHAIN_ARM_STD
```

Note: Why ```LCP1768```? For this example we are using ```LPC1768``` because this platform supports all compilers so you are sure you only need to specify proper compiler.

If you are not using ARM Compiler replace ```ARM``` with your compiler nickname: ```GCC_ARM```, ```GCC_CS```, ```GCC_CR``` or ```IAR```. For example if you are using IAR type command:
```
$ python build.py -m LPC1768 -t IAR
```

Note: Workspace tools track changes in source code. So if for example mbed SDK or test source code changes ```build.py``` script will recompile project with all dependencies. If there are no changes in code consecutive mbed SDK re-builds using build.py will not rebuild project if this is not necessary. Try to run last command once again, we can see script ```build.py``` will not recompile project (there are no changes): 
```
$ python build.py -m LPC1768 -t ARM
Building library CMSIS (LPC1768, ARM)
Building library MBED (LPC1768, ARM)

Completed in: (0.15)s

Build successes:
  * ARM::LPC1768
```

### build.py script

Build script located in mbed/workspace_tools/ is our core script solution to drive compilation, linking and building process for:

* mbed SDK (with libs like Ethernet, RTOS, USB, USB host).
* Tests which also can be linked with libraries like RTOS or Ethernet.

Note: Test suite also uses the same build script, inheriting the same properties like auto dependency tracking and project rebuild in case of source code changes.

Build.py script is a powerful tool to build mbed SDK for all available platforms using all supported by mbed cross-compilers. Script is using our workspace tools build API to create desired platform-compiler builds. Use script option ```--h``` (help) to check all script parameters.
```
$ python build.py --help
```

* The command line parameter ```-m``` specifies the MCUs/platforms for which you want to build the mbed SDK. More than one MCU(s)/platform(s) may be specified with this parameter using comma as delimiter.
Example for one platform build:
```
$ python build.py -m LPC1768 -t ARM
```
or for many platforms:
```
$ python build.py -m LPC1768,NUCLEO_L152RE -t ARM
```

* Parameter ```-t``` defined which toolchain should be used for mbed SDK build. You can build Mbed SDK for multiple toolchains using one command. 
Below example (note there is no space after commas) will compile mbed SDK for Freescale Freedom KL25Z platform using ARM and GCC_ARM compilers:
```
$ python build.py -m KL25Z -t ARM,GCC_ARM
```

* You can combine this technique to compile multiple targets with multiple compilers.
Below example will compile mbed SDK for Freescale's KL25Z and KL46Z platforms using ARM and GCC_ARM compilers:
```
$ python build.py -m KL25Z,KL46Z -t ARM,GCC_ARM
```

* Building libraries included in mbed SDK's source code. Parameters ```-r```, ```-e```, ```-u```, ```-U```, ```-d```, ```-b``` will add ```RTOS```, ```Ethernet```, ```USB```, ```USB Host```, ```DSP```, ```U-Blox``` libraries respectively. 
Below example will build Mbed SDK library for for NXP LPC1768 platform together with RTOS (```-r``` switch) and Ethernet (```-e``` switch) libraries.
```
$ python build.py -m LPC1768 -t ARM -r -e
Building library CMSIS (LPC1768, ARM)
Building library MBED (LPC1768, ARM)
Building library RTX (LPC1768, ARM)
Building library RTOS (LPC1768, ARM)
Building library ETH (LPC1768, ARM)

Completed in: (0.48)s

Build successes:
  * ARM::LPC1768
```

* If you’re unsure which platforms and toolchains are supported please use switch ```-S``` to print simple matrix of platform to compiler dependencies.
```
$ python python build.py -S
+-------------------------+-----------+-----------+-----------+-----------+-----------+-----------+------------+---------------+
| Platform                |    ARM    |    uARM   |  GCC_ARM  |    IAR    |   GCC_CR  |   GCC_CS  | GCC_CW_EWL | GCC_CW_NEWLIB |
+-------------------------+-----------+-----------+-----------+-----------+-----------+-----------+------------+---------------+
| APPNEARME_MICRONFCBOARD | Supported |  Default  | Supported |     -     |     -     |     -     |     -      |       -       |
| ARCH_BLE                |  Default  |     -     | Supported | Supported |     -     |     -     |     -      |       -       |
| ARCH_GPRS               | Supported |  Default  | Supported | Supported | Supported |     -     |     -      |       -       |
...
| UBLOX_C029              | Supported |  Default  | Supported | Supported |     -     |     -     |     -      |       -       |
| WALLBOT_BLE             |  Default  |     -     | Supported | Supported |     -     |     -     |     -      |       -       |
| XADOW_M0                | Supported |  Default  | Supported | Supported | Supported |     -     |     -      |       -       |
+-------------------------+-----------+-----------+-----------+-----------+-----------+-----------+------------+---------------+
*Default - default on-line compiler
*Supported - supported off-line compiler

Total platforms: 90
Total permutations: 297
```

Above list can be overwhelming so please do not hesitate to use switch ```-f``` to filter ```Platform``` column.
```
$ python build.py -S -f ^K
+--------------+-----------+---------+-----------+-----------+--------+--------+------------+---------------+
| Platform     |    ARM    |   uARM  |  GCC_ARM  |    IAR    | GCC_CR | GCC_CS | GCC_CW_EWL | GCC_CW_NEWLIB |
+--------------+-----------+---------+-----------+-----------+--------+--------+------------+---------------+
| K20D50M      |  Default  |    -    | Supported | Supported |   -    |   -    |     -      |       -       |
| K22F         |  Default  |    -    | Supported | Supported |   -    |   -    |     -      |       -       |
| K64F         |  Default  |    -    | Supported | Supported |   -    |   -    |     -      |       -       |
| KL05Z        | Supported | Default | Supported | Supported |   -    |   -    |     -      |       -       |
| KL25Z        |  Default  |    -    | Supported | Supported |   -    |   -    | Supported  |   Supported   |
| KL43Z        |  Default  |    -    | Supported |     -     |   -    |   -    |     -      |       -       |
| KL46Z        |  Default  |    -    | Supported | Supported |   -    |   -    |     -      |       -       |
| NRF51_DK     |  Default  |    -    | Supported | Supported |   -    |   -    |     -      |       -       |
| NRF51_DK_OTA |  Default  |    -    | Supported |     -     |   -    |   -    |     -      |       -       |
+--------------+-----------+---------+-----------+-----------+--------+--------+------------+---------------+
*Default - default on-line compiler
*Supported - supported off-line compiler

Total platforms: 9
Total permutations: 28
```
or just give platform name:
```
$ python build.py -S -f LPC1768
+----------+---------+-----------+-----------+-----------+-----------+-----------+------------+---------------+
| Platform |   ARM   |    uARM   |  GCC_ARM  |    IAR    |   GCC_CR  |   GCC_CS  | GCC_CW_EWL | GCC_CW_NEWLIB |
+----------+---------+-----------+-----------+-----------+-----------+-----------+------------+---------------+
| LPC1768  | Default | Supported | Supported | Supported | Supported | Supported |     -      |       -       |
+----------+---------+-----------+-----------+-----------+-----------+-----------+------------+---------------+
*Default - default on-line compiler
*Supported - supported off-line compiler

Total platforms: 1
Total permutations: 6
```

* You can be more verbose ```-v``` especially if you want to see each compilation / linking command build.py is executing:
```
$ python build.py -t GCC_ARM -m LPC1768 -j 8 -v
Building library CMSIS (LPC1768, GCC_ARM)
Copy: LPC1768.ld
Compile: startup_LPC17xx.s
[DEBUG] Command: C:/Work/toolchains/gcc_arm_4_8/4_8_2013q4/bin\arm-none-eabi-gcc 
-x assembler-with-cpp -c -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers 
-fmessage-length=0 -fno-exceptions -fno-builtin -ffunction-sections -fdata-sections -MMD 
-fno-delete-null-pointer-checks -fomit-frame-pointer -mcpu=cortex-m3 -mthumb -O2 
-DTARGET_LPC1768 -DTARGET_M3 -DTARGET_CORTEX_M -DTARGET_NXP -DTARGET_LPC176X 
-DTARGET_MBED_LPC1768 -DTOOLCHAIN_GCC_ARM -DTOOLCHAIN_GCC -D__CORTEX_M3 -DARM_MATH_CM3 
-DMBED_BUILD_TIMESTAMP=1424903604.77 -D__MBED__=1 -IC:\Work\mbed\libraries\mbed\targets\cmsis 
-IC:\Work\mbed\libraries\mbed\targets\cmsis\TARGET_NXP 
-IC:\Work\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC176X -IC:\Work\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC176X\TOOLCHAIN_GCC_ARM 
-o C:\Work\mbed\build\mbed\.temp\TARGET_LPC1768\TOOLCHAIN_GCC_ARM\TARGET_NXP\TARGET_LPC176X\TOOLCHAIN_GCC_ARM\startup_LPC17xx.o 
C:\Work\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC176X\TOOLCHAIN_GCC_ARM\startup_LPC17xx.s
[DEBUG] Return: 0
...
```

## CppUCheck analysis
[Cppcheck](http://cppcheck.sourceforge.net/) is a static analysis tool for C/C++ code. Unlike C/C++ compilers and many other analysis tools it does not detect syntax errors in the code. Cppcheck primarily detects the types of bugs that the compilers normally do not detect. The goal is to detect only real errors in the code (i.e. have zero false positives).

Prerequisites:
* Please install ```CppCheck``` on your system before you want to use it with build scripts.
* You should also add Cppcheck to your system path.

```build.py``` script supports switching between compilation and building and just static code analysis testing. You can use switch ```--cppcheck``` to perform CppCheck static code analysis. 

* When you are using --cppcheck switch all macros, toolchain dependencies etc. are preserved so you are sure you are checking exactly the same code you would compile for your application.

* Cppcheck analysis can take up to few minutes on slower machines.

* Usually you will use switches ```-t``` and ```-m``` to define toolchain and MCU (platform) respectively. You should do the same in case of CppCheck analysis. Please note that build script can also compile and build RTOS, Ethernet library etc. If you want to check those just use corresponding build script switches (e.g. ```-r```, ```-e```, ...).

Example:
```
$ python build.py -t uARM -m NUCLEO_F334R8 --cppcheck
```

# make.py script
```make.pt``` is a ```mbed/workspace_tools/``` script used to build tests (we call them sometimes 'programs') one by one manually. Script allows you to flash board with test and execute it. This is deprecated functionality and will not be described here. Instead please use ```singletest.py``` file to build mbed SDK, tests and run automation for test cases included in ```mbedmicro/mbed```.
Note: ```make.py``` script depends on existing already built mked SDK and library sources so you need to pre-build mbed SDK and for example RTOS library to link 'program' (test) with mebd SDK and RTOS library. To pre-build mbed SDK please use ```build.py``` script.

Just for sake of example please see few ways to use ```make.py``` together with Freedom K64F board.

* We need to build mbed SDK (in directory ```mbed/build/```:
```
$ python build.py -t GCC_ARM -m K64F -j 8
Building library CMSIS (K64F, GCC_ARM)
Building library MBED (K64F, GCC_ARM)

Completed in: (0.59)s

Build successes:
  * GCC_ARM::K64F
```
* We can print all 'programs' (test cases) ```make.py``` can build for us:
```
$ python make.py
.
[  0] MBED_A1: Basic
[  1] MBED_A2: Semihost file system
[  2] MBED_A3: C++ STL
[  3] MBED_A4: I2C TMP102
.
```
For example 'program' under index ```2``` is ```MBED_A3``` test case we can build and flash onto K64F board.
* Building test with ```make.py``` by specifying test case name with ```-n``` option:
```
$ python make.py -t GCC_ARM -m K64F -n MBED_A3
Building project STL (K64F, GCC_ARM)
Compile: main.cpp
[Warning] main.cpp@76: In function 'int main()': deprecated conversion from string constant to 'char*' [-Wwrite-strings]
.
.
.
[Warning] main.cpp@76: In function 'int main()': deprecated conversion from string constant to 'char*' [-Wwrite-strings]
Compile: test_env.cpp
Link: stl
Elf2Bin: stl
Image: C:\Work\mbed\build\test\K64F\GCC_ARM\MBED_A3\stl.bin
```
Because we previously have built mbed SDK we are now able to drive test case compilation and linking with mbed SDK and produce ```MBED_A3``` test case binary in build directory:
```
C:\Work\mbed\build\test\K64F\GCC_ARM\MBED_A3\stl.bin
```

For more help type ```$ python make.py --help``` in your command line.

# project.py script
```project.py``` script is used to export test cases ('programs') from test case portfolio to off-line IDE. This is a easy way to export test project to IDEs such as:
* codesourcery.
* coide.
* ds5_5.
* emblocks.
* gcc_arm.
* iar.
* kds.
* lpcxpresso.
* uvision.

You can export project using command line. All you need to do is to specify mbed platform name (option ```-m```), your IDE (option ```-i```) and project name you want to export (option ```-n``` or (option ```-p```).

In below example we export our project so we can work on it using GCC ARM cross-compiler. Building mechanism used to drive exported build will be ```Make```.
```
$ python project.py -m K64F -n MBED_A3 -i gcc_arm
Copy: test_env.h
Copy: AnalogIn.h
Copy: AnalogOut.h
.
.
.
Copy: K64FN1M0xxx12.ld
Copy: main.cpp

Successful exports:
  * K64F::gcc_arm       C:\Work\mbed\build\export\MBED_A3_gcc_arm_K64F.zip
```
You can see exporter placed compressed project export in ```zip``` file in ```mbed/build/export/``` directory.

Example export file ```MBED_A3_gcc_arm_K64F.zip``` structure:
```
MBED_A3
├───env
└───mbed
    ├───api
    ├───common
    ├───hal
    └───targets
        ├───cmsis
        │   └───TARGET_Freescale
        │       └───TARGET_MCU_K64F
        │           └───TOOLCHAIN_GCC_ARM
        └───hal
            └───TARGET_Freescale
                └───TARGET_KPSDK_MCUS
                    ├───TARGET_KPSDK_CODE
                    │   ├───common
                    │   │   └───phyksz8081
                    │   ├───drivers
                    │   │   ├───clock
                    │   │   ├───enet
                    │   │   │   └───src
                    │   │   ├───interrupt
                    │   │   └───pit
                    │   │       ├───common
                    │   │       └───src
                    │   ├───hal
                    │   │   ├───adc
                    │   │   ├───can
                    │   │   ├───dac
                    │   │   ├───dmamux
                    │   │   ├───dspi
                    │   │   ├───edma
                    │   │   ├───enet
                    │   │   ├───flextimer
                    │   │   ├───gpio
                    │   │   ├───i2c
                    │   │   ├───llwu
                    │   │   ├───lptmr
                    │   │   ├───lpuart
                    │   │   ├───mcg
                    │   │   ├───mpu
                    │   │   ├───osc
                    │   │   ├───pdb
                    │   │   ├───pit
                    │   │   ├───pmc
                    │   │   ├───port
                    │   │   ├───rcm
                    │   │   ├───rtc
                    │   │   ├───sai
                    │   │   ├───sdhc
                    │   │   ├───sim
                    │   │   ├───smc
                    │   │   ├───uart
                    │   │   └───wdog
                    │   └───utilities
                    │       └───src
                    └───TARGET_MCU_K64F
                        ├───device
                        │   ├───device
                        │   │   └───MK64F12
                        │   └───MK64F12
                        ├───MK64F12
                        └───TARGET_FRDM
```

After unpacking exporter ```zip``` file we can go to directory and see files inside MBED_A3 directory:
```
$ ls
GettingStarted.htm  Makefile  env  main.cpp  mbed
```
Exporter generated for us ```Makefile```  so now we can build our software:
```
$ make -j 8
.
.
.
   text    data     bss     dec     hex filename
  29336     184     336   29856    74a0 MBED_A3.elf
```

We can see root directory of exporter project is now populated with binary files:
* MBED_A3.bin.
* MBED_A3.elf .
* MBED_A3.hex.
You have also map file ```MBED_A3.map``` for your disposal.
```
$ ls
GettingStarted.htm  MBED_A3.bin  MBED_A3.elf  MBED_A3.hex  MBED_A3.map  Makefile  env  main.cpp  main.d  main.o  mbed
```

