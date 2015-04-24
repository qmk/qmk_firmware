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
"""
import sys
from time import time
from os.path import join, abspath, dirname
from optparse import OptionParser

# Be sure that the tools directory is in the search path
ROOT = abspath(join(dirname(__file__), ".."))
sys.path.insert(0, ROOT)

from workspace_tools.build_api import build_mbed_libs
from workspace_tools.build_api import write_build_report
from workspace_tools.targets import TARGET_MAP

OFFICIAL_MBED_LIBRARY_BUILD = (
    ('LPC11U24',     ('ARM', 'uARM', 'GCC_ARM', 'IAR')),
    ('LPC1768',      ('ARM', 'GCC_ARM', 'GCC_CR', 'GCC_CS', 'IAR')),
    ('UBLOX_C027',   ('ARM', 'GCC_ARM', 'GCC_CR', 'GCC_CS', 'IAR')),
    ('ARCH_PRO',     ('ARM', 'GCC_ARM', 'GCC_CR', 'GCC_CS', 'IAR')),
    ('LPC2368',      ('ARM', 'GCC_ARM')),
    ('LPC812',       ('uARM','IAR')),
    ('LPC824',       ('uARM', 'GCC_ARM', 'IAR', 'GCC_CR')),
    ('SSCI824',      ('uARM','GCC_ARM')),
    ('LPC1347',      ('ARM','IAR')),
    ('LPC4088',      ('ARM', 'GCC_ARM', 'GCC_CR', 'IAR')),
    ('LPC4088_DM',   ('ARM', 'GCC_ARM', 'GCC_CR', 'IAR')),
    ('LPC1114',      ('uARM','GCC_ARM', 'GCC_CR', 'IAR')),
    ('LPC11U35_401', ('ARM', 'uARM','GCC_ARM','GCC_CR', 'IAR')),
    ('LPC11U35_501', ('ARM', 'uARM','GCC_ARM','GCC_CR', 'IAR')),
    ('LPC1549',      ('uARM','GCC_ARM','GCC_CR', 'IAR')),
    ('XADOW_M0',     ('ARM', 'uARM','GCC_ARM','GCC_CR')),
    ('ARCH_GPRS',    ('ARM', 'uARM', 'GCC_ARM', 'GCC_CR', 'IAR')),
    ('LPC4337',      ('ARM',)),
    ('LPC11U37H_401', ('ARM', 'uARM','GCC_ARM','GCC_CR', 'IAR')),

    ('KL05Z',        ('ARM', 'uARM', 'GCC_ARM', 'IAR')),
    ('KL25Z',        ('ARM', 'GCC_ARM', 'IAR')),
    ('KL43Z',        ('ARM', 'GCC_ARM')),
    ('KL46Z',        ('ARM', 'GCC_ARM', 'IAR')),
    ('K64F',         ('ARM', 'GCC_ARM', 'IAR')),
    ('K22F',         ('ARM', 'GCC_ARM', 'IAR')),
    ('K20D50M',      ('ARM', 'GCC_ARM' , 'IAR')),
    ('TEENSY3_1',      ('ARM', 'GCC_ARM')),

    ('NUCLEO_F030R8', ('ARM', 'uARM', 'IAR', 'GCC_ARM')),
    ('NUCLEO_F070RB', ('ARM', 'uARM', 'IAR', 'GCC_ARM')),
    ('NUCLEO_F072RB', ('ARM', 'uARM', 'IAR', 'GCC_ARM')),
    ('NUCLEO_F091RC', ('ARM', 'uARM', 'IAR', 'GCC_ARM')),
    ('NUCLEO_F103RB', ('ARM', 'uARM', 'IAR', 'GCC_ARM')),
    ('NUCLEO_F302R8', ('ARM', 'uARM', 'IAR', 'GCC_ARM')),
    ('NUCLEO_F303RE', ('ARM', 'uARM', 'IAR')),
    ('NUCLEO_F334R8', ('ARM', 'uARM', 'IAR', 'GCC_ARM')),
    ('NUCLEO_F401RE', ('ARM', 'uARM', 'IAR', 'GCC_ARM')),
    ('NUCLEO_F411RE', ('ARM', 'uARM', 'IAR', 'GCC_ARM')),
    ('NUCLEO_L053R8', ('ARM', 'uARM', 'IAR', 'GCC_ARM')),
    ('NUCLEO_L152RE', ('ARM', 'uARM', 'IAR', 'GCC_ARM')),
    ('MTS_MDOT_F405RG', ('ARM', 'uARM', 'IAR', 'GCC_ARM')),
    ('MTS_MDOT_F411RE', ('ARM', 'uARM', 'IAR', 'GCC_ARM')),

    ('ARCH_MAX',     ('ARM', 'GCC_ARM')),

    ('NRF51822',     ('ARM', 'GCC_ARM', 'IAR')),
    ('NRF51_DK',     ('ARM', 'GCC_ARM', 'IAR')),
    ('NRF51_DONGLE', ('ARM', 'GCC_ARM', 'IAR')),
    ('HRM1017',      ('ARM', 'GCC_ARM', 'IAR')),
    ('ARCH_BLE',     ('ARM', 'GCC_ARM', 'IAR')),
    ('SEEED_TINY_BLE', ('ARM', 'GCC_ARM', 'IAR')),
    ('RBLAB_NRF51822', ('ARM', 'GCC_ARM')),
    ('RBLAB_BLENANO', ('ARM', 'GCC_ARM')),
    ('WALLBOT_BLE',  ('ARM', 'GCC_ARM')),

    ('LPC11U68',     ('ARM', 'uARM','GCC_ARM','GCC_CR', 'IAR')),
    ('OC_MBUINO',     ('ARM', 'uARM', 'GCC_ARM', 'IAR')),

    ('RZ_A1H'   ,     ('ARM', 'GCC_ARM')),
)


if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option('-o', '--official', dest="official_only", default=False, action="store_true",
                      help="Build using only the official toolchain for each target")
    parser.add_option("-j", "--jobs", type="int", dest="jobs",
                      default=1, help="Number of concurrent jobs (default 1). Use 0 for auto based on host machine's number of CPUs")
    parser.add_option("-v", "--verbose", action="store_true", dest="verbose",
                      default=False, help="Verbose diagnostic output")
    parser.add_option("-t", "--toolchains", dest="toolchains", help="Use toolchains names separated by comma")

    parser.add_option("", "--report-build", dest="report_build_file_name", help="Output the build results to an html file")


    options, args = parser.parse_args()
    start = time()
    failures = []
    successes = []
    skips = []
    build_report = []
    for target_name, toolchain_list in OFFICIAL_MBED_LIBRARY_BUILD:
        if options.official_only:
            toolchains = (getattr(TARGET_MAP[target_name], 'default_toolchain', 'ARM'),)
        else:
            toolchains = toolchain_list

        if options.toolchains:
            print "Only building using the following toolchains: %s" % (options.toolchains)
            toolchainSet = set(toolchains)
            toolchains = toolchainSet and set((options.toolchains).split(','))


        cur_target_build_report = { "target": target_name, "passing": [], "failing": [], "skipped": []}

        for toolchain in toolchains:
            id = "%s::%s" % (target_name, toolchain)
            try:
                built_mbed_lib = build_mbed_libs(TARGET_MAP[target_name], toolchain, verbose=options.verbose, jobs=options.jobs)

                if built_mbed_lib:
                    successes.append(id)
                    cur_target_build_report["passing"].append({ "toolchain": toolchain })
                else:
                    skips.append(id)
                    cur_target_build_report["skipped"].append({ "toolchain": toolchain })


            except Exception, e:
                failures.append(id)
                cur_target_build_report["failing"].append({ "toolchain": toolchain })
                print e

        if len(toolchains) > 0:
            build_report.append(cur_target_build_report)

    # Write summary of the builds

    if options.report_build_file_name:
        write_build_report(build_report, 'library_build/report.html', options.report_build_file_name)

    print "\n\nCompleted in: (%.2f)s" % (time() - start)

    if successes:
        print "\n\nBuild successes:"
        print "\n".join(["  * %s" % s for s in successes])

    if skips:
        print "\n\nBuild skips:"
        print "\n".join(["  * %s" % s for s in skips])

    if failures:
        print "\n\nBuild failures:"
        print "\n".join(["  * %s" % f for f in failures])
        sys.exit(1)
