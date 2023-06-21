<template>
  <n-grid :x-gap="12" :y-gap="8" cols="3 s:1 m:3 l:3 xl:3 2xl:3" responsive="screen">
    <n-gi span="2">
      <n-space size="large" vertical>
        <n-card
            hoverable
            size="large"
        >
          <template #header>
            <n-space>
              <n-icon size="24">
                <Announcement/>
              </n-icon>
              公告
            </n-space>
          </template>
          <n-h1 prefix="bar">
            TimeWizard v2023.6.21.1固件版本发布！
          </n-h1>
          <n-blockquote>
            一代版本一代神。<br />
            —— Nickwald & KeithCoreDumped (TimeWizard Developer)
          </n-blockquote>
          <n-p>
            哈喽大家好！本次TimeWizard为各位客官提供了新一轮的更新嗷~
          </n-p>
          <n-p>
            本次更新属于月度更新，您的闹钟将会全程自动化更新，无需手动设置呢！
          </n-p>
        </n-card>
        <n-card
            hoverable
            size="large"
        >
          <template #header>
            <n-space>
              <n-icon size="24">
                <Analyze/>
              </n-icon>
              数据
            </n-space>
          </template>
          <n-space justify="space-around">
              <n-statistic label="总专注">
                <template #prefix>
                  <n-icon>
                    <Time />
                  </n-icon>
                </template>
                <n-number-animation :from="0" :to="63" />
                <template #suffix>
                  个小时
                </template>
              </n-statistic>
              <n-statistic label="已培养">
                <template #prefix>
                  <n-icon>
                    <CheckmarkCircle />
                  </n-icon>
                </template>
                <n-number-animation :from="0" :to="10" />
                <template #suffix>
                  个习惯
                </template>
              </n-statistic>
              <n-statistic label="已完成">
                <template #prefix>
                  <n-icon>
                    <FileTrayFull />
                  </n-icon>
                </template>
                <n-number-animation :from="0" :to="136" />
                <template #suffix>
                  个任务
                </template>
              </n-statistic>
              <n-statistic label="已激活">
                <template #prefix>
                  <n-icon>
                    <Core />
                  </n-icon>
                </template>
                <n-number-animation :from="0" :to="2" />
                <template #suffix>
                  个硬件
                </template>
              </n-statistic>
          </n-space>
          <n-divider title-placement="left">
            时间足迹
          </n-divider>
          <n-timeline size="large">
            <n-timeline-item
                type="success"
                title="取得成就"
                content="「新的一年」成就取得！"
                time="2023-1-1 00:00"
            />
            <n-timeline-item
                type="warning"
                title="计划预警"
                content="「导论」计划堆积较多，建议清理"
                time="2023-3-30 8:00"
            />
            <n-timeline-item
                type="error"
                title="打卡失败"
                content="「跑步」习惯在最后84%打卡失败嗷……"
                line-type="dashed"
                time="2023-5-23 14:31"
            />
            <n-timeline-item
                title="继续努力"
                content="「时间足迹」可以带你回到开头，但是时间是回不去了"
                time="现在"
            />
          </n-timeline>
          <n-divider title-placement="left">
            习惯进度
          </n-divider>
          <n-list>
            <n-list-item>
              <n-space justify="space-evenly">
                <n-space size="small">
                  <n-icon size="24"><Sport /></n-icon>
                  <span>锻炼</span>
                </n-space>
                <n-progress
                    type="line"
                    :percentage="48"
                    :height="24"
                    status="warning"
                    border-radius="12px 12px 0 0"
                    style="width: 500px;"
                    :indicator-placement="'inside'"
                    fill-border-radius="12px 0 12px 12px"
                    processing
                />
              </n-space>
            </n-list-item>
            <n-list-item>
              <n-space justify="space-evenly">
                <n-space size="small">
                  <n-icon size="24"><Pencil /></n-icon>
                  <span>写作</span>
                </n-space>
                <n-progress
                    type="line"
                    :percentage="73"
                    :height="24"
                    status="success"
                    border-radius="12px 12px 0 0"
                    style="width: 500px;"
                    :indicator-placement="'inside'"
                    fill-border-radius="12px 0 12px 12px"
                    processing
                />
              </n-space>
            </n-list-item>
            <n-list-item>
              <n-space justify="space-evenly">
                <n-space size="small">
                  <n-icon size="24"><Core /></n-icon>
                  <span>模电</span>
                </n-space>
                <n-progress
                    type="line"
                    :percentage="21"
                    :height="24"
                    status="error"
                    border-radius="12px 12px 0 0"
                    style="width: 500px;"
                    :indicator-placement="'inside'"
                    fill-border-radius="12px 0 12px 12px"
                    processing
                />
              </n-space>
            </n-list-item>
          </n-list>
          <n-divider title-placement="left">
            时间分析
          </n-divider>
          <n-divider title-placement="left">
            硬件管理
          </n-divider>
          <n-list hoverable clickable>
            <n-list-item>
              <template #prefix>
                <n-button>
                  <template #icon>
                    <n-icon><Settings /></n-icon>
                  </template>
                  设置
                </n-button>
              </template>
              <n-thing title="Nickwald's Home Clock">
                <template #description>
                  <n-space size="small">
                    <n-tag :bordered="false" type="info" size="small">TW-0型号</n-tag>
                    <n-tag :bordered="false" type="error" size="small">v2022.12.29.4固件</n-tag>
                    <n-tag :bordered="false" type="success" size="small">已激活</n-tag>
                    <n-space size="small">
                      <n-icon size="16" color="red"><CloudDownload /></n-icon>
                      <n-gradient-text size="16" type="error">设备正在从服务器更新固件……</n-gradient-text>
                    </n-space>
                  </n-space>
                </template>
                <template #header-extra>
                  <n-button type="error" tertiary>解绑</n-button>
                </template>
                这是放在家里的闹钟~
              </n-thing>
            </n-list-item>
            <n-list-item>
              <template #prefix>
                <n-button>
                  <template #icon>
                    <n-icon><Settings /></n-icon>
                  </template>
                  设置
                </n-button>
              </template>
              <n-thing title="Nickwald's School Clock">
                <template #description>
                  <n-space size="small">
                    <n-tag :bordered="false" type="info" size="small">TW-1型号</n-tag>
                    <n-tag :bordered="false" type="success" size="small">v2023.6.21.1固件</n-tag>
                    <n-tag :bordered="false" type="success" size="small">已激活</n-tag>
                    <n-space size="small">
                      <n-icon size="16" color="green"><CloudDone /></n-icon>
                      <n-gradient-text size="16" type="success">设备已通过WiFi同步</n-gradient-text>
                    </n-space>
                  </n-space>
                </template>
                <template #header-extra>
                  <n-button type="error" tertiary>解绑</n-button>
                </template>
                学校的闹钟，不要忘记拿了。
              </n-thing>
            </n-list-item>
            <n-list-item>
              <template #prefix>
                <n-button type="error">
                  <template #icon>
                    <n-icon><Key /></n-icon>
                  </template>
                  激活
                </n-button>
              </template>
              <n-spin size="large">
                <n-thing title="TimeWizard TW-1 2c4N9">
                  <template #description>
                    <n-space size="small">
                      <n-tag :bordered="false" type="info" size="small">TW-1型号</n-tag>
                      <n-tag :bordered="false" type="success" size="small">v2023.6.21.1固件</n-tag>
                      <n-tag :bordered="false" type="error" size="small">未激活</n-tag>
                      <n-space size="small">
                        <n-icon size="16" color="red"><Key /></n-icon>
                        <n-gradient-text size="16" type="error">正在通过小程序绑定……</n-gradient-text>
                      </n-space>
                    </n-space>
                  </template>
                  <template #header-extra>
                    <n-button type="error" tertiary>解绑</n-button>
                  </template>
                  这是放在家里的闹钟~
                </n-thing>
              </n-spin>
            </n-list-item>
          </n-list>
        </n-card>
        <n-card
            hoverable
            size="large"
        >
          <template #header>
            <n-space>
              <n-icon size="24">
                <Prize/>
              </n-icon>
              勋章墙
            </n-space>
          </template>
          <template #header-extra>
            <n-statistic label="荣誉总数">
              <n-number-animation :from="0" :to="0"/>
            </n-statistic>
          </template>
          <n-empty description="乘风破浪，独占鳌头" size="huge">
            <template #icon>
              <n-icon>
                <Good/>
              </n-icon>
            </template>
            <template #extra>
              <n-button>
                填满它
              </n-button>
            </template>
          </n-empty>
        </n-card>
        <n-card
            hoverable
            size="large"
        >
          <template #header>
            <n-space>
              <n-icon size="24">
                <Alarm/>
              </n-icon>
              进行中
            </n-space>
          </template>
          <n-empty description="正在摸鱼，等待努力……" size="huge">
            <template #icon>
              <n-icon>
                <Fish/>
              </n-icon>
            </template>
            <template #extra>
              <n-button>
                找点事做
              </n-button>
            </template>
          </n-empty>
        </n-card>
        <n-card
            hoverable
            size="large"
        >
          <template #header>
            <n-space>
              <n-icon size="24">
                <Newspaper/>
              </n-icon>
              最近阅览
            </n-space>
          </template>
          <n-empty description="你看过的书，最终都会成为脚下的路" size="huge">
            <template #icon>
              <n-icon>
                <Library/>
              </n-icon>
            </template>
            <template #extra>
              <n-button>
                有道理
              </n-button>
            </template>
          </n-empty>
        </n-card>
      </n-space>
    </n-gi>
    <n-gi span="1">
      <n-space size="large" vertical>
        <n-card
            :segmented="{
            content: true,
            footer: 'soft'
          }"
            hoverable
            size="huge"
        >
          <template #header>
            <n-space>
              <n-icon size="30">
                <Account/>
              </n-icon>
              账户
            </n-space>
          </template>
          <template #header-extra>
            <n-button round tertiary size="small">
              <template #icon>
                <n-icon><Pencil /></n-icon>
              </template>
              编辑
            </n-button>
          </template>
          <n-space justify="center">
            <n-avatar :size="80" src="https://www.nickwald.top/logo.jpg">
              <template #placeholder>
                <n-icon>
                  <Person/>
                </n-icon>
              </template>
            </n-avatar>
            <n-space size="small" vertical>
              <n-gradient-text size="large" type="success" v-if="false">Nickwald</n-gradient-text>
              <span style="font-size: large" v-else>Nickwald</span>
              <n-space>
                <n-popover trigger="hover">
                  <template #trigger>
                    <n-tag size="large" type="error">未激活</n-tag>
                  </template>
                  <span>会员有效期至</span>
                </n-popover>
                <n-button type="error" ghost>
                  <template #icon>
                    <n-icon>
                      <Key/>
                    </n-icon>
                  </template>
                </n-button>
              </n-space>
            </n-space>
          </n-space>
          <template #footer>
            <n-table :bordered="false" :striped="true" size="large">
              <tbody>
              <tr>
                <td>邮箱</td>
                <td>123<span class="mosaic">456@qq.com</span></td>
              </tr>
              <tr>
                <td>手机</td>
                <td>186<span class="mosaic">xxxxxxxx</span></td>
              </tr>
              <tr>
                <td>QQ/微信</td>
                <td>wx<span class="mosaic">xxsafaxxxxx</span></td>
              </tr>
              <tr>
                <td>签名</td>
                <td>向阳生长，灿若花开</td>
              </tr>
              </tbody>
            </n-table>
          </template>
          <template #action>
            <n-space align="center" justify="center">
              <n-button round size="large" type="primary">
                <template #icon>
                  <n-icon>
                    <Checkmark/>
                  </n-icon>
                </template>
                今日签到
              </n-button>
              <n-statistic label="已签到" tabular-nums>
                <n-number-animation :from="0" :to="12"/>
                <template #suffix>天</template>
              </n-statistic>
            </n-space>
          </template>
        </n-card>
        <n-card
            hoverable
            size="huge"
        >
          <template #header>
            <n-space>
              <n-icon size="30">
                <Mail/>
              </n-icon>
              收件箱
            </n-space>
          </template>
          <n-empty description="你步入了荒原" size="huge">
            <template #extra>
              <n-button size="small">
                看点别的
              </n-button>
            </template>
          </n-empty>
        </n-card>
        <n-card
            hoverable
            size="huge"
        >
          <template #header>
            <n-space>
              <n-icon size="30">
                <List/>
              </n-icon>
              待办
            </n-space>
          </template>
          <n-empty v-if="false" description="命运等待你誊写" size="huge">
            <template #icon>
              <n-icon>
                <Airplane/>
              </n-icon>
            </template>
            <template #extra>
              <n-button size="small">
                马上就办
              </n-button>
            </template>
          </n-empty>
          <n-list v-else clickable hoverable>
            <n-list-item>
              <n-thing>
                <template #header>周末加班</template>
                <template #header-extra>
                  <n-checkbox size="large"/>
                </template>
                <template #description>
                  <n-tag :bordered="false" size="tiny" type="error">紧急</n-tag>
                </template>
              </n-thing>
            </n-list-item>
            <n-list-item>
              <n-thing>
                <template #header>第一届“扣力杯”比赛</template>
                <template #header-extra>
                  <n-checkbox size="large"/>
                </template>
                <template #description>
                  <n-tag :bordered="false" size="tiny" type="warning">重要</n-tag>
                </template>
              </n-thing>
            </n-list-item>
            <n-list-item>
              <n-thing>
                <template #header>“算法·第一章”训练</template>
                <template #header-extra>
                  <n-checkbox size="large"/>
                </template>
                <template #description>
                  <n-space size="small">
                    <n-tag :bordered="false" size="tiny" type="warning">重要</n-tag>
                    <n-tag :bordered="false" size="tiny" type="info">测试</n-tag>
                  </n-space>
                </template>
              </n-thing>
            </n-list-item>
            <n-list-item>
              <n-thing>
                <template #header>VIP课程·算法概要一</template>
                <template #header-extra>
                  <n-checkbox size="large"/>
                </template>
                <template #description>
                  <n-space size="small">
                    <n-tag :bordered="false" size="tiny" type="warning">重要</n-tag>
                    <n-tag :bordered="false" size="tiny" type="success">课程</n-tag>
                  </n-space>
                </template>
              </n-thing>
            </n-list-item>
            <n-list-item>
              <n-thing>
                <template #header>天梯赛·第二季度</template>
                <template #header-extra>
                  <n-checkbox size="large"/>
                </template>
                <template #description>
                  <n-tag :bordered="false" size="tiny" type="warning">重要</n-tag>
                </template>
              </n-thing>
            </n-list-item>
          </n-list>
        </n-card>
      </n-space>
    </n-gi>
  </n-grid>
