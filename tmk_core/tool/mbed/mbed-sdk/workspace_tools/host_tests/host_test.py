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

# Check if 'serial' module is installed
try:
    from serial import Serial
except ImportError, e:
    print "Error: Can't import 'serial' module: %s"% e
    exit(-1)

import os
import re
import types
from sys import stdout
from time import sleep, time
from optparse import OptionParser

import host_tests_plugins

# This is a little tricky. We need to add upper directory to path so
# we can find packages we want from the same level as other files do
import sys
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../..')))


class Mbed:
    """ Base class for a host driven test
    """
    def __init__(self):
        parser = OptionParser()

        parser.add_option("-m", "--micro",
                          dest="micro",
                          help="The target microcontroller",
                          metavar="MICRO")

        parser.add_option("-p", "--port",
                          dest="port",
                          help="The serial port of the target mbed",
                          metavar="PORT")

        parser.add_option("-d", "--disk",
                          dest="disk",
                          help="The target disk path",
                          metavar="DISK_PATH")

        parser.add_option("-f", "--image-path",
                          dest="image_path",
                          help="Path with target's image",
                          metavar="IMAGE_PATH")

        parser.add_option("-c", "--copy",
                          dest="copy_method",
                          help="Copy method selector",
                          metavar="COPY_METHOD")

        parser.add_option("-C", "--program_cycle_s",
                          dest="program_cycle_s",
                          help="Program cycle sleep. Define how many seconds you want wait after copying bianry onto target",
                          type="float",
                          metavar="COPY_METHOD")

        parser.add_option("-t", "--timeout",
                          dest="timeout",
                          help="Timeout",
                          metavar="TIMEOUT")

        parser.add_option("-r", "--reset",
                          dest="forced_reset_type",
                          help="Forces different type of reset")

        parser.add_option("-R", "--reset-timeout",
                          dest="forced_reset_timeout",
                          metavar="NUMBER",
                          type="int",
                          help="When forcing a reset using option -r you can set up after reset timeout in seconds")

        (self.options, _) = parser.parse_args()

        self.DEFAULT_RESET_TOUT = 0
        self.DEFAULT_TOUT = 10

        if self.options.port is None:
            raise Exception("The serial port of the target mbed have to be provided as command line arguments")

        # Options related to copy / reset mbed device
        self.port = self.options.port
        self.disk = self.options.disk
        self.image_path = self.options.image_path.strip('"')
        self.copy_method = self.options.copy_method
        self.program_cycle_s = float(self.options.program_cycle_s)

        self.serial = None
        self.serial_baud = 9600
        self.serial_timeout = 1

        self.timeout = self.DEFAULT_TOUT if self.options.timeout is None else self.options.timeout
        print 'MBED: Instrumentation: "%s" and disk: "%s"' % (self.port, self.disk)

    def init_serial_params(self, serial_baud=9600, serial_timeout=1):
        """ Initialize port parameters.
            This parameters will be used by self.init_serial() function to open serial port
        """
        self.serial_baud = serial_baud
        self.serial_timeout = serial_timeout

    def init_serial(self, serial_baud=None, serial_timeout=None):
        """ Initialize serial port.
            Function will return error is port can't be opened or initialized
        """
        # Overload serial port configuration from default to parameters' values if they are specified
        serial_baud = serial_baud if serial_baud is not None else self.serial_baud
        serial_timeout = serial_timeout if serial_timeout is not None else self.serial_timeout

        # Clear serial port
        if self.serial:
            self.serial.close()
            self.serial = None

        # We will pool for serial to be re-mounted if it was unmounted after device reset
        result = self.pool_for_serial_init(serial_baud, serial_timeout) # Blocking

        # Port can be opened
        if result:
            self.flush()
        return result

    def pool_for_serial_init(self, serial_baud, serial_timeout, pooling_loops=40, init_delay=0.5, loop_delay=0.25):
        """ Functions pools for serial port readiness
        """
        result = True
        last_error = None
        # This loop is used to check for serial port availability due to
        # some delays and remounting when devices are being flashed with new software.
        for i in range(pooling_loops):
            sleep(loop_delay if i else init_delay)
            try:
                self.serial = Serial(self.port, baudrate=serial_baud, timeout=serial_timeout)
            except Exception as e:
                result = False
                last_error = "MBED: %s"% str(e)
                stdout.write('.')
                stdout.flush()
            else:
                print "...port ready!"
                result = True
                break
        if not result and last_error:
            print last_error
        return result

    def set_serial_timeout(self, timeout):
        """ Wraps self.mbed.serial object timeout property
        """
        result = None
        if self.serial:
            self.serial.timeout = timeout
            result = True
        return result

    def serial_read(self, count=1):
        """ Wraps self.mbed.serial object read method
        """
        result = None
        if self.serial:
            try:
                result = self.serial.read(count)
            except:
                result = None
        return result

    def serial_readline(self, timeout=5):
        """ Wraps self.mbed.serial object read method to read one line from serial port
        """
        result = ''
        start = time()
        while (time() - start) < timeout:
            if self.serial:
                try:
                    c = self.serial.read(1)
                    result += c
                except Exception as e:
                    print "MBED: %s"% str(e)
                    result = None
                    break
                if c == '\n':
                    break
        return result

    def serial_write(self, write_buffer):
        """ Wraps self.mbed.serial object write method
        """
        result = None
        if self.serial:
            try:
                result = self.serial.write(write_buffer)
            except:
               result = None
        return result

    def reset_timeout(self, timeout):
        """ Timeout executed just after reset command is issued
        """
        for n in range(0, timeout):
            sleep(1)

    def reset(self):
        """ Calls proper reset plugin to do the job.
            Please refer to host_test_plugins functionality
        """
        # Flush serials to get only input after reset
        self.flush()
        if self.options.forced_reset_type:
            result = host_tests_plugins.call_plugin('ResetMethod', self.options.forced_reset_type, disk=self.disk)
        else:
            result = host_tests_plugins.call_plugin('ResetMethod', 'default', serial=self.serial)
        # Give time to wait for the image loading
        reset_tout_s = self.options.forced_reset_timeout if self.options.forced_reset_timeout is not None else self.DEFAULT_RESET_TOUT
        self.reset_timeout(reset_tout_s)
        return result

    def copy_image(self, image_path=None, disk=None, copy_method=None):
        """ Closure for copy_image_raw() method.
            Method which is actually copying image to mbed
        """
        # Set closure environment
        image_path = image_path if image_path is not None else self.image_path
        disk = disk if disk is not None else self.disk
        copy_method = copy_method if copy_method is not None else self.copy_method
        # Call proper copy method
        result = self.copy_image_raw(image_path, disk, copy_method)
        sleep(self.program_cycle_s)
        return result

    def copy_image_raw(self, image_path=None, disk=None, copy_method=None):
        """ Copy file depending on method you want to use. Handles exception
            and return code from shell copy commands.
        """
        if copy_method is not None:
            # image_path - Where is binary with target's firmware
            result = host_tests_plugins.call_plugin('CopyMethod', copy_method, image_path=image_path, destination_disk=disk)
        else:
            copy_method = 'default'
            result = host_tests_plugins.call_plugin('CopyMethod', copy_method, image_path=image_path, destination_disk=disk)
        return result;

    def flush(self):
        """ Flush serial ports
        """
        result = False
        if self.serial:
            self.serial.flushInput()
            self.serial.flushOutput()
            result = True
        return result


