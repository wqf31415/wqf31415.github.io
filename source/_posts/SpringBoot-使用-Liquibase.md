---
title: SpringBoot 使用 Liquibase
date: 2019-03-12 16:33:42
tags:
- springboot
- liquibase
- database
categories:
- 技术
---

### 概述
本文主要介绍了 什么是 Liquibase，以及在 SpringBoot 项目中集成使用 Liquibase 对数据库表进行管理，包括自动创建数据库表、自动初始化数据、更新表结构。

### 认识 Liquibase
> 官网：Liquibase | Database Refactoring | Liquibase: [http://www.liquibase.org/](http://www.liquibase.org/)
Liquibase 是用于数据库重构、管理、记录变化与回滚的开源工具。

### Liquibase 特点
- 支持项目代码多人多分支开发与合并；
- 支持多种数据库类型：MySQL、PostgreSQL、Oracle、Sql Server、DB2、H2等，更多信息请移步官网：  [http://www.liquibase.org/databases.html](http://www.liquibase.org/databases.html) ；
- 支持多种变化日志格式：XML、YML、JSON、SQL；
- 支持自定义上下文执行逻辑，可指定需要运行的上下文；
- 集群安全的数据库更新；
- 可生成数据库修改文档(HTML)；
- 使用命令对比两个数据库；
- 可以使用 build 工具(Command Line、Ant、Maven)运行，也可以嵌入到 Application 中；
- 可以自动生成数据库 SQL 脚本，供 DBA 重构代码使用；
- 可以使用离线数据库；

### 使用 Liquibase
#### 环境依赖
+ windows 操作系统 PC
+ Java 1.8 运行环境，liquibase 2.x 依赖 java 1.5+，3.x 依赖 java1.6+
+ Maven 3.0
+ MySQL 5.7
+ liquibase 3.6.3
+ (可选)Navicat for MySQL ，用于查看数据库表结构与数据

#### 使用命令行体验 Liquibase
##### 下载压缩包
> 官网下载地址：[https://download.liquibase.org/download/?frm=n](https://download.liquibase.org/download/?frm=n "download liquibase")
> liquibase-3.6.3-bin.zip: [我的下载地址](http://source.qiniu.wqf31415.xyz/liquibase-3.6.3-bin.zip "我的下载地址")

![](http://blog-images.qiniu.wqf31415.xyz/liquibase_download.png "download liquibase")

##### 解压文件、下载 JDBC jar 包
将上一步下载好的 liquibase zip 包解压出来。
我电脑上使用的 MySQL ，所以我需要下载 mysql-connector-java 用来连接操作数据库，我这里使用的版本是 8.0.13，下载下来后将这个 jar 包放到 liquibase 根目录下的 `lib` 文件夹中，使用 liquibase 时，会自动扫描 `lib` 下的包。
> 下载地址：[mysql-connector-java-8.0.13](http://source.qiniu.wqf31415.xyz/mysql-connector-java-8.0.13.jar "mysql-connector-java-8.0.13")

##### 创建数据库修改日志文件(database chanagelog file)
liquibase 支持多种格式的日志文件，包括 XML、YML、JSON、SQL，个人喜欢更加简洁的 yml 格式。在 liquibase 根目录下创建文件夹 `chanagelog` ，用来存储修改日志文件。从官网拷贝示例，存储到 `chanagelog` 目录下，文件名为 `master.yml` ，文件内容如下：
> 注意直接从官方文档中考出来的，要修改 databaseChangeLog.preConditions.runningAs.username ，改为自己数据库的用户名，我使用的是 root 。

``````yml
databaseChangeLog:
  - preConditions:
    - runningAs:
        username: root

  - changeSet:
      id: 1
      author: nvoxland
      changes:
        - createTable:
            tableName: person
            columns:
              - column:
                  name: id
                  type: int
                  autoIncrement: true
                  constraints:
                    primaryKey: true
                    nullable: false
              - column:
                  name: firstname
                  type: varchar(50)
              - column:
                  name: lastname
                  type: varchar(50)
                  constraints:
                    nullable: false
              - column:
                  name: state
                  type: char(2)

  - changeSet:
      id: 2
      author: nvoxland
      changes:
        - addColumn:
            tableName: person
            columns:
              - column:
                  name: username
                  type: varchar(8)

  - changeSet:
      id: 3
      author: nvoxland
      changes:
        - addLookupTable:
            existingTableName: person
            existingColumnName: state
            newTableName: state
            newColumnName: id
            newColumnDataType: char(2)
`````` 

##### 运行命令
在数据库中新建数据库 `test_liquibase`，在 liquibase 根目录打开命令行，执行命令
``````
liquibase.bat --url="jdbc:mysql://localhost:3306/test_liquibase?useUnicode=true&characterEncoding=utf8&serverTimezone=GMT%2B8" --changeLogFile="/chanagelog/master.yml" --username=root --password=123456 --driver=com.mysql.cj.jdbc.Driver update 
``````
> liquibase 命令中必须的必须选项有：
  --url=数据库连接，其中 serverTimezone=GMT%2B8 参数用来指定时区，在使用高版本 jdbc 时需要，不指定可能会报时区错误
  --chanagelog=数据库修改日志文件
  --username=数据库用户名
  --password=数据库密码
  --driver=数据库连接驱动
  最后的 update 是 liquibase 命令，必须放到选项的后面。
  关于命令的更多内容可以使用 `liquibase --help` 命令查看帮助信息，也可以到官网查询详细信息: [http://www.liquibase.org/documentation/command_line.html](http://www.liquibase.org/documentation/command_line.html)

执行结果：
![](http://blog-images.qiniu.wqf31415.xyz/liquibase_update_by_cmd.png "update success")

##### 检查数据库
查看 `test_liquibase` 数据库，发现多了 4 张表：
![](http://blog-images.qiniu.wqf31415.xyz/liquibase_create_table.png "数据库表")

打开 databasechanagelog 表，发现在 `master.yml` 中的 3 个修改都已经被执行了。
![](http://blog-images.qiniu.wqf31415.xyz/liquibase_create_table_2.png "databasechanagelog")

#### SpringBoot 项目继承 Liquibase


### 注意事项


### 参考资料
- 官网：Liquibase | Database Refactoring | Liquibase: [http://www.liquibase.org/](http://www.liquibase.org/)

