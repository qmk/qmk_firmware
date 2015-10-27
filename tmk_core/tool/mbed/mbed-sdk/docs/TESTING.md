# Mbed SDK automated test suite
## Introduction

Test suit allows users to run locally on their machines Mbed SDK’s tests included in Mbed SDK repository. It also allows users to create their own tests and for example add new tests to test set as they progress with their project. If test is generic enough it could be included into official Mbed SDK test pool just do it via normal pull request!

Each test is supervised by python script called “host test” which will at least Test suite is using build script API to compile and build test source together with required by test libraries like CMSIS, Mbed, Ethernet, USB etc.

## What is host test?
Test suite supports test supervisor concept. This concept is realized by separate Python script called ```host test```. Host tests can be found in ```mbed/workspace_tools/host_tests/``` directory. Note: In newer mbed versions (mbed OS) host tests will be separate library.

Host test script is executed in parallel with test runner to monitor test execution. Basic host test just monitors device's default serial port for test results returned by test runner. Simple tests will print test result on serial port. In other cases host tests can for example judge by test results returned by test runner is test passed or failed. It all depends on test itself.

In some cases host test can be TCP server echoing packets from test runner and judging packet loss. In other cases it can just check if values returned from accelerometer are actually valid (sane).

## Test suite core: singletest.py script

```singletest.py``` script located in ```mbed/workspace_tools/``` is a test suite script which allows users to compile, build tests and test runners (also supports CppUTest unit test library). Script also is responsible for test execution on devices selected by configuration files.

### Parameters of singletest.py

Test execution script ```singletest.py``` is a fairly powerful tool to run tests for mbed SDK platform. It is flexible and allows users to configure test execution process and define which mbed platforms will be tested.

By specifying external configuration files (in JSON format) you can gain flexibility and prepare many different test scenarios. Just pass configuration file names to your script and run it.

