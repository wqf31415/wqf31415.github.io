---
title: 认识和使用TCP协议
tags:
  - tcp
  - java
categories:
  - 技术
date: 2025-08-30 16:13:06
---

### 概述

这篇文章介绍了 tcp 协议的含义、特点与使用场景，以 java 语言实现了 tcp 服务端与客户端，并进行通信。



### 什么是 tcp

传输控制协议(**T**ransmission **C**ontrol **P**rotocol，缩写 TCP)，是一种面向连接的、可靠的、基于字节流的传输层通信协议，TCP协议基于 IP 协议实现。与用户数据报协议（**U**ser **D**atagram **P**rotocol，简称 UDP）一起作为传输层的两个重要协议。

| 五层网络模型 | 协议                                                      |
| ------------ | --------------------------------------------------------- |
| 应用层       | HTTP、FTP、TELNET、SSH、SNMP、DNS、SMTP、POP3、RPC...     |
| 传输层       | <b style="color:red">TCP</b>、UDP、TLS/SSL、PPTP、RSVP... |
| 网络层       | IP(v4,v6)、ICMP(v6)、IGMP、RARP、IS-IS...                 |
| 链路层       | Wi-Fi(IEEE 802.11)、ARP、以太网、GPRS、PPP...             |
| 物理层       | 以太网、调制解调器、电力线通信、光导纤维、双绞线...       |

<!-- more -->



### tcp 协议的特点

#### 面向连接--三次握手、四次挥手

TCP协议通信需要先建立连接，需要进行3次交互，称为三次握手；在终止连接时会进行4次交互，称为四次挥手。这么做的好处是确保通信双方都做好准备，并为后续的可靠传输初始化必要的序列号。

#### 可靠

这是TCP协议最核心的特点，通过一系列机制确保数据能够无误、不丢失、不重复、按序达到收端。

- 确认应答机制（ACK）：收到数据后，收端会发送一个响应报文（ACK），告知发送方已收到；
- 超时重传机制：发送方发送一个数据段后，会开启定时器，在一定时间内未收到对应的ACK，则认为发送失败，会重新发送该数据段；
- 序列号和确认号：每个字节都分配了序列号，每个ACK中包含确认号，告知发送方已收到哪个序列号之前的所有数据，下次从这个序列号开始发，这个特性解决了排序和去重的问题；

#### 基于字节流

TCP协议按字节流发送数据，不关注应用层定义的结构或边界。可能出现发送方程序多次写入数据，接收方一次读出；或发送方一次写入大量数据，接收方分多次读出。所以使用TCP传输时，应用层需要自己定义和处理数据边界，如使用特定的分隔符或消息头中指定长度。

#### 流量控制

TCP 可以通过控制流量防止数据发送过快，导致接收方缓冲区溢出。
实现机制：滑动窗口协议，接收方在每次ACK中告知发送方自己接收窗口大小，即自己缓冲区还可容纳多少字节，发送方根据这个大小调整发送速率，确保发送的数据不会超过接收方的处理能力。

#### 拥塞控制

TCP 通过拥塞控制防止发送方过多注入数据到网络中，避免网络链路（如路由器）过载，这是为了整个网络的全局利益。
实现机制：维护一个拥塞窗口，其大小表示当前网络的承载能力，TCP使用多种算法动态调整这个大小。
- 慢启动：连接刚开始时，窗口指数级增长，快速探测网络容量；
- 拥塞避免：窗口达到阈值后，转为线性增长，谨慎试探；
- 快速重传：收到3个相同ACK（表明有包丢失）后，立即重传丢失的报文，不必等待超时；
- 快速回复：在快速重传执行后，将窗口调整到一个合理值，避免网络震荡；

#### 全双工通信

TCP连接运行数据在同一时间双向流动，通信双方都有发送缓冲区和接收缓冲区，双方可以同时进行数据的发送和接收。

### tcp 协议使用场景

#### 基于tcp协议的应用层协议

tcp是广泛使用的传输层协议，在tcp协议基础上开发出了多种应用层协议，比如用于web访问的 http 协议，用于文件传输的 ftp 协议，用于远程登录的 telnet、ssh协议，用于邮件传输的smtp、pop3、imap等。

#### 基于tcp协议的通信业务

在通信或物联网行业中，常常会基于 tcp 协议结合自己的业务场景，开发出自己的通信协议，这些往往是在行业内或企业内部使用，称为私有协议。在基于 TCP 的自定义协议中，需要注意处理TCP黏包拆包问题。

