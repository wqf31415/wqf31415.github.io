---
title: 使用ibd文件恢复Mysql数据
tags:
  - database
  - mysql
  - 数据库
categories:
  - mysql
date: 2021-01-21 23:04:43
---

### 概述

这篇文章介绍了使用 ibd 文件还原 MySQL 数据的方法。

![](http://blog-images.qiniu.wqf31415.xyz/binary_data.jpg)

### ibd 简介

MySQL 中默认使用 InnoDB 存储引擎存储数据，存储数据和索引生成的文件就是以 `.ibd` 为后缀，利用 ibd 文件可以完成数据迁移与还原。

ibd 文件以页为单位进行管理，默认情况下页大小为 16kb，ibd 文件大小必然是 16k 的整数倍，页结构分为页头（38字节）、页身（16338字节）、页尾（8字节）。



<!-- more -->

### 相关概念

如果 MySQL 数据库使用的是 InnoDB 引擎，没有开启独立表空间，所有的数据库表信息和元数据都会写入 ibdata 文件，这样时间久了文件会变得很大，影响数据库性能。如果开启了独立表空间，ibdata 文件只会存储一下引擎相关的索引空间，实际数据都会写入独立的 frm 和 ibd 文件里。

- frm 文件：保存了每个表的元数据，包括表结构的定义等，与数据库引擎无关。
- ibd 文件：存放数据和索引的文件（使用 InnoDB 并开启了独立表空间）。



### 操作步骤

#### 创建表

创建一张与原表结构一致的表，创建数据库后查看数据存储目录，发现有表的 frm 文件。



#### 删除表空间

删除新建表的表空间，执行命令删除表空间：

```sql
ALTER TABLE <table_name> DISCARD TABLESPACE;
```



#### 拷贝 ibd 文件

将包含数据的 ibd 文件拷贝到新创建表的数据目录下。



#### 导入表空间

执行下述 sql 添加表空间。

```sql
ALTER TABLE <table_name> IMPORT TABLESPACE;
```



### 参考资料

- MySQL InnoDB ibd 文件格式解析: <https://baijiahao.baidu.com/s?id=1651899113311145118> 
- mysql从.ibd文件恢复数据: <https://blog.csdn.net/wearegouest/article/details/79538618> 
- MySQL如何利用ibd文件恢复数据: <https://www.sohu.com/a/147397553_733939> 



### 总结

利用 ibd 文件可以将数据从出错的数据库中拯救出来，亦可以用来迁移大量数据，直接拷贝文件比导出数据到文件再导入的效率要高很多。