---
title: Linux文件压缩与解压
tags:
  - linux
categories:
  - linux
date: 2021-08-05 19:54:56
---

### 概述

这篇文章介绍了 linux 系统中常见的文件压缩类型，以及压缩工具的使用。



### 关于文件压缩

文件压缩就是通过某种编码方式将数据信息中的重复度、冗余度降低，达到数据压缩的目的。通过压缩文件可以缩小数据文件的大小，另外通过数据压缩还能将零散的文件整合到一起，便于网络传输。

网络中常见的文件压缩格式有：

- `.zip` (Zipped 压缩档)
- `.rar` (WinRAR 压缩存档)
- `.tar` (unix 统一压缩档)
- `.gz` (GNU Zipped 压缩档)
- `.bz` (Bzipped 压缩档) 
- `.jar` (Java Archive)
- `.exe` (自解压文件) 

<!-- more -->



### linux 中常用的文件压缩

#### .tar

linux 系统中最常见的归档方式，可以把一大堆文件打成一个包，用于备份文件。

> tar 包只是将文件打包在一起形成一个包，而不进行压缩，如果需要压缩需要使用其他命令进行压缩。

使用 `tar` 命令进行打包、解析。

创建 `.tar` 包：

```bash
tar -cf mytar.tar a.txt b.md
```

查看 `.tar` 包中的文件：

```bash
tar -tvf mytar
```

解析 `.tar` 包文件：

```bash
tar -xf mytar
```



#### .tar.gz

使用 `tar` 打包后，再使用 `gzip` 压缩后的压缩包。使用 `tar` 工具打包和解压，也可以 `tar` 和 `gzip` 一起使用来操作。

打包：

```bash
tar -zcf mytar.tar.gz a.txt b.md
```

或者，先打包成 `tar` 包，再用 `gzip` 压缩：

```bash
tar -cf mytar.tar a.txt b.md
gzip -r mytar.tar
```

 

查看：

```bash
tar -ztvf mytar.tar.gz
```



解压：

```bash
tar -zxf mytar.tar.gz
```

或可先用 `gzip` 解压，再用 `tar` 提取文件：

```bash
gzip -d mytar.tar.gz
tar -xf mytar.tar
```



#### .tar.xz

先使用 tar 打包，然后使用 xz 压缩的包。可使用 `tar` 工具打包或解压，可以同时使用 `tar` 和 `xz` 来操作。

打包：

```bash
tar -Jcf mytar.tar.xz a.txt b.md 
```

或先打包成 `tar` 包，再使用 `xz` 压缩：

```bash
tar -cf mytar.tar a.txt b.md
xz mytar.tar
```



查看：

```bash
tar -Jtvf mytar.tar.xz
```



解压：

```bash
tar -Jxf mytar.tar.xz
```

或者先用 `xz` 解压，再用 `tar` 提取文件：

```bash
xz -d mytar.tar.xz
tar -xf mytar.tar
```



#### .zip

网络中最常见的压缩包格式。linux 中使用 `zip` 工具打包，使用 `unzip` 工具查看和解压。

> `zip` 和 `unzip` 工具如果没有，可以使用系统包管理器安装。如(CentOS)：
>
> ```bash
> yum install -y zip
> yum install -y unzip
> ```

打包：

```bash
zip -r myZip.zip a.txt b.md
zip -r myDir.zip myDir/
```

查看：

```bash
unzip -l myZip.zip
```

解压：

```bash
unzip myZip.zip
```



#### .bz2

打包：

```bash
tar -jcf myBzip.bz2 a.txt b.md
```

或使用 `tar` 打包，再用 `bzip2` 压缩：

```bash
tar -cf mytar.tar
bzip2 mytar.tar
```



查看：

```bash
tar -jtvf myBzip.bz2
```



解压：

```bash
tar -jxf myBzip.bz2
```

对于 `.tar.bz2` 的，也可以先用 `bzip2` 解压，再用 `tar` 提取文件：

```bash
bzip2 -d mytar.tar.bz2
tar -xf mytar.tar
```

 

### 参考资料

- 文件压缩与解压_Linux命令大全: <https://man.linuxde.net/sub/%E6%96%87%E4%BB%B6%E5%8E%8B%E7%BC%A9%E4%B8%8E%E8%A7%A3%E5%8E%8B> 



### 总结

从本文的示例中可以看出，在 linux 系统中 `tar` 命令能够配合其他压缩工具很好的完成文件的打包、压缩、解压，使用不同类型的压缩工具时，只需要指定相应的参数即可，非常方便。
