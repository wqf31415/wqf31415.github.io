---
title: LuckFoxPico联网与搭建Web服务
tags:
- linux
- luckfox
- C
- 开发板
- 硬件
- 嵌入式
- 网络
- web
- web服务
- IoT
categories:
- 嵌入式
date: 2026-03-21 10:18:45
---

### 概述

这篇文章讲述了将 LuckFox Pico 开发板接入网络，以及使用 mongoose 库编译 web 服务，并在 LuckFox Pico 上运行。



### 组网拓扑

<svg xmlns="http://www.w3.org/2000/svg" style="background: transparent; background-color: transparent; color-scheme: light;" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1" width="649px" height="291px" viewBox="0 0 649 291"><defs/><g><g data-cell-id="0"><g data-cell-id="1"><g data-cell-id="W5FYgok1wJqNMqm_KsO0-3"><g transform="translate(0.5,0.5)"><path d="M 175 210 L 175 140" fill="none" stroke="#000000" stroke-miterlimit="10" pointer-events="stroke" style="stroke: rgb(0, 0, 0);"/></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-3"><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 171px; margin-left: 175px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; background-color: #ffffff; "><div style="display: inline-block; font-size: 11px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; background-color: #ffffff; white-space: nowrap; ">数据线</div></div></div></foreignObject><text x="175" y="175" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="11px" text-anchor="middle">数据线</text></switch></g></g></g></g><g data-cell-id="W5FYgok1wJqNMqm_KsO0-1"><g transform="translate(0.5,0.5)"><rect x="130" y="210" width="90" height="30" rx="4.5" ry="4.5" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: rgb(255, 255, 255); stroke: rgb(0, 0, 0);"/></g><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 88px; height: 1px; padding-top: 225px; margin-left: 131px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; white-space: normal; word-wrap: normal; ">LuckFox Pico</div></div></div></foreignObject><text x="175" y="229" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="12px" text-anchor="middle">LuckFox Pico</text></switch></g></g></g><g data-cell-id="W5FYgok1wJqNMqm_KsO0-5"><g transform="translate(0.5,0.5)"><path d="M 175 110 L 175 40" fill="none" stroke="#000000" stroke-miterlimit="10" pointer-events="stroke" style="stroke: rgb(0, 0, 0);"/></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-1"><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 75px; margin-left: 175px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; background-color: #ffffff; "><div style="display: inline-block; font-size: 11px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; background-color: #ffffff; white-space: nowrap; ">网线</div></div></div></foreignObject><text x="175" y="78" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="11px" text-anchor="middle">网线</text></switch></g></g></g></g><g data-cell-id="W5FYgok1wJqNMqm_KsO0-2"><g transform="translate(0.5,0.5)"><rect x="130" y="110" width="90" height="30" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: rgb(255, 255, 255); stroke: rgb(0, 0, 0);"/></g><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 88px; height: 1px; padding-top: 125px; margin-left: 131px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; white-space: normal; word-wrap: normal; ">Windows电脑</div></div></div></foreignObject><text x="175" y="129" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="12px" text-anchor="middle">Windows电脑</text></switch></g></g></g><g data-cell-id="W5FYgok1wJqNMqm_KsO0-7"><g transform="translate(0.5,0.5)"><path d="M 135 20 L 80 20" fill="none" stroke="#000000" stroke-miterlimit="10" pointer-events="stroke" style="stroke: rgb(0, 0, 0);"/></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-2"><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 22px; margin-left: 111px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; background-color: #ffffff; "><div style="display: inline-block; font-size: 11px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; background-color: #ffffff; white-space: nowrap; ">网线</div></div></div></foreignObject><text x="111" y="26" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="11px" text-anchor="middle">网线</text></switch></g></g></g></g><g data-cell-id="W5FYgok1wJqNMqm_KsO0-4"><g transform="translate(0.5,0.5)"><path d="M 155 0 L 195 0 L 215 20 L 195 40 L 155 40 L 135 20 Z" fill="#ffffff" stroke="#000000" stroke-miterlimit="10" pointer-events="all" style="fill: rgb(255, 255, 255); stroke: rgb(0, 0, 0);"/></g><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 78px; height: 1px; padding-top: 20px; margin-left: 136px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; white-space: normal; word-wrap: normal; ">路由器</div></div></div></foreignObject><text x="175" y="24" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="12px" text-anchor="middle">路由器</text></switch></g></g></g><g data-cell-id="W5FYgok1wJqNMqm_KsO0-6"><g transform="translate(0.5,0.5)"><rect x="0" y="0" width="80" height="40" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: rgb(255, 255, 255); stroke: rgb(0, 0, 0);"/></g><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 78px; height: 1px; padding-top: 20px; margin-left: 1px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; white-space: normal; word-wrap: normal; ">Ubuntu主机</div></div></div></foreignObject><text x="40" y="24" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="12px" text-anchor="middle">Ubuntu主机</text></switch></g></g></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-4"><g transform="translate(0.5,0.5)"><path d="M 467 210 L 467 140" fill="none" stroke="#000000" stroke-miterlimit="10" pointer-events="stroke" style="stroke: rgb(0, 0, 0);"/></g></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-6"><g transform="translate(0.5,0.5)"><rect x="422" y="210" width="90" height="30" rx="4.5" ry="4.5" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: rgb(255, 255, 255); stroke: rgb(0, 0, 0);"/></g><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 88px; height: 1px; padding-top: 225px; margin-left: 423px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; white-space: normal; word-wrap: normal; ">LuckFox Pico</div></div></div></foreignObject><text x="467" y="229" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="12px" text-anchor="middle">LuckFox Pico</text></switch></g></g></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-7"><g transform="translate(0.5,0.5)"><path d="M 467 110 L 467 40" fill="none" stroke="#000000" stroke-miterlimit="10" pointer-events="stroke" style="stroke: rgb(0, 0, 0);"/></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-8"><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 75px; margin-left: 467px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; background-color: #ffffff; "><div style="display: inline-block; font-size: 11px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; background-color: #ffffff; white-space: nowrap; ">网线</div></div></div></foreignObject><text x="467" y="78" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="11px" text-anchor="middle">网线</text></switch></g></g></g></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-9"><g transform="translate(0.5,0.5)"><rect x="422" y="110" width="90" height="30" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: rgb(255, 255, 255); stroke: rgb(0, 0, 0);"/></g><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 88px; height: 1px; padding-top: 125px; margin-left: 423px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; white-space: normal; word-wrap: normal; ">Type-C转网口</div></div></div></foreignObject><text x="467" y="129" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="12px" text-anchor="middle">Type-C转网口</text></switch></g></g></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-10"><g transform="translate(0.5,0.5)"><path d="M 427 20 L 370 20" fill="none" stroke="#000000" stroke-miterlimit="10" pointer-events="stroke" style="stroke: rgb(0, 0, 0);"/></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-11"><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 22px; margin-left: 402px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; background-color: #ffffff; "><div style="display: inline-block; font-size: 11px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; background-color: #ffffff; white-space: nowrap; ">网线</div></div></div></foreignObject><text x="402" y="26" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="11px" text-anchor="middle">网线</text></switch></g></g></g></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-15"><g transform="translate(0.5,0.5)"><path d="M 507 20 L 557 20" fill="none" stroke="#000000" stroke-miterlimit="10" pointer-events="stroke" style="stroke: rgb(0, 0, 0);"/></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-16"><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 20px; margin-left: 537px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; background-color: #ffffff; "><div style="display: inline-block; font-size: 11px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; background-color: #ffffff; white-space: nowrap; ">网线</div></div></div></foreignObject><text x="537" y="24" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="11px" text-anchor="middle">网线</text></switch></g></g></g></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-12"><g transform="translate(0.5,0.5)"><path d="M 447 0 L 487 0 L 507 20 L 487 40 L 447 40 L 427 20 Z" fill="#ffffff" stroke="#000000" stroke-miterlimit="10" pointer-events="all" style="fill: rgb(255, 255, 255); stroke: rgb(0, 0, 0);"/></g><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 78px; height: 1px; padding-top: 20px; margin-left: 428px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; white-space: normal; word-wrap: normal; ">路由器</div></div></div></foreignObject><text x="467" y="24" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="12px" text-anchor="middle">路由器</text></switch></g></g></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-13"><g transform="translate(0.5,0.5)"><rect x="290" y="0" width="80" height="40" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: rgb(255, 255, 255); stroke: rgb(0, 0, 0);"/></g><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 78px; height: 1px; padding-top: 20px; margin-left: 291px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; white-space: normal; word-wrap: normal; ">Ubuntu主机</div></div></div></foreignObject><text x="330" y="24" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="12px" text-anchor="middle">Ubuntu主机</text></switch></g></g></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-17"><g transform="translate(0.5,0.5)"><path d="M 602 140 L 602 225 L 512 225" fill="none" stroke="#000000" stroke-miterlimit="10" pointer-events="stroke" style="stroke: rgb(0, 0, 0);"/></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-21"><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 185px; margin-left: 602px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; background-color: #ffffff; "><div style="display: inline-block; font-size: 11px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; background-color: #ffffff; white-space: nowrap; ">杜邦线</div></div></div></foreignObject><text x="602" y="188" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="11px" text-anchor="middle">杜邦线</text></switch></g></g></g></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-20"><g transform="translate(0.5,0.5)"><path d="M 602 35 L 602 110" fill="none" stroke="#000000" stroke-miterlimit="10" pointer-events="stroke" style="stroke: rgb(0, 0, 0);"/></g></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-14"><g transform="translate(0.5,0.5)"><rect x="557" y="5" width="90" height="30" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: rgb(255, 255, 255); stroke: rgb(0, 0, 0);"/></g><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 88px; height: 1px; padding-top: 20px; margin-left: 558px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; white-space: normal; word-wrap: normal; ">Windows电脑</div></div></div></foreignObject><text x="602" y="24" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="12px" text-anchor="middle">Windows电脑</text></switch></g></g></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-18"><g transform="translate(0.5,0.5)"><rect x="557" y="110" width="90" height="30" fill="#ffffff" stroke="#000000" pointer-events="all" style="fill: rgb(255, 255, 255); stroke: rgb(0, 0, 0);"/></g><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 88px; height: 1px; padding-top: 125px; margin-left: 558px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; white-space: normal; word-wrap: normal; ">USB转TTL</div></div></div></foreignObject><text x="602" y="129" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="12px" text-anchor="middle">USB转TTL</text></switch></g></g></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-22"><g transform="translate(0.5,0.5)"><rect x="70" y="260" width="130" height="30" fill="none" stroke="none" pointer-events="all"/></g><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 128px; height: 1px; padding-top: 275px; margin-left: 71px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; white-space: normal; word-wrap: normal; ">方式一：共享电脑网络</div></div></div></foreignObject><text x="135" y="279" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="12px" text-anchor="middle">方式一：共享电脑网络</text></switch></g></g></g><g data-cell-id="aeIFG-fnVNL3SueNQPq8-23"><g transform="translate(0.5,0.5)"><rect x="410" y="260" width="130" height="30" fill="none" stroke="none" pointer-events="all"/></g><g><g><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 128px; height: 1px; padding-top: 275px; margin-left: 411px;"><div style="box-sizing: border-box; font-size: 0; text-align: center; color: #000000; "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: #000000; line-height: 1.2; pointer-events: all; white-space: normal; word-wrap: normal; ">方式二：USB扩展网卡</div></div></div></foreignObject><text x="475" y="279" fill="light-dark(#000000, #ffffff)" font-family="Helvetica" font-size="12px" text-anchor="middle">方式二：USB扩展网卡</text></switch></g></g></g></g></g></g></svg> 

