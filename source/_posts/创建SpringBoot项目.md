---
title: 创建SpringBoot项目
date: 2017-11-27 22:52:41
tags:
- java
- spring
- springboot
categories:
- java
---

## 什么是 SpringBoot ?
> 官网：[http://projects.spring.io/spring-boot/](http://projects.spring.io/spring-boot/ "springboot官网")

![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_logo.png ) 

简单来说，SpringBoot 的出现是为了简化Spring项目的创建、运行、调试、部署过程，boot的意思是启动、引导，整体来说就是快速启动 Spring。springboot 并不是一个新的框架，它只是spring的一个封装，从根本上讲就是一些库的集合，帮助开发者快速构建spring 项目，项目里面还是使用 spring 框架实现，所以 Spring 能做的，SpringBoot 也能做，而且做的更方便、快捷。

在使用 Spring 开发的时候，写项目时有伴有大量的 xml 配置文件要编写，随着快速开发的流行，这种方式已经不能满足需要了，springboot 的出现帮我们简化了项目配置，同时提供了很多注解，让我们编码也变得简单了。**SpringBoot 简化了配置，不用再写 xml 了** ,传统 Spring 项目的 xml 配置文件被转化成 java config，直接利用 @Autowire 注解注入 Bean，而环境变量中的 properties、xml 文件集中到一个application.yml中。同时，**SpringBoot 使项目部署变得简单**，传统的Spring项目需要外部的 tomcat 容器来运行，而在springboot 中已经集成了 tomcat ，我们将项目打包成一个 jar 包，直接通过 `java -jar xxx.jar` 就可以运行项目，这也方便后续使用 docker 。

SpringBoot 能够使我们更加专注于业务逻辑的开发，只需记住 **Just run** 就可以了，那怎么创建一个 SpringBoot 项目呢？话不多说，还是先上个 demo 尝尝味道吧！全文里介绍了一个 SpringBoot 项目从创建到测试运行，再到打包部署的全过程。

<!-- more -->

## 创建 SpringBoot 项目
### 开发环境及工具
- **java 1.8+** springboot 是Javaweb开发框架，所以java开发环境是必要的，从[Oracle官网](http://www.oracle.com/)上下载java1.8的安装包，安装到计算机上，并配置好环境变量。

- **maven 3.2+** 利用 maven 下载管理项目中需要的依赖资源，从 [maven官网](http://maven.apache.org/) 下载 maven，解压到本地，将bin目录配置到环境变量 path 中，方便使用，为了提升依赖下载速度，建议配置阿里镜像。

- **IDE** 我们使用 IntelliJ IDEA 工具来创建 spring boot 项目，所谓 “工欲善其事必先利其器”，我个人习惯使用 IDEA 来开发 java项目。也可以使用其它开发工具，比如 **eclipse** ，或官方推荐使用的 [Spring Tool Suite](https://spring.io/tools) 。


### 使用 maven 创建 SpringBoot 项目
#### 用IDEA创建maven项目框架
- 打开IDEA，点击 **Create New Project** 创建项目
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_project_create_01.png "创建项目")


- 选择maven项目，Project SDK 选择 java1.8（如果没有，点击 **New...** 选择java安装路径），点击 **Next**
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_project_create_02.png "选择maven项目和java版本")


- 填入 GroupId 和 ArtifactId，点击 **Next**
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_project_create_03.png "填写项目信息")
> GroupId 一般是公司域名倒序，如域名为 xxx.com，GroupId 就写com.xxx。ArtifactId 为模块名，也就是项目名。


- 填写项目名和存储路径，点击 **Finish**
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_project_create_04.png "填写项目名称及存储路径")


- 完成项目创建，这是一个maven项目，目前还只有项目骨架
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_project_create_05.png "")



