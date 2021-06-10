---
title: Windows服务注册
date: 2021-06-03 10:12:08
tags:
  - Windows
  - 工具
  - 服务器
categories:
  - 工具
---

### 概述

这篇文章介绍了在 Windows 系统中将程序注册成服务，让程序自动启动或在后台运行。



### Windows 服务



<!-- more -->

### 查看 Windows 服务

打开命令行（CMD 或 PowerShell），或使用快捷键 <kbd>Windows</kbd> + <kbd>R</kbd> 调出运行工具，执行 `services.msc` ，即可快速打开系统服务管理界面。在服务列表中点击服务名，可查看服务详情，可对服务进行启动、停止等操作。右键点击服务名称，点击 “属性” 可修改服务启动类型（自动延迟、自动、手动、禁用）。

![](http://blog-images.qiniu.wqf31415.xyz/windows_service.png)

另外，在任务管理器中的 “服务” 选项卡中点击 “打开服务” 按钮，也可以打开系统服务管理界面，如：

![](http://blog-images.qiniu.wqf31415.xyz/windows_tm_service.png)



### 注册 Windows 服务



NSSM (Non-Sucking Service Manager): <http://www.nssm.cc/> 

WinSW (Windows Service Wrapper): <https://github.com/winsw/winsw> 



### 参考资料

- 2种方法教你，如何将exe注册为windows服务，直接从后台运行: <https://zhuanlan.zhihu.com/p/93808282> 
- 注册jar包为windows服务: <https://blog.csdn.net/zl_action/article/details/102869227> 
