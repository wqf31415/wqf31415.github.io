---
title: langchain初体验
tags:
  - langchain
  - AI
  - 开发
  - python
categories:
  - AI
date: 2026-04-09 01:35:19
---

### 概述

langchain 已经成为当前市场上构建 AI 智能体的行业标准框架。这篇文档介绍了 langchain 的基本概念和使用方法。
 
### 认识 langchain

> langchain 官网：<https://www.langchain.com/> 
> 
> langchain 源码：<https://github.com/langchain-ai> 
>
> langchain 文档：<https://docs.langchain.com/> 
>
> langchain 中文文档：<https://langchain-doc.cn/>

langchain 是一个用于构建基于大模型的应用程序的开源框架，支持 python 和 javascript 两种语言。

大语言模型（LLMs）好比是一个聪明的大脑，langchain 的作用是给这个大脑添加手脚（Tools）、记忆（Memory）和工作技能（Chains），让它能够自主思考决策，调用工具操作外部资源（数据），完成各种复杂的任务。

<!-- more -->

### langchain 核心理念

langchain 最核心的理念是**模块化**和**组合**，把 AI 应用中的各种功能标准化形成组件，然后组合起来构建完整的应用，就像搭乐高积木一样，灵活组合不同的组件，构建出复杂的应用。

#### LLMs（大语言模型）

大语言模型（LLMs）是 AI 应用的核心，负责思考和生成文本。langchain 封装了主流的大语言模型接口，如OpenAI、千问、Deepseek等，提供了统一的接口，让用户只需要修改少量代码就可以切换不同模型。

#### Prompts（提示词模板）

使用提示词工程（Prompts）设计好与大模型交互的模板，提高大模型的性能和准确性，设定返回值的格式，让交互更稳定。

#### Chains（链）

> 核心概念，即 langchain 名称中的 Chain

像链条一样，将多个模块组件按顺序组合成一个工作流，上一个步骤的输出自动作为下一个步骤的输入。

#### Memory（记忆）

让大模型拥有记忆能力，记住当前会话中的历史消息与中间状态，实现多轮会话。

#### Tools（工具）

给大模型添加 “手”、“脚”，让它能够执行外部任务，如调用外部 API、操作数据库、发邮件、写文件等。

#### Retrievers（检索器）

基于向量数据库的检索增强生成（RAG），让大模型能够从私有知识库中检索信息，解决模型知识固定、上下文有限的问题。langchain提供了文档加载器、切分器、Embeding 接口、向量库封装、检索器，把RAG组件标准化。

#### Agents（智能体）

由大模型根据任务目标进行思考，自己决策，动态的使用一个或多个工具（Tools）、检索器（Retrievers）等组件，完成目标。

### langchain 相似产品

#### AI Agent开发框架

- [AutoGen](https://microsoft.github.io/autogen/stable/index.html)：微软推出的开源智能体开发框架，特点是多代理对话，每个代理扮演不同的角色，拥有不同的技能，它们相互协作完成复杂任务。支持 python 、.NET 语言。

- [CrewAI](https://crewai.org.cn/open-source): 用于编排自主 AI 代理和构建复杂工作流的开源框架。支持 python 语言。

- OpenAI Agents SDK

- Google ADK

- Semantic Kernel

#### RAG

- [LlamaIndex](https://www.llamaindex.ai/): 专注数据处理与检索增强生成，提供强大索引与查询能力，是 RAG 领域专家，在 RAG 方面比 langchain 更深，更专业。数据处理能力更强，Agent能力较弱，适合做私有文档、知识库问答等。

- [Haystack](https://haystack.deepset.ai/) : 一个基于 RAG 的框架，提供文档加载器、切分器、Embeding 接口、向量库封装、检索器，把RAG组件标准化。

#### 低代码/可视化工作流

- Dify

- Coze

- n8n

#### Java 生态

- langchain4j

- Spring AI Alibaba

### hello world

#### 环境要求

> 1. 安装 python 3.11 或以上版本
> 2. 安装 langchain 库
> 3. 安装其他依赖库

#### 安装依赖

> 1. 打开终端
> 2. 运行以下命令安装依赖
> 3. 安装完成后，打开项目目录
> 4. 运行以下命令启动项目

```bash
python main.py
```
#### 项目结构

#### 代码

```python
from langchain.llms import OpenAI
from langchain.prompts import ChatPromptTemplate
from langchain.output_parsers import StrOutputParser

llm = OpenAI()
prompt = ChatPromptTemplate.from_messages([
    ("system", "You are a helpful assistant."),
    ("human", "{input}"),
])
parser = StrOutputParser()

def main():
    while True:
        input_str = input("请输入: ")
        if input_str == "exit":
            break
        response = llm.invoke(prompt.format(input=input_str))
        print(parser.parse(response))

if __name__ == "__main__":
    main()
```


### 参考资料

### 总结

