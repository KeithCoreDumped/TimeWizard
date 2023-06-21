import { createApp } from 'vue'
import App from './App.vue'
import indexPage from "@/pages/indexPage.vue";
import loginPage from "@/pages/loginPage";
import axios from "axios";
import { createRouter, createWebHistory } from 'vue-router';
import darkTheme from "naive-ui"

const routes = [
    { path: '/', component: indexPage },
    { path: '/login', component: loginPage },
]

const router = createRouter({
    history: createWebHistory(),
    routes,
})

const API = axios.create({
    baseURL:'https://api.nickwald.top/codability/',
    timeout: 2000
})

const app = createApp(App);
app.config.globalProperties.$request = API;
app.config.globalProperties.$darkTheme = darkTheme;
app.use(router).mount('#app')