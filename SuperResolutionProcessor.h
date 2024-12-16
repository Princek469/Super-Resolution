#ifndef SUPERRESOLUTIONPROCESSOR_H
#define SUPERRESOLUTIONPROCESSOR_H

#include <QObject>
#include <QProcess>

class SuperResolutionProcessor : public QObject {
    Q_OBJECT

public:
    explicit SuperResolutionProcessor(QObject *parent = nullptr);
    ~SuperResolutionProcessor(); // Destructor to clean up resources

    // Function to run the super resolution process
    void runSuperResolution(const QString &inputImagePath, const QString &outputImagePathName, int scale, const QString &extension, const QString &modelPath);

    // Function to set the model type (0 for 2x, 1 for 4x)
    void setModelType(int modelType);
    bool isRunning() const;
     void terminateProcess();

signals:
    // Signal emitted when the processing finishes
    void processFinished(bool success, const QString &message);

private slots:
    // Slot to handle the process finished event
    void handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    //void readStandardOutput();
    //void readStandardError();

private:
    QProcess *process; // Process to run the super resolution command
    QString modelPath; // To store the selected model path
    int selectedModelType; // 0 for 2x, 1 for 4x

    // Model paths
};

#endif // SUPERRESOLUTIONPROCESSOR_H
