#include "SuperResolutionProcessor.h"
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QFile>
#include <QCoreApplication>

SuperResolutionProcessor::SuperResolutionProcessor(QObject *parent)
    : QObject(parent), process(new QProcess(this)) {
    connect(process, &QProcess::finished, this, &SuperResolutionProcessor::handleProcessFinished);

}

SuperResolutionProcessor::~SuperResolutionProcessor() {
    // Ensure the process is terminated if still running
    if (process) {
        if (process->state() == QProcess::Running) {
            process->terminate();
            process->waitForFinished();
        }
        process->deleteLater(); // Clean up the process
    }
}



bool SuperResolutionProcessor::isRunning() const {
    return process->state() == QProcess::Running;
}

void SuperResolutionProcessor::runSuperResolution(const QString &inputImagePath, const QString &outputImagePathName, int scale, const QString &extension, const QString &modelPath) {



    // Check if the process is already running
    if (isRunning()) {
        emit processFinished(false, "A process is already running.");
        return;
    }

    // Construct the command and arguments
    QString program = QCoreApplication::applicationDirPath() + "/SuperResolution/inference_realesrgan.exe"; // Corrected path
    QStringList arguments;
    arguments << "-i" << inputImagePath << "-s" << QString::number(scale);

    // Append output path if provided
    if (!outputImagePathName.isEmpty()) {
        arguments << "-o" << outputImagePathName;
    }

    // Append output extension if provided
    if (!extension.isEmpty()) {
        arguments << "--ext" << extension;
    }

    // Add the model path argument
    arguments << "--model_path" << modelPath;

    // Start the process with the program and arguments
    process->start(program, arguments);

    // Check if the process started successfully
    if (!process->waitForStarted()) {
        emit processFinished(false, "Failed to start process: " + process->errorString());
        return; // No need to delete the process here, it's managed by the QObject parent
    }
}

void SuperResolutionProcessor::terminateProcess() {
    if (process && process->state() == QProcess::Running) {
        qDebug() << "Terminating process...";
        process->terminate(); // Terminate the process
        if (!process->waitForFinished(3000)) { // Wait for 3 seconds
            process->kill(); // Force kill if it doesn't terminate
        }
        qDebug() << "Process terminated.";
    }
}
void SuperResolutionProcessor::handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus) {

    if (exitStatus == QProcess::CrashExit || exitCode != 0) {
        emit processFinished(false, "Error occurred while running super resolution:");
    } else {
        qDebug() << "Super resolution executed successfully.";
        emit processFinished(true, "Tiles Processes Successfully!");
    }
}

