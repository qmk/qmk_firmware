"""
This module defines the attributes of the
PyPI package for the Mbed SDK
"""

from shutil import copyfileobj
from os.path import isfile, join
from tempfile import TemporaryFile
from setuptools import find_packages
from distutils.core import setup

LICENSE = open('LICENSE').read()
DESCRIPTION = """A set of Python scripts that can be used to compile programs written on top of the `mbed framework`_. It can also be used to export mbed projects to other build systems and IDEs (uVision, IAR, makefiles).

.. _mbed framework: http://mbed.org"""
OWNER_NAMES = 'emilmont, bogdanm'
OWNER_EMAILS = 'Emilio.Monti@arm.com, Bogdan.Marinescu@arm.com'

# If private_settings.py exists in workspace_tools, read it in a temporary file
# so it can be restored later
private_settings = join('workspace_tools', 'private_settings.py')
backup = None
if isfile(private_settings):
    backup = TemporaryFile()
    with open(private_settings, "rb") as f:
        copyfileobj(f, backup)

# Create the correct private_settings.py for the distribution
with open(private_settings, "wt") as f:
    f.write("from mbed_settings import *\n")

setup(name='mbed-tools',
      version='0.1.14',
      description='Build and test system for mbed',
      long_description=DESCRIPTION,
      author=OWNER_NAMES,
      author_email=OWNER_EMAILS,
      maintainer=OWNER_NAMES,
      maintainer_email=OWNER_EMAILS,
      url='https://github.com/mbedmicro/mbed',
      packages=find_packages(),
      license=LICENSE,
      install_requires=["PrettyTable>=0.7.2", "PySerial>=2.7", "IntelHex>=1.3", "colorama>=0.3.3", "Jinja2>=2.7.3"])

# Restore previous private_settings if needed
if backup:
    backup.seek(0)
    with open(private_settings, "wb") as f:
        copyfileobj(backup, f)
