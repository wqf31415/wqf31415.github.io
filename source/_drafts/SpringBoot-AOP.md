---
title: SpringBoot AOP
date: 2020-07-02 09:22:16
tags:
- java
- spring
- springboot
categories:
- java

---

### 概述

IOC 和 AOP 是 spring 的两大特性，这篇文章介绍了如何在 springboot 项目中使用 aop 特性。



### AOP

AOP，即 Aspect Oriented Programming，面向切面编程，通过预编译方式和运行期间动态代理实现程序功能的统一维护的一种技术。AOP 技术将业务逻辑进行横切，在其中加入统一的逻辑处理，减少了重复代码，降低了模块之间的耦合度。被广泛用在程序中的日志记录、性能统计、安全控制、事务处理、异常处理等方面。



<!-- more -->



### 重要概念

#### 切面 Advisor

切面通常是一个类，里面可以定义切入点和通知。



#### 切点 Pointcut

切入点是指带有通知的连接点，在程序中主要体现为书写切入点表达式。



#### 通知 Advice

AOP 在特定的切入点上执行的增强处理，有六种，分别是： 

- before（前置），在目标方法调用前做增强处理。
- after（后置），在目标方法调用之后（不论是否成功）做增强。
- afterReturning（最终），在目标方法正常完成后做增强处理。
- afterThrowing（异常），在目标方法调用抛出异常时做增强处理。
- around（环绕），在目标方法完成前后做增强处理，环绕通知时最重要的通知类型，一般日志、事务等都是使用环绕通知。



#### 连接点 Joinpoint

程序执行过程中明确的点，一般是方法的调用。被拦截到的点，因为 spring 只支持方法类型的连接点，所以在 spring 中连接点指的是被拦截到的方法，实际上连接点还可以是字段或者构造器。



### 实践

创建一个 spring web 项目来实践 aop。

#### 引入 spring-boot-starter-aop 依赖

```xml
<!-- 为了节省篇幅，只展示关键依赖配置 -->
<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>

    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-aop</artifactId>
    </dependency>
</dependencies>
```









### 参考资料

- Springboot中Aspect实现切面（以记录日志为例）: <https://blog.csdn.net/zhuzhezhuzhe1/article/details/80565067> 

- spring aop 及实现方式 : <https://www.jianshu.com/p/5b9a0d77f95f> 





### 总结

