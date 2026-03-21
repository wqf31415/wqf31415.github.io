---
title: LuckFoxPico联网与搭建Web服务
tags:
- linux
- luckfox
- C
- 开发板
- 硬件
- 嵌入式
- 网络
- web
- web服务
- IoT
categories:
- 嵌入式
date: 2026-03-21 10:18:45
---

### 概述

这篇文章讲述了将 LuckFox Pico 开发板接入网络，以及使用 mongoose 库编译 web 服务，并在 LuckFox Pico 上运行。



### 组网拓扑

<svg xmlns="http://www.w3.org/2000/svg" style="background: transparent; background-color: transparent; color-scheme: light;" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1" width="281px" height="401px" viewBox="0 0 281 401"><defs/><g><g data-cell-id="0"><g data-cell-id="1"><g data-cell-id="W5FYgok1wJqNMqm_KsO0-3"><g transform="translate(0.5,0.5)"><path d="M 60 340 L 60 306.37" fill="none" stroke="#000000" stroke-miterlimit="10" pointer-events="stroke" style="stroke: rgb(0, 0, 0);"/><path d="M 60 301.12 L 63.5 308.12 L 60 306.37 L 56.5 308.12 Z" fill="#000000" stroke="#000000" stroke-miterlimit="10" pointer-events="all" style="fill: rgb(0, 0, 0); stroke: rgb(0, 0, 0);"/></g></g><g data-cell-id="W5FYgok1wJqNMqm_KsO0-1"><g transform="translate(0.5,0.5)"><rect x="0" y="340" width="120" height="60" rx="9" ry="9" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: rgb(255, 255, 255); stroke: rgb(0, 0, 0);"/></g><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 118px; height: 1px; padding-top: 370px; margin-left: 1px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; white-space: normal; word-wrap: normal; ">LuckFox Pico</div></div></div></foreignObject><text x="60" y="374" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="12px" text-anchor="middle">LuckFox Pico</text></switch></g></g></g><g data-cell-id="W5FYgok1wJqNMqm_KsO0-5"><g transform="translate(0.5,0.5)"><path d="M 60 240 L 60 206.37" fill="none" stroke="#000000" stroke-miterlimit="10" pointer-events="stroke" style="stroke: rgb(0, 0, 0);"/><path d="M 60 201.12 L 63.5 208.12 L 60 206.37 L 56.5 208.12 Z" fill="#000000" stroke="#000000" stroke-miterlimit="10" pointer-events="all" style="fill: rgb(0, 0, 0); stroke: rgb(0, 0, 0);"/></g></g><g data-cell-id="W5FYgok1wJqNMqm_KsO0-2"><g transform="translate(0.5,0.5)"><rect x="0" y="240" width="120" height="60" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: rgb(255, 255, 255); stroke: rgb(0, 0, 0);"/></g><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 118px; height: 1px; padding-top: 270px; margin-left: 1px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; white-space: normal; word-wrap: normal; ">Windows电脑</div></div></div></foreignObject><text x="60" y="274" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="12px" text-anchor="middle">Windows电脑</text></switch></g></g></g><g data-cell-id="W5FYgok1wJqNMqm_KsO0-7"><g transform="translate(0.5,0.5)"><path d="M 120 160 L 153.63 160" fill="none" stroke="#000000" stroke-miterlimit="10" pointer-events="stroke" style="stroke: rgb(0, 0, 0);"/><path d="M 158.88 160 L 151.88 163.5 L 153.63 160 L 151.88 156.5 Z" fill="#000000" stroke="#000000" stroke-miterlimit="10" pointer-events="all" style="fill: rgb(0, 0, 0); stroke: rgb(0, 0, 0);"/></g></g><g data-cell-id="W5FYgok1wJqNMqm_KsO0-9"><g transform="translate(0.5,0.5)"><path d="M 60 120 L 60 86.37" fill="none" stroke="#000000" stroke-miterlimit="10" pointer-events="stroke" style="stroke: rgb(0, 0, 0);"/><path d="M 60 81.12 L 63.5 88.12 L 60 86.37 L 56.5 88.12 Z" fill="#000000" stroke="#000000" stroke-miterlimit="10" pointer-events="all" style="fill: rgb(0, 0, 0); stroke: rgb(0, 0, 0);"/></g></g><g data-cell-id="W5FYgok1wJqNMqm_KsO0-4"><g transform="translate(0.5,0.5)"><path d="M 20 120 L 100 120 L 120 160 L 100 200 L 20 200 L 0 160 Z" fill="#ffffff" stroke="#000000" stroke-miterlimit="10" pointer-events="all" style="fill: rgb(255, 255, 255); stroke: rgb(0, 0, 0);"/></g><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 118px; height: 1px; padding-top: 160px; margin-left: 1px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; white-space: normal; word-wrap: normal; ">路由器</div></div></div></foreignObject><text x="60" y="164" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="12px" text-anchor="middle">路由器</text></switch></g></g></g><g data-cell-id="W5FYgok1wJqNMqm_KsO0-6"><g transform="translate(0.5,0.5)"><rect x="160" y="130" width="120" height="60" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: rgb(255, 255, 255); stroke: rgb(0, 0, 0);"/></g><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 118px; height: 1px; padding-top: 160px; margin-left: 161px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; white-space: normal; word-wrap: normal; ">Ubuntu主机</div></div></div></foreignObject><text x="220" y="164" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="12px" text-anchor="middle">Ubuntu主机</text></switch></g></g></g><g data-cell-id="W5FYgok1wJqNMqm_KsO0-8"><g transform="translate(0.5,0.5)"><path d="M 30 20 C 6 20 0 40 19.2 44 C 0 52.8 21.6 72 37.2 64 C 48 80 84 80 96 64 C 120 64 120 48 105 40 C 120 24 96 8 75 16 C 60 4 36 4 30 20 Z" fill="#ffffff" stroke="#000000" stroke-miterlimit="10" pointer-events="all" style="fill: rgb(255, 255, 255); stroke: rgb(0, 0, 0);"/></g><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 118px; height: 1px; padding-top: 40px; margin-left: 1px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; white-space: normal; word-wrap: normal; ">互联网</div></div></div></foreignObject><text x="60" y="44" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="12px" text-anchor="middle">互联网</text></switch></g></g></g></g></g></g></svg> 

