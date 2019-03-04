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

然而以上内容，只需要我们执行一个指令回答几个问题就可以搞定了，JHipster 一下帮我们写了几百行代码，怎么样，想不想学学这种操作？

<!-- more -->

### 依赖版本

- java：1.8
- JHipster : 3.12.2
- gulp：3.9.1


### 用标准命令行接口创建实体

以上内容只需要执行一条指令，然后回答几个问题即可完成：

``````
yo jhipster:entity [options] <name>
``````

**请注意，这里使用的 JHipster 生成器版本为 3.12.2，更新的版本命令可能不同**

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
注意：实体名要用 **大驼峰** 命名方式，如AaaBbbCcc，在数据库中创建的表名为：aaa_bbb_ccc

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

注意：在给实体添加字段时不用添加主键id，系统会自动添加id字段作为主键

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

在回答完上述问题后，将开始在项目中创建实体，过程中会生成一些文件，有些文件已经存在，就会产生冲突，这时会提示我们是否选择覆盖原文件，根据需要输入 y 覆盖，n 不覆盖，a 覆盖全部冲突文件。

处理完所有冲突后，创建实体完成，将自动执行 `gulp inject` 指令将生成的js文件注入到 index.html 中，至此，创建一个 Author 实体完成。


### 批量创建实体

#### 使用 JDL 批量生成实体

在刚开始搭建项目时，要创建实体数量很多，建议使用 JDL 将所有实体信息都写在一起，便于核对及修改，创建实体时可以一键创建多个实体，提高效率。

> 最好先看下官网提供的 jdl 说明：http://www.jhipster.tech/jdl/

推荐使用 JHipster 官方的 JDL Studio 在线工具：http://www.jhipster.tech/jdl-studio/ ，进入页面可以看到官网提供的 jdl demo，页面左侧是编辑区域，右侧是 uml 图形展示，可以仿照这个demo 快速创建自己的 JDL 文件，编辑完成后点击右上角的下载图标即可把 jdl 文件保存到本地，文件格式为 **.jh**。

在体验阶段，我们直接下载官网提供的 jdl 文件到本地，默认文件名 **jhipster-jdl.jh** ，将这个文件放到项目根目录，在根目录打开命令行工具，执行指令：

``````
yo jhipster:import-jdl jhipster-jdl.jh
``````

然后就等待程序执行，创建实体就行了，偶尔会有冲突，让你选择是否覆盖原有的文件，根据需要选择输入y 覆盖，n 不覆盖。

在实体创建完成后，会自动执行 `gulp inject` 将产生的静态资源(javascript文件)注入到 index.html 中。

完成后就可以启动项目，查看结果了。


#### JDL语法：
> 官方在线 JDL 工具: https://start.jhipster.tech/jdl-studio/
3.12.2 JDL 文档: https://www.jhipster.tech/documentation-archive/v3.12.2/jdl/

- 添加实体
``````
entity \<实体名\> {
	参数名 类型 限制条件,
	参数名 类型 限制条件,
	......
}
``````
注意：
​	- 实体名用大驼峰方式命名，参数名用小驼峰命名，不能出现“-”，“-”等符号；
​	- 用 jdl 时也不用添加 id 字段，系统将自动添加一个 ID 字段作为主键；
​	- 字段类型有：String，Integer，Long，BigDecimal，Float，Double，Enum，Boolean，LocalDate，ZonedDateTime，Blob，AnyBlob，ImageBlob，Textblob，Instant
​	- 限制条件有：required（必须，不能为空），对于字符串类型独有 minlength（最小长度），maxlength（最大长度），pattern（正则表达式限制），对于数值类型独有 min（最小值），max（最大值），对于Blob类型独有 minbytes（最小字节），maxbytes（最大字节）；

-添加枚举
``````
// 语法格式，枚举值必须大写
enum 枚举名 {
枚举值,枚举值
}
// 例如
enum Language {
    FRENCH, ENGLISH, SPANISH
  }
// 使用枚举
entity Book {
    title String required,
    description String,
    language Language
  }
``````

- 添加关系：
关系类型：OneToMany 、 ManyToOne 、 OneToOne 、 ManyToMany
``````
// 语法
relationship <type> {
<from entity>[{<relationship name>}]
to
<to entity>[{<relationship name>}]
}
// 例如，一本书有一个作者，一个作者有多本书
relationship OneToMany {
  Author{book} to Book{writer(name)}
}
``````

- 分页
添加分页查询功能，分页方式有： pager 、 pagination 、 infinite-scroll
``````
paginate A with pagination
paginate B,C with pager
paginate D with infinite-scroll
// 全部分页
paginate * with pagination
// 排除部分实体分页
paginate all with pagination except A,B,C,D
``````

- 给实体创建 Service 
可选方式：serviceClass 、 serviceImpl
``````
service * with serviceClass
// 或
service ALL with serviceImpl
``````

- 使用 DTO 
``````
dto * with mapstruct
``````

- 其它选项
	+ skipClient 不生成前端代码
	+ skipServer 不生成后端代码
	+ angularSuffix 给 Angular 路由名称添加前缀
	+ specify 指定其他微服务中的实体名
	+ search  指定其他微服务中的搜索项

JDL 示例：
``````
/**
* 林业局
*/
entity Bureau{
    /**林业局名*/
    name String required maxlength(60)
    /**编码*/
    code String maxlength(20),
    /**地址*/
    address String maxlength(255),
    /**级别*/
    level String maxlength(20),
    /**备注*/
    remark String maxlength(250),
	createBy String maxlength(20),
	createDate ZonedDateTime,
	lastModifiedBy String maxlength(20),
	lastModifiedDate ZonedDateTime,
}

/**林场*/
entity Station{
    /**林场名*/
    name String required maxlength(60),
    /**林场编号*/
    code String maxlength(20),
    /**地址*/
    address String maxlength(255),
    /**级别*/
    level String maxlength(20),
    /**备注*/
    remark String,
	createBy String maxlength(20),
	createDate ZonedDateTime,
	lastModifiedBy String maxlength(20),
	lastModifiedDate ZonedDateTime,
}

relationship ManyToOne{
	Station{bureau}  to Bureau
}

relationship ManyToOne{
	PreventionTeam{parentUnit}  to Station
}

paginate * with pagination

service * with serviceClass
``````

#### 使用 UML 批量创建实体

这个我也没用过，先挖个坑，后面再填！

## 修改实体


## 注意事项：
### JHipster版本不同，使用的生成命令可能不同
在现在(20190304)使用的 JHipster 5.8.2 中，生成单个实体的命令为：`jhipster entity <entityName> --[options]`，使用 JDL 批量生成实体的命令变成了：`jhipster import-jdl your-jdl-file.jh`。


