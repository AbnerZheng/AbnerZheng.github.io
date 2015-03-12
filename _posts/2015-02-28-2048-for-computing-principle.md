---
layout: post
title: "2048 for computing principle"
description: 
modified: 2015-02-28 13:48:32 +0800
category: 
tags: [2048, python]
image:
  feature: 19.jpg-clip.jpg
  credit: 
  creditlink: 
comments: true
share: true
alias: [/2015/02/28/2048 for computing principle]
---

### Computing Principal Assignment

Coursera欢(dou)快(bi)组合又给我们带来一门中阶课程，也是python入门课的后续课程，名叫Computing Principal。

<!--more-->

第一周和第二周的作业是编写一个2048，和往常一样，基本轮廓和GUI库都已经帮你搭建好了，你需要做的就是填写核心代码。

2048大家都玩过，当初风靡的时候也废了我好多时间的说。今天自己来写一个也是挺有趣的。

代码实现的地址为：[http://www.codeskulptor.org/#user39_7e81XhxIwc_9.py][1]

亲测，可玩，可能还有不足。有几处代码其实我是有点小嘚瑟的啦，觉得写的很简洁，放出来先：
{% highlight python linenos %}
def move(self, direction):
    """
    Move all tiles in the given direction and add
    a new tile if any tiles moved.
    """
    offset_row,offset_col = OFFSETS[direction]
    temp = self._grid
    if offset_row == 0 :
        self._grid = [merge(e[::offset_col])[::offset_col] for e in self._grid]
    else:
        self._grid = map(list,zip(*[merge(e[::offset_row])[::offset_row] for e in map(list,zip(*self._grid))]))
    if(temp == self._grid):
        return
    self.new_tile()
{% endhighlight %}

所有代码就到上面的链接里看吧。 

后续：有个大牛做了个AI，能够达到90%的几率完成2048，使用完alpha beta剪枝，其代码也是开源的，此大牛还在stackoverflow上回答过启发函数的设计，我读了好几遍，还是似懂非懂啊。待我找到实习之后，再来研读一番，自己实现，不也美哉~~~

[1]: http://www.codeskulptor.org/#user39_7e81XhxIwc_9.py