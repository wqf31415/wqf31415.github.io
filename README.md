# wqf31415.github.io

## 描述
这是使用 [Hexo](https://hexo.io/zh-cn/) 生成的静态博客，`master` 分支提供 page 页面访问， `source` 分支为博客资源。

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
在 `themes_config` 目录中存了主题相关的配置文件备份，将其中配置文件 `_config.yml` 复制到 `themes/next/` 目录下覆盖文件：
```bash
cp themes_config/next/_config.yml themes/next/
```
### 修改翻译错误
在博客中可能存在一些自定义的菜单项，显示为英文，如需要修改成显示中文，则可以修改 `themes/next/languages/zh-CN.yml` 中的配置，在 `menu` 一项中添加需要的字段配置即可。

### 渲染博客内容并开启预览
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

## 新建博文

使用 hexo 命令创建一篇新博文：

```bash
hexo new "新博文的名称"
```

命令执行完成后，将在 `source/_post` 目录下生成新的博文文件，是一个 markdown 格式的文档，将新博文的内容写在这个文档中即可。

## 部署

> Hexo 官方文档： <https://hexo.io/docs/deployment.html> 

使用以下命令即可将博客部署到相应平台上：

```bash
hexo deploy
```

也可以使用简写命令 `hexo d` 。

> 当前已有部署方式包括 git 和 sftp 两种，其中使用的 git 平台是 GitHub 和 coding.me ，sftp 部署地址为 www.wqf31415.xyz ，**注意：如果需要使用 sftp 部署 ，需要修改博客根目录中的配置文件 `_config.yml` ，将 sftp 的密码填上**。



