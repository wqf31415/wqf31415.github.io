---
title: modify blog source
date: 2017-02-11 12:25:47
tags: 
- hexo
- git
categories: 
- 技术

---



在其他电脑上只需要把github上wqf31415.github.io仓库的source分支克隆到本地

`git clone https://github.com/wqf31415/wqf31415.github.io.git`

克隆到本地后，运行

`npm install`

然后就可以编辑修改blog的内容了！

修改完成后运行下面的git指令推送到github即可：

`git add .`

`git commit -m 'modify something'`

`git push origin source`

