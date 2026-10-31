---
title: Java内网开发攻略
tags:
  - java
  - 开发
  - maven
  - springboot
categories:
  - 开发
date: 2021-10-31 20:37:13
---

### 概述

在工作中，有时会遇到保密要求较高的项目，开发时不能连接互联网，会产生很多问题，带来许多不便。这篇文章总结了在没有外网的环境下开发 java 项目的一些经验，介绍了一些常见问题的解决方案，主要是离线环境下的 maven 环境、springboot 环境搭建。



![](/images/post/java/coffee-beans.webp)



<!-- more -->



### 离线环境

其实，在内网中开发最重要的问题就是环境问题，从环境安装到依赖的类库下载，都会有点不方便。

#### java

需要从公网下载好需要的 jdk 包，拷贝到内网进行安装，此外建议下载相同版本的 jre，方便项目部署时使用。



#### maven

Maven 是一个广泛使用的 java 项目构建工具，它能够帮我们管理复杂的项目依赖，但在没有公网的环境中，无法直接下载 maven 依赖包，需要手动维护。

这时我们需要一台能上网的电脑，在电脑上搭建 maven，然后创建一个maven 项目，引入项目需要的maven依赖，使用maven下载好所有依赖，然后把 maven 的本地仓库打包，拷贝到内网中。最后修改内网 maven 的本地仓库配置，指向拷贝进来的仓库路径，这样就可以愉快的开发了。

##### 快速下载maven依赖包

在断网开发场景中，下载公网资源往往只能到指定的开放电脑上进行，但这台电脑不一定有我们需要的 java 和 maven 环境，这时可以用下述方法快速搭建环境下载需要的依赖库。

- 下载 jre 压缩包：从Oracle官网下载 java 8 的 jre 压缩包，解压后新建系统环境变量 JAVA_HOME，指向jre根目录，不用安装。

- 下载 maven 压缩包：从 Apache maven 官网下载 maven 压缩包，解压，添加 bin 路径到系统环境变量 path 中，然后修改配置文件，添加阿里镜像源，提升下载速度。

- 创建 pom.xml：创建最简单的 maven 项目依赖文件，添加自己需要的依赖，依赖的信息可以从 maven 在线仓库中搜索得到。

  > maven 官方中央仓库提供的搜索网站：<https://central.sonatype.com/> 
  > 常用的第三方maven依赖查询网站：<https://mvnrepository.com/> 

  ```xml
  <project>
  <groupId>xx</groupId>
  <artifactId>xx</artifactId>
  <version>x</version>
  <dependencies>
  <!-- 把要下载的依赖定义粘贴到这里 -->
  </dependencies>
  </project>
  ```

- 执行命令下载依赖：在pom.xml 目录中打开命令行执行命令: `mvn -f pom.xml dependency:copy-dependencies` ，等待依赖下载完成。

- 拷贝依赖包：将下载到本地的依赖文件打包，默认本地依赖保存路径是 `~/.m2` ，将其压缩打包后，传输到内网，使用时直接将其中内容解压，与内网原有依赖放在一起即可使用。

- 更新idea本地仓库索引：进入 idea，点击菜单栏 File，点 `Settings...` 进入设计界面，进入 `Build, Execution, Deployment` - `Build Tools` - `Maven` - `Repositories`，在右侧选择本地仓库（Type为Local），点击 `Update`。

#### springboot

当我们使用 idea 创建 SpringBoot 项目时，idea 会访问 spring 官方提供的项目初始化网站 <https://start.spring.io/> 生成初始化的项目文件。在内网环境中，无法访问该网站，导致无法创建项目。

其实这个网站的是开源的，github 地址是：<https://github.com/spring-io/start.spring.io.git> 

我们可以把这个项目的源码拉下来，到内网中运行起来，然后修改 idea 创建 SpringBoot 项目的 Server URL，改成我们运行的地址。

但是有一个问题，当我们请求自己搭建的 start 服务创建项目时，start 服务会访问 spring 官网获取 SpringBoot 项目版本信息，地址是：<https://spring.io/project_metadata/spring-boot> ，内容类似下面的<small>(这个项目元信息会随着 SpringBoot 的版本更新而更新)</small>：