#### 添加 SpringBoot 的依赖
- 将 springboot 最基础的依赖包加入到 maven 项目的 **pom.xml** 中
``````xml
<!--parent中定义了SpringBoot的基础依赖及一些默认配置内容，如配置文件的位置application.properties-->
<parent>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-parent</artifactId>
    <version>1.5.8.RELEASE</version>
</parent>
<dependencies>
  	<!--全栈web开发模块，包含嵌入式Tomcat、Spring MVC-->
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
</dependencies>
``````

- 用IDEA下载需要的包，将自动导入springframework的包，以及tomcat、日志等web项目需要的包
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_project_create_06.png "导入的包") 


#### 编写项目逻辑代码
- 写一个简单的 controller 用来测试，在 src/main/java 下新建一个包 **hello** ，在其中新建一个java类 **SampleController**，其中代码如下：
``````java
package hello;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * Created by wqf31 on 2017/11/27.
 */
@SpringBootApplication
@RestController
public class SampleController {

    @RequestMapping("/")
    public String home(){
        return "hello springboot!";
    }

    public static void main(String[] args) {
        SpringApplication.run(SampleController.class,args);
    }
}
``````

#### 运行项目
- 在IDEA中点击 **Run** 菜单中的 **Edit Configuration**，进入配置编辑界面
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_project_create_07.png "点击 Edit Configuration")

- 点击左上角的 “**+**”，选择 **SpringBoot**
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_project_create_08.png "新增一个SpringBoot配置项目")

- Main Class 选择刚才创建的类，点击 **OK** 完成配置
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_project_create_09.png "选择刚才创建的类")

- 运行项目，点击IDEA工具栏中的运行图标
  ![](http://blog-images.qiniu.wqf31415.xyz/idea_run.png "运行项目")

- 运行结果，如果项目启动，并在控制台打出如下日志信息，说明已经成功启动
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_project_create_10.png "项目启动成功")

- 访问 [http://localhost:8080](http://localhost:8080 ) ，页面显示 hello springboot! 


### 使用 Spring Initilizr 创建SpringBoot项目
> 注意：创建过程需要联网，访问 https://start.spring.io

#### 使用 IDEA 中提供的 Spring Initilizr 创建
- 点击 Create New Project ，选择 **Spring Initilizr**，点击 **Next**
  
  > 初始化服务地址可以换成阿里的：https://start.aliyun.com/ 
  >
  > 使用阿里的创建 springboot 项目时的选项和官方的不太一样，创建的项目也略有不同，不过用起来同样方便。
  
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_initializr_02.png "选择 Spring Initilizr")
  
- 选择java版本、创建方式、打包方式、填写项目信息，点击 **Next** 

  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_initializr_03.png "选择java版本，填入项目信息")

- 选择需要的依赖，这里列出了所有可能需要的库，根据需要进行选择，选择完成后点击 **Next**，现在只是创建简单的java web项目体验，所以我们只选择 **Web** 依赖，点击 **Next**
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_initializr_04.png "选择需要的依赖")
  
- 填写项目名称及存储路径，点击 **Finish** 完成项目创建
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_initializr_05.png "填写项目名称及存储路径")

#### 使用 Spring Initilizr 网页版创建
- 进入网站 [https://start.spring.io](https://start.spring.io) ，填入项目相关信息及依赖，点击 “**Create Project**” 按钮即可将初始化完成的项目zip压缩包下载到本地
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_initializr_01.png "Spring Initilizr")


- 将demo项目从压缩包解压出来，导入到IDEA中，导入maven的依赖，完成项目创建
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_initializr_06.png "项目结构")


