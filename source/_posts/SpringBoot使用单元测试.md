---
title: SpringBoot使用单元测试
tags:
  - java
  - spring
  - springboot
  - test
categories:
  - java
date: 2021-07-31 19:10:07
---

### 概述

这篇文章介绍了单元测试的概念，以及在 springboot 项目中如何使用单元测试来检查代码是否正确。



### 关于单元测试

> 单元测试（Unit Testing）又称模块测试，是针对程序模块（软件设计的最小单位）来进行正确性检验的测试工作。程序单元是应用程序的最小可测试部件，在过程化编程中，一个单元就是单个程序、函数、过程；对于面向对象编程，最小单元就是方法，包括基类（超类）、抽象类、或者派生类（子类）中的方法。
>
> ——维基百科



<!-- more -->

### 测试的目的

测试不仅是为了验证代码的正确性，还要确认它符合预期。测试也是一道保障，确认程序在改进的同时不会破坏已有的东西。

另外，为了让代码方便测试，会迫使你以一种合理的、可理解的和可维护的方式来构造代码，这将减少组件的耦合度并增强其聚合度，让代码质量更高。



### 测试的原则

#### AIR 原则

好的单元测试必需遵循 AIR 原则，单元测试在线上运行时像空气一样感觉并不存在，但对于测试质量的保障却是非常关键：

- A：Automatic（自动化），通常测试需要经常执行，执行过程必需完全自动化才有意义。测试过程不需要交互和人工校验，应使用 assert 校验，而不是使用 System.out 输出来校验。
- I：Independent（独立性），为了保证单元测试稳定可靠且便于维护，单元测试用例之间绝不可相互调用，也不能依赖执行的先后顺序。
- R：Repeatable（可重复），单元测试是可以重复执行的，不能受到外界环境影响。

#### 粒度与范围

要保证单元测试的粒度足够小，有助于精确定位问题，单侧粒度至多是类级别，一般是方法级别。单侧不负责检查跨类或者跨系统的交互逻辑，那是集成测试的领域。

系统核心业务、核心应用、核心模块的增量代码确保单元测试通过。新增代码要及时补充单元测试，如果新增代码影响了原有单元测试，要及时修正。

#### 单元测试代码目录

单元测试代码必需写在如下工程目录（Java工程）：`src/test/java` 不允许写在业务代码目录下。因为源码构建时会忽略此目录，而单元测试框架默认扫描此目录。

#### 数据库相关测试

对于数据库相关的查询、更新、删除等操作，不能假设数据库的数据是存在的，或者手动操作数据库插入数据，应使用程序插入或到输入数据的方式来准备数据。

可设定自动回滚机制，不给数据库造成脏数据，或者对单元测试产生的数据有明确的前后缀标识。



### 单元测试用例

测试要验证以下两点:

- 对于所有有效的输入，都会生成正确的输出。
- 对于所有无效的输入，都会生成适当的故障行为。

因此，在编写测试和用例时，要考虑到有效输入集合和无效输入集合，通常来说有效输入集合都非常打，无效输入集合更大，所以必需要挑选出一小部分具有代表性的值，可以使用 BDE 原则。

> BCDE 原则：
>
> - B：Border，边界值测试，包括循环边界、特殊取值（如 0）、特殊时间点、数据顺序等。
> - C：Corrent，正确的输入，挑选一些处于中间位置和边界附近的输入值，得到预期的结果。
> - D：Design，与设计文档相结合，让程序流程中所有条件判断的分支都能被覆盖到。
> - E：Error，强制错误信息输入，如非法数据、异常流程、非业务允许输入等。

此外，使用随机数据也是一种极为有效的测试策略，可能会发现一些你意想不到的细微错误。



### Spring Boot 中的单元测试

在单元测试中通常不需要 Spring 介入， Spring 鼓励松耦合、接口驱动的设计，这些让你很轻松的编写单元测试，但在单元测试时并不需要用到 Spring。但在集成测试时需要使用 Spring，因为集成测试时需要使用 Spring 来配置并组装组件。

#### 添加测试依赖

> 注意：本文中示例代码基于 spring boot 2.5.3 版本。

SpringBoot 官方提供了用于测试的 starter，其中引入了项目测试的工具类库，maven 依赖配置如下：

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-test</artifactId>
    <scope>test</scope>
