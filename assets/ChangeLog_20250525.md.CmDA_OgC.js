import { _ as _export_sfc, c as createElementBlock, I as createVNode, w as withCtx, a8 as createStaticVNode, D as resolveComponent, o as openBlock, l as createBaseVNode, a as createTextVNode } from "./chunks/framework.Cauyuiy8.js";
const __pageData = JSON.parse('{"title":"QMK Breaking Changes - 2025 May 25 Changelog","description":"","frontmatter":{},"headers":[],"relativePath":"ChangeLog/20250525.md","filePath":"ChangeLog/20250525.md","lastUpdated":null}');
const _sfc_main = { name: "ChangeLog/20250525.md" };
const _hoisted_1 = /* @__PURE__ */ createStaticVNode('<h1 id="qmk-breaking-changes-2025-may-25-changelog" tabindex="-1">QMK Breaking Changes - 2025 May 25 Changelog <a class="header-anchor" href="#qmk-breaking-changes-2025-may-25-changelog" aria-label="Permalink to &quot;QMK Breaking Changes - 2025 May 25 Changelog&quot;">​</a></h1><h2 id="notable-features" tabindex="-1">Notable Features <a class="header-anchor" href="#notable-features" aria-label="Permalink to &quot;Notable Features&quot;">​</a></h2><h3 id="flow-tap-25125" tabindex="-1">Flow Tap (<a href="https://github.com/qmk/qmk_firmware/pull/25125" target="_blank" rel="noreferrer">#25125</a>) <a class="header-anchor" href="#flow-tap-25125" aria-label="Permalink to &quot;Flow Tap ([#25125](https://github.com/qmk/qmk_firmware/pull/25125))&quot;">​</a></h3><p>Adds Flow Tap as a core tap-hold option to disable HRMs during fast typing, aka Global Quick Tap, Require Prior Idle.</p><p>Flow Tap modifies mod-tap MT and layer-tap LT keys such that when pressed within a short timeout of the preceding key, the tapping behavior is triggered. It basically disables the hold behavior during fast typing, creating a &quot;flow of taps.&quot; It also helps to reduce the input lag of tap-hold keys during fast typing, since the tapped behavior is sent immediately.</p><p>See the <a href="./../tap_hold#flow-tap">Flow Tap documentation</a> for more information.</p><h3 id="community-modules-1-1-1-25050-25187" tabindex="-1">Community Modules <code>1.1.1</code> (<a href="https://github.com/qmk/qmk_firmware/pull/25050" target="_blank" rel="noreferrer">#25050</a>, <a href="https://github.com/qmk/qmk_firmware/pull/25187" target="_blank" rel="noreferrer">#25187</a>) <a class="header-anchor" href="#community-modules-1-1-1-25050-25187" aria-label="Permalink to &quot;Community Modules `1.1.1` ([#25050](https://github.com/qmk/qmk_firmware/pull/25050), [#25187](https://github.com/qmk/qmk_firmware/pull/25187))&quot;">​</a></h3><p>Version <code>1.1.1</code> introduces support for module defined RGB matrix effects and indicator callbacks, as well as pointing and layer state callbacks.</p><p>See the <a href="./../features/community_modules">Community Modules documentation</a> for more information, including the full list of available hooks.</p><h2 id="changes-requiring-user-action" tabindex="-1">Changes Requiring User Action <a class="header-anchor" href="#changes-requiring-user-action" aria-label="Permalink to &quot;Changes Requiring User Action&quot;">​</a></h2><h3 id="updated-keyboard-codebases" tabindex="-1">Updated Keyboard Codebases <a class="header-anchor" href="#updated-keyboard-codebases" aria-label="Permalink to &quot;Updated Keyboard Codebases&quot;">​</a></h3><table><thead><tr><th>Old Keyboard Name</th><th>New Keyboard Name</th></tr></thead><tbody><tr><td>chew</td><td>chew/split</td></tr><tr><td>deemen17/de60fs</td><td>deemen17/de60/r1</td></tr><tr><td>keyten/kt60hs_t</td><td>keyten/kt60hs_t/v1</td></tr><tr><td>plywrks/ply8x</td><td>plywrks/ply8x/solder</td></tr><tr><td>rookiebwoy/late9/rev1</td><td>ivndbt/late9/rev1</td></tr><tr><td>rookiebwoy/neopad/rev1</td><td>ivndbt/neopad/rev1</td></tr></tbody></table><h2 id="deprecation-notices" tabindex="-1">Deprecation Notices <a class="header-anchor" href="#deprecation-notices" aria-label="Permalink to &quot;Deprecation Notices&quot;">​</a></h2><p>In line with the <a href="./../support_deprecation_policy#how-much-advance-notice-will-be-given">notice period</a>, deprecation notices for larger items are listed here.</p><h3 id="deprecation-of-qmk-generate-compilation-database-25237" tabindex="-1">Deprecation of <code>qmk generate-compilation-database</code> (<a href="https://github.com/qmk/qmk_firmware/pull/25237" target="_blank" rel="noreferrer">#25237</a>) <a class="header-anchor" href="#deprecation-of-qmk-generate-compilation-database-25237" aria-label="Permalink to &quot;Deprecation of `qmk generate-compilation-database` ([#25237](https://github.com/qmk/qmk_firmware/pull/25237))&quot;">​</a></h3><p>This command has been deprecated as it cannot take into account configurables such as <a href="/feature_converters">converters</a> or environment variables normally specified on the command line; please use the <code>--compiledb</code> flag with <code>qmk compile</code> instead.</p><h3 id="deprecation-of-usb-force-nkro-force-nkro-25262" tabindex="-1">Deprecation of <code>usb.force_nkro</code>/<code>FORCE_NKRO</code> (<a href="https://github.com/qmk/qmk_firmware/pull/25262" target="_blank" rel="noreferrer">#25262</a>) <a class="header-anchor" href="#deprecation-of-usb-force-nkro-force-nkro-25262" aria-label="Permalink to &quot;Deprecation of `usb.force_nkro`/`FORCE_NKRO` ([#25262](https://github.com/qmk/qmk_firmware/pull/25262))&quot;">​</a></h3><p>Unpicking the assumption that only USB can do NKRO, forcing of NKRO on every boot has been deprecated. As this setting persists, it produces unnecessary user confusion when the various NKRO keycodes (for example <code>NK_TOGG</code>) do not behave as expected.</p><p>The new defaults can be configured in the following ways:</p>', 19);
const _hoisted_20 = /* @__PURE__ */ createBaseVNode("div", { class: "language-json vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }, "json"),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark has-focused-lines vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "{")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '    "host"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": { ")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "default"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": { ")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "nkro"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        } ")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    } ")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
      ])
    ])
  ])
], -1);
const _hoisted_21 = /* @__PURE__ */ createBaseVNode("div", { class: "language-json vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }, "json"),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark has-focused-lines vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "{")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '    "config"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": {")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "host"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": { ")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "default"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": { ")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '                "nkro"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "            } ")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        } ")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
      ])
    ])
  ])
], -1);
const _hoisted_22 = /* @__PURE__ */ createBaseVNode("div", { class: "language-c vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }, "c"),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark has-focused-lines vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#pragma"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " once")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " NKRO_DEFAULT_ON"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " true")
      ])
    ])
  ])
], -1);
const _hoisted_23 = /* @__PURE__ */ createStaticVNode('<p>The deprecated options will be removed in a future breaking changes cycle.</p><h3 id="ctpc-convert-to-proton-c-removal-25111" tabindex="-1"><code>CTPC</code>/<code>CONVERT_TO_PROTON_C</code> removal (<a href="https://github.com/qmk/qmk_firmware/pull/25111" target="_blank" rel="noreferrer">#25111</a>) <a class="header-anchor" href="#ctpc-convert-to-proton-c-removal-25111" aria-label="Permalink to &quot;`CTPC`/`CONVERT_TO_PROTON_C` removal ([#25111](https://github.com/qmk/qmk_firmware/pull/25111))&quot;">​</a></h3><p>Deprecated build options <code>CTPC</code> and <code>CONVERT_TO_PROTON_C</code> have been removed. Users should of these should migrate to <code>CONVERT_TO=proton_c</code>.</p><p>see the <a href="./../feature_converters">Converters Feature</a> documentation for more information.</p><h3 id="default-folder-removal-23281" tabindex="-1"><code>DEFAULT_FOLDER</code> removal (<a href="https://github.com/qmk/qmk_firmware/pull/23281" target="_blank" rel="noreferrer">#23281</a>) <a class="header-anchor" href="#default-folder-removal-23281" aria-label="Permalink to &quot;`DEFAULT_FOLDER` removal ([#23281](https://github.com/qmk/qmk_firmware/pull/23281))&quot;">​</a></h3><p><code>DEFAULT_FOLDER</code> was originally introduced to work around limitations within the build system. Parent folders containing common configuration would create invalid build targets.</p><p>With the introduction of <a href="./20240526#keyboard-json"><code>keyboard.json</code></a> as a configuration file, the build system now has a consistent method to detect build targets. The <code>DEFAULT_FOLDER</code> functionality is now redundant and the intent is for <code>rules.mk</code> to become pure configuration.</p><p>Backwards compatibility of build targets has been maintained where possible.</p><h3 id="converter-pin-compatible-updates-20330" tabindex="-1">Converter <code>Pin Compatible</code> updates (<a href="https://github.com/qmk/qmk_firmware/pull/20330" target="_blank" rel="noreferrer">#20330</a>) <a class="header-anchor" href="#converter-pin-compatible-updates-20330" aria-label="Permalink to &quot;Converter `Pin Compatible` updates ([#20330](https://github.com/qmk/qmk_firmware/pull/20330))&quot;">​</a></h3><p>Converter support will be further limited to only function if a keyboard declares that is is compatible.</p><p>This can be configured in the following ways:</p>', 11);
const _hoisted_34 = /* @__PURE__ */ createBaseVNode("div", { class: "language-json vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }, "json"),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark has-focused-lines vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "{")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '    "development_board"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"promicro"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", ")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
      ])
    ])
  ])
], -1);
const _hoisted_35 = /* @__PURE__ */ createBaseVNode("div", { class: "language-make vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }, "make"),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "PIN_COMPATIBLE = promicro")
      ])
    ])
  ])
], -1);
const _hoisted_36 = /* @__PURE__ */ createStaticVNode('<p>see the <a href="./../feature_converters">Converters Feature</a> documentation for more information.</p><h3 id="deprecation-of-encoder-update-kb-user" tabindex="-1">Deprecation of <code>encoder_update_{kb|user}</code> <a class="header-anchor" href="#deprecation-of-encoder-update-kb-user" aria-label="Permalink to &quot;Deprecation of `encoder_update_{kb|user}`&quot;">​</a></h3><p>These callbacks are now considered end-of-life and will be removed over the next breaking changes cycle, ending August 2025. PRs containing these callbacks will be asked to change to use <a href="/features/encoders#encoder-map">encoder mapping</a>.</p><p><code>ENCODER_MAP_ENABLE</code> will subsequently be changed to &quot;default-on&quot; when encoders are enabled, and future breaking changes cycles will remove this flag entirely.</p><p>To migrate usage of <code>encoder_update_user</code> to encoder map you&#39;ll need to handle all of the following changes in your <code>keymap.c</code>:</p>', 5);
const _hoisted_41 = /* @__PURE__ */ createBaseVNode("p", null, "Define new keycodes:", -1);
const _hoisted_42 = /* @__PURE__ */ createBaseVNode("div", { class: "language-c vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }, "c"),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark has-focused-lines vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "enum"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " {")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    MY_ENCODER_LEFT "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " QK_USER,")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    MY_ENCODER_RIGHT,")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "};")
      ])
    ])
  ])
], -1);
const _hoisted_43 = /* @__PURE__ */ createBaseVNode("p", null, "Add the keycodes to a new encoder map (optionally with transparent layers above, if you want identical functionality of layer-independence):", -1);
const _hoisted_44 = /* @__PURE__ */ createBaseVNode("div", { class: "language-c vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }, "c"),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark has-focused-lines vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#if"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " defined"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "ENCODER_MAP_ENABLE"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ")")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "const"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " uint16_t"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " PROGMEM encoder_map"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "[]"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "[NUM_ENCODERS][NUM_DIRECTIONS] "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " {")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    ["),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "] "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " { "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "ENCODER_CCW_CW"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(MY_ENCODER_LEFT, MY_ENCODER_RIGHT) },")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    ["),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "] "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " { "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "ENCODER_CCW_CW"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(KC_TRNS, KC_TRNS) },")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    ["),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "2"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "] "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " { "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "ENCODER_CCW_CW"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(KC_TRNS, KC_TRNS) },")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    ["),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "3"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "] "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " { "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "ENCODER_CCW_CW"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(KC_TRNS, KC_TRNS) },")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "};")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#endif")
      ])
    ])
  ])
], -1);
const _hoisted_45 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Handle the new keycodes within "),
  /* @__PURE__ */ createBaseVNode("code", null, "process_record_user"),
  /* @__PURE__ */ createTextVNode(", much like any other keycode in your keymap:")
], -1);
const _hoisted_46 = /* @__PURE__ */ createBaseVNode("div", { class: "language-c vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }, "c"),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark has-focused-lines vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " process_record_user"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " keycode"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "keyrecord_t"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " *"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, "record"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "  switch"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " (keycode) {")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    case"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " MY_ENCODER_LEFT:")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "      if"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " (record"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "->"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "event.pressed) {")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // Add the same code you had in your `encoder_update_user` for the left-rotation code")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "      }")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "      return"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " false"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ";"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Skip all further processing of this keycode")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    case"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " MY_ENCODER_RIGHT:")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "      if"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " (record"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "->"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "event.pressed) {")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // Add the same code you had in your `encoder_update_user` for the right-rotation code")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "      }")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "      return"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " false"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ";"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Skip all further processing of this keycode")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "  }")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
      ])
    ])
  ])
], -1);
const _hoisted_47 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Remove your implementation of "),
  /* @__PURE__ */ createBaseVNode("code", null, "encoder_update_user"),
  /* @__PURE__ */ createTextVNode(" from your "),
  /* @__PURE__ */ createBaseVNode("code", null, "keymap.c"),
  /* @__PURE__ */ createTextVNode(".")
], -1);
const _hoisted_48 = /* @__PURE__ */ createStaticVNode('<p>If your board has multiple encoders, each encoder will need its own pair of keycodes defined as per above.</p><h2 id="full-changelist" tabindex="-1">Full changelist <a class="header-anchor" href="#full-changelist" aria-label="Permalink to &quot;Full changelist&quot;">​</a></h2><p>Core:</p><ul><li>Non-volatile memory data repository pattern (<a href="https://github.com/qmk/qmk_firmware/pull/24356" target="_blank" rel="noreferrer">#24356</a>)</li><li>High resolution scrolling (without feature report parsing) (<a href="https://github.com/qmk/qmk_firmware/pull/24423" target="_blank" rel="noreferrer">#24423</a>)</li><li>Implement battery level interface (<a href="https://github.com/qmk/qmk_firmware/pull/24666" target="_blank" rel="noreferrer">#24666</a>)</li><li>get_keycode_string(): function to format keycodes as strings, for more readable debug logging. (<a href="https://github.com/qmk/qmk_firmware/pull/24787" target="_blank" rel="noreferrer">#24787</a>)</li><li>[Cleanup] Handling of optional <code>*.mk</code> files (<a href="https://github.com/qmk/qmk_firmware/pull/24952" target="_blank" rel="noreferrer">#24952</a>)</li><li>Add EOL to non-keyboard files (<a href="https://github.com/qmk/qmk_firmware/pull/24990" target="_blank" rel="noreferrer">#24990</a>)</li><li>use <code>keycode_string</code> in unit tests (<a href="https://github.com/qmk/qmk_firmware/pull/25042" target="_blank" rel="noreferrer">#25042</a>)</li><li>Add additional hooks for Community modules (<a href="https://github.com/qmk/qmk_firmware/pull/25050" target="_blank" rel="noreferrer">#25050</a>)</li><li>Remove <code>CTPC</code>/<code>CONVERT_TO_PROTON_C</code> options (<a href="https://github.com/qmk/qmk_firmware/pull/25111" target="_blank" rel="noreferrer">#25111</a>)</li><li>Flow Tap tap-hold option to disable HRMs during fast typing (aka Global Quick Tap, Require Prior Idle). (<a href="https://github.com/qmk/qmk_firmware/pull/25125" target="_blank" rel="noreferrer">#25125</a>)</li><li>Remove <code>bluefruit_le_read_battery_voltage</code> function (<a href="https://github.com/qmk/qmk_firmware/pull/25129" target="_blank" rel="noreferrer">#25129</a>)</li><li>Avoid duplication in generated community modules <code>rules.mk</code> (<a href="https://github.com/qmk/qmk_firmware/pull/25135" target="_blank" rel="noreferrer">#25135</a>)</li><li>[chore]: move and rename mouse/scroll min/max defines (<a href="https://github.com/qmk/qmk_firmware/pull/25141" target="_blank" rel="noreferrer">#25141</a>)</li><li>Ignore the Layer Lock key in Repeat Key and Caps Word. (<a href="https://github.com/qmk/qmk_firmware/pull/25171" target="_blank" rel="noreferrer">#25171</a>)</li><li>Allow for disabling EEPROM subsystem entirely. (<a href="https://github.com/qmk/qmk_firmware/pull/25173" target="_blank" rel="noreferrer">#25173</a>)</li><li>Implement connection keycode logic (<a href="https://github.com/qmk/qmk_firmware/pull/25176" target="_blank" rel="noreferrer">#25176</a>)</li><li>Align ChibiOS <code>USB_WAIT_FOR_ENUMERATION</code> implementation (<a href="https://github.com/qmk/qmk_firmware/pull/25184" target="_blank" rel="noreferrer">#25184</a>)</li><li>Enable community modules to define LED matrix and RGB matrix effects. (<a href="https://github.com/qmk/qmk_firmware/pull/25187" target="_blank" rel="noreferrer">#25187</a>)</li><li>Bind Bluetooth driver to <code>host_driver_t</code> (<a href="https://github.com/qmk/qmk_firmware/pull/25199" target="_blank" rel="noreferrer">#25199</a>)</li><li>Enhance Flow Tap to work better for rolls over multiple tap-hold keys. (<a href="https://github.com/qmk/qmk_firmware/pull/25200" target="_blank" rel="noreferrer">#25200</a>)</li><li>Remove force disable of NKRO when Bluetooth enabled (<a href="https://github.com/qmk/qmk_firmware/pull/25201" target="_blank" rel="noreferrer">#25201</a>)</li><li>[New Feature/Core] New RGB Matrix Animation &quot;Starlight Smooth&quot; (<a href="https://github.com/qmk/qmk_firmware/pull/25203" target="_blank" rel="noreferrer">#25203</a>)</li><li>Add battery changed callbacks (<a href="https://github.com/qmk/qmk_firmware/pull/25207" target="_blank" rel="noreferrer">#25207</a>)</li><li>Generate versions to keycode headers (<a href="https://github.com/qmk/qmk_firmware/pull/25219" target="_blank" rel="noreferrer">#25219</a>)</li><li>Add raw_hid support to host driver (<a href="https://github.com/qmk/qmk_firmware/pull/25255" target="_blank" rel="noreferrer">#25255</a>)</li><li>Deprecate <code>usb.force_nkro</code>/<code>FORCE_NKRO</code> (<a href="https://github.com/qmk/qmk_firmware/pull/25262" target="_blank" rel="noreferrer">#25262</a>)</li><li>[Chore] use {rgblight,rgb_matrix}_hsv_to_rgb overrides (<a href="https://github.com/qmk/qmk_firmware/pull/25271" target="_blank" rel="noreferrer">#25271</a>)</li><li>Remove outdated <code>nix</code> support due to bit-rot. (<a href="https://github.com/qmk/qmk_firmware/pull/25280" target="_blank" rel="noreferrer">#25280</a>)</li></ul><p>CLI:</p><ul><li>Align to latest CLI dependencies (<a href="https://github.com/qmk/qmk_firmware/pull/24553" target="_blank" rel="noreferrer">#24553</a>)</li><li>Exclude external userspace from lint checking (<a href="https://github.com/qmk/qmk_firmware/pull/24680" target="_blank" rel="noreferrer">#24680</a>)</li><li>[Modules] Provide access to current path in <code>rules.mk</code>. (<a href="https://github.com/qmk/qmk_firmware/pull/25061" target="_blank" rel="noreferrer">#25061</a>)</li><li>Add &quot;license&quot; field to Community Module JSON schema. (<a href="https://github.com/qmk/qmk_firmware/pull/25085" target="_blank" rel="noreferrer">#25085</a>)</li><li>Prompt for converter when creating new keymap (<a href="https://github.com/qmk/qmk_firmware/pull/25116" target="_blank" rel="noreferrer">#25116</a>)</li><li>Extend lint checks to reject duplication of defaults (<a href="https://github.com/qmk/qmk_firmware/pull/25149" target="_blank" rel="noreferrer">#25149</a>)</li><li>Add lint warning for empty url (<a href="https://github.com/qmk/qmk_firmware/pull/25182" target="_blank" rel="noreferrer">#25182</a>)</li><li>Deprecate <code>qmk generate-compilation-database</code>. (<a href="https://github.com/qmk/qmk_firmware/pull/25237" target="_blank" rel="noreferrer">#25237</a>)</li><li>Use relative paths for schemas, instead of $id. Enables VScode validation. (<a href="https://github.com/qmk/qmk_firmware/pull/25251" target="_blank" rel="noreferrer">#25251</a>)</li></ul><p>Submodule updates:</p><ul><li>STM32G0x1 support (<a href="https://github.com/qmk/qmk_firmware/pull/24301" target="_blank" rel="noreferrer">#24301</a>)</li><li>Update develop branch to Pico SDK 1.5.1 (<a href="https://github.com/qmk/qmk_firmware/pull/25178" target="_blank" rel="noreferrer">#25178</a>)</li><li>Add <code>compiler_support.h</code> (<a href="https://github.com/qmk/qmk_firmware/pull/25274" target="_blank" rel="noreferrer">#25274</a>)</li></ul><p>Keyboards:</p><ul><li>add 75_(ansi|iso) Community Layouts to mechlovin/olly/octagon (<a href="https://github.com/qmk/qmk_firmware/pull/22459" target="_blank" rel="noreferrer">#22459</a>)</li><li>Add the plywrks ply8x hotswap variant. (<a href="https://github.com/qmk/qmk_firmware/pull/23558" target="_blank" rel="noreferrer">#23558</a>)</li><li>Add Community Layout support to daskeyboard4 (<a href="https://github.com/qmk/qmk_firmware/pull/23884" target="_blank" rel="noreferrer">#23884</a>)</li><li>New standard layout for Savage65 (65_ansi_blocker_tsangan_split_bs) (<a href="https://github.com/qmk/qmk_firmware/pull/24690" target="_blank" rel="noreferrer">#24690</a>)</li><li>Add Icebreaker keyboard (<a href="https://github.com/qmk/qmk_firmware/pull/24723" target="_blank" rel="noreferrer">#24723</a>)</li><li>Update Tractyl Manuform and add F405 (weact) variant (<a href="https://github.com/qmk/qmk_firmware/pull/24764" target="_blank" rel="noreferrer">#24764</a>)</li><li>Chew folders (<a href="https://github.com/qmk/qmk_firmware/pull/24785" target="_blank" rel="noreferrer">#24785</a>)</li><li>modelh: add prerequisites for via support (<a href="https://github.com/qmk/qmk_firmware/pull/24932" target="_blank" rel="noreferrer">#24932</a>)</li><li>Only configure <code>STM32_HSECLK</code> within <code>board.h</code> (<a href="https://github.com/qmk/qmk_firmware/pull/25001" target="_blank" rel="noreferrer">#25001</a>)</li><li>Allow LVGL onekey keymap to be able compile for other board (<a href="https://github.com/qmk/qmk_firmware/pull/25005" target="_blank" rel="noreferrer">#25005</a>)</li><li>Remove Sofle <code>rgb_default</code> keymap &amp; tidy readme&#39;s (<a href="https://github.com/qmk/qmk_firmware/pull/25010" target="_blank" rel="noreferrer">#25010</a>)</li><li>Migrate remaining <code>split.soft_serial_pin</code> to <code>split.serial.pin</code> (<a href="https://github.com/qmk/qmk_firmware/pull/25046" target="_blank" rel="noreferrer">#25046</a>)</li><li>Update keymap for keycult 1800 (<a href="https://github.com/qmk/qmk_firmware/pull/25070" target="_blank" rel="noreferrer">#25070</a>)</li><li>Add kt60HS-T v2 PCB (<a href="https://github.com/qmk/qmk_firmware/pull/25080" target="_blank" rel="noreferrer">#25080</a>)</li><li>Refactor Deemen17 Works DE60 (<a href="https://github.com/qmk/qmk_firmware/pull/25088" target="_blank" rel="noreferrer">#25088</a>)</li><li>Rookiebwoy to ivndbt (<a href="https://github.com/qmk/qmk_firmware/pull/25142" target="_blank" rel="noreferrer">#25142</a>)</li><li>Remove duplication of RGB Matrix defaults (<a href="https://github.com/qmk/qmk_firmware/pull/25146" target="_blank" rel="noreferrer">#25146</a>)</li><li>ymdk/id75/rp2040 (<a href="https://github.com/qmk/qmk_firmware/pull/25157" target="_blank" rel="noreferrer">#25157</a>)</li><li>Remove duplication of RGBLight defaults (<a href="https://github.com/qmk/qmk_firmware/pull/25169" target="_blank" rel="noreferrer">#25169</a>)</li><li>Remove empty <code>url</code> fields (<a href="https://github.com/qmk/qmk_firmware/pull/25181" target="_blank" rel="noreferrer">#25181</a>)</li><li>Remove more duplication of defaults (<a href="https://github.com/qmk/qmk_firmware/pull/25189" target="_blank" rel="noreferrer">#25189</a>)</li><li>Remove <code>&quot;console&quot;:false</code> from keyboards (<a href="https://github.com/qmk/qmk_firmware/pull/25190" target="_blank" rel="noreferrer">#25190</a>)</li><li>Remove <code>&quot;command&quot;:false</code> from keyboards (<a href="https://github.com/qmk/qmk_firmware/pull/25193" target="_blank" rel="noreferrer">#25193</a>)</li><li>Remove redundant keyboard headers (<a href="https://github.com/qmk/qmk_firmware/pull/25208" target="_blank" rel="noreferrer">#25208</a>)</li><li>Add debounce to duplicated defaults check (<a href="https://github.com/qmk/qmk_firmware/pull/25246" target="_blank" rel="noreferrer">#25246</a>)</li><li>Remove duplicate of SPI default config from keyboards (<a href="https://github.com/qmk/qmk_firmware/pull/25266" target="_blank" rel="noreferrer">#25266</a>)</li><li>Resolve miscellaneous keyboard lint warnings (<a href="https://github.com/qmk/qmk_firmware/pull/25268" target="_blank" rel="noreferrer">#25268</a>)</li><li>Configure boards to use development_board - 0-9 (<a href="https://github.com/qmk/qmk_firmware/pull/25287" target="_blank" rel="noreferrer">#25287</a>)</li><li>Configure boards to use development_board - UVWXYZ (<a href="https://github.com/qmk/qmk_firmware/pull/25288" target="_blank" rel="noreferrer">#25288</a>)</li><li>Configure boards to use development_board - S (<a href="https://github.com/qmk/qmk_firmware/pull/25293" target="_blank" rel="noreferrer">#25293</a>)</li><li>Configure boards to use development_board - T (<a href="https://github.com/qmk/qmk_firmware/pull/25294" target="_blank" rel="noreferrer">#25294</a>)</li></ul><p>Keyboard fixes:</p><ul><li>Fix <code>boardsource/beiwagon</code> RGB Matrix coordinates (<a href="https://github.com/qmk/qmk_firmware/pull/25018" target="_blank" rel="noreferrer">#25018</a>)</li><li>amptrics/0422 - Prevent OOB in <code>update_leds_for_layer</code> (<a href="https://github.com/qmk/qmk_firmware/pull/25209" target="_blank" rel="noreferrer">#25209</a>)</li><li>salicylic_acid3/getta25 - Fix oled keymap (<a href="https://github.com/qmk/qmk_firmware/pull/25295" target="_blank" rel="noreferrer">#25295</a>)</li></ul><p>Others:</p><ul><li>Require &#39;x&#39;/&#39;y&#39; properties for LED/RGB Matrix layout (<a href="https://github.com/qmk/qmk_firmware/pull/24997" target="_blank" rel="noreferrer">#24997</a>)</li><li>Align <code>new-keyboard</code> template to current standards (<a href="https://github.com/qmk/qmk_firmware/pull/25191" target="_blank" rel="noreferrer">#25191</a>)</li></ul><p>Bugs:</p><ul><li>Fix OS_DETECTION_KEYBOARD_RESET (<a href="https://github.com/qmk/qmk_firmware/pull/25015" target="_blank" rel="noreferrer">#25015</a>)</li><li>Fix outdated GPIO control function usage (<a href="https://github.com/qmk/qmk_firmware/pull/25060" target="_blank" rel="noreferrer">#25060</a>)</li><li>Cater for use of <code>__errno_r()</code> in ChibiOS syscalls.c with newer picolibc revisions (<a href="https://github.com/qmk/qmk_firmware/pull/25121" target="_blank" rel="noreferrer">#25121</a>)</li><li>Fixup eeconfig lighting reset. (<a href="https://github.com/qmk/qmk_firmware/pull/25166" target="_blank" rel="noreferrer">#25166</a>)</li><li>Fix for Flow Tap: fix handling of distinct taps and timer updates. (<a href="https://github.com/qmk/qmk_firmware/pull/25175" target="_blank" rel="noreferrer">#25175</a>)</li><li>Minimise force-included files (<a href="https://github.com/qmk/qmk_firmware/pull/25194" target="_blank" rel="noreferrer">#25194</a>)</li><li>Ensure <code>qmk_userspace_paths</code> maintains detected order (<a href="https://github.com/qmk/qmk_firmware/pull/25204" target="_blank" rel="noreferrer">#25204</a>)</li><li>Resolve alias for <code>qmk new-keymap</code> keyboard prompts (<a href="https://github.com/qmk/qmk_firmware/pull/25210" target="_blank" rel="noreferrer">#25210</a>)</li><li>gcc15 AVR compilation fixes (<a href="https://github.com/qmk/qmk_firmware/pull/25238" target="_blank" rel="noreferrer">#25238</a>)</li><li>Fix typos introduced by PR #25050 (<a href="https://github.com/qmk/qmk_firmware/pull/25250" target="_blank" rel="noreferrer">#25250</a>)</li><li>Fix Wear Leveling compilation (<a href="https://github.com/qmk/qmk_firmware/pull/25254" target="_blank" rel="noreferrer">#25254</a>)</li><li>Remove more USB only branches from NKRO handling (<a href="https://github.com/qmk/qmk_firmware/pull/25263" target="_blank" rel="noreferrer">#25263</a>)</li><li>[Fix] lib8tion: enable fixed scale8 and blend functions (<a href="https://github.com/qmk/qmk_firmware/pull/25272" target="_blank" rel="noreferrer">#25272</a>)</li><li>Fix tap_hold code blocks (<a href="https://github.com/qmk/qmk_firmware/pull/25298" target="_blank" rel="noreferrer">#25298</a>)</li></ul>', 16);
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  const _component_PluginTabsTab = resolveComponent("PluginTabsTab");
  const _component_PluginTabs = resolveComponent("PluginTabs");
  return openBlock(), createElementBlock("div", null, [
    _hoisted_1,
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "keyboard.json" }, {
          default: withCtx(() => [
            _hoisted_20
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "keymap.json" }, {
          default: withCtx(() => [
            _hoisted_21
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "config.h" }, {
          default: withCtx(() => [
            _hoisted_22
          ]),
          _: 1
        })
      ]),
      _: 1
    }),
    _hoisted_23,
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "keyboard.json" }, {
          default: withCtx(() => [
            _hoisted_34
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "rules.mk" }, {
          default: withCtx(() => [
            _hoisted_35
          ]),
          _: 1
        })
      ]),
      _: 1
    }),
    _hoisted_36,
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "1. Add keycode definitions" }, {
          default: withCtx(() => [
            _hoisted_41,
            _hoisted_42
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "2. Add encoder mapping" }, {
          default: withCtx(() => [
            _hoisted_43,
            _hoisted_44
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "3. Add keycode processing" }, {
          default: withCtx(() => [
            _hoisted_45,
            _hoisted_46
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "4. Remove old code" }, {
          default: withCtx(() => [
            _hoisted_47
          ]),
          _: 1
        })
      ]),
      _: 1
    }),
    _hoisted_48
  ]);
}
const _20250525 = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  _20250525 as default
};
