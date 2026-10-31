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

使用 ollama 运行本地的翻译模型，接入 STranslate 软件进行翻译。

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
2. 安装 ollama 软件，在 Settings 中修改模型文件路径配置 Model location ，如修改为 `D:\ollama\models`。


3. 安装 STranslate 软件，修改配置。

### 总结

小参数的模型要达到理想的运行效果，一定要注意根据使用场景选择模型，比如翻译场景就选择翻译模型，这些模型对翻译场景做了训练，效果更好，不要选择通用的模型。

一定要注意运行参数配置，有时候回答效果不好，并不是模型问题，而是参数没配好，要多关注官方提供的参数配置。