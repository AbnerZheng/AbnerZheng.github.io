---
layout: post
title: "computer-graphics"
description: 
modified: 2015-08-09 11:07:54 +0800
category: 
tags: [graphics]
image:
  feature: 19.jpg-clip.jpg
  credit: 
  creditlink: 
comments: true
share: true
alias: [/2015/08/09/computer-graphics]
---

### 正好有契机好好学把计算机图形学，好好学习~~
看的一些资源：
首推Petron的[视频合集][1],该视频合集以HTML5中的canvas为编程平台，讲诉一些简单的图形编程技巧，辅以代码，非常棒的资源，首先学会how to program。
第二个是网易云课堂的《计算机图形学》课程，主讲老师是中国农业大学的赵明老师，夯实理论基础。
第三个就是Coursera上的《计算机图形学》，不过这个我还没开始跟。

<!--more-->

### 第一讲

> 计算机图形学的定义： 计算机图形学就是研究如何在计算机中表示图形、以及利用计算机进行图形的计算、处理和显示的相关原理与算法。真实世界的模拟。

> 计算机图形学的研究内容：如何在计算机中表示图形、以及利用计算机进行图形的计算、处理和显示的相关原理与算法。

一般来说,要生成一个图形，需要有三个步骤：

1. 造型
2. 光照模型
3. 绘制（渲染）技术: 光纤跟踪、辐射度算法、纹理映射、阴影等算法

计算机图形学之父：I.E.Sutherland, MIT林肯实验室，发表《Sketchpad:"A Man Machine Graphical Communication System"》博士论文,于1988年活的"图灵机"。

光栅显示器：我们现在用的都属于光栅显示器。

### 第二讲

#### 数值微分DDA(Digital Differential Analyzer)法

$$y_i = kx_i + b $$

$$y_{i+1} = kx_{i+1} + b $$

可以看到，为了计算一个点，需要一次乘法和一次加法，而如果采用DDA，即可减少到
一次加法:

$$y_{i+1} = k(x_i + 1) + b = kx_i + b + k = y_i + k$$

#### 中点画线法

**基本原理**
每次在最大位移方向上走一步，而另一个方向上是否走步取决于中点误差项的判断。
![中点法][2]

把M带入理想直线方程：

$$F(x_m, y_m) = Ax_m + By_m + C$$

如果$$F(x_m, y_m)>0$$ 说明是在直线上方，此时应该选下面的那点，反之则选上面的那点。

**优化**

$$d_{i+1}=F(x_{m+1},y_{m+1}) = Ax_{m+1} + By_{m+1} + C $$

$$A(x_m + 1) + B(y_m + 1) + C = d_i + A + B + C $$






[1]: http://www.codingmath.com
[2]: /images/post/center1.png
