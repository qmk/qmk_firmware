# Proprietary Vendor Libraries

QMK Firmware cannot include support for any proprietary vendor libraries that impose additional restrictions beyond those in the GPL. This includes binary-only distributions, hardware-locked libraries, and code with redistribution limitations. This document explains why such libraries are incompatible with the GPL-based QMK Firmware and addresses commonly proposed workarounds.

## Architecture Constraints

Firmware presents unique licensing challenges:

- **Monolithic binary**: All code compiles into a single executable image
- **No OS isolation**: No operating system provides process or memory separation
- **Shared resources**: All code shares the same memory space, peripherals, and execution context
- **Static linking**: Everything is statically linked at compile time

This monolithic nature means any proprietary code becomes inseparable from GPL code, creating immediate license violations.

## Common Vendor Library Restrictions

Proprietary vendor libraries typically impose restrictions incompatible with GPL freedoms:

**Hardware Lock-in:**
- Library only licensed for specific vendor's chips
- Cannot port firmware to alternative hardware
- Examples: Nordic's and ST's chip-only clauses in their respective licenses

**No Source Distribution:**
- Binary-only libraries without corresponding source
- Precompiled static libraries (.a/.lib files)
- No ability to modify or fix bugs
- Examples: WCH CH582 precompiled libraries, Nordic SoftDevice

**Redistribution Limitations:**
- Restrictions on who can distribute
- Limitations on commercial use
- Required permissions or fees

**Additional Legal Terms:**
- Patent assertions beyond GPL's scope
- Indemnification requirements
- Jurisdiction restrictions
- Explicit anti-GPL clauses

## Bluetooth Stack Licensing Examples

Both Nordic and ST provide Bluetooth stacks under restrictive licenses:

**Nordic SoftDevice (under Nordic 5-clause license):**
- Binary-only Bluetooth/radio stack
- License restricts to Nordic hardware
- No source code available
- Communicates via SVC interface (still not GPL-compatible)

**ST's Bluetooth Stack (under SLA0044 license):**
- Explicitly forbids being subject to "Open Source Terms", specifically mentioning incompatibility with the GPL
- Restricted to ST microcontrollers only
- Similar functional role to Nordic's SoftDevice

Both represent the same fundamental problem: critical wireless functionality locked behind proprietary licenses.

## Why the System Library Exception Doesn't Apply

The GPL's System Library exception **cannot** rescue proprietary vendor libraries.

### System Library Requirements

The exception only covers libraries that:
1. Are part of the "normal form of packaging a Major Component"
2. The Major Component is an OS kernel, compiler, or similar system software
3. Are not distributed with the application
4. Are not part of the application itself

### Why Vendor Libraries Fail These Requirements

1. **No operating system**: Bare-metal firmware has no OS to provide system libraries
2. **Not Major Components**: Hardware drivers and HALs aren't kernels or compilers
3. **Distributed together**: Vendor code becomes part of the firmware binary
4. **Application-level code**: Peripheral drivers are application functionality

The exception covers things like Windows system DLLs or Linux glibc, not microcontroller vendor libraries or Bluetooth stacks.

## Attempted Workarounds

### Architectural Separation Attempts

**Supervisor Call (SVC) Interfaces:**

Nordic's SoftDevice uses supervisor call based APIs instead of direct linking:
- Fixed memory regions for proprietary code
- Communication through CPU exception mechanisms
- Claims of "no linking" between components

**Why this fails:** The GPL considers functional integration, not just linking methods. In Bluetooth-capable boards, these would require the proprietary component to function, thus they form a single work regardless of the communication mechanism. This applies equally to Nordic's SoftDevice and any similar architecture ST provides.

**Binary-Only Distributions:**

Multiple vendors provide precompiled libraries:
- WCH: Precompiled BLE stack
- Nordic: Binary-only SoftDevice library
- ST: Same solution as Nordic

**Why this fails:** This is classic static linking of proprietary code into GPL code. The inability to modify these libraries violates GPL's fundamental requirements.

### Loader-Based Separation

- Write a GPL bootloader/loader
- Load proprietary firmware (such as Nordic/ST Bluetooth) from external storage
- Claim they're separate works

**Problems:**
- If designed as a system, courts view as single work
- Distribution patterns matter (shipped together?)
- Functional interdependence suggests unity
- Appears designed to circumvent GPL

## Real-World Examples

### Bluetooth/Wireless Stacks
- **Nordic SoftDevice**: Binary-only, SVC-interface, hardware-locked
- **ST Bluetooth**: Binary-only, license explicitly GPL-incompatible
- **WCH CH582**: Precompiled Bluetooth libraries

### HAL and Driver Libraries
- **ST HAL/LL drivers**: Source available but SLA0044 restricted
- **Nordic SDK**: Source visible but 5-Clause restricted
- **Various vendor HALs**: Platform-locked licenses

### Mixed Proprietary/Open
- Open peripheral drivers with closed protocol stacks
- Basic HAL with proprietary performance libraries
- Partially documented systems requiring binary supplements

## Legal and Practical Consequences

Including any proprietary vendor library means:

1. **License Violation**: Immediate GPL non-compliance
2. **Distribution Ban**: Users cannot legally share modified firmware
3. **Commercial Risk**: Products using the firmware face legal liability
4. **Contributor Tainting**: All GPL contributions become legally problematic
5. **Update Restrictions**: Cannot fix bugs in proprietary components

## Evaluation Criteria for Libraries

Before including any library, QMK needs to verify:
- Complete source code available
- GPL-compatible license (GPL, LGPL, MIT, BSD, Apache)
- No hardware restrictions
- No redistribution limitations
- No additional legal terms
- No anti-GPL clauses

## Policy Implementation

QMK Firmware maintains a strict policy:

1. **No proprietary libraries**: Regardless of technical workarounds
2. **No binary blobs**: All code must have source available
3. **No platform restrictions**: Must allow porting to any hardware
4. **No additional terms**: Only GPL restrictions permitted

## Summary

There is no legally safe way to include proprietary vendor libraries in GPL firmware. This applies whether they're:
- Bluetooth stacks (Nordic SoftDevice, ST Bluetooth)
- Precompiled static libraries
- Binary blobs with SVC interfaces
- Source code with restrictive licenses
- Mixed open/closed systems

**Technical architectures cannot overcome license obligations.**

QMK chooses GPL compliance, ensuring users receive all freedoms the GPL promises.