</dependency>
```

如果是使用 spring boot 官方的 Initializr 创建的项目，默认引入了该依赖。



#### 普通类单元测试

这里的普通类是指不需要使用 Spring 注入依赖的类，这些类在进行单元测试时，可直接对其中方法创建测试代码。

普通类示例：

```java
package xyz.wqf.sbtestdemo.biz;

public class Greeting {
    public String sayHi(int gender) {
        String msg;
        if (gender == 1) {
            msg = "hi, man!";
        }else if (gender == 0){
            msg = "hi, woman!";
        }else {
            msg = "hi!";
        }
        return msg;
    }
}
```

创建测试类：使用 IntelliJ IDEA 编辑器开发时，可使用编辑器创建测试类。使用方法是打开要测试的类，点击菜单栏中 `Navigate` 中的 `Test` ，Windows 系统中默认快捷键是 <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>T</kbd> ，在弹出的选项中点击 `Create New Test...` ，随后在弹出框中勾选要测试的方法，点击确定，编辑器就帮我们生成了测试类，生成的测试类在 `src/test/java` 目录下的相同包中。

![](https://blog-images.qiniu.wqf31415.xyz/idea_create_test.png)

测试类：

```java
package xyz.wqf.sbtestdemo.biz;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class GreetingTest {

    @Test
    void sayHi() {
        Greeting greeting = new Greeting();
        assertEquals("hi!", greeting.sayHi(-1));
        assertEquals("hi, woman!", greeting.sayHi(0));
        assertEquals("hi, man!", greeting.sayHi(1));
    }
}
```

在生成的测试类中，加入了对 junit 的断言（Assertions）类的依赖，用于判断测试结果是否符合预期。

测试类中生成的测试方法都加了 `@Test` 注解，表示这是一个测试方法，在方法名一栏的左边会有一个可运行的标识，点击可运行这个方法。在运行整个测试类的时候，这些标有 `@Test` 注解的方法都会被执行。

> 注意事项：
>
> - 测试方法不能用 `private` 修饰，同时建议不用 `public` 和 `protected` 修饰，一般不加访问权限修饰符。
> - 测试方法不能有参数，返回值为 `void` 。
> - 测试类名建议为原类名加 `Test` ，测试方法名建议为原方法名。

JUnit 中还提供了丰富的注解来实现复杂的测试过程，如：

| 注解          | 功能                                 | 备注                       |
| ------------- | ------------------------------------ | -------------------------- |
| `@BeforeAll`  | 在所有测试开启前执行，用于初始化资源 | 该方法必需用 `satic` 修饰  |
| `@BeforeEach` | 在每个测试之前执行                   | 该方法禁止用 `static` 修饰 |
| `@AfterAll`   | 所有测试完成后执行，用于释放资源     | 该方法必需用 `static` 修饰 |
| `@AfterEach`  | 每个测试完成后执行                   | 该方法禁止用 `static` 修饰 |
| `@Timeout`    | 指定测试超时时间，执行超时则不通过   |                            |



#### Service 类测试

在 Service 类中，通常需要使用 Spring 注入一些依赖，以完成测试。

对于需要用到 Spring 环境的测试类，可以在类上添加 `@SpringBootTest` 注解，然后使用 `@Autowired` 注解将需要的 Bean 注入进来，在运行测试方法时会启动 Spring。

```java
package xyz.wqf.sbtestdemo.service;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import static org.junit.jupiter.api.Assertions.*;

@SpringBootTest
class GreetingServiceTest {
    @Autowired
    private GreetingService greetingService;

    @Test
    void sayHi() {
        assertEquals("hi, jack", greetingService.sayHi());
    }
}
```



#### Controller 类测试

对于控制器类，往往需要发起网络请求来测试，我们可以使用 `@WebMvcTest` 注解，它提供了自配置的 MockMvc ，可以不需要完整启动 HTTP 服务器就可以快速测试 MVC 控制器。



#### 数据库相关类测试

在测试数据库相关的类时，可以在测试类上加 `@Transactional` 注解，这样在测试完成后会自动回滚，防止在数据库中留下测试数据。



### 参考资料

- 单元测试 - 维基百科: <https://zh.wikipedia.org/wiki/%E5%8D%95%E5%85%83%E6%B5%8B%E8%AF%95> 
- 阿里巴巴Java开发手册
- 丁雪丰·Spring Boot实战
- 编程匠艺：编写卓越的代码（第二版）
- Spring Boot使用单元测试: <https://blog.csdn.net/sz85850597/article/details/80427408> 