```json
{
    "id":"spring-boot",
    "name":"Spring Boot",
    "projectReleases":[
        {
            "version":"2.6.0-SNAPSHOT",
            "versionDisplayName":"2.6.0-SNAPSHOT",
            "current":false,
            "releaseStatus":"SNAPSHOT",
            "snapshot":true
        },
        {
            "version":"2.6.0-RC1",
            "versionDisplayName":"2.6.0-RC1",
            "current":false,
            "releaseStatus":"PRERELEASE",
            "snapshot":false
        },
        {
            "version":"2.5.7-SNAPSHOT",
            "versionDisplayName":"2.5.7-SNAPSHOT",
            "current":false,
            "releaseStatus":"SNAPSHOT",
            "snapshot":true
        },
        {
            "version":"2.5.6",
            "versionDisplayName":"2.5.6",
            "current":true,
            "releaseStatus":"GENERAL_AVAILABILITY",
            "snapshot":false
        },
        {
            "version":"2.4.13-SNAPSHOT",
            "versionDisplayName":"2.4.13-SNAPSHOT",
            "current":false,
            "releaseStatus":"SNAPSHOT",
            "snapshot":true
        },
        {
            "version":"2.4.12",
            "versionDisplayName":"2.4.12",
            "current":false,
            "releaseStatus":"GENERAL_AVAILABILITY",
            "snapshot":false
        },
        {
            "version":"2.3.12.RELEASE",
            "versionDisplayName":"2.3.12.RELEASE",
            "current":false,
            "releaseStatus":"GENERAL_AVAILABILITY",
            "snapshot":false
        }
    ]
}
```

为了能够创建项目，我们需要让内网的 start 服务能够获取到这个元信息。首先访问项目元信息的地址，获取信息数据。

然后可以修改电脑 hosts 文件，让 `spring.io` 域名指向本地，然后在本地使用 nginx 让请求 `/project_metadata/spring-boot` 返回之前获取的元信息数据。这样就可以方便的创建项目了。

或者修改 `start.spring.io` 项目的配置，修改 `initializr.env.spring-boot-metadata-url` 配置，指向本地能够返回项目元信息的请求地址即可。

> 介绍一种让 nginx 返回 json 数据的配置，可以用来返回 springboot 项目版本信息：

```
http {
  server {
    listen    80;
    server_name    localhost;

    location /project_metadata/spring-boot {
      default_type    application/json;
      return 200 '{"id":"spring-boot","name":"spring boot"}'; # 要返回的 json 数据
    }
  }
}
```

### 搭建仓库服务

当团队中有多人都在内网环境开发时，可以考虑在内网搭建 sonatype nexus 仓库管理服务，作为 Maven 仓库使用。而且 nexus 还可以创建 apt、docker、npm、pypi、rubygems、yum 等类型的离线仓库，满足Linux开发、前端开发等开发的仓库需求。

> nexus 官网下载链接: <https://www.sonatype.com/products/sonatype-nexus-oss-download> 

#### 安装

> 以下方法以 Windows 系统安装 3.90.01 版本 nexus 为例，不同版本安装命令可能有所不同。

1. 下载安装包：从官网下载 nexus 安装包，下载得到一个 zip 压缩包，如 `nexus-3.90.1-01-win-x86_64.zip` ，将压缩包解压到路径没有中文和空格的文件夹中。

2.注册服务：进入 `nexus-3.90.1-01/bin` 目录中，打开命令行工具，运行 `install-nexus-service.bat D:\program\sonatype-work` 安装 nexus 服务，注意这里传参指定了工作目录，后续的配置文件、数据文件、日志等都默认存放在这个目录下。注册服务成功后，可以在Windows系统服务中看到名为 `SonatypeNexusRepository` 的服务。

3. 启动服务：运行 `nexus.exe start SonatypeNexusRepository` 命令启动服务，启动成功后访问 http://localhost:8081 ，用户名为 admin，密码在工作目录下的密码文件（admin.password）中，登录后需要修改密码，修改密码后，原始密码文件将自动删除。

