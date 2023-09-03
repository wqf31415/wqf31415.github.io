---
title: 嵌入式Web服务GoAhead之HelloWorld
tags:
  - c
  - 嵌入式
  - web
  - 服务器
categories:
  - c
date: 2022-06-25 14:15:49
---

### 概述

这篇文件介绍了嵌入式项目中使用的 web  服务器——GoAhead，介绍了 GoAhead 的功能与使用方法，附带一个 helloworld 示例。

![](https://blog-images.qiniu.wqf31415.xyz/goahead-hello.png) 



### 关于 GoAhead

官网: <https://www.embedthis.com/goahead/> 

官方文档: <https://www.embedthis.com/goahead/doc/> 

源码: Github: <https://github.com/embedthis/goahead> 

GoAhead 是一个流行的嵌入式 web 服务器，简单小巧，结构紧凑（115K代码），易于移植。GoAhead 针对通过事件驱动的单线程内核托管动态嵌入式 web 应用程序进行了优化，在减少 web 应用程序的每个请求的内存开销方面特别有效。

GoAhead 具有一组强大的功能，包括：HTTP/1.1、SSL/TSL、身份验证、基于角色的权限控制、会话状态存储、CGI、沙盒资源限制、日志记录等。



<!-- more -->

### GoAhead 支持的功能

- HTTP web 服务器程序和库
- 灵活的 URI 路由和重定向
- 基于劫色的访问权限控制
- 本地或基于 PAM 的密码存储
- CGI处理程序
- 内存中 URI 处理程序
- 支持 HTTPS
- 请求跟踪和日志记录



### 同类产品

#### mongoose

> 官网: <https://mongoose.ws/> 
>
> Github: <https://github.com/cesanta/mongoose> 

开源的嵌入式 web 服务器，为 C/C++ 提供 http、websocket、mqtt 功能库，能够将软件产品、设备或应用APP转变成一个 web 服务器，从而使用浏览器访问和远程控制。mongoose支持 RESTful API 和实时双向通信，能够在内存很小的设备上保存大型固定文件，可通过定时拉取或版本检查，或显式推送自动更新设备。

- mongoose 支持多平台，包括 Linux/UNIX、MacOS、Android、FreeRTOS等；

- 支持多种嵌入式结构：ESP32、STM32、MXP等；

- 内置协议：普通 TCP/UDP、HTTP、MQTT、Websocket；
- SSL/TLS支持：mbedTLS、OpenSSL或自定义(通过api)；

- 支持异步 DNS 解析器；

- 极小的静态和运行时占用空间；

- 源代码同时符合 ISO C 和 ISO C++；

- 适用于任何具有套接字 API 的网络堆栈，如 LwIP 或 FreeRTOS-Plus-TCP；

- 非常容易集成，只需将文件 `mongoose.c` 和 `mongoose.h` 复制到你的项目即可；



#### CivetWeb

> Github: <https://github.com/civetweb/civetweb> 

简单易用且强大的开源 C/C++ 嵌入式 web 服务器，支持 CGI、SSL、Lua脚本、HTTP、Websocket、WebDAV，可作为库引入已有项目，使其转变成 web 服务器，也可做为独立的 web 服务器使用。CivetWeb 是从 Mongoose 发展而来，使用 MIT 开源协议。



#### Lighttpd

> 官网：<https://redmine.lighttpd.net/> 
>
> Github: 
>
> - lighttpd: <https://github.com/lighttpd/lighttpd1.4>
> - lighttpd2: <https://github.com/lighttpd/lighttpd2> 
>
> lighttpd2 是一个正在进行中的版本，尚无法用于生产环境，甚至无法编译，仅为对此感兴趣的人提供。

lighttpd 是一个开源的安全、快速、合规且非常灵活的web 服务器，针对高性能环境进行了优化，其占用内存低，负责处理 cpu 负载。支持 HTTP1.0、HTTP1.1、HTTP2、https、cgi，websocket，支持负载均衡（一个网络服务器将请求分发到多个 PHP 服务器）。



#### Boa

> 官网: <http://www.boa.org/> 

Boa 是一个单任务的 http 服务器，内部以多路复用所有正在进行的http连接，并且只为 CGI 程序（必须是单独的进程）、自动目录生成和自动文件压缩。Boa 能够在 300 MHz Pentium 上每秒处理数千次点击，在低速 20 MHz 386/SX 上每秒处理数十次点击。Boa 的主要设计目标是速度和安全性，而不打算用作功能丰富的服务器。



### GoAhead--HelloWorld

#### 环境

> 以下列出的环境仅为本次测试使用，GoAhead 项目支持多种环境下编译，如 macOS、Linux、Windows等。

操作系统：Huawei Cloud EulerOS release 1.0 (x86_64)

make版本: GNU Make 4.3

gcc 版本: 7.3.0



#### 获取源码

使用 git 从 GoAhead 的 [GitHub 仓库](https://github.com/embedthis/goahead)下载源码：

```bash
 git clone https://github.com/embedthis/goahead
```

源码目录文件说明：

- configure: 配置shell脚本
- configure.bat: 配置脚本(Windows)
- CONTRIBUTING.md: 贡献代码说明
- doc: 参考文档
- installs: 安装脚本存放目录
- LICENSE.md: 许可协议
- main.me: MakeMe 脚本文件
- make.bat: make 脚本(Windows)
- Makefile: make 脚本
- pak.json: 打包配置
- paks: 打包相关依赖
- projects: 项目构建脚本目录，提供了针对不同系统环境的构建脚本
- README.md: 项目说明文件
- src: 源代码
- test: 测试(示例)代码



#### 编译

GoAhead 提供了针对不同操作系统和环境的编译方案，如为 Linux 和 MacOS 提供 make 编译脚本，为 Windows 提供 `make.bat` 脚本等。

本次示例使用 linux 操作系统，先进入 GoAhead 源码目录，然后使用 make 编译:

```bash
cd goahead && make
```

等待编译完成，完成后将会输出如下提示文字:

```
On Linux/MacOS, you can now install via "sudo make  install" or run GoAhead via: "sudo make run"
To run locally, put linux-x64-default/bin in your path
```

编译完成的文件存放在 `/build` 目录下。



#### 安装运行

上一步编译完后，在linux系统中可以执行下面命令将 GoAhead 安装到本地:

```bash
sudo make install
```

安装完成后，将在 `/etc/goahead` 存放 web 服务的配置文件，在 `/var/www/goahead` 目录存放页面文件，执行如下命令启动 web 服务:

```bash
goahead -v --home /etc/goahead/ /var/www/goahead/
```

> 运行命令说明：
>
> `goahead`:  GoAhead 程序，通过 `make install` 安装的
>
> `-v`: 在控制台输出日志信息
>
> `--home /etc/goahead/`: 指定 web 服务根目录，该目录中包含了路由配置文件、权限配置文件、证书文件
>
> `/var/www/goahead/`: 页面文件存放路径，包含主页 html 文件和一个图标文件

运行结果:

```
goahead: 2: Configuration for Embedthis GoAhead
goahead: 2: ---------------------------------------------
goahead: 2: Version:            5.2.0
goahead: 2: BuildType:          Debug
goahead: 2: CPU:                x64
goahead: 2: OS:                 linux
goahead: 2: Host:               127.0.0.1
goahead: 2: Directory:          /etc/goahead
goahead: 2: Documents:          /var/www/goahead/
goahead: 2: Configure:          me -d -q -platform linux-x86-default -conf. -gen make
goahead: 2: ---------------------------------------------
goahead: 2: Started http://*:80
goahead: 2: Started https://*:443
```

启动后，程序将绑定 80 端口提供 http 服务，绑定 443 端口提供 https 服务，访问 http://ip:80 或 https://ip:443（将 ip替换成你电脑ip，端口为默认端口，也可省略不写），进入示例主页，页面标题为 `Home Page` ， 页面内容显示 `Congratulations! The server is up and running。` 

> 注意：使用 https 访问时，可能会提示 `你的连接不是专用连接` 或证书不安全，这是因为证书原因，可忽略，点击 “高级” - “继续访问” 即可。



#### helloworld 

修改 `src/goahead.c` ，添加一个请求处理函数，来响应我们发出的 http 请求。

在文件前面添加一个 hello 方法，内容如下:

```c
static void hello(Webs *wp){
  websSetStatus(wp, 200); // 设置状态码为 200
  websWriteHeaders(wp,-1,0); // 响应头
  websWriteEndHeaders(wp); // 结束响应头内容
  // 写入响应内容，内容为一个 html
  websWrite(wp,"<html><head><title>Demo</title></head><body>");
  websWrite(wp,"Hello, %s",websGetVar(wp,"name","GoAhead")); // 页面内容为 Hello, 再加上用户传过来的 name 参数值，如果不带 name 参数则默认值为 GoAhead
  websWrite(wp,"</body></html>");
  websDone(wp); // 完成响应内容
}
```

这是一个 action 类型的请求函数，需要使用 `websDefineAction("hello", hello);` 将上面写的函数注册成 action 处理函数，其中第一个 `"hello"` 是请求的名称(用户发送请求时使用)，第二个 `hello` 是调用的处理函数。当用户请求 `/action/hello` 时，将会调用 hello 函数来处理请求。



完整代码：

> 请注意：31行\~40行是添加的函数，125行是将 hello 函数注册成请求处理器，其他代码是 GoAhead 项目中的源码。

```c
/*
    goahead.c -- Main program for GoAhead

    Usage: goahead [options] [documents] [IP][:port] ...
        Options:
        --auth authFile        # User and role configuration
        --background           # Run as a Linux daemon
        --home directory       # Change to directory to run
        --log logFile:level    # Log to file file at verbosity level
        --route routeFile      # Route configuration file
        --verbose              # Same as --log stdout:2
        --version              # Output version information

    Copyright (c) All Rights Reserved. See details at the end of the file.
 */

/********************************* Includes ***********************************/

#include    "goahead.h"

/********************************* Defines ************************************/

static int finished = 0;

/********************************* Forwards ***********************************/

static void initPlatform(void);
static void logHeader(void);
static void usage(void);

// 处理 /action/hello 请求的函数
static void hello(Webs *wp){
  websSetStatus(wp, 200);
  websWriteHeaders(wp,-1,0);
  websWriteEndHeaders(wp);
  websWrite(wp,"<html><head><title>Demo</title></head><body>");
  websWrite(wp,"Hello, %s",websGetVar(wp,"name","GoAhead"));
  websWrite(wp,"</body></html>");
  websDone(wp);
}

#if WINDOWS
static void windowsClose();
static int windowsInit();
static LRESULT CALLBACK websWindProc(HWND hwnd, UINT msg, UINT wp, LPARAM lp);
#endif

#if ME_UNIX_LIKE
static void sigHandler(int signo);
#endif

/*********************************** Code *************************************/

MAIN(goahead, int argc, char **argv, char **envp)
{
    char    *argp, *home, *documents, *endpoints, *endpoint, *route, *auth, *tok, *lspec;
    int     argind;

#if WINDOWS
    if (windowsInit() < 0) {
        return 0;
    }
#endif
    route = "route.txt";
    auth = "auth.txt";

    for (argind = 1; argind < argc; argind++) {
        argp = argv[argind];
        if (*argp != '-') {
            break;

        } else if (smatch(argp, "--auth") || smatch(argp, "-a")) {
            if (argind >= argc) usage();
            auth = argv[++argind];

#if ME_UNIX_LIKE && !MACOSX
        } else if (smatch(argp, "--background") || smatch(argp, "-b")) {
            websSetBackground(1);
#endif

        } else if (smatch(argp, "--debugger") || smatch(argp, "-d") || smatch(argp, "-D")) {
            websSetDebug(1);

        } else if (smatch(argp, "--home")) {
            if (argind >= argc) usage();
            home = argv[++argind];
            if (chdir(home) < 0) {
                error("Cannot change directory to %s", home);
                exit(-1);
            }
        } else if (smatch(argp, "--log") || smatch(argp, "-l")) {
            if (argind >= argc) usage();
            logSetPath(argv[++argind]);

        } else if (smatch(argp, "--verbose") || smatch(argp, "-v")) {
            logSetPath("stdout:2");

        } else if (smatch(argp, "--route") || smatch(argp, "-r")) {
            route = argv[++argind];

        } else if (smatch(argp, "--version") || smatch(argp, "-V")) {
            printf("%s\n", ME_VERSION);
            exit(0);

        } else if (*argp == '-' && isdigit((uchar) argp[1])) {
            lspec = sfmt("stdout:%s", &argp[1]);
            logSetPath(lspec);
            wfree(lspec);

        } else {
            usage();
        }
    }
    documents = ME_GOAHEAD_DOCUMENTS;
    if (argc > argind) {
        documents = argv[argind++];
    }
    initPlatform();
    if (websOpen(documents, route) < 0) {
        error("Cannot initialize server. Exiting.");
        return -1;
    }

    // 将 hello 函数注册成 action 类型的请求处理器
    websDefineAction("hello", hello);

#if ME_GOAHEAD_AUTH
    if (auth && websLoad(auth) < 0) {
        error("Cannot load %s", auth);
        return -1;
    }
#endif
    logHeader();
    if (argind < argc) {
        while (argind < argc) {
            endpoint = argv[argind++];
            if (websListen(endpoint) < 0) {
                return -1;
            }
        }
    } else {
        endpoints = sclone(ME_GOAHEAD_LISTEN);
        for (endpoint = stok(endpoints, ", \t", &tok); endpoint; endpoint = stok(NULL, ", \t,", &tok)) {
#if !ME_COM_SSL
            if (strstr(endpoint, "https")) continue;
#endif
            if (websListen(endpoint) < 0) {
                wfree(endpoints);
                return -1;
            }
        }
        wfree(endpoints);
    }
#if ME_ROM && KEEP
    /*
        If not using a route/auth config files, then manually create the routes like this:
        If custom matching is required, use websSetRouteMatch. If authentication is required, use websSetRouteAuth.
     */
    websAddRoute("/", "file", 0);
#endif
#ifdef GOAHEAD_INIT
    /*
        Define your init function in main.me goahead.init, or
        configure with DFLAGS=GOAHEAD_INIT=myInitFunction
     */
    {
        extern int GOAHEAD_INIT();

        if (GOAHEAD_INIT() < 0) {
            exit(1);
        }
    }
#endif
#if ME_UNIX_LIKE && !MACOSX
    /*
        Service events till terminated
     */
    if (websGetBackground()) {
        if (daemon(0, 0) < 0) {
            error("Cannot run as daemon");
            return -1;
        }
    }
#endif
    websServiceEvents(&finished);
    logmsg(1, "Instructed to exit");
    websClose();
#if WINDOWS
    windowsClose();
#endif
    return 0;
}

static void logHeader(void)
{
    char    home[ME_GOAHEAD_LIMIT_STRING];

    getcwd(home, sizeof(home));
    logmsg(2, "Configuration for %s", ME_TITLE);
    logmsg(2, "---------------------------------------------");
    logmsg(2, "Version:            %s", ME_VERSION);
    logmsg(2, "BuildType:          %s", ME_DEBUG ? "Debug" : "Release");
    logmsg(2, "CPU:                %s", ME_CPU);
    logmsg(2, "OS:                 %s", ME_OS);
    logmsg(2, "Host:               %s", websGetServer());
    logmsg(2, "Directory:          %s", home);
    logmsg(2, "Documents:          %s", websGetDocuments());
    logmsg(2, "Configure:          %s", ME_CONFIG_CMD);
    logmsg(2, "---------------------------------------------");
}

static void usage(void) {
    fprintf(stderr, "\n%s Usage:\n\n"
        "  %s [options] [documents] [[IPaddress][:port] ...]\n\n"
        "  Options:\n"
#if ME_GOAHEAD_AUTH
        "    --auth authFile        # User and role configuration\n"
#endif
#if ME_UNIX_LIKE && !MACOSX
        "    --background           # Run as a Unix daemon\n"
#endif
        "    --debugger             # Run in debug mode\n"
        "    --home directory       # Change to directory to run\n"
        "    --log logFile:level    # Log to file file at verbosity level\n"
        "    --route routeFile      # Route configuration file\n"
        "    --verbose              # Same as --log stdout:2\n"
        "    --version              # Output version information\n\n",
        ME_TITLE, ME_NAME);
    exit(-1);
}

static void initPlatform(void)
{
#if ME_UNIX_LIKE
    signal(SIGTERM, sigHandler);
    #ifdef SIGPIPE
        signal(SIGPIPE, SIG_IGN);
    #endif
#elif ME_WIN_LIKE
    _fmode=_O_BINARY;
#endif
}

#if ME_UNIX_LIKE
static void sigHandler(int signo)
{
    finished = 1;
}
#endif

#if WINDOWS
/*
    Create a taskbar entry. Register the window class and create a window
 */
static int windowsInit()
{
    HINSTANCE   inst;
    WNDCLASS    wc;                     /* Window class */
    HMENU       hSysMenu;
    HWND        hwnd;

    inst = websGetInst();
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = inst;
    wc.hIcon         = NULL;
    wc.lpfnWndProc   = (WNDPROC) websWindProc;
    wc.lpszMenuName  = wc.lpszClassName = ME_NAME;
    if (! RegisterClass(&wc)) {
        return -1;
    }
    /*
        Create a window just so we can have a taskbar to close this web server
     */
    hwnd = CreateWindow(ME_NAME, ME_TITLE, WS_MINIMIZE | WS_POPUPWINDOW, CW_USEDEFAULT,
        0, 0, 0, NULL, NULL, inst, NULL);
    if (hwnd == NULL) {
        return -1;
    }

    /*
        Add the about box menu item to the system menu
     */
    hSysMenu = GetSystemMenu(hwnd, FALSE);
    if (hSysMenu != NULL) {
        AppendMenu(hSysMenu, MF_SEPARATOR, 0, NULL);
    }
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);
    return 0;
}


static void windowsClose()
{
    HINSTANCE   inst;

    inst = websGetInst();
    UnregisterClass(ME_NAME, inst);
}


/*
    Main menu window message handler.
 */
static LRESULT CALLBACK websWindProc(HWND hwnd, UINT msg, UINT wp, LPARAM lp)
{
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            finished++;
            return 0;

        case WM_SYSCOMMAND:
            break;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

/*
    Check for Windows Messages
 */
WPARAM checkWindowsMsgLoop()
{
    MSG     msg;

    if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
        if (!GetMessage(&msg, NULL, 0, 0) || msg.message == WM_QUIT) {
            return msg.wParam;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

/*
    Windows message handler
 */
static LRESULT CALLBACK websAboutProc(HWND hwndDlg, uint msg, uint wp, long lp)
{
    LRESULT    lResult;

    lResult = DefWindowProc(hwndDlg, msg, wp, lp);

    switch (msg) {
        case WM_CREATE:
            break;
        case WM_DESTROY:
            break;
        case WM_COMMAND:
            break;
    }
    return lResult;
}

#endif

/*
    Copyright (c) Embedthis Software. All Rights Reserved.
    This software is distributed under a commercial license. Consult the LICENSE.md
    distributed with this software for full details and copyrights.
 */
```



#### 测试

按上述说明改好了 `src/goahead.c` 文件后，回到根目录使用 make 编译：

```bash
make
```

然后安装:

```bash
sudo make install
```

运行：

```bash
goahead -v --home /etc/goahead /var/www/goahead
```

打开浏览器访问 http://ip:80/action/hello?name=World ，页面内容显示为 `Hello, World` ；

访问 http://ip:80/action/hello ，页面内容显示为 `Hello, GoAhead` 



### 注意事项

#### 使用 c99 标准编译

当在 GoAhead 根目录中使用 `make` 命令编译时，发散错误:

```
src/mbedtls/mbedtls.c:7408: error: 'for' loop initial declarations are only allowed in C99 mode
```

说明当前系统默认使用的是非 c99 标准，可以通过参数设定编译标准，如下：

```bash
make CFLAGS=-std=c99
```



#### 使用 gnu99 标准编译

使用 make 编译源码时，错误提示：

```
src/mbedtls/mbedtls.c:39845: error: dereferencing pointer to incomplete type
```

这个错误可以在编译时通过参数指定 gnu99 标准来解决：

```bash
make CFLAGS=-std=gnu99
```



#### 端口冲突

当运行 GoAhead 与其他程序产生端口冲突时，可以在运行命令后增加参数来指定端口，如：

```bash
goahead -v --home /etc/goahead /var/www/goahead :8080
```

将使用 8080 作为服务端口，需要注意的是这样设置将只会启动 http 服务，如需同时启动 https 服务，可执行如下命令：

```bash
goahead -v --home /etc/goahead/ /var/www/goahead/ http://*:8080 https://*:443
```

将在 8080 端口启动 http 服务，在 443 端口启动 https 服务。



### 总结

GoAhead 使用起来还是比较简单的，需要注意的请求的路由是在 route.txt 文件中配置好的，本示例中未修改路由配置，默认路由配置中 action 类型的请求配置为:

```
route uri=/action handler=action
```

所以，所有 action 类型的请求都需要以 `/action` 开始，如 `/action/hello`，直接访问 http://ip:80/hello 是不行的，除非配置 `route uri=/ handler=action` 。
