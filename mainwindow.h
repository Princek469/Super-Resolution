#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QColor>
#include <QFuture>
#include <QProgressDialog>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDir>
#include <QVariantMap>
#include "CircularLoader.h" // Include your CircularLoader header
// #include "settingsdialog.h"
#include "SuperResolutionProcessor.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT // Ensure this macro is present

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void processNextTile(int currentTileIndex, const QStringList &tileFiles, const QDir &dir, const QString &destinationPath, int scaleFactor);
    void openTileViewer(const QString &tileDirectory, const QString &inputImageName);
    void displaySingleImage(const QString &imagePath);

signals:
    void showLoaderSignal();
    void hideLoaderSignal();
    void processingDoneSignal();
    void processFinished(bool success, const QString &message);

private slots:
    void on_chooseBtn_clicked();
    void on_InputViewBtn_clicked();
    void on_outputChooseBtn_clicked();
    void on_radioButton_2x_toggled(bool checked);
    void on_radioButton_4x_toggled(bool checked);
    void processImage(const QString &inputImagePath, const QString &outputImagePathName, int scaleFactor);
    void on_generateBtn_clicked();
    void handleSuperResolutionResult(bool success, const QString &message);
    void on_outputImageViewBtn_clicked();
    // void openTileViewer(const QString &tileDirectory, const QString &inputImageName);
    void on_imagePathName_textChanged(const QString &arg1);
    void on_resetBtn_clicked();
    void splitImageWithDefaultSettings(const QString& inputPath, const QString& outputPath, const QString& tileSize, double thresholdSizeMB);
    void processTiles(const QString &outputImagePathName, int scaleFactor);
    //void runSuperResolution(const QString &inputImagePath, const QString &outputFolder, int scale, const QString &extension);
    void on_pushButton_clicked();
    void showLoaderSlot(); // Slot to show the loader
    void hideLoaderSlot(); // Slot to hide the loader
    // void onWorkerFinished(bool success, const QString &message);


private:
    Ui::MainWindow *ui;
    QString inputImagePath;
    QString outputImagePathName;
    // QImage resolvedImage;
    int scaleFactor;     // Declare tileSize as a member variable
    QColor backgroundColor;
    QWidget *settingsWindow;
    QPushButton *settingsButton;
    double defaultThresholdSizeMb; // Declare the variable for threshold size
    QString defaultTileSize;
    SuperResolutionProcessor *superResolutionProcessor;
    QList<QString> tilePaths_; // Declare tilePaths_ here
    QVariantMap currentSettings;
    CircularLoader *loader; // Pointer to the CircularLoader instance
    void upscaleImage(int scale);
    void saveResolvedImage(QString folderPath);
    // void loadImage(const QString &imagePath);
    // void displayImage(QImage image);
    void displayMessage(const QString& message, const QString& color, int duration);
    void showProgressDialog();
    void hideProgressDialog();
    void setResizeMode();
    void onProcessingDone();
    void updateSettings(QString tileSize, double thresholdSizeMB);
     QProcess *process;
    QString destinationPath;
    QString lastOutputFilePath;
    QStringList tileFiles; // Member variable to store tile files
    int currentTileIndex;
     void loadTile(int index);
    QWidget *inputImageView = nullptr;
    QWidget *tileViewerWindow = nullptr;
     QWidget *imageWindow = nullptr;
    QLabel *imageLabel = nullptr;
     QLabel *tileLabel = nullptr;


};

#endif // MAINWINDOW_H

