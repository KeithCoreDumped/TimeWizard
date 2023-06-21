<template>

  <n-config-provider :theme="theme">
    <n-message-provider>
      <MessageApi />
    </n-message-provider>
    <div id="app">
      <n-modal
          v-model:show="showLoginModal"
          :style="centerBoxStyle"
          preset="card"
          size="huge"
          title="TimeWizard - 时间魔盒"
          transform-origin="center"
      >
        <n-tabs
            v-model:value="centerBoxTab"
            :tabs-padding="20"
            animated
            pane-style="padding: 20px;"
            size="large"
            type="line"
        >
          <n-tab-pane name="login" tab="登录">
            <template #tab>
              <n-space>
                <n-icon>
                  <LogIn/>
                </n-icon>
                登录
              </n-space>
            </template>
            <n-form>

            </n-form>
          </n-tab-pane>
          <n-tab-pane name="register" tab="注册">
            <template #tab>
              <n-space>
                <n-icon>
                  <PersonAdd/>
                </n-icon>
                注册
              </n-space>
            </template>
            <n-form>

            </n-form>
          </n-tab-pane>
        </n-tabs>
      </n-modal>
      <n-layout position="absolute">
        <n-layout-header bordered style="height: 64px;padding: 24px">
          <n-space justify="space-between">
            <n-h1 style="font-family: Efont,serif">TimeWizard - 时间魔盒</n-h1>
            <n-space>
              <n-switch :value="ThemeSwitchValue" size="large" @click="changeTheme">
                <template #checked-icon>
                  <n-icon>
                    <Moon/>
                  </n-icon>
                </template>
                <template #unchecked-icon>
                  <n-icon>
                    <Sun/>
                  </n-icon>
                </template>
              </n-switch>
              <n-space v-if="false">
                <n-button round tertiary size="small" @click="showRegisterBox">
                  注册
                </n-button>
                <span style="color: darkgray">或</span>
                <n-button round tertiary size="small" @click="showLoginBox">
                  登录
                </n-button>
              </n-space>
              <n-button v-else size="small" round tertiary type="error">
                <template #icon>
                  <n-icon>
                    <LogOut/>
                  </n-icon>
                </template>
                登出
              </n-button>
            </n-space>
          </n-space>
        </n-layout-header>
        <router-view/>
      </n-layout>
    </div>
    <n-global-style/>
  </n-config-provider>

</template>

<script>
import MessageApi from "@/components/messageApi.vue";
import {
  darkTheme,
  NButton,
  NConfigProvider,
  NForm,
  NGlobalStyle,
  NH1,
  NIcon,
  NLayout,
  NLayoutHeader, NMessageProvider,
  NModal,
  NSpace,
  NSwitch,
  NTabPane,
  NTabs,
} from "naive-ui";
import {ref} from "vue";
import {LogIn, LogOut, Moon, PersonAdd, Sunny as Sun} from "@vicons/ionicons5";

const theme = ref(null);
const ThemeSwitchValue = ref(false);
const centerBoxTab = ref('login')
const showLoginModal = ref(false)
const changeTheme = () => {
  theme.value = theme.value == null ? darkTheme : null;
  ThemeSwitchValue.value = theme.value != null;
  if(theme.value != null) {
    document.body.classList.add('dark');
    document.body.classList.remove('light')
  }
  else {
    document.body.classList.remove('dark');
    document.body.classList.add('light')
  }
};
const showLoginBox = () => {
  centerBoxTab.value = 'login';
  showLoginModal.value = true;
}
const showRegisterBox = () => {
  centerBoxTab.value = 'register';
  showLoginModal.value = true;
}
export default {
  name: 'App',
  components: {
    NMessageProvider,
    NH1,
    NForm,
    NTabs,
    NTabPane,
    NModal,
    NSwitch,
    NButton,
    NSpace,
    NIcon,
    NLayoutHeader,
    NLayout,
    NGlobalStyle,
    NConfigProvider,
    Moon,
    Sun,
    LogIn,
    LogOut,
    PersonAdd,
    MessageApi,
  },
  setup() {
    if(theme.value != null) {
      document.body.classList.add('dark');
      document.body.classList.remove('light')
    }
    else {
      document.body.classList.remove('dark');
      document.body.classList.add('light')
    }
    return {
      theme,
      ThemeSwitchValue,
      changeTheme,
      showLoginModal,
      centerBoxStyle: {
        width: "30%"
      },
      centerBoxTab,
      showLoginBox,
      showRegisterBox
    }
  }
}
</script>

<style>

</style>
