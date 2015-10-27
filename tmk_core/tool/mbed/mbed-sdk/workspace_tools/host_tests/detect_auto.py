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

import re

class DetectPlatformTest():
    PATTERN_MICRO_NAME = "Target '(\w+)'"
    re_detect_micro_name = re.compile(PATTERN_MICRO_NAME)

    def test(self, selftest):
        result = True

        c = selftest.mbed.serial_readline() # {{start}} preamble
        if c is None:
           return selftest.RESULT_IO_SERIAL

        selftest.notify(c.strip())
        selftest.notify("HOST: Detecting target name...")

        c = selftest.mbed.serial_readline()
        if c is None:
            return selftest.RESULT_IO_SERIAL
        selftest.notify(c.strip())

        # Check for target name
        m = self.re_detect_micro_name.search(c)
        if m and len(m.groups()):
            micro_name = m.groups()[0]
            micro_cmp = selftest.mbed.options.micro == micro_name
            result = result and micro_cmp
            selftest.notify("HOST: MUT Target name '%s', expected '%s'... [%s]"% (micro_name,
                selftest.mbed.options.micro,
                "OK" if micro_cmp else "FAIL"))

        for i in range(0, 2):
            c = selftest.mbed.serial_readline()
            if c is None:
               return selftest.RESULT_IO_SERIAL
            selftest.notify(c.strip())

        return selftest.RESULT_SUCCESS if result else selftest.RESULT_FAILURE
