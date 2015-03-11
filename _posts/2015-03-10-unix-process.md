---
layout: post
title: "理解Unix进程的nodejs代码实现"
description: 
modified: 2015-03-10 20:36:31 +0800
category: 
tags: [node, unix , process]
image:
  feature: 19.jpg-clip.jpg
  credit: 
  creditlink: 
comments: true
share: true
alias: [/2015/03/10/Unix Process]
---

准备面试中， 重读这本[《理解Unix进程》][1]，该书是用ruby作为讲解语言，面向普通没有C语言系统编程的web开发者，正好我准备投入nodejs的怀抱，想着ruby和node都是脚本语言，涉及到系统调用的地方都是一致的，同为脚本语言，接口的相通性应该是有的，所以在第二遍的阅读中，准备以node实现其中的示例代码，以此作为学习。

<!--more-->

## 第三章 进程皆有标识

查看进程pid的方法：

{% highlight javascript linenos %}
console.log(process.pid);
{% endhighlight %}

实践领域：当有多个进程想一个文件中写入日志的时候，可以通过这个语句将进程的pid写入日志。

#### 对应的系统调用： getpid

#### python实现： os.getpid()

## 第四章 进程皆有父

可以通过getppid的系统调用来获得，但似乎node并没有实现这个函数。难道与node单进程单线程有关？  留坑之后填

(更新) node没有这些posix的系统调用是单纯由于缺失，可以安装posix模块获得支持，获取父进程的node代码如下：
{% highlight javascript %}
var posix = require("posix");
posix.getppid();
{% endhighlight %}

稍微找了一下posix的源码，果然是用c++写的addons，其中getppid的实现很简单，就是调用c的库函数getppid，代码片段如下：
{% highlight cpp linenos %}
NAN_METHOD(node_getppid) {
    NanScope();

    if(args.Length() != 0) {
        return NanThrowError("getppid: takes no arguments");
    }

    NanReturnValue(NanNew<Integer>(getppid()));
}
{% endhighlight %}

#### 对应的系统调用: getppid
#### python实现： os.getppid()

## 第五章 进程皆有文件描述符

在unix的哲学世界中，万物皆文件，设备、socket、pipe，这些资源由文件描述符编号指定，文件描述符不会在无关进程中共享，当进程结束后，会和其他进程所打开的资源一同被关闭。

在node中，通过fs.openSync可以获取文件描述符，js代码如下：

{% highlight javascript linenos %}
var fs = require("fs");

var fid = fs.openSync("./repl_server.js","r");// fid即文件描述符
var buf = new Buffer(1000);
fs.readSync(fid,buf,0,1000,0);
console.log(buf.toString());
fs.closeSync(fid); //关闭文件
{% endhighlight %}

#### 系统调用： open
#### python实现： open("filename","mode").fileno()

文件描述符是操作系统用来跟踪打开的资源，所分配的文件描述符是尚未使用的最小的数值，资源一旦释放，对应的文件描述符就又能够使用了。

### 标准流

每个unix like的进程都有三个打开的资源，即stdin，stdout,stderr,其文件描述符分别为0,1,2。可以通过管道绑定到这三个资源。

在node中，这三个资源被绑定到process中，代码实现如下：

{%highlight javascript %}
console.log(process.stdin.fd) // 0
console.log(process.stdout.fd) // 1
console.log(process.stderr.fd) //2
{% endhighlight %}

#### python实现： sys模块下

## 第六章 进程皆有资源限制

每个进程都有资源限制，这些资源包括文件数，栈大小。 在系统调用中，可以查看getrlimit(2),返回为一个rlimit类型的struct, 包括软限制和硬限制两种。nodejs的核心库同样没实现这个函数，可以通过posix模块获取，与getrlimit(2)的说明不同，posix直接通过接受字符串，来映射到系统调用中的enum resource。

软限制是进程自身对用户的限制，硬限制则是操作系统对进程的限制，我们可以通过setrlimit来修改软限制，而如果进程的权限够大（sudo），甚至可以更改硬限制。显然软限制要比硬限制要小。实现代码如下：

{% highlight javascript %}
> var posix = require("posix");
> posix.getrlimit("nofile"); //字符串也可以是cpu、fsize，参见手册
{ soft: 4096, hard: 4096}
> posix.setrlimit("nofile", {soft: 1000})
undefined
> posix.getrlimit("nofile")
{ soft: 1000, hard: 4096}
> posix.setrlimit("nofile", {soft:10000})
Error: EINVAL, Invalid argument
{% endhighlight %}

#### 系统调用接口： getrlimit,setrlimit

#### python实现: resource模块下的getrlimit以及setrlimit

#### 实际应用场景： 在一些测试工具中，需要成千上万个并发网络链接，这是由于软硬限制，socket的数量将被限定，这时候可以根据这些函数进行更改。

## 第七章 进程皆有环境

这里的环境指的是"环境变量",环境变量包含进程数据的健值对。所有进程都从其父进程继承环境变量。在bash中，环境变量的设置可以通过VAR=value的语法实现。在node中，可以通过process.env获取一个环境变量的健值对，进而可以获取相关的环境变量。

#### 系统调用： setenv(3), getenv(3)

## 第八章 进程皆有参数

所有进程都可以访问名为ARGV的特殊数组来获取bash运行时传入进程的参数，argv是一个数组。node应用代码如下：
{% highlight javascript linenos %}
// test.js
console.log(process.argv);
{% endhighlight %}

然后在bash中运行
{% highlight bash %}
$ node testt.js arg1 arg2 arg3
[ 'node', '/home/abner/testt.js', 'arg1', 'arg2', 'arg3' ]
{% endhighlight %}

#### C语言实现： main的argc和argv

## 第九章进程皆有名

有两种运作在进程自身层面上的机制可以用来互通信息，一个是进程名称，另一个是退出码。在node中，可以如下获得：
{% highlight javascript %}
> console.log(process.title)
'node'
> process.title = "test"
undefined
> console.log(process.title)
test
{% endhighlight %}

在bash中，可以通过ps指令获取进程的pid及名称，在node程序改变自身名称之后，使用ps即可看到改变。

## 第十章 进程皆有退出码

当进程即将结束时，它还有最后一线机会留下自身的信息：退出码（unsigned char 类型). 通过退出码的机制来跟其他进程进行通信。要坚持退出码0代表顺利结束。在node中，可以通过process.exit(exitcode)来实现。如：
{% highlight javascript linenos  %}
// exitTest.js
console.log("The process is running");
process.exit(101)
{% endhighlight %}

使用bash查看结果：
{% highlight bash %}
$ node exitTest.js
The process is running
$ echo $?
101
{% endhighlight %}

## 第十一章



[1]: http://book.douban.com/subject/24298701/
