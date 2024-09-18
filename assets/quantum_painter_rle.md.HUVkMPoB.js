import { _ as _export_sfc, c as createElementBlock, o as openBlock, a8 as createStaticVNode } from "./chunks/framework.Clpp4x2N.js";
const __pageData = JSON.parse('{"title":"QMK QGF/QFF RLE data schema","description":"","frontmatter":{},"headers":[],"relativePath":"quantum_painter_rle.md","filePath":"quantum_painter_rle.md"}');
const _sfc_main = { name: "quantum_painter_rle.md" };
const _hoisted_1 = /* @__PURE__ */ createStaticVNode('<h1 id="qmk-qp-rle-schema" tabindex="-1">QMK QGF/QFF RLE data schema <a class="header-anchor" href="#qmk-qp-rle-schema" aria-label="Permalink to &quot;QMK QGF/QFF RLE data schema {#qmk-qp-rle-schema}&quot;">​</a></h1><p>There are two &quot;modes&quot; to the RLE algorithm used in both <a href="./quantum_painter_qgf">QGF</a>/<a href="./quantum_painter_qff">QFF</a>:</p><ul><li>Non-repeating sections of octets, with associated length of up to <code>128</code> octets <ul><li><code>length</code> = <code>marker - 128</code></li><li>A corresponding <code>length</code> number of octets follow directly after the marker octet</li></ul></li><li>Repeated octet with associated length, with associated length of up to <code>128</code><ul><li><code>length</code> = <code>marker</code></li><li>A single octet follows the marker that should be repeated <code>length</code> times.</li></ul></li></ul><p>Decoder pseudocode:</p><div class="language- vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang"></span><pre class="shiki shiki-themes github-light github-dark vp-code"><code><span class="line"><span>while !EOF</span></span>\n<span class="line"><span>    marker = READ_OCTET()</span></span>\n<span class="line"><span></span></span>\n<span class="line"><span>    if marker &gt;= 128</span></span>\n<span class="line"><span>        length = marker - 128</span></span>\n<span class="line"><span>        for i = 0 ... length-1</span></span>\n<span class="line"><span>            c = READ_OCTET()</span></span>\n<span class="line"><span>            WRITE_OCTET(c)</span></span>\n<span class="line"><span></span></span>\n<span class="line"><span>    else</span></span>\n<span class="line"><span>        length = marker</span></span>\n<span class="line"><span>        c = READ_OCTET()</span></span>\n<span class="line"><span>        for i = 0 ... length-1</span></span>\n<span class="line"><span>            WRITE_OCTET(c)</span></span></code></pre></div>', 5);
const _hoisted_6 = [
  _hoisted_1
];
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return openBlock(), createElementBlock("div", null, _hoisted_6);
}
const quantum_painter_rle = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  quantum_painter_rle as default
};
