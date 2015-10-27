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

import host_test_registry

# This plugins provide 'flashing' methods to host test scripts
import module_copy_mbed
import module_copy_shell
import module_copy_silabs
#import module_copy_firefox
#import module_copy_mps2

# Plugins used to reset certain platform
import module_reset_mbed
import module_reset_silabs
#import module_reset_mps2


# Plugin registry instance
HOST_TEST_PLUGIN_REGISTRY = host_test_registry.HostTestRegistry()

# Static plugin registration
# Some plugins are commented out if they are not stable or not commonly used
HOST_TEST_PLUGIN_REGISTRY.register_plugin(module_copy_mbed.load_plugin())
HOST_TEST_PLUGIN_REGISTRY.register_plugin(module_copy_shell.load_plugin())
HOST_TEST_PLUGIN_REGISTRY.register_plugin(module_reset_mbed.load_plugin())
#HOST_TEST_PLUGIN_REGISTRY.register_plugin(module_copy_firefox.load_plugin())

# Extra platforms support
#HOST_TEST_PLUGIN_REGISTRY.register_plugin(module_copy_mps2.load_plugin())
#HOST_TEST_PLUGIN_REGISTRY.register_plugin(module_reset_mps2.load_plugin())
HOST_TEST_PLUGIN_REGISTRY.register_plugin(module_copy_silabs.load_plugin())
HOST_TEST_PLUGIN_REGISTRY.register_plugin(module_reset_silabs.load_plugin())

# TODO: extend plugin loading to files with name module_*.py loaded ad-hoc

###############################################################################
# Functional interface for host test plugin registry
###############################################################################
def call_plugin(type, capability, *args, **kwargs):
    """ Interface to call plugin registry functional way
    """
    return HOST_TEST_PLUGIN_REGISTRY.call_plugin(type, capability, *args, **kwargs)

def get_plugin_caps(type):
    """ Returns list of all capabilities for plugin family with the same type.
        If there are no capabilities empty list is returned
    """
    return HOST_TEST_PLUGIN_REGISTRY.get_plugin_caps(type)

def print_plugin_info():
    """ Prints plugins' information in user friendly way
    """
    print HOST_TEST_PLUGIN_REGISTRY
