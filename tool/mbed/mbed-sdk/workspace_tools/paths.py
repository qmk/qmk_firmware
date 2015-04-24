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
from os.path import join
from os import getenv

# Conventions about the directory structure
from settings import ROOT, BUILD_DIR

# Allow overriding some of the build parameters using environment variables
BUILD_DIR = getenv("MBED_BUILD_DIR") or BUILD_DIR

# Embedded Libraries Sources
LIB_DIR = join(ROOT, "libraries")

TOOLS = join(ROOT, "workspace_tools")
TOOLS_DATA = join(TOOLS, "data")
TOOLS_BOOTLOADERS = join(TOOLS, "bootloaders")

# mbed libraries
MBED_BASE = join(LIB_DIR, "mbed")

MBED_API = join(MBED_BASE, "api")
MBED_COMMON = join(MBED_BASE, "common")
MBED_HAL = join(MBED_BASE, "hal")
MBED_TARGETS_PATH = join(MBED_BASE, "targets")

MBED_LIBRARIES = join(BUILD_DIR, "mbed")

# Tests
TEST_DIR = join(LIB_DIR, "tests")
HOST_TESTS = join(ROOT, "workspace_tools", "host_tests")

# mbed RPC
MBED_RPC = join(LIB_DIR, "rpc")

# mbed RTOS
RTOS = join(LIB_DIR, "rtos")
MBED_RTX = join(RTOS, "rtx")
RTOS_ABSTRACTION = join(RTOS, "rtos")

RTOS_LIBRARIES = join(BUILD_DIR, "rtos")

# TCP/IP
NET = join(LIB_DIR, "net")

ETH_SOURCES = join(NET, "eth")
LWIP_SOURCES = join(NET, "lwip")
VODAFONE_SOURCES = join(NET, "VodafoneUSBModem")
CELLULAR_SOURCES = join(NET, "cellular", "CellularModem")
CELLULAR_USB_SOURCES = join(NET, "cellular", "CellularUSBModem")
UBLOX_SOURCES = join(NET, "cellular", "UbloxUSBModem")

NET_LIBRARIES = join(BUILD_DIR, "net")
ETH_LIBRARY = join(NET_LIBRARIES, "eth")
VODAFONE_LIBRARY = join(NET_LIBRARIES, "VodafoneUSBModem")
UBLOX_LIBRARY = join(NET_LIBRARIES, "UbloxUSBModem")

# FS
FS_PATH = join(LIB_DIR, "fs")
FAT_FS = join(FS_PATH, "fat")
SD_FS = join(FS_PATH, "sd")
FS_LIBRARY = join(BUILD_DIR, "fat")

# DSP
DSP = join(LIB_DIR, "dsp")
DSP_CMSIS = join(DSP, "cmsis_dsp")
DSP_ABSTRACTION = join(DSP, "dsp")
DSP_LIBRARIES = join(BUILD_DIR, "dsp")

# USB Device
USB = join(LIB_DIR, "USBDevice")
USB_LIBRARIES = join(BUILD_DIR, "usb")

# USB Host
USB_HOST = join(LIB_DIR, "USBHost")
USB_HOST_LIBRARIES = join(BUILD_DIR, "usb_host")

# Export
EXPORT_DIR = join(BUILD_DIR, "export")
EXPORT_WORKSPACE = join(EXPORT_DIR, "workspace")
EXPORT_TMP = join(EXPORT_DIR, ".temp")

# CppUtest library
CPPUTEST_DIR = join(ROOT, "..")
CPPUTEST_SRC = join(CPPUTEST_DIR, "cpputest", "src", "CppUTest")
CPPUTEST_INC = join(CPPUTEST_DIR, "cpputest", "include")
CPPUTEST_INC_EXT = join(CPPUTEST_DIR, "cpputest", "include", "CppUTest")
# Platform dependant code is here (for armcc compiler)
CPPUTEST_PLATFORM_SRC = join(CPPUTEST_DIR, "cpputest", "src", "Platforms", "armcc")
CPPUTEST_PLATFORM_INC = join(CPPUTEST_DIR, "cpputest", "include", "Platforms", "armcc")
# Function 'main' used to run all compiled UTs
CPPUTEST_TESTRUNNER_SCR = join(TEST_DIR, "utest", "testrunner")
CPPUTEST_TESTRUNNER_INC = join(TEST_DIR, "utest", "testrunner")

CPPUTEST_LIBRARY = join(BUILD_DIR, "cpputest")
