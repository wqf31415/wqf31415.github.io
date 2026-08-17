---
title: 安装配置keycloak
tags:
  - keycloak
  - docker
  - 服务器
categories:
  - 工具
date： 2026-08-17 14:28:00
---

### 概述

这篇文章介绍了安装和配置 keycloak 的操作方法。



### 认识 keycloak

>官网：<https://www.keycloak.org/> 

Keycloak 是一个开源的企业身份认证与访问（IAA）管理基金方案，可以给应用、服务添加统一身份认证、授权和用户管理能力，而无需从零编写复杂的登录、注册和权限管理代码。

主要功能与优点：

- 核心认证功能：提供单点登录（SSO），用户登录一次即可访问所有授权系统，支持多因素认证（MFA）、社交账号登录。
- 标准协议支持：支持OpenID Connect、OAuth 2.0、SAML 2.0等业界主流标准协议，能与绝大多数现代应用和api无缝集成。
- 集中管理：提供管理控制台，可以集中管理用户、角色、权限，提供用户自助服务的账号控制台，如密码重置、管理个人资料。
- 集成与扩展能力：内置LDAP和Active Directory集成，可与企业现有用户系统同步；同时提供用户存储SPI，允许开发者为任何自定义用户数据库编写扩展。
- 开源免费：Apache 2.0许可，功能强大无授权费用。
- 高可用：模块化架构支持集群部署和横向扩展，满足高可用需求。

相似产品：

