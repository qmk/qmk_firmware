import path from "path";
import { defineConfig } from "vitepress";
import { tabsMarkdownPlugin } from "vitepress-plugin-tabs";
import { createRequire } from "node:module";
const require = createRequire(import.meta.url);

// https://vitepress.dev/reference/site-config
export default defineConfig(({ mode }) => {
    const prod = mode === "production";
    return {
        title: "QMK Firmware",
        description: "Documentation for QMK Firmware",

        srcDir: path.resolve("../../docs"),
        assetsDir: path.resolve("../../docs"),
        outDir: path.resolve("../../.build/docs"),
        cleanUrls: true,

        srcExclude: ["ja/**", "zh-cn/**"],

        markdown: {
            config(md) {
                md.use(tabsMarkdownPlugin);
            },
        },

        vite: {
            resolve: {
                alias: prod // for some reason prod builds require a different method of resolving the renderer
                    ? {
                          "vue/server-renderer": require.resolve(
                              "vue/server-renderer"
                          ),
                          vue: require.resolve("vue"),
                      }
                    : {},
            },
        },

        themeConfig: {
            // https://vitepress.dev/reference/default-theme-config
            nav: [{ text: "Home", link: "./" }],

            search: {
                provider: "local",
            },

            sidebar: [
                {
                    text: "Examples",
                    items: [
                        {
                            text: "Markdown Examples",
                            link: "/markdown-examples",
                        },
                        { text: "Runtime API Examples", link: "/api-examples" },
                    ],
                },
            ],

            socialLinks: [
                { icon: "github", link: "https://github.com/vuejs/vitepress" },
            ],
        },
    };
});
