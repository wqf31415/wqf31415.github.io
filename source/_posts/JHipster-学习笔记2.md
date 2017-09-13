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

当你创建好一个项目后，你下一步要做的可能就是添加实体了，对于每个实体，你都需要：

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



以上内容只需要一条指令即可完成：` yo jhipster:entity [options] <name> ` ，需要帮助可以执行 `yo jhipster:entity --help` 指令，然后我们会看到指令的说明。

options 为可选项：

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



**【例】** 要创建一个 Book 实体，我们可以输入指令：`yo jhipster:entity Book` ，然后根据需要添加实体的属性和关联关系即可：

Do you want to add a field to your entity? (Y/n)	

What field name of your field?

What is the type of your field? (Use arrow keys)

- String
- Integer
- Long
- Float
- Double
- BigDecimal
- LocalDate
- ZonedDateTime
- Boolean
- Enumeration (Java enum type)
- [BETA] Blob

Do you want to add validation rules to your field? (y/N)

Which validation rules do you want to add? (Press \<apace\> to select, \<a\> to toggle all, \<i\> to inverse selection)

- ( ) Required
- ( ) Minimum length
- ( ) Maximum length
- ( ) Regular expression pattern

What is the minimum length of your field? (0)

What is the maximum length of your field? (20)

What is the regular expression pattern you want to apply on your field? (^[a-zA-Z0-9]*$)

Do you want to add a relationship to another entity? (Y/n)

What is the name of the other entity?

What is the name of the relationship? (Auther)

What is the type of the relationship? (Use arrow keys)

- one-to-many
- many-to-one
- many-to-many
- one-to-one

What the name of this relationship in the other entity? (book)

Do you want to use a Data Transfer Object (DTO)? (Use arrow keys)

- No, use the entity directly?
- [BETA] Yes, generate a DTO with MapStruct

Do you want to use separate service class for your business logic? (Use arrow keys)

- No, the REST controller should use the repository directly
- Yes, generate a separate service class
- Yes, generate a separate service interface and implementation

Do you want pagination on your entity? (Use arrow keys)

- No
- Yes, with a simple pager
- Yes, with pagination links
- Yes, with infinite scroll







