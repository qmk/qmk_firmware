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
from host_test import Test


class EchoTest(Test):
    def __init__(self):
        Test.__init__(self)
        self.mbed.init_serial()
        self.mbed.extra_serial.rtscts = True
        self.mbed.reset()

    def test(self):
        self.mbed.flush()
        self.notify("Starting the ECHO test")
        TEST="longer serial test"
        check = True
        for i in range(1, 100):
            self.mbed.extra_serial.write(TEST + "\n")
            l = self.mbed.extra_serial.readline().strip()
            if not l: continue

            if l != TEST:
                check = False
                self.notify('"%s" != "%s"' % (l, TEST))
            else:
                if (i % 10) == 0:
                    self.notify('.')

        return check


if __name__ == '__main__':
    EchoTest().run()