4. 停止服务：当不需要仓库时可以运行  `nexus.exe stop SonatypeNexusRepository` 命令启动服务。

5. 删除服务：运行 `sc delete SonatypeNexusRepository` 命令删除服务。


#### 创建 maven 仓库

1. 创建存储空间：登录 nexus，进入 `Settings` - `Repository` - `Blob stores` 页面，点击 `Create Blob Store` ，选择 `File` 类型，Name 填写 `mvn` ，存储路径可保持默认，点击 Save。

2. 创建 hosted 仓库：进入 `Settings` - `Repository` - `Repositories` 页面，点击 `Create repository` ，选择 `maven2 (hosted)` 类型，填写配置：

- Name：myhostedrepository
- Version policy：Mixed
- Blob store：mvn
- Deployment policy：Allow redeploy

3. 创建 group 仓库：进入 `Settings` - `Repository` - `Repositories` 页面，点击 `Create repository` ，选择 `maven2 (group)` 类型，填写配置：

- Name：mygrouprepository
- Blob store：mvn
- Member repositories：添加上一步创建的 hosted 仓库 `myhostedrepository` 



#### 上传 maven 依赖

先将下载的依赖放到本地 maven 存储路径中，执行脚本，脚本读取本地仓库文件，上传到 nexus 的 hosted 仓库中。

```shell
#!/usr/bin/env bash
set -uo pipefail

# ============ 配置区（按需修改） ============
NEXUS_URL="http://127.0.0.1:8081"          # Nexus 根地址
NEXUS_USER="admin"
NEXUS_PASS="admin123"
REPO_RELEASE="myhostedrepository"              # release 仓库名，填写创建的 hosted 仓库名
REPO_SNAPSHOT="myhostedrepository"            # snapshot 仓库名，填写创建的 hosted 仓库名
LOCAL_REPO="$HOME/.m2/repository"          # 本地仓库根目录
# ============================================

NEXUS_URL="${NEXUS_URL%/}"
LOCAL_REPO="${LOCAL_REPO%/}"

# 收集一个 GAV 目录下所有需要上传的文件
# 输出: classifier<US>extension<US>路径   (US=\x1f，避免空 classifier 被 read 吞掉)
collect_assets() {
  local dir="$1" aid="$2" ver="$3" base="${3%-SNAPSHOT}"
  local f name ext stem cls
  for f in "$dir"/*; do
    [ -f "$f" ] || continue
    name=$(basename "$f")
    case "$name" in
      *.lastUpdated|*.sha1|*.md5|_remote.repositories|resolver-status.properties|maven-metadata*.xml)
        continue ;;
    esac
    ext="${name##*.}"
    stem="${name%.*}"
    if [ "$stem" = "${aid}-${ver}" ]; then
      cls=""                                          # 主构件
    elif [[ "$stem" == "${aid}-${ver}-"* ]]; then
      cls="${stem#"${aid}-${ver}-"}"                  # 带 classifier
    elif [[ "$stem" =~ ^${aid}-${base}-[0-9]{8}\.[0-9]{6}-[0-9]+(.*)$ ]]; then
      cls="${BASH_REMATCH[1]#-}"                      # SNAPSHOT timestamp 形式
    else
      continue
    fi
    printf '%s\x1f%s\x1f%s\n' "$cls" "$ext" "$f"
  done
}

upload_component() {
  local gid="$1" aid="$2" ver="$3" dir="$4"
  local repo="$REPO_RELEASE"
  [[ "$ver" == *SNAPSHOT* ]] && repo="$REPO_SNAPSHOT"

  local -a args=(-sS -X POST
    "${NEXUS_URL}/service/rest/v1/components?repository=${repo}"
    -u "${NEXUS_USER}:${NEXUS_PASS}"
    -w '%{http_code}' -o /dev/null
    -F "maven2.groupId=${gid}"
    -F "maven2.artifactId=${aid}"
    -F "maven2.version=${ver}")

  local i=0 cls ext f
  while IFS=$'\x1f' read -r cls ext f; do
    i=$((i + 1))
    args+=(-F "maven2.asset${i}=@${f}"
           -F "maven2.asset${i}.extension=${ext}")
    [ -n "$cls" ] && args+=(-F "maven2.asset${i}.classifier=${cls}")
  done < <(collect_assets "$dir" "$aid" "$ver")

  if [ "$i" -eq 0 ]; then
    echo "SKIP  ${gid}:${aid}:${ver}  (无可上传文件)"
    return
  fi

  local code
  code=$(curl "${args[@]}")
  case "$code" in
    20[04]) echo "OK    ${gid}:${aid}:${ver}  (${i} 个文件 → ${repo})" ;;
    400)    echo "SKIP  ${gid}:${aid}:${ver}  (已存在或禁止重部署)" ;;
    *)      echo "FAIL  ${gid}:${aid}:${ver}  HTTP ${code}" ;;
  esac
}

while IFS= read -r -d '' pom; do
  dir=$(dirname "$pom")
  ver=$(basename "$dir")
  aid=$(basename "$(dirname "$dir")")
  gpath=$(dirname "$(dirname "$dir")")
  gid="${gpath#"$LOCAL_REPO"}"; gid="${gid#/}"; gid="${gid//\//.}"
  [ -z "$gid" ] && continue
  upload_component "$gid" "$aid" "$ver" "$dir"
done < <(find "$LOCAL_REPO" -type f -name '*.pom' -print0)
```

