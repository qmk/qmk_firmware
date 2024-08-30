import type { Theme } from 'vitepress'
import DefaultTheme from 'vitepress/theme'
import { enhanceAppWithTabs } from 'vitepress-plugin-tabs/client'
import QMKLayout from './QMKLayout.vue'
import './custom.css'

export default {
  extends: DefaultTheme,
  Layout: QMKLayout,
  enhanceApp({ app }) {
    enhanceAppWithTabs(app)
  }
} satisfies Theme
