---
title: curl工具的使用方法
tags:
  - 工具
  - test
  - 网络
  - 终端
categories:
  - 工具
date: 2025-09-24 22:17:23
---

### 概述

这篇文章介绍了一个开源功能强大的命令行网络工具 curl，curl 功能丰富，用法简单，被广泛用于命令行、终端的网络请求场景中。这篇文件简要介绍了 curl 的功能和使用方法。

<svg xmlns="http://www.w3.org/2000/svg" style="background: #ffffff; background-color: light-dark(#ffffff, var(--ge-dark-color, #121212)); color-scheme: light dark;" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1" width="652px" height="311px" viewBox="-0.5 -0.5 652 311"><defs/><rect fill="#ffffff" width="100%" height="100%" x="0" y="0" style="fill: light-dark(#ffffff, var(--ge-dark-color, #121212));"/><g><g data-cell-id="0"><g data-cell-id="1"><g data-cell-id="MQQ1DA55CuxLmnpaJDzZ-1"><g><rect x="20" y="110" width="120" height="40" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: light-dark(#ffffff, var(--ge-dark-color, #121212)); stroke: light-dark(rgb(0, 0, 0), rgb(255, 255, 255));"/></g></g><g data-cell-id="MQQ1DA55CuxLmnpaJDzZ-2"><g><rect x="0" y="150" width="50" height="120" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: light-dark(#ffffff, var(--ge-dark-color, #121212)); stroke: light-dark(rgb(0, 0, 0), rgb(255, 255, 255));"/></g></g><g data-cell-id="MQQ1DA55CuxLmnpaJDzZ-3"><g><rect x="20" y="270" width="120" height="40" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: light-dark(#ffffff, var(--ge-dark-color, #121212)); stroke: light-dark(rgb(0, 0, 0), rgb(255, 255, 255));"/></g></g><g data-cell-id="MQQ1DA55CuxLmnpaJDzZ-4"><g><rect x="190" y="110" width="50" height="200" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: light-dark(#ffffff, var(--ge-dark-color, #121212)); stroke: light-dark(rgb(0, 0, 0), rgb(255, 255, 255));"/></g></g><g data-cell-id="MQQ1DA55CuxLmnpaJDzZ-5"><g><rect x="300" y="110" width="50" height="200" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: light-dark(#ffffff, var(--ge-dark-color, #121212)); stroke: light-dark(rgb(0, 0, 0), rgb(255, 255, 255));"/></g></g><g data-cell-id="MQQ1DA55CuxLmnpaJDzZ-6"><g><rect x="190" y="270" width="110" height="40" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: light-dark(#ffffff, var(--ge-dark-color, #121212)); stroke: light-dark(rgb(0, 0, 0), rgb(255, 255, 255));"/></g></g><g data-cell-id="MQQ1DA55CuxLmnpaJDzZ-8"><g><rect x="400" y="110" width="50" height="200" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: light-dark(#ffffff, var(--ge-dark-color, #121212)); stroke: light-dark(rgb(0, 0, 0), rgb(255, 255, 255));"/></g></g><g data-cell-id="MQQ1DA55CuxLmnpaJDzZ-9"><g><rect x="450" y="120" width="110" height="40" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: light-dark(#ffffff, var(--ge-dark-color, #121212)); stroke: light-dark(rgb(0, 0, 0), rgb(255, 255, 255));"/></g></g><g data-cell-id="MQQ1DA55CuxLmnpaJDzZ-10"><g><rect x="601" y="0" width="50" height="310" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: light-dark(#ffffff, var(--ge-dark-color, #121212)); stroke: light-dark(rgb(0, 0, 0), rgb(255, 255, 255));"/></g></g></g></g></g></svg>

### curl 是什么

curl 是一个命令行工具，利用 URL 语法在命令行中完成数据传输的工具，支持文件上传和下载。

> 官网：<https://curl.se/> 
>
> 源码：<https://github.com/curl/curl> 

curl 支持的协议（参考官网介绍）：

