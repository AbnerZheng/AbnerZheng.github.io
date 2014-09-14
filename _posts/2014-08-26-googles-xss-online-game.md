---
layout: post
title: "google's xss online game "
description: 
modified: 2014-08-26 10:05:15 +0800
category: 
tags: [xss]
image:
  feature: 19.jpg-clip.jpg
  credit: 
  creditlink: 
comments: true
share: true
alias: [/2014/08/26/google's xss online game ]
---

### 破关记录

最近开始学习xss(Cross Site Script)攻击，在知乎上查到有这个[网站](www.xss-game.appspot.com)(www.xss-game.appspot.com)，配合《白帽子讲web安全》这本书的讲解，算是课后练习啦。将破关的思路方法以及遇到的一些问题，做个记录。
<!--more-->

## Level1: Hello world of XSS
查看Target code,可以看到这个网站是用python在GAE上开发的，在35行注释可以看到，程序人为地将reflect XSS filter关闭了，于是可以想到这关可以用反射型XSS攻击技术解决。

> 反射型XSS： 反射性XSS只是简单地吧用户输入的数据"反射"给浏览器。也叫做“非持久型XSS”(Non-persistent XSS)

所以很简单，在搜索框里输入`<script>alert()</script>`即可。