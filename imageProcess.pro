QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

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
    artistic_menu.cpp \
    common_def.cpp \
    contrast_dialog.cpp \
    enhance_menu.cpp \
    file_menu.cpp \
    filter_menu.cpp \
    gauss_dialog.cpp \
    help_menu.cpp \
    hist_bar.cpp \
    main.cpp \
    mainwindow.cpp \
    my_graphics_view.cpp \
    qcustomplot.cpp \
    segment_menu.cpp \
    sharpen_menu.cpp \
    threshold_dialog.cpp

HEADERS += \
    artistic_menu.h \
    common_def.h \
    contrast_dialog.h \
    enhance_menu.h \
    file_menu.h \
    filter_menu.h \
    gauss_dialog.h \
    help_menu.h \
    hist_bar.h \
    mainwindow.h \
    my_graphics_view.h \
    qcustomplot.h \
    segment_menu.h \
    sharpen_menu.h \
    threshold_dialog.h

FORMS += \
    contrastdialog.ui \
    gaussdialog.ui \
    histbar.ui \
    mainwindow.ui \
    thresholddialog.ui

INCLUDEPATH += D:/Opencv3.4.10/opencv/build/include \
               D:/Opencv3.4.10/opencv/build/include/opencv \
               D:/Opencv3.4.10/opencv/build/include/opencv2
LIBS += D:/Opencv3.4.10/opencv/build/x64/vc15/lib/opencv_world3410.lib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

RC_ICONS = exe_icon.ico
