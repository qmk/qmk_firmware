import { _ as _export_sfc, c as createElementBlock, l as createBaseVNode, a as createTextVNode, I as createVNode, w as withCtx, a8 as createStaticVNode, D as resolveComponent, o as openBlock } from "./chunks/framework.Cauyuiy8.js";
const __pageData = JSON.parse('{"title":"info.json Reference","description":"","frontmatter":{},"headers":[],"relativePath":"reference_info_json.md","filePath":"reference_info_json.md","lastUpdated":null}');
const _sfc_main = { name: "reference_info_json.md" };
const _hoisted_1 = /* @__PURE__ */ createStaticVNode("", 4);
const _hoisted_5 = /* @__PURE__ */ createBaseVNode("code", null, "keyboard_name", -1);
const _hoisted_6 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("A free-form text string describing the keyboard. This will be used as the USB product string. Can include Unicode characters, escaped to ASCII eg. "),
    /* @__PURE__ */ createBaseVNode("code", null, "\\u03A8"),
    /* @__PURE__ */ createTextVNode(" (Ψ).")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"Clueboard 66%"')
  ])
], -1);
const _hoisted_7 = /* @__PURE__ */ createBaseVNode("code", null, "maintainer", -1);
const _hoisted_8 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("GitHub username of the maintainer, or "),
    /* @__PURE__ */ createBaseVNode("code", null, "qmk"),
    /* @__PURE__ */ createTextVNode(" for community maintained boards.")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"skullydazed"')
  ])
], -1);
const _hoisted_9 = /* @__PURE__ */ createBaseVNode("code", null, "manufacturer", -1);
const _hoisted_10 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("A free-form text string describing the keyboard's manufacturer. This will be used as the USB manufacturer string. Can include Unicode characters, escaped to ASCII eg. "),
    /* @__PURE__ */ createBaseVNode("code", null, "\\u03A8"),
    /* @__PURE__ */ createTextVNode(" (Ψ).")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"Clueboard"')
  ])
], -1);
const _hoisted_11 = /* @__PURE__ */ createBaseVNode("code", null, "url", -1);
const _hoisted_12 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("A URL to the keyboard's product page, "),
    /* @__PURE__ */ createBaseVNode("a", {
      href: "https://browse.qmk.fm/",
      target: "_blank",
      rel: "noreferrer"
    }, "QMK Keyboards"),
    /* @__PURE__ */ createTextVNode(" page, or other page describing information about the keyboard.")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"https://clueboard.co"')
  ])
], -1);
const _hoisted_13 = /* @__PURE__ */ createBaseVNode("code", null, "bootloader_instructions", -1);
const _hoisted_14 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Instructions for putting the keyboard into a mode that allows for firmware flashing."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"Press the button marked RESET on the back of the PCB"')
  ])
], -1);
const _hoisted_15 = /* @__PURE__ */ createBaseVNode("code", null, "tags", -1);
const _hoisted_16 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "A list of tags describing the keyboard."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, '["ortho", "split", "rgb"]')
  ])
], -1);
const _hoisted_17 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "hardware-configuration",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Hardware Configuration "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#hardware-configuration",
    "aria-label": 'Permalink to "Hardware Configuration {#hardware-configuration}"'
  }, "​")
], -1);
const _hoisted_18 = /* @__PURE__ */ createBaseVNode("code", null, "board", -1);
const _hoisted_19 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Override the default ChibiOS board name (ARM-based keyboards only)."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"BLACKPILL_STM32_F411"')
  ])
], -1);
const _hoisted_20 = /* @__PURE__ */ createBaseVNode("code", null, "bootloader", -1);
const _hoisted_21 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The bootloader in use on the keyboard. Required if "),
    /* @__PURE__ */ createBaseVNode("code", null, "development_board"),
    /* @__PURE__ */ createTextVNode(" is not specified.")
  ])
], -1);
const _hoisted_22 = /* @__PURE__ */ createBaseVNode("code", null, "development_board", -1);
const _hoisted_23 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The microcontroller development board, if applicable."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"promicro"')
  ])
], -1);
const _hoisted_24 = /* @__PURE__ */ createBaseVNode("code", null, "pin_compatible", -1);
const _hoisted_25 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The form factor of the development board, if applicable. Must be one of "),
    /* @__PURE__ */ createBaseVNode("code", null, "elite_c"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "promicro"),
    /* @__PURE__ */ createTextVNode(".")
  ])
], -1);
const _hoisted_26 = /* @__PURE__ */ createBaseVNode("code", null, "processor", -1);
const _hoisted_27 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The microcontroller in use on the keyboard. Required if "),
    /* @__PURE__ */ createBaseVNode("code", null, "development_board"),
    /* @__PURE__ */ createTextVNode(" is not specified.")
  ])
], -1);
const _hoisted_28 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "firmware-configuration",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Firmware Configuration "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#firmware-configuration",
    "aria-label": 'Permalink to "Firmware Configuration {#firmware-configuration}"'
  }, "​")
], -1);
const _hoisted_29 = /* @__PURE__ */ createBaseVNode("code", null, "build", -1);
const _hoisted_30 = /* @__PURE__ */ createBaseVNode("code", null, "debounce_type", -1);
const _hoisted_31 = /* @__PURE__ */ createStaticVNode("", 1);
const _hoisted_32 = /* @__PURE__ */ createBaseVNode("code", null, "firmware_format", -1);
const _hoisted_33 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The format of the final output binary. Must be one of "),
    /* @__PURE__ */ createBaseVNode("code", null, "bin"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "hex"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "uf2"),
    /* @__PURE__ */ createTextVNode(".")
  ])
], -1);
const _hoisted_34 = /* @__PURE__ */ createBaseVNode("code", null, "lto", -1);
const _hoisted_35 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Enable Link-Time Optimization."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_36 = /* @__PURE__ */ createBaseVNode("code", null, "features", -1);
const _hoisted_37 = /* @__PURE__ */ createStaticVNode("", 2);
const _hoisted_39 = /* @__PURE__ */ createBaseVNode("code", null, "qmk", -1);
const _hoisted_40 = /* @__PURE__ */ createBaseVNode("code", null, "locking", -1);
const _hoisted_41 = /* @__PURE__ */ createBaseVNode("code", null, "enabled", -1);
const _hoisted_42 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Enable locking switch support."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_43 = /* @__PURE__ */ createBaseVNode("code", null, "resync", -1);
const _hoisted_44 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Keep switch state consistent with keyboard LED state."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_45 = /* @__PURE__ */ createBaseVNode("code", null, "tap_capslock_delay", -1);
const _hoisted_46 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The delay between keydown and keyup for Caps Lock tap events in milliseconds."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "80"),
    /* @__PURE__ */ createTextVNode(" (80 ms)")
  ])
], -1);
const _hoisted_47 = /* @__PURE__ */ createBaseVNode("code", null, "tap_keycode_delay", -1);
const _hoisted_48 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The delay between keydown and keyup for tap events in milliseconds."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "0"),
    /* @__PURE__ */ createTextVNode(" (no delay)")
  ])
], -1);
const _hoisted_49 = /* @__PURE__ */ createBaseVNode("code", null, "tapping", -1);
const _hoisted_50 = /* @__PURE__ */ createBaseVNode("code", null, "chordal_hold", -1);
const _hoisted_51 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_52 = /* @__PURE__ */ createBaseVNode("code", null, "hold_on_other_key_press", -1);
const _hoisted_53 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_54 = /* @__PURE__ */ createBaseVNode("code", null, "hold_on_other_key_press_per_key", -1);
const _hoisted_55 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_56 = /* @__PURE__ */ createBaseVNode("code", null, "permissive_hold", -1);
const _hoisted_57 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_58 = /* @__PURE__ */ createBaseVNode("code", null, "permissive_hold_per_key", -1);
const _hoisted_59 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_60 = /* @__PURE__ */ createBaseVNode("code", null, "retro", -1);
const _hoisted_61 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_62 = /* @__PURE__ */ createBaseVNode("code", null, "retro_per_key", -1);
const _hoisted_63 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_64 = /* @__PURE__ */ createBaseVNode("code", null, "term", -1);
const _hoisted_65 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "200"),
    /* @__PURE__ */ createTextVNode(" (200 ms)")
  ])
], -1);
const _hoisted_66 = /* @__PURE__ */ createBaseVNode("code", null, "term_per_key", -1);
const _hoisted_67 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_68 = /* @__PURE__ */ createBaseVNode("code", null, "toggle", -1);
const _hoisted_69 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "5")
  ])
], -1);
const _hoisted_70 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "apa102",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("APA102 "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#apa102",
    "aria-label": 'Permalink to "APA102 {#apa102}"'
  }, "​")
], -1);
const _hoisted_71 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./drivers/apa102" }, "APA102"),
  /* @__PURE__ */ createTextVNode(" driver.")
], -1);
const _hoisted_72 = /* @__PURE__ */ createBaseVNode("code", null, "apa102", -1);
const _hoisted_73 = /* @__PURE__ */ createBaseVNode("code", null, "clock_pin", -1);
const _hoisted_74 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The GPIO pin connected to "),
    /* @__PURE__ */ createBaseVNode("code", null, "CI"),
    /* @__PURE__ */ createTextVNode(" on the first LED in the chain.")
  ])
], -1);
const _hoisted_75 = /* @__PURE__ */ createBaseVNode("code", null, "data_pin", -1);
const _hoisted_76 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The GPIO pin connected to "),
    /* @__PURE__ */ createBaseVNode("code", null, "DI"),
    /* @__PURE__ */ createTextVNode(" on the first LED in the chain.")
  ])
], -1);
const _hoisted_77 = /* @__PURE__ */ createBaseVNode("code", null, "default_brightness", -1);
const _hoisted_78 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The initial global brightness level (independent of the RGB data), from 0 to 31."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "31")
  ])
], -1);
const _hoisted_79 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "audio",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Audio "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#audio",
    "aria-label": 'Permalink to "Audio {#audio}"'
  }, "​")
], -1);
const _hoisted_80 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/audio" }, "Audio"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_81 = /* @__PURE__ */ createBaseVNode("code", null, "audio", -1);
const _hoisted_82 = /* @__PURE__ */ createBaseVNode("code", null, "default", -1);
const _hoisted_83 = /* @__PURE__ */ createBaseVNode("code", null, "on", -1);
const _hoisted_84 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default audio enabled state."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "true")
  ])
], -1);
const _hoisted_85 = /* @__PURE__ */ createBaseVNode("code", null, "clicky", -1);
const _hoisted_86 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default audio clicky enabled state."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "true")
  ])
], -1);
const _hoisted_87 = /* @__PURE__ */ createBaseVNode("code", null, "driver", -1);
const _hoisted_88 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The driver to use. Must be one of "),
    /* @__PURE__ */ createBaseVNode("code", null, "dac_additive"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "dac_basic"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "pwm_software"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "pwm_hardware"),
    /* @__PURE__ */ createTextVNode(".")
  ])
], -1);
const _hoisted_89 = /* @__PURE__ */ createBaseVNode("code", null, "macro_beep", -1);
const _hoisted_90 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Play a short beep for "),
    /* @__PURE__ */ createBaseVNode("code", null, "\\a"),
    /* @__PURE__ */ createTextVNode(" (ASCII "),
    /* @__PURE__ */ createBaseVNode("code", null, "BEL"),
    /* @__PURE__ */ createTextVNode(") characters in Send String macros.")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_91 = /* @__PURE__ */ createBaseVNode("code", null, "pins", -1);
