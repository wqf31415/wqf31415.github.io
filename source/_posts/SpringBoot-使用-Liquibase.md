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


### 注意事项


### 参考资料
- 官网：Liquibase | Database Refactoring | Liquibase: [http://www.liquibase.org/](http://www.liquibase.org/)

