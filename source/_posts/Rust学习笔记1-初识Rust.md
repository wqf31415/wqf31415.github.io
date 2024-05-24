---
title: Rust学习笔记1-初识Rust
date: 2024-01-31 23:44:46
tags:
- Rust
categories:
- Rust
---

### 概述

Rust 是一门系统编程语言，在 Stack Overflow 的年度开发者调查中，多年获得 “最喜爱的编程语言” 奖项；Rust 已被 Google、亚马逊、微软、华为、百度、阿里等大厂使用。本文介绍了 Rust 语言的基础特性、优缺点、适用场景，介绍了Rust的使用，包括安装Rust、创建基础体验代码以及代码编译执行，介绍了Rust的开发工具及配置方法。此外，还介绍了一些优秀的 Rust 开源项目和 Rust 学习项目与资料。



### 关于Rust

> 官网: <https://www.rust-lang.org/> 
>
> Rust 是一门赋予每个人构建可靠且高效软件能力的语言。

Rust 语言是 2009 年由 Graydon Hoare 设计，由 Mozilla 实验室资助和完善，现已成为 Mozilla 官方项目。Rust 最大的特点是安全可靠、运行速度快，可作为 C/C++ 的替代语言，相比 C/C++，Rust 和它们具有相同的运行速度，却可以避免 C/C++ 中很多常见的 bug，比如悬垂指针问题、内存泄漏问题。Rust 语言的应用场景包括：系统级编程、嵌入式开发、并发编程、高性能WEB服务、跨平台开发、数据处理和机器学习等。



<!-- more -->

### Rust 的特点

- 安全可靠：使用所有权系统和丰富的类型系统，防止内存泄漏、悬垂指针、数据竞争、缓冲区溢出等安全问题，强大的编译器能够帮助我们在编译时就排除各种错误。

- 生产力：Rust具有许多工效学特性，如泛型、复制数据类型、模式匹配、闭包。Rust 提供了功能全面的软件包管理工具 cargo，同时也是项目构建工具。

- 高性能：Rust 编译器能生成高效的机器代码，运行速度快，且内存利用率极高，Rust 没有运行时和垃圾回收，适用于高性能要求的业务场景。

- 无畏并发：Rust 通过所有权、类型检查机制，在编译阶段即可排除可能存在的并发问题，让你无所畏惧的编写并发代码或重构代码。





### Rust 适用场景

