---
title: 网络抓包分析工具——Wireshark
date: 2020-6-3 21:55:32
tags:
- 工具
- 网络
categories:
- 工具
---

### 概述

这篇文章介绍了最常用的网络抓包工具——Wireshark 的简单使用方法，还讲解了一些相关概念。



### Wireshark 是什么

> 官方网站：<https://www.wireshark.org/> 

Wireshark 是开源的、世界上使用最广泛的网络抓包分析工具，可以从微观角度查看网络上发生的事情，是许多商业、非盈利企业、政府和教育机构的标准。Wireshark 可以用来解决网络问题，检查网络安全，验证网络应用，调试协议实现，还可以用来学习网络协议内部。

<!-- more -->



### Wireshark 的功能与特性

- 深入检查数百种协议，还在不断增加
- 即可实时捕获，也可以离线分析
- 标准三窗格数据包浏览器
- 多平台支持：Windows、Linux、macOS、Solaris 等多种操作系统
- 捕获的网络数据可以通过 GUI 或 TTY 模式的 TShark 使用程序进行浏览
- 业界最强大的显示过滤器
- 丰富的 VolP 分析
- 读取/写入许多不同的捕获文件格式：tcpdump、Pcap NG、Catapult DCT2000、Microsoft Network Monitor 等多种文件格式
- 使用 gzip 压缩的捕获文件可以即时解压缩
- 可以从以太网、IEEE 802.11、PPP/HDLC、ATM、蓝牙、USB、令牌环、帧中继、FDDI 等读取实时数据
- 对许多协议的解密支持，包括 IPsec、ISAKMP、Kerberos、SNMPv3、SSL/TLS、WEP 和 WPA/WPA2
- 可以将着色规则应用于数据包列表，以进行快速、直观的分析
- 输出可以导出为 xml、postscript、csv 或 纯文本



### 使用 Wireshark

#### 下载软件

Wireshark 是开源的，官网上提供了源码下载，可以下载源码自己编译。

Wireshark 支持 Windows、linux、macOS 等主流平台，这里以 Windows 为例，到官方下载页面进行下载：

<https://www.wireshark.org/#download> 



#### 界面简介

打开 Wireshark 后，界面如下所示，可以输入过滤器表达式限定要捕获的网络包，然后选择下方的网络进行抓包，直接双击即可开始。

