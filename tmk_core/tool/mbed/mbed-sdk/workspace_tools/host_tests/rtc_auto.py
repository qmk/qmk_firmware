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
from time import time, strftime, gmtime

class RTCTest():
    PATTERN_RTC_VALUE = "\[(\d+)\] \[(\d+-\d+-\d+ \d+:\d+:\d+ [AaPpMm]{2})\]"
    re_detect_rtc_value = re.compile(PATTERN_RTC_VALUE)

    def test(self, selftest):
        test_result = True
        start = time()
        sec_prev = 0
        for i in range(0, 5):
            # Timeout changed from default: we need to wait longer for some boards to start-up
            c = selftest.mbed.serial_readline(timeout=10)
            if c is None:
                return selftest.RESULT_IO_SERIAL
            selftest.notify(c.strip())
            delta = time() - start
            m = self.re_detect_rtc_value.search(c)
            if m and len(m.groups()):
                sec = int(m.groups()[0])
                time_str = m.groups()[1]
                correct_time_str = strftime("%Y-%m-%d %H:%M:%S %p", gmtime(float(sec)))
                single_result = time_str == correct_time_str and sec > 0 and sec > sec_prev
                test_result = test_result and single_result
                result_msg = "OK" if single_result else "FAIL"
                selftest.notify("HOST: [%s] [%s] received time %+d sec after %.2f sec... %s"% (sec, time_str, sec - sec_prev, delta, result_msg))
                sec_prev = sec
            else:
                test_result = False
                break
            start = time()
        return selftest.RESULT_SUCCESS if test_result else selftest.RESULT_FAILURE
