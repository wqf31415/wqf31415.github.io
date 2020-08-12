---
title: SpringBoot AOP
date: 2020-08-11 19:29:16
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

切面泛指交叉业务逻辑，比如事物处理、日志处理就可以理解为切面。切面通常是一个类，其中包含了切入点和通知。



#### 切点 Pointcut

切入点是指切面具体织入的位置，是带有通知的连接点，在程序中主要体现为书写切入点表达式。



#### 通知 Advice

AOP 在特定的切入点上执行的增强处理，有5种，分别是： 

- before（前置），在目标方法调用前做增强处理。
- after（后置），在目标方法调用之后（不论是否成功）做增强处理。
- afterReturning（返回后），在目标方法正常完成后做增强处理。
- afterThrowing（异常），在目标方法调用抛出异常时做增强处理。
- around（环绕），在目标方法完成前后做增强处理，环绕通知时最重要的通知类型，一般日志、事务等都是使用环绕通知。

> 执行顺序：
>
> - 正常调用时：around -\> before -\> after -\> afterReturning
> - 调用异常时：around -\> before -\> after -\> afterThrowing



#### 连接点 Joinpoint

程序执行过程中明确的点，一般是方法的调用。被拦截到的点，因为 spring 只支持方法类型的连接点，所以在 spring 中连接点指的是被拦截到的方法，实际上连接点还可以是字段或者构造器。



#### 织入 Weaving

织入是指将切面代码插入到目标对象的过程。



### 实践

创建一个 spring web 项目来实践 aop。

#### 引入 spring-boot-starter-aop 依赖

在 springboot 项目中使用 aop 需要引入 spring-boot-starter-aop 依赖。

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

#### 创建自定义注解

使用注解可以灵活的在需要的方法添加切点。

MyAspectAnno.java

```java
@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
public @interface MyAspectAnno {
    String value() default "";
}
```



#### 定义切面类

在自定义的切面类中，使用 `@Aspect` 标记这是一个切面类，使用 `@Component` 注解标记为 spring 组件，这两个注解都需要有。

在切面类中，我们可以使用 `@Pointcut` 注解标记一个返回值为 void 方法体为空的方法，用于定义切点。

在切面类中使用 `@Around` 、`@Before` 、`@After` 、`@AfterReturning` 、`@AfterThrowing` 来标记方法来指定相应的通知处理，这些通知的注解中需要指定切点，可以引用 `@Pointcut` 注解定义切点的方法，也可以使用切点表达式来指定。

我们要添加的逻辑代码就放在这些通知方法中，这些方法中都有一个 `JoinPoint` 类型的参数（Around 通知方法中的参数 `ProceedingJoinPoint` 继承了 `JoinPoint`），。

MyAspect.java

```java
@Aspect
@Component
public class MyAspect {
        @Pointcut("@annotation(xyz.wqf.spaopdemo.aop.MyAspectAnno) || within(xyz.wqf.spaopdemo.service.*) || execution(* xyz.wqf.spaopdemo.web.rest.HelloController.throwException(..)))")
    public void myPointcut(){}

    // 前置通知
    @Before(value = "myPointcut()")
    public void beforeAdvice(JoinPoint joinPoint){
        System.out.println("Before advice start ...");
        System.out.println(joinPoint);
        System.out.println("Before advice end ...");
    }

    // 环绕通知
    @Around(value = "myPointcut()")
    public Object aroundAdvice(ProceedingJoinPoint joinPoint) throws Throwable {
        System.out.println("Around advice start ...");
        System.out.println(joinPoint);
        System.out.println("Around advice end ...");
        return joinPoint.proceed(); // 需要将结果返回，否则原方法将无法获得返回值
    }

    // 返回后通知
    @AfterReturning(value = "myPointcut()",returning = "res")
    public void afterReturningAdvice(JoinPoint joinPoint, Object res){
        System.out.println("AfterReturning advice start ...");
        System.out.println(joinPoint);
        System.out.println(res);
        System.out.println("AfterReturning advice end ...");
    }

    // 抛出异常通知
    @AfterThrowing(pointcut = "myPointcut()",throwing = "ex")
    public void afterThrowingAdvice(JoinPoint joinPoint,Throwable ex){
        System.out.println("After throwing advice start ...");
        System.out.println(joinPoint);
        System.out.println(ex);
        System.out.println("After throwing advice end ...");
    }

    // 后置通知
    @After(value = "myPointcut()")
    public void afterAdvice(JoinPoint joinPoint){
        System.out.println("After advice start ...");
        System.out.println(joinPoint);
        System.out.println("After advice end ...");
    }
}
```



#### 切点相关的类

##### 使用注解标记的切点

在启动类中开放一个 web 访问接口，在方法上添加自定义的切点注解 `@MyAspectAnno` ，然后在切点定义的时候，使用 `@Pointcut("@annotation(xyz.wqf.spaopdemo.aop.MyAspectAnno)")` 来指定切点，这样就可以给这个方法添加横切逻辑了。

项目启动后，访问 <http://localhost:8080/hi?name=abc> 即可在控制台看到切面类中定义的 advice 方法打印的信息。