class HostTestResults:
    """ Test results set by host tests
    """
    def __init__(self):
        self.RESULT_SUCCESS = 'success'
        self.RESULT_FAILURE = 'failure'
        self.RESULT_ERROR = 'error'
        self.RESULT_IO_SERIAL = 'ioerr_serial'
        self.RESULT_NO_IMAGE = 'no_image'
        self.RESULT_IOERR_COPY = "ioerr_copy"
        self.RESULT_PASSIVE = "passive"
        self.RESULT_NOT_DETECTED = "not_detected"
        self.RESULT_MBED_ASSERT = "mbed_assert"


import workspace_tools.host_tests as host_tests


class Test(HostTestResults):
    """ Base class for host test's test runner
    """
    # Select default host_test supervision (replaced after autodetection)
    test_supervisor = host_tests.get_host_test("default")

    def __init__(self):
        self.mbed = Mbed()

    def detect_test_config(self, verbose=False):
        """ Detects test case configuration
        """
        result = {}
        while True:
            line = self.mbed.serial_readline()
            if "{start}" in line:
                self.notify("HOST: Start test...")
                break
            else:
                # Detect if this is property from TEST_ENV print
                m = re.search('{([\w_]+);([\w\d\+ ]+)}}', line[:-1])
                if m and len(m.groups()) == 2:
                    # This is most likely auto-detection property
                    result[m.group(1)] = m.group(2)
                    if verbose:
                        self.notify("HOST: Property '%s' = '%s'"% (m.group(1), m.group(2)))
                else:
                    # We can check if this is TArget Id in mbed specific format
                    m2 = re.search('^([\$]+)([a-fA-F0-9]+)', line[:-1])
                    if m2 and len(m2.groups()) == 2:
                        if verbose:
                            target_id = m2.group(1) + m2.group(2)
                            self.notify("HOST: TargetID '%s'"% target_id)
                            self.notify(line[len(target_id):-1])
                    else:
                        self.notify("HOST: Unknown property: %s"% line.strip())
        return result

    def run(self):
        """ Test runner for host test. This function will start executing
            test and forward test result via serial port to test suite
        """
        # Copy image to device
        self.notify("HOST: Copy image onto target...")
        result = self.mbed.copy_image()
        if not result:
            self.print_result(self.RESULT_IOERR_COPY)

        # Initialize and open target's serial port (console)
        self.notify("HOST: Initialize serial port...")
        result = self.mbed.init_serial()
        if not result:
            self.print_result(self.RESULT_IO_SERIAL)

        # Reset device
        self.notify("HOST: Reset target...")
        result = self.mbed.reset()
        if not result:
            self.print_result(self.RESULT_IO_SERIAL)

        # Run test
        try:
            CONFIG = self.detect_test_config(verbose=True) # print CONFIG

            if "host_test_name" in CONFIG:
                if host_tests.is_host_test(CONFIG["host_test_name"]):
                    self.test_supervisor = host_tests.get_host_test(CONFIG["host_test_name"])
            result = self.test_supervisor.test(self)    #result = self.test()

            if result is not None:
                self.print_result(result)
            else:
                self.notify("HOST: Passive mode...")
        except Exception, e:
            print str(e)
            self.print_result(self.RESULT_ERROR)

    def setup(self):
        """ Setup and check if configuration for test is
            correct. E.g. if serial port can be opened.
        """
        result = True
        if not self.mbed.serial:
            result = False
            self.print_result(self.RESULT_IO_SERIAL)
        return result

    def notify(self, message):
        """ On screen notification function
        """
        print message
        stdout.flush()

    def print_result(self, result):
        """ Test result unified printing function
        """
        self.notify("\r\n{{%s}}\r\n{{end}}" % result)


class DefaultTestSelector(Test):
    """ Test class with serial port initialization
    """
    def __init__(self):
        HostTestResults.__init__(self)
        Test.__init__(self)

if __name__ == '__main__':
    DefaultTestSelector().run()
