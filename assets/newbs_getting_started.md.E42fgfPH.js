import { _ as _export_sfc, C as resolveComponent, o as openBlock, c as createElementBlock, al as createStaticVNode, E as createVNode, w as withCtx, j as createBaseVNode, a as createTextVNode } from "./chunks/framework.8zKZLKO7.js";
const __pageData = JSON.parse('{"title":"Setting Up Your QMK Environment","description":"","frontmatter":{},"headers":[],"relativePath":"newbs_getting_started.md","filePath":"newbs_getting_started.md","lastUpdated":null}');
const _sfc_main = { name: "newbs_getting_started.md" };
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  const _component_PluginTabsTab = resolveComponent("PluginTabsTab");
  const _component_PluginTabs = resolveComponent("PluginTabs");
  return openBlock(), createElementBlock("div", null, [
    _cache[8] || (_cache[8] = createStaticVNode('<h1 id="setting-up-your-qmk-environment" tabindex="-1">Setting Up Your QMK Environment <a class="header-anchor" href="#setting-up-your-qmk-environment" aria-label="Permalink to &quot;Setting Up Your QMK Environment&quot;">​</a></h1><p>Before you can build keymaps, you need to install some software and set up your build environment. This only has to be done once no matter how many keyboards you plan to compile firmware for.</p><h2 id="_1-prerequisites" tabindex="-1">1. Prerequisites <a class="header-anchor" href="#_1-prerequisites" aria-label="Permalink to &quot;1. Prerequisites&quot;">​</a></h2><p>There are a few pieces of software you&#39;ll need to get started.</p><ul><li><a href="./newbs_learn_more_resources#text-editor-resources">Text editor</a><ul><li>You’ll need a program that can edit and save plain text files. The default editor that comes with many OS&#39;s does not save plain text files, so you&#39;ll need to make sure that whatever editor you chose does.</li></ul></li><li><a href="https://github.com/qmk/qmk_toolbox" target="_blank" rel="noreferrer">Toolbox (optional)</a><ul><li>A graphical program for Windows and macOS that allows you to both program and debug your custom keyboard</li></ul></li></ul><div class="tip custom-block"><p class="custom-block-title">TIP</p><p>If you haven&#39;t worked with the Linux/Unix command line before, there are a few basic concepts and commands you should learn. <a href="./newbs_learn_more_resources#command-line-resources">These resources</a> will teach you enough to be able to work with QMK.</p></div><h2 id="set-up-your-environment" tabindex="-1">2. Prepare Your Build Environment <a class="header-anchor" href="#set-up-your-environment" aria-label="Permalink to &quot;2. Prepare Your Build Environment {#set-up-your-environment}&quot;">​</a></h2><p>We&#39;ve tried to make QMK as easy to set up as possible. You only have to prepare your Linux or Unix environment, then let QMK install the rest.</p>', 8)),
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "Windows" }, {
          default: withCtx(() => [..._cache[0] || (_cache[0] = [
            createBaseVNode("p", null, [
              createTextVNode("QMK maintains a Bundle of MSYS2, the CLI and all necessary dependencies. It also provides a handy "),
              createBaseVNode("code", null, "QMK MSYS"),
              createTextVNode(" terminal shortcut to boot you directly into the correct environment.")
            ], -1),
            createBaseVNode("h4", {
              id: "prerequisites",
              tabindex: "-1"
            }, [
              createTextVNode("Prerequisites "),
              createBaseVNode("a", {
                class: "header-anchor",
                href: "#prerequisites",
                "aria-label": 'Permalink to "Prerequisites"'
              }, "​")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("You will need to install "),
              createBaseVNode("a", {
                href: "https://msys.qmk.fm/",
                target: "_blank",
                rel: "noreferrer"
              }, "QMK MSYS"),
              createTextVNode(". The latest release is available "),
              createBaseVNode("a", {
                href: "https://github.com/qmk/qmk_distro_msys/releases/latest",
                target: "_blank",
                rel: "noreferrer"
              }, "here"),
              createTextVNode(".")
            ], -1),
            createBaseVNode("details", { class: "details custom-block" }, [
              createBaseVNode("summary", null, "Advanced Users"),
              createBaseVNode("div", { class: "danger custom-block" }, [
                createBaseVNode("p", { class: "custom-block-title" }, "DANGER"),
                createBaseVNode("p", null, [
                  createBaseVNode("b", { style: { "font-size": "150%" } }, "This process is not recommended for new users.")
                ])
              ]),
              createBaseVNode("p", null, "If you'd like to manually install MSYS2, the following sections will walk you through the process."),
              createBaseVNode("h4", {
                id: "prerequisites-1",
                tabindex: "-1"
              }, [
                createTextVNode("Prerequisites "),
                createBaseVNode("a", {
                  class: "header-anchor",
                  href: "#prerequisites-1",
                  "aria-label": 'Permalink to "Prerequisites"'
                }, "​")
              ]),
              createBaseVNode("p", null, [
                createTextVNode("You will need to install "),
                createBaseVNode("a", {
                  href: "https://www.msys2.org",
                  target: "_blank",
                  rel: "noreferrer"
                }, "MSYS2"),
                createTextVNode(". Once installed, close any open MSYS terminals (purple icon) and open a new MinGW 64-bit terminal (blue icon) from the Start Menu.")
              ]),
              createBaseVNode("div", { class: "warning custom-block" }, [
                createBaseVNode("p", { class: "custom-block-title" }, "WARNING"),
                createBaseVNode("p", null, [
                  createBaseVNode("strong", null, "NOTE:"),
                  createTextVNode(" The MinGW 64-bit terminal is "),
                  createBaseVNode("em", null, "not"),
                  createTextVNode(' the same as the MSYS terminal that opens when installation is completed. Your prompt should say "MINGW64" in purple text, rather than "MSYS". See '),
                  createBaseVNode("a", {
                    href: "https://www.msys2.org/wiki/MSYS2-introduction/#subsystems",
                    target: "_blank",
                    rel: "noreferrer"
                  }, "this page"),
                  createTextVNode(" for more information on the differences.")
                ])
              ]),
              createBaseVNode("h4", {
                id: "installation",
                tabindex: "-1"
              }, [
                createTextVNode("Installation "),
                createBaseVNode("a", {
                  class: "header-anchor",
                  href: "#installation",
                  "aria-label": 'Permalink to "Installation"'
                }, "​")
              ]),
              createBaseVNode("p", null, "Install the QMK CLI by running:"),
              createBaseVNode("div", { class: "language-sh vp-adaptive-theme" }, [
                createBaseVNode("button", {
                  title: "Copy Code",
                  class: "copy"
                }),
                createBaseVNode("span", { class: "lang" }, "sh"),
                createBaseVNode("pre", {
                  class: "shiki shiki-themes github-light github-dark vp-code",
                  tabindex: "0"
                }, [
                  createBaseVNode("code", null, [
                    createBaseVNode("span", { class: "line" }, [
                      createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "curl"),
                      createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " -fsSL"),
                      createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, " https://install.qmk.fm"),
                      createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " |"),
                      createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " sh")
                    ])
                  ])
                ])
              ])
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "macOS" }, {
          default: withCtx(() => [..._cache[1] || (_cache[1] = [
            createBaseVNode("h4", {
              id: "prerequisites-2",
              tabindex: "-1"
            }, [
              createTextVNode("Prerequisites "),
              createBaseVNode("a", {
                class: "header-anchor",
                href: "#prerequisites-2",
                "aria-label": 'Permalink to "Prerequisites"'
              }, "​")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("You will need to install Homebrew. Follow the instructions on "),
              createBaseVNode("a", {
                href: "https://brew.sh",
                target: "_blank",
                rel: "noreferrer"
              }, "https://brew.sh"),
              createTextVNode(".")
            ], -1),
            createBaseVNode("h4", {
              id: "installation-1",
              tabindex: "-1"
            }, [
              createTextVNode("Installation "),
              createBaseVNode("a", {
                class: "header-anchor",
                href: "#installation-1",
                "aria-label": 'Permalink to "Installation"'
              }, "​")
            ], -1),
            createBaseVNode("p", null, "Install the QMK CLI by running:", -1),
            createBaseVNode("div", { class: "language-sh vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "sh"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "curl"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " -fsSL"),
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, " https://install.qmk.fm"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " |"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " sh")
                  ])
                ])
              ])
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Linux/WSL" }, {
          default: withCtx(() => [..._cache[2] || (_cache[2] = [
            createBaseVNode("h4", {
              id: "installation-2",
              tabindex: "-1"
            }, [
              createTextVNode("Installation "),
              createBaseVNode("a", {
                class: "header-anchor",
                href: "#installation-2",
                "aria-label": 'Permalink to "Installation"'
              }, "​")
            ], -1),
            createBaseVNode("div", { class: "info custom-block" }, [
              createBaseVNode("p", { class: "custom-block-title" }, "INFO"),
              createBaseVNode("p", null, "Many Linux distributions are supported, but not all. Mainstream distributions will have best success -- if possible, choose either Debian or its derivatives (such as Ubuntu, or Mint), CentOS or its derivatives (such as Fedora, or Rocky Linux), and Arch or its derivatives (such as Manjaro, or CachyOS).")
            ], -1),
            createBaseVNode("p", null, "Install the QMK CLI by running:", -1),
            createBaseVNode("div", { class: "language-sh vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "sh"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "curl"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " -fsSL"),
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, " https://install.qmk.fm"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " |"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " sh")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("div", { class: "tip custom-block" }, [
              createBaseVNode("p", { class: "custom-block-title" }, "TIP"),
              createBaseVNode("p", null, [
                createBaseVNode("strong", null, "Note for WSL users"),
                createTextVNode(": By default, the installation process will clone the QMK repository into your WSL home directory, but if you have cloned manually, ensure that it is located inside the WSL instance instead of the Windows filesystem (ie. not in "),
                createBaseVNode("code", null, "/mnt"),
                createTextVNode("), as accessing it is currently "),
                createBaseVNode("a", {
                  href: "https://github.com/microsoft/WSL/issues/4197",
                  target: "_blank",
                  rel: "noreferrer"
                }, "extremely slow"),
                createTextVNode(".")
              ])
            ], -1),
            createBaseVNode("div", { class: "warning custom-block" }, [
              createBaseVNode("p", { class: "custom-block-title" }, "WARNING"),
              createBaseVNode("p", null, "Any QMK packages provided by your distribution's package manager are almost certainly out of date. It is strongly suggested the installation script above is used instead.")
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "FreeBSD" }, {
          default: withCtx(() => [..._cache[3] || (_cache[3] = [
            createBaseVNode("h4", {
              id: "installation-3",
              tabindex: "-1"
            }, [
              createTextVNode("Installation "),
              createBaseVNode("a", {
                class: "header-anchor",
                href: "#installation-3",
                "aria-label": 'Permalink to "Installation"'
              }, "​")
            ], -1),
            createBaseVNode("div", { class: "warning custom-block" }, [
              createBaseVNode("p", { class: "custom-block-title" }, "WARNING"),
              createBaseVNode("p", null, "FreeBSD support is provided on a best-effort basis by the community instead of the QMK maintainers. It is strongly suggested that you use either Windows, macOS, or a supported distribution of Linux instead.")
            ], -1),
            createBaseVNode("p", null, "Install the FreeBSD package for QMK CLI by running:", -1),
            createBaseVNode("div", { class: "language-sh vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "sh"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "pkg"),
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, " install"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " -g"),
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, ' "py*-qmk"')
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("div", { class: "info custom-block" }, [
              createBaseVNode("p", { class: "custom-block-title" }, "NOTE"),
              createBaseVNode("p", null, [
                createTextVNode("Remember to follow the instructions printed at the end of installation (use "),
                createBaseVNode("code", null, 'pkg info -Dg "py*-qmk"'),
                createTextVNode(" to show them again).")
              ])
            ], -1)
          ])]),
          _: 1
        })
      ]),
      _: 1
    }),
    _cache[9] || (_cache[9] = createBaseVNode("h2", {
      id: "set-up-qmk",
      tabindex: "-1"
    }, [
      createTextVNode("3. Run QMK Setup "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#set-up-qmk",
        "aria-label": 'Permalink to "3. Run QMK Setup {#set-up-qmk}"'
      }, "​")
    ], -1)),
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "Windows" }, {
          default: withCtx(() => [..._cache[4] || (_cache[4] = [
            createBaseVNode("p", null, "Open QMK MSYS and run the following command:", -1),
            createBaseVNode("div", { class: "language-sh vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "sh"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "qmk"),
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, " setup")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("In most situations you will want to answer "),
              createBaseVNode("code", null, "y"),
              createTextVNode(" to all of the prompts.")
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "macOS" }, {
          default: withCtx(() => [..._cache[5] || (_cache[5] = [
            createBaseVNode("p", null, "Open Terminal and run the following command:", -1),
            createBaseVNode("div", { class: "language-sh vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "sh"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "qmk"),
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, " setup")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("In most situations you will want to answer "),
              createBaseVNode("code", null, "y"),
              createTextVNode(" to all of the prompts.")
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Linux/WSL" }, {
          default: withCtx(() => [..._cache[6] || (_cache[6] = [
            createBaseVNode("p", null, "Open your preferred terminal app and run the following command:", -1),
            createBaseVNode("div", { class: "language-sh vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "sh"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "qmk"),
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, " setup")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("In most situations you will want to answer "),
              createBaseVNode("code", null, "y"),
              createTextVNode(" to all of the prompts.")
            ], -1),
            createBaseVNode("div", { class: "info custom-block" }, [
              createBaseVNode("p", { class: "custom-block-title" }, "Note on Debian, Ubuntu and their derivatives:"),
              createBaseVNode("p", null, [
                createTextVNode("It's possible, that you will get an error saying something like: "),
                createBaseVNode("code", null, "bash: qmk: command not found"),
                createTextVNode(". This is due to a "),
                createBaseVNode("a", {
                  href: "https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=839155",
                  target: "_blank",
                  rel: "noreferrer"
                }, "bug"),
                createTextVNode(" Debian introduced with their Bash 4.4 release, which removed "),
                createBaseVNode("code", null, "$HOME/.local/bin"),
                createTextVNode(" from the PATH. This bug was later fixed on Debian and Ubuntu. Sadly, Ubuntu reintroduced this bug and is "),
                createBaseVNode("a", {
                  href: "https://bugs.launchpad.net/ubuntu/+source/bash/+bug/1588562",
                  target: "_blank",
                  rel: "noreferrer"
                }, "yet to fix it"),
                createTextVNode(". Luckily, the fix is easy. Run this as your user: "),
                createBaseVNode("code", null, `echo 'PATH="$HOME/.local/bin:$PATH"' >> $HOME/.bashrc && source $HOME/.bashrc`)
              ])
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "FreeBSD" }, {
          default: withCtx(() => [..._cache[7] || (_cache[7] = [
            createBaseVNode("p", null, "Open your preferred terminal app and run the following command:", -1),
            createBaseVNode("div", { class: "language-sh vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "sh"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "qmk"),
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, " setup")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("In most situations you will want to answer "),
              createBaseVNode("code", null, "y"),
              createTextVNode(" to all of the prompts.")
            ], -1)
          ])]),
          _: 1
        })
      ]),
      _: 1
    }),
    _cache[10] || (_cache[10] = createStaticVNode('<div class="tip custom-block"><p class="custom-block-title">TIP</p><p>The qmk home folder can be specified at setup with <code>qmk setup -H &lt;path&gt;</code>, and modified afterwards using the <a href="./cli_configuration#single-key-example">cli configuration</a> and the variable <code>user.qmk_home</code>. For all available options run <code>qmk setup --help</code>.</p></div><div class="tip custom-block"><p class="custom-block-title">TIP</p><p>If you already know how to use GitHub, <a href="./getting_started_github">we recommend that you follow these instructions</a> and use <code>qmk setup &lt;github_username&gt;/qmk_firmware</code> to clone your personal fork. If you don&#39;t know what that means you can safely ignore this message.</p></div><h2 id="_4-test-your-build-environment" tabindex="-1">4. Test Your Build Environment <a class="header-anchor" href="#_4-test-your-build-environment" aria-label="Permalink to &quot;4. Test Your Build Environment&quot;">​</a></h2><p>Now that your QMK build environment is set up, you can build a firmware for your keyboard. Start by trying to build the keyboard&#39;s default keymap. You should be able to do that with a command in this format:</p><div class="language-sh vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">sh</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">qmk</span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;"> compile</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> -kb</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;"> &lt;</span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">keyboar</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">d</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&gt;</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> -km</span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;"> default</span></span></code></pre></div><p>For example, to build a firmware for a Clueboard 66% you would use:</p><div class="language-sh vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">sh</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">qmk</span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;"> compile</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> -kb</span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;"> clueboard/66/rev3</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> -km</span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;"> default</span></span></code></pre></div><div class="tip custom-block"><p class="custom-block-title">TIP</p><p>The keyboard option is the path relative to the keyboard directory, the above example would be found in <code>qmk_firmware/keyboards/clueboard/66/rev3</code>. If you&#39;re unsure you can view a full list of supported keyboards with <code>qmk list-keyboards</code>.</p></div><p>When it is done you should have a lot of output that ends similar to this:</p><div class="language- vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang"></span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span>Linking: .build/clueboard_66_rev3_default.elf                                                       [OK]</span></span>\n<span class="line"><span>Creating load file for flashing: .build/clueboard_66_rev3_default.hex                               [OK]</span></span>\n<span class="line"><span>Copying clueboard_66_rev3_default.hex to qmk_firmware folder                                        [OK]</span></span>\n<span class="line"><span>Checking file size of clueboard_66_rev3_default.hex                                                 [OK]</span></span>\n<span class="line"><span> * The firmware size is fine - 26356/28672 (2316 bytes free)</span></span></code></pre></div><h1 id="creating-your-keymap" tabindex="-1">Creating Your Keymap <a class="header-anchor" href="#creating-your-keymap" aria-label="Permalink to &quot;Creating Your Keymap&quot;">​</a></h1><p>You are now ready to create your own personal keymap! Move on to <a href="./newbs_building_firmware">Building Your First Firmware</a> for that.</p>', 12))
  ]);
}
const newbs_getting_started = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  newbs_getting_started as default
};
