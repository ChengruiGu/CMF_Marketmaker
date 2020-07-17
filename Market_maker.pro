QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bar.cpp \
    future_mm.cpp \
    login_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    mm_page.cpp \
    mm_page2.cpp \
    setting_addconract.cpp \
    setting_changepwd.cpp \
    setting_chooseproduct.cpp \
    setting_createrole.cpp \
    setting_manageuser.cpp \
    setting_resetpwd.cpp \
    setting_riskctrl.cpp \
    setting_riskprmt.cpp \
    setting_setmm.cpp \
    setting_setrole.cpp

HEADERS += \
    bar.h \
    future_mm.h \
    login_dialog.h \
    mainwindow.h \
    mm_page.h \
    mm_page2.h \
    setting_addconract.h \
    setting_changepwd.h \
    setting_chooseproduct.h \
    setting_createrole.h \
    setting_manageuser.h \
    setting_resetpwd.h \
    setting_riskctrl.h \
    setting_riskprmt.h \
    setting_setmm.h \
    setting_setrole.h

FORMS += \
    login_dialog.ui \
    mainwindow.ui \
    mm_page.ui \
    mm_page2.ui \
    setting_addconract.ui \
    setting_changepwd.ui \
    setting_chooseproduct.ui \
    setting_createrole.ui \
    setting_manageuser.ui \
    setting_resetpwd.ui \
    setting_riskctrl.ui \
    setting_riskprmt.ui \
    setting_setmm.ui \
    setting_setrole.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
