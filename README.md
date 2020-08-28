# CMF_Marketmaker

基于Qt + Sqlite3实现的期货做市系统，功能包括用户注册、权限管理、多策略做市、风控设置等。

## 操作指南：
1. 在"策略管理"中上传策略、参数，策略需是.exe可执行文件，参数需是.txt文件
2. 上传成功后，勾选对应的合约，如果合约不存在请点击"合约管理"并添加
3. 在"做市权限管理"中，勾选交易员对应的合约权限
4. 主界面上方的菜单栏中，点击"期货做市"->对应的交易所->对应的品种，打开交易界面
5. 左上方会显示可交易的合约、可使用的策略和参数，选择完成后，点击"启动"按钮
6. 交易进程返回的内容会显示在左下方
7. 点击"停止"或"全部停止"中止交易程序
***
### Qt
Qt 是一套方便的C++库，封装了图形界面的绘制和众多C++原有的特性。

Qt入门请参照这一教程：http://c.biancheng.net/qt/ 看到第12节“第一个Qt程序”就能有初步的了解了。

笔者之前学习时的小作品可以参考：https://github.com/ChengruiGu/tmaj

重点了解一下：
1. 信号、槽的用法，比如怎样给一个按钮添加点击后发生的事件
2. QtSQL、QtStandardItemModel等和数据库有关的方法
3. QProcess等创建进程的方法

记得按照教程安装MinGW编译器，Visual Studio自带的MSVC编译器可能无法识别汉字字符，非常麻烦
***
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
5. 策略运行时读取参数的接口（mm_tradecontrol.cpp中的TODO）
***
## 各文件具体介绍
### account_login.cpp/.h.ui
mainWindow下方状态栏的“登录交易账户”界面，目前登陆功能未实现
***
### bar.cpp
交易页面右下角的柱状图
***
### ctp_login.cpp
尝试在此处实现登录ctp交易账户，并返回账户信息，更新mainWindow状态栏
***
### dbcontroller.cpp, dbcontroller.h
创建数据库的文件，在mainwindow创建时调用

DB_ER_diagram.png 绘制了系统数据库中表格之间的关系，可以参考
***
### login_dialog.cpp/.h/.ui
登录界面，在main.cpp中被调用（开发时为了方便调试可以直接在main里注释掉）
***
### main.cpp
main函数
去掉注释可以显示login窗口
***
### mainWindow.cpp, mainWindow.h, mainWindow.ui
这是系统的主界面，集成了所有功能，可以从mainWindow.cpp开始读代码，了解每个功能是怎么实现的

编辑mainWindow的菜单栏action时可能无法直接输入中文，这时右侧黄色的编辑区中text里可以输中文

请确保action的期货中文名称和数据库中（product_source.txt）的期货中文名称一致
***
### mm_page.cpp, mm_page.h, mm_page.ui
系统的主交易页面，mainwindow中每当菜单被点击就会创建一个mm_page实例

mm := market making
***
### mm_page2.cpp/.h/.ui
期权交易页面 尚未开发
***
### mm_tradecontrol.cpp, mm_tradecontrol.h, mm_tradecontrol.ui
交易进程运行控制，每个mm_tradecontrol对应一个合约的交易进程，可以启动、停止、选择策略、选择参数。

在做市页面mm_page创建时会被创建，mm_page可以调用start_trading(),suspend_trading()来控制交易的启动和停止
***
### mm_addcontract.cpp/.h/.ui
合约管理
***
### setting_changepwd.cpp/.h/ui
修改密码，尚未实现功能。实现起来应该比较简单
TODO: 连接数据库，查询对应username，改密码
***
### setting_chooseproduct.cpp/.h/.ui
以setting_开头的文件都是系统设置相关的功能，开发时有许多相似之处，这里以setting_chooseproduct品种管理为例子，详细介绍一下。

setting系列的.ui文件一般都会有一个view对象，用来显示信息，chooseproduct.ui中用的是tableview，可以显示多列信息；如果只需要单列也可以使用listview。

在.cpp文件中可以看到，view对象会和一个model绑定在一起，操作model便可以改变view显示的信息；chooseproduct.cpp中使用了QSqlRelationalTableModel，这个model可以直接连接数据库读取信息，具体用法可以参考QSqlRelationalTableModel，QSqlRecord的文档和chooseproduct.cpp中的注释，

对数据库进行增删改有两种方式。第一种是通过model进行操作，先修改model，再同步数据库，这样做不需要写sql语句；chooseproduct.cpp采用了这种写法。
第二种则是直接使用sql语句对数据库进行操作，这样在没有model或者model不方便时仍可以操作；uploadstrategy.cpp采用了这种写法。
***
### setting_createrole.cpp/.h/.ui
创建用户，在setting_manageuser中调用
***
### setting_manageuser.cpp/.h/.ui
角色管理
***
### setting_resetpwd.cpp/.h/.ui
密码重置，在setting_manageuser中调用，尚未实现功能。做起来应该跟setting_changepwd差不多
***
### setting_riskprmt
读取风控数据

TODO:让读取的数据能显示在mm_page上
***
### setting_riskctrl category fold p product
风控数据设置的5个文件。具体功能可参考.ui文件中设计的界面。

TODO: setting_riskctrlfold 的缩放有些问题，再次点击按钮之后无法使窗口缩小；可能不该用setVisible()

TODO: 风控的功能都尚未连接数据库，表格未设计
***
### setting_setmm.cpp/.h/.ui
做市权限管理
***
### setting_setrole.cpp/.h/.ui
角色权限管理
***
### setting_uploadstrategy.cpp/.h/.ui
策略管理与参数管理。
***
### twolabel.cpp/.h/.ui
由两个label组成的简单控件，在mainWindow底部状态栏中调用
***
### welcomepage.cpp/.h/.ui
欢迎页
***