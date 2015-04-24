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

class DevNullTest():

    def check_readline(self, selftest, text):
        """ Reads line from serial port and checks if text was part of read string
        """
        result = False
        c = selftest.mbed.serial_readline()
        if c and text in c:
            result = True
        return result

    def test(self, selftest):
        result = True
        # Test should print some text and later stop printing
        # 'MBED: re-routing stdout to /null'
        res = self.check_readline(selftest, "re-routing stdout to /null")
        if not res:
            # We haven't read preamble line
            result = False
        else:
            # Check if there are printed characters
            str = ''
            for i in range(3):
                c = selftest.mbed.serial_read(32)
                if c is None:
                    return selftest.RESULT_IO_SERIAL
                else:
                    str += c
                if len(str) > 0:
                    result = False
                    break
            selftest.notify("Received %d bytes: %s"% (len(str), str))
        return selftest.RESULT_SUCCESS if result else selftest.RESULT_FAILURE