</template>

<script>
import {
  NAvatar,
  NButton,
  NCard,
  NCheckbox, NDivider,
  NEmpty,
  NGi, NGradientText,
  NGrid,
  NIcon,
  NList,
  NListItem,
  NNumberAnimation,
  NPopover, NProgress,
  NSpace, NSpin,
  NStatistic,
  NTable,
  NTag,
  NThing, NTimeline, NTimelineItem,
  NH1, NBlockquote, NP
} from "naive-ui";
import {
  Airplane,
  Alarm,
  Checkmark,
  Fish,
  Key,
  Library,
  List,
  Mail,
  Megaphone as Announcement,
  Newspaper,
  Person,
  PersonCircle as Account,
  PieChart as Analyze,
  Ribbon as Prize,
  ThumbsUp as Good,
  Pencil,
  Time,
  CheckmarkCircle,
  FileTrayFull,
  HardwareChip as Core,
  Settings,
  Barbell as Sport,
  CloudDownload,
  CloudDone
} from "@vicons/ionicons5";

export default {
  name: "previewComponment",
  components: {
    NP,
    NBlockquote,
    NTimelineItem,
    NTimeline,
    NSpin,
    NProgress,
    NDivider,
    NGradientText,
    NTable,
    NPopover,
    NTag,
    NCheckbox,
    NThing,
    NListItem,
    NList,
    NNumberAnimation,
    NStatistic,
    NEmpty,
    NAvatar,
    NSpace,
    NButton,
    NIcon,
    NGrid,
    NGi,
    NCard,
    Announcement,
    Account,
    Mail,
    Analyze,
    List,
    Airplane,
    Alarm,
    Fish,
    Prize,
    Good,
    Checkmark,
    Library,
    Newspaper,
    Person,
    Key,
    Pencil,
    Time,
    CheckmarkCircle,
    FileTrayFull,
    Core,
    Settings,
    Sport,
    CloudDownload,
    CloudDone,
    NH1
  }
}
</script>

<style scoped>
.light .mosaic {
  color: transparent;
  text-shadow: 0 0 10px rgba(0,0,0,0.5);
  transition: all 500ms ease-in;
}

.light .mosaic:hover {
  color: black;
  text-shadow: 0 0 0 rgba(0,0,0,0);
  transition: all 500ms ease-out;
}

.dark .mosaic {
  color: transparent;
  text-shadow: 0 0 10px rgba(255,255,255,0.5);
  transition: all 500ms ease-in;
}

.dark .mosaic:hover {
  color: rgba(255,255,255,0.82);
  text-shadow: 0 0 0 rgba(255,255,255,0);
  transition: all 500ms ease-out;
}
</style>