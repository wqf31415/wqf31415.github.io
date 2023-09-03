---
title: MySQL自动备份
tags:
  - mysql
  - database
  - 数据库
categories:
  - mysql
date: 2021-09-07 13:10:59
---

### 概述

这篇文章介绍了 MySQL 数据库自动备份的方式，包括使用 Navicat 工具备份和使用 MySQL 自带的 `mysqldump` 工具备份。

![](https://blog-images.qiniu.wqf31415.xyz/data-ball.jpg)

<!-- more -->



### 使用 Navicat 自动备份

使用 Navicat 自动备份数据库，可以定时自动备份，备份完成后还可以通过邮件通知用户。操作时需要先创建 `批处理作业` ，然后给批处理作业设置计划任务，设置完成后即可自动执行。

材料：

- MySQL 5.7
- Navicat for MySQL 
- Windows 10

操作步骤：

- 打开Navicat ，创建数据库连接，连接上要备份的数据库。

- 点击 `计划` ， `新建批处理作业` 

  ![](https://blog-images.qiniu.wqf31415.xyz/navicat_data_backup_1.png)

- 打开数据库连接，点击选择要备份的数据库（jhdemo），双击 `可用任务` 中的 `Backup jhdemo`，这个任务会出现在下方 `已选择任务` 中，点击保存；

  ![](https://blog-images.qiniu.wqf31415.xyz/navicat_data_backup_2.png)

- 输入名字后点击确定，关闭对话框；

  ![](https://blog-images.qiniu.wqf31415.xyz/navicat_data_backup_3.png)

- 回到 `计划` 页面，选择刚才保存的批处理作业，点击 `设置计划任务` 

  ![](https://blog-images.qiniu.wqf31415.xyz/navicat_data_backup_4.png)

- 在弹出的对话框中，点击 `计划` 选项卡中的新建，设定计划周期和时间，点击确定；周期可选每天、每周、每月、一次性、系统启动时、系统空闲时、登陆时，高级选项中还可以设置任务开始结束日期。

  ![](https://blog-images.qiniu.wqf31415.xyz/navicat_data_backup_5.png)

- 输入电脑的密码，点击 **确定** 即可完成设置

  ![](https://blog-images.qiniu.wqf31415.xyz/navicat_data_backup_6.png)

  备份事例：

  ![](https://blog-images.qiniu.wqf31415.xyz/navicat_data_backup_7.png)



设置邮件推送：

在创建批处理任务时（或编辑已创建批处理任务时），可点击点击 `高级` 选项卡，勾选 `传送邮件` 选项卡，填入收件人、发件邮箱等相关信息即可。

![](https://blog-images.qiniu.wqf31415.xyz/navicat_data_backup_8.png)



### 使用 mysqldump 工具备份

`mysqldump` 是 MySQL 自带的逻辑备份工具，可编写脚本文件调用这个工具来完成数据备份。把脚本设置成定时执行即可达到定时自动备份效果。



### 参考资料

- Mysql自动备份: <https://www.cnblogs.com/tianyamoon/p/10443925.html> 
- MySQL之mysqldump的使用: <https://www.cnblogs.com/markLogZhu/p/11398028.html> 
- 设置自动备份mysql数据库: <https://www.cnblogs.com/lichunpeng/p/11237526.html> 

