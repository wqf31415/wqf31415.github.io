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

AOP，即 Aspect Oriented Programming，面向切面编程，通过预编译方式和运行期间动态代理实现程序功能的统一维护的一种技术。AOP 技术将业务逻辑进行横切，在其中加入统一的逻辑处理，这样做的好处是将与业务逻辑无关的代码独立出来，对业务逻辑代码没有侵入性。AOP 技术被广泛用在程序中的权限控制、日志记录、性能统计、安全控制、事务处理、异常处理等方面。



<!-- more -->



### 重要概念

#### 切面 Advisor

切面泛指交叉业务逻辑，比如事物处理、日志处理就可以理解为切面。切面通常是一个类，里面可以定义切入点和通知。



#### 切点 Pointcut

切入点是指切面具体织入的位置，是带有通知的连接点，在程序中主要体现为书写切入点表达式。



#### 通知 Advice

AOP 在特定的切入点上执行的增强处理，有5种，分别是： 

- before（前置），在目标方法调用前做增强处理。
- after（后置），在目标方法调用之后（不论是否成功）做增强处理。
- afterReturning（返回后），在目标方法正常完成后做增强处理。
- afterThrowing（异常），在目标方法调用抛出异常时做增强处理。
- around（环绕），在目标方法完成前后做增强处理，环绕通知时最重要的通知类型，一般日志、事务等都是使用环绕通知。



#### 连接点 Joinpoint

程序执行过程中明确的点，一般是方法的调用。被拦截到的点，因为 spring 只支持方法类型的连接点，所以在 spring 中连接点指的是被拦截到的方法，实际上连接点还可以是字段或者构造器。



#### 织入 Weaving

织入是指将切面代码插入到目标对象的过程。



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

- Spring Boot AOP的使用 : <https://www.jianshu.com/p/4d22ea402d14> 



### 总结

我们要知道的一点是，AOP 是一种编程范式，具体的实现有 AspectJ ，可以实现编译成 class 时就织入，spring aop 就是采用这种方式，另外的还有静态代理和动态代理，在运行时进行织入，如 Cglib。