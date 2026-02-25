---
title: LuckFoxPico开发板初试
date: 2026-02-25 12:33:00
tags:
- linux
- luckfox
- C
- 开发板
- 硬件
- 嵌入式
categories:
- 嵌入式
---

### 概述

这篇文章记录了 LuckFox Pico 开发板的初始化过程。



### 关于 LuckFox Pico 开发板

> 官网：<https://www.luckfox.com/> 
>
> 官网 LuckFox Pico 介绍：<https://www.luckfox.com/EN-Luckfox-Pico> 
>
> 官网文档：<https://wiki.luckfox.com/zh/Luckfox-Pico-RV1103> 

LuckFox Pico 开发板是一款高性价比的 Linux 微开发板，基于 Rockchip RV1103 芯片，为开发者提供了一个简单且高效的开发平台，支持多种接口包括 MIPI CSI、GPIO、UART、SPI、I2C、USB 等，方便快速开发和调试。

| 组件 | 参数 |
|:--:|:--:|
|处理器|Cortex A7@1.2GHz + RISC-V|
|NPU|0.5TOPS, supports int4, int8 and int16|
|ISP|Input 4M @30fps (Max)|
|内存|64MB DDR2|
|USB|USB 2.0 Host/Device|
|Camera|MIPI CSI 2-lane|
|GPIO|24 × GPIO pins|
|Ethernet port|10/100M Ethernet controller and embedded PHY|
|Default Storage|TF card (Not included)|

<!-- more -->

### 物料

#### 设备

| 设备 | 操作系统 | 系统版本 | IP | 备注 |
|:--:|:--:|:--:|:--:|:--:|
|PC|Windows|11|192.168.2.102、172.32.0.100|用于烧录系统与远程访问开发板|
|LuckFox Pico 开发板|Buildroot|-g2ae728b52-dirty（2023.02.6）|172.32.0.93|开发板|
|Ubuntu主机|Ubuntu|24.04 LTS|192.168.2.201|完成C代码交叉编译|

#### 工具软件

> 以下软件可以从 LuckFox 官网下载：<https://wiki.luckfox.com/zh/Luckfox-Pico-RV1103/Downloads> 

| 软件 | 版本 | 用途 | 备注 |
|:--:|:--:|:--:|:--:|
|DriverAssitant|v5.13|用于安装 RK 驱动||
|SD Card Formatter|5.0.2|格式化 TF 卡||
|SocToolKit|v1.98_win|烧录操作系统到内存卡中|RV1103/RV1106 镜像烧录工具|
|MobaXterm|v22.0|远程连接开发板与Ubuntu主机||

#### 其他物料

| 物料 | 参数 | 数量 | 备注 |
|:--:|:--:|:--:|:--:|
|MicroSD卡|16G|1|用于烧录操作系统|
|Type-C数据线|1米|1|将开发板连接到PC上|
|TF卡读卡器|-|1|将内存卡连接到电脑，用于格式化内存卡和烧录系统|

### 烧录镜像

> 参考官网文档: <https://wiki.luckfox.com/zh/Luckfox-Pico-Plus-Mini/Flash-image> 

LuckFox Pico 开发板没有 SPI NAND Flash 存储器，所以必须烧录操作系统到 MicroSD 卡上，才能使用。

#### 安装驱动

下载 RK 驱动助手 DriverAssitant，运行后点击“安装驱动”。

#### 烧录Buildroot镜像到内存卡

下载用于 LuckFox Pico 开发板的镜像 Luckfox_Pico_MicroSD_250313，将镜像解压出来。

解压安装 TF 卡擦除工具 SD Card Formatter，将内存卡连接到电脑上，选择 TF 卡盘符，点击 Format。

右键管理员身份运行 SocToolKit 烧录工具，选择 RV1106，切换到 `SD卡工具`。

将 SD 卡插入读卡器并连接至电脑，此时会在 USB 磁盘下会显示 SD 卡大小。

选择 `SD启动`。

点击 `选择启动文件`，进入系统镜像目录，选择除了 `update.img` 之外的所有 `.img` 文件。

点击 `创建 SD`，等待写入完成，当提示 `创建SD卡成功` 说明系统烧录完成。

弹出内存卡，将内存卡插到 LuckFox Pico 开发板上。

### SSH远程访问

用数据线将 LuckFox Pico 开发板连接到电脑，点击板卡上的 `BOOT` 按钮启动开发板。