const _hoisted_92 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The GPIO pin(s) connected to the speaker(s).")
], -1);
const _hoisted_93 = /* @__PURE__ */ createBaseVNode("code", null, "power_control", -1);
const _hoisted_94 = /* @__PURE__ */ createBaseVNode("code", null, "on_state", -1);
const _hoisted_95 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The logical GPIO state required to turn the speaker on."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "1"),
    /* @__PURE__ */ createTextVNode(" (on = high)")
  ])
], -1);
const _hoisted_96 = /* @__PURE__ */ createBaseVNode("code", null, "pin", -1);
const _hoisted_97 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The GPIO pin connected to speaker power circuit.")
], -1);
const _hoisted_98 = /* @__PURE__ */ createBaseVNode("code", null, "voices", -1);
const _hoisted_99 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Use multiple audio voices."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_100 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "backlight",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Backlight "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#backlight",
    "aria-label": 'Permalink to "Backlight {#backlight}"'
  }, "​")
], -1);
const _hoisted_101 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/backlight" }, "Backlight"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_102 = /* @__PURE__ */ createBaseVNode("code", null, "backlight", -1);
const _hoisted_103 = /* @__PURE__ */ createBaseVNode("code", null, "as_caps_lock", -1);
const _hoisted_104 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Use the backlight as a Caps Lock indicator."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_105 = /* @__PURE__ */ createBaseVNode("code", null, "breathing", -1);
const _hoisted_106 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Whether backlight breathing is enabled."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_107 = /* @__PURE__ */ createBaseVNode("code", null, "breathing_period", -1);
const _hoisted_108 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The length of one backlight breathing cycle in seconds."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "6"),
    /* @__PURE__ */ createTextVNode(" (6 seconds)")
  ])
], -1);
const _hoisted_109 = /* @__PURE__ */ createBaseVNode("code", null, "default", -1);
const _hoisted_110 = /* @__PURE__ */ createBaseVNode("code", null, "on", -1);
const _hoisted_111 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default backlight enabled state."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "true")
  ])
], -1);
const _hoisted_112 = /* @__PURE__ */ createBaseVNode("code", null, "breathing", -1);
const _hoisted_113 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default backlight breathing state."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_114 = /* @__PURE__ */ createBaseVNode("code", null, "brightness", -1);
const _hoisted_115 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default brightness level."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "max_brightness")
  ])
], -1);
const _hoisted_116 = /* @__PURE__ */ createBaseVNode("code", null, "driver", -1);
const _hoisted_117 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The driver to use. Must be one of "),
    /* @__PURE__ */ createBaseVNode("code", null, "custom"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "pwm"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "software"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "timer"),
    /* @__PURE__ */ createTextVNode(".")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"pwm"')
  ])
], -1);
const _hoisted_118 = /* @__PURE__ */ createBaseVNode("code", null, "levels", -1);
const _hoisted_119 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The number of brightness levels (excluding off), from 1 to 31."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "3")
  ])
], -1);
const _hoisted_120 = /* @__PURE__ */ createBaseVNode("code", null, "max_brightness", -1);
const _hoisted_121 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The maximum PWM value which brightness is scaled to, from 0 to 255."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "255")
  ])
], -1);
const _hoisted_122 = /* @__PURE__ */ createBaseVNode("code", null, "on_state", -1);
const _hoisted_123 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The logical GPIO state required to turn the LEDs on."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "1"),
    /* @__PURE__ */ createTextVNode(" (on = high)")
  ])
], -1);
const _hoisted_124 = /* @__PURE__ */ createBaseVNode("code", null, "pin", -1);
const _hoisted_125 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The GPIO pin connected to the backlight circuit.")
], -1);
const _hoisted_126 = /* @__PURE__ */ createBaseVNode("code", null, "pins", -1);
const _hoisted_127 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("A list of GPIO pins connected to the backlight LEDs ("),
    /* @__PURE__ */ createBaseVNode("code", null, "software"),
    /* @__PURE__ */ createTextVNode(" and "),
    /* @__PURE__ */ createBaseVNode("code", null, "timer"),
    /* @__PURE__ */ createTextVNode(" drivers only).")
  ])
], -1);
const _hoisted_128 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "battery",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Battery "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#battery",
    "aria-label": 'Permalink to "Battery"'
  }, "​")
], -1);
const _hoisted_129 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/battery" }, "Battery"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_130 = /* @__PURE__ */ createBaseVNode("code", null, "battery", -1);
const _hoisted_131 = /* @__PURE__ */ createBaseVNode("code", null, "adc", -1);
const _hoisted_132 = /* @__PURE__ */ createBaseVNode("code", null, "pin", -1);
const _hoisted_133 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The GPIO pin connected to the voltage divider.")
], -1);
const _hoisted_134 = /* @__PURE__ */ createBaseVNode("code", null, "reference_voltage", -1);
const _hoisted_135 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The ADC reverence voltage, in millivolts."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "3300")
  ])
], -1);
const _hoisted_136 = /* @__PURE__ */ createBaseVNode("code", null, "divider_r1", -1);
const _hoisted_137 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The voltage divider resistance, in kOhm. Set to 0 to disable."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "100")
  ])
], -1);
const _hoisted_138 = /* @__PURE__ */ createBaseVNode("code", null, "divider_r2", -1);
const _hoisted_139 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The voltage divider resistance, in kOhm. Set to 0 to disable."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "100")
  ])
], -1);
const _hoisted_140 = /* @__PURE__ */ createBaseVNode("code", null, "resolution", -1);
const _hoisted_141 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The ADC resolution configured for the ADC Driver."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "10")
  ])
], -1);
const _hoisted_142 = /* @__PURE__ */ createBaseVNode("code", null, "driver", -1);
const _hoisted_143 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The driver to use. Must be one of "),
    /* @__PURE__ */ createBaseVNode("code", null, "adc"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "custom"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "vendor"),
    /* @__PURE__ */ createTextVNode(".")
  ])
], -1);
const _hoisted_144 = /* @__PURE__ */ createBaseVNode("code", null, "sample_interval", -1);
const _hoisted_145 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The delay between sampling the battery in milliseconds."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "30000"),
    /* @__PURE__ */ createTextVNode(" (30 s)")
  ])
], -1);
const _hoisted_146 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "bluetooth",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Wireless/Bluetooth "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#bluetooth",
    "aria-label": 'Permalink to "Wireless/Bluetooth {#bluetooth}"'
  }, "​")
], -1);
const _hoisted_147 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/wireless" }, "Wireless"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_148 = /* @__PURE__ */ createBaseVNode("code", null, "bluetooth", -1);
const _hoisted_149 = /* @__PURE__ */ createBaseVNode("code", null, "driver", -1);
const _hoisted_150 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The driver to use. Must be one of "),
    /* @__PURE__ */ createBaseVNode("code", null, "custom"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "bluefruit_le"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "rn42"),
    /* @__PURE__ */ createTextVNode(".")
  ])
], -1);
const _hoisted_151 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "bootmagic",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Bootmagic "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#bootmagic",
    "aria-label": 'Permalink to "Bootmagic {#bootmagic}"'
  }, "​")
], -1);
const _hoisted_152 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/bootmagic" }, "Bootmagic"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_153 = /* @__PURE__ */ createBaseVNode("code", null, "bootmagic", -1);
const _hoisted_154 = /* @__PURE__ */ createBaseVNode("code", null, "enabled", -1);
const _hoisted_155 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Enables the Bootmagic feature."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_156 = /* @__PURE__ */ createBaseVNode("code", null, "matrix", -1);
const _hoisted_157 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The matrix position of the key to check during startup. This should generally be set to the (physically) top left key."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "[0, 0]")
  ])
], -1);
const _hoisted_158 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "caps-word",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Caps Word "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#caps-word",
    "aria-label": 'Permalink to "Caps Word {#caps-word}"'
  }, "​")
], -1);
const _hoisted_159 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/caps_word" }, "Caps Word"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_160 = /* @__PURE__ */ createBaseVNode("code", null, "caps_word", -1);
const _hoisted_161 = /* @__PURE__ */ createBaseVNode("code", null, "both_shifts_turns_on", -1);
const _hoisted_162 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Activate Caps Word by pressing both Shift keys."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_163 = /* @__PURE__ */ createBaseVNode("code", null, "double_tap_shift_turns_on", -1);
const _hoisted_164 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Activate Caps Word by pressing Left Shift twice."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_165 = /* @__PURE__ */ createBaseVNode("code", null, "enabled", -1);
const _hoisted_166 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Enables the Caps Word feature."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_167 = /* @__PURE__ */ createBaseVNode("code", null, "idle_timeout", -1);
const _hoisted_168 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The amount of time before Caps Word automatically deactivates in milliseconds."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "5000"),
    /* @__PURE__ */ createTextVNode(" (5 seconds)")
  ])
], -1);
const _hoisted_169 = /* @__PURE__ */ createBaseVNode("code", null, "invert_on_shift", -1);
const _hoisted_170 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Invert shift state instead of deactivating Caps Word when Shift is pressed."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_171 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "combo",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Combo "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#combo",
    "aria-label": 'Permalink to "Combo {#combo}"'
  }, "​")
], -1);
const _hoisted_172 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/combo" }, "Combo"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_173 = /* @__PURE__ */ createBaseVNode("code", null, "combo", -1);
const _hoisted_174 = /* @__PURE__ */ createBaseVNode("code", null, "term", -1);
const _hoisted_175 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The amount of time to recognize a combo in milliseconds."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "50"),
    /* @__PURE__ */ createTextVNode(" (50 ms)")
  ])
], -1);
const _hoisted_176 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "dip-switch",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("DIP Switches "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#dip-switch",
    "aria-label": 'Permalink to "DIP Switches {#dip-switch}"'
  }, "​")
], -1);
const _hoisted_177 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/dip_switch" }, "DIP Switches"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_178 = /* @__PURE__ */ createBaseVNode("code", null, "dip_switch", -1);
const _hoisted_179 = /* @__PURE__ */ createBaseVNode("code", null, "enabled", -1);
const _hoisted_180 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Enable the DIP Switches feature."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_181 = /* @__PURE__ */ createBaseVNode("code", null, "pins", -1);
const _hoisted_182 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "A list of GPIO pins connected to the MCU.")
], -1);
const _hoisted_183 = /* @__PURE__ */ createBaseVNode("code", null, "matrix_grid", -1);
const _hoisted_184 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "A list of matrix locations in the key matrix."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, "[ [0,6], [1,6], [2,6] ]")
  ])
], -1);
const _hoisted_185 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "eeprom",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("EEPROM "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#eeprom",
    "aria-label": 'Permalink to "EEPROM {#eeprom}"'
  }, "​")
], -1);
const _hoisted_186 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./drivers/eeprom" }, "EEPROM"),
  /* @__PURE__ */ createTextVNode(" driver.")
], -1);
const _hoisted_187 = /* @__PURE__ */ createBaseVNode("code", null, "eeprom", -1);
const _hoisted_188 = /* @__PURE__ */ createBaseVNode("code", null, "driver", -1);
const _hoisted_189 = /* @__PURE__ */ createStaticVNode("", 1);
const _hoisted_190 = /* @__PURE__ */ createBaseVNode("code", null, "wear_leveling", -1);
const _hoisted_191 = /* @__PURE__ */ createBaseVNode("code", null, "driver", -1);
const _hoisted_192 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The driver to use. Must be one of "),
    /* @__PURE__ */ createBaseVNode("code", null, "embedded_flash"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "legacy"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "rp2040_flash"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "spi_flash"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "custom"),
    /* @__PURE__ */ createTextVNode(".")
  ])
], -1);
const _hoisted_193 = /* @__PURE__ */ createBaseVNode("code", null, "backing_size", -1);
const _hoisted_194 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Number of bytes used by the wear-leveling algorithm for its underlying storage, and needs to be a multiple of the logical size.")
], -1);
const _hoisted_195 = /* @__PURE__ */ createBaseVNode("code", null, "logical_size", -1);
const _hoisted_196 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Number of bytes “exposed” to the rest of QMK and denotes the size of the usable EEPROM.")
], -1);
const _hoisted_197 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "encoder",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Encoder "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#encoder",
    "aria-label": 'Permalink to "Encoder {#encoder}"'
  }, "​")
], -1);
const _hoisted_198 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/encoders" }, "Encoder"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_199 = /* @__PURE__ */ createBaseVNode("code", null, "encoder", -1);
const _hoisted_200 = /* @__PURE__ */ createBaseVNode("code", null, "rotary", -1);
const _hoisted_201 = /* @__PURE__ */ createBaseVNode("code", null, "pin_a", -1);
const _hoisted_202 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The GPIO pin connected to the encoder's "),
    /* @__PURE__ */ createBaseVNode("code", null, "A"),
    /* @__PURE__ */ createTextVNode(" pin.")
  ])
], -1);
const _hoisted_203 = /* @__PURE__ */ createBaseVNode("code", null, "pin_b", -1);
const _hoisted_204 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The GPIO pin connected to the encoder's "),
    /* @__PURE__ */ createBaseVNode("code", null, "B"),
    /* @__PURE__ */ createTextVNode(" pin.")
  ])
], -1);
const _hoisted_205 = /* @__PURE__ */ createBaseVNode("code", null, "resolution", -1);
const _hoisted_206 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The number of edge transitions on both pins required to register an input."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "4")
  ])
], -1);
const _hoisted_207 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "host",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Host "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#host",
    "aria-label": 'Permalink to "Host {#host}"'
  }, "​")
], -1);
const _hoisted_208 = /* @__PURE__ */ createBaseVNode("code", null, "host", -1);
const _hoisted_209 = /* @__PURE__ */ createBaseVNode("code", null, "default", -1);
const _hoisted_210 = /* @__PURE__ */ createBaseVNode("code", null, "nkro", -1);
const _hoisted_211 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default nkro state."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_212 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "indicators",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Indicators "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#indicators",
    "aria-label": 'Permalink to "Indicators {#indicators}"'
  }, "​")
], -1);
const _hoisted_213 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/led_indicators" }, "LED Indicators"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_214 = /* @__PURE__ */ createBaseVNode("code", null, "indicators", -1);
const _hoisted_215 = /* @__PURE__ */ createBaseVNode("code", null, "caps_lock", -1);
const _hoisted_216 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The GPIO pin connected to the Caps Lock LED.")
], -1);
const _hoisted_217 = /* @__PURE__ */ createBaseVNode("code", null, "compose", -1);
const _hoisted_218 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The GPIO pin connected to the Compose LED.")
], -1);
const _hoisted_219 = /* @__PURE__ */ createBaseVNode("code", null, "kana", -1);
const _hoisted_220 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The GPIO pin connected to the Kana LED.")
], -1);
const _hoisted_221 = /* @__PURE__ */ createBaseVNode("code", null, "num_lock", -1);
const _hoisted_222 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The GPIO pin connected to the Num Lock LED.")
], -1);
const _hoisted_223 = /* @__PURE__ */ createBaseVNode("code", null, "on_state", -1);
const _hoisted_224 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The logical GPIO state required to turn the LEDs on."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "1"),
    /* @__PURE__ */ createTextVNode(" (on = high)")
  ])
], -1);
const _hoisted_225 = /* @__PURE__ */ createBaseVNode("code", null, "scroll_lock", -1);
const _hoisted_226 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The GPIO pin connected to the Scroll Lock LED.")
], -1);
const _hoisted_227 = /* @__PURE__ */ createStaticVNode("", 5);
const _hoisted_232 = /* @__PURE__ */ createBaseVNode("code", null, "community_layouts", -1);
const _hoisted_233 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "A list of community layouts supported by the keyboard."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, '["60_ansi", "60_iso"]')
  ])
], -1);
const _hoisted_234 = /* @__PURE__ */ createBaseVNode("code", null, "layout_aliases", -1);
const _hoisted_235 = /* @__PURE__ */ createStaticVNode("", 2);
const _hoisted_237 = /* @__PURE__ */ createBaseVNode("code", null, "layouts", -1);
const _hoisted_238 = /* @__PURE__ */ createBaseVNode("li", null, "A dictionary of layouts supported by the keyboard.", -1);
const _hoisted_239 = /* @__PURE__ */ createBaseVNode("code", null, "LAYOUT_<layout_name>", -1);
const _hoisted_240 = /* @__PURE__ */ createBaseVNode("code", null, "layout", -1);
const _hoisted_241 = /* @__PURE__ */ createBaseVNode("code", null, "matrix", -1);
const _hoisted_242 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The matrix position for the key."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, "[0, 4]"),
    /* @__PURE__ */ createTextVNode(" (row 0, column 4)")
  ])
], -1);
const _hoisted_243 = /* @__PURE__ */ createBaseVNode("code", null, "x", -1);
const _hoisted_244 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The absolute position of the key in the horizontal axis, in key units.")
], -1);
const _hoisted_245 = /* @__PURE__ */ createBaseVNode("code", null, "y", -1);
const _hoisted_246 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The absolute position of the key in the vertical axis, in key units.")
], -1);
const _hoisted_247 = /* @__PURE__ */ createBaseVNode("code", null, "h", -1);
const _hoisted_248 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The height of the key, in key units."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "1"),
    /* @__PURE__ */ createTextVNode(" (1u)")
  ])
], -1);
const _hoisted_249 = /* @__PURE__ */ createBaseVNode("code", null, "hand", -1);
const _hoisted_250 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The handedness of the key for Chordal Hold, either "),
    /* @__PURE__ */ createBaseVNode("code", null, '"L"'),
    /* @__PURE__ */ createTextVNode(" (left hand), "),
    /* @__PURE__ */ createBaseVNode("code", null, '"R"'),
    /* @__PURE__ */ createTextVNode(" (right hand), or "),
    /* @__PURE__ */ createBaseVNode("code", null, '"*"'),
    /* @__PURE__ */ createTextVNode(" (either or exempted handedness).")
  ])
], -1);
const _hoisted_251 = /* @__PURE__ */ createBaseVNode("code", null, "label", -1);
const _hoisted_252 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("What to name the key. This is "),
    /* @__PURE__ */ createBaseVNode("em", null, "not"),
    /* @__PURE__ */ createTextVNode(" a key assignment as in the keymap, but should usually correspond to the keycode for the first layer of the default keymap.")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"Escape"')
  ])
], -1);
const _hoisted_253 = /* @__PURE__ */ createBaseVNode("code", null, "r", -1);
const _hoisted_254 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The rotation angle in degrees. Currently not implemented.")
], -1);
const _hoisted_255 = /* @__PURE__ */ createBaseVNode("code", null, "rx", -1);
const _hoisted_256 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The absolute X position of the rotation axis. Currently not implemented.")
], -1);
const _hoisted_257 = /* @__PURE__ */ createBaseVNode("code", null, "ry", -1);
const _hoisted_258 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The absolute Y position of the rotation axis. Currently not implemented.")
], -1);
const _hoisted_259 = /* @__PURE__ */ createBaseVNode("code", null, "w", -1);
const _hoisted_260 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The width of the key, in key units."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "1"),
    /* @__PURE__ */ createTextVNode(" (1u)")
  ])
], -1);
const _hoisted_261 = /* @__PURE__ */ createBaseVNode("code", null, "encoder", -1);
const _hoisted_262 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The index of an encoder this key should be linked to")
], -1);
const _hoisted_263 = /* @__PURE__ */ createBaseVNode("li", null, [
  /* @__PURE__ */ createTextVNode("Example: "),
  /* @__PURE__ */ createBaseVNode("code", null, '{"label": "Shift", "matrix": [4, 0], "x": 0, "y": 4.25, "w": 2.25}')
], -1);
const _hoisted_264 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "leader-key",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Leader Key "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#leader-key",
    "aria-label": 'Permalink to "Leader Key {#leader-key}"'
  }, "​")
], -1);
const _hoisted_265 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/leader_key" }, "Leader Key"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_266 = /* @__PURE__ */ createBaseVNode("code", null, "leader_key", -1);
const _hoisted_267 = /* @__PURE__ */ createBaseVNode("code", null, "timing", -1);
const _hoisted_268 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Reset the "),
    /* @__PURE__ */ createBaseVNode("code", null, "timeout"),
    /* @__PURE__ */ createTextVNode(" on each keypress.")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_269 = /* @__PURE__ */ createBaseVNode("code", null, "strict_processing", -1);