- 自动创建的pom.xml 内容如下：
  ``````xml
  <?xml version="1.0" encoding="UTF-8"?>
  <project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
	<modelVersion>4.0.0</modelVersion>
  
	<groupId>com.example</groupId>
	<artifactId>demo</artifactId>
	<version>0.0.1-SNAPSHOT</version>
  	<!--打包类型-->
	<packaging>jar</packaging>
  
	<name>demo</name>
	<description>Demo project for Spring Boot</description>
  
	<parent>
		<groupId>org.springframework.boot</groupId>
		<artifactId>spring-boot-starter-parent</artifactId>
		<version>1.5.8.RELEASE</version>
		<relativePath/> <!-- lookup parent from repository -->
	</parent>
  
	<properties>
		<project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
		<project.reporting.outputEncoding>UTF-8</project.reporting.outputEncoding>
		<java.version>1.8</java.version>
	</properties>
  
	<dependencies>
		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-web</artifactId>
		</dependency>
		<!--通用测试模块，包含Junit、Hamcrest、Mockito-->
		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-test</artifactId>
			<scope>test</scope>
		</dependency>
	</dependencies>
	<!--SpringBoot maven插件-->
	<build>
		<plugins>
			<plugin>
				<groupId>org.springframework.boot</groupId>
				<artifactId>spring-boot-maven-plugin</artifactId>
			</plugin>
		</plugins>
	</build>
  </project>
  ``````

#### 运行测试
- **用IDEA启动**，在IDEA中直接点击工具栏中的运行按钮，即可运行项目，运行起来后到浏览器中访问：[http://localhost:8080](http://localhost:8080 ) ，发现显示如下页面，这说明项目已经正确的运行起来了，只是我们还没有写controller来处理请求，所以返回这个错误提示页面。
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_initializr_07.png )

- **使用springboot maven插件运行**，因为Spring Boot Maven插件中包含一个run目标，可以用来快速编译和运行程序，这种运行模式是热加载，可以即时编辑资源。进入项目根目录，运行指令 `mvn spring-boot:run`，会编译并运行项目。类似的，如果项目用gradle构建，可以运行 `gradle bootRun` 来运行项目。

- 如果运行测试的时候发现项目启动不了，控制台输出 `Unregistering JMX-exposed beans on shutdown`
  原因是在创建项目时没有选择web依赖，创建的项目没有导入web工程所需的依赖，所以此时我们可以将 pom.xml 中springboot依赖的 artifactId，原来是 spring-boot-starter，改成 spring-boot-starter-web，再次导入需要的依赖即可正常启动。
  原来的：
``````xml
	<dependency>
		<groupId>org.springframework.boot</groupId>
		<artifactId>spring-boot-starter</artifactId>
	</dependency>
``````

	修改后的：
	​``````xml
		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-web</artifactId>
		</dependency>
	​``````

### 使用SpringBoot-Cli 安装 springboot
CLI 意思是 Command Line Interface，即命令行界面，使用命令行工具是体验 SpringBoot 的最佳方式，也是快速开发 Spring 的方法。
#### 下载、安装、配置 SpringBoot-Cli
> SpringBoot-Cli 下载地址：[http://repo.spring.io/release/org/springframework/boot/spring-boot-cli/](http://repo.spring.io/release/org/springframework/boot/spring-boot-cli/ "下载地址")

- 打开链接后发现有很多历史版本可以选，根据需要选择下载，推荐下载最新发行版：1.5.8.RELEASE/
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_cli_01.png "下载springboot-cli 1.5.8")

- 在windows系统下，我们选择下载 zip 压缩包
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_cli_02.png "下载zip压缩包")

- 解压文件，并将 bin 目录配置到系统环境变量 path 中，这样在任意路径下都可以使用
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_cli_03.png "配置环境变量")

- 测试安装结果，打开命令行工具（windows键 + R，运行 cmd），指定指令 `spring --version` ，如果正确显示spring cli 版本号，说明安装正确
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_cli_04.png "查看spring cli 版本")

- 使用 `spring help` 指令可以获取更多帮助信息