<!-- more -->

### 物料

#### 设备

|        设备         | 操作系统  |            系统版本            |       IP        |                  备注                   |
| :-----------------: | :-------: | :----------------------------: | :-------------: | :-------------------------------------: |
|         PC          |  Windows  |               11               |  192.168.2.176  |      用于烧录系统与远程访问开发板       |
| LuckFox Pico 开发板 | Buildroot | -g2ae728b52-dirty（2023.02.6） | 192.168.137.100 | 开发板，已经插入烧录Buildroot镜像的SD卡 |
|     Ubuntu主机      |  Ubuntu   |           24.04 LTS            |  192.168.2.190  |     编译系统镜像；完成C代码交叉编译     |

#### 软件

|         软件         |  版本  |            用途            |                           下载链接                           |
| :------------------: | :----: | :------------------------: | :----------------------------------------------------------: |
| Android Debug Bridge | 1.0.41 |     通过USB连接开发板      | [adb_fastboot.zip](https://files.luckfox.com/wiki/Luckfox-Pico/Software/adb_fastboot.zip) |
|      MobaXterm       | v22.0  | 远程连接开发板与Ubuntu主机 | [MobaXterm_Portable_v22.0.zip](https://wiki.luckfox.com/Tools/MobaXterm_Portable_v22.0.zip) |

#### 其他物料

|         物料         |   参数   | 数量 |                       备注                       |
| :------------------: | :------: | :--: | :----------------------------------------------: |
|         电源         |  5V直流  |  1   |                   给开发板供电                   |
|        交换机        | 八孔千兆 |  1   |             让电脑、开发板接入局域网             |
| Type-C转网口有线网卡 |   百兆   |  1   |       插在开发板，为开发板提供有线联网功能       |
|     USB转TTL模块     |  CH340   |  1   |                通过串口访问开发板                |
|     Type-C数据线     |   1米    |  1   |                将开发板连接到PC上                |
|         网线         |   1米    |  1   |             连接Type-C 网卡到交换机              |
|        杜邦线        |    -     |  6   | 连接USB转TTL模块；连接电源和开发板，给开发板供电 |

### LuckFox Pico接入网络

#### 方式一：USB共享电脑网络（RNDIS）

使用 Windows 电脑网络共享，让开发板的网络共享使用电脑网络，这样就可以让开发板连接到局域网和公网，这是最简单的联网方式，但是局域网访问开发板会有点麻烦。

##### 使用 ADB 连接开发板

通过 ADB 方式可以直接使用数据线访问开发板，而且不需要输入密码，当开发板因为一些问题（ IP 配置错误）无法使用 ssh 访问时，可以使用这种方式。

> 参考官网文档：[登录 | LUCKFOX WIKI](https://wiki.luckfox.com/zh/Luckfox-Pico-Plus-Mini/Login)

下载 [adb_fastboot.zip](https://files.luckfox.com/wiki/Luckfox-Pico/Software/adb_fastboot.zip) 并解压到本地，记录存放路径，比如 `D:\luckfox\adb_fastboot` ，将路径添加到系统环境变量 path 中。

![](/images/post/luckfox/env_path_cfg.webp) 

打开命令行窗口，运行命令如下命令，能打印出软件版本信息说明配置正确：

```powershell
adb version
```

用数据线将开发板连接到 Windows 电脑，等待开发板启动完成后（约30秒），在命令行窗口执行如下命令查看已接入的设备信息：

```powershell
adb devices
```

输入如下，说明设备连接成功：

```
List of devices attached
b8319ff24268c8a4        device
```

当只有一个设备时，执行如下命令连接：

```cmd
adb shell
```

当有多个设备时，要添加 `-s` 参数指定连接的设备的序列号：

```cmd
 adb -s b8319ff24268c8a4 shell
```

连接成功后，界面显示如下，就可以输入指令和开发板交互了，如执行 `ip addr` 查看开发板 IP 地址。

```
[root@luckfox ]#
[root@luckfox ]# ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
2: usb0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast qlen 1000
    link/ether e2:c3:a2:f0:aa:37 brd ff:ff:ff:ff:ff:ff
    inet 192.168.137.100/24 brd 192.168.137.255 scope global usb0
       valid_lft forever preferred_lft forever
```

##### 配置电脑网络共享

找到 LuckFox Pico 使用的网卡：当用数据线把 LuckFox Pico 开发板连接到电脑后，会出现一个新的网络设备，通常名为“**Remote NDIS based Internet Sharing Device**”或类似名称，在Windows的“网络连接”面板中，找到这个对应的网卡，它可能显示为“**以太网 X**”。

在“网络连接”面板中，找到电脑**正在用来上网**的那张网卡，右键点击它，选择 **“属性”** -> **“共享”** 选项卡。

> 如下图所示：
>
> - 开发板的网卡是 `以太网 3` 
> - 电脑上网的网卡是 `以太网` 

![](/images/post/luckfox/net_adapter.webp) 

勾选 **“允许其他网络用户通过此计算机的 Internet 连接来连接”**，在“家庭网络连接”下拉框中，**选择第一步中识别出的、代表Luckfox Pico的那张虚拟网卡**（例如我的是“以太网 3”）

![](/images/post/luckfox/net_share.webp) 

点击“确定”，Windows会自动为这张虚拟网卡设置一个固定IP：`192.168.137.1`

##### 设置开发板网络

通过 ADB 登录到 LuckFox Pico开发板，将开发板的USB虚拟网卡（通常是`usb0`）配置到与Windows共享网卡相同的网段。

可以逐条执行如下命令设置开发板 IP：

```sh
# 为 usb0 接口设置一个与 Windows 共享网卡同网段的 IP
# 注意：不能使用 192.168.137.1，这个已被电脑占用
ifconfig usb0 192.168.137.100 netmask 255.255.255.0
# 添加默认网关，指向 Windows 共享网卡的 IP
route add default gw 192.168.137.1
# 设置 DNS 服务器，用于域名解析（如 ping baidu.com）
echo "nameserver 114.114.114.114" > /etc/resolv.conf
```

> **注意**：这种方式配置的 IP 会在重启后失效，如果需要持久化，需要编写开机启动脚本，参考官网教程[自启动配置 | LUCKFOX WIKI](https://wiki.luckfox.com/zh/Luckfox-Pico-Plus-Mini/Autostart)，在系统启动时自动修改IP配置：
>
> 在 `/etc/init.d/` 目录下新增并编辑配置静态路由的脚本文件，命名为`S99z_static_ip` （确保该命名在系统脚本之后）
>
> ```sh
> vi /etc/init.d/S99z_static_ip
> ```
>
> 内容如下：
>
> ```sh
> #!/bin/sh
> case $1 in
>   start)
>       ifconfig usb0 192.168.137.100 netmask 255.255.255.0
>       route add default gw 192.168.137.1
>       echo "nameserver 114.114.114.114" > /etc/resolv.conf
>       ;;
>   stop)
>       ;;
>   *)
>       exit 1
>       ;;
> esac
> ```
>
> 给脚本添加可执行权限：
>
> ```sh
> chmod +x /etc/init.d/S99z_static_ip
> ```

在开发板上尝试 ping 局域网其他主机或百度域名 `www.baidu.com` ，能够ping通，说明网络配置成功。

![](/images/post/luckfox/pico_ping_other.webp) 



#### 方式二：USB扩展有线网卡

通过 Type-C 网卡设备，给开发板提供一个网口，连接到局域网交换机或路由器即可上网，注意需要单独提供电源给开发板供电。

##### 编译系统镜像

由于购买的 USB 网卡的芯片是 Realtek RTL8152，从 LuckFox 官网下载的 buildroot 镜像内核没有带有这个网卡驱动，导致无法识别网卡，需要使用官方 SDK 自己编译系统镜像。

当开发板 USB 模式切换到 host 并重启后，连接到 USB 网卡接入网络，发现无法联网，可以通过如下方式排查：

- 检查 USB 模式：`cat /sys/devices/platform/ff3e0000.usb2-phy/otg_mode` ，输出 `peripheral` 说明没有切换到 host 模式，需要使用 `luckfox-config` 配置，参考下一章节

- 检查 USB 设备识别情况：`lsusb` ，看下是否识别到USB设备，如下输出第二行的 `ID 0bda:8152` 说明已经识别到了 8152 的USB设备

  ```
  Bus 001 Device 001: ID 1d6b:0002
  Bus 001 Device 002: ID 0bda:8152
  Bus 002 Device 001: ID 1d6b:0003
  ```

- 检查内核是否包含 RTL8152 驱动模块（如果驱动是编译进内核的，这里不会有输出，但我们可以通过其他方式确认）：

  ```bash
  lsmod | grep r8152
  ```

- 查看内核日志中关于 RTL8152 的信息：

  ```bash
  dmesg | grep -i r8152
  ```

  **如果没有任何输出说明没有 RTL8152 驱动，就需要自己编译带这个驱动的镜像**；如果输出如下内容说明已经有驱动了，但是未识别到版本号，给开发板下电重新上电试试：

  ```
  [    0.585603] r8152 1-1:2.0: Unknown version 0x0000
  ```

  如果正确识别到了网卡，将会输出版本号：

  ```
  [    0.991747] r8152 1-1:1.0: skip request firmware
  [    1.032188] r8152 1-1:1.0 eth0: v1.11.11
  ```

  

> SDK 镜像编译，参考官方文档：<https://wiki.luckfox.com/zh/Luckfox-Pico-Plus-Mini/SDK-Image-Compilation> 

操作步骤：

从 getee 克隆下载源码：

```bash
git clone https://gitee.com/LuckfoxTECH/luckfox-pico.git
```

安装编译环境依赖：

```bash
sudo apt-get install -y git ssh make gcc gcc-multilib g++-multilib module-assistant expect g++ gawk texinfo libssl-dev bison flex fakeroot cmake unzip gperf autoconf device-tree-compiler libncurses5-dev pkg-config bc python-is-python3 passwd openssl openssh-server openssh-client vim file cpio rsync curl
```

进入源码目录：

```sh
cd luckfox-pico
```

进入内核源码目录：

```sh
cd sysdrv/source/kernel
```

**使用 menuconfig 图形界面配置内核，启用 RTL8152 驱动**:

先加载默认配置：

```sh
make ARCH=arm luckfox_rv1106_linux_defconfig
```

打开图形配置界面：

```sh
make ARCH=arm menuconfig
```

![](/images/post/luckfox/menuconfig_ui.webp) 

在 menuconfig 界面中，按以下路径找到 RTL8152 驱动：

> menuconfig 图形界面操作方式：
>
> - 用 **上下箭头** 移动光标
> - 按 **空格键** 选中（显示 `*` 表示编译进内核，推荐）
> - 按 **Y** 直接选中，按 **N** 取消
> - 确认后按 **Esc** 退出，最后选择 **Save** 保存配置

```
Device Drivers  --->
    Network device support  --->
        USB Network Adapters  --->
            [*]   Realtek RTL8152/RTL8153 Based USB Ethernet Adapters
```

![](/images/post/luckfox/menuconfig_rtl8152.webp) 

配置完成后，执行下面命令验证配置是否正确，如果输出 `CONFIG_USB_RTL8152=y`，说明配置成功。

```sh
grep RTL8152 .config
```

回到 SDK 根目录，执行下述命令，选择版型、启动介质、系统配置：

```sh
./build.sh lunch
```

> 我这里选择如下（第一个选了 Pico 后面两个就只有一个选择了）：
>
> - 硬件版本：`[0] RV1103_Luckfox_Pico` 
> - 启动媒介：`[0] SD_CARD`
> - 系统版本：`[0] Buildroot` 

开始编译，我电脑性能一般，编译耗时约 3 小时：

```bash
./build.sh
```

![](/images/post/luckfox/compile_pico_firmware.png) 

编译完成后，生成的镜像文件存放在 `output/image/` 目录下，打包下载到本地，然后用 [SocToolKit](https://wiki.luckfox.com/Tools/SocToolKit_v1.98_win.zip) 软件烧录到SD卡上，插回开发板，上电启动。



##### 修改 USB 模式为 host

开发板 usb 默认是 device 模式，可以通过数据线将开发板连接到电脑，使用 adb 访问。

现在需要将开发板 usb 连接到有线网卡，需要先把开发板 usb 模式修改为 host 模式：

```bash
luckfox-config
```

进入 `Advanced Options` - `USB` ，选择 host，保存，重启生效。

> **注意：usb 设置成 host 模式将导致无法使用 adb 连接，如果IP设置也有问题，就只能使用串口访问了。** 

通过串口连接到开发板后，执行如下命令可查看当前 usb 工作模式，如果输出 `host` 说明配置正确：

```bash
cat /sys/devices/platform/ff3e0000.usb2-phy/otg_mode
```



##### 使用串口连接开发板

在网上购买一个 USB 转 TTL 模块（十几块钱），用来连接开发板查看网口信息，同时用来给开发板供电。

接线方式：

> 可以参考官方文档：<https://wiki.luckfox.com/zh/Luckfox-Pico-Plus-Mini/Login#25-串口登录> 
>
> 注意：这里和官方连线不同，我们要使用 TTL 模块给开发板供电，所以将 USB 转 TTL 模块的 `5V` 输出引脚连到了开发板的供电引脚 `VBUS` 。

| USB 转 TTL | LuckFox Pico |
| :--------: | :----------: |
|     5V     |     VBUS     |
|    GND     |     GND      |
|     TX     |      RX      |
|     RX     |      TX      |

连好线后将 USB 转 TTL 模块插入电脑，打开 MobaXterm ，新建 Session 选择 Serial 串口类型：

- 串口端口 Serial port 选择连接开发板的串口，如 `COM3 (USB-SERIAL CH340(COM3))` 
- 波特率 Speed(bps) 选 `115200` 
- 在 Advanced Serial Settings中配置：
  - Serial engine：PuTTY
  - Data bits：8
  - Stop bits：1
  - Parity：None
  - Flow control：None

点击 OK 建立连接。

![](/images/post/luckfox/MobaXterm_serial_cfg.webp) 



##### 独立电源供电

当开发板调试好，可以使用有线网口接入网络后，建议使用独立电源给开发板供电，不再依赖电脑。

将直流电源设置为 5V 1A，正极连接到开发板 `VBUS` 引脚，负极连接到开发板 `GND` 引脚，启动电源即可自动启动开发板。

 

### 搭建web服务

#### web服务开发

> Mongoose 是一个开源的嵌入式设备的 Web 服务器项目，可作为嵌入式设备网络库，使用 C 语言开发。
>
> Github 地址：<https://github.com/cesanta/mongoose> 

从 GitHub 克隆 mongoose 项目源码：

```bash
git clone https://github.com/cesanta/mongoose.git
```

创建 web 服务项目目录，从源码仓库根目录复制 `mongoose.h` 、`mongoose.c` 到 web 服务项目目录，创建 `main.c` 文件，实例代码将在 `8000` 端口开启 web 服务，代码内容如下：

```c
#include <stdio.h>
#include "mongoose.h"

static const char *s_http_addr = "http://0.0.0.0:8000"; // 在 8000 端口监听 HTTP 请求
static const char *s_root_dir = "web_root";

static void fn(struct mg_connection *c, int ev, void *ev_data) {
  if(ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    if(mg_match(hm->uri, mg_str("/hello"), NULL)) {
      // 解析查询参数中的 name 字段，并返回 JSON 格式的响应
      char name[64] = {0};
      mg_http_get_var(&hm->query, "name", name, sizeof(name));
      mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"msg\":\"hello %s!\"}", name);
    } else {
      // 其他请求，返回静态文件
      struct mg_http_serve_opts opts = {.root_dir = s_root_dir};
      mg_http_serve_dir(c, ev_data, &opts);
    }
  }
}

int main(void) {
  struct mg_mgr mgr;
  mg_log_set(MG_LL_DEBUG);
  mg_mgr_init(&mgr);
  mg_http_listen(&mgr,s_http_addr, fn, NULL);
  for (;;) mg_mgr_poll(&mgr, 1000);
  mg_mgr_free(&mgr);
  return 0;
}
```

在 web 服务目录中创建 `web_root` 目录，用于存放前端文件 `index.html` ，文件内容如下：

```html
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Hello World</title>
</head>
<body>
    <h1>hello world</h1>
</body>
</html>
```

#### 编译部署

编译项目源码：

```bash
arm-rockchip830-linux-uclibcgnueabihf-gcc main.c mongoose.c -o web
```

将 web 服务资源和可执行文件打包成 tar 包：

> 开发板的 tar 命令不支持解压 .gz 文件，所以只能打包成 tar 包。

```bash
tar -cf web_server.tar web web_root/
```

导出 tar 包并上传到开发板，解压 tar 包，运行 web 服务：

```bash
tar -xf web_server.tar
./web
```

#### 访问服务

##### 共享电脑网络方式

在 Windows 电脑上打开浏览器，访问开发板 8000 端口的 web 服务：<http://192.168.137.100:8000/> ，显示 web 服务的主页 index.html。

![](/images/post/luckfox/pico_web_index.webp) 

访问web服务的接口，传入name 参数，<http://192.168.137.100:8000/hello?name=LuckFox> ，返回接口响应 json 数据：

```json
{"msg":"hello LuckFox!"}
```

现在在 Windows 电脑上可以访问开发板上的 web 服务了，如果想要让局域网其他设备访问，可以在 Windows 电脑上使用 ssh 建立和开发板的隧道：

```bash
ssh -N -L 192.168.2.176:8080:192.168.137.100:8000 root@192.168.137.100
```

>命令说明：这个 `ssh` 命令用于建立一个 **SSH 隧道**，实现**本地端口转发**，将本地机器上的一个端口（8080）通过 SSH 连接转发到远程主机上的另一个端口（8000）。
>
>具体参数说明：
>
>- **`ssh`**：SSH 客户端命令，用于建立安全的远程连接。
>- **`-N`**：表示**不执行远程命令**。仅建立连接并用于端口转发，不打开远程 shell 或执行任何命令。
>- **`-L`**：指定**本地端口转发**（Local Forwarding）。其语法为 `[bind_address:]port:host:hostport`，含义是：将本地（或指定接口）的 `port` 上的流量，通过 SSH 隧道转发到远程主机（即 SSH 服务器）所见的 `host:hostport`。
>- **`192.168.2.176:8080:192.168.137.100:8000`**：这是 `-L` 的参数，具体含义：
>  - `192.168.2.176:8080`：在本地机器上，监听 IP 地址为 `192.168.2.176`（这是一个本地网络接口）的 **8080 端口**。这意味着只有从该 IP 地址访问本地 8080 端口的连接才会被转发。
>  - `192.168.137.100:8000`：通过 SSH 隧道，将流量转发到远程主机（即 SSH 服务器）所能访问到的 `192.168.137.100` 的 **8000 端口**。
>- **`root@192.168.137.100`**：指定登录到远程 SSH 服务器，用户名为 `root`，服务器地址为 `192.168.137.100`。

其他设备可以访问 <http://192.168.2.176:8080> 来访问开发板上的 web 服务。



##### USB 网卡联网方式

开发板通过 Type-C 转网口线接入局域网路由器，使用 DHCP 自动获取到 IP 后，在局域网中直接通过开发板 IP 访问其中提供的 web 服务。

开发板 IP 可以通过串口登录到开发板查看：

```sh
ip addr show
```

输出结果：

```
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast qlen 1000
    link/ether 00:e0:4a:16:8a:6e brd ff:ff:ff:ff:ff:ff
    inet 192.168.2.132/24 brd 192.168.2.255 scope global eth0
       valid_lft forever preferred_lft forever
```

这里的 `eth0` 就是我们 USB 网卡，IP 是 `192.168.2.132` ，启动 web 服务器后，访问 <http://192.168.2.132:8000> 就可以打开 web 服务。

![](/images/post/luckfox/pico_web_index_2.webp) 



### 总结

- 通过共享主机网络，可以让开发板通过数据线接入到网络，能够访问局域网和公网。但是要让局域网其他设备访问开发板不太容易，我在 Windows 电脑上配置路由转发，但是没有生效。
- 使用 USB 网卡通过有线方式将 LuckFox Pino 连入网络，但需要单独提供电源，通过 VBUS、GND 引脚供电。
-  USB 网卡联网方式，需要把开发板 USB 模式改成 host 模式，让开发板成为 “主机”，来连接其他 USB 设备，如 USB 网卡、鼠标、键盘等。与之相对的是 **Device（从机）模式**，此时开发板自己充当一个 USB 设备（例如被电脑识别为虚拟网卡或存储设备）。
- 开发板 USB 设置成 host 模式后，电脑就无法通过数据线连接访问开发板了，只能通过串口连接，如果没有 USB 转 TTL 模块，想该回去就只能重新烧录镜像了。
- 网上买的 Type-C 转网口线没说明是用的什么芯片，查了资料才知道是  RTL8152，但LuckFox 官方提供的 buildroot 镜像不带有 RTL8152 驱动，可以下载 SDK 自己编译带  RTL8152 驱动的固件镜像。
- 编译固件的电脑是 Ubuntu 24.04，编译过程很顺利，没有报错，就是全部编译时间太久了。
- 我第一次编译的固件有问题，烧录运行后还是没有运行  RTL8152 驱动，怀疑是编译内核的配置没有生效，重新编译的时候，我选择了只编译内核，得到 `boot.img` ，替换第一次编译的镜像文件，这样只需要几分钟，大大节约了编译时间。
