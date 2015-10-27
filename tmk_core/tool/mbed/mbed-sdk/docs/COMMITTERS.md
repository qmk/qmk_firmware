# Committing changes to mbedmicro/mbed
* Our current branching model is very simple. We are using ```master``` branch to merge all pull requests.
* Based on stable ```SHA``` version of ```master``` branch we decide to release and att he same time ```tag``` our build release.
* Our current release versioning follows simple integer version: ```94```, ```95```, ```96``` etc.

# Committer Guide

## How to decide what release(s) should be patched
This section provides a guide to help a committer decide the specific base branch that a change set should be merged into.

Currently our default branch is ```master``` branch. All pull requests should be created against ```master``` branch. 
mbed SDK is released currently on master branch under certain tag name (see [Git tagging basics]( http://git-scm.com/book/en/v2/Git-Basics-Tagging)). You can see mbed SDK tags and switch between them to for example go back to previous mbed SDK release. 
```
$ git tag
```

Please note: mebd SDK ```master``` branch's ```HEAD``` is our latest code and may not be as stable as you expect. We are putting our best effort to run regression testing (in-house) against pull requests and latest code.
Each commit to ```master``` will trigger [GitHub's Travis Continuous Integration](https://travis-ci.org/mbedmicro/mbed/builds).

### Pull request
Please send pull requests with changes which are:
* Complete (your code will compile and perform as expected).
* Tested on hardware.
 * You can use included mbed SDK test suite to perform testing. See TESTING.md.
 * If your change, feature do not have a test case included please add one (or more) to cover new functionality.
 * If you can't test your functionality describe why.
* Documented source code:
 * New, modified functions have descriptive comments.
 * You follow coding rules and styles provided by mbed SDK project.
* Documented pull request description:
 * Description of changes is added - explain your change / enhancement.
 * References to existing issues, other pull requests or forum discussions are included.
 * Test results are added.

After you send us your pull request our Gate Keeper will change the state of pull request to:
•	``` enhancement``` or ```bug``` when pull request creates new improvement or fixed issue.
Than we will set for you labels:
•	```review``` to let you know your pull request is under review and you can expect review related comments from us.
•	```in progress``` when you pull request requires some additional change which will for now block this pull request from merging.
At the end we will remove ```review``` label and merge your change if everything goes well.

## C++ coding rules & coding guidelines
### Rules
* The mbed SDK code follows K&R style (Reference: [K&R style](http://en.wikipedia.org/wiki/Indent_style#K.26R_style)) with at least 2 exceptions which can be found in the list below the code snippet:

```c++
static const PinMap PinMap_ADC[] = {
    {PTC2, ADC0_SE4b, 0},
    {NC , NC , 0}
};

uint32_t adc_function(analogin_t *obj, uint32_t options)
{
    uint32_t instance = obj->adc >> ADC_INSTANCE_SHIFT;
    switch (options) {
        case 1:
            timeout = 6;
            break;
        default:
            timeout = 10;
            break;
    }

    while (!adc_hal_is_conversion_completed(instance, 0)) {
        if (timeout == 0) {
            break;
        } else {
            timeout--;
        }
    }

    if (obj->adc == ADC_CHANNEL0) {
        adc_measure_channel(instance);
        adc_stop_channel(instance);
    } else {
        error("channel not available");
    }

#if DEBUG
    for (uint32_t i = 0; i < 10; i++) {
        printf("Loop : %d", i);
    }
#endif
    return adc_hal_get_conversion_value(instance, 0);
}
```
* Indentation - 4 spaces. Please do not use tabs!
* Braces - K&R, except for functions where the opening brace is on the new line.
* 1 TBS - use braces for statements ```if```, ```else```, ```while```, ```for``` (exception from K&R) Reference: [1TBS](http://en.wikipedia.org/wiki/Indent_style#Variant:_1TBS)).
* One line per statement.
* Preprocessor macro starts at the beginning of a new line, the code inside is indented accordingly the code above it.
* Cases within switch are indented (exception from K&R).
* Space after statements if, while, for, switch, same applies to binary and ternary operators.
* Each line has preferably at most 120 characters.
* For pointers, ```*``` is adjacent to a name (analogin_t *obj).
* Don't leave trailing spaces at the end of lines.
* Empty lines should have no trailing spaces.
* Unix line endings are default option for files.
* Use capital letters for macros.
* A file should have an empty line at the end.
and:
* We are not using C++11 yet so do not write code compliant to this standard.
* We are not using libraries like ```BOOST``` so please so not include any ```BOOST``` headers to your code.
* C++ & templates: please take under consideration templates are not fully supported by cross-compilers. You may have difficulties compiling template code few cross-compilers so make sure your template code compilers for more than one compiler.

### Naming conventions
Classes:
* Begins with a capital letter, and each word in it begins also with a capital letter (```AnalogIn```, ```BusInOut```).
* Methods contain small letters, distinct words separated by underscore.
* Private members starts with an underscore.

User defined types (typedef):
* Structures - suffix ```_t``` - to denote it is user defined type
* Enumeration - the type name and values name - same naming convention as classes (e.g ```MyNewEnum```)

Functions:
* Contain lower case letters (as methods within classes)
* Distinct words separated by underscore (```wait_ms```, ```read_u16```)
* Please make sure that in your module all functions have unique prefix so when your module is compiled with other modules function names (and e.g. extern global variable names) are not in naming conflict.

Example code look&feel:
```c++
#define ADC_INSTANCE_SHIFT 8

class AnalogIn {
public:
    /** Create an AnalogIn, connected to the specified pin
    *
    * @param pin AnalogIn pin to connect to
    * @param name (optional) A string to identify the object
    */
    AnalogIn(PinName pin) {
        analogin_init(&_adc, pin);
    }

    /** Read the input voltage, represented as a float in the range [0.0, 1.0]
    *
    * @returns
    * A floating-point value representing the current input voltage, measured as a percentage
    */
    uint32_t read() {
        return analogin_read(&_adc, operation);
    }

protected:
    analogin_t _adc;
};

typedef enum {
    ADC0_SE0 = (0 << ADC_INSTANCE_SHIFT) | 0,
} ADCName;

struct analogin_s {
    ADCName adc;
};

typedef struct analogin_s analogin_t;
```
### Doxygen documentation
All functions / methods should contain a documentation using doxygen javadoc in a header file. More information regarding writing API Documentation, follow [this](https://mbed.org/handbook/API-Documentation) link.

Example of well documentet code:
```c++
#ifndef ADC_H
#define ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/** ADC Measurement method
 *
 * @param obj Pointer to the analogin object.
 * @param options Options to be enabled by ADC peripheral.
 *
 * @returns
 * Measurement value on defined ADC channel.
 */
uint32_t adc_function(analogin_t *obj, uint32_t options)

#ifdef __cplusplus
}
#endif

#endif
```
### C/C++ Source code indenter
In Mbed project you can use AStyle (Reference: [Artistic Style](http://astyle.sourceforge.net/)) source code indenter to help you auto format your source code. It will for sure not correct all your coding styles but for sure will eliminate most of them. You can download AStyle from this location.

Official Mbed SDK styles include below AStyle styles (defined by command line switched):
```
--style=kr --indent=spaces=4 --indent-switches
```
To format your file you can execute below command. Just replace ```$(FULL_CURRENT_PATH)``` with path to your source file.
```
$ astyle.exe --style=kr --indent=spaces=4 --indent-switches $(FULL_CURRENT_PATH)
```

## Python coding rules & coding guidelines
Some of our tools in workspace_tools are written in ```Python 2.7```. In case of developing tools for python we prefer to keep similar code styles across all Python source code. Please note that not all rules must be enforced. For example we do not limit you to 80 characters per line, just be sure your code can fit to widescreen display.

Please stay compatible with ```Python 2.7``` but nothing stops you to write your code so in the future it will by Python 3 friendly.

Please check our Python source code (especially ```test_api.py``` and ```singletest.py```) to get notion of how your new code should look like). We know our code is not perfect but please try to fit the same coding style to existing code so source looks consistent and is not series of different flavors.

Some general guidelines:
* Use Python idioms, please refer to one of many on-line guidelines how to write Pythonic code: [Code Like a Pythonista: Idiomatic Python](http://python.net/~goodger/projects/pycon/2007/idiomatic/handout.html).
* Please do not use TABs. Please use 4 spaces instead for indentations.
* Please put space character between operators, after comma etc.
* Please document your code, write comments and ```doc``` sections for each function or class you implement.

### Static Code Analizers for Python
If you are old-school developer for sure you remember tools like lint. "lint was the name originally given to a particular program that flagged some suspicious and non-portable constructs (likely to be bugs) in C language source code." Now lint-like programs are used to check similar code issues for multiple languages, also for Python. Please do use them if you want to commit new code to workspace_tools and other mbed SDK Python tooling.

Below is the list Python lint tools you may want to use:

* [pyflakes](https://pypi.python.org/pypi/pyflakes) - Please scan your code with pyflakes and remove all issues reported by it. If you are unsure if something should be modified or not you can skip lint report related fix and report this issue as possible additional commit in your pull request description.

* [pylint](http://www.pylint.org/) - Please scan your code with pylint and check if there are any issues which can be resolved and are obvious "to fix" bugs. For example you may forgot to add 'self' as first parameter in class method parameter list or you are calling unknown functions / functions from not imported modules.

* [pychecker](http://pychecker.sourceforge.net/) - optional, but more the merrier ;)

Example Python look&feel:
```python
class HostRegistry:
    """ Class stores registry with host tests and objects representing them
    """
    HOST_TESTS = {} # host_test_name -> host_test_ojbect
   
    def register_host_test(self, ht_name, ht_object):
       """ Registers (removes) host test by name from HOST_TESTS registry
           if host test is not already registered (check by name).
       """
       if ht_name not in self.HOST_TESTS:
           self.HOST_TESTS[ht_name] = ht_object
   
    def unregister_host_test(self):
       """ Unregisters (removes) host test by name from HOST_TESTS registry.
       """
       if ht_name in HOST_TESTS:
           self.HOST_TESTS[ht_name] = None
   
    def get_host_test(self, ht_name):
       """ Returns HOST_TEST if host name is valid.
           In case no host test is available return None
       """
       return self.HOST_TESTS[ht_name] if ht_name in self.HOST_TESTS else None
   
    def is_host_test(self, ht_name):
       """ Function returns True if host name is valid (is in HOST_TESTS)
       """
       return ht_name in self.HOST_TESTS
```

## Testing
Please refer to TESTING.md document for detais regarding mbed SDK test suite and build scripts included in ```mbed/workspace_tools/```.

## Before pull request checklist
* Your pull request description section contains:
 * Rationale – tell us why you submitted this pull request. This is your change to write us summary of your change.
 * Description – describe changes you’ve made and tell us which new features / functionalities were implemented.
 * Manual / Cookbook / Handbook – you can put here manual, cookbook or handbook related to your change / enhancement. Your documentation can stay with pull request.
 * Test results (if applicable).
* Make sure you followed project's coding rules and styles.
* No dependencies are created to external C/C++ libraries which are not included already in our repository.
* Please make sure that in your module all functions have unique prefix (no name space collisions).
* You reused existing functionality, please do not add or rewrite existing code. E.g. use mbed’s ```FunctionPointer``` if possible to store your function pointers. Do not write another wrapper for it. We already got one. If some functionality is missing, just add it! Extend our APIs wisely!
* Were you consistent? Please continue using style / code formatting, variables naming etc. in file they are modifying.
* Your code compiles and links. Also doesn’t generate additional compilation warnings.
