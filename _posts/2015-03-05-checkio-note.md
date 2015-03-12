---
layout: post
title: "checkio note"
description: 
modified: 2015-03-05 21:24:01 +0800
category: 
tags: [python, algorithms]
image:
  feature: 19.jpg-clip.jpg
  credit: 
  creditlink: 
comments: true
share: true
alias: [/2015/03/05/checkio note]
---

### checkio闯关小结

checkio的home statation通关，等级也到了10级，感觉对脚本的使用越来越熟练也越喜欢了。在这里做个小结。

<!--more-->

## Roman numerals

题目[链接][1], 题意大致就是输入一个整数，将其转换成罗马数字字符串，然后输出。 题目难点主要在理解罗马数字不仅可以做基本元素的叠加，也可以是相减，即将一个小的字符放在一个大的字符前面表示减，如9的表示方法不是VIIII,而是IX(10-1),观察可以看到任一字符都最多只能连续出现3次。依照罗马数字的这一特点，可以提前凑出减的情况，然后就是简单递归。代码如下：

{% highlight python linenos %}
def checkio(data):
    ROMANS = (('M',  1000),('CM', 900),('D',  500),('CD', 400),('C',  100),('XC', 90),('L',  50),
          ('XL', 40),('X',  10),('IX', 9),('V',  5), ('IV', 4), ('I',  1))
    result = ""
    #replace this for solution
    for i,v in ROMANS:
        while(data>=v):
            data -= v
            result+=i
    return result

if __name__ == '__main__':
    #These "asserts" using only for self-checking and not necessary for auto-testing
    assert checkio(6) == 'VI', '6'
    assert checkio(76) == 'LXXVI', '76'
    assert checkio(499) == 'CDXCIX', '499'
    assert checkio(3888) == 'MMMDCCCLXXXVIII', '3888'
{% endhighlight %}

## Golden Pyramid

题目[链接][2], 该题是一个很基础的动态规划问题，其状态转移方程为：

$$f(i,j)=max\{f(i-1,j)+e[j], f(i-1,j-1)+e[j]\}	$$

依照状态转移方程可的代码如下：

{% highlight python linenos %}
def count_gold(pyramid):
    result = [0]*len(pyramid[-1])
    for e in pyramid:
        for dummy_i in range(len(e)-1,0-1,-1):
            result[dummy_i]=max(result[dummy_i]+e[dummy_i],result[dummy_i-1]+e[dummy_i]if dummy_i>0 else 0 )
    return max(result)


def count_gold2(pyramid):
	#递归解法
    def count(pyramid, level, to, number):
        here = number + pyramid[level][to]
        if level == len(pyramid) - 1:
            return here
        else:
            return max(
              count(pyramid, level + 1, to, here) ,
              count(pyramid, level + 1, to + 1, here),
            )
    return count(pyramid, 0, 0, 0)

if __name__ == '__main__':
    #These "asserts" using only for self-checking and not necessary for auto-testing
    assert count_gold2((
        (1,),
        (2, 3),
        (3, 3, 1),
        (3, 1, 5, 4),
        (3, 1, 3, 1, 3),
        (2, 2, 2, 2, 2, 2),
        (5, 6, 4, 5, 6, 4, 3)
    )) == 23, "First example"
    assert count_gold2((
        (1,),
        (2, 1),
        (1, 2, 1),
        (1, 2, 1, 1),
        (1, 2, 1, 1, 1),
        (1, 2, 1, 1, 1, 1),
        (1, 2, 1, 1, 1, 1, 9)
    )) == 15, "Second example"
    assert count_gold((
        (9,),
        (2, 2),
        (3, 3, 3),
        (4, 4, 4, 4)
    )) == 18, "Third example"
{% endhighlight %}

##Open Labyrinth 

题目[链接][3], 该题是一个迷宫解题的问题，我采用了广度优先的搜索算法，题目提示说可以使用A*搜索算法，这算法我看过，不过不大会，**先留坑，日后填**。 使用广度优先搜索，和遍历不同，要设定一个solution find 条件，即找到目标, 一般这种路径查找问题，都需要输出路径，在这里可以使用一个tuple包装目前所处的地址以及其历史搜索路径，其他貌似就没有什么要注意的了。


