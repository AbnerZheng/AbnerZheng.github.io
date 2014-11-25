---
layout: post
title: "computer graphics"
description: 
modified: 2014-10-15 22:12:11 +0800
category: 
tags: [graphics, algorithm]
image:
  feature: 19.jpg-clip.jpg
  credit: 
  creditlink: 
comments: true
share: true
alias: [/2014/10/15/computer graphics]
---
###光栅图形学算法是用来在计算机处理、显示图形的一系列算法,是基本算法，非常重要。对课题提到的一些算法做个记录和归总。

<!--more-->

## 研究内容

* 直线段的扫描转换算法
* 多边形的扫描转换与区域填充算法
* 裁剪算法
* 反走样算法
* 消隐算法

## 直线段的扫描转换算法
在数学意义上，直线有连续的无穷多个点，而在实际的光栅中，像素点有限，是离散的。如下图所示：(本笔记所有图表来自中国农业大学mooc公开课的课件)
![光栅直线](\images\post\linetransform.jpg)

从连续到离散，我们可以通过取整来获取离散的坐标值，可以用四舍五入取整来减少误差，接近实际。

由直线的斜截式方程 $y=kx+b$,再对y取整可以很简单地得到直线上各点的坐标。但是在方程中有个乘法运算，而直线算法是其他很多算法的基础，如果能够把这个乘法取消就能大大提升效率。

### DDA画线算法
DDA(Digital Differential Analyzer,数值微分)算法引进图形中的一个很重要的思想——增量思想。
由：

$$\begin{equation}
	y_i = kx_i+b
\end{equation}$$

$$\begin{equation}
	\begin{array}{rcl}
		y_{i+1}&=&kx_{i+1}+b \\
	       	&=&k(x_i+1)+b \\
	       	&=&kx + k + b \\
	       	&=&y_i + k
	\end{array}
\end{equation}$$

DDA采用了增量思想，每计算一个坐标，只要做一个浮点加法。但应该注意的是，
当$$\left|k\right|>1$$时,运用DDA算法会导致直线的点太稀疏。

### 中点画线算法
DDA只需做一次浮点加法，改进DDA有两种思路：

1. 改进计算效率：在计算中，整数加法比浮点加法更快，
2. 从直线方程类型(两点式，一般式)做文章(中点画线法)。

直线的一般式方程为 $$ Ax + By + c = 0$$ , 每次在最大位移方向上走一步，而另一个方向时走步还是不走步取决于中点误差项的判断。

![中点画线的误差项](\images\post\Middleline.jpg)

把M点的坐标带入理想直线方程：

$$\begin{equation}F(x_m,y_m) = Ax_m + By_m + C\end{equation}\label{middle}$$

如果($$\ref{middle}$$)式大于0，说明中点$M$在直线上方，所以此时$Y$方向应该不走（取$$P_d$$），反之，如果小于0，则说明$M$在直线下方，此时$Y$方向应该走（取$$P_u$$),如果等于0，则可以任取。
综上， 可以得到

$$\begin{equation}
y_{i+1}=
\begin{cases}
y_i+1& {d>0}\\
y_i& {d\leq0}
\end{cases}
\end{equation}$$
