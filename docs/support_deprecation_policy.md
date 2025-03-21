# Feature support policies

## System Constraints

In general, feature development is encouraged to support as many hardware configurations as possible. Depending on system constraints this may not always be achievable, and is usually bound by microcontroller flash and RAM capabilities.

The most frequently-hit constraint is the amount of code that can be flashed onto an ATmega32U4 -- users almost always need to pick and choose included functionality due to the size constraints.

::: warning
[Squeezing AVR](squeezing_avr) has some steps that users can take in order to minimise the overall firmware size, which in some cases enables the ability for users to include other desired features.
:::

## Deprecation & Removal Policy

QMK Firmware strives for innovation wherever possible. With ongoing feature development and other improvements made to the codebase, sometimes the retirement of outdated, under-utilised, or limited-value functionality is selected for deprecation and subsequent removal.

The intent behind feature deprecation is to maintain and/or improve quality. As a result, perpetually supporting under-utilised features would negatively impact the QMK team's ability to improve other areas of QMK Firmware.

There may be several motivations behind the deprecation or removal of functionality (keeping in mind that this list is not exhaustive):

* Better alternatives have already been implemented
* Lack of adherence to standards
* Poor support from code owners or upstream maintainers
* Poor design
* Hardware constraints
* Minimal use within the QMK Firmware repository
* Copyright disputes
* Bit-rot

When a feature is selected for deprecation, future changes to that area will cease to be developed by the QMK team, and Pull Requests submitted against those areas will be declined.

::: tip
As QMK does not gather metrics from its users, the only way the QMK team can gauge the level of usage is to refer to the main QMK Firmware repository -- searching through forks is not practical due to the sheer number of them.
:::

### How much advance notice will be given?

Disregarding emergencies or other high-risk concerns, deprecation of large features or entire subsystems within QMK will be communicated on the `develop` branch at least one breaking changes cycle (3 months) before removal. Advance notice may be extended for higher impact features, and is at the discretion of the QMK team.

Smaller features may be removed within a breaking changes cycle, and will generally be based on the level of use within the repository. Features with minimal use may be selected for removal at any time on the `develop` branch.

Third-party software libraries leveraged by QMK are generally forked to mitigate disappearance upstream. If the upstream repository is removed, it will generally be replaced when practical, or dependent features will be removed as per the normal deprecation policy.

### How will deprecation be communicated?

Every breaking changes merge from `develop` into `master` is accompanied by a changelog document -- intended and completed deprecations will be communicated here.

In addition, wherever possible warnings will be issued during firmware compilation when deprecated features are still being used.
