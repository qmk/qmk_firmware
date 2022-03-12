"""Generates an interactive list of supported processors."""
from dataclasses import dataclass
from multiprocessing.sharedctypes import Value
from typing import List, Union, ClassVar


@dataclass
class Processor:
    """Holds information about supported processors."""
    family_name: str                        # e.g. "atmega32u4", or "STM32F042"
    category: str                           # Can be "chibios", "lufa", or "vusb"
    valid_affixes: List[Union[str, None]]   # e.g. ['4', '6']. Can contain None, if the lack of an affix is also valid. Must not be empty.
    bootloader: str                         # e.g. "atmel-dfu", or "stm32-dfu"

    cortex_prefix: ClassVar[str] = "cortex"
    
    stm32_prefix: ClassVar[str] = "STM32"
    stm32_affix_separator: ClassVar[str] = "x"

    valid_categories: ClassVar[List[str]] = ["chibios", "lufa", "vusb"]
    valid_bootloaders: ClassVar[List[str]] = ["", "halfkay", "stm32-dfu", "tinyuf2", "stm32duino", "gd32v-dfu", "wb32-dfu", "atmel-dfu", "bootloadhid", "usbasploader"]

    def __post_init__(self):
        """Performs checks on variables that were set."""
        if not self.family_name:
            raise ValueError("Family name must not be an empty string.")

        if self.bootloader not in Processor.valid_bootloaders:
            raise ValueError(f"Bootloader {self.bootloader} is not valid. Use one of {Processor.valid_bootloaders}.")
        
        if self.category not in Processor.valid_categories:
            raise ValueError(f"Category {self.category} is not valid. Use one of {Processor.valid_categories}.")

        if not self.valid_affixes:
            raise ValueError("The list of valid affixes must not be empty, but can be [None], if no valid affix exists.")

    @property
    def listable_affixes(self):
        """Equals the 'valid_affixes', except for the 'None' affix, which is not an actual affix. 
        
        'None' is just a placeholder for when no affix is valid and the 'family_name' is the only 'full_name' of the processor.
        """
        return [affix for affix in self.valid_affixes if affix is not None]

    @property
    def full_names(self) -> List[str]:
        """Gives all valid names for this processor family, e.g. ["STM32F303x8", "STM32F303xC", "STM32F303xE"].

        Returns:
            List[str]: The list of valid names.
        """
        if not self.listable_affixes:
            # If no listable affixes exist, the family name is the only full name of this processor family, e.g. "atmega32u4".
            return [self.family_name]

        elif self.is_stm32:
            # Introduce the STM32 affix separator into the name.
            return [f"{self.family_name}{Processor.stm32_affix_separator}{affix}" for affix in self.listable_affixes]

        else:
            # Do not use any affix separator.
            return [f"{self.family_name}{affix}" for affix in self.listable_affixes]

    def has_prefix(self, prefix: str) -> bool:
        """Determine, whether this processor family name has a certain prefix."""
        return self.family_name.startswith(prefix)

    @property
    def is_generic_cortex(self) -> bool:
        """Determine, whether this processor definition specifies a generic 'cortex' device."""
        return self.has_prefix(Processor.cortex_prefix)

    @property
    def is_stm32(self) -> bool:
        """Determine, whether this processor definition specifies an 'STM32' device."""
        return self.has_prefix(Processor.stm32_prefix)

    def matches_family(self, processor_name: str) -> bool:
        """Matches the processor name against the family name.

        Args:
            processor_name (str): The name to match against a family of processors.

        Returns:
            bool: True, if the family matches, False otherwise.
        """
        return processor_name.startswith(self.family_name)

    def matches_precisely(self, processor_name: str) -> bool:
        """Matches the processor name against the family name.

        Args:
            processor_name (str): The name to match against a family of processors.

        Returns:
            bool: True, if the family matches exactly, False otherwise.
        """
        return processor_name == self.family_name and None in self.valid_affixes

    def matches_affix(self, processor_name: str) -> bool:
        """Matches the processor name against affixes of arbitrary length in the list of valid affixes.

        Args:
            processor_name (str): The name to match against affixes.

        Returns:
            bool: True, if the affix matches on of the valid affixes, False otherwise
        """
        return any([processor_name[-len(affix):] == affix for affix in self.valid_affixes if affix is not None])

    def matches(self, processor_name: str) -> bool:
        """Checks, whether the provided processor name matches this Processor definition.

        Args:
            processor_name (str): The processor name to check.

        Returns:
            bool: True, if the name matches, False otherwise.
        """
        if self.matches_precisely(processor_name):
            return True

        if not self.matches_family(processor_name):
            return False

        return self.matches_affix(processor_name)