#### 与UDP比较

和同为传输层协议的UDP相比，TCP协议需要建立连接，且实现了很多为了保证传输可靠的机制，因此TCP的传输速度较慢，系统开销大，因此TCP协议适用于传输可靠性要求高的场景。

### java 实现 tcp 通信

#### 原生 java

##### TCP 服务端

服务端代码逻辑：

- 使用 `java.net.ServerSocket` 类创建 TCP 服务端，指定监听端口为 `9000` 。

- 使用 `ServerSocket.accept()` 方法阻塞的等待客户端接入，接入后开启新线程处理连接消息；

- 使用 `java.util.Scanner` 按行读取客户端消息（即以换行符为消息分隔符），再将消息原文发回给客户端；

```java
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class TcpSocketServer {
    private static final int SERVER_PORT = 9000;
    public static void main(String[] args) {
        try (ServerSocket server = new ServerSocket(SERVER_PORT)){
            System.out.println("TCP 服务端在"+SERVER_PORT+"端口启动");
            while(true) { // 循环接收客户端连接请求
                Socket socket = server.accept(); // 阻塞的等待客户端接入
                new Thread(()->{ // 为每个客户端连接创建一个线程处理，不阻塞主线程
                    String clientInfo = socket.getInetAddress().getHostAddress()+":"+socket.getPort();
                    try (socket; 
                    InputStream  inputStream = socket.getInputStream(); 
                    OutputStream outStream = socket.getOutputStream();
                    Scanner scanner = new Scanner(inputStream)){ // 使用 scanner 按行读取消息
                        while(scanner.hasNextLine()) {
                            String line = scanner.nextLine();
                            System.out.println("收到客户端"+clientInfo+"消息: "+line);
                            String resp = "服务端收到: "+line +"\n"; // 将原文发回给客户端
                            outStream.write(resp.getBytes());
                            outStream.flush(); // 确保数据立即发出
                            System.out.println("已回复"+clientInfo+":"+resp.trim());
                        }
                        System.out.println("客户端"+clientInfo+"断开");
                    } catch (IOException e) {
                        System.out.println("与客户端"+clientInfo+"通信异常: "+e.getMessage());
                    }
                }).start();
            }
        } catch (IOException e) {
            System.out.println("服务端启动异常:"+e.getMessage());
            e.printStackTrace();
        }
    }
}
```

##### TCP 客户端

客户端代码逻辑：

- 使用 `java.net.Socket` 类创建和服务端的TCP连接，创建连接时指定服务端地址、端口；

- 循环使用 `java.util.Scanner` 读取用户在控制台的输入，判断输入内容为 `exit` 则退出循环，关闭连接，非 `exit` 内容则添加换行符后发送给服务端；

- 使用 `java.util.Scanner` 按行读取服务端响应，打印到控制台；

```java
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Scanner;

public class TcpSocketClient {
    private static final String SERVER_ADDR = "localhost";
    private static final int SERVER_PORT = 9000;
    public static void main(String[] args) {
        try (Socket socket = new Socket(SERVER_ADDR, SERVER_PORT); 
            InputStream input = socket.getInputStream();
            OutputStream output = socket.getOutputStream();
            Scanner consoleScanner = new Scanner(System.in);
            Scanner serverScanner = new Scanner(input);) {

            System.out.println("连接到服务器: "+SERVER_ADDR+":"+SERVER_PORT);
            System.out.println("输入发送的信息(输入exit退出):");
            while (true) {
                System.out.print("> ");
                String userInput = consoleScanner.nextLine(); // 读取用户输入
                if ("exit".equals(userInput.trim())){ // 检查用户是否想退出
                    System.out.println("关闭客户端");
                    break;
                }
                String msgToSend = userInput+"\n"; //  给发送的消息后加上换行，方便服务端使用 Scanner按行读取消息
                output.write(msgToSend.getBytes());
                output.flush(); // 立即发出消息
                System.out.println("向服务器发送消息:"+userInput);
                if (serverScanner.hasNextLine()) { // 阻塞的等待服务端响应消息
                    String serverResp = serverScanner.nextLine();
                    System.out.println("收到服务端消息:"+serverResp);
                } else {
                    System.out.println("服务端未返回响应或连接已关闭");
                }
            }
        } catch (IOException e) {
            System.out.println("连接失败:"+e.getMessage());
            e.printStackTrace();
        }
        System.out.println("客户端已关闭");
    }
}
```

#### netty

##### TCP 服务端

