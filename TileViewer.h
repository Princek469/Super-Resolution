#ifndef TILEVIEWER_H
#define TILEVIEWER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QDir>
#include <QFileInfo>

class TileViewer : public QWidget {
    Q_OBJECT

public:
    TileViewer(const QString &tileDirectory, const QString &inputImageName, QWidget *parent = nullptr);

private slots:
    void loadTile(int index);

private:
    int currentTileIndex;
    QString tileDirectory;
    QString baseName;
    QLabel *tileLabel;
    QPushButton *previousTileButton;
    QPushButton *nextTileButton;
};

#endif // TILEVIEWER_H
