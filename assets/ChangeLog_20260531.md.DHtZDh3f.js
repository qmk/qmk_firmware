import { _ as _export_sfc, C as resolveComponent, o as openBlock, c as createElementBlock, al as createStaticVNode, E as createVNode, w as withCtx, j as createBaseVNode, a as createTextVNode } from "./chunks/framework.8zKZLKO7.js";
const __pageData = JSON.parse('{"title":"QMK Breaking Changes - 2026 May 31 Changelog","description":"","frontmatter":{},"headers":[],"relativePath":"ChangeLog/20260531.md","filePath":"ChangeLog/20260531.md","lastUpdated":null}');
const _sfc_main = { name: "ChangeLog/20260531.md" };
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  const _component_PluginTabsTab = resolveComponent("PluginTabsTab");
  const _component_PluginTabs = resolveComponent("PluginTabs");
  return openBlock(), createElementBlock("div", null, [
    _cache[3] || (_cache[3] = createStaticVNode('<h1 id="qmk-breaking-changes-2026-may-31-changelog" tabindex="-1">QMK Breaking Changes - 2026 May 31 Changelog <a class="header-anchor" href="#qmk-breaking-changes-2026-may-31-changelog" aria-label="Permalink to &quot;QMK Breaking Changes - 2026 May 31 Changelog&quot;">​</a></h1><h2 id="notable-changes" tabindex="-1">Notable Changes <a class="header-anchor" href="#notable-changes" aria-label="Permalink to &quot;Notable Changes {#notable-changes}&quot;">​</a></h2><h2 id="deprecation-notices" tabindex="-1">Deprecation Notices <a class="header-anchor" href="#deprecation-notices" aria-label="Permalink to &quot;Deprecation Notices&quot;">​</a></h2><p>In line with the <a href="./../support_deprecation_policy#how-much-advance-notice-will-be-given">notice period</a>, deprecation notices for larger items are listed here.</p><h3 id="removal-of-deprecated-islefthand-25897" tabindex="-1">Removal of deprecated isLeftHand (<a href="https://github.com/qmk/qmk_firmware/pull/25897" target="_blank" rel="noreferrer">25897</a>) <a class="header-anchor" href="#removal-of-deprecated-islefthand-25897" aria-label="Permalink to &quot;Removal of deprecated isLeftHand ([25897](https://github.com/qmk/qmk_firmware/pull/25897))&quot;">​</a></h3><p>Users must migrate to <code>is_keyboard_left()</code> found in <code>split_util.h</code> instead. For example:</p><div class="language-diff vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">diff</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">oled_rotation_t oled_init_user(oled_rotation_t rotation) {</span></span>\n<span class="line"><span style="--shiki-light:#B31D28;--shiki-dark:#FDAEB7;">-    return isLeftHand ? OLED_ROTATION_180 : OLED_ROTATION_0;</span></span>\n<span class="line"><span style="--shiki-light:#22863A;--shiki-dark:#85E89D;">+    return is_keyboard_left() ? OLED_ROTATION_180 : OLED_ROTATION_0;</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div><h3 id="removal-of-usb-force-nkro-force-nkro-25262" tabindex="-1">Removal of <code>usb.force_nkro</code>/<code>FORCE_NKRO</code> (<a href="https://github.com/qmk/qmk_firmware/pull/25262" target="_blank" rel="noreferrer">#25262</a>) <a class="header-anchor" href="#removal-of-usb-force-nkro-force-nkro-25262" aria-label="Permalink to &quot;Removal of `usb.force_nkro`/`FORCE_NKRO` ([#25262](https://github.com/qmk/qmk_firmware/pull/25262))&quot;">​</a></h3><p>Unpicking the assumption that only USB can do NKRO, forcing of NKRO on every boot has been deprecated. As this setting persists, it produces unnecessary user confusion when the various NKRO keycodes (for example <code>NK_TOGG</code>) do not behave as expected.</p><p>The new defaults can be configured in the following ways:</p>', 10)),
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "keyboard.json" }, {
          default: withCtx(() => [..._cache[0] || (_cache[0] = [
            createBaseVNode("div", { class: "language-json vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "json"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark has-focused-lines vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "{")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line has-focus" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '    "host"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": { ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line has-focus" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "default"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": { ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line has-focus" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "nkro"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line has-focus" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        } ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line has-focus" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    } ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
                  ])
                ])
              ])
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "keymap.json" }, {
          default: withCtx(() => [..._cache[1] || (_cache[1] = [
            createBaseVNode("div", { class: "language-json vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "json"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark has-focused-lines vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "{")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '    "config"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line has-focus" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "host"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": { ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line has-focus" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "default"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": { ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line has-focus" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '                "nkro"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line has-focus" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "            } ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line has-focus" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        } ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
                  ])
                ])
              ])
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "config.h" }, {
          default: withCtx(() => [..._cache[2] || (_cache[2] = [
            createBaseVNode("div", { class: "language-c vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "c"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark has-focused-lines vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#pragma"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " once")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line has-focus" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " NKRO_DEFAULT_ON"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " true")
                  ])
                ])
              ])
            ], -1)
          ])]),
          _: 1
        })
      ]),
      _: 1
    }),
    _cache[4] || (_cache[4] = createStaticVNode('<h2 id="full-changelist" tabindex="-1">Full changelist <a class="header-anchor" href="#full-changelist" aria-label="Permalink to &quot;Full changelist&quot;">​</a></h2><p>Core:</p><ul><li>Remove deprecated <code>isLeftHand</code> (<a href="https://github.com/qmk/qmk_firmware/pull/25897" target="_blank" rel="noreferrer">#25897</a>)</li><li>Either output Unicode or insert in Leader sequence (<a href="https://github.com/qmk/qmk_firmware/pull/25940" target="_blank" rel="noreferrer">#25940</a>)</li><li>Add resolution information to digitizer (<a href="https://github.com/qmk/qmk_firmware/pull/25958" target="_blank" rel="noreferrer">#25958</a>)</li><li>Always generate .map files. (<a href="https://github.com/qmk/qmk_firmware/pull/25961" target="_blank" rel="noreferrer">#25961</a>)</li><li>Add an <code>mcu_reset</code> impl for the kiibohd bootloader. (<a href="https://github.com/qmk/qmk_firmware/pull/25963" target="_blank" rel="noreferrer">#25963</a>)</li><li>VIA v13 (<a href="https://github.com/qmk/qmk_firmware/pull/26001" target="_blank" rel="noreferrer">#26001</a>)</li><li>Added PixArt PMW-3325 mouse sensor driver (<a href="https://github.com/qmk/qmk_firmware/pull/26065" target="_blank" rel="noreferrer">#26065</a>)</li><li>Update WL backing store from 16 to 32-bit for AT32 (<a href="https://github.com/qmk/qmk_firmware/pull/26066" target="_blank" rel="noreferrer">#26066</a>)</li><li>Refactor Pixel Fractal effect (<a href="https://github.com/qmk/qmk_firmware/pull/26071" target="_blank" rel="noreferrer">#26071</a>)</li><li>Minor combo code optimisation (<a href="https://github.com/qmk/qmk_firmware/pull/26073" target="_blank" rel="noreferrer">#26073</a>)</li><li>Options to constrain Speculative Hold: <code>SPECULATIVE_HOLD_ONE_KEY</code> and <code>SPECULATIVE_HOLD_FLOW_TERM</code>. (<a href="https://github.com/qmk/qmk_firmware/pull/26099" target="_blank" rel="noreferrer">#26099</a>)</li><li>Add includes for std::setw (<a href="https://github.com/qmk/qmk_firmware/pull/26153" target="_blank" rel="noreferrer">#26153</a>)</li><li>Bind gtest colour to QMKs &#39;COLOR&#39; variable (<a href="https://github.com/qmk/qmk_firmware/pull/26159" target="_blank" rel="noreferrer">#26159</a>)</li><li>Print correct test names (<a href="https://github.com/qmk/qmk_firmware/pull/26160" target="_blank" rel="noreferrer">#26160</a>)</li><li>Ignore Uninteresting test warnings during test teardown (<a href="https://github.com/qmk/qmk_firmware/pull/26161" target="_blank" rel="noreferrer">#26161</a>)</li><li>Remove FORCE_NKRO (<a href="https://github.com/qmk/qmk_firmware/pull/26206" target="_blank" rel="noreferrer">#26206</a>)</li></ul><p>CLI:</p><ul><li>Update lint to check all keymaps within the repo (<a href="https://github.com/qmk/qmk_firmware/pull/25970" target="_blank" rel="noreferrer">#25970</a>)</li><li>Fail when a duplicate module name is detected (<a href="https://github.com/qmk/qmk_firmware/pull/26238" target="_blank" rel="noreferrer">#26238</a>)</li></ul><p>Submodule updates:</p><ul><li>Update ChibiOS, ChibiOS-Contrib. (<a href="https://github.com/qmk/qmk_firmware/pull/25730" target="_blank" rel="noreferrer">#25730</a>)</li><li>Revert &quot;Update ChibiOS, ChibiOS-Contrib.&quot; (<a href="https://github.com/qmk/qmk_firmware/pull/26074" target="_blank" rel="noreferrer">#26074</a>)</li><li>ChibiOS, ChibiOS-Contrib updates (redux) (<a href="https://github.com/qmk/qmk_firmware/pull/26079" target="_blank" rel="noreferrer">#26079</a>)</li><li>Bump googletest to v1.16.0 (<a href="https://github.com/qmk/qmk_firmware/pull/26154" target="_blank" rel="noreferrer">#26154</a>)</li></ul><p>Keyboards:</p><ul><li>Require &quot;url&quot; field to not be empty (<a href="https://github.com/qmk/qmk_firmware/pull/25152" target="_blank" rel="noreferrer">#25152</a>)</li><li>Add nomis/rpi_pico_25x1 macropad (<a href="https://github.com/qmk/qmk_firmware/pull/25346" target="_blank" rel="noreferrer">#25346</a>)</li><li>Remove override of QK_{LED,RGB}_MATRIX_TOGGLE keycode (<a href="https://github.com/qmk/qmk_firmware/pull/25672" target="_blank" rel="noreferrer">#25672</a>)</li><li>Add reverse layout to SouthPad v2 (<a href="https://github.com/qmk/qmk_firmware/pull/25707" target="_blank" rel="noreferrer">#25707</a>)</li><li>Adding Handwired Bouvet Macropad (<a href="https://github.com/qmk/qmk_firmware/pull/26040" target="_blank" rel="noreferrer">#26040</a>)</li><li>Remove blockader user keymap (<a href="https://github.com/qmk/qmk_firmware/pull/26075" target="_blank" rel="noreferrer">#26075</a>)</li><li>Remove deprecated audio pin defines (<a href="https://github.com/qmk/qmk_firmware/pull/26111" target="_blank" rel="noreferrer">#26111</a>)</li><li>Remove <code>OLED_DISPLAY_128X32</code> config (<a href="https://github.com/qmk/qmk_firmware/pull/26190" target="_blank" rel="noreferrer">#26190</a>)</li><li>Migrate SPLIT_OLED_ENABLE (<a href="https://github.com/qmk/qmk_firmware/pull/26194" target="_blank" rel="noreferrer">#26194</a>)</li><li>Add API version assertion for split_data_sync module (<a href="https://github.com/qmk/qmk_firmware/pull/26237" target="_blank" rel="noreferrer">#26237</a>)</li></ul><p>Others:</p><ul><li>Bump vitepress to 1.6.4 (<a href="https://github.com/qmk/qmk_firmware/pull/26067" target="_blank" rel="noreferrer">#26067</a>)</li><li>Add usage clarifications to docs/features/unicode.md (<a href="https://github.com/qmk/qmk_firmware/pull/26156" target="_blank" rel="noreferrer">#26156</a>)</li></ul><p>Bugs:</p><ul><li>Fix <code>USER_PRINT</code> stripping out <code>uprintf</code> (<a href="https://github.com/qmk/qmk_firmware/pull/25919" target="_blank" rel="noreferrer">#25919</a>)</li><li>Fix possible repeat key infinite recursion (<a href="https://github.com/qmk/qmk_firmware/pull/25926" target="_blank" rel="noreferrer">#25926</a>)</li><li>Fix <code>cc-option</code> on arm-none-eabi-gcc (<a href="https://github.com/qmk/qmk_firmware/pull/26114" target="_blank" rel="noreferrer">#26114</a>)</li><li>Fix color diagnostics for arm-none-eabi-gcc (<a href="https://github.com/qmk/qmk_firmware/pull/26115" target="_blank" rel="noreferrer">#26115</a>)</li><li>Mask out active mods when unregistering after retro tapping (<a href="https://github.com/qmk/qmk_firmware/pull/26127" target="_blank" rel="noreferrer">#26127</a>)</li><li>fix <code>make test:all</code> failures seen on macOS Tahoe (<a href="https://github.com/qmk/qmk_firmware/pull/26136" target="_blank" rel="noreferrer">#26136</a>)</li><li>Add workaround for undefined reference to weak function under mingw (<a href="https://github.com/qmk/qmk_firmware/pull/26167" target="_blank" rel="noreferrer">#26167</a>)</li><li>fix(ws2812-pwm): allow WS2812_PWM_TICK_FREQUENCY override (<a href="https://github.com/qmk/qmk_firmware/pull/26186" target="_blank" rel="noreferrer">#26186</a>)</li><li>Clip mouse report values to the logical range from the USB descriptor. (<a href="https://github.com/qmk/qmk_firmware/pull/26195" target="_blank" rel="noreferrer">#26195</a>)</li><li>Align Mouse USB descriptor (<a href="https://github.com/qmk/qmk_firmware/pull/26230" target="_blank" rel="noreferrer">#26230</a>)</li></ul>', 13))
  ]);
}
const _20260531 = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  _20260531 as default
};
