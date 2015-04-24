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

from shutil import copy
from host_test_plugins import HostTestPluginBase


class HostTestPluginCopyMethod_Mbed(HostTestPluginBase):

    def generic_mbed_copy(self, image_path, destination_disk):
        """ Generic mbed copy method for "mbed enabled" devices.
            It uses standard python shuitl function to copy
            image_file (target specific binary) to device's disk.
        """
        result = True
        if not destination_disk.endswith('/') and not destination_disk.endswith('\\'):
            destination_disk += '/'
        try:
            copy(image_path, destination_disk)
        except Exception, e:
            self.print_plugin_error("shutil.copy('%s', '%s')"% (image_path, destination_disk))
            self.print_plugin_error("Error: %s"% str(e))
            result = False
        return result

    # Plugin interface
    name = 'HostTestPluginCopyMethod_Mbed'
    type = 'CopyMethod'
    stable = True
    capabilities = ['default']
    required_parameters = ['image_path', 'destination_disk']

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
                image_path = kwargs['image_path']
                destination_disk = kwargs['destination_disk']
                # Wait for mount point to be ready
                self.check_mount_point_ready(destination_disk)  # Blocking
                result = self.generic_mbed_copy(image_path, destination_disk)
        return result


def load_plugin():
    """ Returns plugin available in this module
    """
    return HostTestPluginCopyMethod_Mbed()
