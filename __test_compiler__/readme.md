# 文档
https://ffmpeg.xianwaizhiyin.net/base-compile/linux-c-single.html

# 编译单个cpp程序文件
```shell
#  -c 是指只编译程序，不进行链接
#  -o 是指定输出文件名
# hello.c 就是输入文件, 如果一个 参数前面什么都没有，那他就会被当做输入，hello.c 前面就什么# 都没有。可以有多个输入文件，编译出一个输出文件
g++ -c -o ./hello.o ./src/hello.cpp

# hello.o 里面已经包含了 hello.c 对应的字节码，所以我们反编译看一下 hello.o 里面的字节码内容，执行以下命令。
objdump -d hello.o > hello.txt

# 链接程序，这里是动态链接
g++ -o ./hello hello.o

# 查看链接库信息
otool -L ./hello

# 静态链接
# 提示： ld: library not found for -lcrt0.o， 没有找到crt0.o
# 1. 静态链接并不是会把静态库的内容全部复制，只有用到才会复制。
# 2. 通常 静态链接 C 运行时库 是为了解决兼容性问题。另一种方式是不使用静态链接，直接把 libc.so 复制到运行程序当前目录，跟程序一起发布。
# 3. 
g++ -static -o ./hello ./hello.o 
```

# 编译多个cpp程序文件
大部分 C/C++ 开源项目，程序文件都有几百个，甚至几千几万个文件，但是不要被多文件吓到。g++ 编译的时候实际上都是单文件编译，然后链接阶段才是多文件。

无论是多庞大的C/C++ 项目，编译阶段，都是单个文件编译的，单个文件里面引用了外部的变量，函数。编译阶段只会把这些引用 替换成一些占位符号，例如 00 00 。在链接的时候才会替换这些占位符。

```shell
# 下面的命令，我是先 编译 zeus.cpp 文件的，虽然这个 zeus.cpp 文件依赖 sun.cpp，moon.cpp 跟 earth.cpp 3 个文件，但是 编译阶段不需要知道这 3 个 cpp 文件的存在，只需要在代码 里 include 一下他们的头文件，知道函数的定义即可。

# 编译阶段不需要知道 依赖函数的具体实现。
g++ -c -o ./zeus.o ./src/zeus.cpp
g++ -c -o ./sun.o ./src/sun.cpp
g++ -c -o ./moon.o ./src/moon.cpp
g++ -c -o ./earth.o ./src/earth.cpp

#链接
g++ -o ./zeus ./zeus.o ./sun.o ./earth.o ./moon.o
```

# 编译静态库
**静态库** 是可以链接进去 程序自身，**动态库**是共享库，可以由多个程序共享节省空间，动态库只有用到的时候才会加载。

调用静态库里面的函数，通常比调用动态库里面的函数会更高效一些。因为从汇编的角度看，调用静态库的函数只有一条 call 指令就直接跳到函数的地址了，而动态库的方式，需要两次 call，第一次是从 Procedure Linkage Table 表 先找到函数的地址。


```shell
# 生成静态库
# 1. ar 实际上是一个打包封装命令，打包成静态库，静态库也叫归档文件，实际上是对已经编译好的字节码进行封装，封装过程不涉及到链接，以前那些 call 占位符还是 00 00 。
# 2. 其实就是把 moon.o sun.o earth.o 三个文件里面的内容复制合成一个libstar.a文件
# 3. 编译成静态库并不会进行链接操作。
ar -rcs libstar.a moon.o sun.o earth.o


# 引用静态库
# 或者 gcc -v -o ./zeus ./zeus.o  -static -lstar
g++ -o ./zeus ./zeus.o ./libstar.a

```


# 封装静态库
先解释 一下 编译静态库 跟 封装静态库的 区别，编译静态库 就是前文中的 把多个 .o 文件打包成一个 libxxx.a 静态库。

而 封装静态库 是已经有一个第三方的 静态库，我们想在 这个第三方静态库 上面再加一些功能，提供给客户使用。

```shell
# 解压原来的静态库
ar -x libstar.a

# 重新把新的文件和旧的文件一起打包，dog.o pig.o是新增的功能
# 实际上，就是解压之后，再打包，我们使用第三方项目的静态库的时候也可以这样，先解压，再打包我们自己的 .o 文件进去。
ar -rcs libpower.a moon.o sun.o earth.o dog.o pig.o
```


# 编译动态库
由于 静态库 会把内容拷贝进去程序里面，所以会加大磁盘存储空间。

如果有100个软件都用到 某个库，如果这个库是静态链接到100个软件，数据量就会很大，所以操作系统一些底层库，都是以动态库的方式提供给上层程序调用的。

**而且动态库还有一个好处，可以很方便单独更新某个动态库，可以利用动态库的机制做一个插件系统。**

```shell
# 生成动态库
# -fPIC 是编译选项，PIC是 Position Independent Code 的缩写，表示要生成位置无关的代码。
g++ -fPIC -shared -o libstar.so sun.o moon.o earth.o

#  查看汇编代码
#  通过 Procedure Linkage Table 表，跳转到真正的函数。
objdump -d libstar.so > star-so-dump.txt

# 链接动态库
g++ -o ./zeus zeus.o libstar.so

# 运行./zeus，这里和静态链接库不一样的是，libstar.so文件不会打包进zeus文件
# 而是运行时动态加载libstar.so
# 注意： Linux 环境默认不会从当前路径 加载动态库。而 Windows 环境会从当前路径 加载动态库。
./zeus
```

# 显式调用动态库

# 封装静态库成动态库
把 libstar.a 解开还原成 多个 .o 文件，再一起编译出动态库。
```shell
# 解压
ar -x libstar.a
# 打包动态库
gcc -fPIC -shared -o libpower.so dog.o pig.o moon.o earth.o sun.o
# 链接动态库
gcc -o hades hades.o libpower.so
```
