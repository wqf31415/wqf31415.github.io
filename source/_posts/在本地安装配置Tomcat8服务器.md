---
title: 在本地安装配置Tomcat8服务器
date: 2017-04-06 15:57:11
tags:
- web
- tomcat
- 服务器
categories:
- 技术
---

> 摘要：本篇文章讲解在 windows 系统下，本地安装配置 Tomcat 服务器！

![](http://blog-images.qiniu.wqf31415.xyz/image/tomcat.png) 

### 从官网下载 Tomcat8.5
官网地址：[http://tomcat.apache.org/](http://tomcat.apache.org/) 

下载 Tomcat 8.x ：[http://tomcat.apache.org/download-80.cgi](http://tomcat.apache.org/download-80.cgi)

![](http://blog-images.qiniu.wqf31415.xyz/image/download_tomcat_for_windows.png "根据系统选择32/64位")

对于 windows 系统，我们可以下载二进制文件压缩包，或者安装程序，对于新手来说，建议直接下载安装程序，双击执行，根据提示一步一步操作即可，没什么难度。但是，我们这次偏要选择下载 zip 压缩包，先苦后甜。


<!-- more -->
------



### 选块风水宝地，把文件解压进去
选的时候要避免出现中文路径！然后要把这个地方记住，等会要用到的，如我把压缩文件解压到 E 盘的 tomcat 目录下，我的 tomcat 服务器的路径就是： **E:\tomcat\apache-tomcat-8.5.14**

### 添加配置信息
打开 **“控制面板”** --> **“所有控制面板项”** --> **“系统”** ，点击 **“高级系统设置”**
![](http://blog-images.qiniu.wqf31415.xyz/image/open_system_config_on_windows.png "打开‘高级系统设置’")

在 **“系统属性”** 对话框中选择 **“高级”** 选项卡，点击下方的 **“环境变量”**
![](http://blog-images.qiniu.wqf31415.xyz/image/open_environment_variable.png "打开‘环境变量’")

在 **“环境变量”** 中的 **“系统变量”** 中点击 **“新建”**，在 **“新建系统变量”** 中的 **“变量名”** 输入框中输入 **CATALINA_HOME** ，在 **“变量值”** 输入刚才的 tomcat 安装路径 **E:\tomcat\apache-tomcat-8.5.14** 
![](http://blog-images.qiniu.wqf31415.xyz/image/add_new_environment_variable_CATALINA_HOME.png "添加 CATALINA_HOME") 

同时新建一个变量 **CATALINA_BASE** ，变量值是刚才的安装目录 **E:\tomcat\apache-tomcat-8.5.14**

------


### 测试

进入 tomcat 的安装目录，可以看到下面的文件夹：
![](http://blog-images.qiniu.wqf31415.xyz/image/tomcat_directory.png "tomcat 目录") 

- **bin** 二进制文件；
- **conf** 配置文件；
- **lib** 运行库文件；
- **logs** 日志文件；
- **temp** 临时文件；
- **webapps** web 应用(我们部署的应用就放在这里)；
- **work** 工作空间
- **LICENSE** 许可
- **NOTICE** 公告
- **RELEASE-NOTES** 发布记录
- **RUNNING.txt** 运行说明

进入 **bin** 目录，运行 **startup.bat** ，如果出现下面的结果说明服务器已经正确启动了
![](http://blog-images.qiniu.wqf31415.xyz/image/startup_tomcat.png "运行 startup.bat")

打开 [http://localhost:8080/](http://localhost:8080/ ) 若能打开页面，说明 tomcat 服务器已成功启动。
![](http://blog-images.qiniu.wqf31415.xyz/image/tomcat_index.png "http://localhost:8080/") 

若想停止 tomcat 服务器，可以运行 **bin** 目录下的 **shutdown.bat** ，或者在启动时的命令行界面按 **Ctrl + C** 停止。

### 将 Tomcat 添加到系统服务中
进入 **bin** 目录，打开命令行，运行 **service.bat install** 即可将 tomcat 服务器添加到 windows 服务中，在服务中即可启动或关闭 tomcat ，在这个命令中可以对服务命名 **service.bat install tomcat8** 。

运行 **service.bat remove tomcat** 即可从服务中删除 tomcat 。

------


### 第二种安装方法
下载安装 installer 程序，双击进行安装，根据需要进行选择，或直接默认选择一直点下一步就可以了。