- 命令行程序、工具
- 数据处理：搜索引擎、数据处理引擎、日志解析系统。
- 扩展应用程序：JNI(Java Native Interfave) 扩展、C 扩展、Erlang/Elixir NIF(native implemented functions) 扩展。
- 资源受限的环境：嵌入式设备。
- 服务端应用：数据库、监控系统、搜索类应用和消息系统。
- 桌面应用程序：如 [Tauri App](https://tauri.app/) 
- 移动端：Android 和 ios 都提供了运行原生应用程序的能力，可以运行 C++ 编写的程序，同样的 Rust 可以使用相同的接口与手机交互，且没有额外的运行时开销。
- Web：可以将 Rust 代码编译成 WebAssembly ，从而移植到 web 界面中使用；Rust 可用于开发高性能 Web Service。
- 系统编程：编写操作系统、编译器、游戏引擎等。



### Rust 缺点

- 编译速度慢：Rust 的编译器很强大，帮我们排除了大量问题，但相应的复杂度也很高，编译工具链很复杂，有多种中间表达形式，会发送大量代码给低级虚拟机（LLVM）编译器；在使用 cargo 编译项目时需要编译所有引用的模块（create）。
- 严格：编译器检查非常严格，可能会导致 “误伤”。
- 学习曲线陡峭：Rust语言规模很大，比起其他编程语言，Rust包含了丰富的类型系统、几十个关键字；Rust 包含了很多独有的概念，和其他主流语言都不同，增加了学习难度。



### Rust 初体验

> 官网入门文档: <https://www.rust-lang.org/zh-CN/learn/get-started> 



#### 安装

从 [Rust 官网](https://www.rust-lang.org/tools/install) 下载适合自己电脑CPU架构与操作系统的 `rustup` 管理工具链，安装后可以使用这个工具对 Rust 进行安装和管理。

> 如果需要离线安装，可下载独立的安装包，参考官网说明：<https://forge.rust-lang.org/infra/other-installation-methods.html>。

安装完成后，打开终端，运行 `rustc --version` 和 `cargo --version` 命令测试安装是否成功，如果答应出版本号，说明安装成功，如下：

```
PS C:\Users\wqf31> rustc --version
rustc 1.75.0 (82e1608df 2023-12-21)

PS C:\Users\wqf31> cargo --version
cargo 1.75.0 (1d8b05cdd 2023-11-20)
```



> 获取帮助文档：安装 `rustup` 时，会自动安装 Rust 的文档，运行 `rustup doc` 可以打开本地的 Rust 文档网页。



#### 单文件 Hello World

创建 Rust 代码文件 `hello.rs`，Rust 的源码文件扩展名为 `.rs` 。文件内容如下：

```rust
fn main(){
    println!("Hello, world!"); // print msg
}
```

打开终端（命令行）工具，进入到 `hello.rs` 文件所在目录，运行命令 `rustc hello.rs` 进行编译，编译成功时，终端没有输出内容，查看目录中的文件，发现多了一个可执行文件，文件名为 `hello` （Windows 系统中该文件扩展名为 `.exe`），与代码文件名相同。

在终端中运行可执行文件，如 Windows 中运行 `hello.exe`，打印出 `Hello, world!` ，运行成功。

代码说明：

> 第一行代码中 `fn` 为 Rust 定义函数的关键字；`main` 为函数名，和其他编程语言一样，`main` 函数作为程序入口，只能包含一个 `main` 函数；Rust中函数内容以 `{}` 包裹。

> 第二行代码中 `println!` 是一个宏（`!` 标识这是一个宏），用于输出内容；`"Hello, world!"` 是要输出的内容，是一个字符串，Rust 中字符串用 `""` 包裹；`;` 是代码行结束标识，不可省略；`// print msg` 是注释信息，Rust中单行注释以 `//` 标识。



### 开发工具

Rust 官方推荐的开发工具有：VS code、Sublime Text、RustRover、Eclipse、Vim、Emacs、Visual Studio。

**推荐使用 VS code 加官方扩展的方案，开源，免费使用。**

RustRover是 JetBrains 公司开发的 Rust 开发 IDE，功能齐全，开箱即用，2024年9月前的公开预览版可免费使用。

Sublime Text 需要购买注册。

Eclipse 出的 Rust 开发工具，更新不太活跃。

#### VS code + rust-analyzer 扩展

从 vs code 官网下载安装包，安装完成后，在 vs code 扩展库中搜索并安装 Rust 官网开发的 `rust-analyzer` 扩展，这个扩展提供了代码补全、定义跳转、类型文档提示、语法高亮等功能。



##### 相关链接

- Visual Studio Code: <https://code.visualstudio.com/> 
- VS code 开发 Rust 的说明: <https://code.visualstudio.com/docs/languages/rust> 



#### RustRover：JetBrains 出品的 Rust IDE

[RustRover](https://www.jetbrains.com/zh-cn/rust/) 是 JetBrains 公司提供的 Rust 开发工具，功能丰富，目前提供的是预览版本，可免费使用。



### Rust 开源项目

- rustdesk/rustdesk: 开源的远程桌面工具，可作为 TeamViewer 的替代品：
  https://github.com/rustdesk/rustdesk
- rust-lang/rustlings: 跟着小练习学会读写Rust：
  https://github.com/rust-lang/rustlings
- rust-unofficial/awesome-rust:  超棒的Rust代码和资源：
  https://github.com/rust-unofficial/awesome-rust
- google/comprehensive-rust: 谷歌安卓团队使用的 Rest 课程：
  https://github.com/google/comprehensive-rust
- rwf2/Rocket: Rust Web框架：
  https://github.com/rwf2/Rocket



### 学习相关链接

- Rust语言中文社区: <https://rustcc.cn/> 
- B站 Rust 入门教程: <https://www.bilibili.com/video/BV1hp4y1k7SV/> 
- 使用 `rustup doc` 打开本地的 Rust 文档网页



### 总结

当我们想要一种没有 GC 的语言，同时还想要该语言在安全性至关重要的上下文环境中是可信任的，这时 Rust 就是绝佳选择了。

- Rust 语言的最大优势是运行速度快、安全，适用于系统编程、嵌入式开发、高性能服务端开发、高并发场景。
- Rust 语言的缺点是编译速度慢、上手难度高。
- Rust 支持多种常见操作系统和 CPU 架构，使用 `rustup` 工具来安装 Rust，管理 Rust 版本和编译工具链；安装 Rust 时默认携带构建工具 `cargo` 。
- 推荐使用 VS code、RustRover 开发 Rust 项目 。
- Rust 代码文件后缀为 `.rs`，`main` 函数作为程序入口，使用 `rustc` 编译成可执行文件。
- Rust 中使用 `fn` 定义函数，代码块以 `{}` 包括，以 `;` 作为代码语句结束标识，用 `//` 添加单行注释， `/**/` 添加多行注释。

