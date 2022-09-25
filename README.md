# 基于协程的轻量级分布式RPC框架

## 项目介绍
该项目基于C++20的stackless协程实现了一个带服务治理的RPC框架，该项目主要包括协程同步模块、网络模块、序列化模块以及服务注册和发现、服务订阅与推送、负载均衡、健康检测和连接复用等模块组成。

## 项目构建与运行
1. 安装yaml-cpp 需要sudo权限
```
git clone https://github.com/jbeder/yaml-cpp.git && cd yaml-cpp
mkdir build && cd build
cmake -DYAML_BUILD_SHARED_LIBS=on ..
sudo make install
```
如若报错，请在~/.bashrc文件中添加
```shell
export LD_LIBRARY_PATH=/usr/local/lib
```
2. 安装g++11编译器

使用以下方法升级g++编译器（ubuntu）
```
sudo apt install software-properties-common
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt install gcc-11 g++-11
```
然后设置gcc-11 g++-11为高优先级（优先使用版本11）
```shell
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 1

sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 1

sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 10

sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 10
```
3. 构建项目
```
mkdir build && cd build
cmake .. && make
```

4. 测试项目
在根目录运行bin目录下程序进行测试

## 致谢

- sylar C++高性能分布式服务器框架：https://github.com/sylar-yin/sylar
- sofa-pbrpc A light-weight RPC implement of google protobuf RPC framework：https://github.com/baidu/sofa-pbrpc
- grpc：https://github.com/grpc/grpc
- ACID: 分布式服务治理框架：https://github.com/zavier-wong/acid
- 基于zookeeper的分布式网络通信rpc框架：https://github.com/attackoncs/rpc

