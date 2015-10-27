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

from os import access, F_OK
from sys import stdout
from time import sleep
from subprocess import call


class HostTestPluginBase:
    """ Base class for all plug-ins used with host tests.
    """
    ###########################################################################
    # Interface:
    ###########################################################################

    ###########################################################################
    # Interface attributes defining plugin name, type etc.
    ###########################################################################
    name = "HostTestPluginBase" # Plugin name, can be plugin class name
    type = "BasePlugin"         # Plugin type: ResetMethod, Copymethod etc.
    capabilities = []           # Capabilities names: what plugin can achieve
                                # (e.g. reset using some external command line tool)
    stable = False              # Determine if plugin is stable and can be used

    ###########################################################################
    # Interface methods
    ###########################################################################
    def setup(self, *args, **kwargs):
        """ Configure plugin, this function should be called before plugin execute() method is used.
        """
        return False

    def execute(self, capabilitity, *args, **kwargs):
        """ Executes capability by name.
            Each capability e.g. may directly just call some command line
            program or execute building pythonic function
        """
        return False

    ###########################################################################
    # Interface helper methods - overload only if you need to have custom behaviour
    ###########################################################################
    def print_plugin_error(self, text):
        """ Function prints error in console and exits always with False
        """
        print "Plugin error: %s::%s: %s"% (self.name, self.type, text)
        return False

    def print_plugin_info(self, text, NL=True):
        """ Function prints notification in console and exits always with True
        """
        if NL:
            print "Plugin info: %s::%s: %s"% (self.name, self.type, text)
        else:
            print "Plugin info: %s::%s: %s"% (self.name, self.type, text),
        return True

    def print_plugin_char(self, char):
        """ Function prints char on stdout
        """
        stdout.write(char)
        stdout.flush()
        return True

    def check_mount_point_ready(self, destination_disk, init_delay=0.2, loop_delay=0.25):
        """ Checks if destination_disk is ready and can be accessed by e.g. copy commands
            @init_delay - Initial delay time before first access check
            @loop_delay - pooling delay for access check
        """
        if not access(destination_disk, F_OK):
            self.print_plugin_info("Waiting for mount point '%s' to be ready..."% destination_disk, NL=False)
            sleep(init_delay)
            while not access(destination_disk, F_OK):
                sleep(loop_delay)
                self.print_plugin_char('.')

    def check_parameters(self, capabilitity, *args, **kwargs):
        """ This function should be ran each time we call execute()
            to check if none of the required parameters is missing.
        """
        missing_parameters = []
        for parameter in self.required_parameters:
            if parameter not in kwargs:
                missing_parameters.append(parameter)
        if len(missing_parameters) > 0:
            self.print_plugin_error("execute parameter(s) '%s' missing!"% (', '.join(parameter)))
            return False
        return True

    def run_command(self, cmd, shell=True):
        """ Runs command from command line.
        """
        result = True
        try:
            ret = call(cmd, shell=shell)
            if ret:
                self.print_plugin_error("[ret=%d] Command: %s"% (int(ret), cmd))
                return False
        except Exception as e:
            result = False
            self.print_plugin_error("[ret=%d] Command: %s"% (int(ret), cmd))
            self.print_plugin_error(str(e))
        return result
