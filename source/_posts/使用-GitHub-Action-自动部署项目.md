---
title: 使用 GitHub Action 自动部署项目
tags:
  - github
  - ci
  - 持续集成
  - 工具
categories:
  - 工具
date: 2020-08-27 08:56:53
---

### 概述

这篇文章简单的介绍了使用 GitHub 的 Action 工具自动部署项目。



### 什么是 GitHub Action

Action 是 GitHub 提供了的持续集成工具，可以自动对 GitHub 仓库上构建、测试、封装、发行或部署项目。提供了自定义自动化软件设计开发工作流的功能，还可以发现、创建和共享操作，并可以将操作合并到完全自定义的工作流程中。

<!-- more -->



### 体验

#### 配置工作流程

创建仓库 `test` ，在 `.github/workflows` 目录下创建工作流配置文件，使用 `.yml` 或 `.yaml` 文件编辑工作流配置。如 `myAction.yml` ：

```yml
name: my-action # 名称
on:
  push:
    branches: [ master ] # 当推送代码到 master 时触发任务

jobs: # 任务
  build: # 定义一个 id 为 build 的任务项
    runs-on: ubuntu-latest # 运行平台
    steps: # 任务步骤
      - uses: actions/checkout@v2 # 使用官方提供的操作
      - name: Run a one-line script # 自定义任务名
        run: echo Hello, world! # 自定义任务命令，打印 Hello, world!
      - name: Run a multi-line script
        run: |
          echo Add other action to build,
          echo test, and deploy your project.
```

> 上述配置了名为 `my-action` 的Action，将在推送代码到 `master` 分支时触发工作任务，任务执行平台为最新的 Ubuntu 平台

#### 提交代码查看效果

提交代码到 `test` 仓库的 `master` 分支，点击 `Actions` 标签，将展示工作执行结果：

