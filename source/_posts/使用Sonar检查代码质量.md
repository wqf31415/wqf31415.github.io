---
title: 使用Sonar检查代码质量
date: 2021-01-23 11:31:08
tags:
- bug
- test
- 开发
- 工具
categories:
- 工具
---

### 概述

这篇文章简单介绍了代码质量检测工具——Sonar，并使用 Sonar 对项目进行代码质量检查与管理。



### 认识 Sonar

![](https://blog-images.qiniu.wqf31415.xyz/sonarqube.png)

> sonar ，读作 `/ˈsoʊnɑːr/` ，意为声呐，声波定位仪。

Sonar 是一个开源的代码质量监测与管理软件，能够检测出不规范的代码，分析代码中的漏洞，分析单元测试覆盖率等。

Sonar 基于 web 访问，无需安装客户端。具有版本控制，提供多用户、多角色管理。

Sonar 支持 java、C#、Go、Python、Ruby、JavaScript、Kotlin 等二十多种语言。

> Sonar 官网: <http://www.sonar.org.cn/> 

<!-- more -->



### Sonar 的功能

Sonar 的主要功能是进行代码质量检测，检测的内容包括如下几点：

- 不遵循规范的代码：使用 PMD、CheckStyle、Findbugs 等代码规则检测工具规范代码编写。
- 潜在缺陷：使用 PMD、CheckStyle、Findbugs 等检测潜在缺陷。
- 复杂度分布：检测文件、类、方法的复杂度，防止复杂度过高导致维护困难。
- 重复代码：检测代码中复制粘贴的重复代码。
- 注释过多或不足：分析代码注释，提示注释过多和缺少注释的代码。
- 单元测试覆盖率：统计并展示单元测试的覆盖率。
- 检测耦合：能够找出循环，展示包与包、类与类之间的依赖关系。
- 提高代码质量：了解编码过程中犯过的错误，让自己的代码更有可读性和维护性。



### 使用

Sonar 提供的代码质量检测软件名称叫 SonarQube，官方提供了四个版本，分别是社区版、开发者版、企业版、数据中心版，其中社区版可免费使用。



#### 下载安装

> SonarQube 下载地址：<https://www.sonarqube.org/downloads/> 

从 Sonar 官方网站下载软件 SonarQube 的社区版安装包，解压后进入 `/bin` 目录，根据操作系统不同执行相应的启动脚本，即可启动。这里我是在本地测试，使用的是 Windows 系统，运行 `/bin/windows-x86-64/StartSonar.bat` ，即可启动。

此外，SonarQube 还可使用 docker 启动：

```bash
docker run -d --name my-sonarqube -p9000:9000 sonarqube:8.6.0-community
```

安装完成后，使用浏览器访问 <http://localhost:9000> ，刚启动时 SonarQube 需要一段时间进行初始化，随后进入登陆界面，使用默认用户名 `admin` 密码 `admin` 登陆，修改密码后，即可开始享用 SonarQube。

![](https://blog-images.qiniu.wqf31415.xyz/sonarqube_login.png) 



#### 中文界面

SonarQube 默认界面为英文，可安装中文包，方便使用。

点击 **Administration** 菜单，点击 **Marketplace** 子菜单，在 Plugins 搜索栏中搜索 `Chinese` ，安装中文包 `Chinese Pack` ，安装完成后需要重启 SonarQube。(页面上会提示安装了新插件需要重启，点击页面按钮即可完成重启)

![](https://blog-images.qiniu.wqf31415.xyz/sonarqube_chinese_pack.png)



#### 检测代码质量

##### 创建项目

检测代码质量前需要先创建项目。登陆 SonarQube ，点击 **项目** 菜单，创建新项目，或点击右上角 **+** 按钮，创建项目。填入项目表示和名称后，还需要创建一个令牌，在执行分析时要使用。

![](https://blog-images.qiniu.wqf31415.xyz/sonarqube_create_project.png)



##### 分析代码

###### 使用令牌分析

创建令牌后，页面会提示分析项目，根据页面提示选择项目构建类型，SonarQube 会给出检测方法。

![](https://blog-images.qiniu.wqf31415.xyz/sonarqube_analysis_maven.png)

这里我用来检测一个使用 maven 构建的 springboot 测试项目，所以选择 Maven，按页面提示在项目根目录执行命令：

```bash
mvn sonar:sonar \
  -Dsonar.projectKey=test-demo \
  -Dsonar.host.url=http://localhost:9000 \
  -Dsonar.login=8eb24fc4c59931effa3bb6f44a63f9e3071690b5
```

> 这里使用了生成的令牌进行身份验证，这个令牌如需多次使用，要记住，不能再次查看已生成的令牌内容。如果忘记，可以删除令牌重新生成。
>
> 参数说明：
>
> - `sonar.projectKey` : 项目标识，注意不是显示的项目名，可以在项目页面查看项目信息，里面有项目标识
> - `sonar.host.url` : SonarQube 的服务地址
> - `sonar.login` : SonarQube 登陆令牌或登陆用户名



###### 不使用令牌分析

在不使用令牌进行分析时，可以在执行的命令中指定用户名（`sonar.login`）和密码（`sonar.password`），如：

```bash
mvn sonar:sonar -Dsonar.projectKey=test-demo -Dsonar.host.url=http://localhost:9000 -Dsonar.login=admin -Dsonar.password=123456
```



执行结果：

![](https://blog-images.qiniu.wqf31415.xyz/sonarqube_do_analysis.png)



##### 查看检测结果

分析命令执行完成后，返回 SonarQube 的 web 页面查看检测结果。这次检测结果如下所示，发现的问题有：

- 2 个安全性漏洞
- 单元测试率为 0 

![](https://blog-images.qiniu.wqf31415.xyz/sonarqube_analysis_result.png)

点击 **问题** 菜单，查看漏洞详情，能够按照多种方式进行过滤，这里我们选择查看 `严重` 级别的问题。

![](https://blog-images.qiniu.wqf31415.xyz/sonarqube_analysis_issue.png)



##### 整改

根据检测结果对项目代码进行整改，整改完成后再次检测。

![](https://blog-images.qiniu.wqf31415.xyz/sonarqube_analysis_modify.png)



#### 遇到的问题

##### 需要 java 11 环境

运行时提示 `WrapperSimpleApp: Encountered an error running main: java.lang.IllegalStateException: SonarQube requires Java 11 to run` ，表示软件运行需要 java 11 环境。

**解决办法**：

下载 jdk 11，解压后，修改 sonarqube 配置 `/conf/wrapper.conf` ，修改配置项 `wrapper.java.command` 修改成 jdk 11 中的 java 即可。

```properties
# Path to JVM executable. By default it must be available in PATH.
# Can be an absolute path, for example:
#wrapper.java.command=/path/to/my/jdk/bin/java
wrapper.java.command=G:\develop\Java\jdk-11.0.9\bin\java

# 为了节省篇幅，省略了其他配置内容
```



### 参考资料

- 11个实用的代码质量审核和管理工具: <https://baijiahao.baidu.com/s?id=1654313325850883156> 
- 手把手使用SonarQube分析、改善项目代码质量: <https://www.imooc.com/article/291857/> 

### 总结

养成使用工具检测代码问题的习惯，不仅能帮助我们发现代码漏洞，而且还能提示我们的代码水平，减少写出问题代码。