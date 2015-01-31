QML Desktop
=====================

[![Build 
Status](https://travis-ci.org/papyros/qml-desktop.svg?branch=cmake)](https://travis-ci.org/papyros/qml-desktop)

The QML Desktop framework provides a plugin for QML that exposes different system-integrated DBus "components" that are useful for desktop shells as well as apps that would like to get access to notifications or music players, for example.

### How to use

First, compile and install the plugin:

    $ mkdir .build
    $ cd .build
    $ cmake ..
    $ make #or your favourite build tool
    # make install

Then, to use in your desktop shell, simply import the framework like this:

    import Material.Desktop 0.1

### Components
 - MprisConnection
 - NotificationServer
 - UPower
 - DesktopFile + Scrobbler
 - Sound + Mixer
 - KeyEventFilter
 
### To Do
 - Add documentation
 - Port other components to qquicklist for animations
 - Add tests
