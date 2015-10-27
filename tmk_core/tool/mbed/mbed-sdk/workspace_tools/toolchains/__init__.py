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

import re
import sys
from os import stat, walk
from copy import copy
from time import time, sleep
from types import ListType
from shutil import copyfile
from os.path import join, splitext, exists, relpath, dirname, basename, split
from inspect import getmro

from multiprocessing import Pool, cpu_count
from workspace_tools.utils import run_cmd, mkdir, rel_path, ToolException, split_path
from workspace_tools.settings import BUILD_OPTIONS, MBED_ORG_USER
import workspace_tools.hooks as hooks


#Disables multiprocessing if set to higher number than the host machine CPUs
CPU_COUNT_MIN = 1

def print_notify(event, silent=False):
    """ Default command line notification
    """
    if event['type'] in ['info', 'debug']:
        print event['message']

    elif event['type'] == 'cc':
        event['severity'] = event['severity'].title()
        event['file'] = basename(event['file'])
        print '[%(severity)s] %(file)s@%(line)s: %(message)s' % event

    elif event['type'] == 'progress':
        if not silent:
            print '%s: %s' % (event['action'].title(), basename(event['file']))

def print_notify_verbose(event, silent=False):
    """ Default command line notification with more verbose mode
    """
    if event['type'] in ['info', 'debug']:
        print_notify(event) # standard handle

    elif event['type'] == 'cc':
        event['severity'] = event['severity'].title()
        event['file'] = basename(event['file'])
        event['mcu_name'] = "None"
        event['toolchain'] = "None"
        event['target_name'] = event['target_name'].upper() if event['target_name'] else "Unknown"
        event['toolchain_name'] = event['toolchain_name'].upper() if event['toolchain_name'] else "Unknown"
        print '[%(severity)s] %(target_name)s::%(toolchain_name)s::%(file)s@%(line)s: %(message)s' % event

    elif event['type'] == 'progress':
        print_notify(event) # standard handle

def compile_worker(job):
    results = []
    for command in job['commands']:
        _, _stderr, _rc = run_cmd(command, job['work_dir'])
        results.append({
            'code': _rc,
            'output': _stderr,
            'command': command
        })

    return {
        'source': job['source'],
        'object': job['object'],
        'commands': job['commands'],
        'results': results
    }

class Resources:
    def __init__(self, base_path=None):
        self.base_path = base_path

        self.inc_dirs = []
        self.headers = []

        self.s_sources = []
        self.c_sources = []
        self.cpp_sources = []

        self.lib_dirs = set([])
        self.objects = []
        self.libraries = []

        # mbed special files
        self.lib_builds = []
        self.lib_refs = []

        self.repo_dirs = []
        self.repo_files = []

        self.linker_script = None

        # Other files
        self.hex_files = []
        self.bin_files = []

    def add(self, resources):
        self.inc_dirs += resources.inc_dirs
        self.headers += resources.headers

        self.s_sources += resources.s_sources
        self.c_sources += resources.c_sources
        self.cpp_sources += resources.cpp_sources

        self.lib_dirs |= resources.lib_dirs
        self.objects += resources.objects
        self.libraries += resources.libraries

        self.lib_builds += resources.lib_builds
        self.lib_refs += resources.lib_refs

        self.repo_dirs += resources.repo_dirs
        self.repo_files += resources.repo_files

        if resources.linker_script is not None:
            self.linker_script = resources.linker_script

        self.hex_files += resources.hex_files
        self.bin_files += resources.bin_files

    def relative_to(self, base, dot=False):
        for field in ['inc_dirs', 'headers', 's_sources', 'c_sources',
                      'cpp_sources', 'lib_dirs', 'objects', 'libraries',
                      'lib_builds', 'lib_refs', 'repo_dirs', 'repo_files', 'hex_files', 'bin_files']:
            v = [rel_path(f, base, dot) for f in getattr(self, field)]
            setattr(self, field, v)
        if self.linker_script is not None:
            self.linker_script = rel_path(self.linker_script, base, dot)

    def win_to_unix(self):
        for field in ['inc_dirs', 'headers', 's_sources', 'c_sources',
                      'cpp_sources', 'lib_dirs', 'objects', 'libraries',
                      'lib_builds', 'lib_refs', 'repo_dirs', 'repo_files', 'hex_files', 'bin_files']:
            v = [f.replace('\\', '/') for f in getattr(self, field)]
            setattr(self, field, v)
        if self.linker_script is not None:
            self.linker_script = self.linker_script.replace('\\', '/')

    def __str__(self):
        s = []

        for (label, resources) in (
                ('Include Directories', self.inc_dirs),
                ('Headers', self.headers),

                ('Assembly sources', self.s_sources),
                ('C sources', self.c_sources),
                ('C++ sources', self.cpp_sources),

                ('Library directories', self.lib_dirs),
                ('Objects', self.objects),
                ('Libraries', self.libraries),

                ('Hex files', self.hex_files),
                ('Bin files', self.bin_files),
            ):
            if resources:
                s.append('%s:\n  ' % label + '\n  '.join(resources))

        if self.linker_script:
            s.append('Linker Script: ' + self.linker_script)

        return '\n'.join(s)


