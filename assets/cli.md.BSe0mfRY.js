import { _ as _export_sfc, o as openBlock, c as createElementBlock, al as createStaticVNode } from "./chunks/framework.8zKZLKO7.js";
const __pageData = JSON.parse('{"title":"QMK CLI","description":"","frontmatter":{},"headers":[],"relativePath":"cli.md","filePath":"cli.md","lastUpdated":null}');
const _sfc_main = { name: "cli.md" };
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return openBlock(), createElementBlock("div", null, [..._cache[0] || (_cache[0] = [
    createStaticVNode('<h1 id="qmk-cli" tabindex="-1">QMK CLI <a class="header-anchor" href="#qmk-cli" aria-label="Permalink to &quot;QMK CLI {#qmk-cli}&quot;">​</a></h1><h2 id="overview" tabindex="-1">Overview <a class="header-anchor" href="#overview" aria-label="Permalink to &quot;Overview {#overview}&quot;">​</a></h2><p>The QMK CLI (command line interface) makes building and working with QMK keyboards easier. We have provided a number of commands to simplify and streamline tasks such as obtaining and compiling the QMK firmware, creating keymaps, and more.</p><h3 id="installation" tabindex="-1">Installation <a class="header-anchor" href="#installation" aria-label="Permalink to &quot;Installation {#installation}&quot;">​</a></h3><p>The recommended way to install the QMK CLI and all necessary dependencies (toolchains, flashing utilities, udev rules on Linux) is to use the bootstrapper script:</p><div class="language- vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang"></span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span>curl -fsSL https://install.qmk.fm | sh</span></span></code></pre></div><p>For more options, run:</p><div class="language- vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang"></span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span>curl -fsSL https://install.qmk.fm | sh -s -- --help</span></span></code></pre></div><p>For detailed setup instructions, see <a href="./newbs_getting_started#set-up-your-environment">Setting Up Your QMK Environment</a>.</p>', 9)
  ])]);
}
const cli = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  cli as default
};
