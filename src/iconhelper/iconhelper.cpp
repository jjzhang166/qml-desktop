#include "iconhelper.h"

IconHelper::IconHelper(int iconSize, QObject *parent) : QObject(parent), theme(this), m_iconSize(iconSize) {
    hicolor = new Theme(this, "hicolor");
    processIconSize();
}

void IconHelper::processIconName(QString iconSource) {
    if (iconSource.endsWith(".png", Qt::CaseInsensitive) || iconSource.endsWith(".svg", Qt::CaseInsensitive) || iconSource.endsWith(".xpm", Qt::CaseInsensitive) || iconSource.endsWith(".svgz", Qt::CaseInsensitive)) {
        iconSource.truncate(iconSource.length() - 4);
    }
}

void IconHelper::processIconSize() {
    QList<int> sizesList;
    sizesList << 1024 << 512 << 256 << 192 << 128 << 96  << 72 << 64 << 48 << 36 << 32 << 24 << 22 << 16 << 8;
    int diff = abs(m_iconSize - sizesList[0]);
    int num1 = sizesList[0];
    for (int a = 0; a < sizesList.length(); a++) {
        if (diff > abs(m_iconSize - sizesList[a]))
        {
            diff = abs(m_iconSize - sizesList[a]);
            num1 = sizesList[a];
        }
    }
    m_iconSize = num1;
}

QString IconHelper::findIcon(QString iconName) {
    QString fileName = findIconHelper(iconName, &theme);
    if (!fileName.isEmpty()) {
        return fileName;
    }
    fileName = findIconHelper(iconName, hicolor);
    if (!fileName.isEmpty()) {
        return fileName;
    }
    fileName = theme.backupIcon(m_iconSize);
    if (!fileName.isEmpty()) {
        return fileName;
    }
    return hicolor->backupIcon(m_iconSize);
}

QString IconHelper::findIconHelper(QString iconName, Theme *theme) {
    processIconName(iconName);
    QString fileName = theme->lookupIcon(iconName, m_iconSize);
    if (!fileName.isEmpty()) {
        return fileName;
    }
    if (!theme->parents.isEmpty()) {
        for (int i = 0; i < theme->parents.length(); i++) {
            fileName = findIconHelper(iconName, theme->parents.at(i));
            if (!fileName.isEmpty()) {
                return fileName;
            }
        }
    }
    return "";
}
