---
layout: post
title: "Cryptography I"
description: 
modified: 2014-06-30 22:55:50 +0800
category: 
tags: [coursera,cryptography]
image:
  feature: 19.jpg-clip.jpg
  credit: 
  creditlink: 
comments: true
share: true
alias: [/2014/06/30/Cryptography I]
---

##Cryptography课程笔记
很早前就想修这门课了，当时畏惧其难度，现在刚好是暑假，比较空，就挑战下这门好课。

<!--more-->

##Week 1

###密码体制
定义: 

一个密码体制是满足以下条件的五元组 $\left(\mathcal{P,C,K,\varepsilon,D}\right)$ :

1. $\mathcal{P}$表示所有可能的明文组成的有限集
2. $\mathcal{C}$表示所有可能的密文组成的有限集
3. $\mathcal{K}$表示密匙空间，是由所有可能的密匙组成的有限集
4. 对任意的$k\in\mathcal{K}$,都存在一个加密法则$e_k\in\mathcal{\varepsilon}$和对应的加密法则$d_k\in\mathcal{D}$。并且对每一$e_k(\mathcal{P})\to{\mathcal{C}}$   和  $d_k(\mathcal{C})\to{\mathcal{P}}$ , 对任意的明文 $x\in{P}$,均有$d_k(e_k(x))=x$

 


###Symmetric Ciphers 对称加密算法

基本模型：（声明，本笔记图表均来自与Coursera课程Cryptography，下同）
![基本模型](\images\post\Symmetric Ciphers.jpg)

即在加密和解密中，使用的密匙（key）是相同的。

$$\mathcal{A}$$
