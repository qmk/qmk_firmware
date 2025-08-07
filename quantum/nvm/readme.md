# Non-volatile Memory - Data Repositories

This area is intentionally structured in the following way:

```
╰- quantum
   ╰- nvm
      ├- readme.md
      ├- rules.mk
      |
      ├- nvm_eeconfig.h
      ├- nvm_<<system>>.h
      |
      ├- eeprom
      |  ├- nvm_eeconfig.c
      |  ├- nvm_<<system>>.c
      |  ╰- ...
      |
      ├- <<another provider>>
      |  ├- nvm_eeconfig.c
      |  ├- nvm_<<system>>.c
      |  ╰- ...
      ╰- ...
```

At the base `nvm` level, for every QMK core system which requires persistence there must be a corresponding `nvm_<<system>>.h` header file. This provides the data repository API to the "owner" system, and allows the underlying data persistence mechanism to be abstracted away from upper code. Any conversion to/from a `.raw` field should occur inside the `nvm_<<system>>.c` layer, with the API using values, such as structs or unions exposed to the rest of QMK.

Each `nvm` "provider" is a corresponding child directory consisting of its name, such as `eeprom`, and corresponding `nvm_<<system>>.c` implementation files which provide the concrete implementation of the upper `nvm_<<system>>.h`.

New systems requiring persistence can add the corresponding `nvm_<<system>>.h` file, and in most circumstances must also implement equivalent `nvm_<<system>>.c` files for every `nvm` provider. If persistence is not possible for that system, a `nvm_<<system>>.c` file with simple stubs which ignore writes and provide sane defaults must be used instead.