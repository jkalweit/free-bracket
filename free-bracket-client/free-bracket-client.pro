CONFIG += c++11

TEMPLATE = app

QT += qml quick widgets

SOURCES += \
    FreeBracketClient.cpp \
    main.cpp

RESOURCES += \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)


HEADERS += \
    ApplicationData.h \
    FreeBracketClient.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../free-bracket-common/release/ -lfree-bracket-common
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../free-bracket-common/debug/ -lfree-bracket-common
else:unix: LIBS += -L$$OUT_PWD/../free-bracket-common/ -lfree-bracket-common

INCLUDEPATH += $$PWD/../free-bracket-common
DEPENDPATH += $$PWD/../free-bracket-common

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../free-bracket-common/release/libfree-bracket-common.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../free-bracket-common/debug/libfree-bracket-common.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../free-bracket-common/release/free-bracket-common.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../free-bracket-common/debug/free-bracket-common.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../free-bracket-common/libfree-bracket-common.a
