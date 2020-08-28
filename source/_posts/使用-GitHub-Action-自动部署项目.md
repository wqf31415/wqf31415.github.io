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

![](http://blog-images.qiniu.wqf31415.xyz/github_action_1.png)

点击下方的记录，查看详情：

![](http://blog-images.qiniu.wqf31415.xyz/github_action_2.png)

点击 `build` 查看构建的日志详情：

![](http://blog-images.qiniu.wqf31415.xyz/github_action_3.png)

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

定义一系列任务步骤，步骤可以运行命令、运行设置任务，或者运行个人仓库、公共仓库中的操作或 Docker 注册中发布的操作。

```yml
jobs:
  my-job:
    name: my job
    runs-on: ubuntu-latest
    steps:
      - name: Print hello
        env: 
          MY_NAME: Jack
        run: |
          echo hello $MY_NAME
```



###### `timeout-minutes` 

指定超时时间，默认值为 360 分钟。





### 参考资料

- GitHub 操作文档: <https://docs.github.com/cn/actions> 



### 总结

GitHub 提供的 action 可以免费使用，而且配置简单，还能使用别人分享的配置，可以替换 Travis CI 完成项目的自动构建与部署。