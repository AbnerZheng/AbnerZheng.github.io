---
layout: post
title: "线性代数"
description: 
modified: 2016-02-29 10:57:22 +0800
category: 
tags: [learning_note]
image:
  feature: 19.jpg-clip.jpg
  credit: 
  creditlink: 
comments: true
share: true
alias: [/2016/02/29/linear algebra]
---

### 加油加油

<!--more-->

最近在学习Andrew Ng的机器学习，学习资源主要是网易公开课上以及Coursera
上的课程，Coursera上的课程要浅很多，数学推导以及内容都精简了很多，但是
他的MATLAB 编程作业真的很棒，让我学习到很多知识。然而在学习过程过，课
程里面很大量的矩阵运算，发现有些吃不消。果然有点债就是得补，所以干脆将
MIT的线性代数公开课给上完。哈哈哈，就是这么任性。估计下一门课就是概率
论了哈，实在是书到用时方恨少呀。

这里总结一下这些天发现的一些资源，上的是老教授Gilbert的
[课程][opencourse]，该课在MIT上的编号是18.06，
[课程主页地址][MIT18.06]，虽然不是Gilbert老先生教了，但是所用教材一致，
所以感觉应该改变不是很大，感觉改变最大的应该是上机环境增加了Julia，可
以在Julia box上在线做assignment。

现在我成了一个码农，更重要的是如何使用线性代数库进行运算了，所以学习很火的julia也是很棒的事情~~就是这么满足。教材可以用Gilbert的《Introduction to Linear Algebra》,浙江图书馆里面有，然而网上也能找得到。数学这东西嘛，就是做，做各种习题，然而就知道怎么用了，没有捷径而言，那就开干吧，呼哈哈。另开一个Github地址，将这些做完的Julia assignment放出来，给自学的人一些帮助吧，呼哈哈。

##3月一日进度
在做assignment1中间发现有些语法很神奇，在我本来的印象里还以为Julia只是
个Python的类库，最多加点语法糖，然而被啪啪啪打脸了。哎，这里终结下在做
assignment1中间需要注意的点：

* 定义一个row vector： rv = [1 2 3 4]   #这里是空格
* 定义一个column vector: cv = [1, 2, 3, 4] #这里是逗号,或者用回车隔开
* 没有使用缩进来判断代码块

这几天学习速度还是杠杠的，目前网易公开课已经学习到了第十一课，四个子空
间，表示很难呀，今晚和明天就要将课本进度和Online Assignment的进度都同
步上，加强理解。Fighting！

[opencourse]: http://open.163.com/special/opencourse/daishu.html "线性代数课程"

[MIT18.06]: http://web.mit.edu/18.06/www/


