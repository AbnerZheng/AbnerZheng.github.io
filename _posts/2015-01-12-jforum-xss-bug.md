---
layout: post
title: "JForum XSS Bug"
description: 
modified: 2015-03-12 14:06:46 +0800
category: 
tags: [XSS, JForum]
image:
  feature: 19.jpg-clip.jpg
  credit: 
  creditlink: 
comments: true
share: true
alias: [/2015/01/12/JForum XSS Bug]
---

### 引言

我们专业有一个云论坛，就构架于JForum之上。在看过一些Web安全书籍和文章之后，我想自己是否能将学到的XSS知识运用到实际中去。所以在老师的同意之后，就选择云论坛作为漏洞查找对象。

<!--more-->

JForum是一个比较成熟的论坛框架，版本已经到3了，在进行了一些手工尝试之后，我就不得不放弃，转去google上查找漏洞，所幸，著名安全研究机构SEC Consult发布文件CVE-2013-3053，指出JForum的一个XSS漏洞，同时由于JForum社区并没有修复这个漏洞，CVE-2013-3053文档中，将漏洞证明给删去了，于是，我只能根据网上的一篇自称提供漏洞修复方法的博文[9]做逆向分析（事实证明该文章提供的漏洞修复是错误的）。

##漏洞分析

JForum支持BBCode，BBCode常用于BBS、Blog等网络应用，有便利，安全等特点。
JForum对BBCode的支持是通过BBCodeHandler.java实现的，从下面的代码可以看到，JForum从文件系统中读入bb_config.xml文件。
 
![图5 BBCodeconfig代码段](\images\post\BBCodeconfig.jpg)

bb_config.xml文件中是一堆正则替换配置项，如
 

![图6 bb_config.xml中BBCode正则替换项示例](\images\post\BBconfig.jpg)

每个正则替换项都由一个正则表达式、一个替换规则给出，如匹配color的正则表达式为：

~~~
(?s)(?i)\[color=['"]?(.*?[^'"])['"]?\](.*?)\[/color\] 
~~~

前面的(?s)和(?i)表示空格和匹配忽略大小写。其相应的替换规则为：

~~~
<font color='$1'>$2</font>                                     
~~~

替换规则即将(.*?[^'"])匹配到的内容替换到 $1
(.*?)匹配到的内容替换到$2中，如：当输入

[color=red'style='top:0px;left:0px;position:absolute;font-size:100;' /onMouseOver='alert(document.cookie)']XSS By Abner[/color]

这行代码后，正则匹配的内容为:
 
![图7 正则匹配结果](\images\post\regmatch.jpg)

~~~
将匹配到内容替换到$1和$2中，其替换结果为：
~~~

{% highlight html %}
<font color='red' style='top:0px;left:0px;position:absolute;font-size:> 
 100;' onmouseover='alert("hello world";)'>XSS By Abner</font> 
{% endhighlight %}

跟踪代码，这个post会经历一系列JForum的防XSS措施，下面介绍JForum的防御XSS的方法。

当用户在浏览器输入上面的内容之后，点击post，该内容就会发送到服务器中，由PostCommon.java进行处理，如果发表时没有选择允许HTML的话，迎接这串内容的首先是一轮的输入检查：
 
![图8 第一轮输入检查](\images\post\firrunxss.jpg)

这轮检查会将文章中的所有"<"、">" 替换成HTML Entity代码，再保存到节点中去。之后，这串内容将进入SafeHtml类的管辖，SafeHtml是JForum框架针对XSS的主防线。SafeHtml主要做了些什么呢？进行输出检查！和输入检查一样，也是将"<"、">"、'"'替换成HTML Entity代码。
 
![图9 输入检查代码替换](\images\post\tworunxss.jpg)

回顾这两层输入输出检查，可以看到我们在前面输入的代码由于都不包含"<"、">"、'"'，所以就躲过了JForum的防御。

然后就进入JForum的第三个步骤，解析BBCode。其基本思路如上面所说，就是将输入内容按BBCode的正则替换规则，一项一项地替换。这样输入的代码就会被解析为：

{% highlight html %}
<font color='red' style='top:0px;left:0px;position:absolute;font-size:100;' 
onmouseover='alert("hello world";)'>XSS By Abner</font> 
{% endhighlight %}

接下来JForum就没有任何防御措施，这段代码就这样一马平川地被输出。于是，我们就完成了一次持久型XSS攻击，植入了一个onmouseover响应事件，当用户的鼠标移动到这行字时，就会执行alert("hello world";).

## 漏洞修复方法

在发现漏洞以及分析完原因之后，自然就会想如何填上这个漏洞。前面说到，这个漏洞是安全研究机构SEC Consult发布的，而JForum社区并没有填上这个漏洞，所以只能自己尝试方法解决。

显然问题处在了BBCode上，最简单的办法就是禁止用户使用BBCode或者禁用BBCode中color标签，然而，这种方法会使用户体验性下降，不是良策。后来分析BBCode_cofig.xml中的正则项，发现了一个较为简单的修补方法。

分析color的正则匹配，出问题的是(.*)，

将

~~~
(?s)(?i)\[color=['"]?(.*?[^'"])['"]?\](.*?)\[/color\]                          
~~~

改成：

~~~
(?s)(?i)\[color=['"]?([^'"]?[^'"])['"]?\](.*?)\[/color\]                       
~~~

即将所有的单引号双引号都设为非法不匹配。最后经本地测试，**确实**在保证color标签功能的前提下填补了这个漏洞。

##总结

在Web开发中，安全是一个很重要的议题，强调安全是很有必要的。本文介绍了XSS的原理，然后就JForum的一个漏洞进行分析，并分析了JForum这类框架对XSS的防御措施，最后给出了漏洞填补方法。
我希望能够通过这个案例，能让大家认识到了XSS攻击的强大，以及XSS防御的必要性，从而在今后的开发编码中，尽早对这些攻击进行一些防御，并且在平常，多多注意所用框架的漏洞报告，尽早打上漏洞补丁。

