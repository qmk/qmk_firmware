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

from host_test_plugins import HostTestPluginBase


class HostTestPluginResetMethod_Mbed(HostTestPluginBase):

    def safe_sendBreak(self, serial):
        """ Wraps serial.sendBreak() to avoid serial::serialposix.py exception on Linux
            Traceback (most recent call last):
              File "make.py", line 189, in <module>
                serial.sendBreak()
              File "/usr/lib/python2.7/dist-packages/serial/serialposix.py", line 511, in sendBreak
                termios.tcsendbreak(self.fd, int(duration/0.25))
            error: (32, 'Broken pipe')
        """
        result = True
        try:
            serial.sendBreak()
        except:
            # In linux a termios.error is raised in sendBreak and in setBreak.
            # The following setBreak() is needed to release the reset signal on the target mcu.
            try:
                serial.setBreak(False)
            except:
                result = False
        return result

    # Plugin interface
    name = 'HostTestPluginResetMethod_Mbed'
    type = 'ResetMethod'
    stable = True
    capabilities = ['default']
    required_parameters = ['serial']

    def setup(self, *args, **kwargs):
        """ Configure plugin, this function should be called before plugin execute() method is used.
        """
        return True

    def execute(self, capabilitity, *args, **kwargs):
        """ Executes capability by name.
            Each capability may directly just call some command line
            program or execute building pythonic function
        """
        result = False
        if self.check_parameters(capabilitity, *args, **kwargs) is True:
            if capabilitity == 'default':
                serial = kwargs['serial']
                result = self.safe_sendBreak(serial)
        return result


def load_plugin():
    """ Returns plugin available in this module
    """
    return HostTestPluginResetMethod_Mbed()