# Support legacy build conventions: the original mbed build system did not have
# standard labels for the "TARGET_" and "TOOLCHAIN_" specific directories, but
# had the knowledge of a list of these directories to be ignored.
LEGACY_IGNORE_DIRS = set([
    'LPC11U24', 'LPC1768', 'LPC2368', 'LPC4088', 'LPC812', 'KL25Z',
    'ARM', 'GCC_ARM', 'GCC_CR', 'GCC_CS', 'IAR', 'uARM'
])
LEGACY_TOOLCHAIN_NAMES = {
    'ARM_STD':'ARM', 'ARM_MICRO': 'uARM',
    'GCC_ARM': 'GCC_ARM', 'GCC_CR': 'GCC_CR', 'GCC_CS': 'GCC_CS',
    'IAR': 'IAR',
}


class mbedToolchain:
    VERBOSE = True

    CORTEX_SYMBOLS = {
        "Cortex-M0" : ["__CORTEX_M0", "ARM_MATH_CM0"],
        "Cortex-M0+": ["__CORTEX_M0PLUS", "ARM_MATH_CM0PLUS"],
        "Cortex-M1" : ["__CORTEX_M3", "ARM_MATH_CM1"],
        "Cortex-M3" : ["__CORTEX_M3", "ARM_MATH_CM3"],
        "Cortex-M4" : ["__CORTEX_M4", "ARM_MATH_CM4"],
        "Cortex-M4F" : ["__CORTEX_M4", "ARM_MATH_CM4", "__FPU_PRESENT=1"],
        "Cortex-M7" : ["__CORTEX_M7", "ARM_MATH_CM7"],
        "Cortex-M7F" : ["__CORTEX_M7", "ARM_MATH_CM7", "__FPU_PRESENT=1"],
        "Cortex-A9" : ["__CORTEX_A9", "ARM_MATH_CA9", "__FPU_PRESENT", "__CMSIS_RTOS", "__EVAL", "__MBED_CMSIS_RTOS_CA9"],
    }

    GOANNA_FORMAT = "[Goanna] warning [%FILENAME%:%LINENO%] - [%CHECKNAME%(%SEVERITY%)] %MESSAGE%"
    GOANNA_DIAGNOSTIC_PATTERN = re.compile(r'"\[Goanna\] (?P<severity>warning) \[(?P<file>[^:]+):(?P<line>\d+)\] \- (?P<message>.*)"')

    def __init__(self, target, options=None, notify=None, macros=None, silent=False):
        self.target = target
        self.name = self.__class__.__name__
        self.hook = hooks.Hook(target, self)
        self.silent = silent

        self.legacy_ignore_dirs = LEGACY_IGNORE_DIRS - set([target.name, LEGACY_TOOLCHAIN_NAMES[self.name]])

        self.notify_fun = notify if notify is not None else print_notify
        self.options = options if options is not None else []

        self.macros = macros or []
        self.options.extend(BUILD_OPTIONS)
        if self.options:
            self.info("Build Options: %s" % (', '.join(self.options)))

        self.obj_path = join("TARGET_"+target.name, "TOOLCHAIN_"+self.name)

        self.symbols = None
        self.labels = None
        self.has_config = False

        self.build_all = False
        self.timestamp = time()
        self.jobs = 1

        self.CHROOT = None

        self.mp_pool = None

    def notify(self, event):
        """ Little closure for notify functions
        """
        return self.notify_fun(event, self.silent)

    def __exit__(self):
        if self.mp_pool is not None:
            self.mp_pool.terminate()

    def goanna_parse_line(self, line):
        if "analyze" in self.options:
            return self.GOANNA_DIAGNOSTIC_PATTERN.match(line)
        else:
            return None

    def get_symbols(self):
        if self.symbols is None:
            # Target and Toolchain symbols
            labels = self.get_labels()
            self.symbols = ["TARGET_%s" % t for t in labels['TARGET']]
            self.symbols.extend(["TOOLCHAIN_%s" % t for t in labels['TOOLCHAIN']])

            # Config support
            if self.has_config:
                self.symbols.append('HAVE_MBED_CONFIG_H')

            # Cortex CPU symbols
            if self.target.core in mbedToolchain.CORTEX_SYMBOLS:
                self.symbols.extend(mbedToolchain.CORTEX_SYMBOLS[self.target.core])

            # Symbols defined by the on-line build.system
            self.symbols.extend(['MBED_BUILD_TIMESTAMP=%s' % self.timestamp, '__MBED__=1'])
            if MBED_ORG_USER:
                self.symbols.append('MBED_USERNAME=' + MBED_ORG_USER)

            # Add target's symbols
            self.symbols += self.target.macros
            # Add extra symbols passed via 'macros' parameter
            self.symbols += self.macros

            # Form factor variables
            if hasattr(self.target, 'supported_form_factors'):
                self.symbols.extend(["TARGET_FF_%s" % t for t in self.target.supported_form_factors])

        return self.symbols

    def get_labels(self):
        if self.labels is None:
            toolchain_labels = [c.__name__ for c in getmro(self.__class__)]
            toolchain_labels.remove('mbedToolchain')
            self.labels = {
                'TARGET': self.target.get_labels(),
                'TOOLCHAIN': toolchain_labels
            }
        return self.labels

    def need_update(self, target, dependencies):
        if self.build_all:
            return True

        if not exists(target):
            return True

        target_mod_time = stat(target).st_mtime

        for d in dependencies:

            # Some objects are not provided with full path and here we do not have
            # information about the library paths. Safe option: assume an update
            if not d or not exists(d):
                return True

            if stat(d).st_mtime >= target_mod_time:
                return True

        return False

    def scan_resources(self, path):
        labels = self.get_labels()
        resources = Resources(path)
        self.has_config = False

        """ os.walk(top[, topdown=True[, onerror=None[, followlinks=False]]])
        When topdown is True, the caller can modify the dirnames list in-place
        (perhaps using del or slice assignment), and walk() will only recurse into
        the subdirectories whose names remain in dirnames; this can be used to prune
        the search, impose a specific order of visiting, or even to inform walk()
        about directories the caller creates or renames before it resumes walk()
        again. Modifying dirnames when topdown is False is ineffective, because in
        bottom-up mode the directories in dirnames are generated before dirpath
        itself is generated.
        """
        for root, dirs, files in walk(path):
            # Remove ignored directories
            for d in copy(dirs):
                if d == '.hg':
                    dir_path = join(root, d)
                    resources.repo_dirs.append(dir_path)
                    resources.repo_files.extend(self.scan_repository(dir_path))

                if ((d.startswith('.') or d in self.legacy_ignore_dirs) or
                    (d.startswith('TARGET_') and d[7:] not in labels['TARGET']) or
                    (d.startswith('TOOLCHAIN_') and d[10:] not in labels['TOOLCHAIN'])):
                    dirs.remove(d)

            # Add root to include paths
            resources.inc_dirs.append(root)

            for file in files:
                file_path = join(root, file)
                _, ext = splitext(file)
                ext = ext.lower()

                if   ext == '.s':
                    resources.s_sources.append(file_path)

                elif ext == '.c':
                    resources.c_sources.append(file_path)

                elif ext == '.cpp':
                    resources.cpp_sources.append(file_path)

                elif ext == '.h' or ext == '.hpp':
                    if basename(file_path) == "mbed_config.h":
                        self.has_config = True
                    resources.headers.append(file_path)

                elif ext == '.o':
                    resources.objects.append(file_path)

                elif ext == self.LIBRARY_EXT:
                    resources.libraries.append(file_path)
                    resources.lib_dirs.add(root)

                elif ext == self.LINKER_EXT:
                    if resources.linker_script is not None:
                        self.info("Warning: Multiple linker scripts detected: %s -> %s" % (resources.linker_script, file_path))
                    resources.linker_script = file_path

                elif ext == '.lib':
                    resources.lib_refs.append(file_path)

                elif ext == '.bld':
                    resources.lib_builds.append(file_path)

                elif file == '.hgignore':
                    resources.repo_files.append(file_path)

                elif ext == '.hex':
                    resources.hex_files.append(file_path)
                
                elif ext == '.bin':
                    resources.bin_files.append(file_path)

        return resources

    def scan_repository(self, path):
        resources = []

        for root, dirs, files in walk(path):
            # Remove ignored directories
            for d in copy(dirs):
                if d == '.' or d == '..':
                    dirs.remove(d)

            for file in files:
                file_path = join(root, file)
                resources.append(file_path)

        return resources

    def copy_files(self, files_paths, trg_path, rel_path=None):
        # Handle a single file
        if type(files_paths) != ListType: files_paths = [files_paths]

        for source in files_paths:
            if source is None:
                files_paths.remove(source)

        for source in files_paths:
            if rel_path is not None:
                relative_path = relpath(source, rel_path)
            else:
                _, relative_path = split(source)

            target = join(trg_path, relative_path)

            if (target != source) and (self.need_update(target, [source])):
                self.progress("copy", relative_path)
                mkdir(dirname(target))
                copyfile(source, target)

    def relative_object_path(self, build_path, base_dir, source):
        source_dir, name, _ = split_path(source)
        obj_dir = join(build_path, relpath(source_dir, base_dir))
        mkdir(obj_dir)
        return join(obj_dir, name + '.o')

    def compile_sources(self, resources, build_path, inc_dirs=None):
        # Web IDE progress bar for project build
        files_to_compile = resources.s_sources + resources.c_sources + resources.cpp_sources
        self.to_be_compiled = len(files_to_compile)
        self.compiled = 0

        #for i in self.build_params:
        #    self.debug(i)
        #    self.debug("%s" % self.build_params[i])

        inc_paths = resources.inc_dirs
        if inc_dirs is not None:
            inc_paths.extend(inc_dirs)

        objects = []
        queue = []
        prev_dir = None

        # The dependency checking for C/C++ is delegated to the compiler
        base_path = resources.base_path
        files_to_compile.sort()
        for source in files_to_compile:
            _, name, _ = split_path(source)
            object = self.relative_object_path(build_path, base_path, source)

            # Avoid multiple mkdir() calls on same work directory
            work_dir = dirname(object)
            if work_dir is not prev_dir:
                prev_dir = work_dir
                mkdir(work_dir)

            # Queue mode (multiprocessing)
            commands = self.compile_command(source, object, inc_paths)
            if commands is not None:
                queue.append({
                    'source': source,
                    'object': object,
                    'commands': commands,
                    'work_dir': work_dir,
                    'chroot': self.CHROOT
                })
            else:
                objects.append(object)

        # Use queues/multiprocessing if cpu count is higher than setting
        jobs = self.jobs if self.jobs else cpu_count()
        if jobs > CPU_COUNT_MIN and len(queue) > jobs:
            return self.compile_queue(queue, objects)
        else:
            return self.compile_seq(queue, objects)

    def compile_seq(self, queue, objects):
        for item in queue:
            result = compile_worker(item)

            self.compiled += 1
            self.progress("compile", item['source'], build_update=True)
            for res in result['results']:
                self.debug("Command: %s" % ' '.join(res['command']))
                self.compile_output([
                    res['code'],
                    res['output'],
                    res['command']
                ])
            objects.append(result['object'])
        return objects

    def compile_queue(self, queue, objects):
        jobs_count = int(self.jobs if self.jobs else cpu_count())
        p = Pool(processes=jobs_count)

        results = []
        for i in range(len(queue)):
            results.append(p.apply_async(compile_worker, [queue[i]]))

        itr = 0
        while True:
            itr += 1
            if itr > 30000:
                p.terminate()
                p.join()
                raise ToolException("Compile did not finish in 5 minutes")

            pending = 0
            for r in results:
                if r._ready is True:
                    try:
                        result = r.get()
                        results.remove(r)

                        self.compiled += 1
                        self.progress("compile", result['source'], build_update=True)
                        for res in result['results']:
                            self.debug("Command: %s" % ' '.join(res['command']))
                            self.compile_output([
                                res['code'],
                                res['output'],
                                res['command']
                            ])
                        objects.append(result['object'])
                    except ToolException, err:
                        p.terminate()
                        p.join()
                        raise ToolException(err)
                else:
                    pending += 1
                    if pending > jobs_count:
                        break


            if len(results) == 0:
                break

            sleep(0.01)

        results = None
        p.terminate()
        p.join()

        return objects

    def compile_command(self, source, object, includes):
        # Check dependencies
        _, ext = splitext(source)
        ext = ext.lower()

        if ext == '.c' or  ext == '.cpp':
            base, _ = splitext(object)
            dep_path = base + '.d'
            deps = self.parse_dependencies(dep_path) if (exists(dep_path)) else []
            if len(deps) == 0 or self.need_update(object, deps):
                if ext == '.c':
                    return self.compile_c(source, object, includes)
                else:
                    return self.compile_cpp(source, object, includes)
        elif ext == '.s':
            deps = [source]
            if self.need_update(object, deps):
                return self.assemble(source, object, includes)
        else:
            return False

        return None

    def compile_output(self, output=[]):
        _rc = output[0]
        _stderr = output[1]
        command = output[2]

        # Parse output for Warnings and Errors
        self.parse_output(_stderr)
        self.debug("Return: %s"% _rc)
        for error_line in _stderr.splitlines():
            self.debug("Output: %s"% error_line)

        # Check return code
        if _rc != 0:
            for line in _stderr.splitlines():
                self.tool_error(line)
            raise ToolException(_stderr)

    def compile(self, cc, source, object, includes):
        _, ext = splitext(source)
        ext = ext.lower()

        command = cc + ['-D%s' % s for s in self.get_symbols()] + ["-I%s" % i for i in includes] + ["-o", object, source]

        if hasattr(self, "get_dep_opt"):
            base, _ = splitext(object)
            dep_path = base + '.d'
            command.extend(self.get_dep_opt(dep_path))

        if hasattr(self, "cc_extra"):
            command.extend(self.cc_extra(base))

        return [command]

    def compile_c(self, source, object, includes):
        return self.compile(self.cc, source, object, includes)

    def compile_cpp(self, source, object, includes):
        return self.compile(self.cppc, source, object, includes)

    def build_library(self, objects, dir, name):
        lib = self.STD_LIB_NAME % name
        fout = join(dir, lib)
        if self.need_update(fout, objects):
            self.info("Library: %s" % lib)
            self.archive(objects, fout)

    def link_program(self, r, tmp_path, name):
        ext = 'bin'
        if hasattr(self.target, 'OUTPUT_EXT'):
            ext = self.target.OUTPUT_EXT

        if hasattr(self.target, 'OUTPUT_NAMING'):
            self.var("binary_naming", self.target.OUTPUT_NAMING)
            if self.target.OUTPUT_NAMING == "8.3":
                name = name[0:8]
                ext = ext[0:3]

        filename = name+'.'+ext
        elf = join(tmp_path, name + '.elf')
        bin = join(tmp_path, filename)

        if self.need_update(elf, r.objects + r.libraries + [r.linker_script]):
            self.progress("link", name)
            self.link(elf, r.objects, r.libraries, r.lib_dirs, r.linker_script)

        if self.need_update(bin, [elf]):
            self.progress("elf2bin", name)

            self.binary(r, elf, bin)

        self.var("compile_succeded", True)
        self.var("binary", filename)

        return bin

    def default_cmd(self, command):
        _stdout, _stderr, _rc = run_cmd(command)
        # Print all warning / erros from stderr to console output
        for error_line in _stderr.splitlines():
            print error_line

        self.debug("Command: %s"% ' '.join(command))
        self.debug("Return: %s"% _rc)

        for output_line in _stdout.splitlines():
            self.debug("Output: %s"% output_line)
        for error_line in _stderr.splitlines():
            self.debug("Errors: %s"% error_line)

        if _rc != 0:
            for line in _stderr.splitlines():
                self.tool_error(line)
            raise ToolException(_stderr)

    ### NOTIFICATIONS ###
    def info(self, message):
        self.notify({'type': 'info', 'message': message})

    def debug(self, message):
        if self.VERBOSE:
            if type(message) is ListType:
                message = ' '.join(message)
            message = "[DEBUG] " + message
            self.notify({'type': 'debug', 'message': message})

    def cc_info(self, severity, file, line, message, target_name=None, toolchain_name=None):
        self.notify({'type': 'cc',
                     'severity': severity,
                     'file': file,
                     'line': line,
                     'message': message,
                     'target_name': target_name,
                     'toolchain_name': toolchain_name})

    def progress(self, action, file, build_update=False):
        msg = {'type': 'progress', 'action': action, 'file': file}
        if build_update:
            msg['percent'] = 100. * float(self.compiled) / float(self.to_be_compiled)
        self.notify(msg)

    def tool_error(self, message):
        self.notify({'type': 'tool_error', 'message': message})

    def var(self, key, value):
        self.notify({'type': 'var', 'key': key, 'val': value})

