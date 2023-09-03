---
title: 两种方式注册Windows服务
date: 2021-08-11 11:37:08
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

> Microsoft Windows 服务（过去称为 NT 服务）允许用户创建可在其自身的 Windows 会话中长时间运行的可执行应用程序。 这些服务可在计算机启动时自动启动，可以暂停和重启，并且不显示任何用户界面。 这些功能使服务非常适合在服务器上使用，或者需要长时间运行的功能（不会影响在同一台计算机上工作的其他用户）的情况。 还可以在与登录用户或默认计算机帐户不同的特定用户帐户的安全性上下文中运行服务。 --官网



<!-- more -->

### 查看 Windows 服务

打开命令行（CMD 或 PowerShell），或使用快捷键 <kbd>Windows</kbd> + <kbd>R</kbd> 调出运行工具，执行 `services.msc` ，即可快速打开系统服务管理界面。在服务列表中点击服务名，可查看服务详情，可对服务进行启动、停止等操作。右键点击服务名称，点击 “属性” 可修改服务启动类型（自动延迟、自动、手动、禁用）。

![](https://blog-images.qiniu.wqf31415.xyz/windows_service.png)

另外，在任务管理器中的 “服务” 选项卡中点击 “打开服务” 按钮，也可以打开系统服务管理界面，如：

![](https://blog-images.qiniu.wqf31415.xyz/windows_tm_service.png)



### 注册 Windows 服务

Windows 服务可以通过 .Net 或 C# 编写。

要想将自己的程序注册称为 Windows 服务，可以使用第三方工具包，如 nssm、WinSW等。

> NSSM (Non-Sucking Service Manager): <http://www.nssm.cc/> 
>
> WinSW (Windows Service Wrapper): <https://github.com/winsw/winsw> 

#### 使用 nssm

nssm 是一个开源的用于注册 Windows 服务的工具。

##### 下载

登陆[官网](http://www.nssm.cc/)，下载安装包，nssm 最新版是 2014年8月31日发布的 2.24，下载的压缩包中包含为 32位和64位系统准备的主程序文件，还包含软件源码，可以进行二次开发。

![](https://blog-images.qiniu.wqf31415.xyz/nssm_package.png)



##### 注册服务

根据系统架构选择相应的 nssm 程序文件，在程序目录中打开命令行，执行如下命令，将会打开安装交互界面：

```bash
nssm install <servicename>
```

> 其中，`<servicename>` 是你想注册服务的名称，即在 Windows 服务管理中显示的服务名。

![](https://blog-images.qiniu.wqf31415.xyz/nssm_install_service.png)

在 `Application` 选项卡中选择要注册服务的程序路径（Application Path）和启动路径（Startup directory），然后点击 `Install service` 按钮，显示如下提示框，则说明注册服务成功，可进入服务管理中心查看。
![](https://blog-images.qiniu.wqf31415.xyz/nssm_install_service_success.png)  

> **更多配置：**
>
> nssm 还提供了更多参数设置，如添加服务详情介绍（Details）、账号登陆（Log on）、服务依赖（Dependencies）、服务停止设置（Shutdown）、服务退出操作（Exit actions）等，可根据需要进行设置。
>
> **修改配置：**
>
> 已注册的服务，如果需要修改参数配置，可执行命令 `nssm edit myservice` 开启设置界面进行修改。
>
> 更多设置请参考官方文档：http://www.nssm.cc/usage



##### 服务管理

nssm 还提供了一些服务管理功能，包括启动、停止、重启服务、查看服务状态等。

- 启动服务：`nssm start <servicename>` 
- 停止服务：`nssm stop <servicename>` 
- 重启服务：`nssm restart <servicename>` 
- 查看状态：`nssm status <servicename>` 
- 滚动输出：`nssm rotate <servicename>` 



##### 注销服务

要删除用 nssm注册的服务时，可执行下述命令：

```bash
nssm remove <servicename>
```

> `<servicename>` 是要删除的服务名称。

执行命令后，会弹出删除服务的确认提示框，点击 `是` 即可删除服务。

![](https://blog-images.qiniu.wqf31415.xyz/nssm_remove_service.png)

> 如果不想弹出确认提示框，可执行命令：`nssm remove <servicename> confirm` 



#### 使用 WinSW

WinSW 全称 Windows Service Wrapper，是一个开源的 Windows 服务打包和管理工具。运行环境需要 .NET Framework 4.6.1 或更高版本，如果系统没有 .NET ，官方提供了基于 .NET Core 的 32位、64位可执行文件。

##### 下载

登陆 WinSW 的 GitHub 项目发行版下载地址：https://github.com/winsw/winsw/releases

根据需要选择版本，建议选择稳定版，官方提供 32位、64位的可执行文件，还提供配置文件示例、.NET 执行文件以及源码下载。

![](https://blog-images.qiniu.wqf31415.xyz/winsw_download.png)

根据需要下载相应版本，可下载示例配置文件作为参考。



##### 注册服务

WinSW 注册服务有两种使用方式，一是把 WinSW 作为一个公共工具，可同时用于多个服务的注册；二是和具体服务绑定，仅作为该服务的注册工具。

###### 编写服务配置

> 官方文档：<https://github.com/winsw/winsw/blob/v3/docs/xml-config-file.md> 

WinSW 的服务配置使用 xml 文件，根节点为 `<service>` ，配置项中 `id` 和 `executable` 是必需的，其他均为可选项。

示例配置：

```xml
<service>
  <!-- 服务ID -->
  <id>jenkins</id>
  <!-- 服务名称 -->
  <name>Jenkins</name>
  <!-- 描述 -->
  <description>This service runs Jenkins continuous integration system.</description>
  <!-- 使用环境变量 -->
  <env name="JENKINS_HOME" value="%BASE%"/>
  <!-- 服务的执行文件 -->
  <executable>java</executable>
  <!-- 服务启动参数 -->
  <arguments>-Xrs -Xmx256m -jar "%BASE%\jenkins.war" --httpPort=8080</arguments>
  <!-- 日志输出模式：append 追加(默认)、none 无日志、reset 重启时重置、roll 滚动(默认日志文件10M，保留8个) -->
  <log mode="roll"></log>
</service>
```



###### 公共服务注册

将 WinSW 作为公共工具使用时，可以将其配置到环境变量中，方便使用。

先编写好服务配置文件，如 `myservice.xml` ，然后运行下述命令安装服务：

```bash
winsw install myservice.xml
```

启动服务：

```bash
winsw start myservice.xml
```

查看服务状态：

```bash
winsw status myservice.xml
```



###### 单独服务注册

WinSW 单独注册服务是指将 WinSW 作为一个服务打包工具，仅为一个程序注册服务。

首先要将 WinSW 可执行文件改名成服务名，如改成 `myservice.exe` ；然后编写服务配置，配置文件名称也要用服务名来命名，并需要将配置文件与服务注册程序放到一起，如 `myservice.xml` 。

安装服务：

```bash
myservice.exe install
```

启动服务：

```bash
myservice.exe start
```



##### 服务管理

WinSW 也可以用来管理注册的服务，如启停服务、查看服务等。注：改名后的 WinSW 可执行程序也可以使用。

- 启动服务：`winsw start myservice.xml` 或 `myservice.exe start` 
- 停止服务：`winsw stop myservice.xml` 或 `myservice.exe stop` 
- 重启服务：`winsw restart myservice.xml` 或 `myservice.exe restart` 
- 查看服务：`winsw status myservice.xml` 或 `myservice.exe status` 
- 刷新服务：`winsw refresh myservice.xml` 或 `myservice.exe refresh` 

> 上述示例命令中，`winsw` 是公共使用的 WinSW 命令，`myservice.xml` 是具体服务的配置文件，`myservice.exe` 是修改名称的 WinSW 可执行文件。



##### 注销服务

注销 WinSW 注册的服务：

```bash
winsw uninstall myservice.xml
```

或：

```bash
myservice.exe uninstall
```



### 参考资料

- 2种方法教你，如何将exe注册为windows服务，直接从后台运行: <https://zhuanlan.zhihu.com/p/93808282> 
- 注册jar包为windows服务: <https://blog.csdn.net/zl_action/article/details/102869227> 
- Windows 服务应用程序介绍 | Microsoft Docs: <https://docs.microsoft.com/zh-cn/dotnet/framework/windows-services/introduction-to-windows-service-applications> 
