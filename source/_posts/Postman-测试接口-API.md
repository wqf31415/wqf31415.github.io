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

![](https://blog-images.qiniu.wqf31415.xyz/postman.png "postman")

<!-- more -->

### 其他测试工具
- SoapUI
  [SoapUI](https://www.soapui.org) 号称世界上最高级的 REST 和 SOAP 接口自动化测试工具。用于接口功能测试、性能测试、权限测试、API Mock 测试、数据驱动测试与生成测试报表。

- Katalon Studio
  [Katalon Studio](https://www.katalon.com/) 是一个免费、健壮、跨平台的测试工具，高度可定制的自动化测试，用于 Web 和移动 app 测试。

- Jmeter
  [Jmeter](http://jmeter.apache.org) 是 Apache 软件基金会下的一款开源软件测试工具，使用 java 语言开发，用来测试软件应用的功能和性能，可以用来做压力测试。最初用于测试 Web 软件，后来扩展到其他测试领域。

### 基础操作

#### API 请求

打开 Postman ，进入软件界面后，按 <kbd>Ctrl</kbd> + <kbd>T</kbd> 新建一个请求 Tab，选择 GET 方法，在地址栏中填入要请求的 api 地址，如：`postman-echo.com/get` ，点击 Send 按钮即可发送请求，请求成功后在下面的 Response 区域将显示请求结果，请求结果可以格式化显示。

![](https://blog-images.qiniu.wqf31415.xyz/postman_get_request.png "postman request")



#### 设置请求方法

在请求地址栏左边可以设置请求方法，默认可选的请求方法有：

GET、POST、PUT、PATCH、DELETE、COPY、HEAD、OPTIONS、LINK、UNLINK、PURGE、LOCK、UNLOCK、PROPFIND、VIEW。

也可以自定义请求方法，只需要在方法框中输入方法名，按回车确认。



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
  
- **Cookies** 

  管理请求中的 cookles 。



#### 保存请求

我们可以把接口测试请求保存下来，下次继续使用，只需点击 **Save** 按钮(快捷键 <kbd>Ctrl</kbd> + <kbd>S</kbd>) 即会弹出保存窗口，填入请求名称、描述，并选择或创建接口集后即可保存请求。

![](https://blog-images.qiniu.wqf31415.xyz/postman_save_request.png "save request")



#### 请求错误排查

Postman 控制台中会输出请求的详细信息，帮助用户排除请求的错误信息，点击 Postman 界面下发的 **Postman Console** 按钮(快捷键 <kbd>Ctrl</kbd> + <kbd>Alt</kbd> + <kbd>C</kbd>) 即可打开控制台界面。

![](https://blog-images.qiniu.wqf31415.xyz/postman_console.png "Postman Console")



### 进阶操作

#### 环境与变量

在测试接口过程中，在开发环境和生产环境中的请求地址、端口等参数可能有差异，Postman 中可以为每个测试环境创建一个环境变量集合，方便在不同环境下进行测试。

- **添加环境** 

  > 环境管理快捷键：<kbd>Ctrl</kbd> + <kbd>Alt</kbd> + <kbd>E</kbd>

  在 Postm 界面中点击 **New** 按钮，点击 **Environment** 选项即可进入添加环境的界面，填入环境名称以及变量信息后，点击 **Add** 按钮添加环境。如下图添加了名为 `local_test` 的环境，同理还可以添加 `prod_test` 的环境。

  ![](https://blog-images.qiniu.wqf31415.xyz/postman_env_add.png "add environment")

  

- **使用环境**

  添加环境后，在请求中就可以使用环境中添加的变量，在测试时根据需要随时切换环境。

  ![](https://blog-images.qiniu.wqf31415.xyz/postman_use_environment.png "use environment")

  

#### 生成请求代码

Postman 中可以一键将请求导出成请求代码，点击界面中的 **Code** 按钮，选择代码类型，即可生成相应的请求代码，点击 **Copy to Clipboard** 按钮将代码复制到剪贴板。

![](https://blog-images.qiniu.wqf31415.xyz/postman_code_btm.png "postman code button")



#### 接口集

在 Postman 中可以创建接口集，统一管理一类接口请求，在接口集中还可以创建文件夹来分类保存接口。此外，在 Postman 中，接口集能以 json 文件形式导出、导入，分享或与团队成员协同编辑，对接口集中的请求进行评论，还可以打分支、分支合并等

点击 `File` 菜单中的 `New...` 选项(快捷键 <kbd>Ctrl</kbd> + <kbd>N</kbd>)，或点击界面左上角的 `New` 按钮，然后点击选择 `Collection` ，在新建接口集的窗口中，可以设置接口集名称、描述(支持 markdown 语法)，还可以添加统一的权限，设置请求前执行的脚本和请求后的测试，添加变量。

此外，在保存请求的时候将会提示选择或创建接口集。

![](https://blog-images.qiniu.wqf31415.xyz/postman_create_collection.png)

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

![](https://blog-images.qiniu.wqf31415.xyz/postman_api_doc.png)



#### 发布

Postman 允许用户将自己的接口集发布到官方的 [API Network](https://www.getpostman.com/api-network/) ，分享给全世界。

注册 Postman 账号并登陆后，点击接口集管理功能里的 **Publish Docs** 按钮，在跳转的发布页面中，根据需要添加相应的配置，即可完成发布。

可以给发布的接口集添加自定义的 Logo，如果是专业版或企业版用户还可以自定义访问域名。

> 注意：发布的接口文档访问次数是有限制的，普通用户每月提供 1000 次访问量，[查看用户当前已使用的访问量](https://go.pstmn.io/postman-account-limits) 。

例如: <https://documenter.getpostman.com/view/7042523/S1a1aosZ>

![](https://blog-images.qiniu.wqf31415.xyz/postman_publish_collection.png "publish")



### 高级操作

#### 脚本

Postman 中包含了一个强有力的 Node 运行时环境，可以给请求或接口集添加动态行为。使用 JavaScript 语言编写脚本，postman 提供了一些内置对象。这样就可以编写测试套件、设置动态参数等等。在请求发起前(Pre-request script)和收到返回结果后(test script)，都可以添加执行脚本，完成功能测试，执行顺序是： `Pre-request` -> `request` ->  `response` -> `test`。

可以在请求(request)、文件夹(folder)、接口集(collection) 中添加脚本，请求前脚本执行顺序是： 

collection 中的 -> folder 中的 -> request 中的

测试脚本执行顺序与预请求脚本执行顺序相同，如下图所示:

![](https://blog-images.qiniu.wqf31415.xyz/postman_script_execOrder.png "script exec order")

- **请求前脚本** 

  可以在请求前脚本中动态生成数据，当作请求的数据使用，如生成时间戳并设置为环境变量 `my_time` ，在请求中使用 `{{my_time}}` 引用：

  ```javascript
  pm.environment.set("my_time", new Date());
  ```

  在 Postman 界面上有一些快捷按钮帮助生成代码片段：

  ![](https://blog-images.qiniu.wqf31415.xyz/postman_add_pre_request_script.png)

  也可以在利用脚本在每个请求头中添加数据，如在请求头中添加 `Cookie` 和 `X-CSRF-TOKEN` 数据以通过权限验证，具体的 `Cookie` 和 `X-CSRF-TOKEN` 值可以在变量中设定，如 `myCookie` 和 `myX-CSRF-TOKEN` ，这样每次测试时，只需要修改变量中的值即可完成集合中每个请求的权限验证。脚本如下：

  ```javascript
  pm.request.headers.add({key: 'Cookie', value: pm.variables.get("myCookie")});
  pm.request.headers.add({key: 'X-CSRF-TOKEN', value: pm.variables.get("myX-CSRF-TOKEN")});
  ```

  

- **测试脚本**

  在结果执行完成后，添加脚本类检验请求结果是否正确。如判断请求状态码是否是 `200` ：

  ```javas
  pm.test("Status code is 200", function () {
      pm.response.to.have.status(200);
  });
  ```

  ![](https://blog-images.qiniu.wqf31415.xyz/postman_test_script.png)

  还可以验证返回结果中的内容是否正确，如判断返回结果的 json 中的 `found` 值是否为 `true` ：

  ```javascript
  pm.test("Found is true", function () {
      var jsonData = pm.response.json();
      pm.expect(jsonData.found).to.eql(true);
  });
  ```

  

#### 监控(在线自动化测试)

Postman 中可以设置监控器来定时执行 API 请求，用来测试接口性能和验证结果。比如设置每 5 分钟发起一次请求来测试接口是否正常启用。如果你给请求定义了测试脚本，那么监控定时指定请求时也会执行脚本来验证请求结果是否正确，如果请求发生错误将会通知用户。

每个 Postman 普通用户每个月有 1000 条免费监控调用次数，Pro 团队用户 10000次/月，企业用户 100 000 次/月，更多信息参考 [官方网站](https://learning.getpostman.com/docs/postman/monitors/pricing_monitors/) 。

- **创建监控器** 

  通过 Postman 侧边栏、New 按钮、启动页面、网页版添加监控器，如：

  ![](https://blog-images.qiniu.wqf31415.xyz/postman_add_monitor.png "add monitor")

- **设置监控器参数** 

  Postman 监控器中可设置的参数有：

  - **监控器名称** 便于区分不同的监控器。
  - **版本标签** 选择测试使用的接口集版本。如果接口集没有关联到 API，就只能选择当前版本(CURRENT)。
  - **环境** 选择测试使用的环境变量集合。
  - **运行频率** 监控执行的频率，按运行频率由高到低，可以选择周定时器、小时定时器、分钟定时器。
  - **地区** 设置监控器执行请求计划的时区。

- **运行监控器** 

  设置好监控器参数后，点击 **Create** 按钮完成监控器创建，登陆到 Postman 网页控制台，在控制台中找到对应的接口集与监控器，点击运行。这样我们的定时测试监控器就可以在 Postman 云上开始工作了，定时执行请求。

- **查看监控器运行结果**

  登陆 Postman 网页控制台，找到接口集并进入监控器页面，即可看到添加的监控器，点击监控器名称进入结果展示页面。如：

  ![](https://blog-images.qiniu.wqf31415.xyz/postman_monitor_result.png "monitor result")

  

#### 模拟服务器

在接口服务器未开发完成时，我们可以通过 Postman 创建 mock 服务器进行接口测试。

- **创建 mock 服务器** 

  - 在 Postman 中可以使用 **New** 按钮、开始页面、Postman app、Postman API 创建模拟服务器。在这里我们通过点击 **New** 按钮，然后点击 **Mock Server** 选项来创建。

    ![](https://blog-images.qiniu.wqf31415.xyz/postman_create_mock_server_0.png "create mock server")

  

  - 创建 mock 服务器时可以选择已有的接口集，也可以自己填入新的接口，我们在这里添加了一个 `/hello` 的接口，返回结果是一个 json ，点击 **Next** 进入配置页面。

    ![](https://blog-images.qiniu.wqf31415.xyz/postman_create_mock_server.png "create mock server")

    

  - 在配置页面填入服务器名称，选择运行环境，根据需要选择是否将服务器设置为私有，设置好后点击 **Create** 完成 mock 服务器的创建。

    > 注意：如果创建 Mock 服务器时选择了环境，创建成功后，选择的环境被删除时，该 Mock 服务器也将失效。

    ![](https://blog-images.qiniu.wqf31415.xyz/postman_create_mock_server_2.png "create mock server")

    

  - 创建完成后，将自动添加一个接口集和一个环境，名称都是 mock 服务器的名称，这里是 `HelloMoceServer`。

    ![](https://blog-images.qiniu.wqf31415.xyz/postman_create_mock_server_3.png "create mock server")

    

  - 测试，进入接口集 `HelloMoceServer` ，选择刚才添加的 `/hello` 接口请求，设定环境为 `HelloMoceServer` ，发送请求，返回结果为我们设定的返回值。

    ![](https://blog-images.qiniu.wqf31415.xyz/postman_create_mock_server_4.png "test mock server")
  
    
  
- 根据接口集中的请求样例(example)创建 Mock 服务器

  在创建 Mock 服务器时，可以直接选择接口集，按接口集创建。选择这种方式时需要提前给 mock 的请求添加样例，有两种添加 example 的方式：

  - 将实际请求结果保存为 example

    当接口服务器已经可以使用的，可以先发送请求，收到返回结果后，点击返回结果区域中的 **Save** 按钮，即可跳转到保存为 example 的界面，根据需要修改名称等信息，保存即可。

    ![](https://blog-images.qiniu.wqf31415.xyz/postman_create_example_by_request.png)

    

  - 给请求添加虚拟的 example

    当服务器后台还未开发完成时，可以添加一些模拟的请求与结果样例，完成模拟测试。点击请求区域右上方的 **Examples** 按钮，将跳转的添加界面，填入名称、请求方法、请求参数、返回结果码、返回结果内容后，保存。可以给一个接口添加多个不同请求方法、不同参数、不同返回结果的请求样例，增加测试的多样性。

    ![](https://blog-images.qiniu.wqf31415.xyz/postman_create_example.png)

    

#### API 设计与开发

Postman 新特性允许用户直接通过 Postman 设计 API，增加了 API 栏和 API 元素，与接口集、监控器等一样可以使用 Postman 中的版本控制，可以设置版本标签，也可以快捷的分享给团队成员。

点击 Postman 界面上侧边栏选项卡中的 **APIs** ，然后点击 **+ New API** 按钮，填入 API 名称即可创建。

![](https://blog-images.qiniu.wqf31415.xyz/postman_create_API.png)



创建 API 后，需要添加定义，点击 API 显示区域中的 **Add Schema** 下拉选框，选择 **Create new** ，当然如果你有写好的定义文件，也可以从文件导入。

![](https://blog-images.qiniu.wqf31415.xyz/postman_create_API_2.png)



接下来，选择接口框架类型，可选项有：OpenAPI 3.0 ，OpenAPI 2.0 ，OpenAPI 1.0 ，RAML 0.8 ，GraphQL。然后将接口定义写好，点击 **Save** 保存。

随后，可以开发一个 API，对 API 进行测试，给 API 添加监控器自动运行测试，分析 API。



### 参考资料

- [Postman Docs](https://learning.getpostman.com/docs/postman/launching_postman/installation_and_updates/)



### 小结

这篇文章介绍了 Postman 的用法，包括基本的接口测试与云自动测试等功能，也涉及到了 Postman 的一些新特性介绍，但并没有十分深入每个特性，只是走马观花的通篇浏览。写这篇文章的主要目的是为了了解 Postman 这个工具的功能和使用场景，知道它能做什么，以便在以后做测试的时候多一个选择。

文章最后时间：2019-06-22 。