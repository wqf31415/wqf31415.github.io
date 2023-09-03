---
title: markdown 中插入数学公式
date: 2021-01-06 15:10:08
tags:
- markdown
- js
- hexo
categories:
- 技术
---

<link href="https://cdnjs.cloudflare.com/ajax/libs/KaTeX/0.9.0/katex.min.css"  rel="stylesheet"/>

### 概述

这篇文件介绍了 LaTex 的概念与应用，介绍了如何在 markdown 文档中插入数学公式与在 hexo 博客中显示 LaTex 公式。



### 什么是 LaTex

$$
F(w)=\mathcal{F[f(t)]}={\int^{\infty}_{-\infty}}f(t)e^{-iwt}dt
$$

> LaTex，读作 `/ˈlɑːtɛk/` ，写作 L<sup>A</sup>T<sub>E</sub>X，是基于 T<sub>E</sub>X 的一种排版系统，由美国计算机科学家莱斯利·兰伯特在20世纪80年代初期开发，利用这种格式系统的处理，即使用户没有排版和程序设计的知识也可以充分发挥由TEX所提供的强大功能，不必一一亲自去设计或校对，能在几天，甚至几小时内生成很多具有书籍质量的印刷品。对于生成复杂表格和数学公式，这一点表现得尤为突出。因此它非常适用于生成高印刷质量的科技和数学、物理文档。这个系统同样适用于生成从简单的信件到完整书籍的所有其他种类的文档。——维基百科。

在 markdown 中也可以使用 LaTex 插入数学公式，如上展示的傅里叶变换公式。

<!-- more -->



### 在 markdown 中插入公式

> 更多语法可参考：<https://www.caam.rice.edu/~heinken/latex/symbols.pdf> 

在 markdown 中使用美元符号包裹 LaTex 关键字，即可插入行内的 LaTex 符号与公式，如下：

- 希腊字母：`$alpha$` - $\alpha$ 、`$\beta$` - $\beta$ 、`$\chi$` - $\chi$ 、`$\delta$` - $\delta$ 、`$\gamma$` - $\gamma$ 、`$\pi$` - $\pi$ 
- 运算符：`$+$` - $+$ 、`$-$` - $-$ 、`$\times$` - $\times$ 、`$\div$` - $\div$ 、`$=$` - $=$ 、`$\thickapprox$` - $\thickapprox$ 、`$\leq$` - $\leq$ 、`$\geq$` - $\geq$ 、`$\neq$` - $\neq$ 
- 标准函数名：`$\sin$` -$\sin$ 、`$\cos$` - $\cos$ 、`$\tan$` - $\tan$ 、`$\cot$` - $\cot$ 、`$\log$` - $\log$ 
- 箭头符号：`$\leftarrow$` - $\leftarrow$ 、`$\uparrow$` - $\uparrow$ 、`$\rightarrow$` - $\rightarrow$ 、`$\downarrow$` - $\downarrow$ 、`$\leftrightarrows$` - $\leftrightarrows$ 、`$\circlearrowleft$` - $\circlearrowleft$ 
- 其他符号：`$\clubsuit$` - $\clubsuit$ 、`$\diamondsuit$` - $\diamondsuit$ 、`$\heartsuit$` - $\heartsuit$ 、`$\spadesuit$` - $\spadesuit$ 、`$\bigstar$` - $\bigstar$ 
- 其他字体：`$\mathcal{ABCabc123}$` -  $\mathcal{ABCabc123}$ 、`$\mathbb{ABCabc123}$` - $\mathbb{ABCabc123}$ 、`$\mathfrak{ABCabc123}$` - $\mathfrak{ABCabc123}$ 、`$\mathsf{ABCabc123}$` - $\mathsf{ABCabc123}$ 、`$\mathbf{ABCabc123}$` - $\mathbf{ABCabc123}$ 
- 公式：`$\sqrt{3}$` - $\sqrt{3}$ 、`$E=mc^{2}$` - $E=mc^{2}$ 、`$\sin{(\alpha+\beta)}=\sin{\alpha}\cos{\beta}$+\cos{\alpha}\sin{\beta}` - $\sin{(\alpha+\beta)}=\sin{\alpha}\cos{\beta}+\cos{\alpha}\sin{\beta}$ 

在 markdown 中使用双美元符号插入行级公式，如平方差公式：

```markdown
$$
\sigma = \sqrt{\frac{1}{N}\sum_{i=1}^{N}{(x_{i}-\mu)^2}}
$$
```

效果：
$$
\sigma = \sqrt{\frac{1}{N}\sum_{i=1}^{N}{(x_{i}-\mu)^2}}
$$


### 支持 LaTeX 的编辑器和平台

Typora 编辑器已经支持输入 LaTex 公式与符号，输入公式直接使用双美元符号(`$$`)包裹，如需显示 LaTex 符号，需要在配置中勾选内联公式选项。

![](https://blog-images.qiniu.wqf31415.xyz/typora_setting_latex.png)

现在知乎、简书都支持使用 LaTex 公式了。



### 在 Hexo 博客中使用 LaTex 公式

想要在 Hexo 博客文章中渲染出 LaTex 公式，有两步操作：

- 添加渲染器

  需要修改博客项目配置文件 `package.json`，添加渲染工具 `hexo-renderer-markdown-it-plus` 。

  > hexo-renderer-markdown-it-plus: <https://github.com/CHENXCHEN/hexo-renderer-markdown-it-plus> 

  这个渲染器比默认的渲染器更加高效，而且支持多种新颖的 markdown 特性，如上下标语法（`H~2~O`，`X^2^`）、删除（`~~Del~~`）与修正（`++Inserted++`）、emoji 表情、Katex，等等。修改后的 package.json 配置：

  ```json
  {
    "name": "hexo-site",
    "version": "0.0.0",
    "private": true,
    "scripts": {
      "build": "hexo generate",
      "clean": "hexo clean",
      "deploy": "hexo deploy",
      "server": "hexo server"
    },
    "hexo": {
      "version": "4.2.1"
    },
    "dependencies": {
      "hexo": "^4.2.0",
      "hexo-deployer-git": "^2.0.0",
      "hexo-deployer-sftp": "^0.1.0",
      "hexo-filter-mermaid-diagrams": "^1.0.5",
      "hexo-generator-archive": "^1.0.0",
      "hexo-generator-category": "^1.0.0",
      "hexo-generator-index": "^1.0.0",
      "hexo-generator-tag": "^1.0.0",
      "hexo-renderer-ejs": "^1.0.0",
      "hexo-renderer-markdown-it-plus": "^1.0.4",
      "hexo-renderer-stylus": "^1.1.0",
      "hexo-server": "^1.0.0"
    }
  }
  ```

- 添加 css 样式

  在用到了 LaTex 公式的文章中添加  KaTex 样式，如：

  > KaTex: <https://github.com/KaTeX/KaTeX> 

  ```html
  <link href="https://cdnjs.cloudflare.com/ajax/libs/KaTeX/0.9.0/katex.min.css"  rel="stylesheet"/>
  ```

  

### 参考资料

- 使用Markdown输出LaTex数学公式: <https://segmentfault.com/a/1190000018527239> 
- TeX 与 LaTeX: <http://www.ctex.org/documents/shredder/tex_frame.html> 



### 总结

LaTex 在数学、物理方面的文章中输入公式时经常会用到，但它的功能不限于此，LaTex 中还有很多特殊符号和特殊字体，有时还能用来装饰。