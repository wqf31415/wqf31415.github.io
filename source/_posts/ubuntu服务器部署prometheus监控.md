---
title: ubuntu服务器部署prometheus监控
tags:
  - prometheus
  - ubuntu
  - linux
  - docker
  - 服务器
  - grafana
  - 可视化
categories:
  - 工具
date: 2026-02-12 15:39:48
---

### 概述

文章介绍了在 ubuntu 服务器上使用 docker 部署服务监控软件普罗米修斯（prometheus），并将其他 linux 主机添加到监控。



### 认识prometheus

> 官网：<https://prometheus.io/> 
> 
> Github: <https://github.com/prometheus/prometheus> 

普罗米修斯(Prometheus)是云原生计算基金会的一个项目，是一个系统和服务监控系统。它会定期从配置的目标中收集指标，评估规则表达式，显示结果，并且在观察到指定条件时可以触发警报。

<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1" width="699px" height="481px" viewBox="-0.5 -0.5 699 481" content="&lt;mxfile host=&quot;app.diagrams.net&quot; modified=&quot;2023-02-15T10:37:45.696Z&quot; agent=&quot;5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36&quot; version=&quot;20.8.20&quot; etag=&quot;qEbbTptGCHtHlne_CPfj&quot;&gt;&lt;diagram name=&quot;Page-1&quot; id=&quot;0&quot;&gt;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&lt;/diagram&gt;&lt;/mxfile&gt;" style="background-color: rgb(255, 255, 255);"><defs/><g><rect x="248" y="330" width="260" height="70" fill="#e6e6e6" stroke="#808080" pointer-events="all"/><rect x="248" y="180" width="260" height="150" fill="#ffeccf" stroke="#808080" stroke-dasharray="3 3" pointer-events="all"/><rect x="221" y="240" width="2.8" height="50" fill="#4d4d4d" stroke="#4d4d4d" pointer-events="all"/><rect x="226.6" y="240" width="2.8" height="50" fill="#4d4d4d" stroke="#4d4d4d" pointer-events="all"/><rect x="232.2" y="240" width="2.8" height="50" fill="#4d4d4d" stroke="#4d4d4d" pointer-events="all"/><rect x="0" y="340" width="120" height="30" rx="1.8" ry="1.8" fill="rgb(255, 255, 255)" stroke="rgb(0, 0, 0)" pointer-events="all"/><rect x="10" y="350" width="120" height="30" rx="1.8" ry="1.8" fill="rgb(255, 255, 255)" stroke="rgb(0, 0, 0)" pointer-events="all"/><rect x="20" y="360" width="120" height="30" rx="1.8" ry="1.8" fill="rgb(255, 255, 255)" stroke="rgb(0, 0, 0)" pointer-events="all"/><path d="M 218 250 L 68 250 L 68 331.88" fill="none" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 68 338.88 L 64.5 331.88 L 71.5 331.88 Z" fill="#4d4d4d" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="all"/><path d="M 218 260 L 78 260 L 78 341.88" fill="none" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 78 348.88 L 74.5 341.88 L 81.5 341.88 Z" fill="#4d4d4d" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="all"/><path d="M 218 270 L 88 270 L 88 351.88" fill="none" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 88 358.88 L 84.5 351.88 L 91.5 351.88 Z" fill="#4d4d4d" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="all"/><rect x="258" y="225" width="70" height="90" fill="rgb(255, 255, 255)" stroke="#b3b3b3" pointer-events="all"/><rect x="338" y="225" width="80" height="90" fill="rgb(255, 255, 255)" stroke="#b3b3b3" pointer-events="all"/><rect x="428" y="225" width="70" height="90" fill="rgb(255, 255, 255)" stroke="#b3b3b3" pointer-events="all"/><rect x="48" y="100" width="130" height="40" fill="#fff3e6" stroke="rgb(0, 0, 0)" pointer-events="all"/><rect x="8" y="0" width="100" height="30" rx="1.8" ry="1.8" fill="rgb(255, 255, 255)" stroke="rgb(0, 0, 0)" pointer-events="all"/><rect x="18" y="10" width="100" height="30" rx="1.8" ry="1.8" fill="rgb(255, 255, 255)" stroke="rgb(0, 0, 0)" pointer-events="all"/><path d="M 68 40 L 68 91.88" fill="none" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 68 98.88 L 64.5 91.88 L 71.5 91.88 Z" fill="#4d4d4d" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="all"/><path d="M 228 240 L 113 240 L 113 148.12" fill="none" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 113 141.12 L 116.5 148.12 L 109.5 148.12 Z" fill="#4d4d4d" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 240px; margin-left: 166px;"><div data-drawio-colors="color: #4D4D4D; " style="box-sizing: border-box; font-size: 0px; text-align: center;"><div style="display: inline-block; font-size: 11px; font-family: Helvetica; color: rgb(77, 77, 77); line-height: 1.2; pointer-events: all; white-space: nowrap;">pull metrics<div><br /></div><div><br /></div></div></div></div></foreignObject><text x="166" y="243" fill="#4D4D4D" font-family="Helvetica" font-size="11px" text-anchor="middle">pull metrics...</text></switch></g><rect x="399" y="340" width="100" height="50" fill="#575757" stroke="rgb(0, 0, 0)" pointer-events="all"/><rect x="415" y="355" width="67" height="20" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 65px; height: 1px; padding-top: 365px; margin-left: 416px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center; max-height: 16px; overflow: hidden;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;"><font color="#ffffff">HDD / SSD</font></div></div></div></foreignObject><text x="449" y="369" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">HDD / SSD</text></switch></g><rect x="58" y="110" width="110" height="20" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 108px; height: 1px; padding-top: 120px; margin-left: 59px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center; max-height: 16px; overflow: hidden;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">Pushgateway</div></div></div></foreignObject><text x="113" y="124" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Pushgateway</text></switch></g><rect x="23" y="15" width="90" height="20" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 88px; height: 1px; padding-top: 25px; margin-left: 24px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center; max-height: 16px; overflow: hidden;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">Short-lived jobs</div></div></div></foreignObject><text x="68" y="29" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Short-lived jobs</text></switch></g><rect x="30" y="365" width="100" height="20" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 98px; height: 1px; padding-top: 375px; margin-left: 31px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center; max-height: 16px; overflow: hidden;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">Jobs / Exporters</div></div></div></foreignObject><text x="80" y="379" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Jobs / Exporters</text></switch></g><rect x="348" y="230" width="60" height="20" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 58px; height: 1px; padding-top: 240px; margin-left: 349px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center; max-height: 16px; overflow: hidden;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">Storage</div></div></div></foreignObject><text x="378" y="244" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Storage</text></switch></g><rect x="258" y="230" width="70" height="20" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 68px; height: 1px; padding-top: 240px; margin-left: 259px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center; max-height: 16px; overflow: hidden;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">Retrieval</div></div></div></foreignObject><text x="293" y="244" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Retrieval</text></switch></g><rect x="428" y="230" width="70" height="20" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 68px; height: 1px; padding-top: 240px; margin-left: 429px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center; max-height: 16px; overflow: hidden;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">PromQL</div></div></div></foreignObject><text x="463" y="244" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">PromQL</text></switch></g><rect x="318" y="175" width="120" height="50" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 118px; height: 1px; padding-top: 200px; margin-left: 319px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center; max-height: 46px; overflow: hidden;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;"><div style="text-align: left"><b style="line-height: 1.2">Prometheus Server</b></div></div></div></div></foreignObject><text x="378" y="204" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Prometheus Server</text></switch></g><rect x="258" y="355" width="90" height="20" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 88px; height: 1px; padding-top: 365px; margin-left: 259px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center; max-height: 16px; overflow: hidden;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;"><b>Node</b></div></div></div></foreignObject><text x="303" y="369" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Node</text></switch></g><rect x="568" y="110" width="120" height="60" fill="#fff3e6" stroke="#120d00" pointer-events="all"/><rect x="228" y="10" width="150" height="110" fill="#99ccff" stroke="#4d4d4d" pointer-events="all"/><rect x="238" y="15" width="130" height="20" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 128px; height: 1px; padding-top: 25px; margin-left: 239px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center; max-height: 16px; overflow: hidden;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">Service Discovery<div><br /></div></div></div></div></foreignObject><text x="303" y="29" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Service Discovery&#xa;</text></switch></g><path d="M 289 225 L 289 128.12" fill="none" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 289 121.12 L 292.5 128.12 L 285.5 128.12 Z" fill="#4d4d4d" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 151px; margin-left: 294px;"><div data-drawio-colors="color: #4D4D4D; " style="box-sizing: border-box; font-size: 0px; text-align: center;"><div style="display: inline-block; font-size: 11px; font-family: Helvetica; color: rgb(77, 77, 77); line-height: 1.2; pointer-events: all; white-space: nowrap;">             find <div style="text-align: left">                 targets</div></div></div></div></foreignObject><text x="294" y="154" fill="#4D4D4D" font-family="Helvetica" font-size="11px" text-anchor="middle">find...</text></switch></g><rect x="108" y="440" width="130" height="30" rx="1.8" ry="1.8" fill="#fff3e6" stroke="rgb(0, 0, 0)" pointer-events="all"/><rect x="118" y="450" width="130" height="30" rx="1.8" ry="1.8" fill="#fff3e6" stroke="rgb(0, 0, 0)" pointer-events="all"/><rect x="128" y="455" width="110" height="20" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 108px; height: 1px; padding-top: 465px; margin-left: 129px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center; max-height: 16px; overflow: hidden;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">Prometheus Server</div></div></div></foreignObject><text x="183" y="469" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Prometheus Server</text></switch></g><path d="M 218 280 L 168 280 L 168 431.88" fill="none" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 168 438.88 L 164.5 431.88 L 171.5 431.88 Z" fill="#4d4d4d" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="all"/><path d="M 221 290 L 178 290 L 178 441.88" fill="none" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 178 448.88 L 174.5 441.88 L 181.5 441.88 Z" fill="#4d4d4d" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="all"/><path d="M 233.6 265 L 258 265" fill="none" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 293 305 L 293 290 Q 293 280 293 270 L 293 255" fill="none" stroke="#000000" stroke-width="2" stroke-miterlimit="10" stroke-dasharray="2 8" pointer-events="stroke"/><path d="M 303 280 L 368 280 Q 378 280 388 280 L 439.9 279.99" fill="none" stroke="#808080" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 446.9 279.99 L 439.9 283.49 L 439.9 276.49 Z" fill="#808080" stroke="#808080" stroke-miterlimit="10" pointer-events="all"/><path d="M 368 280 L 368 360 Q 368 370 378 369.99 L 389.9 369.98" fill="none" stroke="#808080" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 396.9 369.97 L 389.91 373.48 L 389.9 366.48 Z" fill="#808080" stroke="#808080" stroke-miterlimit="10" pointer-events="all"/><rect x="578" y="130" width="100" height="20" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 98px; height: 1px; padding-top: 140px; margin-left: 579px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center; max-height: 16px; overflow: hidden;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">Alertmanager</div></div></div></foreignObject><text x="628" y="144" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Alertmanager</text></switch></g><path d="M 508 217.5 L 628 217.5 L 628 178.12" fill="none" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 628 171.12 L 631.5 178.12 L 624.5 178.12 Z" fill="#4d4d4d" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 218px; margin-left: 592px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center;"><div style="display: inline-block; font-size: 11px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: nowrap;"><div style="text-align: left"><span style="line-height: 1.2">push alerts         </span></div><div style="text-align: left"><span style="line-height: 1.2"><br /></span></div><div style="text-align: left"><br /></div></div></div></div></foreignObject><text x="592" y="221" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="11px" text-anchor="middle">push alerts...</text></switch></g><rect x="578" y="240" width="110" height="40" fill="#fff3e6" stroke="#4d4d4d" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 108px; height: 1px; padding-top: 260px; margin-left: 579px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">Web UI</div></div></div></foreignObject><text x="633" y="264" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Web UI</text></switch></g><rect x="578" y="280" width="110" height="40" fill="#ffffff" stroke="#4d4d4d" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 108px; height: 1px; padding-top: 300px; margin-left: 579px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">Grafana</div></div></div></foreignObject><text x="633" y="304" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Grafana</text></switch></g><rect x="578" y="320" width="110" height="40" fill="#ffffff" stroke="#4d4d4d" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 108px; height: 1px; padding-top: 340px; margin-left: 579px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">API clients</div></div></div></foreignObject><text x="633" y="344" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">API clients</text></switch></g><path d="M 578 260 L 516.12 259.96" fill="none" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 509.12 259.95 L 516.12 256.46 L 516.12 263.46 Z" fill="#4d4d4d" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="all"/><path d="M 578 300 L 558 300 L 558 260 L 538 260" fill="none" stroke="#000000" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 578 340 L 558 340 L 558 260 L 538 260" fill="none" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="stroke"/><rect x="478" y="10" width="80" height="30" fill="#ffffff" stroke="#808080" pointer-events="all"/><rect x="478" y="15" width="80" height="20" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 78px; height: 1px; padding-top: 25px; margin-left: 479px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center; max-height: 16px; overflow: hidden;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">PagerDuty</div></div></div></foreignObject><text x="518" y="29" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">PagerDuty</text></switch></g><rect x="568" y="10" width="80" height="30" fill="#ffffff" stroke="#808080" pointer-events="all"/><rect x="658" y="10" width="40" height="30" fill="#ffffff" stroke="#808080" pointer-events="all"/><rect x="588" y="15" width="40" height="20" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 38px; height: 1px; padding-top: 25px; margin-left: 589px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center; max-height: 16px; overflow: hidden;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">Email</div></div></div></foreignObject><text x="608" y="29" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Email</text></switch></g><path d="M 628 110 L 628 48.12" fill="none" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 628 41.12 L 631.5 48.12 L 624.5 48.12 Z" fill="#4d4d4d" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="all"/><rect x="228" y="40" width="150" height="80" fill="#e6f2ff" stroke="#4d4d4d" pointer-events="all"/><g transform="translate(-0.5 -0.5)" opacity="0.8"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe flex-start; width: 169px; height: 1px; padding-top: 79px; margin-left: 211px;"><div data-drawio-colors="color: #4D4D4D; " style="box-sizing: border-box; font-size: 0px; text-align: left; max-height: 91px; overflow: hidden;"><div style="display: inline-block; font-size: 11px; font-family: Helvetica; color: rgb(77, 77, 77); line-height: 1.2; pointer-events: all; white-space: nowrap;"><ul><li><font color="#4d4d4d">DNS</font></li><li><font color="#4d4d4d">Kubernetes</font></li><li><font color="#4d4d4d">Consul</font></li><li><font color="#4d4d4d">...</font></li><li><font color="#4d4d4d">Custom integration</font></li></ul></div></div></div></foreignObject><text x="211" y="82" fill="#4D4D4D" font-family="Helvetica" font-size="11px">DNSKubernetesConsul...Custom in...</text></switch></g><path d="M 628 110 L 628 60 L 518 60 L 518 48.12" fill="none" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 518 41.12 L 521.5 48.12 L 514.5 48.12 Z" fill="#4d4d4d" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="all"/><path d="M 628 110 L 628 60 L 678 60 L 678 48.12" fill="none" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 678 41.12 L 681.5 48.12 L 674.5 48.12 Z" fill="#4d4d4d" stroke="#4d4d4d" stroke-miterlimit="10" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 86px; margin-left: 630px;"><div data-drawio-colors="color: #4D4D4D; " style="box-sizing: border-box; font-size: 0px; text-align: center;"><div style="display: inline-block; font-size: 11px; font-family: Helvetica; color: rgb(77, 77, 77); line-height: 1.2; pointer-events: all; white-space: nowrap;"><div style="text-align: right"><span style="line-height: 1.2">              notify</span></div></div></div></div></foreignObject><text x="630" y="89" fill="#4D4D4D" font-family="Helvetica" font-size="11px" text-anchor="middle">              notify</text></switch></g><rect x="658" y="15" width="40" height="20" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 38px; height: 1px; padding-top: 25px; margin-left: 659px;"><div data-drawio-colors="color: #4D4D4D; " style="box-sizing: border-box; font-size: 0px; text-align: center; max-height: 16px; overflow: hidden;"><div style="display: inline-block; font-size: 11px; font-family: Helvetica; color: rgb(77, 77, 77); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">...</div></div></div></foreignObject><text x="678" y="28" fill="#4D4D4D" font-family="Helvetica" font-size="11px" text-anchor="middle">...</text></switch></g></g><switch><g requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"/><a transform="translate(0,-5)" xlink:href="https://www.diagrams.net/doc/faq/svg-export-text-problems" target="_blank"><text text-anchor="middle" font-size="10px" x="50%" y="100%">Text is not SVG - cannot display</text></a></switch></svg> 

