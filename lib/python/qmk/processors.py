"""Generates an interactive list of supported processors."""
from dataclasses import dataclass
from typing import List, Union, ClassVar


@dataclass
class Processor:
    """Holds information about supported processors."""
    family_name: str            # e.g. "atmega32u4", or "STM32F042"
    category: str               # Can be "chibios", "lufa", or "vusb"
    valid_affixes: List[str]    # e.g. ['4', '6'], can also be empty [].
    bootloader: str             # e.g. "atmel-dfu", or "stm32-dfu"

    cortex_prefix: ClassVar[str] = "cortex"
    
    stm32_prefix: ClassVar[str] = "STM32"
    stm32_affix_separator: ClassVar[str] = "x"

    valid_categories: ClassVar[List[str]] = ["chibios", "lufa", "vusb"]
    valid_bootloaders: ClassVar[List[str]] = ["", "halfkay", "stm32-dfu", "tinyuf2", "stm32duino", "gd32v-dfu", "wb32-dfu", "atmel-dfu", "bootloadhid", "usbasploader"]

    @property
    def full_names(self) -> List[str]:
        """Gives all valid names for this processor family, e.g. ["STM32F303x8", "STM32F303xC", "STM32F303xE"].

        Returns:
            List[str]: The list of valid names.
        """
        if not self.valid_affixes:
            # If no affixes exist, the family name is the only full name of this processor family, e.g. "atmega32u4".
            return [self.family_name]

        elif self.is_stm32:
            # Introduce the STM32 affix separator into the name.
            return [f"{self.family_name}{Processor.stm32_affix_separator}{affix}" for affix in self.valid_affixes]

        else:
            # Do not use any affix separator.
            return [f"{self.family_name}{affix}" for affix in self.valid_affixes]

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
        return processor_name == self.family_name

    def matches_affix(self, processor_name: str) -> bool:
        """Matches the processor name against affixes of arbitrary length in the list of valid affixes.

        Args:
            processor_name (str): The name to match against affixes.

        Returns:
            bool: True, if the affix matches on of the valid affixes, False otherwise
        """
        return any([processor_name[-len(affix):] == affix for affix in self.valid_affixes])

    def matches(self, processor_name: str) -> bool:
        """Checks, whether the provided processor name matches this Processor definition.

        Args:
            processor_name (str): The processor name to check.

        Returns:
            bool: True, if the name matches, False otherwise.
        """
        if not self.matches_family(processor_name):
            return False

        if not self.valid_affixes:
            return self.matches_precisely(processor_name)

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
        if not self.processor_exists(processor):
            self.processors.append(processor)

    def new_processor(self, family_name: str, category: str, bootloader = "", valid_affixes: List[str] = []):
        if category in Processor.valid_categories and bootloader in Processor.valid_bootloaders:
            self.add_processor(Processor(family_name, category, valid_affixes, bootloader))
            
        else:
            raise ValueError(f"Unsupported {category=}.")


processor_factory = ProcessorFactory()

processor_factory.new_processor("cortex-m0",     "chibios")
processor_factory.new_processor("cortex-m0plus", "chibios")
processor_factory.new_processor("cortex-m3",     "chibios")
processor_factory.new_processor("cortex-m4",     "chibios")

processor_factory.new_processor("MKL26Z64",  "chibios", bootloader="halfkay")
processor_factory.new_processor("MK20DX128", "chibios", bootloader="halfkay")
processor_factory.new_processor("MK20DX256", "chibios", bootloader="halfkay")
processor_factory.new_processor("MK66FX1M0", "chibios", bootloader="halfkay")

processor_factory.new_processor("STM32F042", "chibios", bootloader="stm32-dfu",  valid_affixes=["6"])
processor_factory.new_processor("STM32F072", "chibios", bootloader="stm32-dfu",  valid_affixes=["B"])
processor_factory.new_processor("STM32F103", "chibios", bootloader="stm32duino", valid_affixes=["8", "B", "D", "E", "G"])
processor_factory.new_processor("STM32F303", "chibios", bootloader="stm32-dfu",  valid_affixes=["8", "C", "E"])
processor_factory.new_processor("STM32F401", "chibios", bootloader="stm32-dfu",  valid_affixes=["C", "E"])
processor_factory.new_processor("STM32F405", "chibios", bootloader="stm32-dfu",  valid_affixes=["G"])
processor_factory.new_processor("STM32F407", "chibios", bootloader="stm32-dfu",  valid_affixes=["E", "G"])
processor_factory.new_processor("STM32F411", "chibios", bootloader="stm32-dfu",  valid_affixes=["C", "E"])
processor_factory.new_processor("STM32F446", "chibios", bootloader="stm32-dfu",  valid_affixes=["C", "E"])
processor_factory.new_processor("STM32G431", "chibios", bootloader="stm32-dfu",  valid_affixes=["B"])
processor_factory.new_processor("STM32G474", "chibios", bootloader="stm32-dfu",  valid_affixes=["E"])
processor_factory.new_processor("STM32L072", "chibios", bootloader="stm32-dfu",  valid_affixes=["8", "B", "Z"])
processor_factory.new_processor("STM32L073", "chibios", bootloader="stm32-dfu",  valid_affixes=["8", "B", "Z"])
processor_factory.new_processor("STM32L412", "chibios", bootloader="stm32-dfu",  valid_affixes=["B", "C"])
processor_factory.new_processor("STM32L422", "chibios", bootloader="stm32-dfu",  valid_affixes=["B", "C"])
processor_factory.new_processor("STM32L432", "chibios", bootloader="stm32-dfu",  valid_affixes=["B", "C"])
processor_factory.new_processor("STM32L433", "chibios", bootloader="stm32-dfu",  valid_affixes=["B", "C"])
processor_factory.new_processor("STM32L442", "chibios", bootloader="stm32-dfu",  valid_affixes=["B", "C"])
processor_factory.new_processor("STM32L443", "chibios", bootloader="stm32-dfu",  valid_affixes=["B", "C"])

processor_factory.new_processor("GD32VF103", "chibios", bootloader="gd32v-dfu")
processor_factory.new_processor("WB32F3G71", "chibios", bootloader="wb32-dfu")

processor_factory.new_processor("at90usb162",  "lufa", bootloader="atmel-dfu")
processor_factory.new_processor("atmega16u2",  "lufa", bootloader="atmel-dfu")
processor_factory.new_processor("atmega32u2",  "lufa", bootloader="atmel-dfu")
processor_factory.new_processor("atmega32u4",  "lufa", bootloader="atmel-dfu")
processor_factory.new_processor("at90usb646",  "lufa", bootloader="atmel-dfu")
processor_factory.new_processor("at90usb647",  "lufa", bootloader="atmel-dfu")
processor_factory.new_processor("at90usb1286", "lufa", bootloader="atmel-dfu")
processor_factory.new_processor("at90usb1287", "lufa", bootloader="atmel-dfu")

processor_factory.new_processor("atmega32a",  "vusb", bootloader="bootloadhid")
processor_factory.new_processor("atmega328p", "vusb", bootloader="usbasploader")
processor_factory.new_processor("atmega328",  "vusb", bootloader="usbasploader")
processor_factory.new_processor("attiny85",   "vusb", bootloader="usbasploader")
