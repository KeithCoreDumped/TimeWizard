<script>
import { defineComponent } from "vue";
import { useMessage } from "naive-ui";

export default defineComponent({
  setup() {
    window.$message = useMessage();
  },
});
</script>

<template>
<div />
</template>

<style scoped>

</style>