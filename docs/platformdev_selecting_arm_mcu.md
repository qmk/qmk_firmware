# Choosing an Arm MCU {#choose-arm-mcu}

This page outlines the selection criteria to ensure compatibility with Arm/ChibiOS.

QMK uses the Hardware Abstraction Layer of ChibiOS in order to run on Arm devices. ChibiOS in general is best supported on STM32 devices, both in the perspective of base MCU support, as well as on-MCU peripheral support. As an extension to the core ChibiOS MCU support, QMK also utilises ChibiOS-Contrib (which includes the Kinetis MCU support layer, as an example), but it does not provide as great a level of peripheral support or general testing for supported devices.

Adding support for new MCU families must go through ChibiOS or ChibiOS-Contrib -- QMK does not have the bandwidth, resources, nor the inclination to maintain long-term MCU support for your board of choice.

To be clear: this also includes commercial boards -- unless agreed upon by all parties, QMK will not take over maintenance of a bespoke MCU support package. Even if MCU support is upstreamed into ChibiOS/ChibiOS-Contrib, QMK reserves the right to deprecate and/or remove keyboards utilising support packages that aren't kept up to date with upstream ChibiOS itself.

## Selecting an already-supported MCU {#selecting-already-supported-mcu}

### STM32 families

As outlined earlier, STM32 is the preferred option to ensure greatest compatibility with the subsystems already implemented in QMK. Not all subsystems are compatible yet, but for the most widely-used support is already present.

The simplest solution to determine if an STM32 MCU is compatible is to navigate to the list of supported STM32 ports in QMK's [ChibiOS fork](https://github.com/qmk/ChibiOS/tree/master/os/hal/ports/STM32). Inside this directory, each of the supported STM32 families will be listed, and inside each family a file called `stm32_registry.h` will be present. Scanning through these files will show `#define`s such as the following, which can be used to determine if ChibiOS supports a particular MCU:

```c
#if defined(STM32F303xC) || defined(__DOXYGEN__)
```

The example shows that STM32F303xC devices are supported by ChibiOS.

The next step is to ensure that USB is supported on those devices by ChibiOS -- you can confirm this by checking inside the same section guarded by the `#define` above, specifically for the following to be `TRUE`:

```c
#define STM32_HAS_USB                       TRUE
```

or one of the following being `TRUE`:

```c
#define STM32_HAS_OTG1                      TRUE
#define STM32_HAS_OTG2                      TRUE
```

For the most part, this is the bare minimum to be able to have a high confidence that QMK will be able to run on your MCU. After that, it's all up to configuration.

### Non-STM32 families

ChibiOS does have support for a handful of non-STM32 devices, and the list can be found in QMK's [ChibiOS fork](https://github.com/qmk/ChibiOS/tree/master/os/hal/ports) and [ChibiOS-Contrib fork](https://github.com/qmk/ChibiOS-Contrib/tree/master/os/hal/ports). Non-STM32 support is likely out of date, and only supports ancient MCUs -- whilst it might be possible to use these, it's not recommended.

Do note that there are sometimes licensing restrictions with respect to redistribution. As an example, binaries built for nRF5 are not able to be redistributed via QMK Configurator, due to the licensing of their board support package.

## Adding support for a new STM32 MCU (for an existing family) {#add-new-stm32-mcu}

Usually, one can "masquerade" as an existing MCU of the same family, especially if the only difference is RAM or Flash size. As an example, some MCUs within the same family are virtually identical, with the exception of adding a cryptographic peripheral -- STM32L072 vs. STM32L082 for instance. Given the unlikely use of the cryptographic peripheral, L082 chips can actually run as if they're an L072, and can be targeted accordingly.

Adding proper support for new MCUs within an existing STM32 family should ideally be upstreamed to ChibiOS. In general, this will require modifications of the `stm32_registry.h` file, providing correct responses for the same `#define`s provided for the other MCUs in that family.

## Adding support for a new STM32 Family {#add-new-stm32-family}

If this is a requirement, this needs to go through upstream ChibiOS before QMK would consider accepting boards targeting the new family. More information for porting should be sought by approaching ChibiOS directly, rather than through QMK.

## Adding support for a new MCU Family {#add-new-mcu-family}

As stated earlier, in order for a new MCU family to be supported by QMK, it needs to be upstreamed into ChibiOS-Contrib before QMK will consider accepting boards using it. The same principle applies for development -- you're best approaching the ChibiOS-Contrib maintainers to get a bit more of an idea on what's involved with upstreaming your contribution.