const _hoisted_270 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Do not extract the tap keycodes from Layer-Tap and Mod-Tap key events."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_271 = /* @__PURE__ */ createBaseVNode("code", null, "timeout", -1);
const _hoisted_272 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The amount of time to complete a leader sequence in milliseconds."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "300"),
    /* @__PURE__ */ createTextVNode(" (300 ms)")
  ])
], -1);
const _hoisted_273 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "led-matrix",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("LED Matrix "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#led-matrix",
    "aria-label": 'Permalink to "LED Matrix {#led-matrix}"'
  }, "​")
], -1);
const _hoisted_274 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/led_matrix" }, "LED Matrix"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_275 = /* @__PURE__ */ createBaseVNode("code", null, "led_matrix", -1);
const _hoisted_276 = /* @__PURE__ */ createBaseVNode("code", null, "animations", -1);
const _hoisted_277 = /* @__PURE__ */ createStaticVNode("", 2);
const _hoisted_279 = /* @__PURE__ */ createBaseVNode("code", null, "center_point", -1);
const _hoisted_280 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The centroid (geometric center) of the LEDs. Used for certain effects."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "[112, 32]")
  ])
], -1);
const _hoisted_281 = /* @__PURE__ */ createBaseVNode("code", null, "flag_steps", -1);
const _hoisted_282 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "A list of flag bitfields that can be cycled through."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "[255, 5, 0]")
  ])
], -1);
const _hoisted_283 = /* @__PURE__ */ createBaseVNode("code", null, "default", -1);
const _hoisted_284 = /* @__PURE__ */ createBaseVNode("code", null, "animation", -1);
const _hoisted_285 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The default effect. Must be one of "),
    /* @__PURE__ */ createBaseVNode("code", null, "led_matrix.animations")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"solid"')
  ])
], -1);
const _hoisted_286 = /* @__PURE__ */ createBaseVNode("code", null, "on", -1);
const _hoisted_287 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default enabled state."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "true")
  ])
], -1);
const _hoisted_288 = /* @__PURE__ */ createBaseVNode("code", null, "val", -1);
const _hoisted_289 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default brightness level."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "max_brightness")
  ])
], -1);
const _hoisted_290 = /* @__PURE__ */ createBaseVNode("code", null, "speed", -1);
const _hoisted_291 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default animation speed."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "128")
  ])
], -1);
const _hoisted_292 = /* @__PURE__ */ createBaseVNode("code", null, "flags", -1);
const _hoisted_293 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default LED flags."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "255")
  ])
], -1);
const _hoisted_294 = /* @__PURE__ */ createBaseVNode("code", null, "driver", -1);
const _hoisted_295 = /* @__PURE__ */ createStaticVNode("", 1);
const _hoisted_296 = /* @__PURE__ */ createBaseVNode("code", null, "layout", -1);
const _hoisted_297 = /* @__PURE__ */ createBaseVNode("code", null, "flags", -1);
const _hoisted_298 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "A bitfield of flags describing the type of LED.")
], -1);
const _hoisted_299 = /* @__PURE__ */ createBaseVNode("code", null, "x", -1);
const _hoisted_300 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The position of the LED in the horizontal axis, from 0 to 224.")
], -1);
const _hoisted_301 = /* @__PURE__ */ createBaseVNode("code", null, "y", -1);
const _hoisted_302 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The position of the LED in the vertical axis, from 0 to 64.")
], -1);
const _hoisted_303 = /* @__PURE__ */ createBaseVNode("code", null, "matrix", -1);
const _hoisted_304 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The key matrix position associated with the LED."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, "[0, 2]")
  ])
], -1);
const _hoisted_305 = /* @__PURE__ */ createBaseVNode("li", null, [
  /* @__PURE__ */ createTextVNode("Example: "),
  /* @__PURE__ */ createBaseVNode("code", null, '{"matrix": [2, 1], "x": 20, "y": 48, "flags": 2}')
], -1);
const _hoisted_306 = /* @__PURE__ */ createBaseVNode("code", null, "led_flush_limit", -1);
const _hoisted_307 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Limits in milliseconds how frequently an animation will update the LEDs."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "16")
  ])
], -1);
const _hoisted_308 = /* @__PURE__ */ createBaseVNode("code", null, "led_process_limit", -1);
const _hoisted_309 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "(led_count + 4) / 5")
  ])
], -1);
const _hoisted_310 = /* @__PURE__ */ createBaseVNode("code", null, "max_brightness", -1);
const _hoisted_311 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The maximum value which brightness is scaled to, from 0 to 255."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "255")
  ])
], -1);
const _hoisted_312 = /* @__PURE__ */ createBaseVNode("code", null, "react_on_keyup", -1);
const _hoisted_313 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Animations react to keyup instead of keydown."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_314 = /* @__PURE__ */ createBaseVNode("code", null, "sleep", -1);
const _hoisted_315 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Turn off the LEDs when the host goes to sleep."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_316 = /* @__PURE__ */ createBaseVNode("code", null, "speed_steps", -1);
const _hoisted_317 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The value by which to increment the speed."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "16")
  ])
], -1);
const _hoisted_318 = /* @__PURE__ */ createBaseVNode("code", null, "split_count", -1);
const _hoisted_319 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "For split keyboards, the number of LEDs on each half."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, "[16, 16]")
  ])
], -1);
const _hoisted_320 = /* @__PURE__ */ createBaseVNode("code", null, "timeout", -1);
const _hoisted_321 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The LED activity timeout in milliseconds."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "0"),
    /* @__PURE__ */ createTextVNode(" (no timeout)")
  ])
], -1);
const _hoisted_322 = /* @__PURE__ */ createBaseVNode("code", null, "val_steps", -1);
const _hoisted_323 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The value by which to increment the brightness."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "8")
  ])
], -1);
const _hoisted_324 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "matrix",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Matrix "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#matrix",
    "aria-label": 'Permalink to "Matrix {#matrix}"'
  }, "​")
], -1);
const _hoisted_325 = /* @__PURE__ */ createBaseVNode("code", null, "debounce", -1);
const _hoisted_326 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The debounce time in milliseconds."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "5"),
    /* @__PURE__ */ createTextVNode(" (5 ms)")
  ])
], -1);
const _hoisted_327 = /* @__PURE__ */ createBaseVNode("code", null, "diode_direction", -1);
const _hoisted_328 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode('Which way the diodes are "pointing". Unused for '),
    /* @__PURE__ */ createBaseVNode("code", null, "matrix_pins.direct"),
    /* @__PURE__ */ createTextVNode(". Must be one of "),
    /* @__PURE__ */ createBaseVNode("code", null, "COL2ROW"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "ROW2COL"),
    /* @__PURE__ */ createTextVNode(".")
  ])
], -1);
const _hoisted_329 = /* @__PURE__ */ createBaseVNode("code", null, "matrix_pins", -1);
const _hoisted_330 = /* @__PURE__ */ createBaseVNode("code", null, "cols", -1);
const _hoisted_331 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "A list of GPIO pins connected to the matrix columns."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, '["A0", "A1", "A2"]')
  ])
], -1);
const _hoisted_332 = /* @__PURE__ */ createBaseVNode("code", null, "custom", -1);
const _hoisted_333 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Whether to use a custom matrix scanning implementation."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_334 = /* @__PURE__ */ createBaseVNode("code", null, "custom_lite", -1);
const _hoisted_335 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, 'Whether to use a "lite" custom matrix scanning implementation.'),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_336 = /* @__PURE__ */ createBaseVNode("code", null, "direct", -1);
const _hoisted_337 = /* @__PURE__ */ createStaticVNode("", 2);
const _hoisted_339 = /* @__PURE__ */ createBaseVNode("code", null, "ghost", -1);
const _hoisted_340 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Whether the matrix has no anti-ghosting diodes."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_341 = /* @__PURE__ */ createBaseVNode("code", null, "input_pressed_state", -1);
const _hoisted_342 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The logical GPIO state of the input pins when a key is pressed."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "0"),
    /* @__PURE__ */ createTextVNode(" (pressed = low)")
  ])
], -1);
const _hoisted_343 = /* @__PURE__ */ createBaseVNode("code", null, "io_delay", -1);
const _hoisted_344 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The amount of time to wait between row/col selection and col/row pin reading, in microseconds."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "30"),
    /* @__PURE__ */ createTextVNode(" (30 µs)")
  ])
], -1);
const _hoisted_345 = /* @__PURE__ */ createBaseVNode("code", null, "masked", -1);
const _hoisted_346 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Whether configured intersections should be ignored."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_347 = /* @__PURE__ */ createBaseVNode("code", null, "rows", -1);
const _hoisted_348 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "A list of GPIO pins connected to the matrix rows."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, '["B0", "B1", "B2"]')
  ])
], -1);
const _hoisted_349 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "mouse-keys",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Mouse Keys "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#mouse-keys",
    "aria-label": 'Permalink to "Mouse Keys {#mouse-keys}"'
  }, "​")
], -1);
const _hoisted_350 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/mouse_keys" }, "Mouse Keys"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_351 = /* @__PURE__ */ createBaseVNode("code", null, "mouse_key", -1);
const _hoisted_352 = /* @__PURE__ */ createBaseVNode("code", null, "delay", -1);
const _hoisted_353 = /* @__PURE__ */ createBaseVNode("code", null, "enabled", -1);
const _hoisted_354 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Enables the Mouse Keys feature."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_355 = /* @__PURE__ */ createBaseVNode("code", null, "interval", -1);
const _hoisted_356 = /* @__PURE__ */ createBaseVNode("code", null, "max_speed", -1);
const _hoisted_357 = /* @__PURE__ */ createBaseVNode("code", null, "time_to_max", -1);
const _hoisted_358 = /* @__PURE__ */ createBaseVNode("code", null, "wheel_delay", -1);
const _hoisted_359 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "one-shot",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("One Shot "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#one-shot",
    "aria-label": 'Permalink to "One Shot {#one-shot}"'
  }, "​")
], -1);
const _hoisted_360 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./one_shot_keys" }, "One Shot keys"),
  /* @__PURE__ */ createTextVNode(".")
], -1);
const _hoisted_361 = /* @__PURE__ */ createBaseVNode("code", null, "oneshot", -1);
const _hoisted_362 = /* @__PURE__ */ createBaseVNode("code", null, "tap_toggle", -1);
const _hoisted_363 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The number of times to tap the key in order to hold it.")
], -1);
const _hoisted_364 = /* @__PURE__ */ createBaseVNode("code", null, "timeout", -1);
const _hoisted_365 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The amount of time before the key is released in milliseconds.")
], -1);
const _hoisted_366 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "ps2",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("PS/2 "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#ps2",
    "aria-label": 'Permalink to "PS/2 {#ps2}"'
  }, "​")
], -1);
const _hoisted_367 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/ps2_mouse" }, "PS/2"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_368 = /* @__PURE__ */ createBaseVNode("code", null, "ps2", -1);
const _hoisted_369 = /* @__PURE__ */ createBaseVNode("code", null, "clock_pin", -1);
const _hoisted_370 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The GPIO pin connected to "),
    /* @__PURE__ */ createBaseVNode("code", null, "CLK"),
    /* @__PURE__ */ createTextVNode(" on the PS/2 device.")
  ])
], -1);
const _hoisted_371 = /* @__PURE__ */ createBaseVNode("code", null, "data_pin", -1);
const _hoisted_372 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The GPIO pin connected to "),
    /* @__PURE__ */ createBaseVNode("code", null, "DATA"),
    /* @__PURE__ */ createTextVNode(" on the PS/2 device.")
  ])
], -1);
const _hoisted_373 = /* @__PURE__ */ createBaseVNode("code", null, "driver", -1);
const _hoisted_374 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The PS/2 driver to use. Must be one of "),
    /* @__PURE__ */ createBaseVNode("code", null, "busywait"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "interrupt"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "usart"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "vendor"),
    /* @__PURE__ */ createTextVNode(".")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"busywait"')
  ])
], -1);
const _hoisted_375 = /* @__PURE__ */ createBaseVNode("code", null, "enabled", -1);
const _hoisted_376 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Enable the PS/2 feature."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_377 = /* @__PURE__ */ createBaseVNode("code", null, "mouse_enabled", -1);
const _hoisted_378 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Enable the PS/2 mouse handling."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_379 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "qmk-lufa-bootloader",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("QMK LUFA Bootloader "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#qmk-lufa-bootloader",
    "aria-label": 'Permalink to "QMK LUFA Bootloader {#qmk-lufa-bootloader}"'
  }, "​")
], -1);
const _hoisted_380 = /* @__PURE__ */ createBaseVNode("code", null, "qmk_lufa_bootloader", -1);
const _hoisted_381 = /* @__PURE__ */ createBaseVNode("code", null, "esc_input", -1);
const _hoisted_382 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode(`The GPIO pin connected to the designated "exit bootloader" key's row (if `),
    /* @__PURE__ */ createBaseVNode("code", null, "COL2ROW"),
    /* @__PURE__ */ createTextVNode(").")
  ])
], -1);
const _hoisted_383 = /* @__PURE__ */ createBaseVNode("code", null, "esc_output", -1);
const _hoisted_384 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode(`The GPIO pin connected to the designated "exit bootloader" key's column (if `),
    /* @__PURE__ */ createBaseVNode("code", null, "COL2ROW"),
    /* @__PURE__ */ createTextVNode(").")
  ])
], -1);
const _hoisted_385 = /* @__PURE__ */ createBaseVNode("code", null, "led", -1);
const _hoisted_386 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The GPIO pin connected to an LED to flash.")
], -1);
const _hoisted_387 = /* @__PURE__ */ createBaseVNode("code", null, "speaker", -1);
const _hoisted_388 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The GPIO pin connected to a speaker to click (can also be used for a second LED).")
], -1);
const _hoisted_389 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "rgblight",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("RGBLight "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#rgblight",
    "aria-label": 'Permalink to "RGBLight {#rgblight}"'
  }, "​")
], -1);
const _hoisted_390 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/rgblight" }, "RGB Lighting"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_391 = /* @__PURE__ */ createBaseVNode("code", null, "rgblight", -1);
const _hoisted_392 = /* @__PURE__ */ createBaseVNode("code", null, "led_count", -1);
const _hoisted_393 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The number of LEDs in the chain.")
], -1);
const _hoisted_394 = /* @__PURE__ */ createBaseVNode("code", null, "animations", -1);
const _hoisted_395 = /* @__PURE__ */ createStaticVNode("", 2);
const _hoisted_397 = /* @__PURE__ */ createBaseVNode("code", null, "brightness_steps", -1);
const _hoisted_398 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The value by which to increment the brightness."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "17")
  ])
], -1);
const _hoisted_399 = /* @__PURE__ */ createBaseVNode("code", null, "default", -1);
const _hoisted_400 = /* @__PURE__ */ createBaseVNode("code", null, "animation", -1);
const _hoisted_401 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The default effect. Must be one of "),
    /* @__PURE__ */ createBaseVNode("code", null, "rgblight.animations")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"static_light"')
  ])
], -1);
const _hoisted_402 = /* @__PURE__ */ createBaseVNode("code", null, "on", -1);
const _hoisted_403 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default enabled state."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "true")
  ])
], -1);
const _hoisted_404 = /* @__PURE__ */ createBaseVNode("code", null, "hue", -1);
const _hoisted_405 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default hue value."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "0")
  ])
], -1);
const _hoisted_406 = /* @__PURE__ */ createBaseVNode("code", null, "sat", -1);
const _hoisted_407 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default saturation value."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "255")
  ])
], -1);
const _hoisted_408 = /* @__PURE__ */ createBaseVNode("code", null, "val", -1);
const _hoisted_409 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default brightness level."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "max_brightness")
  ])
], -1);
const _hoisted_410 = /* @__PURE__ */ createBaseVNode("code", null, "speed", -1);
const _hoisted_411 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default animation speed."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "0")
  ])
], -1);
const _hoisted_412 = /* @__PURE__ */ createBaseVNode("code", null, "driver", -1);
const _hoisted_413 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The driver to use. Must be one of "),
    /* @__PURE__ */ createBaseVNode("code", null, "apa102"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "custom"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "ws2812"),
    /* @__PURE__ */ createTextVNode(".")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"ws2812"')
  ])
], -1);
const _hoisted_414 = /* @__PURE__ */ createBaseVNode("code", null, "hue_steps", -1);
const _hoisted_415 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The value by which to increment the hue."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "8")
  ])
], -1);
const _hoisted_416 = /* @__PURE__ */ createBaseVNode("code", null, "layers", -1);
const _hoisted_417 = /* @__PURE__ */ createBaseVNode("code", null, "blink", -1);
const _hoisted_418 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Enable layer blinking API."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_419 = /* @__PURE__ */ createBaseVNode("code", null, "enabled", -1);
const _hoisted_420 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Enable RGB Lighting Layers."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_421 = /* @__PURE__ */ createBaseVNode("code", null, "max", -1);
const _hoisted_422 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The maximum layer count, from 1 to 32."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "8")
  ])
], -1);
const _hoisted_423 = /* @__PURE__ */ createBaseVNode("code", null, "led_map", -1);
const _hoisted_424 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Remap LED indices."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, "[4, 3, 2, 1, 0]")
  ])
], -1);
const _hoisted_425 = /* @__PURE__ */ createBaseVNode("code", null, "max_brightness", -1);
const _hoisted_426 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, 'The maximum value which the HSV "V" component is scaled to, from 0 to 255.'),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "255")
  ])
], -1);
const _hoisted_427 = /* @__PURE__ */ createBaseVNode("code", null, "saturation_steps", -1);
const _hoisted_428 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The value by which to increment the suturation."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "17")
  ])
], -1);
const _hoisted_429 = /* @__PURE__ */ createBaseVNode("code", null, "sleep", -1);
const _hoisted_430 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Turn off the LEDs when the host goes to sleep."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_431 = /* @__PURE__ */ createBaseVNode("code", null, "split", -1);
const _hoisted_432 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Enable synchronization between split halves."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_433 = /* @__PURE__ */ createBaseVNode("code", null, "split_count", -1);
const _hoisted_434 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("When "),
    /* @__PURE__ */ createBaseVNode("code", null, "rgblight.split"),
    /* @__PURE__ */ createTextVNode(" is enabled, the number of LEDs on each half.")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, "[10, 10]")
  ])
], -1);
const _hoisted_435 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "rgb-matrix",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("RGB Matrix "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#rgb-matrix",
    "aria-label": 'Permalink to "RGB Matrix {#rgb-matrix}"'
  }, "​")
], -1);
const _hoisted_436 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/rgb_matrix" }, "RGB Matrix"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_437 = /* @__PURE__ */ createBaseVNode("code", null, "rgb_matrix", -1);
const _hoisted_438 = /* @__PURE__ */ createBaseVNode("code", null, "animations", -1);
const _hoisted_439 = /* @__PURE__ */ createStaticVNode("", 2);
const _hoisted_441 = /* @__PURE__ */ createBaseVNode("code", null, "center_point", -1);
const _hoisted_442 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The centroid (geometric center) of the LEDs. Used for certain effects."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "[112, 32]")
  ])
], -1);
const _hoisted_443 = /* @__PURE__ */ createBaseVNode("code", null, "flag_steps", -1);
const _hoisted_444 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "A list of flag bitfields that can be cycled through."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "[255, 5, 2, 0]")
  ])
], -1);
const _hoisted_445 = /* @__PURE__ */ createBaseVNode("code", null, "default", -1);
const _hoisted_446 = /* @__PURE__ */ createBaseVNode("code", null, "animation", -1);
const _hoisted_447 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The default effect. Must be one of "),
    /* @__PURE__ */ createBaseVNode("code", null, "rgb_matrix.animations")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"solid_color"')
  ])
], -1);
const _hoisted_448 = /* @__PURE__ */ createBaseVNode("code", null, "on", -1);
const _hoisted_449 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default enabled state."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "true")
  ])
], -1);
const _hoisted_450 = /* @__PURE__ */ createBaseVNode("code", null, "hue", -1);
const _hoisted_451 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default hue value."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "0")
  ])
], -1);
const _hoisted_452 = /* @__PURE__ */ createBaseVNode("code", null, "sat", -1);
const _hoisted_453 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default saturation value."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "255")
  ])
], -1);
const _hoisted_454 = /* @__PURE__ */ createBaseVNode("code", null, "val", -1);
const _hoisted_455 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default brightness level."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "max_brightness")
  ])
], -1);
const _hoisted_456 = /* @__PURE__ */ createBaseVNode("code", null, "speed", -1);
const _hoisted_457 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default animation speed."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "128")
  ])
], -1);
const _hoisted_458 = /* @__PURE__ */ createBaseVNode("code", null, "flags", -1);
const _hoisted_459 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The default LED flags."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "255")
  ])
], -1);
const _hoisted_460 = /* @__PURE__ */ createBaseVNode("code", null, "driver", -1);
const _hoisted_461 = /* @__PURE__ */ createStaticVNode("", 1);
const _hoisted_462 = /* @__PURE__ */ createBaseVNode("code", null, "hue_steps", -1);
const _hoisted_463 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The value by which to increment the hue."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "8")
  ])
], -1);
const _hoisted_464 = /* @__PURE__ */ createBaseVNode("code", null, "layout", -1);
const _hoisted_465 = /* @__PURE__ */ createBaseVNode("code", null, "flags", -1);
const _hoisted_466 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "A bitfield of flags describing the type of LED.")
], -1);
const _hoisted_467 = /* @__PURE__ */ createBaseVNode("code", null, "x", -1);
const _hoisted_468 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The position of the LED in the horizontal axis, from 0 to 224.")
], -1);
const _hoisted_469 = /* @__PURE__ */ createBaseVNode("code", null, "y", -1);
const _hoisted_470 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The position of the LED in the vertical axis, from 0 to 64.")
], -1);
const _hoisted_471 = /* @__PURE__ */ createBaseVNode("code", null, "matrix", -1);
const _hoisted_472 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The key matrix position associated with the LED."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, "[0, 2]")
  ])
], -1);
const _hoisted_473 = /* @__PURE__ */ createBaseVNode("li", null, [
  /* @__PURE__ */ createTextVNode("Example: "),
  /* @__PURE__ */ createBaseVNode("code", null, '{"matrix": [2, 1], "x": 20, "y": 48, "flags": 2}')
], -1);
const _hoisted_474 = /* @__PURE__ */ createBaseVNode("code", null, "led_flush_limit", -1);
const _hoisted_475 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Limits in milliseconds how frequently an animation will update the LEDs."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "16")
  ])
], -1);
const _hoisted_476 = /* @__PURE__ */ createBaseVNode("code", null, "led_process_limit", -1);
const _hoisted_477 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "(led_count + 4) / 5")
  ])
], -1);
const _hoisted_478 = /* @__PURE__ */ createBaseVNode("code", null, "max_brightness", -1);
const _hoisted_479 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, 'The maximum value which the HSV "V" component is scaled to, from 0 to 255.'),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "255")
  ])
], -1);
const _hoisted_480 = /* @__PURE__ */ createBaseVNode("code", null, "react_on_keyup", -1);
const _hoisted_481 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Animations react to keyup instead of keydown."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_482 = /* @__PURE__ */ createBaseVNode("code", null, "sat_steps", -1);
const _hoisted_483 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The value by which to increment the saturation."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "16")
  ])
], -1);
const _hoisted_484 = /* @__PURE__ */ createBaseVNode("code", null, "sleep", -1);
const _hoisted_485 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Turn off the LEDs when the host goes to sleep."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_486 = /* @__PURE__ */ createBaseVNode("code", null, "speed_steps", -1);
const _hoisted_487 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The value by which to increment the speed."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "16")
  ])
], -1);
const _hoisted_488 = /* @__PURE__ */ createBaseVNode("code", null, "split_count", -1);
const _hoisted_489 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "For split keyboards, the number of LEDs on each half."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, "[16, 16]")
  ])
], -1);
const _hoisted_490 = /* @__PURE__ */ createBaseVNode("code", null, "timeout", -1);
const _hoisted_491 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The LED activity timeout in milliseconds."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "0"),
    /* @__PURE__ */ createTextVNode(" (no timeout)")
  ])
], -1);
const _hoisted_492 = /* @__PURE__ */ createBaseVNode("code", null, "val_steps", -1);
const _hoisted_493 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The value by which to increment the brightness."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "16")
  ])
], -1);
const _hoisted_494 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "secure",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Secure "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#secure",
    "aria-label": 'Permalink to "Secure {#secure}"'
  }, "​")
], -1);
const _hoisted_495 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/secure" }, "Secure"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_496 = /* @__PURE__ */ createBaseVNode("code", null, "secure", -1);
const _hoisted_497 = /* @__PURE__ */ createBaseVNode("code", null, "enabled", -1);
const _hoisted_498 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Enable the Secure feature."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_499 = /* @__PURE__ */ createBaseVNode("code", null, "idle_timeout", -1);
const _hoisted_500 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Timeout while unlocked before returning to the locked state. Set to "),
    /* @__PURE__ */ createBaseVNode("code", null, "0"),
    /* @__PURE__ */ createTextVNode(" to disable.")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "60000"),
    /* @__PURE__ */ createTextVNode(" (1 minute)")
  ])
], -1);
const _hoisted_501 = /* @__PURE__ */ createBaseVNode("code", null, "unlock_sequence", -1);
const _hoisted_502 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, 'A list of up to five matrix locations comprising the "unlock sequence".'),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, "[[0, 0], [0, 1], [4, 3]]")
  ])
], -1);
const _hoisted_503 = /* @__PURE__ */ createBaseVNode("code", null, "unlock_timeout", -1);
const _hoisted_504 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Timeout for the user to perform the unlock sequence. Set to "),
    /* @__PURE__ */ createBaseVNode("code", null, "0"),
    /* @__PURE__ */ createTextVNode(" to disable.")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "5000"),
    /* @__PURE__ */ createTextVNode(" (5 seconds)")
  ])
], -1);
const _hoisted_505 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "split-keyboard",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Split Keyboard "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#split-keyboard",
    "aria-label": 'Permalink to "Split Keyboard {#split-keyboard}"'
  }, "​")
], -1);
const _hoisted_506 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/split_keyboard" }, "Split Keyboard"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_507 = /* @__PURE__ */ createBaseVNode("code", null, "split", -1);
const _hoisted_508 = /* @__PURE__ */ createStaticVNode("", 2);
const _hoisted_510 = /* @__PURE__ */ createBaseVNode("code", null, "enabled", -1);
const _hoisted_511 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Enable the Split Keyboard feature."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_512 = /* @__PURE__ */ createBaseVNode("li", null, [
  /* @__PURE__ */ createBaseVNode("code", null, "encoder"),
  /* @__PURE__ */ createBaseVNode("ul", null, [
    /* @__PURE__ */ createBaseVNode("li", null, [
      /* @__PURE__ */ createBaseVNode("code", null, "right"),
      /* @__PURE__ */ createBaseVNode("ul", null, [
        /* @__PURE__ */ createBaseVNode("li", null, [
          /* @__PURE__ */ createBaseVNode("code", null, "rotary"),
          /* @__PURE__ */ createBaseVNode("ul", null, [
            /* @__PURE__ */ createBaseVNode("li", null, [
              /* @__PURE__ */ createTextVNode("See "),
              /* @__PURE__ */ createBaseVNode("a", { href: "#encoder" }, "Encoder"),
              /* @__PURE__ */ createTextVNode(" config.")
            ])
          ])
        ])
      ])
    ])
  ])
], -1);
const _hoisted_513 = /* @__PURE__ */ createBaseVNode("code", null, "handedness", -1);
const _hoisted_514 = /* @__PURE__ */ createBaseVNode("code", null, "pin", -1);
const _hoisted_515 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The GPIO pin connected to determine handedness.")
], -1);
const _hoisted_516 = /* @__PURE__ */ createBaseVNode("code", null, "matrix_grid", -1);
const _hoisted_517 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The GPIO pins of the matrix position which determines the handedness."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, '["A1", "B5"]')
  ])
], -1);
const _hoisted_518 = /* @__PURE__ */ createBaseVNode("li", null, [
  /* @__PURE__ */ createBaseVNode("code", null, "matrix_pins"),
  /* @__PURE__ */ createBaseVNode("ul", null, [
    /* @__PURE__ */ createBaseVNode("li", null, [
      /* @__PURE__ */ createBaseVNode("code", null, "right"),
      /* @__PURE__ */ createBaseVNode("ul", null, [
        /* @__PURE__ */ createBaseVNode("li", null, [
          /* @__PURE__ */ createTextVNode("See "),
          /* @__PURE__ */ createBaseVNode("a", { href: "#matrix" }, "Matrix"),
          /* @__PURE__ */ createTextVNode(" config.")
        ])
      ])
    ])
  ])
], -1);
const _hoisted_519 = /* @__PURE__ */ createBaseVNode("code", null, "serial", -1);
const _hoisted_520 = /* @__PURE__ */ createBaseVNode("code", null, "driver", -1);
const _hoisted_521 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The driver to use. Must be one of "),
    /* @__PURE__ */ createBaseVNode("code", null, "bitbang"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "usart"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "vendor"),
    /* @__PURE__ */ createTextVNode(".")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"bitbang"')
  ])
], -1);
const _hoisted_522 = /* @__PURE__ */ createBaseVNode("code", null, "pin", -1);
const _hoisted_523 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The GPIO pin to use for transmit and receive.")
], -1);
const _hoisted_524 = /* @__PURE__ */ createBaseVNode("code", null, "speed", -1);
const _hoisted_525 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The protocol speed, from "),
    /* @__PURE__ */ createBaseVNode("code", null, "0"),
    /* @__PURE__ */ createTextVNode(" to "),
    /* @__PURE__ */ createBaseVNode("code", null, "5"),
    /* @__PURE__ */ createTextVNode(" (fastest to slowest).")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "1")
  ])
], -1);
const _hoisted_526 = /* @__PURE__ */ createBaseVNode("code", null, "transport", -1);
const _hoisted_527 = /* @__PURE__ */ createBaseVNode("code", null, "protocol", -1);
const _hoisted_528 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The split transport protocol to use. Must be one of "),
    /* @__PURE__ */ createBaseVNode("code", null, "custom"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "i2c"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "serial"),
    /* @__PURE__ */ createTextVNode(".")
  ])
], -1);
const _hoisted_529 = /* @__PURE__ */ createBaseVNode("code", null, "sync", -1);
const _hoisted_530 = /* @__PURE__ */ createBaseVNode("code", null, "activity", -1);
const _hoisted_531 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Mirror the activity timestamps to the secondary half."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_532 = /* @__PURE__ */ createBaseVNode("code", null, "detected_os", -1);
const _hoisted_533 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Mirror the "),
    /* @__PURE__ */ createBaseVNode("a", { href: "./features/os_detection" }, "detected OS"),
    /* @__PURE__ */ createTextVNode(" to the secondary half.")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_534 = /* @__PURE__ */ createBaseVNode("code", null, "haptic", -1);