from workspace_tools.settings import ARM_BIN
from workspace_tools.settings import GCC_ARM_PATH, GCC_CR_PATH, GCC_CS_PATH, CW_EWL_PATH, CW_GCC_PATH
from workspace_tools.settings import IAR_PATH

TOOLCHAIN_BIN_PATH = {
    'ARM': ARM_BIN,
    'uARM': ARM_BIN,
    'GCC_ARM': GCC_ARM_PATH,
    'GCC_CS': GCC_CS_PATH,
    'GCC_CR': GCC_CR_PATH,
    'GCC_CW_EWL': CW_EWL_PATH,
    'GCC_CW_NEWLIB': CW_GCC_PATH,
    'IAR': IAR_PATH
}

from workspace_tools.toolchains.arm import ARM_STD, ARM_MICRO
from workspace_tools.toolchains.gcc import GCC_ARM, GCC_CS, GCC_CR
from workspace_tools.toolchains.gcc import GCC_CW_EWL, GCC_CW_NEWLIB
from workspace_tools.toolchains.iar import IAR

TOOLCHAIN_CLASSES = {
    'ARM': ARM_STD,
    'uARM': ARM_MICRO,
    'GCC_ARM': GCC_ARM,
    'GCC_CS': GCC_CS,
    'GCC_CR': GCC_CR,
    'GCC_CW_EWL': GCC_CW_EWL,
    'GCC_CW_NEWLIB': GCC_CW_NEWLIB,
    'IAR': IAR
}

TOOLCHAINS = set(TOOLCHAIN_CLASSES.keys())