实现基于Netty框架的TCP服务器，这是一个基础模板，可以根据业务和需求进行优化和扩展，代码逻辑：

- 创建了一个 `NettyTcpServer` 类，封装创建TCP服务端和消息处理逻辑，其中 `bind()` 方法可传入要绑定的IP和端口；
- 在方法中创建两个事件循环组，分别用于接收客户端连接和处理已接收的连接；
- 创建一个服务器应道类（`io.netty.bootstrap.ServerBootstrap`）对象，给服务器添加配置，包括设置事件循环组、指定使用NIO传输通道、设置服务器连接队列大小、设置处理连接的处理器；
- 绑定服务器到指定IP和端口，并同步等待绑定完成；
- 等待服务器通道关闭；

`NettyTcpServer.java` 运行后将在 6666 端口开启 tcp 服务端。

```java
import io.netty.bootstrap.ServerBootstrap;
import io.netty.buffer.ByteBuf;
import io.netty.channel.*;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.SocketChannel;
import io.netty.channel.socket.nio.NioServerSocketChannel;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;

public class NettyTcpServer {
    public static void main(String[] args) {
        NettyTcpServer tcpServer = new NettyTcpServer();
        tcpServer.bind("0.0.0.0", 6666);
    }

    public void bind(String ip, int port) {
        // 创建两个事件循环组
        EventLoopGroup bossGroup = new NioEventLoopGroup(); // bossGroup 用于接受客户端连接
        EventLoopGroup workGroup = new NioEventLoopGroup(); // workGroup 用于处理已接受的连接
        try {
            ServerBootstrap bootstrap = new ServerBootstrap(); // 创建服务器启动引导类
            // 配置服务器引导
            bootstrap.group(bossGroup, workGroup) // 设置事件循环组
                    .channel(NioServerSocketChannel.class) // 指定使用NIO传输通道
                    .option(ChannelOption.SO_BACKLOG, 1024) // 设置服务器接受连接的队列大小
                    .childHandler(new ChannelInitializer<SocketChannel>() { // 设置处理连接的处理器
                        @Override
                        protected void initChannel(SocketChannel socketChannel) throws Exception {
                            socketChannel.pipeline().addLast(new ChannelInboundHandlerAdapter() { // 将自定义的ChannelInboundHandlerAdapter添加到管道中
                                @Override
                                public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
                                    InetSocketAddress address = (InetSocketAddress) ctx.channel().remoteAddress(); // 获取客户端地址信息
                                    System.out.println("Recv msg from: " + address.getHostString() + ":" + address.getPort());
                                    // 读取接收到的消息
                                    ByteBuf bf = (ByteBuf) msg;
                                    byte[] bs = new byte[bf.readableBytes()];
                                    bf.readBytes(bs);
                                    System.out.println("Recv msg: " + new String(bs));
                                    // 准备响应消息，固定响应内容为world
                                    ByteBuf repMsg = ctx.alloc().buffer(5);
                                    repMsg.writeBytes("world".getBytes(StandardCharsets.UTF_8));
                                    // 发送响应消息并添加监听器
                                    final ChannelFuture f = ctx.channel().writeAndFlush(repMsg);
                                    f.addListener(new ChannelFutureListener() {
                                        @Override
                                        public void operationComplete(ChannelFuture channelFuture) throws Exception {
                                            assert f == channelFuture;
                                            System.out.println("Send req msg finish");
                                            // 注意：这里注释掉了关闭连接的代码
                                            // 在实际应用中，根据需要决定是否关闭连接
//                                            ctx.close(); // 关闭会话
                                        }
                                    });
                                }

                                @Override
                                public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) throws Exception {
                                    // 异常处理：打印异常并关闭连接
                                    cause.printStackTrace();
                                    ctx.close();
                                }
                            });
                        }
                    });
            ChannelFuture cf = bootstrap.bind(ip, port).sync(); // 绑定服务器到指定IP和端口，并同步等待绑定完成
            cf.channel().closeFuture().sync(); // 等待服务器通道关闭
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            // 优雅关闭事件循环组，释放资源
            workGroup.shutdownGracefully();
            bossGroup.shutdownGracefully();
        }
    }
}
```



##### TCP 客户端

基于Netty框架实现一个基础 TCP 客户端，可根据业务和需求在此基础上优化和扩展。

