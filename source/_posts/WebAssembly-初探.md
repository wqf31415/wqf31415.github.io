---
title: WebAssembly-初探
tags:
  - WebAssembly
  - c
  - js
  - 前端
  - web
categories:
  - wasm
date: 2023-06-29 10:56:49
---

### 概述

WebAssembly 已经极 html、css、js 之后，成为 Web 平台的第四种语言，这篇文章介绍了 WebAssembly 的概念，特点以及使用场景，提供了一个将 C 代码编译成 wasm 并在浏览器访问的简单示例。



### 认识 WebAssembly

> 官网: WebAssembly <https://webassembly.org/> 
>
> 中文网：WebAssembly 中文网 <https://www.wasm.com.cn/>
>
> W3C 标准：
> 
> WebAssembly Core Specification <https://www.w3.org/TR/wasm-core-1/>
>
> WebAssembly JavaScript Interface <https://www.w3.org/TR/wasm-js-api-1/> 
>
> WebAssembly Web API <https://www.w3.org/TR/wasm-web-api-1/>

WebAssembly （简称 wasm），中文含义为网页汇编，是一种基于栈的二进制指令格式的虚拟机标准，它的设计目标包括：高可移植性、高安全性、高效率（包括载入效率和运行效率）、尽可能小的程序体积。WebAssembly 能够在主流的浏览器中运行，它的出现是为了解决前端项目 JavaScript 运行低效的问题。浏览器支持情况参考：[Roadmap - WebAssembly](https://webassembly.org/roadmap/) 。




<!-- more -->



### WebAssembly 用途

wasm 可以在主流的浏览器中运行，也可以脱离浏览器环境。在 Web 中，可以全部使用 wasm ，或使用 wasm 完成复杂的算法，使用 js 完成交互逻辑，还可以在已有的 web 项目中应用部分 wasm 作为工具库，完成部分计算任务。

一些应用场景：

- 更好的让一些语言和工具可以编译到 Web 平台运行
- 图片/视频编辑
- 游戏：需要快速打开的小游戏、AAA级资源量很大的游戏、游戏门户（代理/原创游戏平台）
- P2P应用（游戏/实时合作编辑）
- 音乐播放器（流媒体/缓存）
- 图像识别
- 视频直播
- VR和虚拟现实
- CAD软件
- 科学可视化和仿真
- 互动教育软件和新闻文章
- 模拟仿真平台（ARC、DOSBOX、QEMU等）
- 语言编译器、虚拟机
- POSIX用户空间环境，允许移植现有的POSIX应用程序
- 开发者工具（编辑器、编译器、调试器等）
- 远程桌面
- VPN
- 加密工具



### WebAssembly 优势

在浏览器中， WebAssembly 程序运行在 WebAssembly 虚拟机中，Web 页面通过一组 JavaScript 对象进行 WebAssembly 模块的编译、载入、配置、调用等操作。

- 体积小：wasm 是编译成二进制文件，比原生的 JavaScript 体积更小
- 加载和运行速度快：由于 wasm 体积更小，因此从服务端下载耗时更短，在运行时，是在浏览器提供的 wasm 虚拟机中运行，力求发挥硬件能力已达到原生执行效率
- 可移植性高：由于 wasm 是一套虚拟机标准，因此在有 wasm 虚拟机的环境中都可运行，就像 java 代码号称一次编译到处运行一样，都是靠虚拟机屏蔽了系统及硬件差异



### Hello World

#### 开发环境

> Emscripten：<https://emscripten.org/> 

Emscripten  最用 C/C++ 开发 WebAssembly  应用的最主流开发工具链，是 WebAssembly  宿主接口事实上的标准之一（另一个是 WASI 规范）。



##### 编译安装

> 参考官方下载安装文档: 
>
> Emscripten Download and install: <https://emscripten.org/docs/getting_started/downloads.html> 

从 GitHub 仓库中下载 [emsdk](https://github.com/emscripten-core/emsdk) ，然后进入 emsdk 目录，执行安装命令和激活命令：

linux:

```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk/
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

windows:

```powershell
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk/
emsdk install latest
emsdk activate latest
emsdk_env.bat
```

注： 最后一条命令是创建系统环境，将一些路径写入系统的环境命令 Path 中，如果写入失败，可以手动修改环境变量，添加响应的路径到 Path。



##### 测试

开启命令行，执行命令 `emcc -v` ，打印 emscripten 版本信息，正常打印说明安装成功。

```
emcc (Emscripten gcc/clang-like replacement + linker emulating GNU ld) 3.1.40 (5c27e79dd0a9c4e27ef2326841698cdd4f6b5784)
clang version 17.0.0 (https://github.com/llvm/llvm-project 2922e7cd9334797c24a317d41275f1258ef9ddd3)
Target: wasm32-unknown-emscripten
Thread model: posix
InstalledDir: E:\project\opensource\emsdk\upstream\bin
```



##### Docker 安装

从 GitHub 仓库下载 emsdk 源码后，进入项目目录中的 docker 目录，里面有 `Dockerfile` 文件，可用来创建 docker 镜像。

> apiaryio/emcc - Docker Image | Docker Hub： <https://hub.docker.com/r/apiaryio/emcc> 

具体用法参考 docker 目录中的 `README.md` 文件。



#### 第一个示例

##### C 语言代码

一个最简单的 C 语言 hello world 代码：

`hello.c` ，打印输出 `你好 wasm!` 。

```C
#include <stdio.h>
int main()
{
  printf("你好 wasm!\n");
  return 0;
}
```



##### 编译

在 `hello.c` 文件目录中打开命令行，执行编译命令：

```powershell
emcc hello.c
```

编译完成后，将生成两个文件：

- `a.out.wasm` 由 C 语言代码编译得到的 WebAssembly 代码

- `a.out.js` 自动生成的一个调用 `a.out.wasm` 的 JavaScript 代码



##### 测试

如果安装了 node ，可以直接在命令行中执行 `node a.out.js` ，即可看到打印出 `你好 wasm!` 。

此外，可以手动写一个 html 来调用，新建一个 `index.html` ，内容如下：

```html
<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<title>WebAssembly Demo</title>
	</head>
	<script src="a.out.js"></script>
	<body>
	</body>
</html>
```

在这个 html 文件仅仅引用了 `a.out.js` 文件，并没有做其他事，接下来就要访问这个页面。

**注意：需要将 `index.html` 、`a.out.js` 、`a.out.wasm` 文件放在同一级目录中，并放在 web 服务器（如 [nginx](http://nginx.org/) 、[Tomcat](https://tomcat.apache.org/) ）中，然后在浏览器中访问。** 直接双击打开是无法正确运行的。

![](http://blog-images.qiniu.wqf31415.xyz/wasm-hello.png)

打开浏览1器的开发者工具，进入控制台。看到控制台输出了 `你好 wasm!` ，运行成功。



##### 更多

在使用 `emcc` 编译 C 语言代码文件时，如果不指定输出的文件名，则默认输出 `a.out.js` 和 `a.out.wasm` 文件，我们可以添加参数 `-o` 指定编译输出内容，如:

```powershell
emcc hello.c -o hello.html
```

当使用 `-o` 参数指定的输出文件名后缀为 `.html` 时，将输出同名的 `.html` 、`.js` 、`.wasm` 文件；当指定输出的文件名后缀为 `.js` 时，将输出同名的 `.js` 和 `.wasm` 文件。

如上面的命令将输出文件：`hello.html` 、`hello.js` 、`hello.wasm` ，将这三个文件放到 web 服务器中，使用浏览器访问，页面如下：

![](http://blog-images.qiniu.wqf31415.xyz/wasm-hello-2.png)

> 这个页面上方的黑色区域是一个 canvas 画布，用来模拟图形界面；下方的黑色区域是一个模拟标准控制台输入/输出区域，会打印出 `你好 wasm!` ；同时开发者工具中的控制台也输出了打印内容 `你好 wasm!` 。



### 相关开源项目

- emscripten-core/emscripten: Emscripten: An LLVM-to-WebAssembly Compiler https://github.com/emscripten-core/emscripten

- wasmerio/wasmer: 🚀 The leading WebAssembly Runtime supporting WASI and Emscripten https://github.com/wasmerio/wasmer

- AssemblyScript/assemblyscript: A TypeScript-like language for WebAssembly. https://github.com/AssemblyScript/assemblyscript

- bytecodealliance/wasmtime: A fast and secure runtime for WebAssembly https://github.com/bytecodealliance/wasmtime

- WebAssembly/design: WebAssembly Design Documents https://github.com/WebAssembly/design

- ffmpegwasm/ffmpeg.wasm: FFmpeg for browser and node, powered by WebAssembly https://github.com/ffmpegwasm/ffmpeg.wasm

- mbasso/awesome-wasm: 😎 Curated list of awesome things regarding WebAssembly (wasm) ecosystem. https://github.com/mbasso/awesome-wasm

- WebAssembly/binaryen: Optimizer and compiler/toolchain library for WebAssembly https://github.com/WebAssembly/binaryen

- naptha/tesseract.js: Pure Javascript OCR for more than 100 Languages 📖🎉🖥 https://github.com/naptha/tesseract.js

- pion/webrtc: Pure Go implementation of the WebRTC API https://github.com/pion/webrtc

- tinygo-org/tinygo: Go compiler for small places. Microcontrollers, WebAssembly (WASM/WASI), and command-line tools. Based on LLVM. https://github.com/tinygo-org/tinygo

### 参考资料

- 丁尔男, 柴树杉. 《面向WebAssembly编程：应用开发方法与实践》. 机械工业出版社, 2021



### 总结

WebAssembly 本质上是一个纯的虚拟机指令规范（模块的二级制格式等都属于外延部分），同时在软件层面定义了和外部宿主环境的交互接口。WebAssembly 是对标 Java 中 JVM 的技术，目标是替代底层 CPU，提供一个虚拟机，支持从 C/C++、Rust、Java 等高级语言编译而来的字节码，就像在 JVM 中可以运行很多语言编译而来的字节码。

WQSI（WebAssembly System Interface） 是 WebAssembly 最新的一个技术发展方向，也是 WebAssembly 能够突破 Web 环境自由发展的一个必要前提。
