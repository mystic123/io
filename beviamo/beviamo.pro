TEMPLATE = app

QT += qml quick core widgets network

qtHaveModule(webengine) {
        QT += webengine
        DEFINES += QT_WEBVIEW_WEBENGINE_BACKEND
}

INCLUDEPATH += ../shared/

SOURCES += \
		main.cpp \
		client.cpp \
		../shared/event.cpp \
		../shared/user.cpp \
		../shared/global.cpp

HEADERS +=  \
		client.h \
		../shared/event.h \
                ../shared/user.h \
                ../shared/global.h


RESOURCES += qml.qrc

CONFIG += c++11
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
		android/gradle/wrapper/gradle-wrapper.jar \
		android/AndroidManifest.xml \
		android/res/values/libs.xml \
		android/build.gradle \
		android/gradle/wrapper/gradle-wrapper.properties \
		android/gradlew \
		android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
