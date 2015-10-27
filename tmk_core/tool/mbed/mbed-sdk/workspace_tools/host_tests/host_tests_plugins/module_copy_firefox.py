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

from os.path import join, basename
from host_test_plugins import HostTestPluginBase


class HostTestPluginCopyMethod_Firefox(HostTestPluginBase):

    def file_store_firefox(self, file_path, dest_disk):
        try:
            from selenium import webdriver
            profile = webdriver.FirefoxProfile()
            profile.set_preference('browser.download.folderList', 2) # custom location
            profile.set_preference('browser.download.manager.showWhenStarting', False)
            profile.set_preference('browser.download.dir', dest_disk)
            profile.set_preference('browser.helperApps.neverAsk.saveToDisk', 'application/octet-stream')
            # Launch browser with profile and get file
            browser = webdriver.Firefox(profile)
            browser.get(file_path)
            browser.close()
        except:
            return False
        return True

    # Plugin interface
    name = 'HostTestPluginCopyMethod_Firefox'
    type = 'CopyMethod'
    capabilities = ['firefox']
    required_parameters = ['image_path', 'destination_disk']

    def setup(self, *args, **kwargs):
        """ Configure plugin, this function should be called before plugin execute() method is used.
        """
        try:
            from selenium import webdriver
        except ImportError, e:
            self.print_plugin_error("Error: firefox copy method requires selenium library. %s"% e)
            return False
        return True

    def execute(self, capabilitity, *args, **kwargs):
        """ Executes capability by name.
            Each capability may directly just call some command line
            program or execute building pythonic function
        """
        result = False
        if self.check_parameters(capabilitity, *args, **kwargs) is True:
            image_path = kwargs['image_path']
            destination_disk = kwargs['destination_disk']
            # Prepare correct command line parameter values
            image_base_name = basename(image_path)
            destination_path = join(destination_disk, image_base_name)
            if capabilitity == 'firefox':
                self.file_store_firefox(image_path, destination_path)
        return result


def load_plugin():
    """ Returns plugin available in this module
    """
    return HostTestPluginCopyMethod_Firefox()