{% highlight python linenos %}
def checkio(maze_map):
    visited = set()  #存储已访问过的节点
    queue=[((1,1,),"" )]  #使用queue, 用一个tuple包装目前的地址和其历史搜索路径
    while queue:
        position, path = queue.pop(0)  #queue先入先出
        if position == (10,10):  # solution find
            return path
        if position in visited: # 避免重复
            continue
        else:
            visited.add(position)
            for neigh_position, direction in get_neightbour(maze_map,position):  #获得当前点的邻居
                if neigh_position in visited:
                    continue
                queue.append((neigh_position,path+direction))
    return False

def get_neightbour(maze,position):
    #获取position点的邻居坐标及方向
    NEIGHBORS = {(-1, 0):'N', (0, 1):'E', (1, 0):'S', (0, -1):'W'}
    result=[]
    row,col = position
    for neighbor in NEIGHBORS:
        i, j = neighbor
        if 0 <= row + i < len(maze) and 0 <= col + j < len(maze[0]) and maze[row + i][col + j] == 0:
            result.append(((row+i,col+j),NEIGHBORS[(i,j)]))
    return result




if __name__ == '__main__':
    #This code using only for self-checking and not necessary for auto-testing
    def check_route(func, labyrinth):
        MOVE = {"S": (1, 0), "N": (-1, 0), "W": (0, -1), "E": (0, 1)}
        #copy maze
        route = func([row[:] for row in labyrinth])
        pos = (1, 1)
        goal = (10, 10)
        for i, d in enumerate(route):
            move = MOVE.get(d, None)
            if not move:
                print("Wrong symbol in route")
                return False
            pos = pos[0] + move[0], pos[1] + move[1]
            if pos == goal:
                return True
            if labyrinth[pos[0]][pos[1]] == 1:
                print("Player in the pit")
                return False
        print("Player did not reach exit")
        return False

    # These assert are using only for self-testing as examples.
    assert check_route(checkio, [
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1],
        [1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1],
        [1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1],
        [1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1],
        [1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1],
        [1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1],
        [1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]]), "First maze"
    assert check_route(checkio, [
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]]), "Empty maze"
    assert check_route(checkio, [
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1],
        [1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1],
        [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1],
        [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1],
        [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1],
        [1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1],
        [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1],
        [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1],
        [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1],
        [1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]]), "Up and down maze"
    assert check_route(checkio, [
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1],
        [1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1],
        [1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1],
        [1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1],
        [1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1],
        [1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1],
        [1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1],
        [1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1],
        [1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1],
        [1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]]), "Dotted maze"
    assert check_route(checkio, [
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1],
        [1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1],
        [1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1],
        [1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1],
        [1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1],
        [1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]]), "Need left maze"
    assert check_route(checkio, [
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1],
        [1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1],
        [1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1],
        [1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1],
        [1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1],
        [1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]]), "The big dead end."
    print("The local tests are done.")

{% endhighlight %}

## Fibonacci Golf

题目[链接][4], 该题竞标赛，给了一大堆的类fibonacci的各种数列，考量条件是编译后的长度，编译长度？!  一点概念都没有。。。只能是**先留坑日后填**了。现阶段的解法如下：

{% highlight python linenos %}
def f(a,b,c,d,e,f,n):
    for i in range(n):
        a,b,c=b,c,d*c+e*b+f*a
    return a

def fibgolf(t, n):
    a = t[0]
    if a=='f':return f(0,1,1,1,1,0,n)
    if a=='t':return f(0,1,1,1,1,1,n)
    if a=='l':return f(2,1,3,1,1,0,n)
    if a=='j':return f(0,1,1,1,2,0,n)
    if t=='padovan':return f(0,1,1,0,1,1,n)
    if t=="pell":return f(0,1,2,2,1,0,n)
    return f(3,0,2,0,1,1,n)
{% endhighlight %}

该程序经过判定程序检测，为721，得179分，排91。


[1]: http://www.checkio.org/mission/roman-numerals/
[2]: http://www.checkio.org/mission/golden-pyramid/
[3]: http://www.checkio.org/mission/open-labyrinth/
[4]: http://www.checkio.org/mission/fibonacci-golf/