#### MUTs Specification
You can easily configure your MUTs (Mbed Under Test) by creating configuration file with MUTs description.
Note: This configuration file must be in [JSON format](http://www.w3schools.com/json/).
Note: Unfortunately JSON format is not allowing you to have comments inside JSON code.

Let’s see some example and let's try to configure small "test farm" with three devices connected to your host computer. In this example no peripherals (like SD card or EEPROM) are connected to our Mbed boards. We will use three platforms in this example:
* [NXP LPC1768](https://mbed.org/platforms/mbed-LPC1768) board. 
* \[Freescale KL25Z](https://mbed.org/platforms/KL25Z) board and 
* [STMicro Nucleo F103RB](https://mbed.org/platforms/ST-Nucleo-F103RB) board. 
After connecting boards to our host machine (PC) we can check which serial ports and disks they occupy. For our example let's assume that:
* ```LPC1768``` serial port is on ```COM4``` and disk drive is ```J:```. 
* ```KL25Z``` serial port is on ```COM39``` and disk drive is ```E:```. 
* ```NUCLEO_F103RB``` serial port is on ```COM11``` and disk drive is ```I:```. 
If you are working under Linux your port and disk could look like /dev/ttyACM5 and /media/usb5.

This information is needed to create ```muts_all.json``` configuration file. You can create in in ```mbed/workspace_tools/``` directory:
```
$ touch muts_all.json
```

Its name will be passed to ```singletest.py``` script after ```-M``` (MUTs specification) switch. Let’s see how this file's content would look like in our example below:
```json
{
    "1" : {"mcu": "LPC1768",
        "port":"COM4",
        "disk":"J:\\",
        "peripherals": []
    },
 
    "2" : {"mcu": "KL25Z",
        "port":"COM39",
        "disk":"E:\\",
        "peripherals": []
    },
 
    "3" : {"mcu": "NUCLEO_F103RB",
        "port":"COM11",
        "disk":"I:\\",
        "peripherals": []
    }
}
```

Note: We will leave field ```peripherals``` empty for the sake of this example. We will explain it later. All you need to do now is to properly fill fields ```mcu```, ```port``` and ```disk```. 

Note: Please make sure files muts_all.json and test_spec.json are in workspace_tools/ directory. We will assume in this example they are.
Where to find ```mcu``` names? You can use option ```-S``` of ```build.py``` script (in ```mbed/workspace_tools/``` directory) to check all supported off-line MCUs names.

Note: If you update mbed device firmware or even disconnect / reconnect mbed device you may find that serial port / disk configuration changed. You need to update configuration file accordingly or you will face connection problems and obviously tests will not run.

#### Peripherals testing
When using MUTs configuration file (switch ```-M```) you can define in MUTs JSON file peripherals connected to your device:
```json
{
    "1" : {"mcu" : "KL25Z",
           "port" : "COM39",
           "disk" : "E:\\",
           "peripherals" : ["SD", "24LC256"]}
}
```
You can force test suite to run only common tests (switch ```-C```) or only peripheral tests (switch ```-P```).
```
$ python singletest.py -i test_spec.json -M muts_all.json -C
```
will not include tests for SD card and EEPROM 24LC256.
```
$ python  singletest.py -i test_spec.json -M muts_all.json -P
```
will only run tests bind to SD card and EEPROM 24LC256.

Note: option ```-P``` is useful for example in cases when you have same platform and different shields you want to test. No need to test common part all the time (timers, RTC, RTOS etc.). You can force to test peripherals only on some devices and for example only common tests on other devices.

#### Additional MUTs configuration file settings
You can add extra information to each MUT configuration. In particular you can specify which flashing (binary copy method) should be used, how to reset target and for example set reset timeout (used to delay test execution just after reset).

muts_all.json:
```json
{
    "1" : {"mcu" : "LPC1768",
           "port" : "COM77",
           "disk" : "G:\\",
           "peripherals" : ["TMP102", "digital_loop", "port_loop", "analog_loop", "SD"]},
 
    "2" : {"mcu" : "KL25Z",
           "port" : "COM89",
           "disk" : "F:\\",
           "peripherals" : ["SD", "24LC256", "KL25Z"],
           "copy_method" : "copy",
           "reset_type" : "default",
           "reset_tout" : "2"},
 
    "3" : {"mcu" : "LPC11U24",
           "port" : "COM76",
           "disk" : "E:\\",
           "peripherals" : []}
}
```
Please note that for MUT no. 2 few extra parameters were defined: ```copy_method```, ```reset_type``` and ```reset_tout```. Using this extra options you can tell test suite more about MUT you are using. This will allow you to be more flexible in terms of how you configure and use your MUTs.

* ```copy_method``` - STRING - tells test suite which binary copy method should be used.
You may notice that ```singletest.py``` command line help contains description about:
 * Option ```-c``` (in MUTs file called ```copy_method```) with available copy methods supported by test suite plugin system. 
 * Option ```-r``` (in MUTs file called reset_type) with available reset methods supported by test suite plugin system.
* ```reset_type``` - STRING - some boards may require special reset handling, for example vendor specific command must be executed to reset device.
* ```reset_tout``` - INTEGER - extra timeout just after device is reseted. May be used to wait for few seconds so device may finish booting, flashing data internally etc. 

Part of help listing for singletest.py:
```
  -c COPY_METHOD, --copy-method=COPY_METHOD
                        Select binary copy (flash) method. Default is Python's
                        shutil.copy() method. Plugin support: copy, cp,
                        default, eACommander, eACommander-usb, xcopy
  -r MUT_RESET_TYPE, --reset-type=MUT_RESET_TYPE
                        Extra reset method used to reset MUT by host test
                        script. Plugin support: default, eACommander,
                        eACommander-usb
```

----

Now we've already defined how our devices are connected to our host PC. We can continue and define which of this MUTs will be tested and which compilers we will use to compile and build Mbed SDK and tests. To do so we need to create test specification file (let's call it ```test_spec.json```) and put inside our configuration file information about which MUTs we actually want to test. We will pass this file's name to ```singletest.py``` script using ```-i``` switch.

Below we can see how sample ```test_spec.json``` file content could look like. (I've included all possible toolchains, we will change it in a moment):
```json
{
    "targets": {
        "LPC1768" : ["ARM", "uARM", "GCC_ARM", "GCC_CS", "GCC_CR", "IAR"],
        "KL25Z" : ["ARM", "GCC_ARM"],
        "NUCLEO_F103RB" : ["ARM", "uARM"]
     }
}
```
Above example configuration will force tests for LPC1768, KL25Z, NUCLEO_F103RB platforms and:

* Compilers: ```ARM```, ```uARM```, ```GCC_ARM```, ```GCC_CS```, ```GCC_CR``` and ```IAR``` will be used to compile tests for NXP's ```LPC1768```.
* Compilers: ```ARM``` and ```GCC_ARM``` will be used for Freescales' ```KL25Z``` platform.
* Compilers: ```ARM``` and ```uARM``` will be used for STMicro's ```NUCLEO_F103RB``` platform.

For our example purposes let's assume we only have Keil ARM compiler, so let's change configuration in ```test_spec.json``` file and reduce number of compiler to those we actually have:
```json
{
    "targets": {
        "LPC1768" : ["ARM", "uARM"],
        "KL25Z" : ["ARM"],
        "NUCLEO_F103RB" : ["ARM", "uARM"]
     }
}
```
#### Run your tests

After you configure all your MUTs and compilers you are ready to run tests. Make sure your devices are connected and your configuration files reflect your current configuration (serial ports, devices). Go to workspace_tools directory in your mbed location.
```
$ cd workspace_tools/
```
and execute test suite script.
```
$ python singletest.py -i test_spec.json -M muts_all.json
```
To check your configuration before test execution please use ```--config``` switch:
```
$ python singletest.py -i test_spec.json -M muts_all.json --config
MUTs configuration in m.json:
+-------+-------------+---------------+------+-------+
| index | peripherals | mcu           | disk | port  |
+-------+-------------+---------------+------+-------+
| 1     |             | LPC1768       | J:\  | COM4  |
| 3     |             | NUCLEO_F103RB | I:\  | COM11 |
| 2     |             | KL25Z         | E:\  | COM39 |
+-------+-------------+---------------+------+-------+

Test specification in t.json:
+---------------+-----+------+
| mcu           | ARM | uARM |
+---------------+-----+------+
| NUCLEO_F103RB | Yes | Yes  |
| KL25Z         | Yes | -    |
| LPC1768       | Yes | Yes  |
+---------------+-----+------+
```
It should help you localize basic problems with configuration files and toolchain configuration.
Note: Configurations with issues will be marked with ```*``` sign.

Having multiple configuration files allows you to manage your test scenarios in more flexible manner. You can:

* Set up all platforms and toolchains used during testing.
* Define (using script's ```-n``` switch) which tests you want to run during testing.
* Just run regression (all tests). Regression is default setting for test script. 

You can also force ```singletest.py``` script to:
* Run only peripherals' tests (switch ```-P```) or
* Just skip peripherals' tests (switch ```-C```). 
* Build mbed SDK, libraries and corresponding tests with multiple cores, just use ```-j X``` option where ```X``` is number of cores you want to use for compilation.
```
$ python singletest.py -i test_spec.json -M muts_all.json -j 8
```
* Print test cases console output using ```-V``` option.
* Only build mbed SDK, tests and dependant libraries with switch ```-O```:
```
$ python singletest.py -i test_spec.json -M muts_all.json -j 8 -O
```
* Execute each test case multiple times with ```--global-loops X``` option, where ```X``` number of repeats. Additionally use option ```-W``` to continue repeating test cases execution only if they continue to fail.
```
$ python singletest.py -i test_spec.json -M muts_all.json --global-loops 3 -W
``` 
* Option ```--loops``` can be used to overwrite global loop count and redefine loop count for particular tests. Define test loops as ```TEST_ID=X``` where ```X``` is integer and separate loops count definitions by comma if necessary. E.g. ```TEST_1=5,TEST_2=20,TEST_3=2```. 
```
$ python singletest.py -i test_spec.json -M muts_all.json RTOS_1=10,RTOS_2=5
```
This will execute test ```RTOS_1``` ten (10) times and test ```RTOS_2``` five (5) times.
* Force non default copy method. Note that mbed platforms can be flashed with just binary drag&drop. We simply copy file onto mbed's disk and interface chip flashes target MCU with given binary. Force non standard (Python specific) copy method by using option ```-c COPY_METHOD``` where ```COPY_METHOD``` can be shell, command line copy command like: ```cp```, ```copy````, ```xcopy``` etc. Make sure those commands are available from command line!
```
$ python singletest.py -i test_spec.json -M muts_all.json -c cp
``` 
* Run only selected tests. You can select which tests should be executed when you run test suite. Use ```-n``` switch to define tests by their ids you want to execute. Use comma to separate test ids:
```
$ python singletest.py -i test_spec.json -M muts_all.json -n RTOS_1,RTOS_2,RTOS_3,MBED_10,MBED_16,MBED_11
```
* Set common output binary name for all tests. In some cases you would like to have the same name for all tests. You can use switch ```--firmware-name``` to specify (without extension) build script output binary name.
In below example we would like to have all test binaries called ```firmware.bin`` (or with other extension like .elf, .hex depending on target accepted format).
```
$ python singletest.py -i test_spec.json -M muts_all.json --firmware-name firmware
```
* Where to find test list? Tests are defined in file ```tests.py``` in ```mbed/workspace_tools/``` directory. ```singletest.py``` uses test metadata in ```tests.py``` to resolve libraries dependencies and build tests for proper platforms and peripherals. Option ```-R``` can be used to get test names and direct path and test configuration.
```
$ python singletest.py -R
+-------------+-----------+---------------------------------------+--------------+-------------------+----------+--------------------------------------------------------+
| id          | automated | description                           | peripherals  | host_test         | duration | source_dir                                             |
+-------------+-----------+---------------------------------------+--------------+-------------------+----------+--------------------------------------------------------+
| MBED_1      | False     | I2C SRF08                             | SRF08        | host_test         |       10 | C:\Work\mbed\libraries\tests\mbed\i2c_SRF08            |
| MBED_10     | True      | Hello World                           | -            | host_test         |       10 | C:\Work\mbed\libraries\tests\mbed\hello                |
| MBED_11     | True      | Ticker Int                            | -            | host_test         |       20 | C:\Work\mbed\libraries\tests\mbed\ticker               |
| MBED_12     | True      | C++                                   | -            | host_test         |       10 | C:\Work\mbed\libraries\tests\mbed\cpp                  |
| MBED_13     | False     | Heap & Stack                          | -            | host_test         |       10 | C:\Work\mbed\libraries\tests\mbed\heap_and_stack       |
| MBED_14     | False     | Serial Interrupt                      | -            | host_test         |       10 | C:\Work\mbed\libraries\tests\mbed\serial_interrupt     |
| MBED_15     | False     | RPC                                   | -            | host_test         |       10 | C:\Work\mbed\libraries\tests\mbed\rpc                  |
| MBED_16     | True      | RTC                                   | -            | host_test         |       15 | C:\Work\mbed\libraries\tests\mbed\rtc                  |
| MBED_17     | False     | Serial Interrupt 2                    | -            | host_test         |       10 | C:\Work\mbed\libraries\tests\mbed\serial_interrupt_2   |
| MBED_18     | False     | Local FS Directory                    | -            | host_test         |       10 | C:\Work\mbed\libraries\tests\mbed\dir                  |
...
```
Note: you can filter tests by ```id``` column, just use ```-f``` option and give test name or regular expression:
```
$ python singletest.py -R -f RTOS
+--------------+-----------+-------------------------+-------------+-----------+----------+---------------------------------------------------+
| id           | automated | description             | peripherals | host_test | duration | source_dir                                        |
+--------------+-----------+-------------------------+-------------+-----------+----------+---------------------------------------------------+
| CMSIS_RTOS_1 | False     | Basic                   | -           | host_test |       10 | C:\Work\mbed\libraries\tests\rtos\cmsis\basic     |
| CMSIS_RTOS_2 | False     | Mutex                   | -           | host_test |       20 | C:\Work\mbed\libraries\tests\rtos\cmsis\mutex     |
| CMSIS_RTOS_3 | False     | Semaphore               | -           | host_test |       20 | C:\Work\mbed\libraries\tests\rtos\cmsis\semaphore |
| CMSIS_RTOS_4 | False     | Signals                 | -           | host_test |       10 | C:\Work\mbed\libraries\tests\rtos\cmsis\signals   |
| CMSIS_RTOS_5 | False     | Queue                   | -           | host_test |       20 | C:\Work\mbed\libraries\tests\rtos\cmsis\queue     |
| CMSIS_RTOS_6 | False     | Mail                    | -           | host_test |       20 | C:\Work\mbed\libraries\tests\rtos\cmsis\mail      |
| CMSIS_RTOS_7 | False     | Timer                   | -           | host_test |       10 | C:\Work\mbed\libraries\tests\rtos\cmsis\timer     |
| CMSIS_RTOS_8 | False     | ISR                     | -           | host_test |       10 | C:\Work\mbed\libraries\tests\rtos\cmsis\isr       |
| RTOS_1       | True      | Basic thread            | -           | host_test |       15 | C:\Work\mbed\libraries\tests\rtos\mbed\basic      |
| RTOS_2       | True      | Mutex resource lock     | -           | host_test |       20 | C:\Work\mbed\libraries\tests\rtos\mbed\mutex      |
| RTOS_3       | True      | Semaphore resource lock | -           | host_test |       20 | C:\Work\mbed\libraries\tests\rtos\mbed\semaphore  |
| RTOS_4       | True      | Signals messaging       | -           | host_test |       10 | C:\Work\mbed\libraries\tests\rtos\mbed\signals    |
| RTOS_5       | True      | Queue messaging         | -           | host_test |       10 | C:\Work\mbed\libraries\tests\rtos\mbed\queue      |
| RTOS_6       | True      | Mail messaging          | -           | host_test |       10 | C:\Work\mbed\libraries\tests\rtos\mbed\mail       |
| RTOS_7       | True      | Timer                   | -           | host_test |       15 | C:\Work\mbed\libraries\tests\rtos\mbed\timer      |
| RTOS_8       | True      | ISR (Queue)             | -           | host_test |       10 | C:\Work\mbed\libraries\tests\rtos\mbed\isr        |
| RTOS_9       | True      | SD File write-read      | SD          | host_test |       10 | C:\Work\mbed\libraries\tests\rtos\mbed\file       |
+--------------+-----------+-------------------------+-------------+-----------+----------+---------------------------------------------------+
```

* Shuffle your tests. We strongly encourage you to shuffle your test order each time you execute test suite script.
Rationale: It is probable that tests executed in one particular order will pass and in other will fail. To shuffle your tests’ order please use option ```–u``` (or ```--shuffle```):
```
$ python singletest.py -i test_spec.json -M muts_all.json --shuffle
```
Above command with force test script to randomly generate shuffle seed and shuffle test order execution. Note: Shuffle seed is float in ```[0.0, 1.0)```.

You can always recreate particular test order by forcing shuffle (```-u``` or ```--shuffle```} switch) and passing shuffle seed back to test suite using ```--shuffle-seed``` switch:
```
$ python singletest.py -i test_spec.json -M muts_all.json --shuffle --shuffle-seed 0.4041028336
```
Note: You can also supply your own randomly generated shuffle seed to drive particular test execution order scenarios. Just make sure shuffle seed is float in ```[0.0, 1.0)```.
You can find test shuffle seed in test summary:
```
...
| OK     | LPC1768 | ARM       | MBED_A9   | Serial Echo at 115200       |        2.84        |       10      |  1/1  |
+--------+---------+-----------+-----------+-----------------------------+--------------------+---------------+-------+
Result: 1 FAIL / 22 OK
Shuffle Seed: 0.4041028336

Completed in 234.85 sec
```

### Exmple of device configuration (one device connected to host computer)

This example will show you how to configure single device, run general tests or only peripheral tests. We will also show some real test result examples.

1. We will test only one board STMIcro Nucleo ```F334R8``` board connected to our PC (port ```COM46``` and disk is ```E:```).
2. We will also connect EEPROM ```24LC256``` to SDA, SCL pins of our Nucleo board and define 24LC256 peripheral to make sure our test suite will run all available tests for ```24LC256```.

Let's configure our one MUT and set uARM as the only compiler we will use to compiler Mbed SDK and tests.
We also need to create two configuration files ```muts_all.json``` and ```test_spec.json``` to pass our small testbed configuration to test script. 

muts_all.json:
```json
{
    "1" : { 
            "mcu": "NUCLEO_F334R8",
            "port":"COM46",
            "disk":"E:\\",
            "peripherals": ["24LC256"]
    }
}
```
Note: By defining ```"peripherals": ["24LC256"]``` we are passing to test suite information that this particular board has EEPROM 24LC256 connected to our board. 

test_spec.json:
```json
{
    "targets": {
        "NUCLEO_F334R8" : ["uARM"]
     }
}
```
Note: 
* Please make sure device is connected before we will start running tests.
* Please make sure files ```muts_all.json``` and ```test_spec.json``` are in ```mbed/workspace_tools/``` directory.
Now you can call test suite and execute tests:
```
$ python singletest.py -i test_spec.json -M muts_all.json
...
Test summary:
+--------+---------------+-----------+-----------+---------------------------------+--------------------+---------------+
| Result | Target        | Toolchain | Test ID   | Test Description                | Elapsed Time (sec) | Timeout (sec) |
+--------+---------------+-----------+-----------+---------------------------------+--------------------+---------------+
| OK     | NUCLEO_F334R8 | uARM      | MBED_A25  | I2C EEPROM line read/write test |       12.41        |       15      |
| OK     | NUCLEO_F334R8 | uARM      | MBED_A1   | Basic                           |        3.42        |       10      |
| OK     | NUCLEO_F334R8 | uARM      | EXAMPLE_1 | /dev/null                       |        3.42        |       10      |
| OK     | NUCLEO_F334R8 | uARM      | MBED_24   | Timeout Int us                  |       11.47        |       15      |
| OK     | NUCLEO_F334R8 | uARM      | MBED_25   | Time us                         |       11.43        |       15      |
| OK     | NUCLEO_F334R8 | uARM      | MBED_26   | Integer constant division       |        3.37        |       10      |
| OK     | NUCLEO_F334R8 | uARM      | MBED_23   | Ticker Int us                   |       12.43        |       15      |
| OK     | NUCLEO_F334R8 | uARM      | MBED_A19  | I2C EEPROM read/write test      |       11.42        |       15      |
| OK     | NUCLEO_F334R8 | uARM      | MBED_11   | Ticker Int                      |       12.43        |       20      |
| OK     | NUCLEO_F334R8 | uARM      | MBED_10   | Hello World                     |        2.42        |       10      |
| OK     | NUCLEO_F334R8 | uARM      | MBED_12   | C++                             |        3.42        |       10      |
| OK     | NUCLEO_F334R8 | uARM      | MBED_16   | RTC                             |        4.76        |       15      |
| UNDEF  | NUCLEO_F334R8 | uARM      | MBED_2    | stdio                           |       20.42        |       20      |
| UNDEF  | NUCLEO_F334R8 | uARM      | MBED_A9   | Serial Echo at 115200           |       10.37        |       10      |
+--------+---------------+-----------+-----------+---------------------------------+--------------------+---------------+
Result: 2 UNDEF / 12 OK

Completed in 160 sec
```

If we want to get additional test summary with results in separate columns please use option ```-t```.
```
$ python singletest.py -i test_spec.json -M muts_all.json -t
...
Test summary:
+---------------+-----------+---------------------------------+-------+
| Target        | Test ID   | Test Description                | uARM  |
+---------------+-----------+---------------------------------+-------+
| NUCLEO_F334R8 | EXAMPLE_1 | /dev/null                       | OK    |
| NUCLEO_F334R8 | MBED_10   | Hello World                     | OK    |
| NUCLEO_F334R8 | MBED_11   | Ticker Int                      | OK    |
| NUCLEO_F334R8 | MBED_12   | C++                             | OK    |
| NUCLEO_F334R8 | MBED_16   | RTC                             | OK    |
| NUCLEO_F334R8 | MBED_2    | stdio                           | UNDEF |
| NUCLEO_F334R8 | MBED_23   | Ticker Int us                   | OK    |
| NUCLEO_F334R8 | MBED_24   | Timeout Int us                  | OK    |
| NUCLEO_F334R8 | MBED_25   | Time us                         | OK    |
| NUCLEO_F334R8 | MBED_26   | Integer constant division       | OK    |
| NUCLEO_F334R8 | MBED_A1   | Basic                           | OK    |
| NUCLEO_F334R8 | MBED_A19  | I2C EEPROM read/write test      | OK    |
| NUCLEO_F334R8 | MBED_A25  | I2C EEPROM line read/write test | OK    |
| NUCLEO_F334R8 | MBED_A9   | Serial Echo at 115200           | UNDEF |
+---------------+-----------+---------------------------------+-------+
```
----
Please do not forget you can combine few options together to get result you want. For example you want to repeat few tests multiple number of times, shuffle test ids execution order and select only tests which are critical for you at this point. You can do it using switch -n, --global-loops with --loops and --shuffle:

Execute above command to:

* Run only tests: ```RTOS_1```, ```RTOS_2```, ```RTOS_3```, ```MBED_10```, ```MBED_16```, ```MBED_11```.
* Shuffle test execution order. Note tests in loops will not be shuffled.
* Set global loop count to 3 - each test will repeated 3 times.
* Overwrite global loop count (set above to 3) and:
 * Force to loop test RTOS_1 to execute 3 times.
 * Force to loop test RTOS_2 to execute 4 times.
 * Force to loop test RTOS_3 to execute 5 times.
 * Force to loop test MBED_11 to execute 5 times. 

```
$ python singletest.py -i test_spec.json -M muts_all.json -n RTOS_1,RTOS_2,RTOS_3,MBED_10,MBED_16,MBED_11 --shuffle --global-loops 3 --loops RTOS_1=3,RTOS_2=4,RTOS_3=5,MBED_11=5
```

# CppUTest unit test library support
## CppUTest in Mbed SDK testing introduction
[CppUTest](http://cpputest.github.io/) is a C / C++ based unit xUnit test framework for unit testing and for test-driving your code. It is written in C++ but is used in C and C++ projects and frequently used in embedded systems but it works for any C / C++ project.

Mbed SDK test suite supports writing tests using CppUTest. All you need to do it to provide CppUTest sources and includes with Mbed SDK port. This is already done for you so all you need to do it to get proper sources in your project directory.
CppUTest’s core design principles are:
* Simple in design and simple in use. 
* Portable to old and new platforms. 
* Build with Test-driven Development in mind.

## From where you can get more help about CppUTest library and unit testing
•	You can read [CppUTest manual](http://cpputest.github.io/manual.html)
* [CppUTest forum](https://groups.google.com/forum/?fromgroups#!forum/cpputest) 
* [CppUTest on GitHub](https://github.com/cpputest/cpputest)
* Finally, if you think unit testing is new concept for you, you can have a grasp of it on Wikipedia pages about [unit testing](http://en.wikipedia.org/wiki/Unit_testing) and continue from there. 

## How to add CppUTest to your current Mbed SDK installation

### Do I need CppUTest port for Mbed SDK?
Yes, you do. If you want to use CppUTest with Mbed SDK you need to have CppUTest version with ARMCC compiler (only ARM flavor for now) port and Mbed SDK console port (if you want to have output on serial port). All is already prepared by Mbed engineers and you can get it for example here: http://mbed.org/users/rgrover1/code/CppUTest/

### Prerequisites
* Installed [git client](http://git-scm.com/downloads/).
* Installed [Mercurial client](http://mercurial.selenic.com/).

### How / where to install
We want to create directory structure similar to one below:
```
\your_project_directory
│
├───cpputest
│   ├───include
│   └───src
└───mbed
    ├───libraries
    ├───travis
    └───workspace_tools
```

Please go to directory with your project. For example it could be c:\Projects\Project.
```
$ cd c:\Projects\Project
```
If your project directory already has your mbed SDK repository included just execute below command (Mercurial console client). It should download CppUTest with Mbed SDK port.
```
$ hg clone https://mbed.org/users/rgrover1/code/cpputest/
```

You should see something like this after you execute Mercurial clone command:
```
$ hg clone https://mbed.org/users/rgrover1/code/cpputest/
destination directory: cpputest
requesting all changes
adding changesets
adding manifests
adding file changes
added 3 changesets with 69 changes to 42 files
updating to branch default
41 files updated, 0 files merged, 0 files removed, 0 files unresolved
```

Confirm your project structure. It should look more or less like this:
```
$ ls
cpputest  mbed
```
From now on CppUTest is in correct path. Each time you want to compile unit tests for CppUTest build script will always look for CppUTest library in the same directory where mbed library is.

## New off-line mbed SDK project with CppUTest support

If you are creating new mbed SDK project and you want to use CppUTest with it you need to download both mbed SDK and CppUTest with mbed port to the same directory. You can do it like this:
```
$ cd c:\Projects\Project
$ git clone https://github.com/mbedmicro/mbed.git
$ hg clone https://mbed.org/users/rgrover1/code/cpputest/
```

After above three steps you should have proper directory structure. All you need to do now is to configure your ```private_settings.py``` in ```mbed/workspace_tools/``` directory. Please refer to mbed SDK build script documentation for details.

## CppUTest with mbed port 
To make sure you actualy have CppUTest library with mbed SDK port you can go to CppUTest ```armcc``` platform directory:
```
$ cd c:/Projects/Project/cpputest/src/Platforms/armcc/
```
And open file ```UtestPlatform.cpp```.

You should find part of code responsible for porting console on default serial port of the mbed device:
```c++
#include "Serial.h"
using namespace mbed;
 
int PlatformSpecificPutchar(int c)
{
    /* Please modify this block for test results to be reported as
     * console output. The following is a sample implementation using a
     * Serial object connected to the console. */
#define NEED_TEST_REPORT_AS_CONSOLE_OUTPUT 1
#if NEED_TEST_REPORT_AS_CONSOLE_OUTPUT
    extern Serial console;
 
    #define NEED_LINE_FEED_IN_ADDITION_TO_NEWLINE 1
    #if NEED_LINE_FEED_IN_ADDITION_TO_NEWLINE
    /* CppUTest emits \n line terminators in its reports; some terminals
     * need the linefeed (\r) in addition. */
    if (c == '\n') {
        console.putc('\r');
    }
    #endif /* #if NEED_LINE_FEED_IN_ADDITION_TO_NEWLINE */
 
    return (console.putc(c));
#else /* NEED_TEST_REPORT_AS_CONSOLE_OUTPUT */
    return (0);
#endif /* NEED_TEST_REPORT_AS_CONSOLE_OUTPUT */
}
```

You can find cpputest UT test runner main function in mbed sources: ```c:/Projects/Project/mbed/libraries/tests/utest/testrunner/testrunner.cpp```. Test runner code (in ```testrunner.cpp```) only defined console object and executes all unit tests:
```c++
#include "CommandLineTestRunner.h"
#include <stdio.h>
#include "mbed.h"
#include "testrunner.h"
#include "test_env.h"

/**
Object 'mbed_cpputest_console' is used to show prints on console.
It is declared in \cpputest\src\Platforms\armcc\UtestPlatform.cpp
*/
Serial mbed_cpputest_console(STDIO_UART_TX, STDIO_UART_RX);

int main(int ac, char** av) {
    MBED_HOSTTEST_TIMEOUT(20);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(Unit test);
    MBED_HOSTTEST_START("UT");

    unsigned failureCount = 0;
    {
        // Some compilers may not pass ac, av so we need to supply them ourselves
        int ac = 2;
        char* av[] = {__FILE__, "-v"};
        failureCount = CommandLineTestRunner::RunAllTests(ac, av);
    }

    MBED_HOSTTEST_RESULT(failureCount == 0);
    return failureCount;
}
```

## Unit test location
Unit tests source code is located in below directory: ```c:/Projects/Project/mbed/libraries/tests/utest/```

Each sub directory except testrunner contains compilable unit test source files with test groups and test cases. You can see utest structure below. Please note this is just example and in the future this directory will contain many sub directories with unit tests.
```
$ c:\Projects\Project\mbed\libraries\tests\utest> tree
utest
├───basic
├───semihost_fs
└───testrunner
```

## Define unit tests in mbed SDK test suite structure
All tests defined in test suite are described in ```mbed/workspace_tools/tests.py``` file. This file stores data structure ```TESTS``` which is a list of simple structures describing each test. Below you can find example of ```TESTS``` structure which is configuring one of the unit tests.
```
.
.
.
    {
        "id": "UT_2", "description": "Semihost file system",
        "source_dir": join(TEST_DIR, "utest", "file"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB, CPPUTEST_LIBRARY],
        "automated": False,
        "mcu": ["LPC1768", "LPC2368", "LPC11U24"]
    },
.
.
.
```
Note: In dependency section we've added library ```CPPUTEST_LIBRARY``` which is pointing build script to CppUTest library with mbed port. This is a must for unit tests to be compiled with CppUTest library.

### Tests are now divided into two types:
#### 'Hello world' tests 
First type of test cases we call 'hello world' tests. They do not dependent on CppUTest library and are monolithic programs usually composed of one main function. Yo can find this tests in below example directories:

* ```mbed/libraries/tests/mbed/```
* ```mbed/libraries/tests/net/```
* ```mbed/libraries/tests/rtos/```
* ```mbed/libraries/tests/usb/```

Usually ‘hello world’ test cases are using ```test_env.cpp``` and ```test_env.h``` files which implement simple test framework used to communicate with host test and help test framework instrument your tests.

Below you can see listing of ```test_env.h``` file which contains simple macro definitions used to communicate (via serial port printouts) between test case (on hardware) and host test script (on host computer). 
Each use case should print on console basic information like:
* Default test case timeout.
* Which host test should be used to supervise test case execution.
* Test description and test case ID (short identifier).

```c++
.
.
.
// Test result related notification functions
void notify_start();
void notify_completion(bool success);
bool notify_completion_str(bool success, char* buffer);
void notify_performance_coefficient(const char* measurement_name, const int value);
void notify_performance_coefficient(const char* measurement_name, const unsigned int value);
void notify_performance_coefficient(const char* measurement_name, const double value);

// Host test auto-detection API
void notify_host_test_name(const char *host_test);
void notify_timeout(int timeout);
void notify_test_id(const char *test_id);
void notify_test_description(const char *description);

// Host test auto-detection API
#define MBED_HOSTTEST_START(TESTID)      notify_test_id(TESTID); notify_start()
#define MBED_HOSTTEST_SELECT(NAME)       notify_host_test_name(#NAME)
#define MBED_HOSTTEST_TIMEOUT(SECONDS)   notify_timeout(SECONDS)
#define MBED_HOSTTEST_DESCRIPTION(DESC)  notify_test_description(#DESC)
#define MBED_HOSTTEST_RESULT(RESULT)     notify_completion(RESULT)

/**
    Test auto-detection preamble example:
    main() {
        MBED_HOSTTEST_TIMEOUT(10);
        MBED_HOSTTEST_SELECT( host_test );
        MBED_HOSTTEST_DESCRIPTION(Hello World);
        MBED_HOSTTEST_START("MBED_10");
        // Proper 'host_test.py' should take over supervising of this test

        // Test code
        bool result = ...;

        MBED_HOSTTEST_RESULT(result);
    }
*/
.
.
.
```

Example of 'hello world' test:
```c++
#include "mbed.h"
#include "test_env.h"

#define CUSTOM_TIME  1256729737

int main() {
    MBED_HOSTTEST_TIMEOUT(20);
    MBED_HOSTTEST_SELECT(rtc_auto);
    MBED_HOSTTEST_DESCRIPTION(RTC);
    MBED_HOSTTEST_START("MBED_16");

    char buffer[32] = {0};
    set_time(CUSTOM_TIME);  // Set RTC time to Wed, 28 Oct 2009 11:35:37
    while(1) {
        time_t seconds = time(NULL);
        strftime(buffer, 32, "%Y-%m-%d %H:%M:%S %p", localtime(&seconds));
        printf("MBED: [%ld] [%s]\r\n", seconds, buffer);
        wait(1);
    }
}
```

#### 'Unit test' test cases
Second group of tests are unit tests. They are using CppUTest library and require you to write ```TEST_GROUP```s and ```TEST```s in your test files. Test suite will add test runner sources to your test automatically so you can concentrate on writing tests.

Example of unit test:
```c++
#include "TestHarness.h"
#include <utility>
#include "mbed.h"

TEST_GROUP(BusOut_mask)
{
};

TEST(BusOut_mask, led_1_2_3)
{
    BusOut bus_data(LED1, LED2, LED3);
    CHECK_EQUAL(0x07, bus_data.mask());
}

TEST(BusOut_mask, led_nc_nc_nc_nc)
{
    BusOut bus_data(NC, NC, NC, NC);
    CHECK_EQUAL(0x00, bus_data.mask());
}

TEST(BusOut_mask, led_1_2_3_nc_nc)
{
    BusOut bus_data(LED1, LED2, LED3, NC, NC);
    CHECK_EQUAL(0x07, bus_data.mask());
}

TEST(BusOut_mask, led_1_nc_2_nc_nc_3)
{
    BusOut bus_data(LED1, NC, LED2, NC, NC, LED3);
    CHECK_EQUAL(0x25, bus_data.mask());
}

///////////////////////////////////////////////////////////////////////////////

#ifdef MBED_OPERATORS
TEST_GROUP(BusOut_digitalout_write)
{
};

TEST(BusOut_digitalout_write, led_nc)
{
    BusOut bus_data(NC);
    CHECK_EQUAL(false, bus_data[0].is_connected())
}

TEST(BusOut_digitalout_write, led_1_2_3)
{
    BusOut bus_data(LED1, LED2, LED3);
    bus_data[0].write(1);
    bus_data[1].write(1);
    bus_data[2].write(1);
    CHECK(bus_data[0].read());
    CHECK(bus_data[1].read());
    CHECK(bus_data[2].read());
}

TEST(BusOut_digitalout_write, led_1_2_3_nc_nc)
{
    BusOut bus_data(LED1, LED2, LED3, NC, NC);
    bus_data[0].write(0);
    bus_data[1].write(0);
    bus_data[2].write(0);
    CHECK(bus_data[0].read() == 0);
    CHECK(bus_data[1].read() == 0);
    CHECK(bus_data[2].read() == 0);
}

TEST(BusOut_digitalout_write, led_1_nc_2_nc_nc_3)
{
    BusOut bus_data(LED1, NC, LED2, NC, NC, LED3);
    bus_data[0].write(1);
    bus_data[2].write(0);
    bus_data[5].write(0);
    CHECK(bus_data[0].read());
    CHECK(bus_data[2].read() == 0);
    CHECK(bus_data[5].read() == 0);
}
#endif
```

## Example
In below example we will run two example unit tests that are now available. tests ```UT_1``` and ```UT_2``` are unit tests used for now only to check if mbed SDK works with CppUTest library and if tests are being executed. In future number of unit tests will increase, nothing is also should stop you from writing and executing your own unit tests!

### Example configuration
By default unit tests ```UT_1``` and ```UT_2``` are not automated - simply test suite will ignore them. Also we do not want to create dependency to CppUTest library each time someone executes automation.

Note: To compile ```UT_1``` and ```UT_2``` tests CppUTest library described above installation is needed and not all users wish to add UT libs to their project. Also new to mbed users may find it difficult. This is why unit testing is an extra feature active only after you deliberately install and enable needed components.

Bellow snippet shows how to modify 'automated' flag so test suite will consider unit tests ```UT_1``` and ```UT_2``` as part of "automated test portfolio". Just change flag 'automated' from ```False``` to ```True```.

```tests.py``` listing related to ```UT_1``` and ```UT_2```:
```python
.
.
.
    # CPPUTEST Library provides Unit testing Framework
    #
    # To write TESTs and TEST_GROUPs please add CPPUTEST_LIBRARY to 'dependencies'
    #
    # This will also include:
    # 1. test runner - main function with call to CommandLineTestRunner::RunAllTests(ac, av)
    # 2. Serial console object to print test result on serial port console
    #
 
    # Unit testing with cpputest library
    {
        "id": "UT_1", "description": "Basic",
        "source_dir": join(TEST_DIR, "utest", "basic"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB, CPPUTEST_LIBRARY],
        "automated": True,
    },
    {
        "id": "UT_2", "description": "Semihost file system",
        "source_dir": join(TEST_DIR, "utest", "semihost_fs"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB, CPPUTEST_LIBRARY],
        "automated": True,
        "mcu": ["LPC1768", "LPC2368", "LPC11U24"]
    },
.
.
.
```

### Execute tests
In my test I will use common [LPC1768](http://developer.mbed.org/platforms/mbed-LPC1768/) mbed-enabled board because unit test ```UT_2``` is checking semi-host functionality which is available on this board and handful of others.

Configure your ```test_spec.json``` and ```muts_all.json``` files (refer to test suite build script and automation description) and set mbed disk and serial port.

```
$ singletest.py -i test_spec.json -M muts_all.json -n UT_1,UT_2 -V
Building library CMSIS (LPC1768, ARM)
Building library MBED (LPC1768, ARM)
Building library CPPUTEST (LPC1768, ARM)
Building project BASIC (LPC1768, ARM)
Executing 'python host_test.py -p COM77 -d E:\ -t 10'
Test::Output::Start
Host test instrumentation on port: "COM77" and disk: "E:\"
TEST(FirstTestGroup, FirstTest) - 0 ms

OK (1 tests, 1 ran, 3 checks, 0 ignored, 0 filtered out, 3 ms)

{{success}}
{{end}}
Test::Output::Finish
TargetTest::LPC1768::ARM::UT_1::Basic [OK] in 2.43 of 10 sec
Building library CPPUTEST (LPC1768, ARM)
Building project SEMIHOST_FS (LPC1768, ARM)
Executing 'python host_test.py -p COM77 -d E:\ -t 10'
Test::Output::Start
Host test instrumentation on port: "COM77" and disk: "E:\"
TEST(FirstTestGroup, FirstTest) - 9 ms

OK (1 tests, 1 ran, 10 checks, 0 ignored, 0 filtered out, 10 ms)

{{success}}
{{end}}
Test::Output::Finish
TargetTest::LPC1768::ARM::UT_2::Semihost file system [OK] in 2.43 of 10 sec
Test summary:
+--------+---------+-----------+---------+----------------------+--------------------+---------------+-------+
| Result | Target  | Toolchain | Test ID | Test Description     | Elapsed Time (sec) | Timeout (sec) | Loops |
+--------+---------+-----------+---------+----------------------+--------------------+---------------+-------+
| OK     | LPC1768 | ARM       | UT_1    | Basic                |        2.43        |       10      |  1/1  |
| OK     | LPC1768 | ARM       | UT_2    | Semihost file system |        2.43        |       10      |  1/1  |
+--------+---------+-----------+---------+----------------------+--------------------+---------------+-------+
Result: 2 OK

Completed in 12.02 sec
```

You can compile unit tests using various number of supported compilers, below just few examples with working solutions:
```
Test summary:
+--------+---------+-----------+---------+----------------------+--------------------+---------------+-------+
| Result | Target  | Toolchain | Test ID | Test Description     | Elapsed Time (sec) | Timeout (sec) | Loops |
+--------+---------+-----------+---------+----------------------+--------------------+---------------+-------+
| OK     | LPC1768 | ARM       | UT_1    | Basic                |        2.43        |       10      |  1/1  |
| OK     | LPC1768 | ARM       | UT_2    | Semihost file system |        2.43        |       10      |  1/1  |
| OK     | LPC1768 | uARM      | UT_1    | Basic                |        2.43        |       10      |  1/1  |
| OK     | LPC1768 | uARM      | UT_2    | Semihost file system |        2.43        |       10      |  1/1  |
| OK     | LPC1768 | GCC_ARM   | UT_1    | Basic                |        2.43        |       10      |  1/1  |
| OK     | LPC1768 | GCC_ARM   | UT_2    | Semihost file system |        2.43        |       10      |  1/1  |
| OK     | LPC1768 | GCC_CR    | UT_1    | Basic                |        3.44        |       10      |  1/1  |
| OK     | LPC1768 | GCC_CR    | UT_2    | Semihost file system |        3.43        |       10      |  1/1  |
+--------+---------+-----------+---------+----------------------+--------------------+---------------+-------+
Result: 8 OK

Completed in 55.85 sec
```
