#include "theme.h"

Theme::Theme(QObject *parent, QString themeName) : QObject(parent) {
    extensions << "svg" << "png" << "svgz" << "xpm";
    QStringList envList;
    if (qEnvironmentVariableIsEmpty("XDG_DATA_DIRS")) {
       envList <<  "/usr/local/share/" << "/usr/share/";
    } else {
        envList = QVariant(qgetenv("XDG_DATA_DIRS")).toString().split(":");
    }
    for (int i = 0; i < envList.length(); i++) {
        if (QDir(envList.at(i) + themeName).exists()) {
            themeDir = QDir(envList.at(i) + themeName);
            subdirs = themeDir.entryList(QDir::AllDirs);
            themeIndex = new QSettings(themeDir.absoluteFilePath("index.theme"));
            if (themeIndex->value("Icon Theme/Inherits").isNull()) {
                break;
            } else {
                QStringList themeParents = themeIndex->value("Icon Theme/Inherits").toString().split(",");
                for (int j = 0; j < themeParents.length(); j++) {
                    parents << new Theme(this, themeParents.at(j));
                }
                break;
            }
        }
    }
}

QString Theme::lookupIcon(QString iconName, int iconSize) {
    QString fileName = "%1/apps/%2.%3";
    int minimalSize = 20;
    QString closestFile;
    for (int i = 0; i < subdirs.length(); i++) {
        for (int j = 0; j < extensions.length(); j++) {
            if (directoryMatchesSize(subdirs[i], iconSize)) {
                if (themeDir.exists(fileName.arg(subdirs[i], iconName, extensions[j]))) {
                    return themeDir.absoluteFilePath(fileName.arg(subdirs[i], iconName, extensions[j]));
                }
            } else if (directorySizeDistance(subdirs[i], iconSize) < minimalSize && themeDir.exists(fileName.arg(subdirs[i], iconName, extensions[j]))) {
                closestFile = fileName.arg(subdirs[i], iconName, extensions[j]);
                minimalSize = directorySizeDistance(subdirs[i], iconSize);
            }
        }
    }
    if (!closestFile.isEmpty()) {
        return themeDir.absoluteFilePath(closestFile);
    }
    return "";
}

QString Theme::backupIcon(int iconSize) {
    QString scalable = "scalable/mimetypes/application-x-executable.svg";
    if (themeDir.exists(scalable)) {
        return themeDir.absoluteFilePath(scalable);
    } else if (themeDir.exists(scalable + "z")) {
        return themeDir.absoluteFilePath(scalable + "z");
    } else {
        QString nonScalable = "%1x%1/mimetypes/application-x-executable";
        if (themeDir.exists(nonScalable.arg(iconSize) + ".png")) {
            return themeDir.absoluteFilePath(nonScalable.arg(iconSize) + ".png");
        } else if (themeDir.exists(nonScalable.arg(iconSize) + ".xpm")) {
            return themeDir.absoluteFilePath(nonScalable.arg(iconSize) + ".xpm");
        } else {
            for (int i = 0; i < subdirs.length(); i++) {
                if (themeDir.exists(subdirs[i] + "/mimetypes/application-x-executable.png")) {
                    return themeDir.absoluteFilePath(subdirs[i] + "/mimetypes/application-x-executable.png");
                } else if (themeDir.exists(subdirs[i] + "/mimetypes/application-x-executable.xpm")) {
                    return themeDir.absoluteFilePath(subdirs[i] + "/mimetypes/application-x-executable.xpm");
                }
            }
            return "";
        }
    }
}

bool Theme::directoryMatchesSize(QString dirSize, int iconSize) {
    themeIndex->beginGroup(QString("%1/apps").arg(dirSize));
    QString type = themeIndex->value("Type").toString();
    int themeSize = themeIndex->value("Size").toInt();
    int minSize = themeIndex->value("MinSize").toInt();
    int maxSize = themeIndex->value("MaxSize").toInt();
    int threshold = themeIndex->value("Threshold").toInt();
    themeIndex->endGroup();
    if (type == "Fixed") {
        return themeSize == iconSize;
    }
    if (type == "Scaled") {
        return minSize <= iconSize <= maxSize;
    }
    if (type == "Threshold") {
        return themeSize - threshold <= iconSize <= themeSize + threshold;
    }
    return false;
}

int Theme::directorySizeDistance(QString dirSize, int iconSize) {
    themeIndex->beginGroup(QString("%1/apps").arg(dirSize));
    QString type = themeIndex->value("Type").toString();
    int themeSize = themeIndex->value("Size").toInt();
    int minSize = themeIndex->value("MinSize").toInt();
    int maxSize = themeIndex->value("MaxSize").toInt();
    int threshold = themeIndex->value("Threshold").toInt();
    themeIndex->endGroup();
    if (type == "Fixed") {
        return abs(themeSize - iconSize);
    }
    if (type == "Scaled") {
        if (iconSize < minSize) {
            return minSize - iconSize;
        }
        if (iconSize > maxSize) {
            return iconSize - maxSize;
        }
        return 0;
    }
    if (type == "Threshold") {
        if (iconSize < themeSize - threshold) {
            return minSize - iconSize;
        }
        if (iconSize > themeSize + threshold) {
            return iconSize - maxSize;
        }
        return 0;
    }
    return 0;
}
