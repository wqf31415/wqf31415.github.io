---
title: JVM 调优初探
date: 2019-01-11 09:58:19
tags:
- java
- jvm
categories:
- 技术
---

### 简介
初次接触到 JVM 调优，在本文中记录了相关的概念、方法与工具使用。


### 遇到的问题
> 线上运行的项目，在一次更新时配置出错，没有开启数据消费线程，导致消息队列中积压了超四百万条数据，修改配置后再运行时，发现服务器 cpu 占用率长时间达到 100%，消息队列中不断积压数据，后台无法访问。


### 思路
1. 这台服务器是虚拟机，发现服务器居然是单核 cpu 的(--!)，多分配 cpu 应该可以提高程序运行效率；
2. 项目正常运行时，消息队列消费速度快，不会积压，或是有少量积压也能迅速消费掉，这次由于意外导致消息队列积压数据太多，最终导致程序无法消费，要想办法提高程序吞吐量；
3. 怀疑消息消费代码效率太低，测试发现在消息积压过多时，消费速度严重下降，可能是线程太多，处理不过来；
4. 检查代码发现，应用开启后不断的从消息队列拿数据，生成任务对象放到了一个 LinkedBlockingQueue 中，这个 queue 没有指定容量，使用的是最大容量 Integer.MAX_VALUE ，怀疑是放入了太多的数据，把内存占满了；

<!-- more -->

### 使用 jdk 中自带的工具监测 java 应用程序

#### jps
##### 功能
全称 JavaVirtual Machine Process Status Tool ，用于查看当前运行的 java 进程，可输出进程号 pid 、名称及参数。

##### 用法
直接在命令行执行 `jps` 命令即可，结果如下：
``````
PS C:\Users\Administrator> jps
12480 JpademoApplication
14272 Launcher
11604 HyiomsApp
11736
6440 RemoteMavenServer
13932 Jps
``````

可选参数：
- `-help` 查看帮助信息
- `-q` 只显示进程号
- `-m` 输出传入 main 方法的参数
- `-l` 输出完全的包名，应用主类名，jar的完全路径名
- `-v` 输出jvm参数
- `-V` 输出通过flag文件传递到JVM中的参数
- `[<hostid>]` 远程调用，查询其它机器上的 java 进程，需要在待查看机器上启动 jstatd 。hostid： `[protocol:][[//]hostname][:port][/servername]`

