---
title: 仅3kB的ReactJs替代方案
tags:
  - js
  - react
  - 嵌入式
categories:
  - js
date: 2022-12-05 21:50:08
---

### 概述

这篇文章简要的介绍了一款开源的前端 js 库——PreactJs，其特点是小巧且易用，仅 3kB 即可实现类似 React 的现代化前端 api，特别适用于存储空间有限的环境，比如嵌入式的 web 项目。



### 认识 PreactJs

> 官网: <https://preactjs.com/> 
>
> Github(star 33k): <https://github.com/preactjs/preact> 

PreactJs 是 React 的轻量化、快速的替代方案，拥有与其相同的现代化 API，其优势在于：

- 贴近实质：Preact 在 DOM 上提供了最薄的虚拟 DOM 抽象，在提供稳定的平台特性和注册事件处理程序的同时还确保其余其他库无缝兼容。Preact 无需转译即可在浏览器中直接使用。
- 微小体积：Preact 体积小，意味着下载、解析、执行更少的 JavaScript，让开发人员专心构建用户体验，无需花更多时间在框架本身上。
- 性能卓越：Preact 体积小，加载速度快，而且其基于树差异的简单、可预测而极快的虚拟 DOM 实现也提升了响应速度。
- 即刻生产：Preact 轻量但不牺牲生产性，可以即刻部署到生产环境，甚至提供一些附加功能：
  - 将 `props` 、`state` 和 `context` 传递进 `render()` 
  - 使用 `class` 和 `for` 一类的标准 HTML 属性
- 生态兼容：Preact 的设计能够让您轻松、无缝的借用来自 React 生态中的许多组件。



<!-- more -->

### 快速开始





### 总结

官网号称的 3kB 是有点夸张，最新的 PreactJs 10.11.3 中的压缩版 preac.min.js 是 9.95 KB，但跟其他前端框架动辄几兆大小相比确实是非常轻量了。
