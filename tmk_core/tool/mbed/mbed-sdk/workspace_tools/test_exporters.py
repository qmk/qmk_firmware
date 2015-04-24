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

from workspace_tools.utils import construct_enum


ResultExporterType = construct_enum(HTML='Html_Exporter',
                                    JUNIT='JUnit_Exporter')


class ReportExporter():
    """ Class exports extended test result Python data structure to
        different formats like HTML, JUnit XML.

    Parameter 'test_result_ext' format:

    u'uARM': {   u'LPC1768': {   'MBED_2': {   0: {   'copy_method': 'shutils.copy()',
                                                      'duration': 20,
                                                      'elapsed_time': 1.7929999828338623,
                                                      'single_test_output': 'Host test instrumentation on ...\r\n',
                                                      'single_test_result': 'OK',
                                                      'target_name': u'LPC1768',
                                                      'test_description': 'stdio',
                                                      'test_id': u'MBED_2',
                                                      'toolchain_name': u'uARM'}},
    """
    CSS_STYLE = """<style>
                   .name{
                    border: 1px solid;
                    border-radius: 25px;
                    width: 100px;
                   }
                   .tooltip{
                       position:absolute;
                       background-color: #F5DA81;
                       display:none;
                   }
                   </style>
                """

    JAVASCRIPT = """
                 <script type="text/javascript">
                 function show (elem) {
                     elem.style.display = "block";
                 }
                 function hide (elem) {
                     elem.style.display = "";
                 }
                 </script>
                 """

    def __init__(self, result_exporter_type):
        self.result_exporter_type = result_exporter_type

    def report(self, test_summary_ext, test_suite_properties=None):
        """ Invokes report depending on exporter_type set in constructor
        """
        if self.result_exporter_type == ResultExporterType.HTML:
            # HTML exporter
            return self.exporter_html(test_summary_ext, test_suite_properties)
        elif self.result_exporter_type == ResultExporterType.JUNIT:
            # JUNIT exporter
            return self.exporter_junit(test_summary_ext, test_suite_properties)
        return None

    def report_to_file(self, test_summary_ext, file_name, test_suite_properties=None):
        """ Stores report to specified file
        """
        report = self.report(test_summary_ext, test_suite_properties=test_suite_properties)
        if report is not None:
            with open(file_name, 'w') as f:
                f.write(report)

    def get_tooltip_name(self, toolchain, target, test_id, loop_no):
        """ Generate simple unique tool-tip name which can be used.
            For example as HTML <div> section id attribute.
        """
        return "target_test_%s_%s_%s_%d"% (toolchain.lower(), target.lower(), test_id.lower(), loop_no)

    def get_result_div_sections(self, test, test_no):
        """ Generates separate <dvi> sections which contains test results output.
        """

        RESULT_COLORS = {'OK' : 'LimeGreen',
                         'FAIL' : 'Orange',
                         'ERROR' : 'LightCoral',}

        tooltip_name = self.get_tooltip_name(test['toolchain_name'], test['target_name'], test['test_id'], test_no)
        background_color = RESULT_COLORS[test['single_test_result'] if test['single_test_result'] in RESULT_COLORS else 'ERROR']
        result_div_style = "background-color: %s"% background_color

        result = """<div class="name" style="%s" onmouseover="show(%s)" onmouseout="hide(%s)">
                       <center>%s</center>
                       <div class = "tooltip" id= "%s">
                       <b>%s</b> in <b>%.2f sec</b><br />
                       <hr />
                       <small>
                       %s
                       </small>
                       </div>
                    </div>
                 """% (result_div_style,
                       tooltip_name,
                       tooltip_name,
                       test['single_test_result'],
                       tooltip_name,
                       test['test_description'],
                       test['elapsed_time'],
                       test['single_test_output'].replace('\n', '<br />'))
        return result

    def get_result_tree(self, test_results):
        """ If test was run in a loop (we got few results from the same test)
            we will show it in a column to see all results.
            This function produces HTML table with corresponding results.
        """
        result = '<table>'
        test_ids = sorted(test_results.keys())
        for test_no in test_ids:
            test = test_results[test_no]
            result += """<tr>
                             <td valign="top">%s</td>
                         </tr>"""% self.get_result_div_sections(test, test_no)
        result += '</table>'
        return result

    def get_all_unique_test_ids(self, test_result_ext):
        """ Gets all unique test ids from all ran tests.
            We need this to create complete list of all test ran.
        """
        result = []
        toolchains = test_result_ext.keys()
        for toolchain in toolchains:
            targets = test_result_ext[toolchain].keys()
            for target in targets:
                tests = test_result_ext[toolchain][target].keys()
                result.extend(tests)
        return sorted(list(set(result)))

    #
    # Exporters functions
    #

    def exporter_html(self, test_result_ext, test_suite_properties=None):
        """ Export test results in proprietary html format.
        """
        result = """<html>
                    <head>
                        <title>mbed SDK test suite test result report</title>
                        %s
                        %s
                    </head>
                    <body>
                 """% (self.CSS_STYLE, self.JAVASCRIPT)

        unique_test_ids = self.get_all_unique_test_ids(test_result_ext)
        toolchains = sorted(test_result_ext.keys())
        result += '<table><tr>'
        for toolchain in toolchains:
            targets = sorted(test_result_ext[toolchain].keys())
            for target in targets:
                result += '<td></td>'
                result += '<td></td>'

                tests = sorted(test_result_ext[toolchain][target].keys())
                for test in unique_test_ids:
                    result += """<td align="center">%s</td>"""% test
                result += """</tr>
                              <tr>
                              <td valign="center">%s</td>
                              <td valign="center"><b>%s</b></td>
                          """% (toolchain, target)

                for test in unique_test_ids:
                    test_result = self.get_result_tree(test_result_ext[toolchain][target][test]) if test in tests else ''
                    result += '<td>%s</td>'% (test_result)

                result += '</tr>'
        result += '</table>'
        result += '</body></html>'
        return result

    def exporter_junit(self, test_result_ext, test_suite_properties=None):
        """ Export test results in JUnit XML compliant format
        """
        from junit_xml import TestSuite, TestCase
        test_suites = []
        test_cases = []

        toolchains = sorted(test_result_ext.keys())
        for toolchain in toolchains:
            targets = sorted(test_result_ext[toolchain].keys())
            for target in targets:
                test_cases = []
                tests = sorted(test_result_ext[toolchain][target].keys())
                for test in tests:
                    test_results = test_result_ext[toolchain][target][test]
                    test_ids = sorted(test_results.keys())
                    for test_no in test_ids:
                        test_result = test_results[test_no]
                        name = test_result['test_description']
                        classname = 'test.%s.%s.%s'% (target, toolchain, test_result['test_id'])
                        elapsed_sec = test_result['elapsed_time']
                        _stdout = test_result['single_test_output']
                        _stderr = ''
                        # Test case
                        tc = TestCase(name, classname, elapsed_sec, _stdout, _stderr)
                        # Test case extra failure / error info
                        if test_result['single_test_result'] == 'FAIL':
                            message = test_result['single_test_result']
                            tc.add_failure_info(message, _stdout)
                        elif test_result['single_test_result'] != 'OK':
                            message = test_result['single_test_result']
                            tc.add_error_info(message, _stdout)

                        test_cases.append(tc)
                ts = TestSuite("test.suite.%s.%s"% (target, toolchain), test_cases, properties=test_suite_properties[target][toolchain])
                test_suites.append(ts)
        return TestSuite.to_xml_string(test_suites)
