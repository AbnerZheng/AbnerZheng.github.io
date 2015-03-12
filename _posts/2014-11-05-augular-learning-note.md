---
layout: post
title: "augular learning note"
description: 
modified: 2014-11-05 20:40:22 +0800
category: 
tags: [angular,front-end]
image:
  feature: 19.jpg-clip.jpg
  credit: 
  creditlink: 
comments: true
share: true
alias: [/2014/11/05/augular learning note]
---

### Angular 学习笔记
AngularJs大有革命的意味，用的人还是比较多的，由于手机web app选定要用ionic，而ionic基于AngularJs，所以学习迫在眉睫。

<!--more-->

## 资料推荐

###在网上可以找到很多AngularJs的学习材料，下面推荐几个：
1. [AngularJs主页](https://angularjs.org/)
2. codeSchool上的[Shaping up with AngularJs](http://campus.codeschool.com/courses/shaping-up-with-angular-js)。codeSchool是一个付费在线学习网站，但也有几门入门课是免费的，Angular这门课程也在免费课程当中。另外，好像过段时间就要推出Angular的另一门进阶课程，不过个人感觉免费的可能性不高。
3. 慕课网上的[Angular 实战](http://www.imooc.com/learn/156)，由《AngularJS》中文译者大漠穷秋主讲。
4. 书籍《AngularJs》，中译版《使用AngularJs开发下一代web应用》 

## Angular 实战笔记

### 前端的MVC

####原则：**不要为了MVC而MVC，MVC的目的是为了模块化(解耦)和复用！**

####前端MVC的困难:

*操作DOM的代码必须等待整个页面全部加载完成(不同浏览器加载速度，并发加载数量会存在不一致)
*多个JS文件之间如果出现相互依赖，程序员必须自己解决
*JS的原型继承也给前端编程带来很多困难(其他语言)

### AngularJs中的Controller

AngularJs中Controller的实线方式:
![Controller](\images\post\AngularController.jpg)

应该通过service来提供两个Controller公共的功能,而不是使用scope的层级关系来提供。

#### Controller的一些注意点

* 不要试图去复用Controller，一个控制器一般只负责一小块视图
* 不要在Controller中操作DOM
* 不要在Controller里面做数据格式化，ng有很好的表单控件
* 不要在Controller里面做数据过滤操作，ng有$filter服务
* Controller是不会互相调用，控制器之间的交互应该通过事件进行

### AngularJs中的View
可以通过指令来实现View的复用。AngularJs中的MVC是通过MVC实现的。$scope的查找和JS中的原型继承是一致的，当在当前作用域中找不到该变量时，就向上级进行查找。
$emit：上级可以响应
$broadcast: 下级可以响应

### $scope的特点
* $scope 是一个POJO(plain old javascript object)
* $scope 提供了一个工具方法 $watch()/$apply()
* $scope是表达式的执行环境(或者叫作用域)
* $scope是一个树型结构,与DOM标签平行(可以继承父辈的属性和方法)
* 每一个Angular应用只有一个根$scope对象(一般位于ng-app上)
* $scope可以传播事件，类似DOM事件，可以向上也可以向下
* $scope不仅是MVC的基础，也是后面实现双向数据绑定的基础。
* $scope的生命周期：
![生命周期](\images\post\$scopeLifeCircle.jpg)




