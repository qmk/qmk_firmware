<script setup>
import DefaultTheme from 'vitepress/theme'
import { useRouter } from 'vitepress'
import { onBeforeMount } from 'vue';

const router = useRouter()
onBeforeMount(async () => {
    if (window.location.href.includes('/#/')) {
        const newUrl = window.location.href.replace(/\/#\//, '/').replace(/\?id=/, '#');
        window.history.replaceState({}, '', newUrl);
        await router.go(newUrl);
    }
});
</script>

<template>
    <DefaultTheme.Layout/>
</template>
