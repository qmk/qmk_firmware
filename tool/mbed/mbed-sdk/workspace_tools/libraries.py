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
from workspace_tools.paths import *
from workspace_tools.data.support import *
from workspace_tools.tests import TEST_MBED_LIB


LIBRARIES = [
    # RTOS libraries
    {
        "id": "rtx",
        "source_dir": MBED_RTX,
        "build_dir": RTOS_LIBRARIES,
        "dependencies": [MBED_LIBRARIES],
    },
    {
        "id": "rtos",
        "source_dir": RTOS_ABSTRACTION,
        "build_dir": RTOS_LIBRARIES,
        "dependencies": [MBED_LIBRARIES, MBED_RTX],
    },

    # USB Device libraries
    {
        "id": "usb",
        "source_dir": USB,
        "build_dir": USB_LIBRARIES,
        "dependencies": [MBED_LIBRARIES],
    },

    # USB Host libraries
    {
        "id": "usb_host",
        "source_dir": USB_HOST,
        "build_dir": USB_HOST_LIBRARIES,
        "dependencies": [MBED_LIBRARIES, FAT_FS, MBED_RTX, RTOS_ABSTRACTION],
    },

    # DSP libraries
    {
        "id": "cmsis_dsp",
        "source_dir": DSP_CMSIS,
        "build_dir": DSP_LIBRARIES,
        "dependencies": [MBED_LIBRARIES],
    },
    {
        "id": "dsp",
        "source_dir": DSP_ABSTRACTION,
        "build_dir": DSP_LIBRARIES,
        "dependencies": [MBED_LIBRARIES, DSP_CMSIS],
    },

    # File system libraries
    {
        "id": "fat",
        "source_dir": [FAT_FS, SD_FS],
        "build_dir": FS_LIBRARY,
        "dependencies": [MBED_LIBRARIES]
    },

    # Network libraries
    {
        "id": "eth",
        "source_dir": [ETH_SOURCES, LWIP_SOURCES],
        "build_dir": ETH_LIBRARY,
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES]
    },

    {
        "id": "ublox",
        "source_dir": [UBLOX_SOURCES, CELLULAR_SOURCES, CELLULAR_USB_SOURCES, LWIP_SOURCES],
        "build_dir": UBLOX_LIBRARY,
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, USB_HOST_LIBRARIES],
    },

    # Unit Testing library
    {
        "id": "cpputest",
        "source_dir": [CPPUTEST_SRC, CPPUTEST_PLATFORM_SRC, CPPUTEST_TESTRUNNER_SCR],
        "build_dir": CPPUTEST_LIBRARY,
        "dependencies": [MBED_LIBRARIES],
        'inc_dirs': [CPPUTEST_INC, CPPUTEST_PLATFORM_INC, CPPUTEST_TESTRUNNER_INC, TEST_MBED_LIB],
        'inc_dirs_ext': [CPPUTEST_INC_EXT],
        'macros': ["CPPUTEST_USE_MEM_LEAK_DETECTION=0", "CPPUTEST_USE_STD_CPP_LIB=0", "CPPUTEST=1"],
    },
]


LIBRARY_MAP = dict([(library['id'], library) for library in LIBRARIES])


class Library:
    DEFAULTS = {
        "supported": DEFAULT_SUPPORT,
        'dependencies': None,
        'inc_dirs': None,       # Include dirs required by library build
        'inc_dirs_ext': None,   # Include dirs required by others to use with this library
        'macros': None,         # Additional macros you want to define when building library
    }
    def __init__(self, lib_id):
        self.__dict__.update(Library.DEFAULTS)
        self.__dict__.update(LIBRARY_MAP[lib_id])

    def is_supported(self, target, toolchain):
        if not hasattr(self, 'supported'):
            return True
        return (target.name in self.supported) and (toolchain in self.supported[target.name])