![](https://blog-images.qiniu.wqf31415.xyz/github_action_1.png)

点击下方的记录，查看详情：

![](https://blog-images.qiniu.wqf31415.xyz/github_action_2.png)

点击 `build` 查看构建的日志详情：

![](https://blog-images.qiniu.wqf31415.xyz/github_action_3.png)

查看输出的日志，可以看到我们在配置文件中定义的任务都被正确执行了。



### 工作流程配置

GitHub Action 的工作流配置都是以 yaml 文件配置，都需要放到项目仓库下的 `.github/workflows` 目录下。

#### 任务名称 name

配置文件中以 `name` 项配置工作流程的名称，将在仓库操作页面展示该名称。如果省略 `name` 将设置为相对于仓库根目录的工作流程文件路径。



#### 触发条件 on

`on` 项配置工作流触发事件，值可以是单一事件、事件数组、事件类型数组或事件配置 map。

##### 任意推送代码到任意分支时触发

```yml
on: push
```

##### 在 push 或 pull 时触发

```yaml
on: [push, pull_request]
```

##### 推送到指定分支时触发

```yaml
on: 
  push: 
    branches: [master]
```

##### 定时触发

定时触发的最小间隔是 5 分钟。如下为每 30 分钟触发一次：

```yaml
on:
  schedule:
    - cron: '*/30 * * * *'
```



#### 环境变量 env

`env` 项目用于配置环境变量，可用于工作流中所有作业和步骤，还可以设置为仅适用于作业或步骤的环境变量。如：

```yaml
env:
  SERVER: production
```



#### 默认设置 defaults

将应用到工作流程中所有作业的默认设置，如果有多个默认设置时，以最近的为准。



#### 工作任务 jobs

`jobs` 用于定义一项或多项作业，作业默认是并行运行，可以在作业配置中 `need` 项中指定依赖的作业项。

每项作业有必须关联一个唯一的 ID，ID 为字符串，必须以字母或下划线开头，只能包含字母、数字、下划线 `_` 或横杠 `-` ，如：

```yaml
jobs:
  my_job_1: # 作业ID
    name: my first job
  _other-job:
    name: other job
```



##### 工作任务中的配置项

工作任务中的配置项是定义在 `jobs.<job_id>` 下的配置项。

###### `runs-on` 

指定运行的环境，取值：

| 值                                 | 虚拟环境             |
| ---------------------------------- | -------------------- |
| `windows-latest` 或 `windows-2019` | Windows Server 2019  |
| `ubuntu-20.04`                     | Ubuntu 20.04         |
| `ubuntu-latest` 或 `ubuntu-18.04`  | Ubuntu 18.04         |
| `ubuntu-16.04`                     | Ubuntu 16.04         |
| `macos-latest` 或 `macos-10.15`    | macOS Catalina 10.15 |



###### `name` 

指定任务名称，在查看执行日志时显示

###### `need` 

指定当前任务之前必须完成的作业，可以是一个任务ID或任务ID数组，如：

```yaml
jobs:
  job1:
  job2:
    need: job1
  job3:
    need: [job1,job2]
```

###### `outputs` 

定义此作业的输出内容，供下游作业使用。如：

```yaml
jobs:
  job1:
    runs-on: ubuntu-latest
    outputs:
      output1: ${{steps.step1.test}}
      output2: ${{steps.step2.test}}
    steps:
      - id: step1
        run: echo "::set-output name=test::hello"
      - id: step2
        run: echo "::set-output name=test::world"
  job2:
    runs-on: ubuntu-latest
    needs: job1
    steps:
      - run: echo ${{needs.job1.outputs.output1}} ${{needs.job1.outputs.output2}}
```

###### `if` 

指定作业运行的条件，只有满足条件才会执行。如：

```yaml
jobs:
  job1:
    runs-on: ubuntu-latest
    if: ${{github.event_name == 'pull_request' && github.event.action == 'unassigned' }}
    steps:
      run: echo xxxxx
    
```



###### `steps` 

定义一系列任务步骤，步骤将顺序执行，如果一个失败随后的任务将不执行。在步骤中可以运行命令、运行设置任务，或者运行个人仓库、公共仓库中的操作或 Docker 注册中发布的操作。

```yml
jobs:
  my-job:
    name: my job
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2 # 使用官方提供的检出仓库操作
      - name: Print hello
        env: 
          MY_NAME: Jack
        run: |
          echo hello $MY_NAME
```

> steps 中一些常用配置项：
>
> - `uses` ：使用自定义或 github 社区提供的操作
>
> - `uses.with` ：为使用的操作添加附加条件
>
> - `id` ：步骤的 ID ，方便引用
>
> - `name` ：为步骤命名
>
> - `run` ：运行命令，如果是多条命令使用 `|` 符号标识，如：
>
>   ```yml
>   - name: Run a one-line script # 自定义任务名
>     run: echo Hello, world! # 自定义任务命令，打印 Hello, world!
>   - name: Run a multi-line script
>     run: |
>       echo Add other action to build,
>       echo test, and deploy your project.
>   ```



###### `timeout-minutes` 

指定超时时间，默认值为 360 分钟。



#### 使用密码

在构建与部署过程中，我们可能需要用的一些加密信息，这时我们需要在仓库设置中添加加密信息，需要输入名称和值。

![](https://blog-images.qiniu.wqf31415.xyz/github_repo_add_secret.png)

在使用密码时，可以作为输入参数或者环境变量，如使用名为 `MY_PWD` 的加密信息：

```yml
steps:
  - name use secrets
    with:
      my_pwd: ${{secrets.MY_PWD}}
    env:
      my_pwd: ${{secrets.MY_PWD}}
    run: |
      example-command "$my_pwd"
```



#### 使用预置的操作

操作是一系列特定作业步骤的组合，可以完成特定的任务，可以创建自己的操作，也可以使用 github 社区分享的操作。比如使用官方的检出仓库的操作：

```yaml
- uses: action/checkout@2 # action 为作者，这里是github官方，checkout 是操作名，@2 是指定操作版本为 2
```

> 参考：<https://github.com/marketplace/actions/checkout> 

当在线编辑 action 工作流配置文件时，在编辑页面右侧的 Marketplace 选项卡中可以检索社区分享的操作，点击后可查看操作的介绍。

![](https://blog-images.qiniu.wqf31415.xyz/github_edit_action_conf_marketplace.png)



更多的操作可以到 github marketplace 中的 action 类别中查找：<https://github.com/marketplace?type=actions> 



### 实战

> 背景：项目是一个 hexo 博客，在 github 仓库中 `source` 分支存储模块资源与配置信息。现在需要每次提交代码到 source 分支时触发工作流，完成博客自动编译，编译前需要下载博客主题并替换配置文件，编译完成后将项目打包，通过 sftp 上传到服务器。

配置详情：

```yml
# 名称
name: Deploy to my server

# 当提交代码到 source 分支时触发工作流
on:
  push:
    branch: [source]
    
jobs:
  build:
    runs-on: ubuntu-latest # 使用Ubuntu 18.04 运行
    name: Job to deploy blog
    steps:
      # 检出项目source分支代码
      - name: Checkout
        id: checkout
        uses: actions/checkout@v2
        with:
          ref: source
      # 设置使用 node 12
      - name: use node
        uses: actions/setup-node@v1
        with:
          node-version: '12'
      # 安装 hexo-cli 工具，用于编译项目
      - name: install hexo-cli
        run: npm install hexo-cli -g
      # 安装项目依赖
      - name: Install dependencies
        run: npm install
      # 下载 next 主题
      - name: download theme
        run: git clone https://github.com/theme-next/hexo-theme-next themes/next
      # 复制我的主题配置文件到 next 主题中进行替换
      - name: cp config
        run: |
          cp themes_config/next/_config.yml themes/next/
          cp themes_config/next/languages/zh-CN.yml themes/next/languages/
      # 编译生成项目文件
      - name: Hexo generate
        run: hexo generate
      # 使用 jar 工具打包项目编译获得的文件
      - name: Pack with jar
        run: jar -cvfM blog.war -C ./public/ .
      # 使用 sftp 工具上传项目打包文件到我的服务器
      - name: Upload file
        run: curl --ftp-create-dirs --retry 5 --retry-delay 3 -u hexo:${{secrets.FTP_PASS}} -T ./blog.war ftp://118.24.50.165/blog.war
```

> 以上配置完全复制了手动打包部署的全过程，其中有些可以进行优化，比如对 npm 组件加上缓存提升打包速度；在 `.gitmodules` 中配置 next 主题项目为子模块，以便在检出项目代码的同时也拉取 next 主题的代码。



### 工具

**act**，github 中的一个开源项目，可以在本地运行 Github Action，在调试的时候非常方便。

项目地址：<https://github.com/nektos/act> 



### 参考资料

- GitHub 操作文档: <https://docs.github.com/cn/actions> 



### 总结

GitHub 提供的 action 可以免费使用，而且配置简单，还能使用别人分享的配置，可以替换 Travis CI 完成项目的自动构建与部署。