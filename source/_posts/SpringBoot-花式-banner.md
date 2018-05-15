---
title: SpringBoot 花式 banner
date: 2018-05-14 14:22:16
tags:
- java
- springboot
categories:
- 技术

---

### 什么是 springboot 的 banner？

当 SpringBoot 项目最初运行起来时，在控制台看到的类似下面的信息，就是 SpringBoot 的 banner。

``````
  .   ____          _            __ _ _
 /\\ / ___'_ __ _ _(_)_ __  __ _ \ \ \ \
( ( )\___ | '_ | '_| | '_ \/ _` | \ \ \ \
 \\/  ___)| |_)| | | | | || (_| |  ) ) ) )
  '  |____| .__|_| |_|_| |_\__, | / / / /
 =========|_|==============|___/=/_/_/_/
 :: Spring Boot ::  (v1.5.14.BUILD-SNAPSHOT)
``````



### 加载顺序

SpringBoot 默认寻找banner的顺序是：

- 依次在 classpath 下找文件 banner.gif ，banner.jpg，banner.png，先找到哪个用哪个；
- 在 classpath 下找 banner.txt ；
- 以上都没有就使用默认的；



### 更换 banner

在 **resources ** 目录下创建文件 `banner.txt` ，将想要展示的文字内容写到这个文件中即可。

> 当然，按理说使用图片文件也可以，但我还没找到能在控制台正常显示的图片，╮(￣▽￣")╭

![](http://okbn8yrzu.bkt.clouddn.com/spring-boot-banner.txt.png)



### 编辑 banner 内容

#### 生成漂亮的 banner 文字图

- 将文字转换成文字图形：[http://patorjk.com/software/taag/](http://patorjk.com/software/taag/)

> 输入想要的文字，生成图形文字，将生成的内容粘贴到 `banner.txt` 中即可。

![](http://okbn8yrzu.bkt.clouddn.com/text2text-graph.png)



- 将图片转换成文字图形：[http://www.degraeve.com/img2txt.php](http://www.degraeve.com/img2txt.php)

> 这个就厉害了，给定图片链接，将其转换成文字图形。例如将示例中的美女图转成txt文字：

![](http://okbn8yrzu.bkt.clouddn.com/img2txt-1.png)

=======>

![](http://okbn8yrzu.bkt.clouddn.com/img2txt-2.png)

将文字部分粘贴到 `banner.txt` 中，运行项目看到：

![](http://okbn8yrzu.bkt.clouddn.com/img2txt-3.png)

 如果发现图片有点大了，可以退回到上一步，设置图片输出大小，重新获得txt 文本。

我们看现在这个 banner，在控制台中输出时，被压扁了，我们要把它拉开，在每个字符后面添加一个空格。将文本粘贴到一个空白 word 文档中，按 `Ctrl + F` 键调出查找功能对话框，在 `替换` 选项卡中，勾选上使用通配符，在上面输入问号 `?` ，在下面输入 ^& 加一个空格，点击 `全部替换` 。将全部文本复制到 `banner.txt` 中。

![](http://okbn8yrzu.bkt.clouddn.com/img2txt-4.png)



最终效果：

![](http://okbn8yrzu.bkt.clouddn.com/img2txt-5.png)



#### 给 banner 上色

使用 SpringBoot 提供的颜色枚举类为banner设置颜色，只需要在要上色文字前添加相应颜色代码，即可为后方的所有文字添加字体颜色或背景颜色。如：

Ansi 颜色代码

| 颜色     |        字体颜色代码         |           背景颜色代码           | 颜色值 |
| -------- | :-------------------------: | :------------------------------: | :----: |
| 红色     |      ${AnsiColor.RED}       |      ${AnsiBackground.RED}       |  A00   |
| 亮红色   |   ${AnsiColor.BRIGHT_RED}   |   ${AnsiBackground.BRIGHT_RED}   |  F55   |
| 绿色     |     ${AnsiColor.GREEN}      |     ${AnsiBackground.GREEN}      |  0A0   |
| 亮绿色   |  ${AnsiColor.BRIGHT_GREEN}  |  ${AnsiBackground.BRIGHT_GREEN}  |  5F0   |
| 蓝色     |      ${AnsiColor.BLUE}      |      ${AnsiBackground.BLUE}      |  00A   |
| 亮蓝色   |  ${AnsiColor.BRIGHT_BLUE}   |  ${AnsiBackground.BRIGHT_BLUE}   |  55F   |
| 黑色     |     ${AnsiColor.BLACK}      |     ${AnsiBackground.BLACK}      |  000   |
| 亮黑色   |  ${AnsiColor.BRIGHT_BLACK}  |  ${AnsiBackground.BRIGHT_BLACK}  |  555   |
| 白色     |     ${AnsiColor.WHITE}      |     ${AnsiBackground.WHITE}      |  AAA   |
| 亮白色   |  ${AnsiColor.BRIGHT_WHITE}  |  ${AnsiBackground.BRIGHT_WHITE}  |  FFF   |
| 黄色     |     ${AnsiColor.YELLOW}     |     ${AnsiBackground.YELLOW}     |  A50   |
| 亮黄色   | ${AnsiColor.BRIGHT_YELLOW}  | ${AnsiBackground.BRIGHT_YELLOW}  |  FF5   |
| 青色     |      ${AnsiColor.CYAN}      |      ${AnsiBackground.CYAN}      |  0AA   |
| 亮青色   |  ${AnsiColor.BRIGHT_CYAN}   |  ${AnsiBackground.BRIGHT_CYAN}   |  5FF   |
| 洋红色   |    ${AnsiColor.MAGENTA}     |    ${AnsiBackground.MAGENTA}     |  A0A   |
| 亮洋红色 | ${AnsiColor.BRIGHT_MAGENTA} | ${AnsiBackground.BRIGHT_MAGENTA} |  F5F   |
| 默认色   |    ${AnsiColor.DEFAULT}     |    ${AnsiBackground.DEFAULT}     |   -    |

>  注： 在 banner 结束位置最好使用添加默认颜色和默认背景色，防止后面输出的日志信息颜色混乱影响日志查看。



#### 修改 banner 字体样式

使用 SpringBoot 提供的字体样式枚举设定 banner 展示的字体样式。

|  样式  |          代码          |
| :----: | :--------------------: |
|  正常  |  ${AnsiStyle.NORMAL}   |
|  加粗  |   ${AnsiStyle.BOLD}    |
|  减细  |   ${AnsiStyle.FAINT}   |
|  倾斜  |  ${AnsiStyle.ITALIC}   |
| 下划线 | ${AnsiStyle.UNDERLINE} |

#### 显示项目信息

