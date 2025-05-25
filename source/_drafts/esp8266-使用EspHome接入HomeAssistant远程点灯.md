---
title: esp8266 远程点灯
date: 2025-05-25 18:00:00
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
|      操作系统      | Windows 10 | CentOS 7 | armbian 12 |
|        内存        |   16G     |    4G    |     1G     |
|        硬盘        |    1T     |   64G    |     8G     |
|     docker版本     |    无     |  1.13.1  |   28.1.1   |
| docker-compose版本 |    无     |  1.18.0  |     无     |
|         IP         |     -     | 192.168.1.8 | 192.168.1.10 |

#### ESPHome 环境准备

由于我的 Home Assistant 是用 docker 安装的，容器版的 Home Assistant 不支持扩展功能，无法直接在扩展中安装 ESPHome，因此使用 docker 在 Linux 小主机上单独安装 ESPHome。

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
      - ./config:/config
    ports:
      - "6052:6052"
    restart: unless-stopped
```

运行 ESPHome 容器：

```bash
docker-compose -f esphome.yml up -d
```

运行成功后，打开浏览器，访问主机的 6052 端口验证是否成功启动，我的访问地址是：http://192.168.1.8:6052 

> 推荐使用最新版本的谷歌浏览器，使用国产360急速浏览器发现设备配置编辑、加密信息页面打开是空白的。

#### 将 ESPHome 添加到 Home Assistant

登录 Home Assistant，进入 “设置”-“设备与服务”，点击 “添加集成”，搜索 “ESPHome” 点击搜索到的项，在 ESPHome 的节点连接配置中输入安装 ESPHome 的主机 IP、端口，我的主机IP是 `192.168.1.8`，端口是默认的 `6053` ，点击“提交”。

在 Home Assistant 的“设置”-“设备与服务”页面，选择“集成”选项卡，发现有一个“ESPHome”，说明配置成功。后面的 ESP8266 设备将自动发现添加到 Home Assistant 中。

#### 使用 ESPHome 生成 ESP8266 固件

#### 烧录固件到 ESP8266 开发板

#### 验证远程控制点灯

### 总结

这篇文章中涉及到的知识点包括： 
- 使用 Docker 运行 ESPHome 容器，将 ESPHome 接入到 Home Assistant。
- 使用 ESPHome 生成 ESP8266 开发板固件，修改 ESPHome 的配置脚本，添加控制板载 LED 的控制开关配置。
- 使用乐鑫官方Flash烧录工具给 ESP8266 烧录固件，操作方式可扩展到 ESP32 开发板。
