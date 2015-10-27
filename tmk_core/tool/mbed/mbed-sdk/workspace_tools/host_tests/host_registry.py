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

class HostRegistry:
    """ Class stores registry with host tests and objects representing them
    """ 
    HOST_TESTS = {} # host_test_name -> host_test_ojbect

    def register_host_test(self, ht_name, ht_object):
        if ht_name not in self.HOST_TESTS:
            self.HOST_TESTS[ht_name] = ht_object
    
    def unregister_host_test(self):
        if ht_name in HOST_TESTS:
            self.HOST_TESTS[ht_name] = None

    def get_host_test(self, ht_name):
        return self.HOST_TESTS[ht_name] if ht_name in self.HOST_TESTS else None

    def is_host_test(self, ht_name):
        return ht_name in self.HOST_TESTS
        