---
title: ESP8266初体验 hello world
date: 2019-09-15 14:30:02
tags:
- IoT
- esp8266
categories:
- Arduino
---

### 写在前面

近期在 B站 上看到了一些使用 esp8266 开发板制作小东西的视频，有 wifi 杀手、实时显示B站粉丝数、显示天气信息等等，而一块 esp8266 开发板才十几块钱，也就一顿饭钱，于是心痒痒上淘宝买了一块来玩玩，花了两小时下软件和资源类库，花了半小时调通一个 hello world 代码，把其中过程记录一下。



### 概要

本文主要内容包括购买 ESP8266 开发板，安装与配置开发使用的 Arduino IDE，使用 Arduino 编写一个 hello world 代码，然后烧录到 ESP8266 中，使用 Arduino 查看串口输出结果。



### 什么是 ESP8266

ESP8266 是 [乐鑫信息科技公司](https://www.espressif.com/) 开发的一款 wifi 模块，具有低功耗、高集成度的 wifi 芯片，内封了 8 Mbit 的 Flash，集成了低功耗的 32 位 <abbr title="微控制单元(Microcontroller Unit；MCU)">MCU</abbr>，带有 16 位精简模式，主频支持 80 MHz 和 160 Mhz，支持 RTOS，支持标准 IEEE802.11 b/g/n 协议，完整的 TCP/IP 协议栈。用户可以使用该模块为现有的设备添加联网功能，也可以构建独立的网络控制器。

简单来说就是一个 wifi 模块，可以通过 wifi 联网或提供 wifi 服务，带了一个微处理器，我们可以写入自己的程序，比如联网调取 bilibili 接口获取用户粉丝数量，并通过 LCD 屏显示出来。

![](http://blog-images.qiniu.wqf31415.xyz/esp8266_board.png "ESP8266 开发板")



<!-- more-->



### 购买 ESP8266 开发板

可以上京东或淘宝购买，直接搜索 “ESP8266开发板”，如上图，可以直接使用 安卓数据线接入电脑使用。注意：一般直接搜索 “ESP8266” 找到的是 wifi 模块（如下图），需要另外使用烧录工具，会稍微麻烦一点。

![](http://blog-images.qiniu.wqf31415.xyz/esp8266_wifi_module.png "ESP8266 wifi 模块")



### 安装开发工具 Arduino IDE

到 Arduino 官网下载 IDE 安装包，支持 Windows、Linux、MacOS，其中对于 Win 8.1 或 Win 10 系统，可以直接在 [微软应用商店](https://www.microsoft.com/zh-cn/p/arduino-ide/9nblggh4rsd8?ocid=badge&rtc=1#activetab=pivot:overviewtab) 安装。

> 中文官网：<https://www.arduino.cn/>
>
> 英文官网：<https://www.arduino.cc/>



### 配置 ESP8266 开发环境

#### 添加 ESP8266 开发板管理地址

打开 Arduino IDE，点击 **“文件” - “首选项”** ，或使用默认快捷键 <kbd>Ctrl</kbd> + <kbd>逗号</kbd> 打开首选项设置界面，在其中 “附加开发板管理地址” 中填入以下地址，点 “好” 确认：

```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

![](http://blog-images.qiniu.wqf31415.xyz/esp8266_arduino_preferences.png)



#### 下载安装 ESP8266 开发板模块

点击 Arduino 菜单栏 **“工具” - “开发板” - “开发板管理器”** ，搜索 `esp8266` ，找到 **ESP8266 Community** ，选择一个版本进行安装，我安装的是 2.5.0 版本。安装包不大，但由于网络原因，可能会有点慢，我下载了快两小时才下载完。

![](http://blog-images.qiniu.wqf31415.xyz/esp8266_arduino_board_manage.png)



#### 查看 ESP8266 开发板选项

重启 Arduino ，点击菜单栏 **“工具” - “开发板”** ，看到 ESP8266 开发板相关的选项，说明安装正确。



### 连接 ESP8266 开发板

使用安卓数据线将 ESP8166 开发板连接到电脑上，通电时，开发板灯会闪烁一下。

连接后打开设备管理器（Windows系统），看到 **端口（COM 和 LPT）** 选项中有如下图的设备，说明已经连接成功，同时可以确定连接的串口号，如下图的是 `COM3` 。

![](http://blog-images.qiniu.wqf31415.xyz/esp8266_connect_computer.png)

> 值得注意的是，上图中显示的 CH340，如果没有显示这个设备，可能是因为驱动没安装好，可以上百度搜索 `CH340驱动` ，下载安装好之后才能够实现电脑与开发板通信，才能上传程序代码。

### Hello world！

> 一般硬件开发的第一个程序都是点灯，但是我是搞软件出身的，所以就想写一个输出 hello world 的程序。。。

#### 程序代码

打开 Arduino 点击 **“工具” - “开发板”** ，选择 **Generic ESP8266 Module** 。

点击 **“文件” - “新建”** ，在新的文件中写入如下代码，其中 `//` 开头的是注释信息，可以忽略。写完记得保存，要保存才能上传到开发板。

```c++
void setup() {
  // put your setup code here, to run once:
  // 开启串行通信接口并设置通信波特率
  Serial.begin(115200);
}

void loop() {
  // put your main code here to run repeatedly:
  // 写入字符串数据+换行到串口
  Serial.println("Hello world!");
  // 延迟 2000ms
  delay(2000);
}
```



#### 上传代码

设置一下上传参数，我的 ESP8266 上传时修改了一下参数，其它参数是默认的，以下仅供参考：

点击 **“工具” - “端口”** ，选择刚才在设备管理中看到的串口。

点击 **“工具” - “Reset Method”** ，选择 **nodemcu** 。

点击 **“工具” - “Upload Speed”** ，选择 **115200** 。

点击 Arduino 工具栏中的 **上传** 图标，将写的程序烧录到 ESP8266 中，期间 ESP8266 的指示灯会一直闪烁，在 Arduino 控制台中会显示上传进度，上传到 100% 就可以查看效果了。

![](http://blog-images.qiniu.wqf31415.xyz/esp8266_upload.png)



#### 查看结果

点击 **“工具” - “串口监视器”**，或使用默认快捷键 <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>M</kbd> 打开串口监视器，在串口监视器窗口中设置波特率为 `115200` ，可以看到每隔 2 秒会打印一句 `Hello world!` 

![](http://blog-images.qiniu.wqf31415.xyz/esp8266_arduino_com_output.png)



### 遇到的问题

#### 下载开发板模块包时速度慢

可以找一个网速快的地方下啊，也可以想办法科学上网，实在不行可以找别人下载好的，直接拷贝到资源目录下。



#### 上传程序失败

可能是 USB 转串口的驱动程序没安装好，据说市面上 ESP8266 有两种 USB 转串口芯片，一种是 ch340，一种是 cp2102，可以根据自己的开发板情况，下载不同的驱动安装到电脑上，推荐到安信可官网下载相关驱动： <https://wiki.ai-thinker.com/tools> 。

可能是因为上传速度(Upload Speed)、重启方法(Reset Method)、端口选择错误，按 hello world 示例中的设置方式设置试试看吧！



#### 不知道代码怎么写

点击 Arduino 菜单栏 **“工具” - “开发板” - “Generic ESP8266 Module”** ，然后点击 **“文件” - “示例”** ，就可以找到很多示例代码，可以通过这些示例学习代码编辑。

另外，可以上 [哔哩哔哩](https://search.bilibili.com/all?keyword=esp8266&from_source=banner_search) 看看大神们的教程，不仅能够学到代码，还能见识到各种新奇的用法，增长见识。



#### 从哪获得固件资源

首先，可以从购买 ESP8266 的卖家那里获取固件、烧录工具，烧录有问题的话可以咨询卖家。

其次，可以在 <https://nodemcu-build.com/> 在线构建 nodemcu 固件。

最后，还可以上安信可官网或者贴吧、论坛寻找其他玩家提供的固件。



### 小结

这篇文章是 ESP8266 小白——我的初次体验，实现了循环打印信息到串口中，涉及的内容都非常简单，适合初次接触的人看看。虽然整体功能比较简单，但却是很重要的信息输出方式，以后写程序调试时，可以通过这种方式打印运行日志。ESP8266 的总体体验感觉还可以，没踩太多坑，买板子的时候同时还买了一块 OLED 屏，下次试试把文字输出到屏幕上。

