# wqf31415.github.io

## 描述
这是使用 Hexo 生成的静态博客，`master` 分支提供 page 页面访问， `source` 分支为博客资源。

## 运行环境
- Node v10.15.3+
- Npm 6.4.1+
- Git 2.13.3+

## 运行

### 下载源码
- 使用 Git 克隆：
  ```
  git clone https://github.com/wqf31415/wqf31415.github.io.git
  ```

- 下载 ZIP 压缩包：
  <https://codeload.github.com/wqf31415/wqf31415.github.io/zip/master>

### 切换到 `source` 分支
进入项目根目录，执行命令：
```bash
git checkout source
```

### 安装依赖
在项目根目录，使用 npm 安装需要的依赖：
```bash
npm install
```

### 下载主题
当前使用的是 [NexT](https://theme-next.org) 主题，下载方式，进入项目根目录，执行：
```bash
git clone https://github.com/theme-next/hexo-theme-next themes/next
```

### 修改主题配置
在 `themes_config` 目录中存了主题相关的配置，将其中配置文件 `_config.yml` 复制到 `themes/next/` 目录下覆盖文件：
```bash
cp themes_config/next/_config.yml themes/next/
```
### 修改翻译错误
在博客中可能存在一些自定义的菜单项，显示为英文，如需要修改成显示中文，则可以修改 `themes/next/languages/zh-CN.yml` 中的配置，在 `menu` 一项中添加需要的字段配置即可。

### 生成博客页面
先使用命令清除已生成的页面：
```bash
hexo clean
```

然后渲染生成页面文件：
```bash
hexo generate
```

最后开启本地 hexo 服务：
```bash
hexo server
```

访问 <http://localhost:4000> ，查看页面显示是否正确。

