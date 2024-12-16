#include "TileViewer.h"

TileViewer::TileViewer(const QString &tileDirectory, const QString &inputImageName, QWidget *parent)
    : QWidget(parent), currentTileIndex(0), tileDirectory(tileDirectory) {

    baseName = QFileInfo(inputImageName).baseName();

    setWindowTitle("Tile Viewer");
    resize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create a QScrollArea to handle large images
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // Create a QLabel to display the tile
    tileLabel = new QLabel(scrollArea);
    tileLabel->setStyleSheet("border: none; qproperty-alignment: AlignCenter;");
    tileLabel->setAlignment(Qt::AlignCenter);
    scrollArea->setWidget(tileLabel);

    layout->addWidget(scrollArea);

    // Create buttons for navigation
    previousTileButton = new QPushButton("Previous Tile", this);
    nextTileButton = new QPushButton("Next Tile", this);
    layout->addWidget(previousTileButton);
    layout->addWidget(nextTileButton);

    // Load the first tile
    loadTile(currentTileIndex);

    // Connect button signals to load the next and previous tiles
    connect(nextTileButton, &QPushButton::clicked, this, [this]() {
        currentTileIndex++;
        loadTile(currentTileIndex);
    });

    connect(previousTileButton, &QPushButton::clicked, this, [this]() {
        if (currentTileIndex > 0) {
            currentTileIndex--;
            loadTile(currentTileIndex);
        }
    });
}

void TileViewer::loadTile(int index) {
    QString tileFileName = QString("%1_out%2_out.jpg").arg(baseName).arg(index);
    QString tilePath = QDir(tileDirectory).filePath(tileFileName);

    QPixmap tilePixmap(tilePath);
    if (!tilePixmap.isNull()) {
        tileLabel->setPixmap(tilePixmap);
        tileLabel->setScaledContents(true);
        tileLabel->adjustSize();
    } else {
        // Handle case where the tile does not exist
        tileLabel->setText("No more tiles to display.");
        nextTileButton->setEnabled(false); // Disable button if no more tiles
    }

    // Update button states based on the current index
    previousTileButton->setEnabled(currentTileIndex > 0);
    nextTileButton->setEnabled(QFile::exists(QDir(tileDirectory).filePath(QString("%1_out%2_out.jpg").arg(baseName).arg(currentTileIndex + 1)))); // Enable next button if the next tile exists
}
