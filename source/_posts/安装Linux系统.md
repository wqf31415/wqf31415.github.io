---
title: 安装Linux系统
tags:
  - linux
categories:
  - linux
date: 2021-07-07 19:33:53
---

### 概述

这篇文章介绍了如何在虚拟机和实体机中安装 Linux 系统，这是学习 Linux 系统的第一步。



### 关于 Linux 系统

Linux，全称 GNU/Linux ，是一开源和自由传播的类 UNIX 操作系统，是一个基于 POSIX 的多用户、多任务、支持多线程和多 CPU 的操作系统，深受全世界软件爱好者、组织和公司的支持。Linux 可以运行在服务器和其他大型平台上，也广泛应用于嵌入式系统中，在移动设备中广泛使用的 Android 操作系统就是创建在 Linux 内核之上。

Linux通常被打包成供个人计算机和服务器使用的 Linux 发行版，发行版包含 Linux 内核和支撑内核的实用程序和库，通常还带有大量可满足各类需求的应用程序。现在流行的 Linux 发行版主要分为两派：一是 Debian 及其衍生版本 Ubuntu、Linux mint，二是 Fedora 及相关版本 Red Hat Enterprise Linux、CentOS 等。

> Linux 系统族谱
>
> GNU/Linux Distribution Timeline: <http://futurist.se/gldt/> 

<!-- more -->



### 安装 Linux

#### 下载系统镜像

由于 Linux 是自由开源的，发展至今有成百上千个发行版，为了系统安全和学习顺利，建议选择流行的发行版，并从其官方网站中下载系统镜像。<small>本文中选择 Ubuntu 作为示例</small>。 

一些常见的 Linux 发行版：

- MX Linux: <https://mxlinux.org/> 
- Manjaro: <https://manjaro.org/> 
- Mint: <https://linuxmint.com/> 
- Ubuntu: <https://ubuntu.com/> 
- Debian: <https://www.debian.org/> 
- CentOS: <https://www.centos.org/> 
- Kali: <https://www.kali.org/> 
- 深度 deepin: <https://www.deepin.org/zh/> 
- 优麒麟: <https://www.ubuntukylin.com/> 
- 红旗 Linux: <https://www.linuxsir.cn/> 



#### 虚拟机安装

虚拟机安装 Linux 系统，需要先安装模拟软件，然后创建虚拟机项目，使用下载的系统镜像启动，即可进入系统安装程序。

##### 安装虚拟机软件

使用虚拟工具安装是体验  Linux 的很好方式，安装方便，不影响当前系统正常使用，如果有问题可以直接删掉重装，而且一些软件还提供系统快照备份功能，<abbr title="存档/读取">SL</abbr>大法解决你的后顾之忧。常见的虚拟机软件有 VisualBox、VMware Workstation 等。

- Oracle VM VirtualBox: 免费开源的虚拟机软件，项目地址: <https://www.virtualbox.org/> 。

- VMware Workstation Player: 功能强大，成熟稳定，安全的虚拟化工具，非商业用途可免费使用，地址： <https://www.vmware.com/cn/products/workstation-player.html> 。

这里使用 Oracle VM VirtualBox 来做示例，模拟器软件安装过程非常简单，就不做介绍了。



##### 创建虚拟机项目

以安装 Ubuntu 为例，Ubuntu 是一个广为人知的 Linux 发行版，带有操作界面，对于新手来说更加友好，更容易上手。

打开安装好的 Oracle VM VirtualBox，根据引导程序设置虚拟机参数，创建一个虚拟机项目，然后启动项目，选择下载好的系统镜像文件，开始安装系统。

<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/lightgallery.js@1.1.3/dist/css/lightgallery.min.css"/>
<script src="https://cdn.jsdelivr.net/npm/lightgallery.js@1.1.3/dist/js/lightgallery.min.js"></script>
<div id="gallery-container" style="max-width: 900px;position: relative;">
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_1.png" data-sub-html="<h4>1. 打开VirtualBox，点击新建</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_1.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_2.png" data-sub-html="<h4>2. 填写虚拟机名称，选择存储的目录、虚拟机类型、版本</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_2.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_3.png" data-sub-html="<h4>3. 选择内存大小，默认为1G</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_3.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_4.png" data-sub-html="<h4>4. 选择创建虚拟硬盘，点击下一步</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_4.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_5.png" data-sub-html="<h4>5. 选择虚拟硬盘类型</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_5.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_6.png" data-sub-html="<h4>6. 选择动态分配</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_6.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_7.png" data-sub-html="<h4>7. 选择文件存储位置，调整硬盘大小，默认为10G，点击创建</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_7.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_8.png" data-sub-html="<h4>8. 创建完成，点击启动</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_8.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_9.png" data-sub-html="<h4>9. 选择启动盘，点击右侧添加新镜像</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_9.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_10.png" data-sub-html="<h4>10. 选择下载的镜像</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_10.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_11.png" data-sub-html="<h4>11. 点击启动</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_11.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_12.png" data-sub-html="<h4>12. 选择字体：中文(简体)</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_12.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_13.png" data-sub-html="<H4>13. 选择安装 </H4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_13.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_14.png" data-sub-html="<h4>14. 开始安装</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_create_vm_14.png"/>
    </a>