<!-- more -->

### 环境说明

| 操作系统 | 架构 | CPU | 内存 | docker版本 | IP | 部署服务 |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|Ubuntu 24.04 LTS|x86_64|4|8G|28.4.0|192.168.2.201|prometheus server&node exporter|
|Ubuntu 24.04 LTS|x86_64|4|8G|28.4.0|192.168.2.202|node exporter|
|Ubuntu 24.04 LTS|x86_64|4|8G|28.4.0|192.168.2.203|node exporter|
|Ubuntu 24.04 LTS|x86_64|2|4G|28.4.0|192.168.2.204|node exporter|
|Armbian|armv7l|4|1G|28.3.1|192.168.2.243|node exporter|

### 安装prometheus

使用 docker 容器化安装 prometheus。

#### 准备prometheus镜像

首先需要准备镜像，本次从docker官网下载 v3.9.1 版本镜像，打开 github 中克隆的 [DockerTarBuilder](https://github.com/wukongdaily/DockerTarBuilder) 项目，执行 `x86-64 Pull and Save Docker Image` 的Action，参数填写 `prom/prometheus:v3.9.1` ，运行完成后下载镜像文件。

将镜像文件解压出来，使用 MobaXterm 连接到服务器，将 prometheus 镜像文件 `prom_prometheus_v3.9.1-amd64.tar.gz` 上传到服务器上。

执行如下命令加载镜像：

```bash
sudo docker load -i prom_prometheus_v3.9.1-amd64.tar.gz
```

#### 创建配置文件和挂载目录

我的服务器中 docker 相关的数据存放目录是 `/home/wqf31415/docker/data/`，在这个目录中创建目录存放 prometheus 相关数据和配置文件：

```bash
cd /home/wqf31415/docker/data/
sudo mkdir -p prometheus/data
```

创建配置文件：

```bash
vim prometheus/prometheus.yml
```

`prometheus.yml` 内容如下，在初始的配置文件中增加了对 prometheus 自身的监控：

```yaml
global:
  scrape_interval: 15s # 每15秒收集一次指标
  evaluation_interval: 15s # 每15秒评估一次规则

scrape_configs:
  - job_name: 'prometheus' # 第一个抓取任务：监控Prometheus自己
    static_configs:
      - targets: ['localhost:9090']
```

#### 准备docker-compose配置文件

创建 `docker-compose-prometheus.yml` 文件，填写内容如下：

```yaml
services:
  prometheus:
    image: prom/prometheus:v3.9.1
    container_name: prometheus
    user: "root"
    restart: unless-stopped
    network_mode: host
    volumes:
      # 将本地配置文件挂载到容器内，方便修改
      - /home/wqf31415/docker/data/prometheus/prometheus.yml:/etc/prometheus/prometheus.yml
      # 将数据目录挂载出来，确保数据持久化，不随容器删除而丢失
      - /home/wqf31415/docker/data/prometheus/data:/prometheus
    command:
      - '--config.file=/etc/prometheus/prometheus.yml'
      - '--storage.tsdb.path=/prometheus'
      - '--web.console.libraries=/etc/prometheus/console_libraries'
      - '--web.console.templates=/etc/prometheus/consoles'
      - '--storage.tsdb.retention.time=30d' # 可选项：设置数据保留30天
````

#### 启动prometheus容器

运行命令启动容器：

```bash
sudo docker compose -f docker-compose-prometheus.yml up -d
```

查看容器运行状态，状态为 `Up` 说明启动正常：

```bash 
sudo docker ps
```

如果容器运行异常，使用 `sudo docker logs prometheus` 查看日志，分析错误原因。

容器运行正常，可以用浏览器访问服务器的 `9090` 端口，我的访问地址是 http://192.168.2.201:9090，查看 prometheus 页面，在页面的 Status -> Target Health 页面中能看到监控的 prometheus 自身服务，State 为 `UP` 说明监控正常。

![](/images/post/prometheus/prometheus_status.webp "Prometheus状态页面")


### 安装node-exporter

#### 二进制安装

访问官方 github 的发布地址：<https://github.com/prometheus/node_exporter/releases> ，根据操作系统和CPU架构选择合适的版本，我这里根据章节 [环境说明](#环境说明) 中信息选择了 `node_exporter-1.10.2.linux-amd64.tar.gz` 和 `node_exporter-1.10.2.linux-armv7.tar.gz`，可以直接下载后导入到服务器，或者复制文件连接，在服务器上使用 `wget` 下载，我这里复制文件链接，在服务器上下载：

```bash
sudo wget https://github.com/prometheus/node_exporter/releases/download/v1.10.2/node_exporter-1.10.2.linux-amd64.tar.gz
```

解压文件：

```bash 
tar -zxvf node_exporter-1.10.2.linux-amd64.tar.gz
```

创建独立用户，拷贝可执行程序到 `/usr/local/bin` 目录，修改

```bash 
# 创建专用用户（提升安全性）
sudo useradd --no-create-home --shell /bin/false node_exporter

# 复制二进制文件并设置权限
sudo cp node_exporter /usr/local/bin/
sudo chown node_exporter:node_exporter /usr/local/bin/node_exporter
```

配置 Systemd 服务：

```bash
sudo tee /etc/systemd/system/node_exporter.service <<EOF
[Unit]
Description=Node Exporter
Wants=network-online.target
After=network-online.target

[Service]
User=node_exporter
Group=node_exporter
Type=simple
ExecStart=/usr/local/bin/node_exporter

[Install]
WantedBy=multi-user.target
EOF
```

启动 node-exporter：

```bash 
sudo systemctl daemon-reload
sudo systemctl enable node_exporter
sudo systemctl start node_exporter
sudo systemctl status node_exporter  # 确保状态为 active (running)
```

#### docker安装

参考章节 [准备prometheus镜像](#准备prometheus镜像) 从 docker 官方仓库下载镜像 `prom/node-exporter:v1.10.2` ，将镜像导入到需要部署的服务器上。

准备 docker-compose 配置文件 `docker-compose-node-exporter.yml` ，内容如下：

```yaml
services:
  node_exporter:
    image: prom/node-exporter:v1.10.2
    container_name: node_exporter
    restart: unless-stopped
    network_mode: host          # 必须使用 host 网络，否则无法获取宿主机真实指标
    pid: host                  # 允许访问宿主机进程信息
    privileged: true           # 需要特权以读取部分内核指标
    command:
      - '--path.rootfs=/host'  # 指定根文件系统路径
    volumes:
      - '/:/host:ro'    # 将宿主机根目录挂载为只读
```

创建并启动容器：

```bash
sudo docker compose -f docker-compose-node-exporter.yml up -d
```

查看容器启动情况，状态为 `Up` 说明启动正常：

```bash 
sudo docker ps
```

验证 node_exporter 功能：

```bash 
curl http://localhost:9100/metrics
```

### 修改prometheus服务配置

修改 prometheus 服务配置文件 `sudo vim /home/wqf31415/docker/data/prometheus/prometheus.yml`，在 `scrape_configs` 中新增任务配置，内容如下：

```yaml
global:
  scrape_interval: 15s # 每15秒收集一次指标
  evaluation_interval: 15s # 每15秒评估一次规则

scrape_configs:
  - job_name: 'prometheus' # 第一个抓取任务：监控Prometheus自己
    static_configs:
      - targets: ['localhost:9090']

    # 新增：监控服务器
  - job_name: 'linux-server'
    static_configs:
      - targets: ['192.168.2.201:9100']
        labels:
          name: 'ubuntu-01'
          system: 'ubuntu'
          arch: 'x86_64'
      - targets: ['192.168.2.202:9100']
        labels:
          name: 'ubuntu-02'
          system: 'ubuntu'
          arch: 'x86_64'
      - targets: ['192.168.2.203:9100']
        labels:
          name: 'ubuntu-03'
          system: 'ubuntu'
          arch: 'x86_64'
      - targets: ['192.168.2.204:9100']
        labels:
          name: 'ubuntu-04'
          system: 'ubuntu'
          arch: 'x86_64'
      - targets: ['192.168.2.243:9100']
        labels:
          name: 'onecloud'
          system: 'armbian'
          arch: 'armv7l'
```

修改配置文件后，重启 prometheus 容器：

```bash
sudo docker restart prometheus
```

浏览器访问 prometheus 页面的 Status -> Target Health，查看已添加的监控节点状态，State 为 `UP` 说明节点监控正常。


### 安装Grafana可视化监控

#### 创建目录和配置文件

创建容器挂载目录和数据源配置文件：

```bash 
cd /home/wqf31415/docker/data # 进入docker数据目录
sudo mkdir grafana/data
sudo mkdir grafana/provisioning/{datasources,dashboards}
```

在 `provisioning/datasources` 目录中创建 prometheus 数据源配置文件 `prometheus.yaml` 内容如下：

```bash 
apiVersion: 1
datasources:
  - name: Prometheus
    type: prometheus
    access: proxy
    url: http://localhost:9090
    isDefault: true
```

#### 准备grafana镜像

参考章节 [准备prometheus镜像](#准备prometheus镜像) 从 docker 官方仓库下载镜像 `grafana/grafana:main` ，将镜像导入到需要部署的服务器上。

准备 docker-compose 配置文件 `docker-compose-grafana.yml` ，内容如下：

```yaml
services:
  grafana:
    image: grafana/grafana:main
    container_name: grafana
    restart: unless-stopped
    network_mode: host  # 与 Prometheus 保持一致，使用主机网络
    environment:
      # 强制修改 Grafana 的 HTTP 服务端口为 3001（或其他你喜欢的可用端口）
      - GF_SERVER_HTTP_PORT=9091
      # 设置管理员初始密码，请务必在生产环境中修改！
      - GF_SECURITY_ADMIN_PASSWORD=123456
      # （可选）禁止 Grafana 自动尝试使用 3000 端口，避免启动日志报错
      - GF_SERVER_PROTOCOL=http
    user: "root"  # 避免潜在的权限问题，与你的 Prometheus 容器保持一致
    volumes:
      # 持久化存储 Grafana 的所有数据（配置、仪表盘、插件等）
      - /home/wqf31415/docker/data/grafana/data:/var/lib/grafana
      # （可选）如果你想预先配置数据源，可以挂载一个配置文件
      - /home/wqf31415/docker/data/grafana/provisioning:/etc/grafana/provisioning

volumes:
  grafana_data:  # 命名卷，确保数据安全持久
```

> 注：
> 上述 docker-compose 配置文件中环境变量中添加的 `GF_SERVER_HTTP_PORT=9091` 是将 web 访问端口修改成 `9091`，是因为 grafana 默认端口 `3000` 和已有的其他程序冲突了，如果端口不冲突可以删除这个配置。

#### 启动grafana

运行命令创建并启动 grafana 容器：

```bash
sudo docker compose -f docker-compose-grafana.yml up -d
```

浏览器访问 grafana 页面，我这里修改过访问端口，所以访问地址为 <http://192.168.2.201:9091/> ，用户名为 `admin`，密码是配置的 `123456`。

由于在创建容器时添加了 prometheus 的数据源，所以在 grafana 页面的 Connections -> Data sources 页面可以看到名为 `Prometheus` 的数据源。

> 注：如果没有添加数据源配置文件，可以在 Data sources 页面手动添加。

#### 创建可视化监控面板

Grafana 官网提供了很多看板模板，可以复制模板的 ID 或 json 描述数据，导入到本地使用，地址：<https://grafana.com/grafana/dashboards>

进入 grafana 页面的 Dashboards 页面，点击 New -> Import ，模板ID 填写 `1860`，点击 `Load` 加载模板，加载完成后选择已添加的 prometheus 数据源，保存后就可以在 Dashboards 页面查看监控面板。

![](/images/post/prometheus/grafana_dashboards_prometheus.webp "Prometheus 看板")
