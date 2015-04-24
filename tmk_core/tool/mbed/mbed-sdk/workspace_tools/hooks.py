# Configurable hooks in the build system. Can be used by various platforms
# to customize the build process.

################################################################################
# Hooks for the various parts of the build process

# Internal mapping of hooks per tool
_hooks = {}

# Internal mapping of running hooks
_running_hooks = {}

# Available hook types
_hook_types = ["binary", "compile", "link", "assemble"]

# Available hook steps
_hook_steps = ["pre", "replace", "post"]

# Hook the given function. Use this function as a decorator
def hook_tool(function):
    tool = function.__name__
    tool_flag = "_" + tool + "_done"
    def wrapper(t_self, *args, **kwargs):
        # if a hook for this tool is already running, it's most likely
        # coming from a derived class, so don't hook the super class version
        if _running_hooks.get(tool, False):
            return function(t_self, *args, **kwargs)
        _running_hooks[tool] = True
        # If this tool isn't hooked, return original function
        if not _hooks.has_key(tool):
            res = function(t_self, *args, **kwargs)
            _running_hooks[tool] = False
            return res
        tooldesc = _hooks[tool]
        setattr(t_self, tool_flag, False)
        # If there is a replace hook, execute the replacement instead
        if tooldesc.has_key("replace"):
            res = tooldesc["replace"](t_self, *args, **kwargs)
        # If the replacement has set the "done" flag, exit now
        # Otherwise continue as usual
        if getattr(t_self, tool_flag, False):
            _running_hooks[tool] = False
            return res
        # Execute pre-function before main function if specified
        if tooldesc.has_key("pre"):
            tooldesc["pre"](t_self, *args, **kwargs)
        # Execute the main function now
        res = function(t_self, *args, **kwargs)
        # Execute post-function after main function if specified
        if tooldesc.has_key("post"):
            post_res = tooldesc["post"](t_self, *args, **kwargs)
            _running_hooks[tool] = False
            return post_res or res
        else:
            _running_hooks[tool] = False
            return res
    return wrapper

class Hook:
    def __init__(self, target, toolchain):
        _hooks.clear()
        self._cmdline_hooks = {}
        self.toolchain = toolchain
        target.init_hooks(self, toolchain.__class__.__name__)

    # Hook various functions directly
    def _hook_add(self, hook_type, hook_step, function):
        if not hook_type in _hook_types or not hook_step in _hook_steps:
            return False
        if not hook_type in _hooks:
            _hooks[hook_type] = {}
        _hooks[hook_type][hook_step] = function
        return True

    def hook_add_compiler(self, hook_step, function):
        return self._hook_add("compile", hook_step, function)

    def hook_add_linker(self, hook_step, function):
        return self._hook_add("link", hook_step, function)

    def hook_add_assembler(self, hook_step, function):
        return self._hook_add("assemble", hook_step, function)

    def hook_add_binary(self, hook_step, function):
        return self._hook_add("binary", hook_step, function)

    # Hook command lines
    def _hook_cmdline(self, hook_type, function):
        if not hook_type in _hook_types:
            return False
        self._cmdline_hooks[hook_type] = function
        return True

    def hook_cmdline_compiler(self, function):
        return self._hook_cmdline("compile", function)

    def hook_cmdline_linker(self, function):
        return self._hook_cmdline("link", function)

    def hook_cmdline_assembler(self, function):
        return self._hook_cmdline("assemble", function)

    def hook_cmdline_binary(self, function):
        return self._hook_cmdline("binary", function)

    # Return the command line after applying the hook
    def _get_cmdline(self, hook_type, cmdline):
        if self._cmdline_hooks.has_key(hook_type):
            cmdline = self._cmdline_hooks[hook_type](self.toolchain.__class__.__name__, cmdline)
        return cmdline

    def get_cmdline_compiler(self, cmdline):
        return self._get_cmdline("compile", cmdline)

    def get_cmdline_linker(self, cmdline):
        return self._get_cmdline("link", cmdline)

    def get_cmdline_assembler(self, cmdline):
        return self._get_cmdline("assemble", cmdline)

    def get_cmdline_binary(self, cmdline):
        return self._get_cmdline("binary", cmdline)

################################################################################

