<template>
  <n-layout has-sider position="absolute" style="top: 64px;">
    <n-layout-sider
        :collapsed="collapsed"
        :collapsed-width="64"
        :width="240"
        bordered
        collapse-mode="width"
        show-trigger
        @collapse="collapsed = true"
        @expand="collapsed = false"
    >
      <n-menu
          v-model:value="activeKey"
          :collapsed="collapsed"
          :collapsed-icon-size="22"
          :collapsed-width="64"
          :options="menuOptions"
      />
    </n-layout-sider>
    <n-layout :native-scrollbar="false" content-style="padding: 24px;" embedded>
      <n-back-top :right="100"/>
      <preview-component v-if="activeKey === 'preview'"/>
      <course-component v-else-if="activeKey === ''"/>
    </n-layout>
  </n-layout>
</template>

<script>
import {NBackTop, NIcon, NLayout, NLayoutSider, NMenu} from "naive-ui";
import {
  ChatboxEllipses as Discuss,
  Cog as Setting,
  Compass as Wiki,
  GameController as Activity,
  Home as Preview,
  LogoYoutube as Course,
  Map as KnowledgeMap,
  Podium as Rank,
  Ribbon as Competition,
  Rocket as Game,
  School as Learn,
  Storefront as Shopping,
  TrashBin as Mistake
} from "@vicons/ionicons5";
import {h, ref} from "vue";

import previewComponent from "@/components/previewComponent.vue";
import CourseComponent from "@/components/courseComponent.vue";

function renderIcon(icon) {
  return () => h(NIcon, null, {default: () => h(icon)});
}
const menuOptions = [
  {
    label: "总览",
    key: "preview",
    icon: renderIcon(Preview)
  },
  {
    label: "学习",
    key: "learn",
    icon: renderIcon(Learn),
    children: [
      {
        label: "课程",
        key: "course",
        icon: renderIcon(Course)
      },
      {
        label: "知识图谱",
        key: "knowledgeMap",
        icon: renderIcon(KnowledgeMap)
      },
      {
        label: "错题本",
        key: "mistake",
        icon: renderIcon(Mistake)
      }
    ]
  },
  {
    label: "闯关",
    key: "game",
    icon: renderIcon(Game),
    children: [
      {
        label: "活动",
        key: "activity",
        icon: renderIcon(Activity)
      },
      {
        label: "比赛",
        key: "competition",
        icon: renderIcon(Competition)
      },
      {
        label: "天梯",
        key: "rank",
        icon: renderIcon(Rank)
      }
    ]
  },
  {
    label: "论坛",
    key: "discuss",
    icon: renderIcon(Discuss)
  },
  {
    label: "Wiki",
    key: "wiki",
    icon: renderIcon(Wiki)
  },
  {
    label: "商店",
    key: "shopping",
    icon: renderIcon(Shopping)
  },
  {
    label: "设置",
    key: "setting",
    icon: renderIcon(Setting)
  }
];

export default {
  name: "indexPage",
  components: {
    CourseComponent,
    NMenu,
    NBackTop,
    NLayout,
    NLayoutSider,
    previewComponent,
  },
  setup() {
    const message = window.$message
    message.success("欢迎，你以成功登录~")
    return {
      activeKey: ref('preview'),
      collapsed: ref(true),
      menuOptions,
    }
  }
}
</script>

<style scoped>
@font-face {
  font-family: Efont;
  src: url("/public/res/Efont.ttf");
}
</style>