</div>
<script>
    lightGallery(document.getElementById('gallery-container'), {
        galleryId: "nature",
        animateThumb: false,
        allowMediaOverlap: true,
        toggleThumb: true
    });
</script>


##### Ubuntu 安装设置

进入 Ubuntu 系统安装引导，根据引导设置语言、分区、时区、用户名、密码等信息后开始安装，等待安装完成，然后即可登陆系统开始享用。

> 安装设置过程中的分区和用户信息非常关键，分区可根据系统用途进行细微调整，初学者可直接使用默认配置，用户信息在登陆时要用到，需要记住。

<div id="gallery-container-2" style="max-width: 900px;position: relative;">
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_1.png" data-sub-html="<h4>1. 选择系统语言</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_1.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_2.png" data-sub-html="<h4>2. 是否更新和安装第三方软件</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_2.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_3.png" data-sub-html="<h4>3. 磁盘设置</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_3.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_4.png" data-sub-html="<h4>4. 确认分区，点击继续</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_4.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_5.png" data-sub-html="<h4>5. 选择时区</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_5.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_6.png" data-sub-html="<h4>6. 选择键盘布局</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_6.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_7.png" data-sub-html="<h4>7. 填写用户名、密码</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_7.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_8.png" data-sub-html="<h4>8. 开始安装，等待安装完成</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_8.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_9.png" data-sub-html="<h4>9. 已经安装完成，点击重启</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_9.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_10.png" data-sub-html="<h4>10. 重启，提示移除安装媒体，按回车继续</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_10.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_11.png" data-sub-html="<h4>11. 已经启动，输入密码进入系统</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_11.png"/>
    </a>
    <a data-src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_12.png" data-sub-html="<h4>12. 进入系统</h4>">
        <img style="max-width:280px; padding:5px; display: inline-block;" class="img-responsive"
             src="https://blog-images.qiniu.wqf31415.xyz/virtualBox_ubuntu_12.png"/>
    </a>
</div>
<script>
    lightGallery(document.getElementById('gallery-container-2'), {
        galleryId: "nature",
        animateThumb: false,
        allowMediaOverlap: true,
        toggleThumb: true
    });
</script>


#### 实体机安装

实体机安装系统时需要先做一个系统盘，然后让电脑从系统盘启动，即可进入安装程序。

##### 将系统镜像写入U盘

安装系统时需要先将系统镜像写入U盘，这里使用 ISO to USB 工具进行刻录。

> 注意：U盘容量要大于镜像尺寸，写入U盘时将格式化U盘，注意备份U盘内容。
>
> 文件系统选项可能会影响系统安装，建议选择 `FAT32` 类型。

![](https://blog-images.qiniu.wqf31415.xyz/iso_to_usb.png) 

一些镜像刻录工具：

- ISO to USB：免费小巧（1.6M），英文操作界面，地址： <http://www.isotousb.com/> 
- UltraISO软碟通：收费软件，可免费试用，中文官方网站: <https://cn.ultraiso.net/> 



##### 安装系统

插入U盘，重启电脑，在启动时，进入 BIOS ，选择从 USB 启动，然后即可进入系统安装的引导，这部分与虚拟机安装过程相同。

> 进入 BIOS 的方法：
>
> 启动电脑时，多数电脑会显示品牌 logo 画面，会提示进入 BIOS 的按键，此时按对应的键即可进入。一般是 F2、F10 或 F12。



### 参考资料

- Linux家族族谱: <https://zhuanlan.zhihu.com/p/313443723> 
- 百度百科：<https://baike.baidu.com/item/Linux> 
- 维基百科：<https://zh.wikipedia.org/wiki/Linux> 

