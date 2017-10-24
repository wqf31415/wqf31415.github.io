---
title: JHipster 学习笔记2
date: 2017-09-12 16:12:52
tags:
- JHipster
- java
- web
categories:
- 技术
---

## JHipster 核心 —— 创建实体（Create Entity）

当你创建好一个项目后，你下一步要做的可能就是添加实体了，对于每个实体，你都需要下面这些内容：

- 一张数据库表；
- 一个 Liquibase 修改集；
- 一个 JPA 实体；
- 一个 Spring Data JPA 仓库对象；
- 一个 spring MVC 的控制器，实现了基础的增、查、删、改方法；
- 一个 Angular 路由、组件和server；
- 一个 html 展示页面；
- 集成测试来验证所有东西是否正确运行；
- 性能测试来验证所有东西是否允许流畅；

如果你有多个实体，那实体之间可能还有相互关联，因此，还需要：

- 数据库外键关联；
- 特殊的 JS 和 html 代码来管理这些关联关系


### 用标准命令行接口创建实体

以上内容只需要执行一条指令，然后回答几个问题即可完成：

``````
yo jhipster:entity [options] <name>
``````

需要帮助可以执行 `yo jhipster:entity --help` 指令，然后我们会看到指令的说明。
这种方式适合实体数量少的情况，或者在开发过程中途添加实体。

name 为实体名，options 为可选项：

| option           | 功能                   | 默认值   |
| ---------------- | -------------------- | ----- |
| --help 或 -h      | 打印出指令的选项和用法          | false |
| --skip-cache     | 不缓存选项的回答内容           | false |
| --skip-install   | 不自动安装依赖              | false |
| --regenerate     | 重新生成实体但不出现提示选项       | false |
| --table-name     | 自定义数据库表名             | false |
| --fluent-methods | 在实体中生成流利的方法，允许链式对象构造 | true  |
| --angular-suffix | 自定义Angular 前缀        | false |
| --skip-server    | 不生成服务器端代码            | false |
| --skip-client    | 不生成客户端代码             | false |



**【例】** 要创建一个 Book 实体，我们可以在项目根目录下打开命令行，输入指令：

#### 执行指令

``````
yo jhipster:entity Book
``````

#### 回答问题

然后根据提示，添加实体需要的属性和关联关系：

Do you want to add a field to your entity? (Y/n)	-- 是否要为实体添加字段？输入 **y** 回车，或直接回车

What field name of your field?		-- 字段名是什么？输入 author 回车，字段命名采用小驼峰命名方式

What is the type of your field? (Use arrow keys)		-- 字段的类型，用上下键选择，回车确定，类型如下：

- String		-- 字符串

- Integer-- 整形

- Long-- 长整形

- Float-- 浮点型

- Double-- 双精度型

- BigDecimal-- 大位数

- LocalDate-- 本地日期

- ZonedDateTime-- 时区化的时间

- Boolean-- 布尔型

- Enumeration (Java enum type)-- 枚举

- [BETA] Blob-- 二进制大对象

Do you want to add validation rules to your field? (y/N)-- 是否为字段添加验证规则，默认不添加，输入 **y** 回车添加验证

Which validation rules do you want to add? (Press \<apace\> to select, \<a\> to toggle all, \<i\> to inverse selection)-- 如果选择添加验证且字段类型为 String 时将会出现这个问题，用上下键选择，空格键确定选择，可选择多个

- ( ) Required

- ( ) Minimum length

- ( ) Maximum length

- ( ) Regular expression pattern

  What is the minimum length of your field? (0)-- 为字段添加最小长度限定，默认为 0 

  What is the maximum length of your field? (20)-- 字段最大长度限定，默认为 20

  What is the regular expression pattern you want to apply on your field? (^[a-zA-Z0-9]*$)-- 用正则表达式限定字段内容

  Do you want to add a relationship to another entity? (Y/n)-- 当字段添加完成后，会提示是否添加关系，默认添加

  What is the name of the other entity?-- 输入要关联的实体名，如为书籍添加作者，输入 Author 回车确定

  What is the name of the relationship? (auther)-- 关系名称，默认值为关联的实体名，可以直接回车确定

  What is the type of the relationship? (Use arrow keys)-- 选择关联类型

- one-to-many

- many-to-one

- many-to-many

- one-to-one

  What the name of this relationship in the other entity? (book)	-- 关系在其他实体中的名称

  Do you want to use a Data Transfer Object (DTO)? (Use arrow keys)	-- 是否使用 DTO

- No, use the entity directly?

- [BETA] Yes, generate a DTO with MapStruct

  Do you want to use separate service class for your business logic? (Use arrow keys)	-- 是否为实体逻辑添加分离的 server 类，选择第二项生成单独的 service 类

- No, the REST controller should use the repository directly

- Yes, generate a separate service class

- Yes, generate a separate service interface and implementation

  Do you want pagination on your entity? (Use arrow keys)-- 是否添加分页，选择第二项，生成简单的分页页面

- No

- Yes, with a simple pager

- Yes, with pagination links

- Yes, with infinite scroll

#### 处理冲突

在回答完上述问题后，将在项目中创建实体，过程中会生成一些文件，有些文件已经存在，就会产生冲突，这时会提示我们是否选择覆盖原文件，根据需要输入 y 覆盖，n 不覆盖，a 全部覆盖。

处理完所有冲突后，创建实体完成，将自动执行 `gulp inject` 指令将生成的js文件注入到 index.html 中，至此，创建一个 Author 实体完成。

### 批量创建实体

#### 使用 JDL 批量生成实体

在刚开始搭建项目时，要创建实体数量很多，建议使用 JDL 将所有实体信息都写在一起，便于核对及修改，创建实体时可以一键创建多个实体，提高效率。

> 最好先看下官网提供的 jdl 说明：

推荐使用 JHipster 官方的 JDL Studio 在线工具：http://www.jhipster.tech/jdl-studio/ ，进入页面可以看到官网提供的 jdl demo，页面左侧是编辑区域，右侧是 uml 图形展示，可以仿照这个demo 快速创建自己的 JDL 文件，编辑完成后点击右上角的下载图标即可把 jdl 文件保存到本地，文件格式为 **.jh**。

在体验阶段，我们直接下载官网提供的 jdl 文件到本地，默认文件名 **jhipster-jdl.jh** ，将这个文件放到项目根目录，在根目录打开命令行工具，执行指令：

``````
yo jhipster:import-jdl jhipster-jdl.jh
``````

然后就等待程序执行，创建实体就行了，偶尔会有冲突，让你选择是否覆盖原有的文件，根据需要选择输入y 覆盖，n 不覆盖。

在实体创建完成后，会自动执行 `gulp inject` 将产生的静态资源注入到 index.html 中。

完成后就可以启动项目，查看结果了。



#### 使用 UML 批量创建实体

这个我也没用过，先挖个坑，后面再填！










