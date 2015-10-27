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
from jinja2 import Template

from workspace_tools.paths import TOOLS_DATA, MBED_RPC

RPC_TEMPLATES_PATH = join(TOOLS_DATA, "rpc")

RPC_TEMPLATE = "RPCClasses.h"
CLASS_TEMPLATE = "class.cpp"
RPC_CLASSES_PATH = join(MBED_RPC, RPC_TEMPLATE)


def get_template(name):
    return Template(open(join(RPC_TEMPLATES_PATH, name)).read())


def write_rpc_classes(classes):
    template = get_template(RPC_TEMPLATE)
    open(RPC_CLASSES_PATH, "w").write(template.render({"classes":classes}))


RPC_CLASSES = (
    {
        "name": "DigitalOut",
        "cons_args": ["PinName"],
        "methods": [
            (None , "write", ["int"]),
            ("int", "read" , []),
        ]
    },
    {
        "name": "DigitalIn",
        "cons_args": ["PinName"],
        "methods": [
            ("int", "read" , []),
        ]
    },
    {
        "name": "DigitalInOut",
        "cons_args": ["PinName"],
        "methods": [
            ("int", "read"  , []),
            (None , "write" , ["int"]),
            (None , "input" , []),
            (None , "output", []),
        ]
    },
    {
        "name": "AnalogIn",
        "required": "ANALOGIN",
        "cons_args": ["PinName"],
        "methods": [
            ("float"         , "read"    , []),
            ("unsigned short", "read_u16", []),
        ]
    },
    {
        "name": "AnalogOut",
        "required": "ANALOGOUT",
        "cons_args": ["PinName"],
        "methods": [
            ("float", "read"     , []),
            (None   , "write"    , ["float"]),
            (None   , "write_u16", ["unsigned short"]),
        ]
    },
    {
        "name": "PwmOut",
        "required": "PWMOUT",
        "cons_args": ["PinName"],
        "methods": [
            ("float", "read"         , []),
            (None   , "write"        , ["float"]),
            (None   , "period"       , ["float"]),
            (None   , "period_ms"    , ["int"]),
            (None   , "pulsewidth"   , ["float"]),
            (None   , "pulsewidth_ms", ["int"]),
        ]
    },
    {
        "name": "SPI",
        "required": "SPI",
        "cons_args": ["PinName", "PinName", "PinName"],
        "methods": [
            (None , "format"   , ["int", "int"]),
            (None , "frequency", ["int"]),
            ("int", "write"    , ["int"]),
        ]
    },
    {
        "name": "Serial",
        "required": "SERIAL",
        "cons_args": ["PinName", "PinName"],
        "methods": [
            (None , "baud"     , ["int"]),
            ("int", "readable" , []),
            ("int", "writeable", []),
            ("int", "putc"     , ["int"]),
            ("int", "getc"     , []),
            ("int", "puts"     , ["const char *"]),
        ]
    },
    {
        "name": "Timer",
        "cons_args": [],
        "methods": [
            (None   , "start"  , []),
            (None   , "stop"   , []),
            (None   , "reset"  , []),
            ("float", "read"   , []),
            ("int"  , "read_ms", []),
            ("int"  , "read_us", []),
        ]
    }
)


def get_args_proto(args_types, extra=None):
    args = ["%s a%d" % (s, n) for n, s in enumerate(args_types)]
    if extra:
        args.extend(extra)
    return ', '.join(args)


def get_args_call(args):
    return ', '.join(["a%d"    % (n)    for n in range(len(args))])


classes = []
class_template = get_template(CLASS_TEMPLATE)

for c in RPC_CLASSES:
    c_args = c['cons_args']
    data = {
        'name': c['name'],
        'cons_type': ', '.join(c_args + ['const char*']),
        "cons_proto": get_args_proto(c_args, ["const char *name=NULL"]),
        "cons_call": get_args_call(c_args)
    }

    c_name = "Rpc" +  c['name']

    methods = []
    rpc_methods = []
    for r, m, a in c['methods']:
        ret_proto = r if r else "void"
        args_proto = "void"

        ret_defin = "return " if r else ""
        args_defin = ""

        if a:
            args_proto = get_args_proto(a)
            args_defin = get_args_call(a)

        proto = "%s %s(%s)"   % (ret_proto, m, args_proto)
        defin = "{%so.%s(%s);}" % (ret_defin, m, args_defin)
        methods.append("%s %s" % (proto, defin))

        rpc_method_type = [r] if r else []
        rpc_method_type.append(c_name)
        rpc_method_type.extend(a)
        rpc_methods.append('{"%s", rpc_method_caller<%s, &%s::%s>}' % (m, ', '.join(rpc_method_type), c_name, m))

    data['methods'] = "\n    ".join(methods)
    data['rpc_methods'] = ",\n            ".join(rpc_methods)

    class_decl = class_template.render(data)
    if 'required' in c:
        class_decl = "#if DEVICE_%s\n%s\n#endif" % (c['required'], class_decl)

    classes.append(class_decl)

write_rpc_classes('\n\n'.join(classes))