#### 本地 maven 配置

修改开发电脑的 maven 配置文件，一般是 `~/.ms/settings.xml`，添加 `<mirror>` ：

```xml
<mirrors>
  <mirror>
    <id>nexus-offline</id>
    <mirrorOf>central</mirrorOf>
    <url>http://<Nexus-IP>:8081/repository/mygrouprepository/</url>
  </mirror>
</mirrors>
```

> 配置文件中的服务 ip 替换成真实的ip地址，`mygrouprepository` 是上一步创建的 group 仓库名。

如果后续需要发布构建到 nexus 仓库，还需要在配置文件中添加服务器认证配置，`<id>` 必须与 mvn deploy 命令中的 `-DrepositoryId` 一致：

```xml
<servers>
  <server>
    <id>nexus-releases</id>
    <username>admin</username>
    <password>你的密码</password>
  </server>
</servers>
```

### 遇到的问题

#### 打包时 maven 总是从远端仓库下载依赖

离线环境中，maven 依赖需要在公网环境下载好，再拷贝到开发机，有时会出现明明本地仓库有依赖包，在idea开发中运行也正常，但一到打包时，maven就从远端下载依赖，导致打包失败。

导致这种现象的原因是maven将依赖包的远端仓库源信息记录在依赖目录下的 `_remote.repositories` 文件中，如果源头不存在或不存在依赖的jar包，maven 在 resolve 时就会失败，导致项目构建失败。删除这个文件后，maven将不再从远程仓库执行这个操作，问题得以解决。

解决办法：删除依赖目录下的 `_remote.repositories` 文件

> Tips: 可以写个简单的程序遍历仓库路径下所有文件，将  `_remote.repositories` 文件删除。

```java
public class App {
  private static final String TARGET_FILE_NAME = "_remote.repositories";
  public static void main(String[] args){
    // 待处理的仓库目录
    String basePath = "D:/develop/.m2/repo";
    File pth = new File(basePath);
    if (path.exists()){
      handleFile(path, "|");
    } else {
      System.out.println("path ["+basePath+"] not exist");
    }
  }
  
  private static void handleFile(File file, String s){
    System.out.println(s+file.getName());
    if (file.isDirectory()){
      File fs = file.listFiles();
      for(File f: fs){
        handleFile(f, s+"  ");
      }
    } else {
      if(TARGET_FILE_NAME.equals(file.getName())){
        file.delete();
      }
    }
  }
}
```


### 总结

断网开发在一些银行项目、国家项目或科技项目中比较常见，其实也不用太担心，只要解决了开发环境问题就可以了。
