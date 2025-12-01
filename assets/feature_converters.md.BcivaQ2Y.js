import { _ as _export_sfc, c as createElementBlock, I as createVNode, w as withCtx, a8 as createStaticVNode, D as resolveComponent, o as openBlock, l as createBaseVNode, a as createTextVNode } from "./chunks/framework.Cauyuiy8.js";
const _imports_0 = "/pin_compatible_promicro.svg";
const _imports_1 = "/pin_compatible_elite_c.svg";
const __pageData = JSON.parse('{"title":"Converters","description":"","frontmatter":{},"headers":[],"relativePath":"feature_converters.md","filePath":"feature_converters.md","lastUpdated":null}');
const _sfc_main = { name: "feature_converters.md" };
const _hoisted_1 = /* @__PURE__ */ createStaticVNode('<h1 id="converters" tabindex="-1">Converters <a class="header-anchor" href="#converters" aria-label="Permalink to &quot;Converters&quot;">​</a></h1><p>This page documents the automated process for converting keyboards to use drop-in replacement controllers. This process is designed to be easy to use and can be completed in a few simple steps.</p><p>You can generate the firmware by appending <code>-e CONVERT_TO=&lt;target&gt;</code> to your compile/flash command. For example:</p><div class="language-sh vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">sh</span><pre class="shiki shiki-themes github-light github-dark vp-code"><code><span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">qmk</span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;"> flash</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> -c</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> -kb</span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;"> keebio/bdn9/rev1</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> -km</span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;"> default</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> -e</span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;"> CONVERT_TO=proton_c</span></span></code></pre></div><p>You can also configure this within your <a href="#keymap">keymap</a> to accomplish the same thing.</p><div class="tip custom-block"><p class="custom-block-title">TIP</p><p>If you get build errors, you will need to convert the keyboard&#39;s code to be <a href="#keyboard-req">compatible</a> with the converter feature, or provide additional <a href="#keymap-add">keymap</a> configuration.</p></div><h2 id="supported-converters" tabindex="-1">Supported Converters <a class="header-anchor" href="#supported-converters" aria-label="Permalink to &quot;Supported Converters&quot;">​</a></h2><p>Each converter category is broken down by its declared <code>pin compatibility</code>. This ensures that only valid combinations are attempted.</p><p>The following converters are available at this time:</p><table><thead><tr><th>From</th><th>To</th></tr></thead><tbody><tr><td><code>promicro</code></td><td><code>proton_c</code></td></tr><tr><td><code>promicro</code></td><td><code>kb2040</code></td></tr><tr><td><code>promicro</code></td><td><code>sparkfun_pm2040</code></td></tr><tr><td><code>promicro</code></td><td><code>blok</code></td></tr><tr><td><code>promicro</code></td><td><code>bit_c_pro</code></td></tr><tr><td><code>promicro</code></td><td><code>stemcell</code></td></tr><tr><td><code>promicro</code></td><td><code>bonsai_c4</code></td></tr><tr><td><code>promicro</code></td><td><code>rp2040_ce</code></td></tr><tr><td><code>promicro</code></td><td><code>elite_pi</code></td></tr><tr><td><code>promicro</code></td><td><code>helios</code></td></tr><tr><td><code>promicro</code></td><td><code>liatris</code></td></tr><tr><td><code>promicro</code></td><td><code>imera</code></td></tr><tr><td><code>promicro</code></td><td><code>michi</code></td></tr><tr><td><code>promicro</code></td><td><code>svlinky</code></td></tr><tr><td><code>elite_c</code></td><td><code>stemcell</code></td></tr><tr><td><code>elite_c</code></td><td><code>rp2040_ce</code></td></tr><tr><td><code>elite_c</code></td><td><code>elite_pi</code></td></tr><tr><td><code>elite_c</code></td><td><code>helios</code></td></tr><tr><td><code>elite_c</code></td><td><code>liatris</code></td></tr></tbody></table><h2 id="configuration" tabindex="-1">Configuration <a class="header-anchor" href="#configuration" aria-label="Permalink to &quot;Configuration&quot;">​</a></h2><p>Configuring a converter to use can be done by adding one of the following lines to your keymaps&#39;s configuration:</p>', 12);
const _hoisted_13 = /* @__PURE__ */ createBaseVNode("div", { class: "language-json vp-adaptive-theme" }, [
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
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '    "version"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '    "keyboard"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"keebio/bdn9/rev1"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '    "keymap"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"keebio_bdn9_rev1_layout_2025-05-20"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '    "converter"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"proton_c"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", ")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '    "layout"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"LAYOUT"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
      ])
    ])
  ])
], -1);
const _hoisted_14 = /* @__PURE__ */ createBaseVNode("div", { class: "language-makefile vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }, "makefile"),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "CONVERT_TO = proton_c")
      ])
    ])
  ])
], -1);
const _hoisted_15 = /* @__PURE__ */ createStaticVNode('<div class="tip custom-block"><p class="custom-block-title">TIP</p><p>If you get build errors, you will need to convert the keyboard&#39;s code to be <a href="#keyboard-req">compatible</a> with the converter feature, or provide additional <a href="#keymap-add">keymap</a> configuration.</p></div><h2 id="pro-micro-converters" tabindex="-1">Pro Micro Converters <a class="header-anchor" href="#pro-micro-converters" aria-label="Permalink to &quot;Pro Micro Converters&quot;">​</a></h2><p>If a board currently supported by QMK uses a <a href="https://www.sparkfun.com/products/12640" target="_blank" rel="noreferrer">Pro Micro</a> (or compatible board), the supported alternative controllers are:</p><table><thead><tr><th>Device</th><th>Target</th><th>CLI Argument</th><th><code>rules.mk</code></th><th>Condition</th></tr></thead><tbody><tr><td><a href="https://qmk.fm/proton-c/" target="_blank" rel="noreferrer">Proton C</a></td><td><code>proton_c</code></td><td><code>-e CONVERT_TO=proton_c</code></td><td><code>CONVERT_TO=proton_c</code></td><td><code>#ifdef CONVERT_TO_PROTON_C</code></td></tr><tr><td><a href="https://learn.adafruit.com/adafruit-kb2040" target="_blank" rel="noreferrer">Adafruit KB2040</a></td><td><code>kb2040</code></td><td><code>-e CONVERT_TO=kb2040</code></td><td><code>CONVERT_TO=kb2040</code></td><td><code>#ifdef CONVERT_TO_KB2040</code></td></tr><tr><td><a href="https://www.sparkfun.com/products/18288" target="_blank" rel="noreferrer">SparkFun Pro Micro - RP2040</a></td><td><code>sparkfun_pm2040</code></td><td><code>-e CONVERT_TO=sparkfun_pm2040</code></td><td><code>CONVERT_TO=sparkfun_pm2040</code></td><td><code>#ifdef CONVERT_TO_SPARKFUN_PM2040</code></td></tr><tr><td><a href="https://boardsource.xyz/store/628b95b494dfa308a6581622" target="_blank" rel="noreferrer">Blok</a></td><td><code>blok</code></td><td><code>-e CONVERT_TO=blok</code></td><td><code>CONVERT_TO=blok</code></td><td><code>#ifdef CONVERT_TO_BLOK</code></td></tr><tr><td><a href="https://nullbits.co/bit-c-pro" target="_blank" rel="noreferrer">Bit-C PRO</a></td><td><code>bit_c_pro</code></td><td><code>-e CONVERT_TO=bit_c_pro</code></td><td><code>CONVERT_TO=bit_c_pro</code></td><td><code>#ifdef CONVERT_TO_BIT_C_PRO</code></td></tr><tr><td><a href="https://github.com/megamind4089/STeMCell" target="_blank" rel="noreferrer">STeMCell</a></td><td><code>stemcell</code></td><td><code>-e CONVERT_TO=stemcell</code></td><td><code>CONVERT_TO=stemcell</code></td><td><code>#ifdef CONVERT_TO_STEMCELL</code></td></tr><tr><td><a href="https://shop.custommk.com/products/bonsai-c4-microcontroller-board" target="_blank" rel="noreferrer">customMK Bonsai C4</a></td><td><code>bonsai_c4</code></td><td><code>-e CONVERT_TO=bonsai_c4</code></td><td><code>CONVERT_TO=bonsai_c4</code></td><td><code>#ifdef CONVERT_TO_BONSAI_C4</code></td></tr><tr><td><a href="#rp2040_ce">RP2040 Community Edition</a></td><td><code>rp2040_ce</code></td><td><code>-e CONVERT_TO=rp2040_ce</code></td><td><code>CONVERT_TO=rp2040_ce</code></td><td><code>#ifdef CONVERT_TO_RP2040_CE</code></td></tr><tr><td><a href="https://keeb.io/products/elite-pi-usb-c-pro-micro-replacement-rp2040" target="_blank" rel="noreferrer">Elite-Pi</a></td><td><code>elite_pi</code></td><td><code>-e CONVERT_TO=elite_pi</code></td><td><code>CONVERT_TO=elite_pi</code></td><td><code>#ifdef CONVERT_TO_ELITE_PI</code></td></tr><tr><td><a href="https://keeb.supply/products/0xcb-helios" target="_blank" rel="noreferrer">0xCB Helios</a></td><td><code>helios</code></td><td><code>-e CONVERT_TO=helios</code></td><td><code>CONVERT_TO=helios</code></td><td><code>#ifdef CONVERT_TO_HELIOS</code></td></tr><tr><td><a href="https://splitkb.com/products/liatris" target="_blank" rel="noreferrer">Liatris</a></td><td><code>liatris</code></td><td><code>-e CONVERT_TO=liatris</code></td><td><code>CONVERT_TO=liatris</code></td><td><code>#ifdef CONVERT_TO_LIATRIS</code></td></tr><tr><td><a href="https://splitkb.com/products/imera" target="_blank" rel="noreferrer">Imera</a></td><td><code>imera</code></td><td><code>-e CONVERT_TO=imera</code></td><td><code>CONVERT_TO=imera</code></td><td><code>#ifdef CONVERT_TO_IMERA</code></td></tr><tr><td><a href="https://github.com/ci-bus/michi-promicro-rp2040" target="_blank" rel="noreferrer">Michi</a></td><td><code>michi</code></td><td><code>-e CONVERT_TO=michi</code></td><td><code>CONVERT_TO=michi</code></td><td><code>#ifdef CONVERT_TO_MICHI</code></td></tr><tr><td><a href="https://github.com/sadekbaroudi/svlinky" target="_blank" rel="noreferrer">Svlinky</a></td><td><code>svlinky</code></td><td><code>-e CONVERT_TO=svlinky</code></td><td><code>CONVERT_TO=svlinky</code></td><td><code>#ifdef CONVERT_TO_SVLINKY</code></td></tr></tbody></table><h3 id="proton_c" tabindex="-1">Proton C <a class="header-anchor" href="#proton_c" aria-label="Permalink to &quot;Proton C {#proton_c}&quot;">​</a></h3><p>The Proton C only has one on-board LED (C13), and by default, the TXLED (D5) is mapped to it. If you want the RXLED (B0) mapped to it instead, add this line to your <code>config.h</code>:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> CONVERT_TO_PROTON_C_RXLED</span></span></code></pre></div><p>The following defaults are based on what has been implemented for STM32 boards.</p><table><thead><tr><th>Feature</th><th>Notes</th></tr></thead><tbody><tr><td><a href="./features/audio">Audio</a></td><td>Enabled</td></tr><tr><td><a href="./features/rgblight">RGB Lighting</a></td><td>Disabled</td></tr><tr><td><a href="./features/backlight">Backlight</a></td><td>Forces <a href="./features/backlight#software-pwm-driver">task driven PWM</a> until ARM can provide automatic configuration</td></tr><tr><td>USB Host (e.g. USB-USB converter)</td><td>Not supported (USB host code is AVR specific and is not currently supported on ARM)</td></tr><tr><td><a href="./features/split_keyboard">Split keyboards</a></td><td>Partial - heavily dependent on enabled features</td></tr></tbody></table><h3 id="kb2040" tabindex="-1">Adafruit KB2040 <a class="header-anchor" href="#kb2040" aria-label="Permalink to &quot;Adafruit KB2040 {#kb2040}&quot;">​</a></h3><p>The following defaults are based on what has been implemented for <a href="./platformdev_rp2040">RP2040</a> boards.</p><table><thead><tr><th>Feature</th><th>Notes</th></tr></thead><tbody><tr><td><a href="./features/rgblight">RGB Lighting</a></td><td>Enabled via <code>PIO</code> vendor driver</td></tr><tr><td><a href="./features/backlight">Backlight</a></td><td>Forces <a href="./features/backlight#software-pwm-driver">task driven PWM</a> until ARM can provide automatic configuration</td></tr><tr><td>USB Host (e.g. USB-USB converter)</td><td>Not supported (USB host code is AVR specific and is not currently supported on ARM)</td></tr><tr><td><a href="./features/split_keyboard">Split keyboards</a></td><td>Partial via <code>PIO</code> vendor driver - heavily dependent on enabled features</td></tr></tbody></table><h3 id="sparkfun_pm2040" tabindex="-1">SparkFun Pro Micro - RP2040, Blok, Bit-C PRO and Michi <a class="header-anchor" href="#sparkfun_pm2040" aria-label="Permalink to &quot;SparkFun Pro Micro - RP2040, Blok, Bit-C PRO and Michi {#sparkfun_pm2040}&quot;">​</a></h3><p>Feature set is identical to <a href="#kb2040">Adafruit KB2040</a>.</p><h3 id="stemcell" tabindex="-1">STeMCell <a class="header-anchor" href="#stemcell" aria-label="Permalink to &quot;STeMCell {#stemcell}&quot;">​</a></h3><p>Feature set currently identical to <a href="#proton_c">Proton C</a>. There are two versions of STeMCell available, with different pinouts:</p><ul><li>v1.0.0</li><li>v2.0.0 (pre-release v1.0.1, v1.0.2) Default official firmware only supports v2.0.0 STeMCell.</li></ul><p>STeMCell has support to swap UART and I2C pins to enable single-wire uart communication in STM chips. The following additional flags has to be used while compiling, based on the pin used for split communication:</p><table><thead><tr><th>Split Pin</th><th>Compile flags</th></tr></thead><tbody><tr><td>D3</td><td>-e STMC_US=yes</td></tr><tr><td>D2</td><td>Not needed</td></tr><tr><td>D1</td><td>-e STMC_IS=yes</td></tr><tr><td>D0</td><td>Not needed</td></tr></tbody></table><h3 id="bonsai_c4" tabindex="-1">Bonsai C4 <a class="header-anchor" href="#bonsai_c4" aria-label="Permalink to &quot;Bonsai C4 {#bonsai_c4}&quot;">​</a></h3><p>The Bonsai C4 only has one on-board LED (B2), and by default, both the Pro Micro TXLED (D5) and RXLED (B0) are mapped to it. If you want only one of them mapped, you can undefine one and redefine it to another pin by adding these line to your <code>config.h</code>:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#undef</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> B0</span></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// If VBUS detection is unused, we can send RXLED to the Vbus detect pin instead</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> B0</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> PAL_LINE</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(GPIOA, </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">9</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">)</span></span></code></pre></div><h3 id="rp2040_ce" tabindex="-1">RP2040 Community Edition - Elite-Pi, Helios, and Liatris <a class="header-anchor" href="#rp2040_ce" aria-label="Permalink to &quot;RP2040 Community Edition - Elite-Pi, Helios, and Liatris {#rp2040_ce}&quot;">​</a></h3><p>Feature set is identical to <a href="#kb2040">Adafruit KB2040</a>. VBUS detection is enabled by default for superior split keyboard support. For more information, refer to the <a href="./platformdev_rp2040#rp2040_ce">Community Edition pinout</a> docs.</p><h3 id="svlinky" tabindex="-1">Svlinky <a class="header-anchor" href="#svlinky" aria-label="Permalink to &quot;Svlinky {#svlinky}&quot;">​</a></h3><p>Feature set is a pro micro equivalent of the <a href="#rp2040_ce">RP2040 Community Edition</a>, except that two of the analog GPIO have been replaced with digital only GPIO. These two were moved to the FPC connector to support the <a href="https://github.com/sadekbaroudi/vik" target="_blank" rel="noreferrer">VIK specification</a>. This means that if you are expecting analog support on all 4 pins as provided on a RP2040 Community Edition pinout, you will not have that. Please see the <a href="https://github.com/sadekbaroudi/svlinky" target="_blank" rel="noreferrer">Svlinky github page</a> for more details.</p><h2 id="elite-c-converters" tabindex="-1">Elite-C Converters <a class="header-anchor" href="#elite-c-converters" aria-label="Permalink to &quot;Elite-C Converters&quot;">​</a></h2><p>If a board currently supported by QMK uses an <a href="https://keeb.io/products/elite-c-low-profile-version-usb-c-pro-micro-replacement-atmega32u4" target="_blank" rel="noreferrer">Elite-C</a>, the supported alternative controllers are:</p><table><thead><tr><th>Device</th><th>Target</th><th>CLI Argument</th><th><code>rules.mk</code></th><th>Condition</th></tr></thead><tbody><tr><td><a href="https://github.com/megamind4089/STeMCell" target="_blank" rel="noreferrer">STeMCell</a></td><td><code>stemcell</code></td><td><code>-e CONVERT_TO=stemcell</code></td><td><code>CONVERT_TO=stemcell</code></td><td><code>#ifdef CONVERT_TO_STEMCELL</code></td></tr><tr><td><a href="#rp2040_ce_elite">RP2040 Community Edition</a></td><td><code>rp2040_ce</code></td><td><code>-e CONVERT_TO=rp2040_ce</code></td><td><code>CONVERT_TO=rp2040_ce</code></td><td><code>#ifdef CONVERT_TO_RP2040_CE</code></td></tr><tr><td><a href="https://keeb.io/products/elite-pi-usb-c-pro-micro-replacement-rp2040" target="_blank" rel="noreferrer">Elite-Pi</a></td><td><code>elite_pi</code></td><td><code>-e CONVERT_TO=elite_pi</code></td><td><code>CONVERT_TO=elite_pi</code></td><td><code>#ifdef CONVERT_TO_ELITE_PI</code></td></tr><tr><td><a href="https://keeb.supply/products/0xcb-helios" target="_blank" rel="noreferrer">0xCB Helios</a></td><td><code>helios</code></td><td><code>-e CONVERT_TO=helios</code></td><td><code>CONVERT_TO=helios</code></td><td><code>#ifdef CONVERT_TO_HELIOS</code></td></tr><tr><td><a href="https://splitkb.com/products/liatris" target="_blank" rel="noreferrer">Liatris</a></td><td><code>liatris</code></td><td><code>-e CONVERT_TO=liatris</code></td><td><code>CONVERT_TO=liatris</code></td><td><code>#ifdef CONVERT_TO_LIATRIS</code></td></tr></tbody></table><h3 id="stemcell_elite" tabindex="-1">STeMCell <a class="header-anchor" href="#stemcell_elite" aria-label="Permalink to &quot;STeMCell {#stemcell_elite}&quot;">​</a></h3><p>Identical to <a href="#stemcell">Pro Micro - STeMCell</a> with support for the additional bottom row of pins.</p><h3 id="rp2040_ce_elite" tabindex="-1">RP2040 Community Edition <a class="header-anchor" href="#rp2040_ce_elite" aria-label="Permalink to &quot;RP2040 Community Edition {#rp2040_ce_elite}&quot;">​</a></h3><p>Identical to <a href="#rp2040_ce">Pro Micro - RP2040 Community Edition</a> with support for the additional bottom row of pins.</p><h2 id="advanced-topics" tabindex="-1">Advanced Topics <a class="header-anchor" href="#advanced-topics" aria-label="Permalink to &quot;Advanced Topics&quot;">​</a></h2><h3 id="keyboard-configuration" tabindex="-1">Keyboard Configuration <a class="header-anchor" href="#keyboard-configuration" aria-label="Permalink to &quot;Keyboard Configuration&quot;">​</a></h3><p>To configure a keyboard to allow the converter feature, add the following line to your keyboard&#39;s <code>.json</code> configuration:</p><div class="language-json vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">json</span><pre class="shiki shiki-themes github-light github-dark has-focused-lines vp-code"><code><span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">{</span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;maintainer&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;QMK&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">,</span></span>\n<span class="line has-focus"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;development_board&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;promicro&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;diode_direction&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;COL2ROW&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">,</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div><p>See the <a href="#pin_compatible">pin compatibility</a> for more information.</p><h4 id="keyboard-req" tabindex="-1">Additional Requirements <a class="header-anchor" href="#keyboard-req" aria-label="Permalink to &quot;Additional Requirements {#keyboard-req}&quot;">​</a></h4><p>Keyboards must use the platform agnostic abstractions provided by QMK. This includes:</p><ul><li>Use of <a href="./drivers/gpio">GPIO Controls</a>.</li></ul><h3 id="keymap-add" tabindex="-1">Additional Keymap Configuration <a class="header-anchor" href="#keymap-add" aria-label="Permalink to &quot;Additional Keymap Configuration {#keymap-add}&quot;">​</a></h3><p>While effort has been made to make converters as compatible as possible, sometimes additional platform specific configuration is required.</p><p>For example, enabling hardware peripherals by adding a keymap level <code>mcuconf.h</code> with something like the following:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#pragma</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> once</span></span>\n<span class="line"></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#include_next</span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;"> &lt;mcuconf.h&gt;</span></span>\n<span class="line"></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#undef</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> RP_SIO_USE_UART0</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> RP_SIO_USE_UART0</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> TRUE</span></span></code></pre></div><p>You can find details on how to configure drivers on their respective pages.</p><p>Alternatively, you may have to disable incompatible features. For example:</p>', 47);
const _hoisted_62 = /* @__PURE__ */ createBaseVNode("div", { class: "language-json vp-adaptive-theme" }, [
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
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '    "version"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '    "keyboard"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"keebio/bdn9/rev1"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '    "keymap"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"keebio_bdn9_rev1_layout_2025-05-20"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '    "converter"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"proton_c"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '    "config"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": { ")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "features"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": { ")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line has-focus" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "audio"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "false")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        }")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '    "layout"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#B31D28", "--shiki-dark": "#FDAEB7", "--shiki-light-font-style": "italic", "--shiki-dark-font-style": "italic" } }, ":"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, ' "LAYOUT"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
      ])
    ])
  ])
], -1);
const _hoisted_63 = /* @__PURE__ */ createBaseVNode("div", { class: "language-makefile vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }, "makefile"),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "AUDIO_ENABLE = no")
      ])
    ])
  ])
], -1);
const _hoisted_64 = /* @__PURE__ */ createStaticVNode('<h3 id="conditional-configuration" tabindex="-1">Conditional Configuration <a class="header-anchor" href="#conditional-configuration" aria-label="Permalink to &quot;Conditional Configuration&quot;">​</a></h3><p>Once a converter is enabled, it exposes the <code>CONVERT_TO_&lt;target_uppercase&gt;</code> flag that you can use in your code with <code>#ifdef</code>s, For example:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#ifdef</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> CONVERT_TO_PROTON_C</span></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">    // Proton C code</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#else</span></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">    // Pro Micro code</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#endif</span></span></code></pre></div><h3 id="pin_compatible" tabindex="-1">Pin Compatibility <a class="header-anchor" href="#pin_compatible" aria-label="Permalink to &quot;Pin Compatibility {#pin_compatible}&quot;">​</a></h3><p>To ensure compatibility, provide validation, and power future workflows, a keyboard should declare its <code>pin compatibility</code>. This ensures that only valid combinations are attempted.</p><div class="tip custom-block"><p class="custom-block-title">Note</p><p>This will already be configured for you if are using the <code>promicro</code> development board preset.</p></div><p>To declare the base interface for conversions, add the following line to your keyboard&#39;s configuration:</p><div class="language-json vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">json</span><pre class="shiki shiki-themes github-light github-dark has-focused-lines vp-code"><code><span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">{</span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;maintainer&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;QMK&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">,</span></span>\n<span class="line has-focus"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;development_board&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;elite_c&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span></span>\n<span class="line has-focus"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;pin_compatible&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;elite_c&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;diode_direction&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;COL2ROW&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">,</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div><p>The above example, configures a keyboard for a default of <code>elite_c</code> while allowing any of the <code>elite_c</code> converter targets.</p><p>The framework then allows mapping of pins from <code>&lt;PIN_COMPATIBLE&gt;</code> to converter <code>&lt;target&gt;</code>.</p><div class="warning custom-block"><p class="custom-block-title">WARNING</p><p>Mapped pins should adhere strictly to the defined interface, any extras present on the hardware should be ignored.</p></div><h4 id="available-pin-compatibility" tabindex="-1">Available Pin Compatibility <a class="header-anchor" href="#available-pin-compatibility" aria-label="Permalink to &quot;Available Pin Compatibility&quot;">​</a></h4>', 12);
const _hoisted_76 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createBaseVNode("img", {
    src: _imports_0,
    alt: "promicro"
  })
], -1);
const _hoisted_77 = /* @__PURE__ */ createBaseVNode("div", { class: "info custom-block" }, [
  /* @__PURE__ */ createBaseVNode("p", { class: "custom-block-title" }, "Notes:"),
  /* @__PURE__ */ createBaseVNode("p", null, "Includes LEDs - these may be mapped to unused/unavailable pins when not present.")
], -1);
const _hoisted_78 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createBaseVNode("img", {
    src: _imports_1,
    alt: "elite_c"
  })
], -1);
const _hoisted_79 = /* @__PURE__ */ createBaseVNode("div", { class: "info custom-block" }, [
  /* @__PURE__ */ createBaseVNode("p", { class: "custom-block-title" }, "Notes:"),
  /* @__PURE__ */ createBaseVNode("p", null, "Includes bottom row pins, no LEDs.")
], -1);
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  const _component_PluginTabsTab = resolveComponent("PluginTabsTab");
  const _component_PluginTabs = resolveComponent("PluginTabs");
  return openBlock(), createElementBlock("div", null, [
    _hoisted_1,
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "keymap.json" }, {
          default: withCtx(() => [
            _hoisted_13
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "rules.mk" }, {
          default: withCtx(() => [
            _hoisted_14
          ]),
          _: 1
        })
      ]),
      _: 1
    }),
    _hoisted_15,
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "keymap.json" }, {
          default: withCtx(() => [
            _hoisted_62
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "rules.mk" }, {
          default: withCtx(() => [
            _hoisted_63
          ]),
          _: 1
        })
      ]),
      _: 1
    }),
    _hoisted_64,
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "promicro" }, {
          default: withCtx(() => [
            _hoisted_76,
            _hoisted_77
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "elite_c" }, {
          default: withCtx(() => [
            _hoisted_78,
            _hoisted_79
          ]),
          _: 1
        })
      ]),
      _: 1
    })
  ]);
}
const feature_converters = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  feature_converters as default
};
