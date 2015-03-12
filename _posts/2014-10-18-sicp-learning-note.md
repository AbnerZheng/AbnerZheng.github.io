---
layout: post
title: "SICP learning note"
description: 
modified: 2014-10-18 20:46:15 +0800
category: 
tags: [SICP,Python]
image:
  feature: 19.jpg-clip.jpg
  credit: 
  creditlink: 
comments: true
share: true
alias: [/2014/10/18/SICP learning note]
---

### Berkeley大学 Computer Science 61a 课堂笔记

<!--more-->

## 001 
经常听到各式大牛推荐SICP这本书，故很想拜读一番，恰好，在Berkeley的webcast上发现了[CS61a](http://webcast.berkeley.edu/playlist#c,d,Computer_Science,-XXv-cvA_iDbsAvTYyJnMkObr12IIkyg)这门课，更好的是，Berkeley大学是将正在上的课程录下来同步放上去，所以进度是他们学校的进度,而且Berkeley大学很大方地将所用[在线教材、课题笔记、lab以及课后习题](http://cs61a.org/)都公开出来，不得不佩服这些学校的开放和自信。 CS61a并没有像SCIP一样采用scheme作为教学语言，而是选择了python3，而这也正好合我的心意，现在的我还是不想入lisp语言的坑。我准备开此篇记录做读书笔记以及assignment的记录。

##  Church Numerals 

Church Numerals 是homework2的Challenge Problem，是由逻辑学家Alonzo Church发明的，可以用函数来表示所有非负整数，其目的是证明函数能够描述整个数论：如果我们有函数，我们不必去假设那些数存在，而是去发明他们。 反正我是看不懂这句话的意思啦。。

题目给了两个基础函数：

{% highlight python %}
def zero(f):
    return lambda x: x

def successor(n):
    return lambda f: lambda x: f(n(f)(x))
{% endhighlight %}

然后是要我们定义出函数one和two,其中one等价与successor(zero), two 等价与 successor(one), one和two中的定义不能使用successor。

观察successor，其实实现的就是f(f(x)),增加一阶，将zero看做零阶函数，one则为一阶函数，two则是二阶函数。那么one和two可以如以下实现：

{% highlight python linenos %}
def one(f):
    """Church numeral 1: same as successor(zero)"""
    return lambda x: f(x)


def two(f):
    """Church numeral 2: same as successor(successor(zero))"""
    return lambda x: f(f(x))
{% endhighlight %}

然后题目又要求我们完成church_to_int, 该函数实现将Church numeral转换为整数。 其实现代码如下：

{% highlight python linenos %}
def church_to_int(n):
    """Convert the Church numeral n to a Python integer.

     >>> church_to_int(zero)
     0
     >>> church_to_int(one)
     1
     >>> church_to_int(two)
     2
     >>> church_to_int(three)
     3
     """
    return n(lambda x: x + 1)(0)
{% endhighlight %}

由上得，

$$zero(f,x)=x, one(f,x) = f(x) , two(f,x) = f(f(x))$$

设计函数church_to_int，要使得传入zero、one、two后分别等于0、1、2,则可以想到可以令f = lambda x: x+1， 从而获得下一阶比前一阶加一的功能。

接下来就是设计Church numeral的运算, 对于加，观察successor，它所做的运算其实就是完成加一的功能，现在要完成任意两个数的相加，从successor函数出发，是一条解决的好方法： 实际上n(f)(x)就是Church numeral n，而套在外面的f就是1的定义（即one(f))，类比可以得到，现在我要加m，那么可以得到应该是m(f),所以add_church(m,n)的代码实现为：

{% highlight python lineos %}
def add_church(m, n):
    """Return the Church numeral for m + n, for Church numerals m and n.

    >>> church_to_int(add_church(two, three))
    5
    """
    return lambda f:lambda x:m(f)(n(f)(x))
{% endhighlight %}

接下来的是乘法和乘方，乘方应该比较容易得到（试出来的），但是这个乘法我一直看不懂看不懂啊。。。智商捉急。。。。下面是老师deadline之后发出来的答案，看了还是懵懵懂懂。  好像这个属于lambda验算里的知识，哎，难啊。。。。

**更新**

好像有点细微的思路了。对于一个Church numeral n, 有 

$$n(f)(x) = f^n(x) $$

同理，对于Church numeral m, 有

$$m(g)(x) = g^m(x) $$

令g=n(f),代入，得到

$$m(g)(x) = (f^n)^m(x) = f^{mn}(x) $$ 

由此得证。 

但是这样的话，乘方却不能按这种套路证明出来，我觉得这种验算肯定有它的一套数学抽象方法，**先挖坑日后填**

{% highlight python %}
def mul_church(m, n):
    """Return the Church numeral for m * n, for Church numerals m and n.

    >>> four = successor(three)
    >>> church_to_int(mul_church(two, three))
    6
    >>> church_to_int(mul_church(three, four))
    12
    """
    return lambda f: m(n(f))


def pow_church(m, n):
    """Return the Church numeral m ** n, for Church numerals m and n.

    >>> church_to_int(pow_church(two, three))
    8
    >>> church_to_int(pow_church(three, two))
    9
    """
    return n(m)
{% endhighlight %}