|协议|详情|
|:----:|:-----|
|Protocol|DICT, FILE, FTP, FTPS, GOPHER, GOPHERS, HTTP, HTTPS, IMAP, IMAPS, LDAP, LDAPS, MQTT, POP3, POP3S, RTMP, RTMPS, RTSP, SCP, SFTP, SMB, SMBS, SMTP, SMTPS, TELNET, TFTP, WS, WSS|
|Proxies|SOCKS4, SOCKS5, HTTP, HTTPS (HTTP/1 and HTTP/2), tunneling, via unix domain sockets, haproxy, SOCKS+HTTP proxy chain|
|HTTP|GET, POST, PUT, HEAD, multipart formpost, HTTP/0.9, HTTP/1.0, HTTP/1.1, HTTP/2 (h2c, h2, prior knowledge), HTTP/3 (dual connect h1/h2 + h3 or h3-only), HSTS, Alt-Svc, cookies, PSL, etags, transfer compression, ranges, custom headers, custom method, follow redirects|
|FTP|IPv6 (EPRT, EPSV), STLS, upload/download, append, range, passive/active, kerberos, directory listing, custom commands|
|SCP + SFTP|known hosts, md5/sha256 fingerprint, compression, upload/download, directory listing|
|TLS|1.0 - 1.3, mutual authentication, STARTTLS, OCSP stapling, ECH, False Start, key pinning, PQC ready, session resumption, early data, export/import sessions|
|QUIC|0RTT handshakes|
|Auth|Basic, Plain, Digest, CRAM-MD5, SCRAM-SHA, NTLM, Negotiate, Kerberos, Bearer tokens, AWS Sigv4, SASL, .netrc|
|HTTP compression|gzip, brotli and zstd|
|Name resolving|DNS-over-HTTPS, custom address for host, name+port redirect, custom DNS servers, DNS caching, HTTPS RR|
|Connection|connection reuse, Interface binding, Happy Eyeballs, IPv4/IPv6-only, unix domain sockets, TCP keepalive, TCP Fast Open, TCP Nodelay, MPTCP, VLAN priority, IP Type Of Service|
|Transfers|transfer rate limiting, request rate limiting, stall detection, retries, timeouts|
|URLs|Unlimited amount, parallel and serial transfers, globbing|
|Output|IDN hostnames, custom info from transfer, metadata as JSON, per content-disposition, libcurl source code, bold headers|


<!-- more -->

### curl 的特性

#### 基本特性

curl 支持数百个选项参数，支持无限数量的 URL 地址。

选项参数支持短选项（如`-v`）和长选项（如`--verbose`），短选项使用单个 `-` 后面跟一个字母，长选项使用 `--` 后面跟上选项名。

>很多选项是切换开关，用于启动某些功能或切换两个已知状态，可以将多个这种短选项写到一起，如 `-vL` 打开详细模式并启动重定向。

```bash
# 打开详细模式并启动重定向
curl -vL http://example.com
curl --verbose --location http://example.com
```
curl 中带参数的选项使用时，需要先指定选项，以空格分隔，后面跟上参数值。如果参数中带有空格则需要用引号包括，如果参数值中包含引号，则可以使用单引号包括，或者将传输内容写到文件中，读取文件内容进行传输。

```bash 
# -d 选项指定要发送的数据内容
curl -d '{"name":"Zhang San"}' http://example.com
curl -d @info.json http://example.com
```

在 curl 内部维护着一个连接池，让创建的连接存活一段时间，后续发给相同主机的请求可以重用这些已经建立的连接。如果在同一命令行中指定多个 URL，就会看到它将使用多个连接或重用已有的连接，因此连接的计数器可能会增加，也可能不会增加，具体取决于 curl 需要执行的操作。

执行 curl 指令时，curl 会先解析整条命令，应用指定的命令行选项，所以**选项可以放在任意位置**，甚至是 URL 之后，然后（按从左到右的顺序）遍历 URL 并执行相应操作。

> 注意，默认情况下 curl 会将命令中所有选项都应用到每个 URL请求中。
> 但 curl 提供了选项 `--next` ，短格式为 `-;` ，可以在一组选项和 URL 之间插入间隔。
> 当命令行解析器遇到 `--next` 选项时，它会将后面的选项应用于下一组URL。因此，`--next` 选项可以作为多组选项和URL之间的分隔符。使用多少个 `--next` 选项取决于实际的需要。