#### 用springboot-cli创建SpringBoot项目
- 在要存储项目的目录下打开命令行工具，执行指令 `spring init --dependencies=web spring-boot-demo`，（其中 **spring-boot-demo** 是项目名，也是模块名，artifactId），会访问 https://start.spring.io/ ，过一会就会将项目需要的文件下载到 /spring-boot-demo 目录下，将其导入IDEA下载相关maven依赖后就可以启动。如果需要多个依赖可以在参数后面，如 `spring init --dependencies=web,jpa spring-boot-demo` 。
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_cli_07.png "使用springboot-cli创建项目")

#### 一个文件体验springboot
- 写一个 java 测试文件，文件名为：**app.java**，内容如下：
``````java
@RestController
public class Hello {
    @RequestMapping("/")
    public String hello() {
        return "Hello Spring Boot!";
    }
}
``````

- 也可以写一个 groovy 文件来测试，文件名为： **app.groovy**，内容如下：
``````groovy
@RestController
class Hello {
    @RequestMapping("/")
    def hello() {
        return "Hello SpringBoot Groovy!";
    }
}
``````

#### 运行测试
- 进入到测试文件目录下，打开命令行工具，使用SpringBoot-CLI 提供的 **spring run <文件>** 指令来启动SpringBoot。如果是java测试文件，执行指令 `spring run app.java`，如果是groovy测试文件，执行指令 `spring run app.groovy`，打出如下日志，说明已经正确启动项目
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_cli_05.png "成功在8080端口启动项目")
- 打开浏览器，进入 [http://localhost:8080](http://localhost:8080) 页面，显示 Hello Spring Boot!




## 单元测试

在项目中引入 spring-boot-starter-test 模块后，就可以使用 Junit 进行单元测试。
``````xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-test</artifactId>
    <version>1.5.9.RELEASE</version>
    <scope>test</scope>
</dependency>

``````

自动生成的 SpringBoot 项目中的test目录就是用来存放单元测试代码的，我们可以把生成的单元测试类放到这里，建议单元测试类的目录结构与源代码的目录结构保持一致，规范管理，方便查找。

单元测试类需要添加两个注解，`@RunWith(SpringRunner.class)` 和 `@SpringBootTest(classes = DemoApplication.class)` ，前者用于引入 Spring 对 Junit 的支持，后者用于指定 SpringBoot 的启动类（参数为项目中启动类的class），在测试时就可以使用 `@Autowired` 注解注入需要的 bean 或 service 等。在运行测试方法时会将整个项目都运行起来，最后完成测试后退出。

``````java
// 测试类代码
@RunWith(SpringRunner.class)
@SpringBootTest(classes = DemoApplication.class)
public class ControllerTest {
    @Autowired
    private HelloService helloService;

    @Test
    public void testHello(){
        String result = helloService.sayHello();
        System.out.println(result);
    }
}
``````

``````java
// 被测试的 service 类，其中 appName 属性是依靠 Spring 注入的
@Service
public class HelloService {
    @Value("${spring.application.name}")
    private String appName;
    
    public String sayHello(){
        return "Hello "+appName;
    }
}
``````



## 项目打包部署
> 我们的 SpringBoot 项目是使用 maven 工具来构建的，所以我们可以很方便的使用maven来打包项目。

### 引入打包插件
> 当我们创建的是maven项目，我们可以在依赖中添加打包方式和 spring-boot-maven-plugin 打包插件（如下所示），利用maven来打包。如果是使用 Spring Initilizr 方式创建的项目，已经导入了打包插件，不用手动添加，可以在 pom.xml 中看到，如下代码：

``````xml
	<!-- 打包方式：jar 或 war -->
	<packaging>jar</packaging>
	
	<!-- spring-boot-maven-plugin 打包插件 -->
	<build>
		<plugins>
			<plugin>
				<groupId>org.springframework.boot</groupId>
				<artifactId>spring-boot-maven-plugin</artifactId>
			</plugin>
		</plugins>
	</build>
``````



### 使用IDEA打包

- 如图所示，点击IDEA侧边的 **Maven Projects** → 项目名 “**demo**” → **Lifecycle** → **package** 或 **install**，点击上方的绿色播放按钮“Run Maven Build”开始打包。使用IDEA 的maven项目管理功能打包完成后，提示 “ **BUILD SUCCESS** ”，说明打包成功，在项目根目录下的 target目录下存放着打包好的项目文件，文件名为：demo-0.0.1-SNAPSHOT.jar，如果打包方式为 war，将产生 .war 的包。
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_maven_package_01.png "IDAE maven 打包")

