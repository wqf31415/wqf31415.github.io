---
title: esp8266 远程点灯
date: 2025-09-01 01:06:00
tags:
- IoT
- esp8266
- ESPHome
- 开发板
- 硬件
- HomeAssistant
categories:
- HomeAssistant
---

### 概述

ESP8266 作为远程控制器，接入 Home Assistant，实现从 Home Assistant 远程控制开关 LED 灯。这篇文章介绍了使用 ESPHome 从配置文件生成 ESP8266 固件，然后使用乐鑫官方提供的烧录工具烧录固件到板卡，最后将ESP8266 接入到 Home Assistant 进行开关灯控制。



### 远程控制原理

在局域网中搭建 Home Assistant 和 ESPHome 服务，ESP8266 设备烧录固件后通过 wifi 接入网络，自动识别添加到 Home Assistant。


<!-- more -->

### 核心组件与概念

#### ESP8266

ESP8266 官方介绍: <https://www.espressif.com.cn/zh-hans/products/socs/esp8266> 

> ESP8266 是 [乐鑫信息科技公司](https://www.espressif.com/) 开发的一款 wifi 模块，具有低功耗、高集成度的 wifi 芯片，内封了 8 Mbit 的 Flash，集成了低功耗的 32 位 <abbr title="微控制单元(Microcontroller Unit；MCU)">MCU</abbr>，带有 16 位精简模式，主频支持 80 MHz 和 160 Mhz，支持 RTOS，支持标准 IEEE802.11 b/g/n 协议，完整的 TCP/IP 协议栈。用户可以使用该模块为现有的设备添加联网功能，也可以构建独立的网络控制器。

#### 固件烧录工具

乐鑫官网提供的模组固件烧录工具，支持乐鑫所有芯片模组的固件烧录。

Flash 下载工具用户指南：<https://docs.espressif.com/projects/esp-test-tools/zh_CN/latest/esp8266/production_stage/tools/flash_download_tool.html> 

#### ESPHome

ESPHome: <https://esphome.io/> 

ESPHome 是一个开源的固件框架，可用于配置和管理基于 ESP8266 、ESP32、RP2040 等微控制器的智能家居设备。它通过简单的 YAML 配置文件来简化设备的设置和集成过程，使得用户无需编写复杂的代码即可实现设备的自定义和控制。支持接入Home Assistant、GoogleHome 等智能家居平台，提供自动发现功能。

#### Home Assistant

Home Assistant: <https://www.home-assistant.io/> 

Home Assistant（简称 HA）是一款开源的智能家居自动化平台，专注于本地化控制、隐私保护和多设备兼容性。它允许用户将不同品牌的智能设备整合到一个统一的系统中，并通过自动化规则实现设备联动。

#### Docker

Docker: <https://www.docker.com/> 

Docker 是一个开源的容器化平台，用于开发、部署和运行应用程序。它允许开发者将应用及其依赖打包成轻量级、可移植的容器，确保应用在不同环境中一致运行。

### 实现流程

#### 基础环境

这次测试用到了 3 台主机，一台 Windows 主机用于访问和操作 Home Assistant 与 ESPHome 界面，同时用于连接 ESP8266 开发板进行固件烧录。一台 Linux 小主机安装了 docker 与 docker-compose 用于运行 ESPHome。第三个设备是退休的玩客云，刷了 armbian 系统，安装 Home Assistant。

|                    |   主机1   |  主机2   |   主机3    |
| :----------------: | :-------: | :------: | :--------: |
|      操作系统      | Windows 10 | Ubuntu 24.04 | armbian 12 |
|        内存        |   16G     |    4G    |     1G     |
|        硬盘        |    1T     |   64G    |     8G     |
|     docker版本     |    无     |  28.1.1  |   28.1.1   |
| docker-compose版本 |    无     |  v2.33.1  |     无     |
|         IP         |     -     | 192.168.2.202 | 192.168.2.243 |

#### ESPHome 环境准备

由于我的 Home Assistant 是用 docker 安装的，容器版的 Home Assistant 不支持扩展功能，无法直接在扩展中安装 ESPHome，因此使用 docker 在 Linux 小主机上单独安装 ESPHome。

> 官方的安装指导：<https://esphome.io/guides/getting_started_command_line/> 

由于国内访问 docker 仓库网络受阻，通过 github 从 docker 官方仓库下载了 ESPHome 的镜像 `esphome/esphome`，版本是 `stable` ，上传到 linux 小主机，执行指令 `docker load -i esphome_esphome_stable-amd64.tar.gz` 加载镜像。

创建文件路径，包括存放 docker-compose 配置文件目录、esphome 配置目录：

```bash
mkdir -p docker-compose/esphome
cd docker-compose/esphome
mkdir config
```

编辑 docker-compose 配置文件，`vim esphome.yml` ，内容如下：

```yaml
version: '3'
services:
  esphome:
    image: esphome/esphome:stable
    privileged: true
    volumes:
      - /data/esphome/config:/config
      - /etc/localtime:/etc/localtime:ro
    privileged: true
    network_mode: host
    environment:
      - USERNAME=admin
      - PASSWORD=123456
    restart: unless-stopped
```

运行 ESPHome 容器：

```bash
docker-compose -f esphome.yml up -d
```

运行成功后，打开浏览器，访问主机的 6052 端口验证是否成功启动，我的访问地址是：http://192.168.2.202:6052 ，登录用户名密码是 decker-compse.yml 中设置的，我这里的用户名是 admin，密码是 123456。

> 推荐使用最新版本的谷歌浏览器或edge浏览器，使用国产360急速浏览器发现设备配置编辑、加密信息页面打开是空白的。

![](/images/post/esp8266/esphome_page_home.png)

#### 使用 ESPHome 生成 ESP8266 固件

进入到eshome页面，点击页面中 `+ NEW DEVICE` 按钮，添加新设备，弹框提示需要通过usb将设备接入电脑，我们点击继续 `CONTINUE` 按钮。

![](/images/post/esp8266/esphome_add_device.png) 


页面弹框提示需要输入设备名称、网络名称和密码，我这里设定设备名称为 `test-001`，网络名称为我家的WiFi名称，密码为WiFi密码。点击 `NEXT` 。

![](/images/post/esp8266/esphome_create_device_config.png) 

页面弹框显示需要选择设备类型，这里点击选项 `ESP8266`。

![](/images/post/esp8266/esphome_create_device_type.png) 

页面弹框显示配置已创建，并显示了一个秘钥，把这个秘钥复制保存下来，点击 `INSTALL` 按钮。

![](/images/post/esp8266/esphome_create_device_config_ok.png) 

页面提示选择安装配置到设备的方式，这里是第一次安装，需要选择 `Manual download`，即手动下载安装。

![](/images/post/esp8266/esphome_create_device_install_select.png) 

页面弹出编译固件界面，这里需要从网络下载需要的包，并完成固件编译，编译完成后触发浏览器下载文档到本地。

![](/images/post/esp8266/esphome_create_device_install_compile_finish.png) 

#### 烧录固件到 ESP8266 开发板

将 ESP8266 设备连接到电脑上，我这里是连接在串口3上。

打开从乐鑫官网下载的固件烧录程序，弹框提示选择烧录固件的芯片类型，Chip Type 选择 `ESP8266` ，WorkMode 选择 `Develop` ，点击 `OK` 进入烧录界面。

![](/images/post/esp8266/flash_download_tool_start.png) 

选择下载的固件文件，地址填 `0x00`，`COM` 端口选择ESP8266 连接的串口 `COM3`，点击 `START` 开始烧录。

![](/images/post/esp8266/flash_download_tool_down.png) 

等待一会，烧录完成后界面显示 `FINISH完成` 。按一下板卡上的 `RST` 按钮，或断电重连。

![](/images/post/esp8266/flash_download_tool_down_finish.png) 

#### 添加设备到HomeAssistant

登录到 HomeAssistant 页面，发现有新的通知，点击查看。

![](/images/post/esp8266/home_assistant_notice.png) 

HomeAssistant通知提示在网络中发现新的设备，我们点击 `Check it out` ，进入设备配置页面。

![](/images/post/esp8266/home_assistant_notice_content.png) 

在HomeAssistant的设备配置页面中有一个标记为 `已发现` 的设备，点击 `配置` 按钮，提示是否要添加到 HomeAssistant，点击 `提交`。

![](/images/post/esp8266/home_assistant_find_esphome_device.png) 

弹框提示需要输入设备加密秘钥，我们将上一步获取到的设备秘钥填入，点击 `提交` ，这样设备就被添加到了 HomeAssistant 中。

#### 添加控制LED的配置

登录到 esphome 页面，页面中显示了添加的设备，且设备显示状态为在线 `ONLINE` ，点击 `EDIT` 按钮编辑设备配置。

![](/images/post/esp8266/esphome_device_list.png) 

在配置编辑页面中添加如下配置，点击 `SAVE` 按钮或按 Ctrl+S 快捷键保存配置，点击 `INSTALL` 按钮安装到设备。

```yaml
switch:
  - platform: gpio
    pin: GPIO02
    name: "LED BUILTIN"
```

![](/images/post/esp8266/esphome_device_edit.png) 

弹框提示选择安装配置的方式，点击 `Wirelessly` 无线安装。

> 设备已经通过无线方式注册到 esphome 中了，所以可以使用 ota 方式进行升级。

![](/images/post/esp8266/esphome_device_config_install.png) 

等待编译完成，完成后 esphome 会通过WiFi将固件包传给ESP8266，并完成安装。

![](/images/post/esp8266/esphome_create_device_config_install.png) 

#### 验证远程控制点灯

等待esphome将修改后的配置安装到设备后，设备会自动重启，不需要再手动按 RST按键。

登录 HomeAssistant 页面，在概览页面找到添加的设备，发现开关按钮和状态显示，点击开关按钮，查看ESP8266板卡上的LED，发现通过HomeAssistant页面上的按钮可以控制板载LED灯的亮和灭。

![](/images/post/esp8266/home_assistant_esp8266_led_switch.png) 

> 但是这里有个问题，HomeAssistant页面显示的开关状态和灯的状态是相反的，即页面显示是关，ESP8266上的灯是亮的。原因是我们使用ESP8266的2号引脚控制板载LED，这个引脚为高电平时LED灯熄灭，这个引脚为低电平时LED灯点亮。

#### 优化配置

esphome 的开关提供了状态逆转配置项 `inverted` ，添加这个配置项并将其设置为 `true` ，重新安装到设备，发现开关控制状态和板载LED灯状态一致。

完整配置内容如下：

```yaml
esphome:
  name: test-001
  friendly_name: test_001

esp8266:
  board: esp01_1m

# Enable logging
logger:

# Enable Home Assistant API
api:
  encryption:
    key: "iWlG3sG+FXXhp+9xPFR8IpCxPvQW+gweZ47ijvjZRR0="

ota:
  - platform: esphome
    password: "9c546b72baa8ca4b339253548fd7c839"

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password

  # Enable fallback hotspot (captive portal) in case wifi connection fails
  ap:
    ssid: "Test-001 Fallback Hotspot"
    password: "QLlqZI6DKXSD"

captive_portal:
switch:
  - platform: gpio
    pin: GPIO02
    name: "LED BUILTIN"
    inverted: True
```

### 总结

这篇文章中涉及到的知识点包括： 
- 使用 Docker 运行 ESPHome 容器，将 ESPHome 接入到 Home Assistant。
- 使用 ESPHome 生成 ESP8266 开发板固件，修改 ESPHome 的配置脚本，添加控制板载 LED 的控制开关配置。更多的配置选项可参考 esphome 官方文档。
- 使用乐鑫官方Flash烧录工具给 ESP8266 烧录固件，操作方式可扩展到 ESP32 开发板。
- 更多玩法：参考 ESPHome 官方文档，添加传感器，采集传感器数据上报到 Home Assistant。