```bash
curl 选项组1 URL1 --next 选项组2 URL2_1 URL2_2 --next ...
```

curl 会在处理完最后一个 URL 后返回一个退出码。想让 curl 在第一次出现错误时就退出，则可以使用 `--fail-early` 选项。

#### 通配

curl 使用保留符号 `[]` 和 `{}` 进行通配，使用 `[N-M]` 语法来指定一个数值范围，其中 `N` 是起始索引，`M` 是结束索引（包括M在内）。可以指定步进（step counter），curl 也可以处理字母范围。如：

```bash 
# 请求 1~100 的图片文件
# -O 选项指定使用URL中的名称作为文件名保存
curl -O http://example.com/[1-100].jpg 

# 请求 001~100 的图片文件
curl -O http://example.com/[001-100].jpg

# 指定步进为2
curl -O http://example.com/[1-100:2].jpg

# 请求 a-z 的图片
curl -O http://example.com/[a-z].jpg
```

有时 URL 不是以简单的数字或字母顺序命名的模式，curl 支持指定完整的匹配列表，但要放在花括号，而不是中括号中。

在同一个 URL 中使用多个通配时，URL 中的每个通配都对应一个单独的变量，可以通过 '#[num]' 来引用，即在 '#' 后面跟上与通配对应的数字，从 1（对应第一个通配）开始，以最后一个通配结束。

```bash
# 获取一周的图片
curl -O http://example.com/{Mon,Tues,Wed,Thur,Fri,Sat,Sun}.jpg

# 多个通配一起使用，请求一周每个小时的图片
curl -O http://example.com/{Mon,Tues,Wed,Thur,Fri,Sat,Sun}-[0-23].jpg

# 引用通配变量，将图片按星期保存
curl http://example.com/{Mon,Tues,Wed,Thur,Fri,Sat,Sun}-[0-23].jpg -o /pic/#1/#2.jpg
```

#### 配置文件

curl 支持配置文件，可以将命令行选项写在文本文件中，curl 执行每个命令，都会从配置文件中读取命令行选项。

默认查找使用主目录中的配置文件，可以使用 `-K` 或 `--config` 选项指定使用的配置文件；使用 `-q` 选项让 curl 不读取配置文件。

> 在类 Unix 系统上，会查找主目录下的 `.curlrc` 文件;
> 在 Windows 系统上则查找主目录下的 `_curlrc` 文件，如果没找到会在 curl 可执行程序所在目录中查找。

```bash
curl -K curl.conf http://example.com
```
配置文件内容：

- 以 `#` 添加注释

- 配置文件中可以使用短选项和长选项，与命令行中写法相同，为了便于阅读，允许使用不带破折号的长选项。

- 配置文件中带参数的选项，参数必须与该选项处于同一行。

- 配置文件中允许在选项及其参数之间使用 `=` 或 `:`，虽然这样做不是必须的。

- 选项的参数也可以不使用引号，curl将下一个空格或换行视为当前参数的结尾，如果参数中带有空格，则必须使用双引号。

- 如果想在配置文件中指定URL，则必须使用 `--url` 或 `url` ，而且不会像在命令行中那样不是选项的所有东西都被视为URL

```
# 注释，开启跟踪重定向
--location
# 发送 HEAD 请求
--head
# 配置 user-agent 头部
user-agent "Everything-is-an-agent"
# 使用短选项
-H 'Content-Type: application/json'
# 使用 = 连接参数，指定 URL
url="http://example.com"
```

#### 身份验证

curl 中最基本的身份验证选项是 `-u` 或 `--user`，支持传递用户名密码，用户名和密码使用冒号分隔，如 `-u admin:123456` 。

为了避免在命令行中暴露密码信息，可以使用 `-u` 选项，但不指定密码，这样在执行时会提示用户输入密码。

另外一种方法是使用 `.netrc` 文件或配置文件。

#### 保存文件

可以通过 `-o [filename]` 或 `--output` 选项为 curl 指定一个特定的文件名来保存下载的内容。filename可以是文件名，也可以是文件的相对路径或完整路径。