![](http://blog-images.qiniu.wqf31415.xyz/wireshark_ui.png) 



例如我们捕获电脑以太网中的 tcp 协议数据包，可以过滤器输入框中输入 `tcp` ，然后双击下方的以太网一栏即可开始抓包。

![](http://blog-images.qiniu.wqf31415.xyz/wireshark_tcp.png) 

抓包界面分为三个区域：

- 第一个区域是数据历史，里面是从开始捕获至今所有的数据报记录，记录了包含了报文的编号（从 1 开始）、时间、源地址、目标地址、协议、报文长度、报文信息，点击项目的标题可以按相应的项排序，可以右键点击勾选或隐藏要显示的项目。
- 第二个区域是报文信息，不同报文的信息不同。
- 第三部分是报文内容，左侧以十六进制展示报文内容，右侧是尝试解析的结果。



#### 捕获过滤器

Wireshark 支持使用过滤器来限定要捕获的数据，Wireshark 的捕获过滤器使用 libpcap 过滤器语言编写，更多详情可以参考[pcap-filter 手册](https://www.tcpdump.org/manpages/pcap-filter.7.html) 。

> 官方示例：<https://wiki.wireshark.org/CaptureFilters> 

需要注意的是，这个捕获过滤器是在开始捕获前设定的，设定后 Wireshark 只会捕获限定的网络数据，其它不满足条件的数据将不会出现捕获记录中，用于大范围筛选。

##### 基础过滤器

- **协议**：如 `tcp`、`udp` 用来指定只捕获 TCP 或 UDP 协议的数据。在 `tcp` 或 `udp` 关键词后，可以使用 port、portrange 来补充限定端口的条件，如捕获 tcp 协议在 80 端口上的网络数据：`tcp port 80` ，`udp portrange 8080-8090` 
- **端口**：使用 `port` 指定捕获的端口，如 `port 80` 捕获 80 端口的数据；
- **端口范围**：使用 `portrange` 指定捕获的端口范围，如 `portrange 8080-8090` 
- **主机**：使用 `host` 指定捕获发往或来自指定主机的数据，如 `host 192.168.0.11` 或 `host www.wqf31415.xyz` ，或 ipv6 地址，如：`host 2001:db8::1` 
- **IP段**：使用 `net` 捕获指定 ip 范围内的网络数据，如 `net 192.168.0.0/24` 或 `net 192.168.0.0 mask 255.255.255.0` 
- **源地址**：使用 `src` 捕获指定发出请求的网络数据，需要加 host、net、port、portrange 来指定具体捕获条件，不能单独使用，如 `src host 127.0.0.1` ，`src port 8650` 
- **目标地址**：使用 `dst` 捕获发往指定地址的网络数据，需要加 host、net、port、portrange 来指定具体捕获条件，不能单独使用，如 `dst host 192.168.0.11` ，`dst port 8080` 
- **以太网**：使用 `ether` 指定捕获以太网数据，不能单独使用需要加 host、proto、src、dst、broadcast、multicast 来使用，如 `ether proto 0x888e`  
- **IPV4**：使用 `ip` 指定只捕获 ipv4 网络数据
- **广播**：使用 `broadcast` 指定捕获广播数据
- **多播**：使用 `multicast` 指定捕获多播数据



##### 联接过滤器

捕获过滤器支持多个表达式联接使用，还可以取反使用。

- 与：同时满足前后的过滤器，使用 `and` 或 `&&` 联接，如 `tcp port 23 and src host 10.1.1.1` 
- 或：满足其中一个过滤器，使用 `or` 或 `||` 联接，如 `tcp port 5566 or tcp port 5577`
- 非：只要不满足当前过滤器的，在过滤器前加 `not` 或 `!` ，如 `not port 80 and ! port 25 and host www.wireshark.org` 

多个表达式可以使用括号来区分优先级，如 `host www.example.com and not (port 80 or port 25)` 



#### 过滤表达式

Wireshark 过滤表达式用于在捕获到网络数据，或打开捕获记录文件后，对网络数据记录进行二次筛选。

##### 比较运算符

Wireshark 过滤表达式的比较运算符用于将字段和值进行比较，比较运算符可以通过类似英语缩写或类似 C 的符号来表示，如 `tcp.port == 80` 和 `tcp.port eq 80` 是等价的，只是后者前后需要加空格，前者不需要空格。

| 英文缩写 | 符号 | 含义                                                         | 示例                      |
| -------- | ---- | ------------------------------------------------------------ | ------------------------- |
| eq       | `==` | 等于（<span style="color:red">Eq</span>ual）                 | `ip.src == 192.168.0.102` |
| ne       | `!=` | 不等于（<span style="color:red">N</span>ot <span style="color:red">E</span>qual） | `tcp.port != 80`          |
| gt       | `>`  | 大于（<span style="color:red">G</span>reater <span style="color:red">T</span>han） | `frame.len > 10`          |
| lt       | `<`  | 小于（<span style="color:red">L</span>ess <span style="color:red">T</span>han） | `frame.len < 128`         |
| ge       | `>=` | 大于或等于（<span style="color:red">G</span>reater than or <span style="color:red">E</span>qual to） | `frame.len ge 0x100`      |
| le       | `<=` | 小于或等于（<span style="color:red">L</span>ess than or <span style="color:red">E</span>qual to） | `frame.len <= 0x20`       |
| in       |      | 在指定数组中，参数以 `{}` 包裹，每个值以空格分隔             | `udp.port in {80 90}`     |

> 过滤表达式中的数值可以使用十进制或十六进制形式。



##### 常见过滤表达式

- 按协议过滤：如过滤出 tcp 协议的网络数据，只需要输入 `tcp` 即可。
- 按 ip 地址过滤：如 `ip.addr == 192.0.2.1` ，`ip.src == 192.168.0.102` 
- 按端口过滤：按端口过滤时，要首先指定协议，如 `tcp.port eq 80` ，`udp.port in {80 90}`  
- 按帧长度过滤：如 `frame.len == 1560` 
- 按http内容类型过滤，如 `http.content_type contains "application/octet-steam"` ，`http.content_type[0:4] == text` ，这里的 `[0:4]` 是指从第 0 个字节开始计算，总长度为 4 字节的字符串
- 按http响应状态码过滤：如 `http.response.code == 404` 
- 按http请求方法过滤：如 `http.request.method == "POST"` 



##### 过滤表达式联接

与捕获过滤器一样，在过滤表达式中也可以使用 `and` 或 `&&` 、`or` 或 `||` 、`not` 或 `!` 来联接多个表达式，实现更复杂的过滤效果。详情参考捕获表达式。



### 参考资料

- 官方文档：<https://www.wireshark.org/docs/wsug_html_chunked/> 
- wireshark数据包分析技巧总结：<https://blog.csdn.net/rodney443220/article/details/43761811> 



### 总结

这篇文章介绍了使用 Wireshark 进行抓包分析网络请求，介绍了 Wireshark 的捕获过滤器和过滤表达式。