```java
@SpringBootApplication
@RestController
public class SpAopDemoApplication {

    public static void main(String[] args)  {
        SpringApplication.run(SpAopDemoApplication.class, args);
    }

    @MyAspectAnno("for test")
    @GetMapping("/hi")
    public String sayHi(String name){
        return "Hi " + name;
    }
}
```



##### 使用 execution 指定的切点

在定义切点时，使用 execution 可以指定符合表达式的方法为切点，比如指定 `HelloController` 类的 `throwException` 方法为切点，可以写作 `@Pointcut("execution(* xyz.wqf.spaopdemo.web.rest.HelloController.throwException(..)))")` 。

HelloController.java

```java
@RestController
public class HelloController {
    @Autowired
    private HelloService helloService;
    
    @GetMapping("/hello")
    public String sayHello(String name){
        return helloService.sayHello(name);
    }

    @GetMapping("/ex")
    public String throwException() throws Exception {
        throw new Exception("my exception");
    }
}
```



##### 使用 within 指定的切点

在定义切点时，使用 `within(xyz.wqf.spaopdemo.service.*)` 指定 `xyz.wqf.spaopdemo.service` 包下所有方法为切点。

HelloService.java

```java
@Service
public class HelloService {
    public String sayHello(String name){
        return "Hello " + name;
    }
}
```



### 切点表达式

在使用注解 `@Pointcut` 注解指定切点时，在其中的 value 参数中指定切点，可以使用 `@annotation` 、`execution` 、`within` 、`this` 、`target` 等注解表达式来指定切点。

#### execution

execution 的用法是： execution(_[public]_ _\<returnType\>_ _\<package\>_._\<class\>_._\<method\>_(_param_)) 

- _[public]_ ：匹配公开的方法，可以省略
- _\<returnType\>_ ：返回值类型，可以使用通配符 `*` 表示接受所有类型
- _\<package\>_ ：包名，可以使用通配符 `*` 匹配所有包
- _\<class\>_ ：类名
- _\<method\>_ ：方法
- _param_ ：参数，使用 `..` 表示接受任意参数

举例：

`execution(* *(..))` 匹配所有公开类

`execution(* set*(..))` 匹配所有以 `set` 开头的方法

`execution(* xyz.wqf.server.*.*(..))` 匹配 `xyz.wqf.server` 包下所有类所有方法，第一个 `.*` 表示所有类，第二个 `.*` 表示所有方法

`execution(* xyz.wqf.server..*.*(..))` 匹配 `xyz.wqf.server` 包及其子包下所有方法，`..*` 表示任意包或子包

`execution(* xyz.wqf..MyServer.*(..))` 匹配 `xyz.wqf` 包及其子包下 `MyServer` 类中的所有方法



#### @annotation

使用 `@annotation` 表达式将指定注解标记的方法作为切点。

举例：

使用自定义的注解 `@annotation(xyz.wqf.spaopdemo.aop.MyAspectAnno)` 

使用 spring 的事务注解 `@annotation(org.springframework.transaction.annotation.Transactional)` 。



#### within

`within` 用于将指定类下的方法为切点。

举例：

`within(xyz.wqf.service.*)` 匹配 `xyz.wqf.service` 包下所有类的方法

`within(xyz.wqf.service.HelloService)` 匹配 `xyz.wqf.service` 包下的 `HelloService` 类

`within(xyz.wqf.service..*)` 匹配 `xyz.wqf.service` 包及其子包中的所有方法



#### this

实现类指定接口或继承指定类以及该类本身的所有方法，不包含父类的方法。

举例：

`this(xyz.wqf.service.IUserService)` 所有实现 `xyz.wqf.service.IUserService` 接口的所有类

`this(xyz.wqf.service.AbstractService)` 所有继承 `xyz.wqf.service.AbstractService` 抽象类及该抽象类本身的所有方法。



#### target

实现类指定接口或继承指定类以及该类本身的所有方法，包含父类的方法。

举例:

`target(xyz.wqf.service.AbstractService)`  匹配继承 `xyz.wqf.service.AbstractService` 抽象类及该抽象类本身的所有方法。



### AOP 实现原理

#### 动态代理

在调用要做 AOP 处理的方法时，系统生成一个代理类，在实际类方法前后添加横切的方法， 使用代理类来完成调用。



### 参考资料

- Springboot中Aspect实现切面（以记录日志为例）: <https://blog.csdn.net/zhuzhezhuzhe1/article/details/80565067> 
- spring aop 及实现方式 : <https://www.jianshu.com/p/5b9a0d77f95f> 
- Spring Boot AOP的使用 : <https://www.jianshu.com/p/4d22ea402d14> 
- spring aop Pointcut execution规则 : <https://blog.csdn.net/id19870510/article/details/79163639> 
- Spring 框架之 AOP 原理深度剖析 : <https://baijiahao.baidu.com/s?id=1651110900506017940> 



### 总结

我们要知道的一点是，AOP 是一种编程范式，具体的实现有 AspectJ ，可以实现编译成 class 时就织入，spring aop 就是采用这种方式，另外的还有静态代理和动态代理，在运行时进行织入，如 Cglib。