PROJECT(qml-desktop)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

FIND_PACKAGE(Qt5Quick REQUIRED)
FIND_PACKAGE(Qt5DBus REQUIRED)
FIND_PACKAGE(PkgConfig REQUIRED)

PKG_CHECK_MODULES(GLIB glib-2.0)

INCLUDE_DIRECTORIES(${Qt5Quick_INCLUDE_DIRS})
ADD_DEFINITIONS(${Qt5Quick_DEFINITIONS})
INCLUDE_DIRECTORIES(${Qt5DBus_INCLUDE_DIRS})
ADD_DEFINITIONS(${Qt5DBus_DEFINITIONS})

INCLUDE_DIRECTORIES(${GLIB_INCLUDE_DIRS})
LINK_DIRECTORIES(${GLIB_LIBRARY_DIRS})
ADD_DEFINITIONS(${GLIB_CXXFLAGS_OTHER})

EXECUTE_PROCESS(COMMAND qmake -query QT_INSTALL_QML OUTPUT_VARIABLE QT_INSTALL_QML OUTPUT_STRIP_TRAILING_WHITESPACE)

SET(LIB_SRCS
    ${CMAKE_SOURCE_DIR}/src/qmldesktop_plugin.cpp
    ${CMAKE_SOURCE_DIR}/src/qmldesktop_plugin.h
    ${CMAKE_SOURCE_DIR}/src/desktop/desktopfile.cpp
    ${CMAKE_SOURCE_DIR}/src/desktop/desktopfile.h
    ${CMAKE_SOURCE_DIR}/src/desktop/desktopscrobbler.cpp
    ${CMAKE_SOURCE_DIR}/src/desktop/desktopscrobbler.h
    ${CMAKE_SOURCE_DIR}/src/keyeventfilter/keyeventfilter.cpp
    ${CMAKE_SOURCE_DIR}/src/keyeventfilter/keyeventfilter.h
    ${CMAKE_SOURCE_DIR}/src/mixer/alsamixer.cpp
    ${CMAKE_SOURCE_DIR}/src/mixer/alsamixer.h
    ${CMAKE_SOURCE_DIR}/src/mixer/pulseaudiomixer.cpp
    ${CMAKE_SOURCE_DIR}/src/mixer/pulseaudiomixer.h
    ${CMAKE_SOURCE_DIR}/src/mixer/sound.cpp
    ${CMAKE_SOURCE_DIR}/src/mixer/sound.h
    ${CMAKE_SOURCE_DIR}/src/mpris/mpris2player.cpp
    ${CMAKE_SOURCE_DIR}/src/mpris/mpris2player.h
    ${CMAKE_SOURCE_DIR}/src/mpris/mprisconnection.cpp
    ${CMAKE_SOURCE_DIR}/src/mpris/mprisconnection.h
    ${CMAKE_SOURCE_DIR}/src/notifications/notificationserver.cpp
    ${CMAKE_SOURCE_DIR}/src/notifications/notificationserver.h
    ${CMAKE_SOURCE_DIR}/src/notifications/notification.h
    ${CMAKE_SOURCE_DIR}/src/notifications/notificationadaptor.h
    ${CMAKE_SOURCE_DIR}/src/qquicklist/qobjectlistmodel.cpp
    ${CMAKE_SOURCE_DIR}/src/qquicklist/qobjectlistmodel.h
    ${CMAKE_SOURCE_DIR}/src/qquicklist/qquicklist.h
    ${CMAKE_SOURCE_DIR}/src/upower/upowerconnection.cpp
    ${CMAKE_SOURCE_DIR}/src/upower/upowerconnection.h
    ${CMAKE_SOURCE_DIR}/src/upower/upowerdevice.cpp
    ${CMAKE_SOURCE_DIR}/src/upower/upowerdevice.h
    ${CMAKE_SOURCE_DIR}/src/upower/upowerdevicestate.h
    ${CMAKE_SOURCE_DIR}/src/upower/upowerdevicetype.h
    ${CMAKE_SOURCE_DIR}/src/processhelper/processhelper.h
)

ADD_LIBRARY(MaterialDesktop SHARED ${LIB_SRCS})
TARGET_LINK_LIBRARIES(MaterialDesktop Qt5::Quick)
TARGET_LINK_LIBRARIES(MaterialDesktop Qt5::DBus)
TARGET_LINK_LIBRARIES(MaterialDesktop Qt5::Qml)
TARGET_LINK_LIBRARIES(MaterialDesktop pulse)
TARGET_LINK_LIBRARIES(MaterialDesktop pulse-mainloop-glib)

SET(FILES_TO_INSTALL ${CMAKE_CURRENT_BINARY_DIR}/libMaterialDesktop.so ${CMAKE_CURRENT_SOURCE_DIR}/src/qmldir)

INSTALL(FILES ${FILES_TO_INSTALL} DESTINATION ${QT_INSTALL_QML}/Material/Desktop)