class ProcessorFactory:
    """A factory for generating a list of supported processors, and matching a processor name against it."""
    
    def __init__(self):
        """Initialize the ProcessorFactory with an empty list of supported processors.
        
        Add new processors by using `new_processor()`"""
        self.processors: List[Processor] = []

    @property
    def processor_names(self):
        names = []

        for processor in self.processors:
            if processor.is_generic_cortex:
                # Do not add generic 'cortex' processor definitions to the list of processor names.
                ...

            else:
                names.extend(processor.full_names)

        return names

    def get_matching_processor(self, processor_name: str) -> Union[Processor, None]:
        """Returns the processor that matches the provided name.

        Args:
            processor_name (str): The name to match against.

        Raises:
            ValueError: If there were multiple processors that matched. The provided name must be more specific.

        Returns:
            Union[Processor, None]: The processor, in case of a match, None otherwise.
        """
        try:
            matching_processors = [processor for processor in self.processors if processor.matches(processor_name)]

            if not matching_processors:
                return None

            elif len(matching_processors) > 1:
                raise ValueError("Processor definition not specific enough, multiple matches: %s", matching_processors)

            else:
                # Only one matching processor was found, which is desired.
                return matching_processors[0]

        except IndexError:
            return None

    def processor_exists(self, processor: Processor) -> bool:
        """Check, if a processor already exists in the list.

        Only add new processor definitions.

        Args:
            processor (Processor): The processor for wich to check existence in the list of processors.

        Raises:
            ValueError: If the processor already exists in the list.

        Returns:
            bool: False, if the processor does not yet exist.
        """
        if any([processor == p for p in self.processors]):
            raise ValueError(f"Processor '{processor}' already exists in the list of processors.")

        else:
            return False

    def add_processor(self, processor: Processor):
        """Add a processor to the internal list of supported processors.

        Only adds the processor, if it does not exist yet.

        Args:
            processor (Processor): The processor to add.
        """
        if not self.processor_exists(processor):
            self.processors.append(processor)

    def new_processor(self, family_name: str, category: str, default_bootloader = "", valid_affixes: List[Union[str, None]] = [None]):
        """Generate a new processor and add it to the list of known processors.

        The below example arguments are given for an 'STM32F042x6' processor.

        Args:
            family_name (str): The family name of the processor (e.g. 'STM32').
            category (str): Decides on the variant of the application to be built (e.g. 'chibios').
            default_bootloader (str, optional): Selects the default bootloader variant of the processor (e.g. 'stm32-dfu'). Defaults to "".
            valid_affixes (List[Union[str, None]], optional): A list of valid affixes for a processor (e.g. ['4', '6']). Defaults to [None].
        """
        if category in Processor.valid_categories and default_bootloader in Processor.valid_bootloaders:
            self.add_processor(Processor(family_name, category, valid_affixes, default_bootloader))
            
        else:
            raise ValueError(f"Unsupported {category=}.")

    def new_stm32(self, variant_name: str, default_bootloader = "stm32-dfu", valid_affixes: List[Union[str, None]] = [None]):
        """A helper function that simplifies generation of 'STM32' processors, by wrapping 'new_processor'.

        The below example arguments are given for an 'STM32F042x6' processor.

        Args:
            variant_name (str): The name of the variant of the 'STM32' processor (e.g. 'F042')
            default_bootloader (str, optional): Selects the default bootloader variant of the processor (e.g. 'stm32-dfu'). Defaults to "".
            valid_affixes (List[Union[str, None]], optional): A list of valid affixes for a processor (e.g. ['4', '6']). Defaults to [None].
        """
        self.new_processor(f"STM32{variant_name}", "chibios", default_bootloader=default_bootloader, valid_affixes=valid_affixes)


processor_factory = ProcessorFactory()

# Generic cortex processors
processor_factory.new_processor("cortex-m0", "chibios", valid_affixes=[None, "plus"])
processor_factory.new_processor("cortex-m3", "chibios")
processor_factory.new_processor("cortex-m4", "chibios")

# STM32 processors
processor_factory.new_stm32("F042", valid_affixes=["6"])
processor_factory.new_stm32("F072", valid_affixes=["B"])
processor_factory.new_stm32("F103", default_bootloader="stm32duino", valid_affixes=["8", "B", "D", "E", "G"])
processor_factory.new_stm32("F303", valid_affixes=["8", "C", "E"])
processor_factory.new_stm32("F401", valid_affixes=["C", "E"])
processor_factory.new_stm32("F405", valid_affixes=["G"])
processor_factory.new_stm32("F407", valid_affixes=["E", "G"])
processor_factory.new_stm32("F411", valid_affixes=["C", "E"])
processor_factory.new_stm32("F446", valid_affixes=["C", "E"])
processor_factory.new_stm32("G431", valid_affixes=["B"])
processor_factory.new_stm32("G474", valid_affixes=["E"])
processor_factory.new_stm32("L072", valid_affixes=["8", "B", "Z"])
processor_factory.new_stm32("L073", valid_affixes=["8", "B", "Z"])
processor_factory.new_stm32("L412", valid_affixes=["B", "C"])
processor_factory.new_stm32("L422", valid_affixes=["B", "C"])
processor_factory.new_stm32("L432", valid_affixes=["B", "C"])
processor_factory.new_stm32("L433", valid_affixes=["B", "C"])
processor_factory.new_stm32("L442", valid_affixes=["B", "C"])
processor_factory.new_stm32("L443", valid_affixes=["B", "C"])

# Atmel processors
processor_factory.new_processor("at90usb",  "lufa", default_bootloader="atmel-dfu", valid_affixes=["162", "646", "647", "1286", "1287"])
processor_factory.new_processor("atmega16", "lufa", default_bootloader="atmel-dfu", valid_affixes=["u2", "u4"])
processor_factory.new_processor("atmega32", "lufa", default_bootloader="atmel-dfu", valid_affixes=["u2", "u4"])

processor_factory.new_processor("atmega32a", "vusb", default_bootloader="bootloadhid")
processor_factory.new_processor("atmega328", "vusb", default_bootloader="usbasploader", valid_affixes=[None, "p"])
processor_factory.new_processor("attiny85",  "vusb", default_bootloader="usbasploader")

# Others
processor_factory.new_processor("GD32VF103", "chibios", default_bootloader="gd32v-dfu")

processor_factory.new_processor("WB32F3G71", "chibios", default_bootloader="wb32-dfu")

processor_factory.new_processor("MK20DX",    "chibios", default_bootloader="halfkay", valid_affixes=["128", "256"])
processor_factory.new_processor("MKL26Z64",  "chibios", default_bootloader="halfkay")
processor_factory.new_processor("MK66FX1M0", "chibios", default_bootloader="halfkay")