- 使用 maven 指令打包，进入到项目根目录，打开命令行工具，执行 maven 打打包命令 `mvn package` 或 maven 的安装命令 `mvn install` 开始打包，打包完成后提示 **BUILD SUCCESS**，说明打包成功，可以到target目录下查看打好的包。<small>(打包前最好先使用 `mvn clean` 清除以前编译的内容，或者使用 `mvn clean package` 命令先清空再编译打包。如果需要跳过测试可增加参数，如 `mvn clean package -D maven.test.skip=true` 。)</small> 

- 使用 SpringBoot-CLI 打包，前面的示例中，我们可以只写一个 java 或groovy文件就用 springboot-cli 启动了项目，现在我们只需要执行 `spring jar app.jar *.java`，就可以打包成一个名叫 app.jar 的包了，同样可以执行 `spring jar app.jar *.groovy` 来打包groovy文件。使用 `spring init` 指令创建的项目也是maven项目，打包方式参考上面两条。
  ![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_cli_06.png "使用springboot-cli打包")



### 部署及运行打包的项目

- jar 包：使用 `java -jar <文件名>` 命令运行 jar 包，在target目录下打开命令行工具，执行指令 `java -jar demo-0.0.1-SNAPSHOT.jar`，项目可以正常启动，并可以在浏览器中访问，说明打包正确。

  > 在使用 jar 包运行时，可以在运行命令中指定运行参数，如
  >
  > 设定字符编码为 UTF-8，防止乱码：
  >
  > `java -jar -Dfile.encoding=utf-8 demo.jar` 
  >
  > 设置运行的端口：
  >
  > `java -jar --server.port=8081 demo.jar` 

- war 包：使用 Tomcat 运行 war 包，如果在 pom.xml 中设置的打包方式是 war，使用maven打包出来的将是一个 war 包，我们可以把它放到 Tomcat 的 webapps 路径下，启动 Tomcat 时将会自动解压并运行项目，在浏览器中测试是否能够正常访问。



### 打包 web 资源

当我们使用 SpringBoot 创建了 web 项目，web 前端的内容一般放在 `src/main/webapp` 目录下，打包时往往需要将前端的内容一起打包，这时需要修改 `pom.xml` 中打包配置，增加资源配置。在 `bulid` 项中增加子项 `resources` ，在其中的 `resource` 中添加要打包的资源。使用相同的方法还可以打包其它目录下的资源。

示例：

```xml
<build>
    <resources>
        <!-- 打包 webapp 目录下的资源 -->
        <resource>
            <!-- 指定原始资源路径 -->
            <directory>${basedir}/src/main/webapp</directory>
            <!-- 打包后的路径 -->
            <targetPath>META-INF/resources</targetPath>
            <!-- 包含的资源 -->
            <includes>
                <include>**/**</include>
            </includes>
        </resource>
        <!-- 打包 resources 目录下的资源 -->
        <resource>
        <directory>${basedir}/src/main/resources</directory>
        <includes>
            <include>**/**</include>
        </includes>
    </resource>
    </resources>
    </resources>
    <plugins>
        <plugin>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-maven-plugin</artifactId>
        </plugin>
    </plugins>
</build>
```






## 完结撒花
![](http://blog-images.qiniu.wqf31415.xyz/%E5%AE%8C%E7%BB%93%E6%92%92%E8%8A%B1.jpg )



