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

LIBRARIES BUILD
"""
import sys
from time import time
from os.path import join, abspath, dirname


# Be sure that the tools directory is in the search path
ROOT = abspath(join(dirname(__file__), ".."))
sys.path.insert(0, ROOT)


from workspace_tools.toolchains import TOOLCHAINS
from workspace_tools.toolchains import print_notify_verbose
from workspace_tools.targets import TARGET_NAMES, TARGET_MAP
from workspace_tools.options import get_default_options_parser
from workspace_tools.build_api import build_mbed_libs, build_lib
from workspace_tools.build_api import mcu_toolchain_matrix
from workspace_tools.build_api import static_analysis_scan, static_analysis_scan_lib, static_analysis_scan_library
from workspace_tools.build_api import print_build_results
from workspace_tools.settings import CPPCHECK_CMD, CPPCHECK_MSG_FORMAT

if __name__ == '__main__':
    start = time()

    # Parse Options
    parser = get_default_options_parser()

    # Extra libraries
    parser.add_option("-r", "--rtos",
                      action="store_true",
                      dest="rtos",
                      default=False,
                      help="Compile the rtos")

    parser.add_option("-e", "--eth",
                      action="store_true", dest="eth",
                      default=False,
                      help="Compile the ethernet library")

    parser.add_option("-U", "--usb_host",
                      action="store_true",
                      dest="usb_host",
                      default=False,
                      help="Compile the USB Host library")

    parser.add_option("-u", "--usb",
                      action="store_true",
                      dest="usb",
                      default=False,
                      help="Compile the USB Device library")

    parser.add_option("-d", "--dsp",
                      action="store_true",
                      dest="dsp",
                      default=False,
                      help="Compile the DSP library")

    parser.add_option("-F", "--fat",
                      action="store_true",
                      dest="fat",
                      default=False,
                      help="Compile FS ad SD card file system library")

    parser.add_option("-b", "--ublox",
                      action="store_true",
                      dest="ublox",
                      default=False,
                      help="Compile the u-blox library")

    parser.add_option("", "--cpputest",
                      action="store_true",
                      dest="cpputest_lib",
                      default=False,
                      help="Compiles 'cpputest' unit test library (library should be on the same directory level as mbed repository)")

    parser.add_option("-D", "",
                      action="append",
                      dest="macros",
                      help="Add a macro definition")

    parser.add_option("-S", "--supported-toolchains",
                      action="store_true",
                      dest="supported_toolchains",
                      default=False,
                      help="Displays supported matrix of MCUs and toolchains")

    parser.add_option("", "--cppcheck",
                      action="store_true",
                      dest="cppcheck_validation",
                      default=False,
                      help="Forces 'cppcheck' static code analysis")

    parser.add_option('-f', '--filter',
                      dest='general_filter_regex',
                      default=None,
                      help='For some commands you can use filter to filter out results')

    parser.add_option("-j", "--jobs", type="int", dest="jobs",
                      default=1, help="Number of concurrent jobs (default 1). Use 0 for auto based on host machine's number of CPUs")

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

    parser.add_option("-x", "--extra-verbose-notifications",
                      action="store_true",
                      dest="extra_verbose_notify",
                      default=False,
                      help="Makes compiler more verbose, CI friendly.")

    (options, args) = parser.parse_args()

    # Only prints matrix of supported toolchains
    if options.supported_toolchains:
        print mcu_toolchain_matrix(platform_filter=options.general_filter_regex)
        exit(0)

    # Get target list
    if options.mcu:
        mcu_list = (options.mcu).split(",")
        for mcu in mcu_list:
            if mcu not in TARGET_NAMES:
                print "Given MCU '%s' not into the supported list:\n%s" % (mcu, TARGET_NAMES)
                sys.exit(1)
        targets = mcu_list
    else:
        targets = TARGET_NAMES

    # Get toolchains list
    if options.tool:
        toolchain_list = (options.tool).split(",")
        for tc in toolchain_list:
            if tc not in TOOLCHAINS:
                print "Given toolchain '%s' not into the supported list:\n%s" % (tc, TOOLCHAINS)
                sys.exit(1)
        toolchains = toolchain_list
    else:
        toolchains = TOOLCHAINS

    # Get libraries list
    libraries = []

    # Additional Libraries
    if options.rtos:
        libraries.extend(["rtx", "rtos"])
    if options.eth:
        libraries.append("eth")
    if options.usb:
        libraries.append("usb")
    if options.usb_host:
        libraries.append("usb_host")
    if options.dsp:
        libraries.extend(["cmsis_dsp", "dsp"])
    if options.fat:
        libraries.extend(["fat"])
    if options.ublox:
        libraries.extend(["rtx", "rtos", "usb_host", "ublox"])
    if options.cpputest_lib:
        libraries.extend(["cpputest"])

    notify = print_notify_verbose if options.extra_verbose_notify else None  # Special notify for CI (more verbose)

    # Build results
    failures = []
    successes = []
    skipped = []

    # CPPCHECK code validation
    if options.cppcheck_validation:
        for toolchain in toolchains:
            for target in targets:
                try:
                    mcu = TARGET_MAP[target]
                    # CMSIS and MBED libs analysis
                    static_analysis_scan(mcu, toolchain, CPPCHECK_CMD, CPPCHECK_MSG_FORMAT, verbose=options.verbose, jobs=options.jobs)
                    for lib_id in libraries:
                        # Static check for library
                        static_analysis_scan_lib(lib_id, mcu, toolchain, CPPCHECK_CMD, CPPCHECK_MSG_FORMAT,
                                  options=options.options,
                                  notify=notify, verbose=options.verbose, jobs=options.jobs, clean=options.clean,
                                  macros=options.macros)
                        pass
                except Exception, e:
                    if options.verbose:
                        import traceback
                        traceback.print_exc(file=sys.stdout)
                        sys.exit(1)
                    print e
    else:
        # Build
        for toolchain in toolchains:
            for target in targets:
                tt_id = "%s::%s" % (toolchain, target)
                try:
                    mcu = TARGET_MAP[target]
                    lib_build_res = build_mbed_libs(mcu, toolchain,
                                                    options=options.options,
                                                    notify=notify,
                                                    verbose=options.verbose,
                                                    silent=options.silent,
                                                    jobs=options.jobs,
                                                    clean=options.clean,
                                                    macros=options.macros)
                    for lib_id in libraries:
                        notify = print_notify_verbose if options.extra_verbose_notify else None  # Special notify for CI (more verbose)
                        build_lib(lib_id, mcu, toolchain,
                                  options=options.options,
                                  notify=notify,
                                  verbose=options.verbose,
                                  silent=options.silent,
                                  clean=options.clean,
                                  macros=options.macros,
                                  jobs=options.jobs)
                    if lib_build_res:
                        successes.append(tt_id)
                    else:
                        skipped.append(tt_id)
                except Exception, e:
                    if options.verbose:
                        import traceback
                        traceback.print_exc(file=sys.stdout)
                        sys.exit(1)
                    failures.append(tt_id)
                    print e

    # Write summary of the builds
    print
    print "Completed in: (%.2f)s" % (time() - start)
    print

    print print_build_results(successes, "Build successes:"),
    print print_build_results(skipped, "Build skipped:"),
    print print_build_results(failures, "Build failures:"),

    if failures:
        sys.exit(1)
