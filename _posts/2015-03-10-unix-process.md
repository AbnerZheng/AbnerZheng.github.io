---
layout: post
title: "理解Unix进程的nodejs代码实现"
description: 
modified: 2015-03-10 20:36:31 +0800
category: 
tags: [node, unix , process]
image:
  feature: 19.jpg-clip.jpg
  credit: 
  creditlink: 
comments: true
share: true
alias: [/2015/03/10/Unix Process]
---

准备面试中， 重读这本《理解Unix进程》，该书是用ruby作为讲解语言，面向普通没有C语言系统编程的web开发者，正好我准备投入nodejs的怀抱，想着ruby和node都是脚本语言，涉及到系统调用的地方都是一致的，同为脚本语言，接口的相通性应该是有的，所以在第二遍的阅读中，准备以node实现其中的示例代码，以此作为学习。
### 

## 第三章 进程皆有标识

查看进程pid的方法：
{% highlight python %} 
console.log(process.pid);
{% endhighlight %}

<!--more-->