打开 Windows 电脑设置，进入 “网络和Internet” -> “以太网”，找到一个 `未识别的网络`，描述信息是 `Remote NDIS based Internet Sharing Device` ，在 “IP分配” 项中点击编辑，将 `自动(DHCP)` 修改为 `手动`，开启 `IPv4`，IP地址设置为 `172.32.0.100`，子网掩码设置为 `255.255.0.0`，保存配置。

打开 MobaXterm 软件，创建 SSH 连接，Remote host 为 `172.32.0.93`，勾选 `Specify username` 并填写用户名 `root`，点击 OK，输入密码 `luckfox` 回车。

### Hello world

在开发板上运行一个输出 Hello world 的程序，需要在 Ubuntu 主机上使用交叉编译工具链编译 Buildroot 系统的可执行程序。

> 参考官网文档：<https://wiki.luckfox.com/zh/Luckfox-Pico-Plus-Mini/Cross-Compile> 

#### 准备交叉编译工具链

从 LuckFox 官网下载 Buildroot 系统的交叉编译工具链，下载的是一个压缩包，名为：`arm-rockchip830-linux-uclibcgnueabihf.tar.gz` 。

使用 MobaXterm 软件 SSH 登录到 Ubuntu 主机，通过 MobaXterm 软件自带的 SFTP 将下载的交叉编译工具链压缩包上传到 Ubuntu 主机上，我主机上存放工具的路径是 `/home/wqf31415/tools/`。

将编译工具链解压到当前目录：

```bash
tar -zxvf arm-rockchip830-linux-uclibcgnueabihf.tar.gz
```

执行命令 `vim ~/.bashrc` 修改 `~/.bashrc` 文件，在文件最后面添加如下内容(注意下述的路径要根据交叉编译工具链的实际路径修改)：

```
export PATH=/home/wqf31415/tools/arm-rockchip830-linux-uclibcgnueabihf/bin:$PATH
```

更新环境变量，执行以下命令使配置生效：

```bash
source ~/.bashrc
```

#### 编写代码

编写 `hello.c` 文件，内容如下：

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello world\n");
    return 0;
}
```

#### 编译代码

##### 方式一：直接编译

在代码文件目录中，运行如下命令进行交叉编译，编译完成后在当前目录下生成可执行文件 `hello`：

```bash
arm-rockchip830-linux-uclibcgnueabihf-gcc hello.c -o hello
```

##### 方式二：Makefile

在代码文件目录中创建 `Makefile` 文件，内容如下：

```Makefile
CC := /home/wqf31415/tools/arm-rockchip830-linux-uclibcgnueabihf/bin/arm-rockchip830-linux-uclibcgnueabihf-gcc

hello:hello.c
        -$(CC) $^ -o $@

clean:
        rm -f hello
```

运行命令 `make` 完成编译，完成后将在当前目录下生成可执行文件 `hello` 。

> 运行命令 `make clean` 可清除生成的可执行文件 `hello` 。

#### 运行

使用 MobaXterm 软件的 SFTP 将 Ubuntu 主机上编译得到的可执行文件下载到 Windows 电脑本地，再用 MobaXterm 软件的 SFTP 将可执行文件上传到 LuckFox Pico 开发板上，在文件目录执行如下命令给文件添加可执行权限：

```bash
chmod +x hello
```

运行可执行文件，打印出 `Hello world` 说明运行成功：

```bash
./hello
```

### 总结

- LuckFox 官方文档支持中文，而且写的很详细，对于初学者非常友好，这篇文章中的操作完全参考官方文档完成。
- 官方文档中将使用 RV1103 芯片的一系列开发板的文档放在一起的，需要注意各种开发板的网口和存储介质有差异，导致使用方法有所不同，比如 LuckFox Pico 没有 SPI NAND FLASH，需要将操作系统烧录到 MicroSD 卡中；LuckFox Pico 没有网口，需要使用 Type-C 连接到电脑，配置 RNDIS 虚拟网卡才能用 SSH 远程登录。
- 在配置交叉编译工具链时，通过修改 `~/.bashrc` 文件将工具链路径添加到了当前用户的 PATH 中，所以当前用户可以在任意路径下直接调用编译工具 `arm-rockchip830-linux-uclibcgnueabihf-gcc` ，需要注意这个配置仅对当前用户生效，如果切换到其他用户，直接调用编译工具会报错，比如运行 `sudo arm-rockchip830-linux-uclibcgnueabihf-gcc` 会提示 `command not found`。