> 可以将 `-o` 放在 URL 之前或之后，二者没有什么区别。

`-O` 或 `--remote-name` 选项指定从 URL 中提取文件名保存文件。注意 `-O` 选项只会提取文件名的部分作为本地文件名，路径部分将被忽略。

> 即使发生了重定向（而且你告诉curl要跟踪重定向），curl选择的文件名也不会发生变化。

HTTP 服务器可以选择在响应消息中提供 Content-Disposition 标头，这个标头可能包含服务器建议的文件名，可以使用 `-J` 或 `--remote-header-name` 选项让 curl 使用这个名字作为本地文件名。

> 如果同时还使用了-O选项，那么curl默认使用 URL 中的文件名，只有当响应消息中包含有效的 Content-Disposition 标头时，才会使用这个建议的文件名。

注意：

- curl 只会使用建议文件名的最右边部分，服务器建议的其他路径或目录都会被忽略。
- 如果服务器提供了与本地文件相同的文件名，那么 curl 将覆盖当前目录中已有的本地文件。
- curl 不会对文件名进行编码，因此你可能会得到一个 URL 编码的文件名

每个 URL 都需要单独指定 “存储指令”，没有指定 “存储指令” 的，curl会默认将数据发送到 stdout。

存储指令和 URL 的顺序是一一对应的，第一个存储指令对应第一个URL。存储指令所在的位置不影响与 URL 的对应关系。

`-O` 只用于单个下载，如果你要下载多个 URL，则需要使用多个 `-O`。

```bash
# 如果你要下载两个URL并只为第一个URL提供保存位置，那么第二个URL将被发送到stdout
# 图片文件保存到本地，txt文件内容输出到标准输出
curl -O http://example.com/1.jpg http://example/1.txt

# “存储指令”的读取和处理顺序与下载的URL的顺序相同，因此它们不一定要位于URL之后。你可以将所有输出选项放在最前面或最后面，或者与URL交错放置
curl -o my_1.jpg http://example.com/1.jpg -o 2.jpg http://example.com/2.jpg
curl -o my_1.jpg http://example.com/1.jpg http://example.com/2.jpg -o 2.jpg
curl -o my_1.jpg -o 2.jpg http://example.com/1.jpg http://example.com/2.jpg
curl http://example.com/1.jpg http://example.com/2.jpg -o my_1.jpg -o 2.jpg
```

#### 断点续传

`-C` 或 `--continu-at` 选项可以指定开始传输的位置，选项的值可以是表示偏移量的普通的数字（单位：字节），或者使用字符串 `-` 让 curl 自动识别从哪里开始传输。

如果使用 `-` ，那么 curl 将计算本地目标文件的数据量，并将其作为向服务器请求更多数据的偏移量。


### 使用 curl 发起 http 请求

curl 发起 http请求时，具体使用的请求方法取决于使用的选项。默认方法是 GET，`-d` 或 `-F` 选项对应 POST方法，`-I` 对应 HEAD 方法，`-T` 对应 PUT 方法。

| 请求方法 | 选项 | 示例 |
|:-----:|:-----:|:-----|
|GET|`-G` 或 `--get` |`curl -G http://example.com`|
|POST|`-d` 或 `-F` |`curl -d 'name=xiaoming&age=12' http://example.com/`|
|PUT| `-T` 或 `curl -T localfile http://example.com/new/resource/file` |
|DELETE| `-X DELETE` | `curl -X DELETE http://example.com/file` |

#### GET

curl 默认发起的 http 请求使用 GET 方法，也可以使用 `-G` 或 `--get` 选项显式的指定使用 GET 方法。

```bash
curl https://www.example.com
curl -G https://www.example.com

# 带参数的 GET 请求
curl http://example.com/?id=101&name=xiaoming
```

#### POST

在 html 表单中填好表单后，浏览器会以URL编码的形式将数据发送出去，在 curl 中，可以使用 `-d` 或 `--data` 选项发送数据。

```bash 
curl -d 'name=xiaoming&age=12' http://example.com/
```

在命令行上使用多个 `-d` 选项时，curl 会将它们串联起来，并在它们之间插入 `&` 符号。以下命令和上面的是等价的:

