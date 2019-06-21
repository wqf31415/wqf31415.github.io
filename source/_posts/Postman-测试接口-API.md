---
title: Postman 测试接口 API
date: 2019-06-14 11:02:25
tags:
- api
- test
- postman
categories:
- 工具
---

### 概述
这篇文章主要在讲述使用 Postman 工具测试 api 接口的操作，从最基础的发送一个 get 请求到自动接口测试，还包含一些 postman 的使用技巧。

### Postman 是什么？
[Postman](https://www.getpostman.com/) 是一个强大且好用的接口测试工具。早期是 Chrome 浏览器的一个插件，后续插件版不再维护，开发成了一个桌面测试工具。
现在， Postman 被设计成 API 开发工具，不仅包含了接口测试功能，还添加了一些接口设计、自动化测试、模拟接口服务、监控、文档生成以及接口发布功能，最新版本的 Postman 还支持团队协作开发使用。
Postman 提供企业版，提供了更加强大的测试功能。

![](http://blog-images.qiniu.wqf31415.xyz/postman.png "postman")

<!-- more -->

### 其他测试工具
- SoapUI
  [SoapUI](https://www.soapui.org) 号称世界上最高级的 REST 和 SOAP 接、口自动化测试工具。用于接口功能测试、性能测试、权限测试、API Mock 测试、数据驱动测试与生成测试报表。

- Katalon Studio
  [Katalon Studio](https://www.katalon.com/) 是一个免费、健壮、跨平台的测试工具，高度可定制的自动化测试，用于 Web 和移动 app 测试。

- Jmeter
  [Jmeter](http://jmeter.apache.org) 是 Apache 软件基金会下的一款开源软件测试工具，使用 java 语言开发，用来测试软件应用的功能和性能，可以用来做压力测试。最初用于测试 Web 软件，后来扩展到其他测试领域。

### 基础操作

#### API 请求

打开 Postman ，进入软件界面后，按 <kbd>Ctrl</kbd> + <kbd>T</kbd> 新建一个请求 Tab，选择 GET 方法，在地址栏中填入要请求的 api 地址，如：`postman-echo.com/get` ，点击 Send 按钮即可发送请求，请求成功后在下面的 Response 区域将显示请求结果。

![](http://blog-images.qiniu.wqf31415.xyz/postman_get_request.png)



#### 设置请求方法

在请求地址栏左边可以设置请求方法，默认可选的请求方法有：

GET、POST、PUT、PATCH、DELETE、COPY、HEAD、OPTIONS、LINK、UNLINK、PURGE、LOCK、UNLOCK、PROPFIND、VIEW。

也可以自己输入请求方法，按回车保存。



#### 设置请求参数

在接口请求界面中，在地址栏下发的选项卡中可以给请求设置参数。

- **参数(Params)** 

  添加请求参数，分别在 **KEY** 、 **VALUE** 、 **DESCRIPTION** 中填入所需参数的名称、值和描述信息，描述信息可以不写。可以勾选需要使用的参数。

- **权限(Authorization)** 

  设置接口请求所需的权限信息，支持多种权限类型。

- **请求头(Headers)** 

  设置 http 请求头，有时一些权限验证信息需要放到请求头中。

- **请求体(Body)** 

  很多时候我们将请求中的数据放到请求体中。请求体有多种类型可供选择，如 from-data、x-www-urlencoded、raw、binary、GraphQL。

  当选择 raw 类型时，还可以指定请求体数据类型，包括 Text、Text(text/plain)、Json(application/json)、javascript(application/javascript)、XML(application/xml)、XML(xml)、HTML(text/html)。

  选择 binary 可以上传文件。

- **预请求脚本(Pre-request Script)** 

  请求发起前执行的脚本。

- **测试(Tests)** 

  请求完成后运行的测试脚本。



#### 保存请求

我们可以把接口测试请求保存下来，下次继续使用，只需点击 **Save** 按钮(快捷键 <kbd>Ctrl</kbd> + <kbd>S</kbd>) 即会弹出保存窗口，填入请求名称、描述，并选择或创建接口集后即可保存请求。

![](http://blog-images.qiniu.wqf31415.xyz/postman_save_request.png)

### 进阶操作

#### 接口集

在 Postman 中可以创建接口集，用来分类保存接口。

点击 `File` 菜单中的 `New...` 选项(快捷键 <kbd>Ctrl</kbd> + <kbd>N</kbd>)，或点击界面左上角的 `New` 按钮，然后点击选择 `Collection` ，在新建接口集的窗口中，可以设置接口集名称、描述(支持 markdown 语法)，还可以添加统一的权限，设置请求前执行的脚本和请求后的测试，添加变量。

此外，在保存请求的时候将会提示选择或创建接口集。

![](http://blog-images.qiniu.wqf31415.xyz/postman_create_collection.png)

创建了接口集后，即可将请求保存的接口集中，在接口集中将会保存接口完整的请求信息，包括 url、参数、脚本等。

- **描述(Description)** 

  建议在接口集描述框中清晰的说明该集合中接口的使用说明、注意事项等，方便生成接口描述文档。

- **权限(Authorization)** 

  Postman 提供多种权限验证机制，如 API Key、OAuth 1.0、OAuth 2.0 等。设置后，集合中每个请求都会使用这个权限验证方式，可以在请求中单独设置来覆盖默认权限。

- **预请求脚本(Pre-request Scripts)** 

  在集合中每个请求发起前都会执行的脚本。

- **测试(Tests)** 

  集合中每个请求完成后都会执行的脚本。

- **变量(Variables)** 

  添加在集合中可用的变量，比如设置所有接口使用的基本请求地址，如设置 baseUrl 为 `http://127.0.0.1:8080` ，在当前集合中的请求中就可以使用 `{{baseUrl}}` 来代替了，如需修改请求地址就直接修改集合变量中的值，不用修改每个请求了。

#### 接口文档

使用 Postman 可以方便的将接口集、请求描述生成接口文档。点击接口集旁边的按钮即可显示接口集中的描述信息，点击 **View in web** 还可以生成网页版，**在网页版中不仅包含了基本描述信息，还可以生成请求示例代码**，如生成请求对应的 cURL 请求命令，生成 jQuery 请求代码，生成 Ruby、Python Requests、Node、PHP、Go 请求代码。

![](http://blog-images.qiniu.wqf31415.xyz/postman_api_doc.png)

#### 发布

### 高级操作

#### 监控

#### 自动化测试

#### API 设计与 MOCK

#### DEBUG

### 小结

