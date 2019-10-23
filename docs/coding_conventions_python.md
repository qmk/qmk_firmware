# Coding Conventions (Python)

Most of our style follows PEP8 with some local modifications to make things less nit-picky. 

* We target Python 3.5 for compatability with all supported platforms.
* We indent using four (4) spaces (soft tabs)
* We encourage liberal use of comments
  * Think of them as a story describing the feature
  * Use them liberally to explain why particular decisions were made.
  * Do not write obvious comments
  * If you not sure if a comment is obvious, go ahead and include it.
* We require useful docstrings for all functions.
* In general we don't wrap lines, they can be as long as needed. If you do choose to wrap lines please do not wrap any wider than 76 columns.
* Some of our practices conflict with the wider python community to make our codebase more approachable to non-pythonistas.

# YAPF

You can use [yapf](https://github.com/google/yapf) to style your code. We provide a config in [setup.cfg](setup.cfg).

# Imports

We don't have a hard and fast rule for when to use `import ...` vs `from ... import ...`. Understandability and maintainability is our ultimate goal.

Generally we prefer to import specific function and class names from a module to keep code shorter and easier to understand. Sometimes this results in a name that is ambiguous, and in such cases we prefer to import the module instead. You should avoid using the "as" keyword when importing, unless you are importing a compatability module.

Imports should be one line per module. We group import statements together using the standard python rules- system, 3rd party, local.

Do not use `from foo import *`. Supply a list of objects you want to import instead, or import the whole module.

## Import Examples

Good:

```
from qmk import effects

effects.echo()
```

Bad:

```
from qmk.effects import echo

echo()  # It's unclear where echo comes from
```

Good:

```
from qmk.keymap import compile_firmware

compile_firmware()
```

OK, but the above is better:

```
import qmk.keymap

qmk.keymap.compile_firmware()
```

# Statements

One statement per line.

Even when allowed (EG `if foo: bar`) we do not combine 2 statements onto a single line.

# Naming

`module_name`, `package_name`, `ClassName`, `method_name`, `ExceptionName`, `function_name`, `GLOBAL_CONSTANT_NAME`, `global_var_name`, `instance_var_name`, `function_parameter_name`, `local_var_name`.

Function names, variable names, and filenames should be descriptive; eschew abbreviation. In particular, do not use abbreviations that are ambiguous or unfamiliar to readers outside your project, and do not abbreviate by deleting letters within a word.

Always use a .py filename extension. Never use dashes.

## Names to Avoid

* single character names except for counters or iterators. You may use "e" as an exception identifier in try/except statements.
* dashes (-) in any package/module name
* __double_leading_and_trailing_underscore__ names (reserved by Python)

# Docstrings

To maintain consistency with our docstrings we've set out the following guidelines.

* Use markdown formatting
* Always use triple-dquote docstrings with at least one linebreak: `"""\n"""`
* First line is a short (< 70 char) description of what the function does
* If you need more in your docstring leave a blank line between the description and the rest.
* Start indented lines at the same indent level as the opening triple-dquote
* Document all function arguments using the format described below
* If present, Args:, Returns:, and Raises: should be the last three things in the docstring, separated by a blank line each.

## Simple docstring example

```
def my_awesome_function():
    """Return the number of seconds since 1970 Jan 1 00:00 UTC.
    """
    return int(time.time())
```

## Complex docstring example

```
def my_awesome_function():
    """Return the number of seconds since 1970 Jan 1 00:00 UTC.

    This function always returns an integer number of seconds.
    """
    return int(time.time())
```

## Function arguments docstring example

```
def my_awesome_function(start=None, offset=0):
    """Return the number of seconds since 1970 Jan 1 00:00 UTC.

    This function always returns an integer number of seconds.


    Args:
        start
            The time to start at instead of 1970 Jan 1 00:00 UTC

        offset
            Return an answer that has this number of seconds subtracted first

    Returns:
        An integer describing a number of seconds.

    Raises:
        ValueError
            When `start` or `offset` are not positive numbers
    """
    if start < 0 or offset < 0:
        raise ValueError('start and offset must be positive numbers.')

    if not start:
        start = time.time()

    return int(start - offset)
```

# Exceptions

Exceptions are used to handle exceptional situations. They should not be used for flow control. This is a break from the python norm of "ask for forgiveness." If you are catching an exception it should be to handle a situation that is unusual.

If you use a catch-all exception for any reason you must log the exception and stacktrace using cli.log.

Make your try/except blocks as short as possible. If you need a lot of try statements you may need to restructure your code.

# Tuples

When defining one-item tuples always include a trailing comma so that it is obvious you are using a tuple. Do not rely on implicit one-item tuple unpacking. Better still use a list which is unambiguous.

This is particularly important when using the printf-style format strings that are commonly used.

# Lists and Dictionaries

We have configured YAPF to differentiate between sequence styles with a trailing comma. When a trailing comma is omitted YAPF will format the sequence as a single line. When a trailing comma is included YAPF will format the sequence with one item per line.

You should generally prefer to keep short definition on a single line. Break out to multiple lines sooner rather than later to aid readability and maintainability.

# Parentheses

Avoid excessive parentheses, but do use parentheses to make code easier to understand. Do not use them in return statements unless you are explicitly returning a tuple, or it is part of a math expression.

# Format Strings

We generally prefer printf-style format strings. Example:

```
name = 'World'
print('Hello, %s!' % (name,))
```

This style is used by the logging module, which we make use of extensively, and we have adopted it in other places for consistency. It is also more familiar to C programmers, who are a big part of our casual audience.

Our included CLI module has support for using these without using the percent (%) operator. Look at `cli.echo()` and the various `cli.log` functions (EG, `cli.log.info()`) for more details.

# Comprehensions & Generator Expressions

We encourage the liberal use of comprehensions and generators, but do not let them get too complex. If you need complexity fall back to a for loop that is easier to understand.

# Lambdas

OK to use but probably should be avoided. With comprehensions and generators the need for lambdas is not as strong as it once was.

# Conditional Expressions

OK in variable assignment, but otherwise should be avoided.

Conditional expressions are if statements that are in line with code. For example:

```
x = 1 if cond else 2
```

It's generally not a good idea to use these as function arguments, sequence items, etc. It's too easy to overlook.

# Default Argument Values

Encouraged, but values must be immutable objects.

When specifying default values in argument lists always be careful to specify objects that can't be modified in place. If you use a mutable object the changes you make will persist between calls, which is usually not what you want. Even if that is what you intend to do it is confusing for others and will hinder understanding.

Bad:

```
def my_func(foo={}):
    pass
```

Good:

```
def my_func(foo=None):
    if not foo:
        foo = {}
```

# Properties

Always use properties instead of getter and setter functions.

```
class Foo(object):
    def __init__(self):
        self._bar = None

    @property
    def bar(self):
        return self._bar

    @bar.setter
    def bar(self, bar):
        self._bar = bar
```

# True/False Evaluations

You should generally prefer the implicit True/False evaluation in if statements, rather than checking equivalency.

Bad:

```
if foo == True:
    pass

if bar == False:
    pass
```

Good:

```
if foo:
    pass

if not bar:
    pass
```

# Decorators

Use when appropriate. Try to avoid too much magic unless it helps with understanding.

# Threading and Multiprocessing

Should be avoided. If you need this you will have to make a strong case before we merge your code.

# Power Features

Python is an extremely flexible language and gives you many fancy features such as custom metaclasses, access to bytecode, on-the-fly compilation, dynamic inheritance, object reparenting, import hacks, reflection, modification of system internals, etc.

Don't use these.

Performance is not a critical concern for us, and code understandability is. We want our codebase to be approachable by someone who only has a day or two to play with it. These features generally come with a cost to easy understanding, and we would prefer to have code that can be readily understood over faster or more compact code.

Note that some standard library modules use these techniques and it is ok to make use of those modules. But please keep readability and understandability in mind when using them.

# Type Annotated Code

For now we are not using any type annotation system, and would prefer that code remain unannotated. We may revisit this in the future.

# Function length

Prefer small and focused functions.

We recognize that long functions are sometimes appropriate, so no hard limit is placed on function length. If a function exceeds about 40 lines, think about whether it can be broken up without harming the structure of the program.

Even if your long function works perfectly now, someone modifying it in a few months may add new behavior. This could result in bugs that are hard to find. Keeping your functions short and simple makes it easier for other people to read and modify your code.

You could find long and complicated functions when working with some code. Do not be intimidated by modifying existing code: if working with such a function proves to be difficult, you find that errors are hard to debug, or you want to use a piece of it in several different contexts, consider breaking up the function into smaller and more manageable pieces.

# FIXMEs

It is OK to leave FIXMEs in code. Why? Encouraging people to at least document parts of code that need to be thought out more (or that are confusing) is better than leaving this code undocumented.

All FIXMEs should be formatted like:

```
FIXME(username): Revisit this code when the frob feature is done.
```

...where username is your GitHub username.

# Unit Tests

These are good. We should have some one day.
