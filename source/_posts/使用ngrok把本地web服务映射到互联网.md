---
title: 使用ngrok把本地web服务映射到互联网
date: 2017-08-15 19:18:53
tags:
- web服务
- ngrok
- 内网穿透
categories:
- 工具
---

2019-03-16 如果自己有服务器，可以自己搭建一个内网穿透服务，参考: [使用云服务器搭建 frp 服务实现内网穿透](/2019/03/16/使用云服务器搭建-frp-服务实现内网穿透/ )

在学会了web服务器开发之后，愉（tong）快（ku）的写好了一个网站，在本地跑起来了，想给小伙伴演（zhuang）示（bi）一下，但这时小伙伴并不在身边，发出去的链接都访问不了，唉~

但是自从用了 ngrok 之后，腰不酸了，腿不疼了，一口气上六楼也不费劲了~ 啊呸，错了，自从用了 ngrok，远在天涯的小伙伴也能预览我本地的 web 项目了，啊哈哈哈哈哈哈隔~

### 首先，ngrok先自我介绍一下，大家欢迎！（掌声）
大家好，我是ngrok，我是一个**反向代理**，我可以帮助你在公共端点和本地运行的web服务器建立安全的连接，这样你的朋友在外网也可以访问你本地运行的web服务了,另外在本地开发微信服务的时候，我可以帮你哦！
这是我家：[https://ngrok.com/](https://ngrok.com/ "ngrok") 。
我说完了，谢谢！

<!--more-->

### 大爷，来玩嘛！~
可以直接来我家找我哦！有好多版本可以选择的呢，有Mac OS的，有Linux的，有Windows的，有。。。。

这次就点 Windows 的好了，在主页 Download 页面选择 windows 版本下载，如果网速慢，可以[点这里](http://ouq616hsi.bkt.clouddn.com/7z/ngrok.7z 'ngrok') ，我打包好的，应该要快点！



### 启动姿势很重要！

#### 第一个姿势

如果是选择我打包好的，下载下来是一个 .7z 压缩包，解压出来有三个文件，分别是：

- ngrok.cfg		配置文件
- ngrok.exe		主程序
- start.bat		启动脚本（我写的）

我们在 **start.bat** 文件上右键用记事本打开，发现里面内容如下：

`ngrok -config ngrok.cfg -subdomain mywebserver 8080` 

>  现在可以将 **mywebserver** 改成你想要的服务名称，把 **8080** 改成你本地web项目的端口号，然后保存、退出！

双击 **start.bat** ，会自动打开命令窗口，出现如下界面：

![](http://blog-images.qiniu.wqf31415.xyz/ngrok_run.jpg '运行ngrok')  

说明 ngrok 已经正确运行了，只要访问上面提示的链接即可访问本地的项目了，现在的链接是：http://mywebserver.tunnel.qydev.com ，快去试试吧，骚年！



#### 第二个姿势

第二种方法，去官网下载，下载后解压出来只有一个 **ngrok.exe** ，但是你必须在官网注册账号，然后会获得一个Authtoken 验证码，然后在解压目录下打开命令行工具，执行下面的指令将验证码保存到本地：

`ngrok authtoken 验证码内容` 	验证码内容是注册后获得的；

然后运行：`ngrok http 8080` 

![](http://blog-images.qiniu.wqf31415.xyz/ngrok_64_run.jpg '运行 ngrok') 

访问提示的链接(http://10e4cc06.ngrok.io/)了，界面中上半部分是运行情况，下面是请求统计，可以直接看到请求状态！

另外，我们发现访问链接前面有一串字符，这个是不能改变的，如果你想用自定义的，就得运行下面的指令：

`ngrok -subdomain=mywebserver 8080 `

但是运行之后会报错，这是因为你没有付费，要付费之后才能用自定义的，骚年你需要登录官网购买！



如果用官方下载的 **ngrok.exe** ，可以在命令行输入 `ngrok help` 或 `ngrok -h` 获取帮助信息，里面会有常用的指令示例，非常人性化！



### 就这样吧！

ngrok 还有其它功能，比如创建 TCP 通道等。

这个 ngrok 有个缺点，就是服务器在国外，国内使用时访问速度会比较慢，所以还是用上面那个吧！

更多的操作技巧可以查看官方文档：[https://ngrok.com/docs](https://ngrok.com/docs 'ngrok 官方文档') 

其它类似的工具还有：**nginx** ，**frp** ，**花生壳** ，**nat123** ，**natapp** 等等



### 下台鞠躬！

![](http://blog-images.qiniu.wqf31415.xyz/meme/meme_bow_02.jpg )  

