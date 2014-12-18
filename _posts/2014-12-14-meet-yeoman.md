---
layout: post
title: "Meet Yeoman "
description: 
modified: 2014-12-14 20:04:49 +0800
category: 
tags: [front end, automate workflow]
image:
  feature: 19.jpg-clip.jpg
  credit: 
  creditlink: 
comments: true
share: true
alias: [/2014/12/14/Meet Yeoman ]
---

### 前记
今天花了半天的时间体验了下Yeoman，不得不说这是很好的一套前端自动化开发workflow，相当棒，值得大家拥有。

<!--more-->

## Yeoman 介绍
Yeoman是一个能够帮助管理、提高效率的工具，他集成了Grunt和Bower的特长，以Generator的形式帮助我们快速搭建框架、自动测试、自动压缩等等。官网现有1300多个[Generator](http://yeoman.io/generators/)，基本上想得到的框架都涵盖了。

Yeoman的官网上有一个[Tutorial](http://yeoman.io/codelab.html)，我花了一个下午搭建环境、编写demo，收获颇多，建议大家也可以去看看。Yeoman还有一个云IDE，如果不想搭建环境，可以先用它尝试使用一下。

## 搭建环境碰到的一些坑
由于我在前端比较喜欢使用windows的开发环境，而windows系统在这些开源工具及框架下碰到坑完全是常事，只能百度+google了。

Yeoman要求nodejs的版本高于0.10.x、npm版本高于2.1.0, nodejs没啥问题，微软和node的合作还是很不错的。但是node自带安装的npm版本确实1.33的，以为是nodejs版本不够新，遂下载一个全新的msi发布版，结果还是没高过2.0。在github的一个wiki上找到解决方法，用npm全局安装npm，然后再将nodejs安装目录下的npm和npm.cmd文件给删了。

第二个坑是git，我一直用的是git shell（Github家的产品,感觉是powershell配了些常数)，然后npm默认安装的路径是C盘下的Roaming文件夹，需要管理员权限才能执行，然而git shell没法给它管理员权限，然后就悲剧了，最后只能换到git bash，忍受搓比的响应速度和体验。。。

除这之外应该就没有什么问题了，其他诸如ruby家的compass之类的，安装都会很顺利。（其实这些我很早前就转好了，不保证忘了当时可能会遇到的坑）

##  命令总结
输入yo，可以弹出一个简单交互的命令行选择器，如下:
![yo命令行](\images\post\yo.jpg)

首先赞下nodejs的命令行交互和配色，真心棒！

然后可以在这个命令下完成安装、更新、运行generator。

在tutorial中，采用的是Angular的generator，这个generator提供了一套grunt命令，忘了命令的话，大家可以打开Gruntfile.js看下，这些工具给我的感觉都很像Makefile。

当运行yo angular之后，yo就运行这个generator，然后就调用bower和npm安装依赖包，之后我们通过grunt管理这些文件。基本流程就是这样了。

文件夹结构：
![文件结构](\images\post\folderStru.jpg)

其中app文件夹存放的就是我们的程序，而dist文件夹存放的是自动压缩之后的部署程序。

### 运行服务器

~~~
$ grunt serve
~~~

自带自动监视文件修改，当修改源程序之后，打开的浏览器会自动刷新。

### bower 管理js依赖文件

查看已安装的js包文件:

~~~
$ bower list
~~~

查找需要的js包文件：

~~~
$ bower search js's-name
~~~

安装js包

~~~
$ bower install --save js's-name
~~~

加上--save，bower会自动将该包加入到工程中bower配置文件中。