```bash 
curl -d name=xiaoming -d age=12 http://example.com/
```

如果要发送的数据量不适合作为字符串放在命令行中，还可以从文件中读取：

```bash
curl -d @filename http://example.com
```

##### 发送 JSON 格式数据

使用 curl 的 `-d` 选项发送 POST 请求时，请求中默认会包含一个类似 `Content-Type: application/x-www-form-urlencoded` 这样的标头。典型的浏览器在发送 POST 请求时也会使用这个标头。

如果需要使用其他标头，可以使用 `-H` 指定想要的标头，如指定使用 JSON 格式传输数据:

```bash 
curl -d '{json}' -H 'Content-Type: application/json' http://example.com
```

##### 发送二进制内容

使用 `-d` 选项从文件读取内容时，回车符和换行符将被移除，可以使用 `--data-binary` 选项让 curl 从文件读取二进制内容。

```bash 
curl --data-binary @filename http://example.com
```

##### 发送文件

在 html 的表单中要上传文件时（通常是 type 属性为 file 的 input 标签），表单的 enctype 属性被设置成 `multipart/form-data` ，使用 curl时，可以通过 `-F` 或 `--form` 选项添加每个单独的 multipart，然后继续为表单每个字段添加一个 `-F` 。

```bash 
curl -F name=xiaoming -F img=@my.png http://example.com
```

#### PUT

`-T` 选项指定使用 PUT 方法，POST 和 PUT 非常相似，也可以用 `-d` 加上字符串来发送 PUT 请求：

```bash
curl -T localfile http://example.com/new/resource/file
curl -d "data to PUT" -X PUT http://example.com/new/resource/file
```

#### 其他请求方法

使用 `-X` 或 `--request` 选项其他请求方法，如 `-X DELETE` 。

```bash
curl -X DELETE http://example.com/file
```

#### 使用 cookie

使用 `-c` 选项将 cookie 写入指定文件：
```bash
curl -c cookie-jar.txt http://example.com
```

使用 `-b` 选项从文件读取初始 cookie：

```bash
curl -L -b cookies.txt http://example.com
```

使用 `-j` 或 `--junk-session-cookies` 选项让 curl 开始新的 cookie 会话：

```bash
curl -j -b cookies.txt http://example.com/
```

#### 身份认证

要让 curl 发出带有身份认证的 http 请求，可以使用 `-u` 或 `--user` 选项提供用户名和密码（用冒号分隔）。

```bash 
curl -u admin:123456 http://example.com/
```

curl 默认使用 Basic 身份校验方法，如果想明确指定使用这个方法，可以使用 `--basic` 选项。

如果要让 curl 先确认服务器是否真的需要身份验证，可以使用 `--anyauth` 选项，它会自动使用curl 所知道的最安全的身份验证方法。curl 将尝试无须身份验证的请求，然后在必要的时候使用身份验证。

```bash 
curl --anyauth -u admin:123456 http://example.com/
```

curl 通常支持几种身份验证方法，包括 Digest、Negotiate、NTLM，可以分别使用 `--digest` 、`--negotiate` 、`--ntlm` 选项指定。

#### 请求 http 区间

curl 支持获取http 资源的指定范围内容，如获取远程资源前 200 个字节或中间 300 个字节，使用 `-r` 或 `--range` 选项发起区间请求。

```bash 
# 获取前200个字节
curl -r 0-199 http://example.com

# 索引200之后的所有内容
curl -r 200- http://example.com

# 从索引0处获取200个字节，再从索引800处获取200个字节
curl -r 0-199,800-199 http://example.com
```

#### 压缩

 HTTP 支持压缩传输响应消息，curl 中使用 `--compressed` 选项请求压缩后进行数据传输，可使用 `--tr-encoding` 选项指定压缩传输编码。

服务端接受压缩传输请求后，通常会在响应头中携带 `Content-Encoding: gzip` 的标头，通知客户端内容经过了压缩。

在接收压缩的内容后，curl 会自动进行解压。


#### 指定 http 协议版本

使用如下选项指定使用的 HTTP 协议版本：

