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
from mbedrpc import SerialRPC, DigitalOut, DigitalIn, pin


class RpcTest(Test):
    def test(self):
        self.notify("RPC Test")
        s = SerialRPC(self.mbed.port, debug=True)

        self.notify("Init remote objects")

        p_out = pin("p10")
        p_in  = pin("p11")

        if hasattr(self.mbed.options, 'micro'):
            if self.mbed.options.micro == 'M0+':
                print "Freedom Board: PTA12 <-> PTC4"
                p_out = pin("PTA12")
                p_in  = pin("PTC4")

        self.output = DigitalOut(s, p_out);
        self.input = DigitalIn(s, p_in);

        self.check = True
        self.write_read_test(1)
        self.write_read_test(0)
        return self.check

    def write_read_test(self, v):
        self.notify("Check %d" % v)
        self.output.write(v)
        if self.input.read() != v:
            self.notify("ERROR")
            self.check = False
        else:
            self.notify("OK")


if __name__ == '__main__':
    RpcTest().run()
