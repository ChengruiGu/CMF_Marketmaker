# CMF_Marketmaker

基于Qt + Sqlite3实现的期货做市系统，功能包括用户注册、权限管理、多策略做市、风控设置等。

## Qt
Qt 是一套方便的C++库，封装了图形界面的绘制和众多C++原有的特性。
Qt入门请参照这一教程：http://c.biancheng.net/qt/ 看到第12节“第一个Qt程序”就能有初步的了解了。
笔者之前学习时的小作品可以参考：https://github.com/ChengruiGu/tmaj
重点了解一下：
1. 信号、槽的用法，比如怎样给一个按钮添加点击后发生的事件
2. QtSQL、QtStandardItemModel等和数据库有关的方法
3. QProcess等创建进程的方法
记得按照教程安装MinGW编译器，Visual Studio自带的MSVC编译器可能无法识别汉字字符，非常麻烦


写sql语句时，因为软件没法对sql语句进行语法提示，所以需要仔细检查对应的表格名、选项名和条件是否正确，建议仔细参考dbcontroller中是如何定义表格的。
使用qDebug可以打印输出，调试时很有用。sql执行失败的时候，.lastError()方法可以查看失败原因

## 各文件手册
### mainWindow.cpp, mainWindow.h, mainWindow.ui
这是系统的主界面

### mm_page.cpp, mm_page.h, mm_page.ui
系统的主交易页面，mm stands for market making