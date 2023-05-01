// @ts-check
// Note: type annotations allow type checking and IDEs autocompletion

const lightCodeTheme = require("prism-react-renderer/themes/github");
const darkCodeTheme = require("prism-react-renderer/themes/dracula");

/** @type {import('@docusaurus/types').Config} */
const config = {
    title: "QMK Firmware",
    tagline: "The full documentation of the open-source firmware",
    favicon: "img/favicon.ico",
    url: "https://docs.qmk.fm",
    baseUrl: "/",
    organizationName: "qmk",
    projectName: "qmk_firmware",
    deploymentBranch: "gh-pages",
    onBrokenLinks: "warn",
    onBrokenMarkdownLinks: "warn",
    i18n: {
        defaultLocale: "en",
        locales: ["en"], //, 'ja', 'zh-cn'],
    },
    themes: [
        [
            "classic",
            {
                customCss: require.resolve("./src/css/custom.css"),
            }
        ],
        [
            require.resolve("@easyops-cn/docusaurus-search-local"),
            {
                indexBlog: false,
                docsRouteBasePath: '/',
                searchResultLimits: 12,
                searchBarShortcut: false,
            },
        ],
    ],
    plugins: [
        [
            "@docusaurus/plugin-content-docs",
            {
                sidebarPath: require.resolve("./sidebars.js"),
                path: ".",
                routeBasePath: "/",
                exclude: [
                    "node_modules",
                    "src",
                    "static",
                    "ja",
                    "zh-cn",
                    "gitbook",
                    // "ChangeLog"
                ],
                editUrl:
                    "https://github.com/qmk/qmk_firmware/edit/master/docs/",
            },
        ],
        [
            "@docusaurus/plugin-client-redirects",
            {
                // fromExtensions: ['md', 'html'],
                redirects: [
                    // from index.html
                    {
                        from: '/adding_a_keyboard_to_qmk',
                        to: '/hardware_keyboard_guidelines',
                    },
                    {
                        from: '/build_environment_setup',
                        to: '/newbs_getting_started',
                    },
                    {
                        from: '/cli_dev_configuration',
                        to: '/cli_configuration',
                    },
                    {
                        from: '/dynamic_macros',
                        to: '/feature_dynamic_macros',
                    },
                    {
                        from: '/feature_common_shortcuts',
                        to: '/feature_advanced_keycodes',
                    },
                    {
                        from: '/glossary',
                        to: '/reference_glossary',
                    },
                    {
                        from: '/key_lock',
                        to: '/feature_key_lock',
                    },
                    {
                        from: '/make_instructions',
                        to: '/getting_started_make_guide',
                    },
                    {
                        from: ['/space_cadet_shift', '/feature_space_cadet_shift'],
                        to: '/feature_space_cadet',
                    },
                    {
                        from: '/getting_started_getting_help',
                        to: '/support',
                    },
                    {
                        from: '/tap_dance',
                        to: '/feature_tap_dance',
                    },
                    {
                        from: '/unicode',
                        to: '/feature_unicode',
                    },
                    {
                        from: '/python_development',
                        to: '/cli_development',
                    },
                    {
                        from: '/getting_started_build_tools',
                        to: '/newbs_getting_started',
                    },
                    {
                        from: '/tutorial',
                        to: '/newbs',
                    },
                    // from redirects.json
                    // {
                    //     from: "/adding_a_keyboard_to_qmk",
                    //     to: "/hardware_keyboard_guidelines"
                    // },
                    // {
                    //     from: "/build_environment_setup",
                    //     to: "/getting_started_build_tools"
                    // },
                    // {
                    //     from: "/dynamic_macros",
                    //     to: "/feature_dynamic_macros"
                    // },
                    // {
                    //     from: "/feature_common_shortcuts",
                    //     to: "/feature_advanced_keycodes"
                    // },
                    // {
                    //     from: "/glossary",
                    //     to: "/reference_glossary"
                    // },
                    // {
                    //     from: "/key_lock",
                    //     to: "/feature_key_lock"
                    // },
                    // {
                    //     from: "/make_instructions",
                    //     to: "/getting_started_make_guide"
                    // },
                    // {
                    //     from: "/porting_your_keyboard_to_qmk",
                    //     to: "/hardware_avr"
                    // },
                    // {
                    //     from: "/space_cadet_shift",
                    //     to: "/feature_space_cadet_shift"
                    // },
                    // {
                    //     from: "/tap_dance",
                    //     to: "/feature_tap_dance"
                    // },
                    // {
                    //     from: "/unicode",
                    //     to: "/feature_unicode"
                    // },
                    // {
                    //     from: "/python_development",
                    //     to: "/cli_development"
                    // }
                  ],
            },
        ],
    ],

    themeConfig:
        /** @type {import('@docusaurus/preset-classic').ThemeConfig} */
        ({
            image: "img/qmk-social-card.jpg",
            navbar: {
                title: "QMK Firmware Docs",
                logo: {
                    alt: "QMK Firmware",
                    src: "img/qmk-new-light.svg",
                    srcDark: "img/qmk-new-dark.svg",
                    width: 32,
                    height: 32,
                },
                items: [
                    // {
                    // type: 'localeDropdown',
                    // position: 'right',
                    // },
                    {
                        href: "https://github.com/qmk/qmk_firmware",
                        label: "GitHub",
                        position: "right",
                    },
                ],
            },
            docs: {
                sidebar: {
                    autoCollapseCategories: false,
                },
            },
            footer: {
                style: "dark",
                links: [
                    {
                        title: "Docs",
                        items: [
                            {
                                label: "Docs",
                                to: "/",
                            },
                        ],
                    },
                    {
                        title: "Community",
                        items: [
                            {
                                label: "Discord",
                                href: "https://discord.gg/Uq7gcHh",
                            },
                            {
                                label: "Reddit",
                                href: "https://reddit.com/r/olkb",
                            },
                        ],
                    },
                    {
                        title: "More",
                        items: [
                            {
                                label: "GitHub",
                                href: "https://github.com/qmk/qmk_firmware",
                            },
                        ],
                    },
                ],
                copyright: `Copyright © ${new Date().getFullYear()} QMK. Built with Docusaurus.`,
            },
            prism: {
                theme: lightCodeTheme,
                darkTheme: darkCodeTheme,
            },
            // applied for - will fill out once we hear back
            //
            // algolia: {
            //   // The application ID provided by Algolia
            //   appId: 'YOUR_APP_ID',

            //   // Public API key: it is safe to commit it
            //   apiKey: 'YOUR_SEARCH_API_KEY',

            //   indexName: 'YOUR_INDEX_NAME',

            //   // Optional: see doc section below
            //   contextualSearch: true,

            //   // Optional: Specify domains where the navigation should occur through window.location instead on history.push. Useful when our Algolia config crawls multiple documentation sites and we want to navigate with window.location.href to them.
            //   externalUrlRegex: 'external\\.com|domain\\.com',

            //   // Optional: Replace parts of the item URLs from Algolia. Useful when using the same search index for multiple deployments using a different baseUrl. You can use regexp or string in the `from` param. For example: localhost:3000 vs myCompany.com/docs
            //   replaceSearchResultPathname: {
            //     from: '/docs/', // or as RegExp: /\/docs\//
            //     to: '/',
            //   },

            //   // Optional: Algolia search parameters
            //   searchParameters: {},

            //   // Optional: path for search page that enabled by default (`false` to disable it)
            //   searchPagePath: 'search',

            //   //... other Algolia params
            // },
        }),
};

module.exports = config;
