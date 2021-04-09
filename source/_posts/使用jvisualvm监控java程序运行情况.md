---
title: 使用jvisualvm监控java程序运行情况
date: 2021-04-09 18:16:08
tags:
- java
- jvm
categories:
- java
---

### 概述

jvisualvm 是 jdk 中提供的程序监控工具，能够帮我们监控程序运行，辅助程序调优。比如 java 项目中很多时候需要用到线程池来并发处理工作任务，但在写代码的时候很难确定线程池的容量配置，此时可以使用 jvisualvm 来监测程序中创建线程的情况，以此来确定线程池配置。



### 关于 jvisualvm

jvisualvm （Java VisualVM）是 jdk（1.8） 中自带的故障处理工具，功能强大，能够对 java 程序进行运行时监测和故障处理，还能进行性能分析。jvisualvm的优点是不需要被监视的程序基于特殊的 Agent 运行，对应用程序的实际性能影响很小，这使得它可以直接运用在生产环境中。

jvisualvm 还支持扩展插件，实现更多功能。



<!-- more -->

### VisualVM 功能

- 显示虚拟机进城以及进程的配置、环境信息（jps、jinfo）
- 监视程序的CPU、GC、堆、方法区以及线程的信息（jstat、jstack）
- dump 以及分析堆转储快照（jmap、jhat）
- 方法级的程序运行性能分析，找出调用最多、运行时间最长的方法
- 离线程序快照：收集程序的运行时配置、线程dump、内存dump等信息建立一个快照，可以将快照发送开发者处理bug反馈



### 插件扩展

点击菜单栏 “工具” - “插件” ，打开插件管理界面，在 “可用插件” 选项卡中选择并安装需要的插件，在右侧可查看版本和功能说明。

![](http://blog-images.qiniu.wqf31415.xyz/jvisualvm_plug.png)

>如果更新插件列表失败，可以到 [Java VisualVM 插件中心](https://visualvm.github.io/pluginscenters.html) 找到对应 jdk 版本的插件更新目录链接，添加到插件设置中。



### 监视应用程序

Java VisualVM 可以监视本地运行的 java 程序，也可以使用 JMX 远程监控其他主机上的程序。

连接到监控的 JVM 后，

- 概述：查看应用程序信息、JVM 参数、系统参数以及保存的数据。

- 监视：实时监视程序运行情况，可查看CPU使用情况、垃圾回收活动、堆使用情况、线程数量，还可以生成堆 Dump，手动执行垃圾回收。

  ![](http://blog-images.qiniu.wqf31415.xyz/jvisualvm_monitor_springboot.png)

  

- 线程：实时监控线程活动情况，生成线程 Dump。

  ![](http://blog-images.qiniu.wqf31415.xyz/jvisualvm_thread.png)

  

- 抽样器：按CPU收集性能数据、收集内存数据。



### 参考资料

- 周志明 · 深入理解java虚拟机

- visualVM安装插件，无法连接到visualVM 插件中心: <https://blog.csdn.net/weixin_33800593/article/details/92295832> 