- [MaxKey](https://www.maxkey.top/)：国产开源IAM-IDaas身份管理和认证产品，对国内社交账号（微信/QQ/微博/钉钉）支持较好。
- [Authentik]([Welcome | authentik](https://goauthentik.io/))：**现代、轻量**，以用户友好的管理界面和内置的**用户自助门户**著称，是社区中常被提及的现代替代方案。
- [ZITADEL](https://zitadel.com/)：**云原生、高性能**，使用Go语言编写，资源占用低，**天生为Kubernetes和多租户设计**。
- [Logto](https://logto.io/)：**发者优先**，提供漂亮、现代化的登录界面，丰富的SDK，易用性高。

<!-- more -->

### 安装 keycloak

#### 创建数据库

登录MYSQL数据库，创建 keycloak 数据库：

```sql
CREATE DATABASE IF NOT EXISTS `keycloak` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

-- （可选）创建keycloak用户
CREATE USER IF NOT EXISTS 'keycloak'@'%' IDENTIFIED BY 'keycloak@123456';
GRANT ALL PRIVILEGES ON `keycloak`.* TO 'keycloak'@'%';
FLUSH PRIVILEGES;
```



#### 准备初始化数据

realm-config.json

```json
{
  "realm": "hq",
  "enabled": true,
  "clients": [
    {
      "clientId": "ruoyi-admin",
      "enabled": true,
      "publicClient": true,
      "directAccessGrantsEnabled": true,
      "redirectUris": [
        "http://localhost:8080/auth/keycloak/callback",
        "http://localhost:8080/*",
        "http://127.0.0.1:8080/*",
        "http://192.168.130.129:8080/auth/keycloak/callback",
        "http://192.168.130.129:8080/*",
        "http://ruoyi-admin:8080/auth/keycloak/callback",
        "http://ruoyi-admin:8080/*",
        "http://192.168.19.116:8080/auth/keycloak/callback",
        "http://192.168.19.116:8080/*",
        "http://192.168.38.243:8080/auth/keycloak/callback",
        "http://192.168.38.243:8080/*",
        "http://*:8080/auth/keycloak/callback",
        "http://*:8080/*",
        "https://*:8080/auth/keycloak/callback",
        "https://*:8080/*",
        "http://*/*",
        "https://*/*"
      ],
      "webOrigins": ["+"],
      "protocolMappers": [
        {
          "name": "preferred_username",
          "protocol": "openid-connect",
          "protocolMapper": "oidc-usermodel-property-mapper",
          "consentRequired": false,
          "config": {
            "userinfo.token.claim": "true",
            "user.attribute": "username",
            "id.token.claim": "true",
            "access.token.claim": "true",
            "claim.name": "preferred_username",
            "jsonType.label": "String"
          }
        }
      ]
    }
  ],
  "users": [
    {
      "username": "admin",
      "email": "admin@abc.com.cn",
      "firstName": "系统",
      "lastName": "管理员",
      "enabled": true,
      "credentials": [
        {
          "type": "password",
          "value": "admin123",
          "temporary": false
        }
      ],
      "realmRoles": ["offline_access", "uma_authorization"],
      "clientRoles": {
        "account": ["manage-account", "view-profile"]
      }
    },{
      "username": "zhangsan",
      "email": "zhangsan@abc.com.cn",
      "firstName": "三",
      "lastName": "张",
      "enabled": true,
      "credentials": [
        {
          "type": "password",
          "value": "Aa1111",
          "temporary": false
        }
      ],
      "realmRoles": ["offline_access", "uma_authorization"],
      "clientRoles": {
        "account": ["manage-account", "view-profile"]
      }
    }
  ]
}
```



#### 使用 docker 安装 keycloak

docker-compose.yml

```yaml
version: '3.8'

services:
  # Keycloak 认证服务（本地测试）
  keycloak:
    image: quay.io/keycloak/keycloak:26.6.1
    container_name: keycloak-local
    restart: unless-stopped
    environment:
      # 管理员账号
      KEYCLOAK_ADMIN: admin
      KEYCLOAK_ADMIN_PASSWORD: admin
      # 数据库配置 - 连接本地 MySQL
      KC_DB: mysql
      KC_DB_URL: jdbc:mysql://host.docker.internal:3306/keycloak?useSSL=false&allowPublicKeyRetrieval=true&characterEncoding=UTF-8&serverTimezone=Asia/Shanghai
      KC_DB_USERNAME: root
      KC_DB_PASSWORD: root
      # 放宽主机名限制，允许本地测试
      KC_HOSTNAME_STRICT: "false"
      KC_HOSTNAME_STRICT_HTTPS: "false"
      # 开发模式（可选，启用热重载等）
      KC_DEV: "true"
    ports:
      - "8180:8080"
    volumes:
      # 挂载 realm 配置文件
      - D:/program/docker/data/keycloak/import/realm-config.json:/opt/keycloak/data/import/realm-config.json
      # 挂载日志目录
      - D:/program/docker/data/keycloak/logs:/opt/keycloak/data/log
    command:
      - "start-dev"
      - "--import-realm"
```



运行命令：

```sh
docker compose -f .\docker-compose.yml up -d
```



### 配置 keycloak

浏览器访问 <http://localhost:8180/admin> ，使用账号 `admin` 、密码 `admin` 登录。

#### 中文界面配置

登录后点击菜单栏 Configure 分类下的 `Realm settings` 按钮，点击进入页面中 `Localization` 的 Tab 框。

> 也可以直接访问设置地址：<http://localhost:8180/admin/master/console/#/master/realm-settings/localization> 

打开 `Internationalization` 配置；

在 Supported locales 中增加简体中文 `Simplified Chinese` 选项；

Default locale 选择 `Simplified Chinese` 选项；

点击 Save 按钮保存，刷新浏览器，界面显示中文。

#### 进入领域管理

点击菜单栏 `管理领域` ，点击页面中的 `hq` ，进入 hq 领域管理，界面显示目前领域为 hq，后续菜单栏的设置都是针对 hq 领域的。

> 快捷访问地址：<http://localhost:8180/admin/master/console/#/hq> 

#### 配置领域支持中文

进入 hq 领域管理，点击菜单栏配置分类下的 `领域设置` 菜单，进入 `本地化` Tab页，修改下述配置：

> 快捷访问链接：<http://192.168.19.116:8180/admin/master/console/#/hq/realm-settings/localization> 

- 国际化：开启
- 支持的语言环境：添加 `简体中文` 
- 默认语言环境：选择 `简体中文` 

保存配置。

#### 添加用户信息字段

keycloak默认用户信息包括用户名、姓名、邮箱，可以根据需要添加新的用户属性，比如性别、手机号等。

进入 hq 领域管理，点击菜单栏配置分类下的 `领域设置` 菜单，进入 `用户资料` Tab页。

> 快捷链接：<http://localhost:8180/admin/master/console/#/hq/realm-settings/user-profile/attributes> 

点击 `创建属性` ，添加性别 `gender` 、手机号码 `phone` 、职位 `position` 属性，配置选项如下：

| 设置项            | 性别                                                   | 手机号码                    | 职位                      |
| ----------------- | ------------------------------------------------------ | --------------------------- | ------------------------- |
| 属性 [名称]       | gender                                                 | phone                       | position                  |
| 展示名称-简体中文 | 性别                                                   | 电话                        | 岗位                      |
| 展示名称-英文     | gender                                                 | phone                       | position                  |
| 多值的            | 关                                                     | 关                          | 开                        |
| 谁可以编辑        | 用户、管理员                                           | 用户、管理员                | 管理员                    |
| 谁可以查看        | 用户、管理员                                           | 用户、管理员                | 用户、管理员              |
| 验证              | options：`secret（保密）`,`male（男）`,`female（女）"` | pattern：`^1[3-9]\\\\d{9}$` | length：`min：2，max：20` |
| 注释              | inputType：select                                      | inputType：text             | inputType：text           |



修改方式二：可以使用 json 编辑器直接修改、添加属性，这种方式适合导入初始化数据，但需要注意这种方式没有国际化翻译信息，在导入后需要手动编辑属性，添加翻译。完整 json 数据：

```json
{
  "attributes": [
    {
      "name": "username",
      "displayName": "${username}",
      "validations": {
        "length": {
          "min": 3,
          "max": 255
        },
        "username-prohibited-characters": {},
        "up-username-not-idn-homograph": {}
      },
      "permissions": {
        "view": [
          "admin",
          "user"
        ],
        "edit": [
          "admin",
          "user"
        ]
      },
      "multivalued": false
    },
    {
      "name": "email",
      "displayName": "${email}",
      "validations": {
        "email": {},
        "length": {
          "max": 255
        }
      },
      "required": {
        "roles": [ "user" ]
      },
      "permissions": {
        "view": [
          "admin",
          "user"
        ],
        "edit": [
          "admin",
          "user"
        ]
      },
      "multivalued": false
    },
    {
      "name": "firstName",
      "displayName": "${firstName}",
      "validations": {
        "length": {
          "max": 255
        },
        "person-name-prohibited-characters": {}
      },
      "required": {
        "roles": [ "user" ]
      },
      "permissions": {
        "view": [
          "admin",
          "user"
        ],
        "edit": [
          "admin",
          "user"
        ]
      },
      "multivalued": false
    },
    {
      "name": "lastName",
      "displayName": "${lastName}",
      "validations": {
        "length": {
          "max": 255
        },
        "person-name-prohibited-characters": {}
      },
      "required": {
        "roles": [ "user" ]
      },
      "permissions": {
        "view": [
          "admin",
          "user"
        ],
        "edit": [
          "admin",
          "user"
        ]
      },
      "multivalued": false
    },
    {
      "name": "gender",
      "displayName": "${profile.attributes.gender}",
      "validations": {
        "options": {
          "options": [
            "secret（保密）",
            "male（男）",
            "female（女）"
          ]
        }
      },
      "annotations": {
        "inputType": "select"
      },
      "permissions": {
        "view": [
          "admin",
          "user"
        ],
        "edit": [
          "admin",
          "user"
        ]
      },
      "multivalued": false
    },
    {
      "name": "phone",
      "displayName": "${profile.attributes.phone}",
      "validations": {
        "pattern": {
          "pattern": "^1[3-9]\\\\d{9}$",
          "error-message": ""
        }
      },
      "annotations": {
        "inputType": "text"
      },
      "permissions": {
        "view": [
          "admin",
          "user"
        ],
        "edit": [
          "admin",
          "user"
        ]
      },
      "multivalued": false
    },
    {
      "name": "position",
      "displayName": "${profile.attributes.position}",
      "validations": {
        "length": {
          "min": "2",
          "max": "20"
        }
      },
      "annotations": {
        "inputType": "text"
      },
      "permissions": {
        "view": [
          "admin",
          "user"
        ],
        "edit": [ "admin" ]
      },
      "multivalued": true
    }
  ],
  "groups": [
    {
      "name": "user-metadata",
      "displayHeader": "User metadata",
      "displayDescription": "Attributes, which refer to user metadata"
    }
  ]
}
```

#### 配置给客户端的信息

可以配置客户端使用 keycloak 登录时，返回给客户端的用户信息，比如自定义的用户属性、用户所在组的信息。

进入 hq 领域管理，点击菜单栏管理分类中的 `客户端` ，进入 `客户端列表` Tab页；

> 快捷链接：<http://localhost:8180/admin/master/console/#/hq/clients/list> 

点击 `ruoyi-admin` 进入客户端详情页，点击 `客户端范围` Tab，点击 `ruoyi-admin-专用` ，添加如下字段映射器：

- 来自预定义映射：`email` 、`gender` 
- 根据配置：
  - User Attrbute：`phone`、`position` 
  - Group Membership

配置参数：

| 配置项         | email  | phone        | gender | position | group             |
| -------------- | ------ | ------------ | ------ | -------- | ----------------- |
| 名称           | email  | phone number | gender | position | group membership  |
| 用户属性       | email  | phone        | gender | position | -                 |
| 令牌申明名称   | email  | phone_number | gender | position | department_groups |
| 申明的JSON类型 | String | String       | String | String   | -                 |
| 支持多值       | 关     | 关           | 关     | 开       | -                 |

> 配置说明：
>
> - 映射名称可以自定义，要唯一
> - 令牌声明名称是给客户端的字段名，需要和客户端协调一致

### 导入用户数据

#### 准备用户数据

把公司部门信息和员工信息写入表格中，需要包含用户名、姓、名、邮箱、性别、部门、岗位，如下表：

| 用户名  | 姓   | 名   | 邮箱            | 性别 | 部门           | 岗位       |
| ------- | ---- | ---- | --------------- | ---- | -------------- | ---------- |
| zhaoyi  | 赵   | 一   | zhaoyi@abc.com  | 男   | /研发部        | 研发部经理 |
| qianer  | 钱   | 二   | qianer@abc.com  | 女   | /研发部/后端组 | 后端组主管 |
| sunsan  | 孙   | 三   | sunsan@abc.com  | 男   | /研发部/后端组 | 后端开发   |
| lisi    | 李   | 四   | lisi@abc.com    | 男   | /研发部/后端组 | 后端开发   |
| zhouwu  | 周   | 五   | zhouwu@abc.com  | 女   | /研发部/前端组 | 前端组主管 |
| wuliu   | 吴   | 六   | wuliu@abc.com   | 女   | /研发部/前端组 | 前端开发   |
| zhengqi | 郑   | 七   | zhengqi@abc.com | 男   | /研发部/前端组 | UI设计     |
| wangba  | 王   | 八   | wangba@abc.com  | 男   | /财务部        | 财务主管   |

根据员工表生成部门数据 json 和用户信息 json，可以放到一个 json 文件中一次导入。



#### 生成导入用户的json

```json
{
    "users": [
        {
            "username": "zhaoyi",
            "enabled": true,
            "emailVerified": false,
            "email": "zhaoyi@abc.com",
            "firstName": "赵",
            "lastName": "一",
            "credentials": [
                {
                    "type": "password",
                    "value": "Aa1111",
                    "temporary": true
                }
            ],
            "requiredActions": [ "UPDATE_PASSWORD" ],
            "realmRoles": [ "user" ],
            "groups": [ "/研发部" ],
            "attributes": {
                "locale": [ "zh-CN" ],
                "gender": [ "secret（保密）" ],
                "phone": [ "13011112222" ],
                "position": [ "研发部经理" ]
            }
        },
        {...}
    ],
    "ifResourceExists": "SKIP"
}
```

字段说明：

| **字段**                  | **类型** | **说明**                                                     |
| :------------------------ | :------- | :----------------------------------------------------------- |
| `users[].username`        | string   | **必填**，登录账号，全局唯一                                 |
| `users[].firstName`       | string   | 名                                                           |
| `users[].lastName`        | string   | 姓（Keycloak 显示名是 firstName + lastName 拼的）            |
| `users[].email`           | string   | 邮箱，建议唯一                                               |
| `users[].enabled`         | boolean  | 是否启用，设 `true`                                          |
| `users[].emailVerified`   | boolean  | 邮箱是否已验证，首次导入一般设 `false`                       |
| `users[].groups`          | string[] | Group **完整路径**数组，对应 Keycloak 里的 Group 路径        |
| `users[].realmRoles`      | string[] | 分配的 Realm 角色，如 `["user", "admin"]`                    |
| `users[].credentials`     | object[] | 凭证数组，一般只放一条密码                                   |
| `credentials[].type`      | string   | 固定填 `"password"`                                          |
| `credentials[].value`     | string   | 明文密码（导入时 Keycloak 会自动哈希）                       |
| `credentials[].temporary` | boolean  | `true` = 临时密码，用户首次登录必须改密码                    |
| `users[].attributes`      | object   | 自定义属性，**值必须是数组**（即使只有一个值）               |
| `ifResourceExists`        | string   | `SKIP`=已存在跳过（幂等安全） / `OVERWRITE`=覆盖 / `FAIL`=报错停 |



#### 生成导入部门的json

```json
{
    "groups": [
        {
            "name": "财务部",
            "path": "/财务部",
            "attributes": {},
            "subGroups": []
        },
        {
            "name": "研发部",
            "path": "/研发部",
            "attributes": {},
            "subGroups": [
                {
                    "name": "后端组",
                    "path": "/研发部/后端组",
                    "attributes": {},
                    "subGroups": []
                },
                {
                    "name": "前端组",
                    "path": "/研发部/前端组",
                    "attributes": {},
                    "subGroups": []
                }
            ]
        }
    ],
    "ifResourceExists": "SKIP"
}
```

字段说明：

| **字段**             | **类型** | **说明**                                                     |
| :------------------- | :------- | :----------------------------------------------------------- |
| `groups[].name`      | string   | Group 名称                                                   |
| `groups[].path`      | string   | Group 完整路径，以 `/` 开头                                  |
| `groups[].subGroups` | object[] | 子组，递归结构                                               |
| `ifResourceExists`   | string   | `SKIP`=已存在跳过（幂等安全） / `OVERWRITE`=覆盖 / `FAIL`=报错停 |



#### 导入部门与用户数据

进入 hq 领域管理，点击菜单栏配置分类下的 `领域设置` 。

>  快捷链接：<http://localhost:8180/admin/master/console/#/hq/realm-settings> 

点击页面右上角 `操作` - `部分导入` ，选择生成的 json 数据文件，勾选用户，选择冲突处理策略，点击导入。
