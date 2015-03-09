#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QObject>
#include "theme.h"

class IconHelper : public QObject
{
    Q_OBJECT
public:
     IconHelper(int iconSize, QObject *parent = 0);
     QString findIcon(QString iconName);

private:
     QString findIconHelper(QString iconName, Theme* theme);
     void processIconName(QString iconSource);
     void processIconSize();

     Theme theme;
     Theme* hicolor;
     int m_iconSize;
};

#endif // ICONHELPER_H