<!-- more -->

### 物料

#### 设备

|        设备         | 操作系统  |            系统版本            |       IP        |                  备注                   |
| :-----------------: | :-------: | :----------------------------: | :-------------: | :-------------------------------------: |
|         PC          |  Windows  |               11               |  192.168.2.176  |      用于烧录系统与远程访问开发板       |
| LuckFox Pico 开发板 | Buildroot | -g2ae728b52-dirty（2023.02.6） | 192.168.137.100 | 开发板，已经插入烧录Buildroot镜像的SD卡 |
|     Ubuntu主机      |  Ubuntu   |           24.04 LTS            |  192.168.2.190  |            完成C代码交叉编译            |

#### 软件

|         软件         |  版本  |            用途            |                           下载链接                           |
| :------------------: | :----: | :------------------------: | :----------------------------------------------------------: |
| Android Debug Bridge | 1.0.41 |     通过USB连接开发板      | [adb_fastboot.zip](https://files.luckfox.com/wiki/Luckfox-Pico/Software/adb_fastboot.zip) |
|      MobaXterm       | v22.0  | 远程连接开发板与Ubuntu主机 | [MobaXterm_Portable_v22.0.zip](https://wiki.luckfox.com/Tools/MobaXterm_Portable_v22.0.zip) |

#### 其他物料

|         物料         |   参数   | 数量 |                 备注                 |
| :------------------: | :------: | :--: | :----------------------------------: |
|         电源         |  5V直流  |  1   |             给开发板供电             |
|        交换机        | 八孔千兆 |  1   |       让电脑、开发板接入局域网       |
| Type-C转网口有线网卡 |   百兆   |  1   | 插在开发板，为开发板提供有线联网功能 |
|     Type-C数据线     |   1米    |  1   |          将开发板连接到PC上          |
|         网线         |   1米    |  1   |       连接Type-C 网卡到交换机        |
|        杜邦线        |    -     |  2   |    连接电源和开发板，给开发板供电    |

### LuckFox Pico接入网络

#### 方式一：USB共享电脑网络（RNDIS）

使用 Windows 电脑网络共享，让开发板的网络共享使用电脑网络，这样就可以让开发板连接到局域网和公网。

##### 使用 ADB 连接开发板

通过 ADB 方式可以直接使用数据线访问开发板，而且不需要输入密码，当开发板因为一些问题（ IP 配置错误）无法使用 ssh 访问时，可以使用这种方式。

> 参考官网文档：[登录 | LUCKFOX WIKI](https://wiki.luckfox.com/zh/Luckfox-Pico-Plus-Mini/Login)

下载 [adb_fastboot.zip](https://files.luckfox.com/wiki/Luckfox-Pico/Software/adb_fastboot.zip) 并解压到本地，记录存放路径，比如 `D:\luckfox\adb_fastboot` ，将路径添加到系统环境变量 path 中。

![](/images/post/luckfox/env_path_cfg.webp) 

打开命令行窗口，运行命令如下命令，能打印出软件版本信息说明配置正确：

```powershell
adb version
```

用数据线将开发板连接到 Windows 电脑，等待开发板启动完成后（约30秒），在命令行窗口执行如下命令查看已接入的设备信息：

```powershell
adb devices
```

输入如下，说明设备连接成功：

```
List of devices attached
b8319ff24268c8a4        device
```

当只有一个设备时，执行如下命令连接：

```cmd
adb shell
```

当有多个设备时，要添加 `-s` 参数指定连接的设备的序列号：

```cmd
 adb -s b8319ff24268c8a4 shell
```

连接成功后，界面显示如下，就可以输入指令和开发板交互了，如执行 `ip addr` 查看开发板 IP 地址。

```
[root@luckfox ]#
[root@luckfox ]# ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
2: usb0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast qlen 1000
    link/ether e2:c3:a2:f0:aa:37 brd ff:ff:ff:ff:ff:ff
    inet 192.168.137.100/24 brd 192.168.137.255 scope global usb0
       valid_lft forever preferred_lft forever
```

##### 配置电脑网络共享

找到 LuckFox Pico 使用的网卡：当用数据线把 LuckFox Pico 开发板连接到电脑后，会出现一个新的网络设备，通常名为“**Remote NDIS based Internet Sharing Device**”或类似名称，在Windows的“网络连接”面板中，找到这个对应的网卡，它可能显示为“**以太网 X**”。

在“网络连接”面板中，找到电脑**正在用来上网**的那张网卡，右键点击它，选择 **“属性”** -> **“共享”** 选项卡。

> 如下图所示：
>
> - 开发板的网卡是 `以太网 3` 
> - 电脑上网的网卡是 `以太网` 

![](/images/post/luckfox/net_adapter.webp) 

勾选 **“允许其他网络用户通过此计算机的 Internet 连接来连接”**，在“家庭网络连接”下拉框中，**选择第一步中识别出的、代表Luckfox Pico的那张虚拟网卡**（例如我的是“以太网 3”）

![](/images/post/luckfox/net_share.webp) 

点击“确定”，Windows会自动为这张虚拟网卡设置一个固定IP：`192.168.137.1`

##### 设置开发板网络

通过 ADB 登录到 LuckFox Pico开发板，将开发板的USB虚拟网卡（通常是`usb0`）配置到与Windows共享网卡相同的网段。

可以逐条执行如下命令设置开发板 IP：

```sh
# 为 usb0 接口设置一个与 Windows 共享网卡同网段的 IP
# 注意：不能使用 192.168.137.1，这个已被电脑占用
ifconfig usb0 192.168.137.100 netmask 255.255.255.0
# 添加默认网关，指向 Windows 共享网卡的 IP
route add default gw 192.168.137.1
# 设置 DNS 服务器，用于域名解析（如 ping baidu.com）
echo "nameserver 114.114.114.114" > /etc/resolv.conf
```

> **注意**：这种方式配置的 IP 会在重启后失效，如果需要持久化，需要编写开机启动脚本，参考官网教程[自启动配置 | LUCKFOX WIKI](https://wiki.luckfox.com/zh/Luckfox-Pico-Plus-Mini/Autostart)，在系统启动时自动修改IP配置：
>
> 在 `/etc/init.d/` 目录下新增并编辑配置静态路由的脚本文件，命名为`S99z_static_ip` （确保该命名在系统脚本之后）
>
> ```sh
> vi /etc/init.d/S99z_static_ip
> ```
>
> 内容如下：
>
> ```sh
> #!/bin/sh
> case $1 in
>   start)
>       ifconfig usb0 192.168.137.100 netmask 255.255.255.0
>       route add default gw 192.168.137.1
>       echo "nameserver 114.114.114.114" > /etc/resolv.conf
>       ;;
>   stop)
>       ;;
>   *)
>       exit 1
>       ;;
> esac
> ```
>
> 给脚本添加可执行权限：
>
> ```sh
> chmod +x /etc/init.d/S99z_static_ip
> ```

在开发板上尝试 ping 局域网其他主机或百度域名 `www.baidu.com` ，能够ping通，说明网络配置成功。

![](/images/post/luckfox/pico_ping_other.webp) 



#### 方式二：USB扩展有线网卡

通过 Type-C 网卡设备，给开发板提供一个网口，连接到局域网交换机或路由器即可上网，注意需要单独提供电源给开发板供电。

##### 修改 USB 模式为 host

开发板 usb 默认是 device 模式，可以通过数据线将开发板连接到电脑，使用 adb 访问。

现在需要将开发板 usb 连接到有线网卡，需要先把 usb 模式修改为 host 模式：

```bash
luckfox-config
```

进入 `Advanced Options` - `USB` ，选择 host，保存，重启生效。

> **注意：usb 设置成 host 模式将导致无法使用 adb 连接，如果IP设置也有问题，就只能使用串口访问了。** 

##### 使用串口连接开发板

<!-- TODO: 待验证 -->



##### 电源供电

将直流电源设置为 5V 1A，正极连接到开发板 `VBUS` 引脚，负极连接到开发板 `GND` 引脚。

启动电源即可自动启动开发板。

 

### 搭建web服务

#### web服务开发

> Mongoose 是一个开源的嵌入式设备的 Web 服务器项目，可作为嵌入式设备网络库，使用 C 语言开发。
>
> Github 地址：<https://github.com/cesanta/mongoose> 

从 GitHub 克隆 mongoose 项目源码：

```bash
git clone https://github.com/cesanta/mongoose.git
```

创建 web 服务项目目录，从源码仓库根目录复制 `mongoose.h` 、`mongoose.c` 到 web 服务项目目录，创建 `main.c` 文件，实例代码将在 `8000` 端口开启 web 服务，代码内容如下：

```c
#include <stdio.h>
#include "mongoose.h"

static const char *s_http_addr = "http://0.0.0.0:8000"; // 在 8000 端口监听 HTTP 请求
static const char *s_root_dir = "web_root";

static void fn(struct mg_connection *c, int ev, void *ev_data) {
  if(ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    if(mg_match(hm->uri, mg_str("/hello"), NULL)) {
      // 解析查询参数中的 name 字段，并返回 JSON 格式的响应
      char name[64] = {0};
      mg_http_get_var(&hm->query, "name", name, sizeof(name));
      mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"msg\":\"hello %s!\"}", name);
    } else {
      // 其他请求，返回静态文件
      struct mg_http_serve_opts opts = {.root_dir = s_root_dir};
      mg_http_serve_dir(c, ev_data, &opts);
    }
  }
}

int main(void) {
  struct mg_mgr mgr;
  mg_log_set(MG_LL_DEBUG);
  mg_mgr_init(&mgr);
  mg_http_listen(&mgr,s_http_addr, fn, NULL);
  for (;;) mg_mgr_poll(&mgr, 1000);
  mg_mgr_free(&mgr);
  return 0;
}
```

在 web 服务目录中创建 `web_root` 目录，用于存放前端文件 `index.html` ，文件内容如下：

```html
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Hello World</title>
</head>
<body>
    <h1>hello world</h1>
</body>
</html>
```

#### 编译部署

编译项目源码：

```bash
arm-rockchip830-linux-uclibcgnueabihf-gcc main.c mongoose.c -o web
```

将 web 服务资源和可执行文件打包成 tar 包：

> 开发板的 tar 命令不支持解压 .gz 文件，所以只能打包成 tar 包。

```bash
tar -cf web_server.tar web web_root/
```

导出 tar 包并上传到开发板，解压 tar 包，运行 web 服务：

```bash
tar -xf web_server.tar
./web
```

#### 访问服务

##### 共享电脑网络方式

在 Windows 电脑上打开浏览器，访问开发板 8000 端口的 web 服务：<http://192.168.137.100:8000/> ，显示 web 服务的主页 index.html。

![](/images/post/luckfox/pico_web_index.webp) 

访问web服务的接口，传入name 参数，<http://192.168.137.100:8000/hello?name=LuckFox> ，返回接口响应 json 数据：

```json
{"msg":"hello LuckFox!"}
```

现在在 Windows 电脑上可以访问开发板上的 web 服务了，如果想要让局域网其他设备访问，可以在 Windows 电脑上使用 ssh 建立和开发板的隧道：

```bash
ssh -N -L 192.168.2.176:8080:192.168.137.100:8000 root@192.168.137.100
```

>命令说明：这个 `ssh` 命令用于建立一个 **SSH 隧道**，实现**本地端口转发**，将本地机器上的一个端口（8080）通过 SSH 连接转发到远程主机上的另一个端口（8000）。
>
>具体参数说明：
>
>- **`ssh`**：SSH 客户端命令，用于建立安全的远程连接。
>- **`-N`**：表示**不执行远程命令**。仅建立连接并用于端口转发，不打开远程 shell 或执行任何命令。
>- **`-L`**：指定**本地端口转发**（Local Forwarding）。其语法为 `[bind_address:]port:host:hostport`，含义是：将本地（或指定接口）的 `port` 上的流量，通过 SSH 隧道转发到远程主机（即 SSH 服务器）所见的 `host:hostport`。
>- **`192.168.2.176:8080:192.168.137.100:8000`**：这是 `-L` 的参数，具体含义：
>  - `192.168.2.176:8080`：在本地机器上，监听 IP 地址为 `192.168.2.176`（这是一个本地网络接口）的 **8080 端口**。这意味着只有从该 IP 地址访问本地 8080 端口的连接才会被转发。
>  - `192.168.137.100:8000`：通过 SSH 隧道，将流量转发到远程主机（即 SSH 服务器）所能访问到的 `192.168.137.100` 的 **8000 端口**。
>- **`root@192.168.137.100`**：指定登录到远程 SSH 服务器，用户名为 `root`，服务器地址为 `192.168.137.100`。

其他设备可以访问 <http://192.168.2.176:8080> 来访问开发板上的 web 服务。

### 总结

- 通过共享主机网络，可以让开发板通过数据线接入到网络，能够访问局域网和公网。但是要让局域网其他设备访问开发板不太容易，我在 Windows 电脑上配置路由转发，但是没有生效。
- 使用 USB 网卡通过有线方式将 LuckFox Pino 连入网络，但需要单独提供电源，通过 VBUS、GND 引脚供电。
