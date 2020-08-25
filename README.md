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

本项目使用到的Qt数据库相关库有：QSqlDatabase(https://doc.qt.io/qt-5/qsqldatabase.html); QSqlQuery(https://doc.qt.io/qt-5/qsqlquery.html)

前者负责建立数据库连接、创建数据库，后者负责执行sql语句。

### TODO LIST
1. 风控设置功能的后台逻辑，riskctrlfold.ui调整布局
2. 监控指标功能
3. 底部状态栏显示账户信息
4. 期权交易、合约、权限等相关功能
5. 上传参数、参数管理（应该基本跟策略管理setting_uploadstrategy.cpp代码一样）
6. 策略运行时读取参数的接口（mm_tradecontrol.cpp中的TODO）

### 各文件具体介绍
#### mainWindow.cpp, mainWindow.h, mainWindow.ui
这是系统的主界面，集成了所有功能，可以从mainWindow.cpp开始读代码，了解每个功能是怎么实现的

编辑mainWindow的菜单栏action时可能无法直接输入中文，这时右侧黄色的编辑区中text里可以输中文

请确保action的期货中文名称和数据库中（product_source.txt）的期货中文名称一致
***
#### mm_page.cpp, mm_page.h, mm_page.ui
系统的主交易页面，mainwindow中每当菜单被点击就会创建一个mm_page实例

mm := market making
***
#### dbcontrol.cpp, dbcontrol.h
创建数据库的文件，在mainwindow创建时调用

DB_ER_diagram.png 绘制了系统数据库中表格之间的关系，可以参考
***
#### mm_tradecontrol.cpp, mm_tradecontrol.h, mm_tradecontrol.ui
交易进程运行控制，每个mm_tradecontrol对应一个合约的交易进程，可以启动、停止、选择策略、选择参数。

在做市页面mm_page创建时会被创建，mm_page可以调用start_trading(),suspend_trading()来控制交易的启动和停止
***
#### setting_chooseproduct.cpp/.h/.ui
以setting_开头的文件都是系统设置相关的功能，开发时有许多相似之处，这里以setting_chooseproduct品种管理为例子，详细介绍一下。

setting系列的.ui文件一般都会有一个view对象，用来显示信息，chooseproduct.ui中用的是tableview，可以显示多列信息；如果只需要单列也可以使用listview。

在.cpp文件中可以看到，view对象会和一个model绑定在一起，操作model便可以改变view显示的信息；chooseproduct.cpp中使用了QSqlRelationalTableModel，这个model可以直接连接数据库读取信息，具体用法可以参考QSqlRelationalTableModel，QSqlRecord的文档和chooseproduct.cpp中的注释，

对数据库进行增删改有两种方式。第一种是通过model进行操作，先修改model，再同步数据库，这样做不需要写sql语句；chooseproduct.cpp采用了这种写法。
第二种则是直接使用sql语句对数据库进行操作，这样在没有model或者model不方便时仍可以操作；uploadstrategy.cpp采用了这种写法。
***