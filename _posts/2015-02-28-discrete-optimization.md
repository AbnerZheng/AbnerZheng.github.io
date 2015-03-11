---
layout: post
title: "Discrete Optimization"
description: 
modified: 2015-02-28 23:10:32 +0800
category: 
tags: [Algorithms, Coursera]
image:
  feature: 19.jpg-clip.jpg
  credit: 
  creditlink: 
comments: true
share: true
alias: [/2015/02/28/Discrete Optimization]
---

### 前记

墨尔本大学带来的这门Discrete Optimization课大概是去年这个时候知道的，当时也报了，结果没听几节课，就被难倒了，当时的水平确实不够支持完成这门课。后来的一年，我的编程水平应该说有很大水平的提升，入门了数据结构，看了[《算法导论》][3]，跟着上了UC Berkeley的SCIP的Python翻版课程[CS61a][2]，特别在codewar以及checkio上刷了一些题，我觉得现在的自己应该有资本来挑战一下这门难课了。Discrete Optimization是专门讲NP-hard问题，关于这个领域，我曾经看过一本[《可能与不可能的边界：PNP问题趣史》][1]，从题目就可以看出这是本讲NP求解历史的书籍，其中理清了发展以及目前学术界针对该问题的发展情况。然后我所看过的对这门课最有帮助的就是崔天翼的[《背包九讲》][4]，讲得很通透，每次看都会有新感受。本文即是对Discrete Optimization课程的笔记以及Programming Assignment的一些分析，并且针对Forum中的一些好观点进行分析及记录。

愿我能完成这门课。。。。阿门~~~

<!--more-->

### 1、 0，1背包问题

推导公式：

$$\begin{equation}
	\begin{array}{rcl}
	 \mbox{maximize} &\sum_{i\in I}{v_ix_i}&\\
	 \mbox{subject to} & \\
	 \qquad &\sum_{i\in I}{w_i x_i}&\leq K\\ 
	 					&x_i\in\{0,1\}& \: (i\in I)&
	\end{array}
\end{equation}$$

可以看到如果使用遍历，那么将会有
$$2^{ \left| I \right| }$$
中可能情况,是指数级，显然不能用遍历，考虑其中很多情况重量远远未达到K，这显然是应该被减去的，所以给我们留下了优化求解空间，背包问题是很好的动态规划问题。其递归解如下：

令
$$f(i,w)$$
表示容量为w时，前i件物品放入背包所能得到的最大价值，则递归方程(同状态转移方程，我比较喜欢叫成递归方程(^ ^)）可以写成：

$$\begin{equation}
	f(i,w)=
	\begin{cases}
	max\{f(i-1,w), f(i-1,w-w_i)+v_i\}, & \mbox{if }w\ge w_i \\
	f(i-1,w),& \mbox{otherwise }
	\end{cases}

\end{equation}$$

其中初始条件为：

$$f(0,w)=0 \qquad \mbox{for all k}$$

显然根据这两个公式我们就可以得到一个递归版本的01问题求解程序：

{% highlight python linenos %}
def zeroOnePack(i,k):
	if i==0:
		return 0
	elif k>=w[i]:
		return max(zeroOnePack(i-1,k),v[i]+zeroOnePack(i-1,k-w[i]))
	else:
		return zeroOnePack(i-1,k)
{% endhighlight %}

观察式（2），符合动态规划里的最优子结构和重复特点，可以通过动态规划求解。动态规划就是通过自底向上的求解，来避免递归中的重复计算。

{% highlight python linenos %}
#coding=utf8
w = [4,5,3,4,3]
v = [5,6,2,6,3]
def zeroOnePack2(w,v,k):
	result = [0] * (k+1) #初始化,空间复杂度为O(k)
	for dummy_i in range(0,len(v)):
		for ww in range(k,0,-1):
			if ww - w[dummy_i]>=0:
				result[ww] = max(v[dummy_i]+result[ww-w[dummy_i]],result[ww])
	return result[-1]

print zeroOnePack2(w,v,13)

{% endhighlight %}

该程序的时间复杂度为
$$O(k^2)$$

#### 3月6日更新

这几点忙着准备找实习，这门课看来又要往后拖了，怨念啊。慢慢填坑吧。

继续前面的01背包问题，老师在之后的视频介绍了branch and bound算法，这个算法现在已经被淘汰了。不过我查了wikipedia，发现这个算法在亮相之初曾获得了旅行商锦标赛的冠军，还算挺经典的算法。不过还不急着上branch and bound，先用backtrace刷一遍。程序如下，基本套用backtrace即可，backtrace是深度优先搜索（没用队列），递归基一般选为遍历完数组。

{% highlight python linenos %}
nn = len(v)
resultBacktrace = [0]* nn
maxV =0
def zeroOnePackBacktrace(k):
	"""
	k表示背包容量，i为第几个物品，ww为目前选入背包物品的重量，vv为其价值
	"""
    def backtrace(i,ww,vv):
        global maxV
        #求解成功,递归基
        if i== nn:
            if vv>maxV:
                maxV = vv
                print resultBacktrace
            return

        if ww + w[i]<=k:
            #放进背包
            resultBacktrace[i]= 1
            backtrace(i+1, ww+w[i],vv+v[i])
        #不放入背包
        resultBacktrace[i] = 0
        backtrace(i+1,ww,vv)

    backtrace(0,0,0)

zeroOnePackBacktrace(21)
print maxV
{% endhighlight %}

分析可以知道，这种backtrace的复杂度是指数爆炸的。

接下来撸一把branch and bound，这是一种远古剪枝算法，其求解目标是找出解空间树种满足约束条件的所有解，而分支限界法的求解目标则是找出满足约束条件的一个解或是某种意义下的最优解，再看搜索方式，回溯法






[1]: http://book.douban.com/subject/25779326/
[2]: http://cs61a.org/
[3]: http://book.douban.com/subject/1885170/
[4]: http://love-oriented.com/pack/