| 选项 | 描述 |
|:----:|:----:|
|`--http1.0`|HTTP/1.0|
|`--http1.1`|HTTP/1.1|
|`http2`|HTTP/2|
|`http3`|HTTP/3|


### FTP 请求

#### 关于FTP的一些知识

使用 FTP 传输数据时，会创建两个 TCP 连接：

1、客户端连接到 FTP 服务器时建立第一个连接，称作控制连接。作为初始连接，它将负责处理身份验证、切换到正确的远程服务器目录，等等。

2、当客户端准备好传输文件时，第二个TCP连接将建立，并通过这个连接传输数据。

FTP的主动模式和被动模式：

**主动模式**：在建立数据传输的TCP连接时，客户端可以请求服务器回连到客户端来建立连接，即所谓的“主动”连接。

**被动模式**：客户端向服务器发送 PASV 或 EPSV 命令，服务器为第二个连接打开一个新端口，然后客户端会连接到这个端口上。curl默认请求使用被动模式。

#### 上传文件

使用 FTP 上传文件时，需要在 URL 中指定整个目标文件的路径和名字，并用 `-T` 或 `--upload-file` 选项指定要上传的本地文件。

> 如果目标URL以斜杠结尾，curl会自动将本地路径中的文件名追加到URL中，并将其作为远程文件名。

```bash
curl -T localfile ftp://ftp.example.com/dir/path/
```

curl 使用 FTP 上传文件时，`-T` 参数支持通配符，可一次指定上传多个文件。

#### 安全文件传输

SCP 和 SFTP 都是建立在 SSH 之上的协议，SSH是一种类似于 TLS 的安全加密数据协议，但在某些方面有所不同。例如，SSH不使用任何类型的证书，而是使用公钥和私钥。

```bash
curl sftp://example.com/file.zip -u user
curl scp://example.com/file.zip -u user
```

如果 URL 以斜杠 `/` 结尾，SFTP（不是SCP）可以获取文件列表：

```bash
curl sftp://example.com/ -u user
```

> FTP 与 SFTP、SCP 的 URL 路径区别：
> SFTP 或 SCP 请求文件时，URL 中的文件路径被视为远程服务器上的绝对路径。可以使用 /~/ 来指定用户主目录的相对路径。
> FTP 请求文件时， URL 中的路径是相对路径。

使用基于密钥的安全传输时，如 SFTP、SCP，curl会先确认服务器是否可被信任，即检查 `known_hosts` 中是否存在目标主机的密钥散列，检查通过后 curl 就会开始执行传输。想强制 curl 跳过检查，可以使用 `-k` 或 `--insecure` 选项。

> 在Linux系统上， `known_hosts` 文件通常存放在 `~/.ssh` 目录。



### 邮件请求

curl 支持邮件协议，可以收发邮件。

#### 使用 POP3 读取邮件

列出消息编号和大小：`curl pop3://mail.example.com/` 

下载消息1：`curl pop3://mail.example.com/1` 

删除消息1：`curl --request DELE pop3://mail.example.com/1` 

#### 使用 SMTP 发送邮件

发送邮件时，下面两个参数是必须的：

- `--mail-rcpt` 选项指定收件人的邮箱（至少一个）

- `--mail-from` 选项指定发件人的邮箱

发送邮件时，邮件数据是一个使用RFC 5322 指定格式的文本文件，它由一组标头和正文组成，标头和正文都需要进行正确编码。

标头通常包括 `To:`、`From:`、`Subject:`、`Date:` 等

如果邮箱支持 SSL 端口，可以用 `smtps://` 代替 `smtp://`，默认的 SMTP SSL 端口为 465 。

```bash
curl smtp://mail.example.com --mail-form xiaoming@example.com --mail-rcpt daming@example.com --upload-file example.txt
```

example.txt:

```
From: Xiaoming<xiaoming@example.com>
To: Daming<daming@example.com>
Subject: Example email
Date: Mon 23 Set 2025 23:19:00

Dear Daming,
xxxx....
```


### 参考资料

- 丹尼尔·斯坦伯格.《cURL必知必会》.20200101
- Everything curl: <https://ec.haxx.se/> 
- github everything-curl: <https://github.com/bagder/everything-curl> 
