---
title: 无GPU本地部署翻译小模型
tags:
  - AI
  - LLM
  - 小模型
  - ollama
categories:
  - AI
date: 2026-10-31 11:39:04
---

### 概述

这篇文章介绍了使用 ollama 在本地部署翻译模型（Hy-MT2-1.8B）的详细操作方法与注意事项，提供了必要的下载链接、运行脚本。

### 实现方案

为了在没有显卡的内网电脑上使用翻译功能，这次选择使用 ollama 运行本地的翻译模型 Hy-MT2-1.8B，选择了 Q4_K_M 量化版本，模型文件仅 1.13G 大小，在纯 CPU 场景下也能顺畅运行。

模型运行起来后，再接入 STranslate 软件，方便平时实时的划词翻译、截屏翻译。

<!-- more -->

### 模型介绍

> Hy-MT2 是一款面向真实复杂场景的“快思考”多语言翻译模型家族，涵盖 1.8B、7B 和 30B-A3B（MoE）三种体量，支持 33 种语言互译并具备强大的多语言指令遵循能力。在端侧部署上，得益于 AngelSlim 1.25-bit 极端量化，其 1.8B 模型仅需 440MB 存储空间，推理速度显著提升 1.5 倍。多维度评测表明，Hy-MT2 在通用、真实业务、专业领域及指令遵循等翻译任务中表现卓越：7B 和 30B-A3B 模型性能不仅超越了 DeepSeek-V4-Pro、Kimi K2.6 等开源模型在快思考模式下的表现，轻量级 1.8B 模型亦在整体上超越了微软和豆包等主流商业 API。

模型地址：

HF Mirror：<https://hf-mirror.com/tencent/Hy-MT2-1.8B> 

Q4 量化版本模型(1.13G)下载地址：

HF Mirror：<https://hf-mirror.com/tencent/Hy-MT2-1.8B-GGUF/blob/main/Hy-MT2-1.8B-Q4_K_M.gguf> 

### 软件

#### 模型运行工具：ollama

本地运行大语言模型并对外提供API访问的工具。

官网地址：<https://ollama.com/> 

Windows 下载地址(1.6G)：<https://ollama.com/download/OllamaSetup.exe> 

#### 翻译工具：STranslate

一款使用大语言模型进行本地翻译的软件，支持划词翻译、OCR识别翻译，可接入本地大语言模型。

官网地址：<https://stranslate.zggsong.com/> 

GitHub地址：<https://github.com/STranslate/STranslate> 


### 安装与配置

1. 下载所需的模型文件、ollama、STranslate 软件安装包。
2. 安装 ollama 软件，安装完成后进入软件界面，在 Settings 中修改模型文件路径配置 Model location ，如修改为 `D:\ollama\models`。

将下载的模型文件 `Hy-MT2-1.8B-Q4_K_M.gguf` 放到一个不含中文、空格的目录下，在当前目录创建文件 `Modelfile` 内容如下：

```dockerfile
FROM ./Hy-MT2-1.8B-Q4_K_M.gguf

# 1. 核心：添加官方控制符模板
TEMPLATE """<｜hy_begin▁of▁sentence｜>{{ if .System }}{{ .System }}<｜hy_place▁holder▁no▁3｜>{{ end }}{{ if .Prompt }}<｜hy_User｜>{{ .Prompt }}{{ end }}<｜hy_Assistant｜>"""

# 2. 核心：添加停止符，防止模型输出失控
PARAMETER stop "<｜"
PARAMETER stop "<ｆin｜hy-"
PARAMETER stop "<ｈy-"
PARAMETER stop "<ｺ｜hy-"
PARAMETER stop "<ｂ｜hy-"

# 3. 官方推荐的采样参数
PARAMETER temperature 0.7
PARAMETER top_p 0.6
PARAMETER top_k 20
PARAMETER repeat_penalty 1.05
PARAMETER num_predict 4096

# 4. 建议保持 num_ctx 为 2048 或更高
PARAMETER num_ctx 2048
```

**经测试，上面 Modelfile 中的控制符模版、停止符参数必须添加，否则翻译效果不好。**

在 `Modelfile` 文件目录下打开命令行工具，运行命令 `ollama create hy-mt2:1.8b` 创建模型，命令执行打印 `success` 说明执行成功。

在命令行中执行 `ollama list` 查看已安装的模型列表，在模型列表中应有名为 `hy-mt2:1.8b` 的模型。

此时可以在 ollama 软件 Chat 界面中选择这个模型，发送单词、句子进行测试，比如发送：

```
翻译成中文：
　　We got there at nine o'clock. After pied into three groups, we began to work. Each group had their own tasks. Group one planted trees and watered flowers. Group Two picked up litter left by tourists and cleaned the benches. My group wiped all the equipment in Children's Playground. Each of us worked hard. At about half past eleven, we finished working. Though we were tired,we were happy. It was a meaningful day for us because we had done a good deed.
```

回复：

```
我们在九点钟到达那里。分成三个小组后，我们开始工作。每个小组都有各自的任务。第一小组种植树木并浇花。第二小组清理游客留下的垃圾并打扫长椅。我的小组则清理了儿童游乐场的所有设备。我们每个人都努力工作。大约十一点半，我们完成了工作。虽然很疲惫，但我们感到快乐。对我们来说这是有意义的一天，因为我们做了好事。
```

3. 安装 STranslate 软件，右键点击任务栏中软件图标，点击 `偏好设置` ，在设置页面点击进入 `服务设置` - `文本翻译` ，点击下方 `+` 按钮，添加 Ollama ，修改配置：

- 接口：http://localhost:11434
- 模型：hy-mt2:1.8b

可点击配置页面中联通测试的 `验证` 按钮测试模型连接是否正常，提示 `验证成功` 说明配置正确，保存配置。

4. 使用 STranslate 进行翻译：

  - 输入翻译（Alt + A）：输入文本进行翻译
  - 划词翻译（Alt + D）：鼠标选中要翻译的文本，按快捷键进入划词翻译
  - 截图翻译（Alt + S）：按快捷键后进入截图模式，截取要翻译文本的图像，自动调用 OCR 转成文本进行翻译

### 总结

小参数的模型要达到理想的运行效果，一定要注意根据使用场景选择模型，比如翻译场景就选择翻译模型，这些模型对翻译场景做了训练，效果更好，不要选择通用的模型。

一定要注意运行参数配置，有时候回答效果不好，并不是模型问题，而是参数没配好，要多关注官方提供的参数配置。