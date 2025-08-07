<script setup>
import DefaultTheme from 'vitepress/theme'
import { useRouter } from 'vitepress'
import { onBeforeMount } from 'vue';
import aliases from "../../../../docs/_aliases.json";

const router = useRouter()
onBeforeMount(async () => {
    // Convert from docsify-style to vitepress-style URLs
    let newUrl = window.location.href.replace(/\/#\//, '/').replace(/\?id=/, '#');

    // Convert any aliases
    let testUrl = new URL(newUrl);
    while (testUrl.pathname in aliases) {
        testUrl.pathname = aliases[testUrl.pathname];
    }
    newUrl = testUrl.toString();

    // Redirect if required
    if (newUrl != window.location.href) {
        window.history.replaceState({}, '', newUrl);
        await router.go(newUrl);
    }
});
</script>

<template>
    <DefaultTheme.Layout/>
</template>
