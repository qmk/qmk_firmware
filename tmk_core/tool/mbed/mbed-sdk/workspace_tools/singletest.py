#!/usr/bin/env python2

"""
mbed SDK
Copyright (c) 2011-2014 ARM Limited

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Author: Przemyslaw Wirkus <Przemyslaw.Wirkus@arm.com>
"""

"""
File format example: test_spec.json:
{
    "targets": {
        "KL46Z": ["ARM", "GCC_ARM"],
        "LPC1768": ["ARM", "GCC_ARM", "GCC_CR", "GCC_CS", "IAR"],
        "LPC11U24": ["uARM"],
        "NRF51822": ["ARM"]
    }
}

File format example: muts_all.json:
{
    "1" : {"mcu": "LPC1768",
           "port":"COM4",
           "disk":"J:\\",
           "peripherals": ["TMP102", "digital_loop", "port_loop", "analog_loop", "SD"]
    },

    "2" : {"mcu": "KL25Z",
           "port":"COM7",
           "disk":"G:\\",
           "peripherals": ["digital_loop", "port_loop", "analog_loop"]
    }
}
"""


# Be sure that the tools directory is in the search path
import sys
from os.path import join, abspath, dirname

ROOT = abspath(join(dirname(__file__), ".."))
sys.path.insert(0, ROOT)


# Check: Extra modules which are required by core test suite
from workspace_tools.utils import check_required_modules
check_required_modules(['prettytable', 'serial'])

# Imports related to mbed build api
from workspace_tools.build_api import mcu_toolchain_matrix

# Imports from TEST API
from workspace_tools.test_api import SingleTestRunner
from workspace_tools.test_api import singletest_in_cli_mode
from workspace_tools.test_api import detect_database_verbose
from workspace_tools.test_api import get_json_data_from_file
from workspace_tools.test_api import get_avail_tests_summary_table
from workspace_tools.test_api import get_default_test_options_parser
from workspace_tools.test_api import print_muts_configuration_from_json
from workspace_tools.test_api import print_test_configuration_from_json
from workspace_tools.test_api import get_autodetected_MUTS
from workspace_tools.test_api import get_autodetected_TEST_SPEC
from workspace_tools.test_api import get_module_avail

# Importing extra modules which can be not installed but if available they can extend test suite functionality
try:
    import mbed_lstools
except:
    pass

def get_version():
    """ Returns test script version
    """
    single_test_version_major = 1
    single_test_version_minor = 4
    return (single_test_version_major, single_test_version_minor)


