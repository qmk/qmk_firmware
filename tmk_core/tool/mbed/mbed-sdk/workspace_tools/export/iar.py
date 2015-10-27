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
from workspace_tools.export.exporters import Exporter
import re
import os
class IAREmbeddedWorkbench(Exporter):
    """
    Exporter class for IAR Systems.
    """
    NAME = 'IAR'
    TOOLCHAIN = 'IAR'

    TARGETS = [
        'LPC1768',
        'LPC1347',
        'LPC11U24',
        'LPC11U35_401',
        'LPC11U35_501',
        #Removed LPCCAPPUCCINO linker file and startup file missing
        #'LPCCAPPUCCINO',
        'LPC1114',
        'LPC1549',
        'LPC812',
        'LPC4088',
        'LPC4088_DM',
        'LPC824',
        'UBLOX_C027',
        'ARCH_PRO',
        'K20D50M',
        'KL05Z',
        'KL25Z',
        'KL46Z',
        'K22F',
        'K64F',
        'NUCLEO_F030R8',
        'NUCLEO_F070RB',
        'NUCLEO_F072RB',
        'NUCLEO_F091RC',
        'NUCLEO_F103RB',
        'NUCLEO_F302R8',
        'NUCLEO_F303RE',
        'NUCLEO_F334R8',
        'NUCLEO_F401RE',
        'NUCLEO_F411RE',
        'NUCLEO_L053R8',
        'NUCLEO_L073RZ',
        'NUCLEO_L152RE',
        #'STM32F407', Fails to build same for GCC
        'MAXWSNENV',
        'MAX32600MBED',
        'MTS_MDOT_F405RG',
        'MTS_MDOT_F411RE',
        'MTS_DRAGONFLY_F411RE',
        'NRF51822',
        'NRF51_DK',
        'NRF51_DONGLE',
        'DELTA_DFCM_NNN40',
        'SEEED_TINY_BLE',
        'HRM1017',
        'ARCH_BLE',
        'MOTE_L152RC',
    ]

    def generate(self):
        """
        Generates the project files
        """
        sources = []
        sources += self.resources.c_sources
        sources += self.resources.cpp_sources
        sources += self.resources.s_sources

        iar_files = IarFolder("", "", [])
        for source in sources:
            iar_files.insert_file(source)

        ctx = {
            'name': self.program_name,
            'include_paths': self.resources.inc_dirs,
            'linker_script': self.resources.linker_script,
            'object_files': self.resources.objects,
            'libraries': self.resources.libraries,
            'symbols': self.get_symbols(),
            'source_files': iar_files.__str__(),
            'binary_files': self.resources.bin_files,
        }
        self.gen_file('iar_%s.ewp.tmpl' % self.target.lower(), ctx, '%s.ewp' % self.program_name)
        self.gen_file('iar.eww.tmpl', ctx, '%s.eww' % self.program_name)
        self.gen_file('iar_%s.ewd.tmpl' % self.target.lower(), ctx, '%s.ewd' % self.program_name)

class IarFolder():
    """
    This is a recursive folder object.
    To present the folder structure in the IDE as it is presented on the disk.
    This can be used for uvision as well if you replace the __str__ method.
    Example:
    files: ./main.cpp, ./apis/I2C.h, ./mbed/common/I2C.cpp
    in the project this would look like:
    main.cpp
    common/I2C.cpp
    input:
    folder_level : folder path to current folder
    folder_name : name of current folder
    source_files : list of source_files (all must be in same directory)
    """
    def __init__(self, folder_level, folder_name, source_files):
        self.folder_level = folder_level
        self.folder_name = folder_name
        self.source_files = source_files
        self.sub_folders = {}

    def __str__(self):
        """
        converts the folder structue to IAR project format.
        """
        group_start = ""
        group_end = ""
        if self.folder_name != "":
            group_start = "<group>\n<name>%s</name>\n" %(self.folder_name)
            group_end = "</group>\n"

        str_content = group_start
        #Add files in current folder
        if self.source_files:
            for src in self.source_files:
                str_content += "<file>\n<name>$PROJ_DIR$/%s</name>\n</file>\n" % src
        #Add sub folders
        if self.sub_folders:
            for folder_name in self.sub_folders.iterkeys():
                str_content += self.sub_folders[folder_name].__str__()

        str_content += group_end
        return str_content

    def insert_file(self, source_input):
        """
        Inserts a source file into the folder tree
        """
        if self.source_files:
            #All source_files in a IarFolder must be in same directory.
            dir_sources = IarFolder.get_directory(self.source_files[0])
            #Check if sources are already at their deepest level.
            if not self.folder_level == dir_sources:
                _reg_exp = r"^" + re.escape(self.folder_level) + r"[/\\]?([^/\\]+)"
                folder_name = re.match(_reg_exp, dir_sources).group(1)
                self.sub_folders[folder_name] = IarFolder(os.path.join(self.folder_level, folder_name), folder_name, self.source_files)
                self.source_files = []

        dir_input = IarFolder.get_directory(source_input)
        if dir_input == self.folder_level:
            self.source_files.append(source_input)
        else:
            _reg_exp = r"^" + re.escape(self.folder_level) + r"[/\\]?([^/\\]+)"
            folder_name = re.match(_reg_exp, dir_input).group(1)
            if self.sub_folders.has_key(folder_name):
                self.sub_folders[folder_name].insert_file(source_input)
            else:
                if self.folder_level == "":
                    #Top level exception
                    self.sub_folders[folder_name] = IarFolder(folder_name, folder_name, [source_input])
                else:
                    self.sub_folders[folder_name] = IarFolder(os.path.join(self.folder_level, folder_name), folder_name, [source_input])

    @staticmethod
    def get_directory(file_path):
        """
        Returns the directory of the file
        """
        return os.path.dirname(file_path)
