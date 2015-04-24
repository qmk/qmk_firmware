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

Author: Przemyslaw Wirkus <Przemyslaw.wirkus@arm.com>
"""

import sys
import json
import optparse
from flask import Flask
from os.path import join, abspath, dirname

# Be sure that the tools directory is in the search path
ROOT = abspath(join(dirname(__file__), ".."))
sys.path.insert(0, ROOT)

# Imports related to mbed build api
from workspace_tools.utils import construct_enum
from workspace_tools.build_api import mcu_toolchain_matrix

# Imports from TEST API
from test_api import SingleTestRunner
from test_api import SingleTestExecutor
from test_api import get_json_data_from_file
from test_api import print_muts_configuration_from_json
from test_api import print_test_configuration_from_json
from test_api import get_avail_tests_summary_table
from test_api import get_default_test_options_parser


class SingleTestRunnerWebService(SingleTestRunner):
    def __init__(self):
        super(SingleTestRunnerWebService, self).__init__()

        # With this lock we should control access to certain resources inside this class
        self.resource_lock = thread.allocate_lock()

        self.RestRequest = construct_enum(REST_MUTS='muts',
                                          REST_TEST_SPEC='test_spec',
                                          REST_TEST_RESULTS='test_results')

    def get_rest_result_template(self, result, command, success_code):
        """ Returns common part of every web service request
        """
        result = {"result" : result,
                  "command" : command,
                  "success_code": success_code} # 0 - OK, >0 - Error number
        return result

    # REST API handlers for Flask framework
    def rest_api_status(self):
        """ Returns current test execution status. E.g. running / finished etc.
        """
        with self.resource_lock:
            pass

    def rest_api_config(self):
        """ Returns configuration passed to SingleTest executor
        """
        with self.resource_lock:
            pass

    def rest_api_log(self):
        """ Returns current test log """
        with self.resource_lock:
            pass

    def rest_api_request_handler(self, request_type):
        """ Returns various data structures. Both static and mutable during test
        """
        result = {}
        success_code = 0
        with self.resource_lock:
            if request_type == self.RestRequest.REST_MUTS:
                result = self.muts # Returns MUTs
            elif request_type == self.RestRequest.REST_TEST_SPEC:
                result = self.test_spec # Returns Test Specification
            elif request_type == self.RestRequest.REST_TEST_RESULTS:
                pass # Returns test results
            else:
                success_code = -1
        return json.dumps(self.get_rest_result_template(result, 'request/' + request_type, success_code), indent=4)


def singletest_in_webservice_mode():
    # TODO Implement this web service functionality
    pass


def get_default_test_webservice_options_parser():
    """ Get test script web service options used by CLI, webservices etc.
    """
    parser = get_default_test_options_parser()

    # Things related to web services offered by test suite scripts
    parser.add_option('', '--rest-api',
                      dest='rest_api_enabled',
                      default=False,
                      action="store_true",
                      help='Enables REST API.')

    parser.add_option('', '--rest-api-port',
                      dest='rest_api_port_no',
                      help='Sets port for REST API interface')

    return parser

'''
if __name__ == '__main__':
    # Command line options
    parser = get_default_test_options_parser()

    parser.description = """This script allows you to run mbed defined test cases for particular MCU(s) and corresponding toolchain(s)."""
    parser.epilog = """Example: singletest.py -i test_spec.json -M muts_all.json"""

    (opts, args) = parser.parse_args()

    # Print summary / information about automation test status
    if opts.test_automation_report:
        print get_avail_tests_summary_table()
        exit(0)

    # Print summary / information about automation test status
    if opts.test_case_report:
        test_case_report_cols = ['id', 'automated', 'description', 'peripherals', 'host_test', 'duration', 'source_dir']
        print get_avail_tests_summary_table(cols=test_case_report_cols, result_summary=False, join_delim='\n')
        exit(0)

    # Only prints matrix of supported toolchains
    if opts.supported_toolchains:
        print mcu_toolchain_matrix(platform_filter=opts.general_filter_regex)
        exit(0)

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

    # Only prints read MUTs configuration
    if MUTs and opts.verbose_test_configuration_only:
        print "MUTs configuration in %s:"% opts.muts_spec_filename
        print print_muts_configuration_from_json(MUTs)
        print
        print "Test specification in %s:"% opts.test_spec_filename
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
                                   _test_spec=test_spec,
                                   _opts_goanna_for_mbed_sdk=opts.goanna_for_mbed_sdk,
                                   _opts_goanna_for_tests=opts.goanna_for_tests,
                                   _opts_shuffle_test_order=opts.shuffle_test_order,
                                   _opts_shuffle_test_seed=opts.shuffle_test_seed,
                                   _opts_test_by_names=opts.test_by_names,
                                   _opts_test_only_peripheral=opts.test_only_peripheral,
                                   _opts_test_only_common=opts.test_only_common,
                                   _opts_verbose_skipped_tests=opts.verbose_skipped_tests,
                                   _opts_verbose_test_result_only=opts.verbose_test_result_only,
                                   _opts_verbose=opts.verbose,
                                   _opts_firmware_global_name=opts.firmware_global_name,
                                   _opts_only_build_tests=opts.only_build_tests,
                                   _opts_suppress_summary=opts.suppress_summary,
                                   _opts_test_x_toolchain_summary=opts.test_x_toolchain_summary,
                                   _opts_copy_method=opts.copy_method
                                   )

    try:
        st_exec_thread = SingleTestExecutor(single_test)
    except KeyboardInterrupt, e:
        print "\n[CTRL+c] exit"
    st_exec_thread.start()

    if opts.rest_api_enabled:
        # Enable REST API

        app = Flask(__name__)

        @app.route('/')
        def hello_world():
            return 'Hello World!'

        @app.route('/status')
        def rest_api_status():
            return single_test.rest_api_status() # TODO

        @app.route('/config')
        def rest_api_config():
            return single_test.rest_api_config() # TODO

        @app.route('/log')
        def rest_api_log():
            return single_test.rest_api_log() # TODO

        @app.route('/request/<request_type>') # 'muts', 'test_spec', 'test_results'
        def rest_api_request_handler(request_type):
            result = single_test.rest_api_request_handler(request_type) # TODO
            return result

        rest_api_port = int(opts.rest_api_port_no) if opts.rest_api_port_no else 5555
        app.debug = False
        app.run(port=rest_api_port) # Blocking Flask REST API web service
    else:
        st_exec_thread.join()

'''
