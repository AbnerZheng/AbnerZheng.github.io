---
layout: post
title: "《Python 核心编程》学习笔记及思考"
description: 
modified: 2014-06-29 13:11:33 +0800
category: 
tags: [python,note]
image:
  feature: 19.jpg-clip.jpg
  credit: 
  creditlink: 
comments: true
share: true
alias: [/2014/06/29/note_python_core_programming]
---

# Python 学习
决定用几天的功夫，通过刷《Python 核心编程》这本书，来巩固提高一下Python水平，接下来会将书中一些有用的点记录下来。由于用的是第二版，书针对是python 2.5以下的特性，所以在看这本书的时候还需要看下2.7版本的帮助文档。
现在开始第一天的记录！
<!--more-->

##第一章
这一章主要是对Python的起源特点做些介绍，我一直以为python是近些年才出现的，才发现，python的第一个公开发行版在91年就发布了，和我年龄相当啊。

对于书中提到的python特点，这里需要记住的是python类似于Java，是字节编译的，中间会生成一种近似机器语言的中间形式。

###一些思考
python的开发工具的话，IDE我采用的Python(x,y)，其中集成了Spyder,以及常用的一些如scipy算法库，非常方便，而Spyder提供的Object inspector则是我及其喜欢的功能，可以帮助我快速查阅帮助文档，很实用的功能。另外平常写些小程序的话，都选用sublime，启动vim模式，写代码还是很爽的！

另外，python也有一些好玩的网站，如[Python Challenge](http://www.pythonchallenge.com/) 和[Checkio.org](http://www.checkio.org/)。大家在学习python过程中，可以玩玩。

##第二章
这章是对Python的快速介绍，目的在于使读者对Python的语法及特性能够有个全览。

###不清晰的要点
- 下划线‘_’ 表示最后一个表达式的值
- print输出重定向，如：

{% highlight python %} 
logfile = open('mylog.txt','a')
print >> logfile, 'Fatal error: invalid input'
logfile.close
{% endhighlight %}
- 两种除法：'/' 以及 '//', 后者是强制浮点除。
- python 不支持C语言中的自增1和自减1操作。
- 长整型数字类型，如2999999L，在末尾加L。
- c语言中重用的else if 在python中用elif表达

##第三章 Python 基础

### 要记忆的一些要点
- 注释用#
- 单引号和双引号不区分
- 可以用";"来在同一行书写多个语句
- python支持多重赋值和多元赋值，如：
{% highlight python %}
#多值赋值
>>> x = y = z = 1
>>> x
1
>>> y
1
>>> z
1

#多元赋值
>>> x, y, z = 1, 2, 'a string'
>>> x
1
>>> y
2
>>> z
'a string'
{% endhighlight %}
- 在类Unix中，每个Python文件的起始行可以加入一句注释：
```
#!/usr/bin/env python 
```
使在系统能仅输入脚本名字来执行脚本
- 下划线语法：_xxx常表示一个类中的私有变量名，而这些变量不能用'from module import'导入，而_xxx_则是系统定义名字。所以在编写陈鑫的时候，避免使用下划线开头的变量名。
- 在Python程序中，_name_指示模块是被导入调用还是直接执行，当是被导入时，_name_的值为模块名字，而直接执行的话，_name_的值为’_main_’，因此利用这个特性，就可以在模块的main函数里写demo或测试程序，当判断_name_=='_main_'为真时，调用这个函数。
- 内存管理：1. 变量无需事先声明  2. 变量无需指定类型  3.程序员不用关心内存管理  4.变量名会被回收，python使用了引用计数的技术来追逐内存中的对象  5.del语句能够直接释放资源
- 勘误：makeTextFile.py 的第十行应该加上一句：```fname=raw_input('Enter the name of the file')``` ,另外再吐槽下中文版的代码缩进，太差了！