##### jps 原理
Java 程序启动后，会在 `java.io.tmpdir` 指定的目录下生成 `hsperfdata_XXX` 的文件夹，XXX 为操作系统用户名，里面的文件就是以 java 进程号命名的，通过解析这些文件获取相关的参数信息。
`java.io.tmpdir` 在 windows 系统下默认为 `C:\Users\Administrator\AppData\Local\Temp\hsperfdata_Administrator` ，Linux 下默认为 `/tmp/hsperfdata_{userName}/` 。
![](http://blog-images.qiniu.wqf31415.xyz/jps_hsperfdata_windows.png "Windows 下的 hsperfdata 目录及文件") 

##### 启动 jstatd
1. 创建策略文件 `jstatd.all.policy` ，文件内容如下：
``````
grant codebase "file:${java.home}/../lib/tools.jar" {
                    permission java.security.AllPermission;
              };
``````

2. 运行命令 `jstatd -J-Djava.security.policy=jstatd.all.policy` 启动 jstatd 。
参数含义：
`-J` 参数是一个公共的参数，如 jps、 jstat 等命令都可以接收这个参数。 由于 jps、 jstat 命令本身也是 Java 应用程序， -J 参数可以为 jps 等命令本身设置 Java 虚拟机参数。
`-Djava.security.policy` 指定策略文件
`-Djava.rmi.server.hostname` 指定服务器的ip地址（可忽略）
默认情况下， jstatd 开启在 1099 端口上开启 RMI 服务器。

在 Windows 下启动后查看 1099 端口监听情况：
``````
PS C:\Users\Administrator\Desktop> netstat -ano | findstr 1099
  TCP    0.0.0.0:1099           0.0.0.0:0              LISTENING       5984
  TCP    172.16.19.233:1099     172.16.19.233:64912    ESTABLISHED     5984
  TCP    172.16.19.233:64912    172.16.19.233:1099     ESTABLISHED     5984
  TCP    [::]:1099              [::]:0                 LISTENING       5984
``````

使用 jps 远程查看 java 进程：
``````
C:\Users\Administrator\Desktop>jps 172.16.19.233
12480 JpademoApplication
5984 Jstatd
11736
22280 HyiomsApp
22300 Launcher
``````

##### 参考资料：
> jvm 性能调优工具之 jps： https://www.jianshu.com/p/d39b2e208e72
> Java jstatd详解： https://www.cnblogs.com/tulianghui/p/5918345.html

#### jconsole
Java Monitoring and Management Console，一种基于 JMX 的，对 JVM 性能和资源消耗的可视化监视、管理工具。

##### 本地使用 jconsole
在 Windows 系统下，命令行执行`jconsole` 命令，或打开 jdk 的 bin 目录下的 `jconsole.exe` ，打开后会自动检索当前机器上运行的 java 进程，选择需要查看的，点击 `连接` 即可。
![](http://blog-images.qiniu.wqf31415.xyz/jconsole_1.png "jconsole")

如果连接失败可以添加以下配置后再试，如果是用 Tomcat 运行的，就加到 Tomcat 的启动参数里，如果是开发时用 IDE 运行的，就加到 IDE 的配置里。：
``````
-Dcom.sun.management.jmxremote
-Dcom.sun.management.jmxremote.port=8011
-Dcom.sun.management.jmxremote.ssl=false
-Dcom.sun.management.jmxremote.authenticate=false
``````

##### 远程使用 jconsole
1. 添加配置
首先要修改远程机器上的配置，如果只是内网测试，可以用上面的配置，不验证用户名、密码。如果需要验证则可以使用下面的配置：
``````
// 远程连接地址
-Djava.rmi.server.hostname=172.16.19.233
-Dcom.sun.management.jmxremote
// 远程连接端口号
-Dcom.sun.management.jmxremote.port=9999
// 是否需要用户认证
-Dcom.sun.management.jmxremote.authenticate=true
// 是否通过 ssl 连接
-Dcom.sun.management.jmxremote.ssl=false
// 指定用户名密码文件
-Dcom.sun.management.jmxremote.pwd.file=C:/Program Files (x86)/Java/jdk1.8.0_111/jre/lib/management/jmxremote.password
``````

2. 添加用户
在上面的配置中，我们指定远程连接密码文件在 $JAVA_HOME/jre/lib/management/ 目录下，默认在这个目录下有几个文件：
``````
jmxremote.access				---- 定义用户与权限
jmxremote.password.template		---- 定义用户与密码，远程连接密码配置模板文件，可以复制这个文件修改成自己需要的用户与密码，在 Linux 下需要把复制的文件权限设置为 600
management.properties			---- 默认用户名权限文件和用户名密码文件为 $JAVA_HOME/jre/lib/management/ 目录下的 jmxremote.access 和 jmxremote.password 文件，可以在此配置文件中修改
snmp.acl.template				---- SNMP 监控连接配置
``````

修改 `jmxremote.access` 文件，添加用户名和权限：
``````
user   readonly
``````

复制 `jmxremote.password.template` 修改文件名为 `jmxremote.password` ，修改文件内容，要修改文件权限为 600  (Linux 系统中执行命令 `chmod 600 jmxremote.password` ，Windows 下暂时不知道怎么设置)，在文件末尾添加内容：
复制 `jmxremote.password.template` 修改文件名为 `jmxremote.password` ，修改文件内容，要修改文件权限为 600  (Linux 系统中执行命令 `chmod 600 jmxremote.password` ，Windows 下暂时不知道怎么设置)，在文件末尾添加内容：
``````
user 123456
``````

3. 启动应用程序，远程连接
在其他机器上启动 jconsole ，使用远程连接，填入设定的地址、端口，以及用户名、密码，点击 “连接” 即可在监控远程服务器上的 java 程序。

##### 参考资料
> JConsole远程连接配置: https://www.cnblogs.com/think-in-java/p/6138439.html
> 使用JCONSOLE远程监控JVM: https://www.cnblogs.com/Dhouse/p/7827175.html
> JVM的SNMP监控配置: https://www.cnblogs.com/zhukunrong/p/3860803.html

#### jstack

#### jvisualvm
> 官方文档：[http://visualvm.github.io/documentation.html](http://visualvm.github.io/documentation.html "VisualVM 官方文档")

