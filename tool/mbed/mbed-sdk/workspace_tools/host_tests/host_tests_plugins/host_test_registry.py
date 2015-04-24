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

class HostTestRegistry:
    """ Simple class used to register and store
        host test plugins for further usage
    """
    # Here we actually store all the plugins
    PLUGINS = {}    # 'Plugin Name' : Plugin Object

    def print_error(self, text):
        print "Plugin load failed. Reason: %s"% text

    def register_plugin(self, plugin):
        """ Registers and stores plugin inside registry for further use.
            Method also calls plugin's setup() function to configure plugin if needed.

            Note: Different groups of plugins may demand different extra parameter. Plugins
            should be at least for one type of plugin configured with the same parameters
            because we do not know which of them will actually use particular parameter.
        """
        # TODO:
        # - check for unique caps for specified type
        if plugin.name not in self.PLUGINS:
            if plugin.setup(): # Setup plugin can be completed without errors
                self.PLUGINS[plugin.name] = plugin
                return True
            else:
                self.print_error("%s setup failed"% plugin.name)
        else:
            self.print_error("%s already loaded"% plugin.name)
        return False

    def call_plugin(self, type, capability, *args, **kwargs):
        """ Execute plugin functionality respectively to its purpose
        """
        for plugin_name in self.PLUGINS:
            plugin = self.PLUGINS[plugin_name]
            if plugin.type == type and capability in plugin.capabilities:
                return plugin.execute(capability, *args, **kwargs)
        return False

    def get_plugin_caps(self, type):
        """ Returns list of all capabilities for plugin family with the same type.
            If there are no capabilities empty list is returned
        """
        result = []
        for plugin_name in self.PLUGINS:
            plugin = self.PLUGINS[plugin_name]
            if plugin.type == type:
                result.extend(plugin.capabilities)
        return sorted(result)

    def load_plugin(self, name):
        """ Used to load module from
        """
        mod = __import__("module_%s"% name)
        return mod

    def __str__(self):
        """ User friendly printing method to show hooked plugins
        """
        from prettytable import PrettyTable
        column_names = ['name', 'type', 'capabilities', 'stable']
        pt = PrettyTable(column_names)
        for column in column_names:
            pt.align[column] =  'l'
        for plugin_name in sorted(self.PLUGINS.keys()):
            name  = self.PLUGINS[plugin_name].name
            type  = self.PLUGINS[plugin_name].type
            stable = self.PLUGINS[plugin_name].stable
            capabilities  = ', '.join(self.PLUGINS[plugin_name].capabilities)
            row = [name, type, capabilities, stable]
            pt.add_row(row)
        return pt.get_string()