代码主要逻辑：
- 创建事件循环组（`EventLoopGroup`），用于处理所有IO操作；
- 创建和配置客户端引导程序`Bootstrap`，设置NIO传输通道和TCP参数；
- 建立到指定IP、端口的连接，将通道（`SocketChannel`）保存下来供后续使用，添加连接状态监听器；
- 通过保存的通道给服务端发送消息，接收处理服务端消息，添加消息发送状态的监听器；
- 最后提供关闭连接的方法，优雅关闭事件循环组；

NettyTcpClient.java

```java
import io.netty.bootstrap.Bootstrap;
import io.netty.buffer.ByteBuf;
import io.netty.buffer.Unpooled;
import io.netty.channel.*;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.SocketChannel;
import io.netty.channel.socket.nio.NioSocketChannel;

import java.nio.charset.StandardCharsets;

public class NettyTcpClient {
    private final EventLoopGroup group = new NioEventLoopGroup(); // 事件循环组，用于处理所有I/O操作
    private volatile SocketChannel socketChannel = null; // 客户端通道，使用volatile保证多线程环境下的可见性

    public static void main(String[] args) throws InterruptedException {
        NettyTcpClient client = new NettyTcpClient(); // 创建客户端实例
        client.connect("127.0.0.1", 6666); // 连接到服务器
        client.send("hello"); // 发送消息
        Thread.sleep(2000); // 等待2秒确保响应被接收
        client.close(); // 关闭连接
    }

    public void connect(String ip, int port) {
        Bootstrap bootstrap = new Bootstrap(); // 创建客户端引导类
        bootstrap.group(group) // 设置事件循环组
                .channel(NioSocketChannel.class)  // 指定使用NIO客户端通道
                .remoteAddress(ip, port)  // 设置远程服务器地址
                .option(ChannelOption.SO_KEEPALIVE, true)  // 启用TCP keepalive机制
                .option(ChannelOption.TCP_NODELAY, true) // 禁用Nagle算法，减少延迟
                .handler(new ChannelInitializer<SocketChannel>() { // 设置处理器
                    @Override
                    protected void initChannel(SocketChannel socketChannel) throws Exception {
                        socketChannel.pipeline().addLast(new ChannelInboundHandlerAdapter() { // 添加入站处理器，处理从服务器接收的消息
                            @Override
                            public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
                                // 读取服务器响应
                                ByteBuf bf = (ByteBuf) msg;
                                byte[] bs = new byte[bf.readableBytes()];
                                bf.readBytes(bs);
                                System.out.println("Recv msg: " + new String(bs));
                            }
                        });
                    }
                });
        ChannelFuture channelFuture = null;
        try {
            channelFuture = bootstrap.connect().sync(); // 连接到服务器并等待连接完成
            channelFuture.addListener(new ChannelFutureListener() { // 添加连接完成监听器
                @Override
                public void operationComplete(ChannelFuture channelFuture) throws Exception {
                    System.out.println("Tcp connect to " + ip + ":" + port + ", result: " + channelFuture.isSuccess());
                }
            });
            socketChannel = (SocketChannel) channelFuture.channel(); // 保存通道引用供后续使用
        } catch (Exception e) {
            e.printStackTrace();
            // 发生异常时优雅关闭事件循环组
            group.shutdownGracefully();
        }
    }

    public void send(String msg) {
        if (socketChannel == null || !socketChannel.isActive()) { // 检查连接状态
            System.out.println("The client do Not connect to server...");
            return;
        }

        try {
            ChannelFuture future = socketChannel.writeAndFlush(Unpooled.wrappedBuffer(msg.getBytes(StandardCharsets.UTF_8))).sync(); // 将消息包装为ByteBuf并发送，等待发送完成
            future.addListener(new ChannelFutureListener() { // 添加发送完成监听器
                @Override
                public void operationComplete(ChannelFuture channelFuture) throws Exception {
                    System.out.println("Send msg: " + msg + ", result: " + channelFuture.isSuccess());
                }
            });
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void close() throws InterruptedException {
        if (socketChannel != null) { // 断开连接并关闭通道
            socketChannel.disconnect();
            socketChannel.close().sync();
        }
        group.shutdownGracefully(); // 优雅关闭事件循环组
    }
}
```





### 参考资料

- 传输控制协议 - 维基百科: <https://zh.wikipedia.org/wiki/%E4%BC%A0%E8%BE%93%E6%8E%A7%E5%88%B6%E5%8D%8F%E8%AE%AE> 



### 总结

- TCP是常用的可靠的传输层协议，基于IP协议实现，用于数据可靠传输场景。
- TCP的特点包括：面向连接、可靠性、基于字节流传输、具有流量控制和拥塞控制、传输速度比UDP慢。