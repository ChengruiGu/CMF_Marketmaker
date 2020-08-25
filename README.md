# CMF_Marketmaker

基于Qt + Sqlite3实现的期货做市系统，功能包括用户注册、权限管理、多策略做市、风控设置等。

### Qt
Qt 是一套方便的C++库，封装了图形界面的绘制和众多C++原有的特性。
Qt入门请参照这一教程：http://c.biancheng.net/qt/ 看到第12节“第一个Qt程序”就能有初步的了解了。
笔者之前学习时的小作品可以参考：https://github.com/ChengruiGu/tmaj
重点了解一下：
1. 信号、槽的用法，比如怎样给一个按钮添加点击后发生的事件
2. QtSQL、QtStandardItemModel等和数据库有关的方法
3. QProcess等创建进程的方法
记得按照教程安装MinGW编译器，Visual Studio自带的MSVC编译器可能无法识别汉字字符，非常麻烦

### SQLite3
需要开发者对sql语句有一定了解，能进行基础增删查改。教程参考：https://www.runoob.com/sqlite/sqlite-tutorial.html
写sql语句时，因为Qt Creater没法对sql语句进行语法提示，所以需要仔细检查对应的表格名、选项名和条件是否一致，建议仔细参考dbcontroller中是如何定义表格的
使用qDebug()可以打印输出，调试时很有用
sql执行失败的时候，.lastError()方法可以查看失败原因
本项目使用到的Qt数据库相关库有：QSqlDatabase(https://doc.qt.io/qt-5/qsqldatabase.html); QSqlQuery(https://doc.qt.io/qt-5/qsqlquery.html)。前者负责建立数据库连接、创建数据库，后者负责执行sql语句。

### TODO LIST
1. 风控设置功能的后台逻辑，riskctrlfold.ui调整布局
2. 监控指标功能
3. 底部状态栏显示账户信息

### 各文件手册
#### mainWindow.cpp, mainWindow.h, mainWindow.ui
这是系统的主界面
编辑mainWindow的菜单栏action时可能无法直接输入中文，这时右侧黄色的编辑区中text里可以输中文
请确保action的期货中文名称和数据库中（product_source.txt）的期货中文名称一致

#### mm_page.cpp, mm_page.h, mm_page.ui
系统的主交易页面，mainwindow中每当菜单被点击就会创建一个mm_page实例
mm := market making

#### dbcontrol.cpp, dbcontrol.h
创建数据库的文件，在mainwindow创建时调用