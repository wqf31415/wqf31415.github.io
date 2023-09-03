---
title: 认识 GraphQL
tags:
  - GraphQL
  - api
categories:
  - 技术
date: 2020-05-17 15:08:29
---

### 概述

<span style="background:#ffa;font-weight:bold">GraphQL 是</span> FaceBook 开发并开源的<span style="background:#ffa;font-weight:bold">一种</span>针对 Graph（图状数据）查询设计的<span style="background:#ffa;font-weight:bold">查询语言</span>（Query Language），旨在提供 RESTful 架构体系的替代方案，其优势是查询图状数据。值得注意的是 GraphQL 没有和任何特定数据库或存储引擎绑定，本身更不是一种数据库。这篇文章介绍了 Graph QL 的概念以及应用场景。



### 什么是 GraphQL

![](https://blog-images.qiniu.wqf31415.xyz/graphql.png)

> 官网：<https://graphql.cn/> 

> GraphQL 是一种用于 API 的查询语言，也是一个满足你数据查询的运行时。 GraphQL 对你的 API 中的数据提供了一套易于理解的完整描述，使得客户端能够准确地获得它需要的数据，而且没有任何冗余，也让 API 更容易地随着时间推移而演进，还能用于构建强大的开发者工具。

<iframe height="415" width="544"  src="//player.bilibili.com/player.html?aid=92129366&bvid=BV1F7411N7UL&cid=157308905&page=1" scrolling="no" border="0" frameborder="no" framespacing="0" allowfullscreen="true"> </iframe>
<!-- more -->

### 类似技术

通过类似技术来理解 GraphQL。

#### RESTful API

RESTful api 是当前流行的一种接口设计风格和开发方式，通过 URI 实现对资源的管理及访问，具有扩展性强、结构清晰的特点。在 RESTful 接口设计中，是以资源为单位管理，为每一类资源要提供特有的请求接口，并通过不同的请求方法来决定对资源的具体操作，如查询资源使用 GET 方法，修改使用 PUT 方法等。

GraphQL 也用于接口设计，与 REST 暴露一组接口相比，GraphQL 只需要对外暴露一个接口，请求的内容可以由客户端自己定义。而在 GraphQL 中一般只需要使用 GET 和 POST 请求方法，用来完成对数据的增删改查。



#### SQL

SQL，结构化查询语言（Structured Query Language），是一种用于数据库查询的程序设计语言，用来存储、查询、更新和管理关系型数据库系统。

GraphQL 也是一种查询语言，跟 SQL 一样，也可以用来查询、更改数据，也有自己的语言格式定义与数据类型定义。但跟 SQL 不同的是，SQL 一般用于关系型数据库的操作，GraphQL 与具体数据库没有关联，没有绑定具体使用的数据库。另外，GraphQL 还可以用来设计接口，而 SQL 一般只能用于底层的数据操作，而不会当作接口直接暴露出来。



#### APIJSON

> 项目地址：<https://gitee.com/TommyLemon/APIJSON> 

APIJSON是一种专为API而生的 JSON 网络传输协议以及基于这套协议实现的ORM库。
为简单的增删改查、复杂的查询、简单的事务操作 提供了完全自动化的API。
能大幅降低开发和沟通成本，简化开发流程，缩短开发周期。
适合中小型前后端分离的项目，尤其是互联网创业项目和企业自用项目。



### GraphQL 使用

GraphQL 主要作用于数据接口，如前后端交互，客户端能够自由获取服务端事先定义好的数据，提高了交互接口的灵活性。所以使用 GraphQL 的第一步是服务端定义数据 schema。

> 学习文档：<https://graphql.cn/learn/> 
>
> 语法说明：<https://spec.graphql.cn/> 

示例：查询 id 为 4 的用户的名字：

```
{
  user(id:4){
    name
  }
}
```

查询结果：

```json
{
  "user": {
    "name": "xxx"
  }
}
```



#### java 代码示例

使用 maven 创建项目，引入 graphql-java 依赖。

```xml
<dependency>
    <groupId>com.graphql-java</groupId>
    <artifactId>graphql-java</artifactId>
    <version>14.0</version>
</dependency>
```

示例代码：

```java
public static void main(String[] args) {
    String schema = "type Query{hello: String} schema{query: Query}";

    SchemaParser schemaParser = new SchemaParser();
    TypeDefinitionRegistry typeDefinitionRegistry = schemaParser.parse(schema);

    RuntimeWiring runtimeWiring = RuntimeWiring.newRuntimeWiring()
        .type("Query", builder -> builder.dataFetcher("hello", new StaticDataFetcher("world")))
        .build();

    SchemaGenerator schemaGenerator = new SchemaGenerator();
    GraphQLSchema graphQLSchema = schemaGenerator.makeExecutableSchema(typeDefinitionRegistry, runtimeWiring);

    GraphQL build = GraphQL.newGraphQL(graphQLSchema).build();
    ExecutionResult executionResult = build.execute("{hello}");

    System.out.println(executionResult.getData().toString());
    // Prints: {hello=world}
}
```



### GraphQL 优势

定义了一套类型系统（Type System）用来描述你的数据。

- **强类型**：使用的是强类型，与 C 、JAVA 等强类型后端语言相得益彰，服务端能够都响应的类型做出一定的保证，而 RESTful 是弱类型的，缺少机器可读的元数据。
- 分工：GraphQL 让服务端定义好支持哪些 Queries，把对数据的 Query 需求下放到客户端管理，分工明确的同时保持对 API 的聚焦。
- 分层：GraphQL 的 Query 本身是一组分层的字段，查询就像返回的数据一样，是一种产品描述数据和需求的自然方式。
- 预测性：GraphQL 的查询只返回客户端要求的内容，没有任何冗余，而且它只有一个接口地址，由此衍生了零一特性——兼容性。
- **兼容性**：由于需求变动带来的新增字段不影响老客户端，服务端再也不需要版本号了，极大的简化了兼容问题。
- **自检性**：GraphQL 在执行查询前（即在开发时）提供描述性错误信息，在给定查询的情况下，工具可以确保其句法是正确有效的，使得构建高质量客户端变得更加容易。
- Doc & Mock：GraphQL 的文档永远和代码同步，开发无需维护散落多处的文档，调用者也无需担心过期问题，而且基于类型系统的强力支撑和 graphql-tools，mocking 会变得无比容易。



### GraphQL 的劣势

- FaceBook 公司没有开放 GraphQL 的后端设计，所以使用的只能是第三方的或自己开发，体验也就没有 FackBook 官方的那么好。

- GraphQL 是针对图状数据设计的，所以数据需要以图的数据结构进行存储才有优势。

- GraphQL 尽管查询的数据是图状数据结构，但实际获得的数据视图是树状数据结构。GraphQL 查询或更新都有自己的根节点，所有数据都是从根节点展开出去的。查询得到的结果如果要在前端变回图的状态，前端不能简单的缓存查询得到的数据，必须对用的 GraphQL 存储库，然后通过顶点的ID 把不同节点之间某些边重新连接起来。



### 相关技术

#### ApolloGraphQL

> Apollo GraphQL: <https://www.apollographql.com/> 

Apollo 是一个平台，用于构建数据图并作为前后端之间的连接层，让你可以轻松使用 GraphQL。

![](https://blog-images.qiniu.wqf31415.xyz/apollo_data_graph.png)

#### Graphcool

> 官网：<https://www.graph.cool/> 

Graphcool 是一个使用 GraphQL 的后端框架。但这个项目将在 2020年 7月 1日下线，官方推荐切换到 Prisma。



#### Prisma

> Prisma: <https://www.prisma.io/> 

Prisma 是一个开源数据库工具，用来替换传统 ORM 框架，使 TypeScript 和 Node.js 更容易访问数据库。



### 总结

GraphQL 是一种新的 api 设计思路，让接口使用更加灵活，没有数据冗余，尤其适合开源平台（如 GitHub），第三方在开发时会更加方便。但它也存在一些问题，如后端实现需要寻找第三方工具或自行开发。GraphQL 虽然很方便，但对于一些简单的数据结构和接口，实际使用 RESTful Api 就可以了，在实际使用的时候需要仔细斟酌。