const _hoisted_535 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Mirror the haptic state and process haptic feedback to the secondary half."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_536 = /* @__PURE__ */ createBaseVNode("code", null, "layer_state", -1);
const _hoisted_537 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Mirror the layer state to the secondary half."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_538 = /* @__PURE__ */ createBaseVNode("code", null, "indicators", -1);
const _hoisted_539 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Mirror the indicator state to the secondary half."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_540 = /* @__PURE__ */ createBaseVNode("code", null, "matrix_state", -1);
const _hoisted_541 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Mirror the main/primary half's matrix state to the secondary half."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_542 = /* @__PURE__ */ createBaseVNode("code", null, "modifiers", -1);
const _hoisted_543 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Mirror the modifier state to the secondary half."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_544 = /* @__PURE__ */ createBaseVNode("code", null, "oled", -1);
const _hoisted_545 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Mirror the OLED on/off status to the secondary half."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_546 = /* @__PURE__ */ createBaseVNode("code", null, "st7565", -1);
const _hoisted_547 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Mirror the ST7565 on/off status to the secondary half."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_548 = /* @__PURE__ */ createBaseVNode("code", null, "wpm", -1);
const _hoisted_549 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Mirror the current WPM value to the secondary half."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_550 = /* @__PURE__ */ createBaseVNode("code", null, "watchdog", -1);
const _hoisted_551 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Reboot the secondary half if it loses connection."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_552 = /* @__PURE__ */ createBaseVNode("code", null, "watchdog_timeout", -1);
const _hoisted_553 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The amount of time to wait for communication from the primary half in milliseconds.")
], -1);
const _hoisted_554 = /* @__PURE__ */ createBaseVNode("code", null, "usb_detect", -1);
const _hoisted_555 = /* @__PURE__ */ createBaseVNode("code", null, "enabled", -1);
const _hoisted_556 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Detect USB connection when determining split half roles.")
], -1);
const _hoisted_557 = /* @__PURE__ */ createBaseVNode("code", null, "polling_interval", -1);
const _hoisted_558 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The polling frequency in milliseconds."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "10"),
    /* @__PURE__ */ createTextVNode(" (10 ms)")
  ])
], -1);
const _hoisted_559 = /* @__PURE__ */ createBaseVNode("code", null, "timeout", -1);
const _hoisted_560 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The amount of time to wait for a USB connection in milliseconds."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "2000"),
    /* @__PURE__ */ createTextVNode(" (2 seconds)")
  ])
], -1);
const _hoisted_561 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "stenography",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Stenography "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#stenography",
    "aria-label": 'Permalink to "Stenography {#stenography}"'
  }, "​")
], -1);
const _hoisted_562 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./features/stenography" }, "Stenography"),
  /* @__PURE__ */ createTextVNode(" feature.")
], -1);
const _hoisted_563 = /* @__PURE__ */ createBaseVNode("code", null, "stenography", -1);
const _hoisted_564 = /* @__PURE__ */ createBaseVNode("code", null, "enabled", -1);
const _hoisted_565 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Enable the Stenography feature."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_566 = /* @__PURE__ */ createBaseVNode("code", null, "protocol", -1);
const _hoisted_567 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The Steno protocol to use. Must be one of "),
    /* @__PURE__ */ createBaseVNode("code", null, "all"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "geminipr"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "txbolt"),
    /* @__PURE__ */ createTextVNode(".")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"all"')
  ])
], -1);
const _hoisted_568 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "usb",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("USB "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#usb",
    "aria-label": 'Permalink to "USB {#usb}"'
  }, "​")
], -1);
const _hoisted_569 = /* @__PURE__ */ createBaseVNode("code", null, "usb", -1);
const _hoisted_570 = /* @__PURE__ */ createBaseVNode("code", null, "device_version", -1);
const _hoisted_571 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("A BCD version number in the format "),
    /* @__PURE__ */ createBaseVNode("code", null, "MM.m.r"),
    /* @__PURE__ */ createTextVNode(" (up to "),
    /* @__PURE__ */ createBaseVNode("code", null, "99.9.9"),
    /* @__PURE__ */ createTextVNode(").")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"1.0.0"')
  ])
], -1);
const _hoisted_572 = /* @__PURE__ */ createBaseVNode("code", null, "pid", -1);
const _hoisted_573 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The USB product ID as a four-digit hexadecimal number."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"0x23B0"')
  ])
], -1);
const _hoisted_574 = /* @__PURE__ */ createBaseVNode("code", null, "vid", -1);
const _hoisted_575 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The USB vendor ID as a four-digit hexadecimal number."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Example: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"0xC1ED"')
  ])
], -1);
const _hoisted_576 = /* @__PURE__ */ createBaseVNode("code", null, "max_power", -1);
const _hoisted_577 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The maximum current draw the host should expect from the device. This does not control the actual current usage."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "500"),
    /* @__PURE__ */ createTextVNode(" (500 mA)")
  ])
], -1);
const _hoisted_578 = /* @__PURE__ */ createBaseVNode("code", null, "no_startup_check", -1);
const _hoisted_579 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Disable USB suspend check after keyboard startup."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_580 = /* @__PURE__ */ createBaseVNode("code", null, "polling_interval", -1);
const _hoisted_581 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The frequency at which the host should poll the keyboard for reports."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "1"),
    /* @__PURE__ */ createTextVNode(" (1 ms/1000 Hz)")
  ])
], -1);
const _hoisted_582 = /* @__PURE__ */ createBaseVNode("code", null, "shared_endpoint", -1);
const _hoisted_583 = /* @__PURE__ */ createBaseVNode("code", null, "keyboard", -1);
const _hoisted_584 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, 'Send keyboard reports through the "shared" USB endpoint.'),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_585 = /* @__PURE__ */ createBaseVNode("code", null, "mouse", -1);
const _hoisted_586 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, 'Send mouse reports through the "shared" USB endpoint.'),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "true")
  ])
], -1);
const _hoisted_587 = /* @__PURE__ */ createBaseVNode("code", null, "suspend_wakeup_delay", -1);
const _hoisted_588 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "The amount of time to wait after sending a wakeup packet, in milliseconds."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "0"),
    /* @__PURE__ */ createTextVNode(" (disabled)")
  ])
], -1);
const _hoisted_589 = /* @__PURE__ */ createBaseVNode("code", null, "wait_for_enumeration", -1);
const _hoisted_590 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Force the keyboard to wait for USB enumeration before starting up."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
const _hoisted_591 = /* @__PURE__ */ createBaseVNode("h2", {
  id: "ws2812",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("WS2812 "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#ws2812",
    "aria-label": 'Permalink to "WS2812 {#ws2812}"'
  }, "​")
], -1);
const _hoisted_592 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Configures the "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./drivers/ws2812" }, "WS2812"),
  /* @__PURE__ */ createTextVNode(" driver.")
], -1);
const _hoisted_593 = /* @__PURE__ */ createBaseVNode("code", null, "ws2812", -1);
const _hoisted_594 = /* @__PURE__ */ createBaseVNode("code", null, "driver", -1);
const _hoisted_595 = /* @__PURE__ */ createStaticVNode("", 1);
const _hoisted_596 = /* @__PURE__ */ createBaseVNode("code", null, "pin", -1);
const _hoisted_597 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The GPIO pin connected to "),
    /* @__PURE__ */ createBaseVNode("code", null, "DI"),
    /* @__PURE__ */ createTextVNode(" on the first LED in the chain ("),
    /* @__PURE__ */ createBaseVNode("code", null, "bitbang"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "pwm"),
    /* @__PURE__ */ createTextVNode(", "),
    /* @__PURE__ */ createBaseVNode("code", null, "spi"),
    /* @__PURE__ */ createTextVNode(" and "),
    /* @__PURE__ */ createBaseVNode("code", null, "vendor"),
    /* @__PURE__ */ createTextVNode(" drivers only).")
  ])
], -1);
const _hoisted_598 = /* @__PURE__ */ createBaseVNode("code", null, "i2c_address", -1);
const _hoisted_599 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The I²C address of the WS2812 controller ("),
    /* @__PURE__ */ createBaseVNode("code", null, "i2c"),
    /* @__PURE__ */ createTextVNode(" driver only).")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, '"0xB0"')
  ])
], -1);
const _hoisted_600 = /* @__PURE__ */ createBaseVNode("code", null, "i2c_timeout", -1);
const _hoisted_601 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("The I²C timeout in milliseconds ("),
    /* @__PURE__ */ createBaseVNode("code", null, "i2c"),
    /* @__PURE__ */ createTextVNode(" driver only).")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "100"),
    /* @__PURE__ */ createTextVNode(" (100 ms)")
  ])
], -1);
const _hoisted_602 = /* @__PURE__ */ createBaseVNode("code", null, "rgbw", -1);
const _hoisted_603 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, "Enable RGBW LEDs."),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Default: "),
    /* @__PURE__ */ createBaseVNode("code", null, "false")
  ])
], -1);
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  const _component_Badge = resolveComponent("Badge");
  return openBlock(), createElementBlock("div", null, [
    _hoisted_1,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_5,
        createTextVNode(),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [
            createTextVNode("String")
          ]),
          _: 1
        }),
        createTextVNode(),
        createVNode(_component_Badge, null, {
          default: withCtx(() => [
            createTextVNode("Required")
          ]),
          _: 1
        }),
        _hoisted_6
      ]),
      createBaseVNode("li", null, [
        _hoisted_7,
        createTextVNode(),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [
            createTextVNode("String")
          ]),
          _: 1
        }),
        createTextVNode(),
        createVNode(_component_Badge, null, {
          default: withCtx(() => [
            createTextVNode("Required")
          ]),
          _: 1
        }),
        _hoisted_8
      ]),
      createBaseVNode("li", null, [
        _hoisted_9,
        createTextVNode(),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [
            createTextVNode("String")
          ]),
          _: 1
        }),
        createTextVNode(),
        createVNode(_component_Badge, null, {
          default: withCtx(() => [
            createTextVNode("Required")
          ]),
          _: 1
        }),
        _hoisted_10
      ]),
      createBaseVNode("li", null, [
        _hoisted_11,
        createTextVNode(),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [
            createTextVNode("String")
          ]),
          _: 1
        }),
        createTextVNode(),
        createVNode(_component_Badge, null, {
          default: withCtx(() => [
            createTextVNode("Required")
          ]),
          _: 1
        }),
        _hoisted_12
      ]),
      createBaseVNode("li", null, [
        _hoisted_13,
        createTextVNode(),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [
            createTextVNode("String")
          ]),
          _: 1
        }),
        _hoisted_14
      ]),
      createBaseVNode("li", null, [
        _hoisted_15,
        createTextVNode(),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [
            createTextVNode("Array: String")
          ]),
          _: 1
        }),
        _hoisted_16
      ])
    ]),
    _hoisted_17,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_18,
        createTextVNode(),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [
            createTextVNode("String")
          ]),
          _: 1
        }),
        _hoisted_19
      ]),
      createBaseVNode("li", null, [
        _hoisted_20,
        createTextVNode(),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [
            createTextVNode("String")
          ]),
          _: 1
        }),
        _hoisted_21
      ]),
      createBaseVNode("li", null, [
        _hoisted_22,
        createTextVNode(),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [
            createTextVNode("String")
          ]),
          _: 1
        }),
        _hoisted_23
      ]),
      createBaseVNode("li", null, [
        _hoisted_24,
        createTextVNode(),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [
            createTextVNode("String")
          ]),
          _: 1
        }),
        _hoisted_25
      ]),
      createBaseVNode("li", null, [
        _hoisted_26,
        createTextVNode(),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [
            createTextVNode("String")
          ]),
          _: 1
        }),
        _hoisted_27
      ])
    ]),
    _hoisted_28,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_29,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_30,
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("String")
              ]),
              _: 1
            }),
            _hoisted_31
          ]),
          createBaseVNode("li", null, [
            _hoisted_32,
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("String")
              ]),
              _: 1
            }),
            _hoisted_33
          ]),
          createBaseVNode("li", null, [
            _hoisted_34,
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_35
          ])
        ])
      ]),
      createBaseVNode("li", null, [
        _hoisted_36,
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [
            createTextVNode("Object: Boolean")
          ]),
          _: 1
        }),
        _hoisted_37
      ]),
      createBaseVNode("li", null, [
        _hoisted_39,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_40,
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _hoisted_41,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Boolean")
                  ]),
                  _: 1
                }),
                _hoisted_42
              ]),
              createBaseVNode("li", null, [
                _hoisted_43,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Boolean")
                  ]),
                  _: 1
                }),
                _hoisted_44
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _hoisted_45,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_46
          ]),
          createBaseVNode("li", null, [
            _hoisted_47,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_48
          ])
        ])
      ]),
      createBaseVNode("li", null, [
        _hoisted_49,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_50,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_51
          ]),
          createBaseVNode("li", null, [
            _hoisted_52,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_53
          ]),
          createBaseVNode("li", null, [
            _hoisted_54,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_55
          ]),
          createBaseVNode("li", null, [
            _hoisted_56,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_57
          ]),
          createBaseVNode("li", null, [
            _hoisted_58,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_59
          ]),
          createBaseVNode("li", null, [
            _hoisted_60,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_61
          ]),
          createBaseVNode("li", null, [
            _hoisted_62,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_63
          ]),
          createBaseVNode("li", null, [
            _hoisted_64,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_65
          ]),
          createBaseVNode("li", null, [
            _hoisted_66,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_67
          ]),
          createBaseVNode("li", null, [
            _hoisted_68,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_69
          ])
        ])
      ])
    ]),
    _hoisted_70,
    _hoisted_71,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_72,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_73,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Pin")
              ]),
              _: 1
            }),
            createTextVNode(),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [
                createTextVNode("Required")
              ]),
              _: 1
            }),
            _hoisted_74
          ]),
          createBaseVNode("li", null, [
            _hoisted_75,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Pin")
              ]),
              _: 1
            }),
            createTextVNode(),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [
                createTextVNode("Required")
              ]),
              _: 1
            }),
            _hoisted_76
          ]),
          createBaseVNode("li", null, [
            _hoisted_77,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_78
          ])
        ])
      ])
    ]),
    _hoisted_79,
    _hoisted_80,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_81,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_82,
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _hoisted_83,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Boolean")
                  ]),
                  _: 1
                }),
                _hoisted_84
              ]),
              createBaseVNode("li", null, [
                _hoisted_85,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Boolean")
                  ]),
                  _: 1
                }),
                _hoisted_86
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _hoisted_87,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("String")
              ]),
              _: 1
            }),
            _hoisted_88
          ]),
          createBaseVNode("li", null, [
            _hoisted_89,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_90
          ]),
          createBaseVNode("li", null, [
            _hoisted_91,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Pin")
              ]),
              _: 1
            }),
            createTextVNode(),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [
                createTextVNode("Required")
              ]),
              _: 1
            }),
            _hoisted_92
          ]),
          createBaseVNode("li", null, [
            _hoisted_93,
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _hoisted_94,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("0|1")
                  ]),
                  _: 1
                }),
                _hoisted_95
              ]),
              createBaseVNode("li", null, [
                _hoisted_96,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Pin")
                  ]),
                  _: 1
                }),
                _hoisted_97
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _hoisted_98,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_99
          ])
        ])
      ])
    ]),
    _hoisted_100,
    _hoisted_101,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_102,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_103,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_104
          ]),
          createBaseVNode("li", null, [
            _hoisted_105,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_106
          ]),
          createBaseVNode("li", null, [
            _hoisted_107,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_108
          ]),
          createBaseVNode("li", null, [
            _hoisted_109,
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _hoisted_110,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Boolean")
                  ]),
                  _: 1
                }),
                _hoisted_111
              ]),
              createBaseVNode("li", null, [
                _hoisted_112,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Boolean")
                  ]),
                  _: 1
                }),
                _hoisted_113
              ]),
              createBaseVNode("li", null, [
                _hoisted_114,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_115
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _hoisted_116,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("String")
              ]),
              _: 1
            }),
            _hoisted_117
          ]),
          createBaseVNode("li", null, [
            _hoisted_118,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_119
          ]),
          createBaseVNode("li", null, [
            _hoisted_120,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_121
          ]),
          createBaseVNode("li", null, [
            _hoisted_122,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("0|1")
              ]),
              _: 1
            }),
            _hoisted_123
          ]),
          createBaseVNode("li", null, [
            _hoisted_124,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Pin")
              ]),
              _: 1
            }),
            _hoisted_125
          ]),
          createBaseVNode("li", null, [
            _hoisted_126,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Pin")
              ]),
              _: 1
            }),
            _hoisted_127
          ])
        ])
      ])
    ]),
    _hoisted_128,
    _hoisted_129,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_130,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_131,
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _hoisted_132,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Pin")
                  ]),
                  _: 1
                }),
                createTextVNode(),
                createVNode(_component_Badge, null, {
                  default: withCtx(() => [
                    createTextVNode("Required")
                  ]),
                  _: 1
                }),
                _hoisted_133
              ]),
              createBaseVNode("li", null, [
                _hoisted_134,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_135
              ]),
              createBaseVNode("li", null, [
                _hoisted_136,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_137
              ]),
              createBaseVNode("li", null, [
                _hoisted_138,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_139
              ]),
              createBaseVNode("li", null, [
                _hoisted_140,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_141
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _hoisted_142,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("String")
              ]),
              _: 1
            }),
            createTextVNode(),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [
                createTextVNode("Required")
              ]),
              _: 1
            }),
            _hoisted_143
          ]),
          createBaseVNode("li", null, [
            _hoisted_144,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_145
          ])
        ])
      ])
    ]),
    _hoisted_146,
    _hoisted_147,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_148,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_149,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("String")
              ]),
              _: 1
            }),
            _hoisted_150
          ])
        ])
      ])
    ]),
    _hoisted_151,
    _hoisted_152,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_153,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_154,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_155
          ]),
          createBaseVNode("li", null, [
            _hoisted_156,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Matrix")
              ]),
              _: 1
            }),
            _hoisted_157
          ])
        ])
      ])
    ]),
    _hoisted_158,
    _hoisted_159,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_160,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_161,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_162
          ]),
          createBaseVNode("li", null, [
            _hoisted_163,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_164
          ]),
          createBaseVNode("li", null, [
            _hoisted_165,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_166
          ]),
          createBaseVNode("li", null, [
            _hoisted_167,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_168
          ]),
          createBaseVNode("li", null, [
            _hoisted_169,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_170
          ])
        ])
      ])
    ]),
    _hoisted_171,
    _hoisted_172,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_173,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_174,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_175
          ])
        ])
      ])
    ]),
    _hoisted_176,
    _hoisted_177,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_178,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_179,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_180
          ]),
          createBaseVNode("li", null, [
            _hoisted_181,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Pin")
              ]),
              _: 1
            }),
            _hoisted_182
          ]),
          createBaseVNode("li", null, [
            _hoisted_183,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Matrix")
              ]),
              _: 1
            }),
            _hoisted_184
          ])
        ])
      ])
    ]),
    _hoisted_185,
    _hoisted_186,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_187,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_188,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("String")
              ]),
              _: 1
            }),
            _hoisted_189
          ]),
          createBaseVNode("li", null, [
            _hoisted_190,
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _hoisted_191,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("String")
                  ]),
                  _: 1
                }),
                _hoisted_192
              ]),
              createBaseVNode("li", null, [
                _hoisted_193,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_194
              ]),
              createBaseVNode("li", null, [
                _hoisted_195,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_196
              ])
            ])
          ])
        ])
      ])
    ]),
    _hoisted_197,
    _hoisted_198,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_199,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_200,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Object")
              ]),
              _: 1
            }),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("A list of encoder objects. "),
                createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    _hoisted_201,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Pin")
                      ]),
                      _: 1
                    }),
                    createTextVNode(),
                    createVNode(_component_Badge, null, {
                      default: withCtx(() => [
                        createTextVNode("Required")
                      ]),
                      _: 1
                    }),
                    _hoisted_202
                  ]),
                  createBaseVNode("li", null, [
                    _hoisted_203,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Pin")
                      ]),
                      _: 1
                    }),
                    createTextVNode(),
                    createVNode(_component_Badge, null, {
                      default: withCtx(() => [
                        createTextVNode("Required")
                      ]),
                      _: 1
                    }),
                    _hoisted_204
                  ]),
                  createBaseVNode("li", null, [
                    _hoisted_205,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Number")
                      ]),
                      _: 1
                    }),
                    _hoisted_206
                  ])
                ])
              ])
            ])
          ])
        ])
      ])
    ]),
    _hoisted_207,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_208,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_209,
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _hoisted_210,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Boolean")
                  ]),
                  _: 1
                }),
                _hoisted_211
              ])
            ])
          ])
        ])
      ])
    ]),
    _hoisted_212,
    _hoisted_213,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_214,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_215,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Pin")
              ]),
              _: 1
            }),
            _hoisted_216
          ]),
          createBaseVNode("li", null, [
            _hoisted_217,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Pin")
              ]),
              _: 1
            }),
            _hoisted_218
          ]),
          createBaseVNode("li", null, [
            _hoisted_219,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Pin")
              ]),
              _: 1
            }),
            _hoisted_220
          ]),
          createBaseVNode("li", null, [
            _hoisted_221,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Pin")
              ]),
              _: 1
            }),
            _hoisted_222
          ]),
          createBaseVNode("li", null, [
            _hoisted_223,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("0|1")
              ]),
              _: 1
            }),
            _hoisted_224
          ]),
          createBaseVNode("li", null, [
            _hoisted_225,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Pin")
              ]),
              _: 1
            }),
            _hoisted_226
          ])
        ])
      ])
    ]),
    _hoisted_227,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_232,
        createTextVNode(),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [
            createTextVNode("Array: String")
          ]),
          _: 1
        }),
        _hoisted_233
      ]),
      createBaseVNode("li", null, [
        _hoisted_234,
        createTextVNode(),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [
            createTextVNode("Object: String")
          ]),
          _: 1
        }),
        _hoisted_235
      ]),
      createBaseVNode("li", null, [
        _hoisted_237,
        createTextVNode(),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [
            createTextVNode("Object")
          ]),
          _: 1
        }),
        createBaseVNode("ul", null, [
          _hoisted_238,
          createBaseVNode("li", null, [
            _hoisted_239,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Object")
              ]),
              _: 1
            }),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _hoisted_240,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Array: Object")
                  ]),
                  _: 1
                }),
                createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    createTextVNode("A list of key dictionaries comprising the layout. Each key dictionary contains: "),
                    createBaseVNode("ul", null, [
                      createBaseVNode("li", null, [
                        _hoisted_241,
                        createTextVNode(),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [
                            createTextVNode("Matrix")
                          ]),
                          _: 1
                        }),
                        createTextVNode(),
                        createVNode(_component_Badge, null, {
                          default: withCtx(() => [
                            createTextVNode("Required")
                          ]),
                          _: 1
                        }),
                        _hoisted_242
                      ]),
                      createBaseVNode("li", null, [
                        _hoisted_243,
                        createTextVNode(),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [
                            createTextVNode("KeyUnit")
                          ]),
                          _: 1
                        }),
                        createTextVNode(),
                        createVNode(_component_Badge, null, {
                          default: withCtx(() => [
                            createTextVNode("Required")
                          ]),
                          _: 1
                        }),
                        _hoisted_244
                      ]),
                      createBaseVNode("li", null, [
                        _hoisted_245,
                        createTextVNode(),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [
                            createTextVNode("KeyUnit")
                          ]),
                          _: 1
                        }),
                        createTextVNode(),
                        createVNode(_component_Badge, null, {
                          default: withCtx(() => [
                            createTextVNode("Required")
                          ]),
                          _: 1
                        }),
                        _hoisted_246
                      ]),
                      createBaseVNode("li", null, [
                        _hoisted_247,
                        createTextVNode(),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [
                            createTextVNode("KeyUnit")
                          ]),
                          _: 1
                        }),
                        _hoisted_248
                      ]),
                      createBaseVNode("li", null, [
                        _hoisted_249,
                        createTextVNode(),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [
                            createTextVNode("String")
                          ]),
                          _: 1
                        }),
                        _hoisted_250
                      ]),
                      createBaseVNode("li", null, [
                        _hoisted_251,
                        createTextVNode(),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [
                            createTextVNode("String")
                          ]),
                          _: 1
                        }),
                        _hoisted_252
                      ]),
                      createBaseVNode("li", null, [
                        _hoisted_253,
                        createTextVNode(),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [
                            createTextVNode("Number")
                          ]),
                          _: 1
                        }),
                        _hoisted_254
                      ]),
                      createBaseVNode("li", null, [
                        _hoisted_255,
                        createTextVNode(),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [
                            createTextVNode("Number")
                          ]),
                          _: 1
                        }),
                        _hoisted_256
                      ]),
                      createBaseVNode("li", null, [
                        _hoisted_257,
                        createTextVNode(),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [
                            createTextVNode("Number")
                          ]),
                          _: 1
                        }),
                        _hoisted_258
                      ]),
                      createBaseVNode("li", null, [
                        _hoisted_259,
                        createTextVNode(),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [
                            createTextVNode("KeyUnit")
                          ]),
                          _: 1
                        }),
                        _hoisted_260
                      ]),
                      createBaseVNode("li", null, [
                        _hoisted_261,
                        createTextVNode(),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [
                            createTextVNode("Number")
                          ]),
                          _: 1
                        }),
                        _hoisted_262
                      ]),
                      _hoisted_263
                    ])
                  ])
                ])
              ])
            ])
          ])
        ])
      ])
    ]),
    _hoisted_264,
    _hoisted_265,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_266,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_267,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_268
          ]),
          createBaseVNode("li", null, [
            _hoisted_269,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_270
          ]),
          createBaseVNode("li", null, [
            _hoisted_271,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_272
          ])
        ])
      ])
    ]),
    _hoisted_273,
    _hoisted_274,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_275,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_276,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Object: Boolean")
              ]),
              _: 1
            }),
            _hoisted_277
          ]),
          createBaseVNode("li", null, [
            _hoisted_279,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Number")
              ]),
              _: 1
            }),
            _hoisted_280
          ]),
          createBaseVNode("li", null, [
            _hoisted_281,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Number")
              ]),
              _: 1
            }),
            _hoisted_282
          ]),
          createBaseVNode("li", null, [
            _hoisted_283,
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _hoisted_284,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("String")
                  ]),
                  _: 1
                }),
                _hoisted_285
              ]),
              createBaseVNode("li", null, [
                _hoisted_286,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Boolean")
                  ]),
                  _: 1
                }),
                _hoisted_287
              ]),
              createBaseVNode("li", null, [
                _hoisted_288,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_289
              ]),
              createBaseVNode("li", null, [
                _hoisted_290,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_291
              ]),
              createBaseVNode("li", null, [
                _hoisted_292,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_293
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _hoisted_294,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("String")
              ]),
              _: 1
            }),
            createTextVNode(),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [
                createTextVNode("Required")
              ]),
              _: 1
            }),
            _hoisted_295
          ]),
          createBaseVNode("li", null, [
            _hoisted_296,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Object")
              ]),
              _: 1
            }),
            createTextVNode(),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [
                createTextVNode("Required")
              ]),
              _: 1
            }),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("List of LED configuration dictionaries. Each dictionary contains: "),
                createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    _hoisted_297,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Number")
                      ]),
                      _: 1
                    }),
                    createTextVNode(),
                    createVNode(_component_Badge, null, {
                      default: withCtx(() => [
                        createTextVNode("Required")
                      ]),
                      _: 1
                    }),
                    _hoisted_298
                  ]),
                  createBaseVNode("li", null, [
                    _hoisted_299,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Number")
                      ]),
                      _: 1
                    }),
                    createTextVNode(),
                    createVNode(_component_Badge, null, {
                      default: withCtx(() => [
                        createTextVNode("Required")
                      ]),
                      _: 1
                    }),
                    _hoisted_300
                  ]),
                  createBaseVNode("li", null, [
                    _hoisted_301,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Number")
                      ]),
                      _: 1
                    }),
                    createTextVNode(),
                    createVNode(_component_Badge, null, {
                      default: withCtx(() => [
                        createTextVNode("Required")
                      ]),
                      _: 1
                    }),
                    _hoisted_302
                  ]),
                  createBaseVNode("li", null, [
                    _hoisted_303,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Matrix")
                      ]),
                      _: 1
                    }),
                    _hoisted_304
                  ]),
                  _hoisted_305
                ])
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _hoisted_306,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_307
          ]),
          createBaseVNode("li", null, [
            _hoisted_308,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_309
          ]),
          createBaseVNode("li", null, [
            _hoisted_310,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_311
          ]),
          createBaseVNode("li", null, [
            _hoisted_312,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_313
          ]),
          createBaseVNode("li", null, [
            _hoisted_314,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_315
          ]),
          createBaseVNode("li", null, [
            _hoisted_316,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_317
          ]),
          createBaseVNode("li", null, [
            _hoisted_318,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Number")
              ]),
              _: 1
            }),
            _hoisted_319
          ]),
          createBaseVNode("li", null, [
            _hoisted_320,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_321
          ]),
          createBaseVNode("li", null, [
            _hoisted_322,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_323
          ])
        ])
      ])
    ]),
    _hoisted_324,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_325,
        createTextVNode(),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [
            createTextVNode("Number")
          ]),
          _: 1
        }),
        _hoisted_326
      ]),
      createBaseVNode("li", null, [
        _hoisted_327,
        createTextVNode(),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [
            createTextVNode("String")
          ]),
          _: 1
        }),
        _hoisted_328
      ]),
      createBaseVNode("li", null, [
        _hoisted_329,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_330,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Pin")
              ]),
              _: 1
            }),
            _hoisted_331
          ]),
          createBaseVNode("li", null, [
            _hoisted_332,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_333
          ]),
          createBaseVNode("li", null, [
            _hoisted_334,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_335
          ]),
          createBaseVNode("li", null, [
            _hoisted_336,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Array: Pin")
              ]),
              _: 1
            }),
            _hoisted_337
          ]),
          createBaseVNode("li", null, [
            _hoisted_339,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_340
          ]),
          createBaseVNode("li", null, [
            _hoisted_341,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("0|1")
              ]),
              _: 1
            }),
            _hoisted_342
          ]),
          createBaseVNode("li", null, [
            _hoisted_343,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_344
          ]),
          createBaseVNode("li", null, [
            _hoisted_345,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_346
          ]),
          createBaseVNode("li", null, [
            _hoisted_347,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Pin")
              ]),
              _: 1
            }),
            _hoisted_348
          ])
        ])
      ])
    ]),
    _hoisted_349,
    _hoisted_350,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_351,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_352,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            })
          ]),
          createBaseVNode("li", null, [
            _hoisted_353,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_354
          ]),
          createBaseVNode("li", null, [
            _hoisted_355,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            })
          ]),
          createBaseVNode("li", null, [
            _hoisted_356,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            })
          ]),
          createBaseVNode("li", null, [
            _hoisted_357,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            })
          ]),
          createBaseVNode("li", null, [
            _hoisted_358,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            })
          ])
        ])
      ])
    ]),
    _hoisted_359,
    _hoisted_360,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_361,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_362,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_363
          ]),
          createBaseVNode("li", null, [
            _hoisted_364,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_365
          ])
        ])
      ])
    ]),
    _hoisted_366,
    _hoisted_367,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_368,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_369,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Pin")
              ]),
              _: 1
            }),
            _hoisted_370
          ]),
          createBaseVNode("li", null, [
            _hoisted_371,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Pin")
              ]),
              _: 1
            }),
            _hoisted_372
          ]),
          createBaseVNode("li", null, [
            _hoisted_373,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("String")
              ]),
              _: 1
            }),
            _hoisted_374
          ]),
          createBaseVNode("li", null, [
            _hoisted_375,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_376
          ]),
          createBaseVNode("li", null, [
            _hoisted_377,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_378
          ])
        ])
      ])
    ]),
    _hoisted_379,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_380,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_381,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Pin")
              ]),
              _: 1
            }),
            createTextVNode(),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [
                createTextVNode("Required")
              ]),
              _: 1
            }),
            _hoisted_382
          ]),
          createBaseVNode("li", null, [
            _hoisted_383,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Pin")
              ]),
              _: 1
            }),
            createTextVNode(),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [
                createTextVNode("Required")
              ]),
              _: 1
            }),
            _hoisted_384
          ]),
          createBaseVNode("li", null, [
            _hoisted_385,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Pin")
              ]),
              _: 1
            }),
            _hoisted_386
          ]),
          createBaseVNode("li", null, [
            _hoisted_387,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Pin")
              ]),
              _: 1
            }),
            _hoisted_388
          ])
        ])
      ])
    ]),
    _hoisted_389,
    _hoisted_390,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_391,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_392,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            createTextVNode(),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [
                createTextVNode("Required")
              ]),
              _: 1
            }),
            _hoisted_393
          ]),
          createBaseVNode("li", null, [
            _hoisted_394,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Object: Boolean")
              ]),
              _: 1
            }),
            _hoisted_395
          ]),
          createBaseVNode("li", null, [
            _hoisted_397,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_398
          ]),
          createBaseVNode("li", null, [
            _hoisted_399,
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _hoisted_400,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("String")
                  ]),
                  _: 1
                }),
                _hoisted_401
              ]),
              createBaseVNode("li", null, [
                _hoisted_402,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Boolean")
                  ]),
                  _: 1
                }),
                _hoisted_403
              ]),
              createBaseVNode("li", null, [
                _hoisted_404,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_405
              ]),
              createBaseVNode("li", null, [
                _hoisted_406,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_407
              ]),
              createBaseVNode("li", null, [
                _hoisted_408,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_409
              ]),
              createBaseVNode("li", null, [
                _hoisted_410,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_411
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _hoisted_412,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("String")
              ]),
              _: 1
            }),
            _hoisted_413
          ]),
          createBaseVNode("li", null, [
            _hoisted_414,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_415
          ]),
          createBaseVNode("li", null, [
            _hoisted_416,
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _hoisted_417,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Boolean")
                  ]),
                  _: 1
                }),
                _hoisted_418
              ]),
              createBaseVNode("li", null, [
                _hoisted_419,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Boolean")
                  ]),
                  _: 1
                }),
                _hoisted_420
              ]),
              createBaseVNode("li", null, [
                _hoisted_421,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_422
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _hoisted_423,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Number")
              ]),
              _: 1
            }),
            _hoisted_424
          ]),
          createBaseVNode("li", null, [
            _hoisted_425,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_426
          ]),
          createBaseVNode("li", null, [
            _hoisted_427,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_428
          ]),
          createBaseVNode("li", null, [
            _hoisted_429,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_430
          ]),
          createBaseVNode("li", null, [
            _hoisted_431,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_432
          ]),
          createBaseVNode("li", null, [
            _hoisted_433,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Number")
              ]),
              _: 1
            }),
            _hoisted_434
          ])
        ])
      ])
    ]),
    _hoisted_435,
    _hoisted_436,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_437,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_438,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Object: Boolean")
              ]),
              _: 1
            }),
            _hoisted_439
          ]),
          createBaseVNode("li", null, [
            _hoisted_441,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Number")
              ]),
              _: 1
            }),
            _hoisted_442
          ]),
          createBaseVNode("li", null, [
            _hoisted_443,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Number")
              ]),
              _: 1
            }),
            _hoisted_444
          ]),
          createBaseVNode("li", null, [
            _hoisted_445,
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _hoisted_446,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("String")
                  ]),
                  _: 1
                }),
                _hoisted_447
              ]),
              createBaseVNode("li", null, [
                _hoisted_448,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Boolean")
                  ]),
                  _: 1
                }),
                _hoisted_449
              ]),
              createBaseVNode("li", null, [
                _hoisted_450,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_451
              ]),
              createBaseVNode("li", null, [
                _hoisted_452,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_453
              ]),
              createBaseVNode("li", null, [
                _hoisted_454,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_455
              ]),
              createBaseVNode("li", null, [
                _hoisted_456,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_457
              ]),
              createBaseVNode("li", null, [
                _hoisted_458,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_459
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _hoisted_460,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("String")
              ]),
              _: 1
            }),
            createTextVNode(),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [
                createTextVNode("Required")
              ]),
              _: 1
            }),
            _hoisted_461
          ]),
          createBaseVNode("li", null, [
            _hoisted_462,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_463
          ]),
          createBaseVNode("li", null, [
            _hoisted_464,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Object")
              ]),
              _: 1
            }),
            createTextVNode(),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [
                createTextVNode("Required")
              ]),
              _: 1
            }),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("List of LED configuration dictionaries. Each dictionary contains: "),
                createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    _hoisted_465,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Number")
                      ]),
                      _: 1
                    }),
                    createTextVNode(),
                    createVNode(_component_Badge, null, {
                      default: withCtx(() => [
                        createTextVNode("Required")
                      ]),
                      _: 1
                    }),
                    _hoisted_466
                  ]),
                  createBaseVNode("li", null, [
                    _hoisted_467,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Number")
                      ]),
                      _: 1
                    }),
                    createTextVNode(),
                    createVNode(_component_Badge, null, {
                      default: withCtx(() => [
                        createTextVNode("Required")
                      ]),
                      _: 1
                    }),
                    _hoisted_468
                  ]),
                  createBaseVNode("li", null, [
                    _hoisted_469,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Number")
                      ]),
                      _: 1
                    }),
                    createTextVNode(),
                    createVNode(_component_Badge, null, {
                      default: withCtx(() => [
                        createTextVNode("Required")
                      ]),
                      _: 1
                    }),
                    _hoisted_470
                  ]),
                  createBaseVNode("li", null, [
                    _hoisted_471,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Matrix")
                      ]),
                      _: 1
                    }),
                    _hoisted_472
                  ]),
                  _hoisted_473
                ])
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _hoisted_474,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_475
          ]),
          createBaseVNode("li", null, [
            _hoisted_476,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_477
          ]),
          createBaseVNode("li", null, [
            _hoisted_478,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_479
          ]),
          createBaseVNode("li", null, [
            _hoisted_480,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_481
          ]),
          createBaseVNode("li", null, [
            _hoisted_482,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_483
          ]),
          createBaseVNode("li", null, [
            _hoisted_484,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_485
          ]),
          createBaseVNode("li", null, [
            _hoisted_486,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_487
          ]),
          createBaseVNode("li", null, [
            _hoisted_488,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Number")
              ]),
              _: 1
            }),
            _hoisted_489
          ]),
          createBaseVNode("li", null, [
            _hoisted_490,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_491
          ]),
          createBaseVNode("li", null, [
            _hoisted_492,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_493
          ])
        ])
      ])
    ]),
    _hoisted_494,
    _hoisted_495,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_496,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_497,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_498
          ]),
          createBaseVNode("li", null, [
            _hoisted_499,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_500
          ]),
          createBaseVNode("li", null, [
            _hoisted_501,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Array: Matrix")
              ]),
              _: 1
            }),
            _hoisted_502
          ]),
          createBaseVNode("li", null, [
            _hoisted_503,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_504
          ])
        ])
      ])
    ]),
    _hoisted_505,
    _hoisted_506,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_507,
        createBaseVNode("ul", null, [
          _hoisted_508,
          createBaseVNode("li", null, [
            _hoisted_510,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_511
          ]),
          _hoisted_512,
          createBaseVNode("li", null, [
            _hoisted_513,
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _hoisted_514,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Pin")
                  ]),
                  _: 1
                }),
                _hoisted_515
              ]),
              createBaseVNode("li", null, [
                _hoisted_516,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Array: Pin")
                  ]),
                  _: 1
                }),
                _hoisted_517
              ])
            ])
          ]),
          _hoisted_518,
          createBaseVNode("li", null, [
            _hoisted_519,
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _hoisted_520,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("String")
                  ]),
                  _: 1
                }),
                _hoisted_521
              ]),
              createBaseVNode("li", null, [
                _hoisted_522,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Pin")
                  ]),
                  _: 1
                }),
                _hoisted_523
              ]),
              createBaseVNode("li", null, [
                _hoisted_524,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_525
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _hoisted_526,
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _hoisted_527,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("String")
                  ]),
                  _: 1
                }),
                _hoisted_528
              ]),
              createBaseVNode("li", null, [
                _hoisted_529,
                createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    _hoisted_530,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Boolean")
                      ]),
                      _: 1
                    }),
                    _hoisted_531
                  ]),
                  createBaseVNode("li", null, [
                    _hoisted_532,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Boolean")
                      ]),
                      _: 1
                    }),
                    _hoisted_533
                  ]),
                  createBaseVNode("li", null, [
                    _hoisted_534,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Boolean")
                      ]),
                      _: 1
                    }),
                    _hoisted_535
                  ]),
                  createBaseVNode("li", null, [
                    _hoisted_536,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Boolean")
                      ]),
                      _: 1
                    }),
                    _hoisted_537
                  ]),
                  createBaseVNode("li", null, [
                    _hoisted_538,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Boolean")
                      ]),
                      _: 1
                    }),
                    _hoisted_539
                  ]),
                  createBaseVNode("li", null, [
                    _hoisted_540,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Boolean")
                      ]),
                      _: 1
                    }),
                    _hoisted_541
                  ]),
                  createBaseVNode("li", null, [
                    _hoisted_542,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Boolean")
                      ]),
                      _: 1
                    }),
                    _hoisted_543
                  ]),
                  createBaseVNode("li", null, [
                    _hoisted_544,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Boolean")
                      ]),
                      _: 1
                    }),
                    _hoisted_545
                  ]),
                  createBaseVNode("li", null, [
                    _hoisted_546,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Boolean")
                      ]),
                      _: 1
                    }),
                    _hoisted_547
                  ]),
                  createBaseVNode("li", null, [
                    _hoisted_548,
                    createTextVNode(),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [
                        createTextVNode("Boolean")
                      ]),
                      _: 1
                    }),
                    _hoisted_549
                  ])
                ])
              ]),
              createBaseVNode("li", null, [
                _hoisted_550,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Boolean")
                  ]),
                  _: 1
                }),
                _hoisted_551
              ]),
              createBaseVNode("li", null, [
                _hoisted_552,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_553
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _hoisted_554,
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _hoisted_555,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Boolean")
                  ]),
                  _: 1
                }),
                _hoisted_556
              ]),
              createBaseVNode("li", null, [
                _hoisted_557,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_558
              ]),
              createBaseVNode("li", null, [
                _hoisted_559,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Number")
                  ]),
                  _: 1
                }),
                _hoisted_560
              ])
            ])
          ])
        ])
      ])
    ]),
    _hoisted_561,
    _hoisted_562,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_563,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_564,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_565
          ]),
          createBaseVNode("li", null, [
            _hoisted_566,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("String")
              ]),
              _: 1
            }),
            _hoisted_567
          ])
        ])
      ])
    ]),
    _hoisted_568,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_569,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_570,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("String")
              ]),
              _: 1
            }),
            createTextVNode(),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [
                createTextVNode("Required")
              ]),
              _: 1
            }),
            _hoisted_571
          ]),
          createBaseVNode("li", null, [
            _hoisted_572,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("String")
              ]),
              _: 1
            }),
            createTextVNode(),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [
                createTextVNode("Required")
              ]),
              _: 1
            }),
            _hoisted_573
          ]),
          createBaseVNode("li", null, [
            _hoisted_574,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("String")
              ]),
              _: 1
            }),
            createTextVNode(),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [
                createTextVNode("Required")
              ]),
              _: 1
            }),
            _hoisted_575
          ]),
          createBaseVNode("li", null, [
            _hoisted_576,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_577
          ]),
          createBaseVNode("li", null, [
            _hoisted_578,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_579
          ]),
          createBaseVNode("li", null, [
            _hoisted_580,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_581
          ]),
          createBaseVNode("li", null, [
            _hoisted_582,
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _hoisted_583,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Boolean")
                  ]),
                  _: 1
                }),
                _hoisted_584
              ]),
              createBaseVNode("li", null, [
                _hoisted_585,
                createTextVNode(),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [
                    createTextVNode("Boolean")
                  ]),
                  _: 1
                }),
                _hoisted_586
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _hoisted_587,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_588
          ]),
          createBaseVNode("li", null, [
            _hoisted_589,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_590
          ])
        ])
      ])
    ]),
    _hoisted_591,
    _hoisted_592,
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _hoisted_593,
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _hoisted_594,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("String")
              ]),
              _: 1
            }),
            _hoisted_595
          ]),
          createBaseVNode("li", null, [
            _hoisted_596,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Pin")
              ]),
              _: 1
            }),
            createTextVNode(),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [
                createTextVNode("Required")
              ]),
              _: 1
            }),
            _hoisted_597
          ]),
          createBaseVNode("li", null, [
            _hoisted_598,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("String")
              ]),
              _: 1
            }),
            _hoisted_599
          ]),
          createBaseVNode("li", null, [
            _hoisted_600,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Number")
              ]),
              _: 1
            }),
            _hoisted_601
          ]),
          createBaseVNode("li", null, [
            _hoisted_602,
            createTextVNode(),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [
                createTextVNode("Boolean")
              ]),
              _: 1
            }),
            _hoisted_603
          ])
        ])
      ])
    ])
  ]);
}
const reference_info_json = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  reference_info_json as default
};
