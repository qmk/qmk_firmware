"""
mbed SDK
Copyright (c) 2010-2013 ARM Limited

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


Example:
> from mbedRPC import*
> mbed = SerialRPC("COM5",9600);
> myled = DigitalOut(mbed, LED1);
> myled.write(1)
>
"""
import serial, urllib2, time


class pin():
    def __init__(self, id):
        self.name = id

LED1 = pin("LED1")
LED2 = pin("LED2")
LED3 = pin("LED3")
LED4 = pin("LED4")

p5 = pin("p5")
p6 = pin("p6")
p7 = pin("p7")
p8 = pin("p8")
p9 = pin("p9")
p10 = pin("p10")
p11 = pin("p11")
p12 = pin("p12")
p13 = pin("p13")
p14 = pin("p14")
p15 = pin("p15")
p16 = pin("p16")
p17 = pin("p17")
p18 = pin("p18")
p19 = pin("p19")
p20 = pin("p20")
p21 = pin("p21")
p22 = pin("p22")
p23 = pin("p23")
p24 = pin("p24")
p25 = pin("p25")
p26 = pin("p26")
p27 = pin("p27")
p28 = pin("p28")
p29 = pin("p29")
p30 = pin("p30")


#mbed super class
class mbed:
    def __init__(self):
            print("This will work as a demo but no transport mechanism has been selected")

    def rpc(self, name, method, args):
            print("Superclass method not overridden")

#Transport mechanisms, derived from mbed

class SerialRPC(mbed):
    def __init__(self, port, baud=9600, reset=True, debug=False):
        self.ser = serial.Serial(port)
        self.ser.setBaudrate(baud)
        self.ser.flushInput()
        self.ser.flushOutput()
        self.debug = debug
        if reset:
            if debug:
                print "Reset mbed"
            self.ser.sendBreak()
            time.sleep(2)

    def rpc(self, name, method, args):
        request = "/" + name + "/" + method + " " + " ".join(args)
        if self.debug:
            print "[RPC::TX] %s" % request
        self.ser.write(request + "\n")

        while True:
            response = self.ser.readline().strip()
            if self.debug:
                print "[RPC::RX] %s" % response

            # Ignore comments
            if not response.startswith('#'): break
        return response


class HTTPRPC(mbed):
    def __init__(self, ip):
        self.host = "http://" + ip

    def rpc(self, name, method, args):
        response = urllib2.urlopen(self.host + "/rpc/" + name + "/" + method + "," + ",".join(args))
        return response.read().strip()


#mbed Interfaces

class DigitalOut():
    def __init__(self, this_mbed , mpin):
        self.mbed = this_mbed
        if isinstance(mpin, str):
            self.name = mpin
        elif isinstance(mpin, pin):
            self.name = self.mbed.rpc("DigitalOut", "new", [mpin.name])

    def __del__(self):
        r = self.mbed.rpc(self.name, "delete", [])

    def write(self, value):
        r = self.mbed.rpc(self.name, "write", [str(value)])

    def read(self):
        r = self.mbed.rpc(self.name, "read", [])
        return int(r)


class AnalogIn():
    def __init__(self, this_mbed , mpin):
        self.mbed = this_mbed
        if isinstance(mpin, str):
            self.name = mpin
        elif isinstance(mpin, pin):
            self.name = self.mbed.rpc("AnalogIn", "new", [mpin.name])

    def __del__(self):
        r = self.mbed.rpc(self.name, "delete", [])

    def read(self):
        r = self.mbed.rpc(self.name, "read", [])
        return float(r)

    def read_u16(self):
        r = self.mbed.rpc(self.name, "read_u16", [])
        return int(r)


class AnalogOut():
    def __init__(self, this_mbed , mpin):
        self.mbed = this_mbed
        if isinstance(mpin, str):
            self.name = mpin
        elif isinstance(mpin, pin):
            self.name = self.mbed.rpc("AnalogOut", "new", [mpin.name])

    def __del__(self):
        r = self.mbed.rpc(self.name, "delete", [])

    def write(self, value):
        r = self.mbed.rpc(self.name, "write", [str(value)])

    def write_u16(self, value):
        r = self.mbed.rpc(self.name, "write_u16", [str(value)])

    def read(self):
        r = self.mbed.rpc(self.name, "read", [])
        return float(r)


class DigitalIn():
    def __init__(self, this_mbed , mpin):
        self.mbed = this_mbed
        if isinstance(mpin, str):
            self.name = mpin
        elif isinstance(mpin, pin):
            self.name = self.mbed.rpc("DigitalIn", "new", [mpin.name])

    def __del__(self):
        r = self.mbed.rpc(self.name, "delete", [])

    def read(self):
        r = self.mbed.rpc(self.name, "read", [])
        return int(r)


class PwmOut():
    def __init__(self, this_mbed , mpin):
        self.mbed = this_mbed
        if isinstance(mpin, str):
            self.name = mpin
        elif isinstance(mpin, pin):
            self.name = self.mbed.rpc("PwmOut", "new", [mpin.name])

    def __del__(self):
        r = self.mbed.rpc(self.name, "delete", [])

    def write(self, value):
        r = self.mbed.rpc(self.name, "write", [str(value)])

    def read(self):
        r = self.mbed.rpc(self.name, "read", [])
        return float(r)

    def period(self, value):
        r = self.mbed.rpc(self.name, "period", [str(value)])

    def period_ms(self, value):
        r = self.mbed.rpc(self.name, "period_ms", [str(value)])

    def period_us(self, value):
        r = self.mbed.rpc(self.name, "period_us", [str(value)])

    def puslewidth(self, value):
        r = self.mbed.rpc(self.name, "pulsewidth", [str(value)])

    def puslewidth_ms(self, value):
        r = self.mbed.rpc(self.name, "pulsewidth_ms", [str(value)])

    def puslewidth_us(self, value):
        r = self.mbed.rpc(self.name, "pulsewidth_us", [str(value)])


class Serial():
    def __init__(self, this_mbed , tx, rx = ""):
        self.mbed = this_mbed
        if isinstance(tx, str):
            self.name = mpin
        elif isinstance(mpin, pin):
            self.name = self.mbed.rpc("Serial", "new", [tx.name, rx.name])

    def __del__(self):
        r = self.mbed.rpc(self.name, "delete", [])

    def putc(self, value):
        r = self.mbed.rpc(self.name, "putc", [str(value)])

    def puts(self, value):
        r = self.mbed.rpc(self.name, "puts", [ "\"" + str(value) + "\""])

    def getc(self):
        r = self.mbed.rpc(self.name, "getc", [])
        return int(r)


class RPCFunction():
    def __init__(self, this_mbed , name):
        self.mbed = this_mbed
        if isinstance(name, str):
            self.name = name

    def __del__(self):
        r = self.mbed.rpc(self.name, "delete", [])

    def read(self):
        r = self.mbed.rpc(self.name, "read", [])
        return int(r)

    def run(self, input):
        r = self.mbed.rpc(self.name, "run", [input])
        return r


class RPCVariable():
    def __init__(self, this_mbed , name):
        self.mbed = this_mbed
        if isinstance(name, str):
            self.name = name

    def __del__(self):
        r = self.mbed.rpc(self.name, "delete", [])

    def write(self, value):
        self.mbed.rpc(self.name, "write", [str(value)])

    def read(self):
        r = self.mbed.rpc(self.name, "read", [])
        return r


def wait(s):
    time.sleep(s)
