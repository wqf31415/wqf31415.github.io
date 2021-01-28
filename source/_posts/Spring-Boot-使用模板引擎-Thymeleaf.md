---
title: Spring Boot 使用模板引擎 Thymeleaf
date: 2019-05-13 11:23:53
tags:
- java
- thymeleaf
- springboot
categories:
- java
---

### 概述
在这篇文章中介绍了 Thymeleaf 模板引擎，以及在 SpringBoot 项目中使用 Thymeleaf 模板引擎渲染页面。

### 什么是模板引擎
在 MVC 架构中，实行模型(Model)、视图(View)和控制器(Controller)分离，降低代码耦合性，模板引擎就是用来渲染视图展示页面的。
模板引擎将模型(Model) 与预先定义好的页面模板进行解析渲染，往页面中填入数据，最终产生给用户看的视图页面。

数据 + 模板 ==(模板引擎)==> 视图页面

<!-- more -->

### 主流的 Java 模板引擎
#### thymeleaf
> thymeleaf 中文译为 百里香的叶子 ，读音为 /taɪm liːf/。官网：<https://www.thymeleaf.org>

SpringBoot 官方推荐的模板引擎。
thymeleaf 支持的模板文件类型包括 HTML(包括 html5、xhtml 1.0/1.1、html4)、XML、TEXT(plain text)、JAVASCRIPT(.js 文件)、CSS(.css 文件)。也可以用于非 web 项目。

#### freemarker
官网：<https://freemarker.apache.org>

#### jsp
全名为 Java Server Pages，是早期出现的 java web 模板引擎，约 2016 年，java web 工程还是使用 servlet 和 jsp 实现页面展示，前端访问资源时，后台将渲染好的 html 页面返回给浏览器。

#### velocity
> 官网：<http://velocity.apache.org>

### 在  Spring Boot  项目中体验  Thymeleaf

#### 初始化项目

使用 <https://start.spring.io> 或 IDE 创建一个 spring boot 项目并引入 Web 和 Thymeleaf 依赖。项目 `pom.xml` 内容如下：

```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.1.7.RELEASE</version>
        <relativePath/> <!-- lookup parent from repository -->
    </parent>
    <groupId>xyz.wqf31415</groupId>
    <artifactId>thymeleafdemo</artifactId>
    <version>0.0.1-SNAPSHOT</version>
    <name>thymeleafdemo</name>
    <description>Demo project for Spring Boot</description>

    <properties>
        <java.version>1.8</java.version>
    </properties>

    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-thymeleaf</artifactId>
        </dependency>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>

        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-test</artifactId>
            <scope>test</scope>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <plugin>
                <groupId>org.springframework.boot</groupId>
                <artifactId>spring-boot-maven-plugin</artifactId>
            </plugin>
        </plugins>
    </build>

</project>
```

#### 创建模板文件

thymeleaf 默认的模板文件存放路径是在 `templates` 目录，如果没有可以手动创建。

在项目 `src/main/resources/templates` 目录下创建模板文件 `hello.html`，内容如下：

```html
<!DOCTYPE html>
<html lang="en" xmlns:th="http://www.thymeleaf.org">
<head>
    <meta charset="UTF-8">
    <title>hello</title>
</head>
<body>
<h2>hello, <span th:text="${name}"></span></h2>
</body>
</html>
```

> 注意，在 html 标签中，我们添加了 thymeleaf 的 th 前缀命名空间，方便直接使用。

#### 创建 Controller

创建一个 Java 类 `HelloController.java` ，在类上添加注解 `@Controller` 表明这是一个 controller，增加方法并加上 `@RequestMapping` 注解，这个方法的返回值类型是 String，返回值是 `hello` ，即刚才我们定义好的模板文件的文件名(文件后缀 `.html` 可以省略)。

```java
package xyz.wqf31415.thymeleafdemo.web.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

/**
 * Created by Administrator on 2019/8/9.
 *
 * @author Administrator
 */
@Controller
public class HelloController {
    @RequestMapping(value = "/hello")
    public String hello(@RequestParam String name, Model model){
        model.addAttribute("name",name);
        return "hello";
    }
}
```

#### 访问页面

在浏览器中访问创建的请求api： <http://localhost:8080/hello?name=world> 

页面中显示 `hello, world` ，说明已经模板引擎已经正常工作了。

### 生成模板页面

一般我们在网站上用邮箱注册账号时，网站会发送一封验证码的邮件到我们邮箱中，这封邮件中除了验证码，其他内容都是固定的，所以我们可以使用模板引擎很方便的生成页面内容。



### 注意事项

#### 禁用缓存，开发时模板引擎实时生效

在开发时我们可以添加配置项来禁用 thymeleaf 的缓存，这样在修改页面后，不重启项目就能看到效果了：

```properties
#禁用模板引擎的缓存
spring.thymeleaf.cache=false
```

在使用 InteliJ IDEA 开发时，修改完页码后，可以按 <kbd>Ctrl</kbd> + <kbd>F9</kbd> 快捷键，把项目 Build 一下，然后就可以刷新页面查看效果了。

#### 页面中的 JavaScript 符号错误

当模板页面中使用 JavaScript 脚本时，某些字符将导致解析错误，如 `<` 、 `>` 、`&` 等。例如：

```html
<script>
    function test(){
        for (var i=0; i < 10; i++){
            console.log(i);
        }
    }
</script>
```

**解决办法**：

将导致错误的代码用 `/* <![CDATA[ */` 和 `/* ]]> */` 括起来，如下：

```html
<script>
    function test(){
        /* <![CDATA[ */
        for (var i=0; i < 10; i++){
            console.log(i);
        }
        /* ]]> */
    }
</script>
```



### 总结

虽然现在项目开发都讲究前后端分离，但模板引擎在某些特定场景下使用还是非常方便，比如生成通知邮件页面、广告页面等。