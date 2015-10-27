#! /usr/bin/env python2
"""
mbed SDK
Copyright (c) 2011-2013 ARM Limited

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


TEST BUILD & RUN
"""
import sys
from time import sleep
from shutil import copy
from os.path import join, abspath, dirname

# Be sure that the tools directory is in the search path
ROOT = abspath(join(dirname(__file__), ".."))
sys.path.insert(0, ROOT)

from workspace_tools.utils import args_error
from workspace_tools.paths import BUILD_DIR
from workspace_tools.paths import RTOS_LIBRARIES
from workspace_tools.paths import ETH_LIBRARY
from workspace_tools.paths import USB_HOST_LIBRARIES, USB_LIBRARIES
from workspace_tools.paths import DSP_LIBRARIES
from workspace_tools.paths import FS_LIBRARY
from workspace_tools.paths import UBLOX_LIBRARY
from workspace_tools.tests import TESTS, Test, TEST_MAP
from workspace_tools.tests import TEST_MBED_LIB
from workspace_tools.targets import TARGET_MAP
from workspace_tools.options import get_default_options_parser
from workspace_tools.build_api import build_project
try:
    import workspace_tools.private_settings as ps
except:
    ps = object()


if __name__ == '__main__':
    # Parse Options
    parser = get_default_options_parser()
    parser.add_option("-p",
                      type="int",
                      dest="program",
                      help="The index of the desired test program: [0-%d]" % (len(TESTS)-1))

    parser.add_option("-n",
                      dest="program_name",
                      help="The name of the desired test program")

    parser.add_option("-j", "--jobs",
                      type="int",
                      dest="jobs",
                      default=1,
                      help="Number of concurrent jobs (default 1). Use 0 for auto based on host machine's number of CPUs")

    parser.add_option("-v", "--verbose",
                      action="store_true",
                      dest="verbose",
                      default=False,
                      help="Verbose diagnostic output")

    parser.add_option("--silent",
                      action="store_true",
                      dest="silent",
                      default=False,
                      help="Silent diagnostic output (no copy, compile notification)")

    parser.add_option("-D", "",
                      action="append",
                      dest="macros",
                      help="Add a macro definition")

    # Local run
    parser.add_option("--automated", action="store_true", dest="automated",
                      default=False, help="Automated test")
    parser.add_option("--host", dest="host_test",
                      default=None, help="Host test")
    parser.add_option("--extra", dest="extra",
                      default=None, help="Extra files")
    parser.add_option("--peripherals", dest="peripherals",
                      default=None, help="Required peripherals")
    parser.add_option("--dep", dest="dependencies",
                      default=None, help="Dependencies")
    parser.add_option("--source", dest="source_dir",
                      default=None, help="The source (input) directory")
    parser.add_option("--duration", type="int", dest="duration",
                      default=None, help="Duration of the test")
    parser.add_option("--build", dest="build_dir",
                      default=None, help="The build (output) directory")
    parser.add_option("-d", "--disk", dest="disk",
                      default=None, help="The mbed disk")
    parser.add_option("-s", "--serial", dest="serial",
                      default=None, help="The mbed serial port")
    parser.add_option("-b", "--baud", type="int", dest="baud",
                      default=None, help="The mbed serial baud rate")
    parser.add_option("-L", "--list-tests", action="store_true", dest="list_tests",
                      default=False, help="List available tests in order and exit")

    # Ideally, all the tests with a single "main" thread can be run with, or
    # without the rtos, eth, usb_host, usb, dsp, fat, ublox
    parser.add_option("--rtos",
                      action="store_true", dest="rtos",
                      default=False, help="Link with RTOS library")

    parser.add_option("--eth",
                      action="store_true", dest="eth",
                      default=False,
                      help="Link with Ethernet library")

    parser.add_option("--usb_host",
                      action="store_true",
                      dest="usb_host",
                      default=False,
                      help="Link with USB Host library")

    parser.add_option("--usb",
                      action="store_true",
                      dest="usb",
                      default=False,
                      help="Link with USB Device library")

    parser.add_option("--dsp",
                      action="store_true",
                      dest="dsp",
                      default=False,
                      help="Link with DSP library")

    parser.add_option("--fat",
                      action="store_true",
                      dest="fat",
                      default=False,
                      help="Link with FS ad SD card file system library")

    parser.add_option("--ublox",
                      action="store_true",
                      dest="ublox",
                      default=False,
                      help="Link with U-Blox library")

    parser.add_option("--testlib",
                      action="store_true",
                      dest="testlib",
                      default=False,
                      help="Link with mbed test library")

    # Specify a different linker script
    parser.add_option("-l", "--linker", dest="linker_script",
                      default=None, help="use the specified linker script")

    (options, args) = parser.parse_args()

    # Print available tests in order and exit
    if options.list_tests is True:
        print '\n'.join(map(str, sorted(TEST_MAP.values())))
        sys.exit()

    # force program to "0" if a source dir is specified
    if options.source_dir is not None:
        p = 0
        n = None
    else:
    # Program Number or name
        p, n = options.program, options.program_name

    if n is not None and p is not None:
        args_error(parser, "[ERROR] specify either '-n' or '-p', not both")
    if n:
        # We will transform 'n' to list of 'p' (integers which are test numbers)
        nlist = n.split(',')
        for test_id in nlist:
            if test_id not in TEST_MAP.keys():
                args_error(parser, "[ERROR] Program with name '%s' not found"% test_id)

        p = [TEST_MAP[n].n for n in nlist]
    elif p is None or (p < 0) or (p > (len(TESTS)-1)):
        message = "[ERROR] You have to specify one of the following tests:\n"
        message += '\n'.join(map(str, sorted(TEST_MAP.values())))
        args_error(parser, message)

    # If 'p' was set via -n to list of numbers make this a single element integer list
    if type(p) != type([]):
        p = [p]

    # Target
    if options.mcu is None :
        args_error(parser, "[ERROR] You should specify an MCU")
    mcu = options.mcu

    # Toolchain
    if options.tool is None:
        args_error(parser, "[ERROR] You should specify a TOOLCHAIN")
    toolchain = options.tool

    # Test
    for test_no in p:
        test = Test(test_no)
        if options.automated is not None:    test.automated = options.automated
        if options.dependencies is not None: test.dependencies = options.dependencies
        if options.host_test is not None:    test.host_test = options.host_test;
        if options.peripherals is not None:  test.peripherals = options.peripherals;
        if options.duration is not None:     test.duration = options.duration;
        if options.extra is not None:        test.extra_files = options.extra

        if not test.is_supported(mcu, toolchain):
            print 'The selected test is not supported on target %s with toolchain %s' % (mcu, toolchain)
            sys.exit()

        # Linking with extra libraries
        if options.rtos:     test.dependencies.append(RTOS_LIBRARIES)
        if options.eth:      test.dependencies.append(ETH_LIBRARY)
        if options.usb_host: test.dependencies.append(USB_HOST_LIBRARIES)
        if options.usb:      test.dependencies.append(USB_LIBRARIES)
        if options.dsp:      test.dependencies.append(DSP_LIBRARIES)
        if options.fat:      test.dependencies.append(FS_LIBRARY)
        if options.ublox:    test.dependencies.append(UBLOX_LIBRARY)
        if options.testlib:  test.dependencies.append(TEST_MBED_LIB)

        build_dir = join(BUILD_DIR, "test", mcu, toolchain, test.id)
        if options.source_dir is not None:
            test.source_dir = options.source_dir
            build_dir = options.source_dir

        if options.build_dir is not None:
            build_dir = options.build_dir

        target = TARGET_MAP[mcu]
        try:
            bin_file = build_project(test.source_dir, build_dir, target, toolchain, test.dependencies, options.options,
                                     linker_script=options.linker_script,
                                     clean=options.clean,
                                     verbose=options.verbose,
                                     silent=options.silent,
                                     macros=options.macros,
                                     jobs=options.jobs)
            print 'Image: %s'% bin_file

            if options.disk:
                # Simple copy to the mbed disk
                copy(bin_file, options.disk)

            if options.serial:
                # Import pyserial: https://pypi.python.org/pypi/pyserial
                from serial import Serial

                sleep(target.program_cycle_s())

                serial = Serial(options.serial, timeout = 1)
                if options.baud:
                    serial.setBaudrate(options.baud)

                serial.flushInput()
                serial.flushOutput()

                try:
                    serial.sendBreak()
                except:
                    # In linux a termios.error is raised in sendBreak and in setBreak.
                    # The following setBreak() is needed to release the reset signal on the target mcu.
                    try:
                        serial.setBreak(False)
                    except:
                        pass

                while True:
                    c = serial.read(512)
                    sys.stdout.write(c)
                    sys.stdout.flush()

        except KeyboardInterrupt, e:
            print "\n[CTRL+c] exit"
        except Exception,e:
            if options.verbose:
                import traceback
                traceback.print_exc(file=sys.stdout)
            else:
                print "[ERROR] %s" % str(e)
