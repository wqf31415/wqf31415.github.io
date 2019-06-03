---
title: Spring Boot 使用模板引擎 Thymeleaf
date: 2019-05-13 11:23:53
tags:
- java
- thymeleaf
- springboot
categories:
- 技术
---

### 概述
在这篇文章中介绍了Thymeleaf 模板引擎，以及在 SpringBoot 项目中使用 Thymeleaf 模板引擎渲染页面。

### 什么是模板引擎
在 MVC 架构中，实行模型(Model)、视图(View)和控制器(Controller)分离，降低代码耦合性，模板引擎就是用来渲染视图展示页面的。
模板引擎将模型(Model) 与预先定义好的页面模板进行解析渲染，往页面中填入数据，最终产生给用户看的页面。

### 主流的 Java 模板引擎
#### thymeleaf
> 官网：<https://www.thymeleaf.org>

SpringBoot 官方推荐的模板引擎。
thymeleaf 支持的模板包括 HTML(包括 html5、xhtml 1.0/1.1、html4)、XML、TEXT(plain text)、JAVASCRIPT(.js 文件)、CSS(.css 文件)。也可以用于非 web 项目。

#### freemarker
官网：<https://freemarker.apache.org>

#### jsp
全名为 Java Server Pages，是早期出现的 java web 模板引擎，

#### velocity
> 官网：<http://velocity.apache.org>


### 在 Spring Boot 项目中使用 Thymeleaf

### 注意事项

### 小结

