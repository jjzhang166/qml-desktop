#ifndef THEME_H
#define THEME_H

#include <QObject>
#include <QIcon>
#include <QDir>
#include <QSettings>

class Theme : public QObject
{
    Q_OBJECT

public:
    Theme(QObject *parent = 0, QString themeName = QIcon::themeName());
    QString lookupIcon(QString iconName, int iconSize);
    QString backupIcon(int iconSize);

    QList<Theme*> parents;

private:
    bool directoryMatchesSize(QString dirSize, int iconSize);
    int directorySizeDistance(QString dirSize, int iconSize);

    QSettings* themeIndex;
    QDir themeDir;
    QStringList subdirs;
    QStringList extensions;
};

#endif // THEME_H
