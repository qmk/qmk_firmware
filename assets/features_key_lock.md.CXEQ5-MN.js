import { _ as _export_sfc, c as createElementBlock, o as openBlock, a8 as createStaticVNode } from "./chunks/framework.Clpp4x2N.js";
const __pageData = JSON.parse('{"title":"Key Lock","description":"","frontmatter":{},"headers":[],"relativePath":"features/key_lock.md","filePath":"features/key_lock.md"}');
const _sfc_main = { name: "features/key_lock.md" };
const _hoisted_1 = /* @__PURE__ */ createStaticVNode('<h1 id="key-lock" tabindex="-1">Key Lock <a class="header-anchor" href="#key-lock" aria-label="Permalink to &quot;Key Lock&quot;">​</a></h1><p>Sometimes you may find yourself needing to hold down a specific key for a long period of time. Key Lock holds down the next key you press for you. Press it again, and it will be released.</p><p>Let&#39;s say you need to type in ALL CAPS for a few sentences. Hit <code>QK_LOCK</code>, and then Shift. Now, Shift will be considered held until you tap it again. You can think of Key Lock as Caps Lock, but supercharged.</p><h2 id="usage" tabindex="-1">Usage <a class="header-anchor" href="#usage" aria-label="Permalink to &quot;Usage&quot;">​</a></h2><p>First, enable Key Lock by setting <code>KEY_LOCK_ENABLE = yes</code> in your <code>rules.mk</code>. Then pick a key in your keymap and assign it the keycode <code>QK_LOCK</code>.</p><h2 id="keycodes" tabindex="-1">Keycodes <a class="header-anchor" href="#keycodes" aria-label="Permalink to &quot;Keycodes&quot;">​</a></h2><table><thead><tr><th>Keycode</th><th>Description</th></tr></thead><tbody><tr><td><code>QK_LOCK</code></td><td>Hold down the next key pressed, until the key is pressed again</td></tr></tbody></table><h2 id="caveats" tabindex="-1">Caveats <a class="header-anchor" href="#caveats" aria-label="Permalink to &quot;Caveats&quot;">​</a></h2><p>Key Lock is only able to hold standard action keys and <a href="./../one_shot_keys">One Shot modifier</a> keys (for example, if you have your Shift defined as <code>OSM(MOD_LSFT)</code>). This does not include any of the QMK special functions (except One Shot modifiers), or shifted versions of keys such as <code>KC_LPRN</code>. If it&#39;s in the <a href="./../keycodes_basic">Basic Keycodes</a> list, it can be held.</p><p>Switching layers will not cancel the Key Lock. The Key Lock can be cancelled by calling the <code>cancel_key_lock()</code> function.</p>', 10);
const _hoisted_11 = [
  _hoisted_1
];
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return openBlock(), createElementBlock("div", null, _hoisted_11);
}
const key_lock = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  key_lock as default
};
