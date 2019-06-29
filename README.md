# ProcessPoolServer

参考：

https://segmentfault.com/a/1190000017043539#articleHeader8

https://github.com/KuiHuaZi/myHttpServer

## usage
```
cd src
make clean
make
./HttpServer 127.0.0.1 8080 5 200
```
浏览器地址栏输入：127.0.0.1:8080/home.html

## 测试每个模块
```
make -f Makefile_debug_TimerHeap clean
make -f Makefile_debug_TimerHeap
./TimerHeap
```
