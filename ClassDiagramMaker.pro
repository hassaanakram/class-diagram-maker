TEMPLATE = app
TARGET = ClassDiagramMaker

QT = core gui
QT += svg
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
      Headers/array.h \
      Headers/button.h \
      Headers/class.h \
      Headers/constructor.h \
      Headers/container.h \
      Headers/function.h \
      Headers/globals.h \
      Headers/variable.h \
      Headers/win_main.h

SOURCES += \
     Source/array.cpp \
     Source/button.cpp \
     Source/class.cpp \
     Source/constructor.cpp \
     Source/container.cpp \
     Source/function.cpp \
     Source/globals.cpp \
     Source/main.cpp \
     Source/variable.cpp \
     Source/win_main.cpp