if __name__ == '__main__':
    # Command line options
    parser = get_default_test_options_parser()

    parser.description = """This script allows you to run mbed defined test cases for particular MCU(s) and corresponding toolchain(s)."""
    parser.epilog = """Example: singletest.py -i test_spec.json -M muts_all.json"""

    (opts, args) = parser.parse_args()

    # Print scrip version
    if opts.version:
        print parser.description
        print parser.epilog
        print "Version %d.%d"% get_version()
        exit(0)

    if opts.db_url and opts.verbose_test_configuration_only:
        detect_database_verbose(opts.db_url)
        exit(0)

    # Print summary / information about automation test status
    if opts.test_automation_report:
        print get_avail_tests_summary_table(platform_filter=opts.general_filter_regex)
        exit(0)

    # Print summary / information about automation test status
    if opts.test_case_report:
        test_case_report_cols = ['id',
                                 'automated',
                                 'description',
                                 'peripherals',
                                 'host_test',
                                 'duration',
                                 'source_dir']
        print get_avail_tests_summary_table(cols=test_case_report_cols,
                                            result_summary=False,
                                            join_delim='\n',
                                            platform_filter=opts.general_filter_regex)
        exit(0)

    # Only prints matrix of supported toolchains
    if opts.supported_toolchains:
        print mcu_toolchain_matrix(platform_filter=opts.general_filter_regex)
        exit(0)

    test_spec = None
    MUTs = None

    if hasattr(opts, 'auto_detect') and opts.auto_detect:
        # If auto_detect attribute is present, we assume other auto-detection
        # parameters like 'toolchains_filter' are also set.
        print "MBEDLS: Detecting connected mbed-enabled devices... "

        if get_module_avail('mbed_lstools'):
            mbeds = mbed_lstools.create()
            muts_list = mbeds.list_mbeds()
            for mut in muts_list:
                print "MBEDLS: Detected %s, port: %s, mounted: %s"% (mut['platform_name'],
                                        mut['serial_port'],
                                        mut['mount_point'])

        # Set up parameters for test specification filter function (we need to set toolchains per target here)
        use_default_toolchain = 'default' in opts.toolchains_filter.split(',') if opts.toolchains_filter is not None else True
        use_supported_toolchains = 'all' in opts.toolchains_filter.split(',') if opts.toolchains_filter is not None else False
        toolchain_filter = opts.toolchains_filter
        platform_name_filter = opts.general_filter_regex.split(',') if opts.general_filter_regex is not None else opts.general_filter_regex
        # Test specification with information about each target and associated toolchain
        test_spec = get_autodetected_TEST_SPEC(muts_list,
                                               use_default_toolchain=use_default_toolchain,
                                               use_supported_toolchains=use_supported_toolchains,
                                               toolchain_filter=toolchain_filter,
                                               platform_name_filter=platform_name_filter)
        # MUTs configuration auto-detection
        MUTs = get_autodetected_MUTS(muts_list)
    else:
        # Open file with test specification
        # test_spec_filename tells script which targets and their toolchain(s)
        # should be covered by the test scenario
        test_spec = get_json_data_from_file(opts.test_spec_filename) if opts.test_spec_filename else None
        if test_spec is None:
            if not opts.test_spec_filename:
                parser.print_help()
            exit(-1)

        # Get extra MUTs if applicable
        MUTs = get_json_data_from_file(opts.muts_spec_filename) if opts.muts_spec_filename else None

        if MUTs is None:
            if not opts.muts_spec_filename:
                parser.print_help()
            exit(-1)

    if opts.verbose_test_configuration_only:
        print "MUTs configuration in %s:"% ('auto-detected' if opts.auto_detect else opts.muts_spec_filename)
        if MUTs:
            print print_muts_configuration_from_json(MUTs, platform_filter=opts.general_filter_regex)
        print
        print "Test specification in %s:"% ('auto-detected' if opts.auto_detect else opts.test_spec_filename)
        if test_spec:
            print print_test_configuration_from_json(test_spec)
        exit(0)

    # Verbose test specification and MUTs configuration
    if MUTs and opts.verbose:
        print print_muts_configuration_from_json(MUTs)
    if test_spec and opts.verbose:
        print print_test_configuration_from_json(test_spec)

    if opts.only_build_tests:
        # We are skipping testing phase, and suppress summary
        opts.suppress_summary = True

    single_test = SingleTestRunner(_global_loops_count=opts.test_global_loops_value,
                                   _test_loops_list=opts.test_loops_list,
                                   _muts=MUTs,
                                   _clean=opts.clean,
                                   _opts_db_url=opts.db_url,
                                   _opts_log_file_name=opts.log_file_name,
                                   _opts_report_html_file_name=opts.report_html_file_name,
                                   _opts_report_junit_file_name=opts.report_junit_file_name,
                                   _opts_report_build_file_name=opts.report_build_file_name,
                                   _test_spec=test_spec,
                                   _opts_goanna_for_mbed_sdk=opts.goanna_for_mbed_sdk,
                                   _opts_goanna_for_tests=opts.goanna_for_tests,
                                   _opts_shuffle_test_order=opts.shuffle_test_order,
                                   _opts_shuffle_test_seed=opts.shuffle_test_seed,
                                   _opts_test_by_names=opts.test_by_names,
                                   _opts_peripheral_by_names=opts.peripheral_by_names,
                                   _opts_test_only_peripheral=opts.test_only_peripheral,
                                   _opts_test_only_common=opts.test_only_common,
                                   _opts_verbose_skipped_tests=opts.verbose_skipped_tests,
                                   _opts_verbose_test_result_only=opts.verbose_test_result_only,
                                   _opts_verbose=opts.verbose,
                                   _opts_firmware_global_name=opts.firmware_global_name,
                                   _opts_only_build_tests=opts.only_build_tests,
                                   _opts_parallel_test_exec=opts.parallel_test_exec,
                                   _opts_suppress_summary=opts.suppress_summary,
                                   _opts_test_x_toolchain_summary=opts.test_x_toolchain_summary,
                                   _opts_copy_method=opts.copy_method,
                                   _opts_mut_reset_type=opts.mut_reset_type,
                                   _opts_jobs=opts.jobs,
                                   _opts_waterfall_test=opts.waterfall_test,
                                   _opts_extend_test_timeout=opts.extend_test_timeout)

    # Runs test suite in CLI mode
    singletest_in_cli_mode(single_test)
