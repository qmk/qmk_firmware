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
import sys
from os import listdir, remove, makedirs
from shutil import copyfile
from os.path import isdir, join, exists, split, relpath, splitext
from subprocess import Popen, PIPE, STDOUT, call


def cmd(l, check=True, verbose=False, shell=False, cwd=None):
    text = l if shell else ' '.join(l)
    if verbose:
        print text
    rc = call(l, shell=shell, cwd=cwd)
    if check and rc != 0:
        raise Exception('ERROR %d: "%s"' % (rc, text))


def run_cmd(command, wd=None, redirect=False):
    p = Popen(command, stdout=PIPE, stderr=STDOUT if redirect else PIPE, cwd=wd)
    _stdout, _stderr = p.communicate()
    return _stdout, _stderr, p.returncode


def run_cmd_ext(command):
    p = Popen(command, stdout=PIPE, stderr=PIPE)
    _stdout, _stderr = p.communicate()
    return _stdout, _stderr, p.returncode


def mkdir(path):
    if not exists(path):
        makedirs(path)


def copy_file(src, dst):
    """ Implement the behaviour of "shutil.copy(src, dst)" without copying the
        permissions (this was causing errors with directories mounted with samba)
    """
    if isdir(dst):
        _, file = split(src)
        dst = join(dst, file)
    copyfile(src, dst)


def delete_dir_files(dir):
    if not exists(dir):
        return

    for f in listdir(dir):
        file = join(dir, f)
        if not isdir(file):
            remove(file)


def error(msg):
    print msg
    sys.exit(1)


def rel_path(path, base, dot=False):
    p = relpath(path, base)
    if dot and not p.startswith('.'):
        p = './' + p
    return p


class ToolException(Exception):
    pass


def split_path(path):
    base, file = split(path)
    name, ext = splitext(file)
    return base, name, ext


def args_error(parser, message):
    print "\n\n%s\n\n" % message
    parser.print_help()
    sys.exit()


def construct_enum(**enums):
    """ Create your own pseudo-enums """
    return type('Enum', (), enums)


def check_required_modules(required_modules, verbose=True):
    """ Function checks for Python modules which should be "importable" (installed)
        before test suite can be used.
        @return returns True if all modules are installed already
    """
    import imp
    all_modules_found = True
    not_installed_modules = []
    for module_name in required_modules:
        try:
            imp.find_module(module_name)
        except ImportError as e:
            all_modules_found = False
            not_installed_modules.append(module_name)
            if verbose:
                print "Error: %s"% e
    if verbose:
        if not all_modules_found:
            print "Warning: Module(s) %s not installed. Please install required module(s) before using this script."% (', '.join(not_installed_modules))
    return all_modules_found
