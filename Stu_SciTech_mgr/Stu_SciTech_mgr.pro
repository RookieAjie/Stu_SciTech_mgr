QT       += core gui sql
QT += axcontainer
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    achievement_add.cpp \
    achievement_update.cpp \
    add_admin.cpp \
    add_college.cpp \
    add_gain.cpp \
    add_group.cpp \
    add_info.cpp \
    apply_achievement.cpp \
    apply_gain.cpp \
    delete_achiv.cpp \
    delete_admin.cpp \
    delete_college.cpp \
    delete_gain.cpp \
    delete_group.cpp \
    delete_stu.cpp \
    imagedialog.cpp \
    main.cpp \
    mainwindow.cpp \
    page_login.cpp \
    stu_sql.cpp \
    stumainwindow.cpp \
    update_admin.cpp \
    update_college.cpp \
    update_gain.cpp \
    update_group.cpp \
    uupdate.cpp

HEADERS += \
    achievement_add.h \
    achievement_update.h \
    add_admin.h \
    add_college.h \
    add_gain.h \
    add_group.h \
    add_info.h \
    apply_achievement.h \
    apply_gain.h \
    delete_achiv.h \
    delete_admin.h \
    delete_college.h \
    delete_gain.h \
    delete_group.h \
    delete_stu.h \
    imagedialog.h \
    mainwindow.h \
    page_login.h \
    stu_sql.h \
    stumainwindow.h \
    update_admin.h \
    update_college.h \
    update_gain.h \
    update_group.h \
    uupdate.h

FORMS += \
    achievement_add.ui \
    achievement_update.ui \
    add_admin.ui \
    add_college.ui \
    add_gain.ui \
    add_group.ui \
    add_info.ui \
    apply_achievement.ui \
    apply_gain.ui \
    delete_achiv.ui \
    delete_admin.ui \
    delete_college.ui \
    delete_gain.ui \
    delete_group.ui \
    delete_stu.ui \
    mainwindow.ui \
    page_login.ui \
    stumainwindow.ui \
    update_admin.ui \
    update_college.ui \
    update_gain.ui \
    update_group.ui \
    uupdate.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
