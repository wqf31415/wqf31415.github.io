---
title: 认识和使用TCP协议
tags:
  - tcp
  - java
categories:
  - 技术
date: 2021-06-09 09:34:06
---

### 概述

这篇文章介绍了 tcp 协议的含义、特点与使用场景，以 java 语言实现了 tcp 服务端与客户端，并进行通信。



### 什么是 tcp

传输控制协议(**T**ransmission **C**ontrol **P**rotocol，缩写 TCP)，是一种面向连接的、可靠的、基于字节流的传输层通信协议。与用户数据报协议（**U**ser **D**atagram **P**rotocol，简称 UDP）一起作为传输层的两个重要协议。

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



#### 可靠



#### 基于字节流



### tcp 协议使用场景



### java 实现 tcp 协议

#### 原生 java



#### netty

##### TCP 服务端

NettyTcpServer.java

运行后将在 6666 端口开启 tcp 服务端。

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
        EventLoopGroup bossGroup = new NioEventLoopGroup();
        EventLoopGroup workGroup = new NioEventLoopGroup();
        try {
            ServerBootstrap bootstrap = new ServerBootstrap();
            bootstrap.group(bossGroup, workGroup)
                    .channel(NioServerSocketChannel.class)
                    .option(ChannelOption.SO_BACKLOG, 1024)
                    .childHandler(new ChannelInitializer<SocketChannel>() {
                        @Override
                        protected void initChannel(SocketChannel socketChannel) throws Exception {
                            socketChannel.pipeline().addLast(new ChannelInboundHandlerAdapter() {
                                @Override
                                public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
                                    InetSocketAddress address = (InetSocketAddress) ctx.channel().remoteAddress();
                                    System.out.println("Recv msg from: " + address.getHostString() + ":" + address.getPort());
                                    ByteBuf bf = (ByteBuf) msg;
                                    byte[] bs = new byte[bf.readableBytes()];
                                    bf.readBytes(bs);
                                    System.out.println("Recv msg: " + new String(bs));
                                    ByteBuf repMsg = ctx.alloc().buffer(5);
                                    repMsg.writeBytes("world".getBytes(StandardCharsets.UTF_8));
                                    final ChannelFuture f = ctx.channel().writeAndFlush(repMsg);
                                    f.addListener(new ChannelFutureListener() {
                                        @Override
                                        public void operationComplete(ChannelFuture channelFuture) throws Exception {
                                            assert f == channelFuture;
                                            System.out.println("Send req msg finish");
//                                            ctx.close(); // 关闭会话
                                        }
                                    });
                                }

                                @Override
                                public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) throws Exception {
                                    cause.printStackTrace();
                                    ctx.close();
                                }
                            });
                        }
                    });
            ChannelFuture cf = bootstrap.bind(ip, port).sync();
            cf.channel().closeFuture().sync();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            workGroup.shutdownGracefully();
            bossGroup.shutdownGracefully();
        }
    }
}
```



##### 客户端

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
    private final EventLoopGroup group = new NioEventLoopGroup();
    private volatile SocketChannel socketChannel = null;

    public static void main(String[] args) throws InterruptedException {
        NettyTcpClient client = new NettyTcpClient();
        client.connect("127.0.0.1", 6666);
        client.send("hello");
        Thread.sleep(2000);
        client.close();
    }

    public void connect(String ip, int port) {
        Bootstrap bootstrap = new Bootstrap();
        bootstrap.group(group)
                .channel(NioSocketChannel.class)
                .remoteAddress(ip, port)
                .option(ChannelOption.SO_KEEPALIVE, true)
                .option(ChannelOption.TCP_NODELAY, true)
                .handler(new ChannelInitializer<SocketChannel>() {
                    @Override
                    protected void initChannel(SocketChannel socketChannel) throws Exception {
                        socketChannel.pipeline().addLast(new ChannelInboundHandlerAdapter() {
                            @Override
                            public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
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
            channelFuture = bootstrap.connect().sync();
            channelFuture.addListener(new ChannelFutureListener() {
                @Override
                public void operationComplete(ChannelFuture channelFuture) throws Exception {
                    System.out.println("Tcp connect to " + ip + ":" + port + ", result: " + channelFuture.isSuccess());
                }
            });
            socketChannel = (SocketChannel) channelFuture.channel();
        } catch (Exception e) {
            e.printStackTrace();
            group.shutdownGracefully();
        }
    }

    public void send(String msg) {
        if (socketChannel == null || !socketChannel.isActive()) {
            System.out.println("The client do Not connect to server...");
            return;
        }

        try {
            ChannelFuture future = socketChannel.writeAndFlush(Unpooled.wrappedBuffer(msg.getBytes(StandardCharsets.UTF_8))).sync();
            future.addListener(new ChannelFutureListener() {
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
        if (socketChannel != null) {
            socketChannel.disconnect();
            socketChannel.close().sync();
        }
        group.shutdownGracefully();
    }
}
```





### 参考资料

- 传输控制协议 - 维基百科: <https://zh.wikipedia.org/wiki/%E4%BC%A0%E8%BE%93%E6%8E%A7%E5%88%B6%E5%8D%8F%E8%AE%AE> 



### 总结

