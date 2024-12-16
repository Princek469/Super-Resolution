#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <TileSettingsDialog.h>
#include "CustomMessageBox.h"
#include "circularloader.h"
#include "ShowSettingsDialog.h"
#include "SuperResolutionProcessor.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFuture>
#include <QProgressDialog>
#include <QProgressBar>
#include <QtConcurrent/QtConcurrent>
#include <QScrollArea>
#include <QScreen>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,defaultThresholdSizeMb(1), // Initialize with a default value
    defaultTileSize("256x256"),
    loader(new CircularLoader(this))
{
    ui->setupUi(this);
    this->setFixedSize(750, 550);
    superResolutionProcessor = new SuperResolutionProcessor(this);
    connect(superResolutionProcessor, &SuperResolutionProcessor::processFinished, this, &MainWindow::handleSuperResolutionResult);
    connect(ui->inputImagePathName, &QLineEdit::textChanged, this, &MainWindow::on_imagePathName_textChanged);
    ui->radioButton_2x->setEnabled(false);
    ui->radioButton_4x->setEnabled(false);
    QString stylesheet = QString("background-color: black;"); // light gray background
    this->setStyleSheet(stylesheet);
    connect(this, &MainWindow::showLoaderSignal, this, &MainWindow::showLoaderSlot);
    connect(this, &MainWindow::hideLoaderSignal, this, &MainWindow::hideLoaderSlot);

}

// ...
MainWindow::~MainWindow(){
    delete loader;
    delete ui;
}
// Slot Definitions
void MainWindow::showLoaderSlot() {
    loader->showLoader(); // Show the loader
}

void MainWindow::hideLoaderSlot() {
    loader->hideLoader(); // Hide the loader
}


void MainWindow::displayMessage(const QString& message, const QString& color, int duration) {
    ui->errorMessage->setText(message);
    ui->errorMessage->setStyleSheet("color: " + color + "; font-size: 14pt; font-weight: bold;");

    QTimer::singleShot(duration, this, [this]() {
        ui->errorMessage->clear();
    });
}




void MainWindow::on_chooseBtn_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files (*)");
    if (!filePath.isEmpty()) {
        ui->inputImagePathName->setText(filePath);
        inputImagePath = filePath; // Update the inputImagePath here

        // Load the image using QImage
        QImage qImage(filePath);
        if (!qImage.isNull()) {

            // Enable the radio buttons
            ui->radioButton_2x->setEnabled(true);
            ui->radioButton_4x->setEnabled(true);

            displayMessage("Image Selected Successfully", "green", 1000);
        }
    }
}

void MainWindow::on_InputViewBtn_clicked()
{
    QString filePath = ui->inputImagePathName->text();
    if (!filePath.isEmpty()) {
        if (QFile::exists(filePath)) {
            QPixmap image(filePath);
            if (!image.isNull()) {
                // Create a new QWidget to display the image
                inputImageView = new QWidget(nullptr); // Create as a top-level window
                inputImageView->setWindowTitle("Input Image");

                // Create a QLabel to display the image
                imageLabel = new QLabel(inputImageView);
                imageLabel->setStyleSheet("border: none; qproperty-alignment: AlignCenter;");
                imageLabel->setPixmap(image);
                imageLabel->setScaledContents(false); // Set this to false to display the image at its actual size

                // Set a scroll area to view the image
                QScrollArea *scrollArea = new QScrollArea(inputImageView);
                scrollArea->setWidget(imageLabel);
                scrollArea->setWidgetResizable(true);

                // Set the layout of the image window
                QVBoxLayout *layout = new QVBoxLayout;
                layout->addWidget(scrollArea);
                inputImageView->setLayout(layout);

                // Dynamically Adjust Window Size
                QSize screenSize = QApplication::primaryScreen()->size();
                int maxWidth = screenSize.width() * 0.8;  // Max 80% of screen width
                int maxHeight = screenSize.height() * 0.8; // Max 80% of screen height

                // Calculate scaled size preserving aspect ratio
                QSize scaledSize = image.size();
                scaledSize.scale(maxWidth, maxHeight, Qt::KeepAspectRatio);

                // Set the size of the image window
                inputImageView->setMinimumSize(QSize(300, 200)); // Set a fixed minimum size for the window
                inputImageView->resize(QSize(800, 600)); // Set the initial size of the window

                // Show the image window
                inputImageView->show();

            } else {
                displayMessage("Failed to load image.", "red", 2000);
            }
        } else {
            displayMessage("File does not exist. Please use correct file.", "red", 2000);
        }
    } else {
        displayMessage("No input path selected", "orange", 1000);
    }
}



void MainWindow::on_imagePathName_textChanged(const QString &arg1)
{
    if (!arg1.isEmpty()) {
        if (QFile::exists(arg1)) {
            inputImagePath = arg1; // Update the inputImagePath here

            // Enable the radio buttons
            ui->radioButton_2x->setEnabled(true);
            ui->radioButton_4x->setEnabled(true);
        } else {
            // Disable the radio buttons
            ui->radioButton_2x->setEnabled(false);
            ui->radioButton_4x->setEnabled(false);

            displayMessage("File does not exist. Please use correct file.", "red", 2000);
        }
    } else {
        // Disable the radio buttons
        ui->radioButton_2x->setEnabled(false);
        ui->radioButton_4x->setEnabled(false);
    }
}

void MainWindow::on_radioButton_2x_toggled(bool checked)
{
    if (checked) {
        // Enable the 2x scaling option
        scaleFactor = 2; // Store the scale factor in a member variable
    }
}

void MainWindow::on_radioButton_4x_toggled(bool checked)
{
    if (checked) {
        // Enable the 4x scaling option
        scaleFactor = 4; // Store the scale factor in a member variable
    }
}

void MainWindow::on_outputChooseBtn_clicked()
{
    // Open dialog box to select output file path
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Image Files (*.jpg)"));
    if (!filePath.isEmpty()) {
        outputImagePathName = filePath; // Update the class member variable
        ui->outputImagePathName->setText(outputImagePathName); // Display selected file path in lineEdit

        displayMessage("Destination Path Selected.", "green", 1000);
    }
}
void MainWindow::processImage(const QString &inputImagePath, const QString &outputImagePathName, int scaleFactor) {
    // Create a CircularLoader instance if not already created

    emit showLoaderSignal(); // Show the loader
    this->setWindowOpacity(0.5); // Dim the window
    this->setEnabled(false); // Disable the window

    // Process the image
    QThread *workerThread = new QThread;
    auto superResolutionProcessor = new SuperResolutionProcessor();
    superResolutionProcessor->moveToThread(workerThread);

    connect(workerThread, &QThread::started, [this, superResolutionProcessor, inputImagePath, outputImagePathName, scaleFactor]() {
        QString modelPath = QCoreApplication::applicationDirPath() + "/SuperResolution/weights/RealESRGAN_x4plus.pth";

        // Start the super-resolution processing
        superResolutionProcessor->runSuperResolution(inputImagePath, outputImagePathName, scaleFactor, "jpg", modelPath);
    });

    connect(superResolutionProcessor, &SuperResolutionProcessor::processFinished, this, [this, workerThread, superResolutionProcessor, outputImagePathName](bool success, const QString &message) {
        // Re-enable the window and hide the loader
        this->setWindowOpacity(1); // Restore opacity
        this->setEnabled(true); // Re-enable the window
        emit hideLoaderSignal(); // Hide the loader

        // Display success or error message
        if (success) {
            displayMessage("Image generated successfully ✅", "green", 2000);
            qDebug() << "Checking if output image exists at:" << outputImagePathName;

            // Check if the output image file exists
            if (QFile::exists(outputImagePathName)) {
                qDebug() << "Output image found, loading image.";
                // Load and display the image
            } else {
                qDebug() << "Output image not found.";
                displayMessage("Output image not found.", "red", 2000);
            }
        } else {
            qDebug() << "Processing failed with message:" << message;
            displayMessage(message, "red", 2000);
        }

        // Clean up
        workerThread->quit();
        workerThread->wait(); // Ensure the thread has finished before deleting
        superResolutionProcessor->deleteLater(); // Clean up the processor instance safely
    });

    connect(workerThread, &QThread::finished, workerThread, &QThread::deleteLater);
    workerThread->start();
}

void MainWindow::processTiles(const QString &destinationPath, int scaleFactor) {
    QDir dir(destinationPath);
    QStringList tileFiles = dir.entryList(QDir::Files);

    if (tileFiles.isEmpty()) {
        emit hideLoaderSignal(); // Hide the loader if no tiles are found
        this->setWindowOpacity(1); // Restore opacity
        this->setEnabled(true); // Re-enable the window
        emit processFinished(true, "No tiles found to process."); // Signal that processing is complete
        return;
    }

    emit showLoaderSignal(); // Show the loader
    this->setWindowOpacity(0.5); // Dim the window
    this->setEnabled(false); // Disable the window

    // Start processing the first tile
    processNextTile(0, tileFiles, dir, destinationPath, scaleFactor);
}

// Helper function to process tiles one by one
void MainWindow::processNextTile(int currentTileIndex, const QStringList &tileFiles, const QDir &dir, const QString &destinationPath, int scaleFactor) {
    if (currentTileIndex < tileFiles.size()) {
        QString tileFile = tileFiles[currentTileIndex];
        QString tilePath = dir.filePath(tileFile);

        // Define a single output directory for processed tiles
        QString processedFolderPath = destinationPath + "/processed" ; // Create a single folder for processed tiles

        // Ensure the processed folder exists
        // Define the processed tile path to save in the single processed folder
        QString processedTilePath = processedFolderPath; // Save in the same folder without "processed_" prefix

        qDebug() << "Processing tile:" << tilePath;

        // Create a new thread for processing this tile
        QThread *workerThread = new QThread;
        auto *superResolutionProcessor = new SuperResolutionProcessor();
        superResolutionProcessor->moveToThread(workerThread);

        // Connect signals and slots for processing
        connect(workerThread, &QThread::started, [=]() {
            QString modelPath = QCoreApplication::applicationDirPath() + "/SuperResolution/weights/RealESRGAN_x4plus.pth";
            superResolutionProcessor->runSuperResolution(tilePath, processedTilePath, scaleFactor, "jpg", modelPath);
        });

        connect(superResolutionProcessor, &SuperResolutionProcessor::processFinished, this, [=](bool success, const QString &message) {
            // Clean up the processor and thread
            superResolutionProcessor->deleteLater();
            workerThread->quit();
            workerThread->wait(); // Ensure the thread has finished

            if (success) {
                displayMessage(message, "green", 2000);
                // Process the next tile after the current one has finished
                processNextTile(currentTileIndex + 1, tileFiles, dir, destinationPath, scaleFactor);
            } else {
                displayMessage(message, "red", 2000);
                emit hideLoaderSignal(); // Hide the loader on error
                this->setWindowOpacity(1); // Restore opacity
                this->setEnabled(true); // Re-enable the window
                emit processFinished(false, "Processing stopped due to an error."); // Signal that processing failed
            }
        });

        connect(workerThread, &QThread::finished, workerThread, &QThread::deleteLater); // Clean up the thread
        workerThread->start(); // Start the worker thread for the tile
    } else {
        // All tiles have been processed
        emit hideLoaderSignal(); // Hide the loader when all tiles are processed
        this->setWindowOpacity(1); // Restore opacity
        this->setEnabled(true); // Re-enable the window
        emit processFinished(true, "All tiles processed successfully."); // Signal that processing is complete
    }
}

void MainWindow::splitImageWithDefaultSettings(const QString &inputImagePath, const QString &destinationPath, const QString &tileSize, double thresholdSizeMB) {
    // Disable the entire window and show the loader
    this->setEnabled(false);
    emit showLoaderSignal(); // Show the loader
    this->setWindowOpacity(0.5); // Dim the window

    // Ensure the destination path exists
    QDir dir(destinationPath);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qDebug() << "Error: Could not create destination directory.";
            QMessageBox::warning(this, "Error", "Could not create destination directory.");
            this->setEnabled(true);
            this->setWindowOpacity(1); // Restore opacity
            emit hideLoaderSignal(); // Hide the loader
            return;
        }
    }

    // Split the tileSize QString into width and height
    QStringList tileSizeList = tileSize.split("x");
    if (tileSizeList.size() != 2) {
        qDebug() << "Invalid tile size format. Please provide tile size in 'widthxheight' format.";
        this->setEnabled(true);
        this->setWindowOpacity(1); // Restore opacity
        emit hideLoaderSignal(); // Hide the loader
        return;
    }

    int tileWidth = tileSizeList[0].toInt();  // Width
    int tileHeight = tileSizeList[1].toInt(); // Height

    // Set output format and script path
    QString outputFormat = "jpg"; // Example: output as PNG
    QString pythonScriptPath = QCoreApplication::applicationDirPath() + "/split_image/image_split.py"; // Path to your Python script

    // Prepare arguments for the Python script
    QStringList arguments;
    arguments << pythonScriptPath
              << inputImagePath
              << QString::number(tileWidth)
              << QString::number(tileHeight)
              << destinationPath
              << outputFormat;

    // Create a new QProcess instance
    process = new QProcess(this);
    connect(process, &QProcess::finished, this, [=](int exitCode, QProcess::ExitStatus exitStatus) {
        // Cleanup and handle the result
        if (exitStatus == QProcess::NormalExit && exitCode == 0) {
            displayMessage("Image Split Successfully", "green", 1000);
            // Process each tile
            processTiles(destinationPath, scaleFactor); // Make sure scaleFactor is defined
        } else {
            qDebug() << "Error occurred while running the Python script";
            qDebug() << process->readAllStandardError();
            QMessageBox::warning(this, "Script Error", "Error occurred while running the Python script:\n" + process->readAllStandardError());
        }

        process->deleteLater(); // Clean up the process
        process = nullptr; // Reset the pointer
    });

    // Start the process
    process->start("python", arguments);
}
// Global flag to track whether split is confirmed

bool splitConfirmed = false;
void MainWindow::on_generateBtn_clicked() {
    // QString inputImagePath = ui->inputImagePathName->text();

    // Validate input image path
    if (!QFile::exists(inputImagePath)) {
        qDebug() << "Error: Input image path is invalid";
        displayMessage("Input image path is invalid", "orange", 1000);
        return;
    }

    // Validate destination path
    QString destinationPath = ui->outputImagePathName->text();
    if (destinationPath.isEmpty() || QFileInfo(destinationPath).suffix().isEmpty()) {
        qDebug() << "Error: Invalid destination path or file name.";
        //QMessageBox::warning(this, "Invalid Destination", "<font color='red'>Error: Please specify a valid destination file name.</font>");
        displayMessage("Please specify a valid destination file name", "orange", 1000);
        return;
    }


    // Check if the last output file already exists
    if (!lastOutputFilePath.isEmpty() && QFile::exists(lastOutputFilePath)) {
        displayMessage("File Already Exist", "orange", 1000);
        return;
    }

    // Get the input image file size
    QFile file(inputImagePath);
    file.open(QIODevice::ReadOnly);
    qint64 fileSize = file.size();
    double fileSizeMB = fileSize / (1024.0 * 1024.0); // Convert to MB
    file.close();

    // Get the current threshold size and tile size from settings
    QVariant thresholdVariant = currentSettings["thresholdSize"];
    double thresholdSizeMB = thresholdVariant.isValid() ? thresholdVariant.toDouble() : 1; // Default value if invalid
    QString tileSize = currentSettings["tileSize"].toString().trimmed(); // Trim whitespace

    if (tileSize.isEmpty()) {
        tileSize = "256x256"; // Default tile size
    }

    // Validate tile size format
    QRegularExpression regex("^(\\d+)x(\\d+)$");
    QRegularExpressionMatch match = regex.match(tileSize);
    if (!match.hasMatch()) {
        qDebug() << "Invalid tile size format.";
        QMessageBox::warning(this, "Invalid Tile Size", "<font color='red'>Invalid tile size format. Please provide tile size in 'widthxheight' format.</font>");
        return;
    }

    // Get the scaling factor from the selected radio button
    int scaleFactor = ui->radioButton_2x->isChecked() ? 2 : (ui->radioButton_4x->isChecked() ? 4 : 0);
    if (scaleFactor == 0) {
        qDebug() << "Error: Please select a scaling factor";
        QMessageBox::warning(this, "Scaling Factor Error", "<font color='red'>Error: Please select a scaling factor.</font>");
        return;
    }

    // If the image size is less than or equal to the threshold;
    if (fileSizeMB <= thresholdSizeMB) {
        // Process the image using the super resolution processor
        lastOutputFilePath = destinationPath; // Store the output file path
        processImage(inputImagePath, destinationPath, scaleFactor);
    } else {
        // If the image size is greater than the threshold and not confirmed
        if (!splitConfirmed) {
            CustomMessageBox msgBox("<font color='white' size='2'>Input image is greater than the threshold.<br>The input image will be divided into tiles.<br>Click Ok to proceed.<br>Click Cancel to change tile resolution in settings and continue.</font>", this);
            msgBox.setFixedSize(250, 150); // Adjusted size to fit all text
            if (msgBox.exec() == QDialog::Accepted) {
                // User clicked Ok, set the confirmation flag to true
                splitConfirmed = true;
                displayMessage("Please Click on Generate again for processing", "green", 1000);

            } else {
                // User clicked Cancel, reset the confirmation flag
                splitConfirmed = false;
            }
            return; // Wait for the user to click Generate again
        }

        // If the split has been confirmed (second click on Generate after OK or Continue), split the image
        if (splitConfirmed) {
            splitImageWithDefaultSettings(inputImagePath, destinationPath, tileSize, thresholdSizeMB);
            lastOutputFilePath = destinationPath; // Update the last output file path

            // After processing is done, stop the loader and show a completion message
            splitConfirmed = false;
        }
    }
}
void MainWindow::updateSettings(QString tileSize, double thresholdSizeMB) {
    currentSettings["tileSize"] = tileSize;
    currentSettings["thresholdSize"] = thresholdSizeMB;
    splitConfirmed = true; // Set the confirmation flag to true after updating settings
}

void MainWindow::handleSuperResolutionResult(bool success, const QString &message) {
    if (success) {
        QMessageBox::information(this, "Success", message);
    } else {
        QMessageBox::warning(this, "Error", message);
    }
}
void MainWindow::on_pushButton_clicked() {
    TileSettingsDialog settingsDialog(this);

    // Open the settings dialog
    if (settingsDialog.exec() == QDialog::Accepted) {
        // Load new settings from the dialog
        double newThresholdSizeMB = settingsDialog.getThresholdSize().toDouble();
        QString newTileSize = settingsDialog.getTileSize();

        // Save the new settings to the current settings object
        currentSettings["thresholdSize"] = newThresholdSizeMB;
        currentSettings["tileSize"] = newTileSize;

        // Notify the user that settings are saved
        displayMessage("New settings have been saved", "white", 1000);
    }
}

void MainWindow::on_outputImageViewBtn_clicked() {

    if (outputImagePathName.isEmpty()) {
        displayMessage("Please select an output path.", "orange", 1000);
        return; // Exit the function if the output path is not set
    }


    QString baseName = QFileInfo(inputImagePath).baseName(); // Assuming inputImagePath is accessible
    QString outputImagePath = QDir(outputImagePathName).filePath(baseName + "_out.jpg");


    // Check if the output image file exists
    if (!QFile::exists(outputImagePath)) {
        // Check if the processed directory exists
        QString tileDirectory = QDir(outputImagePathName).filePath("processed"); // Path to the processed folder
        if (QDir(tileDirectory).exists()) {
            // If the processed directory exists, check for tiles
            QStringList tileFiles = QDir(tileDirectory).entryList(QDir::Files);
            if (!tileFiles.isEmpty()) {
                // If there are tiles, open the tile viewer
                openTileViewer(tileDirectory, inputImagePath);
                return; // Exit the function after opening the tile viewer
            } else {
                displayMessage("No tiles found in the processed directory.", "red", 1000);
                return;
            }
        }
    }

    // Get the size of the output image file
    QFile file(outputImagePath);
    if (!file.open(QIODevice::ReadOnly)) {

        displayMessage("Failed to open the output image file.", "red", 1000);
        return;
    }
    qint64 fileSize = file.size();
    file.close();

    double fileSizeMB = fileSize / (1024.0 * 1024.0); // Convert to MB
    // Allow displaying images larger than 1 MB
    // You can adjust this condition as needed
    if (fileSizeMB > 10) { // Example: Allow images up to 5 MB
        displayMessage("Image size exceeds 5 MB, displaying in tile viewer.", "yellow", 1000);
        QString tileDirectory = QDir(outputImagePathName).filePath("processed");
        openTileViewer(tileDirectory, inputImagePath);
    } else {
        displaySingleImage(outputImagePath);
    }
}

void MainWindow::openTileViewer(const QString &tileDirectory, const QString &inputImageName) {

    if (tileDirectory.isEmpty()) {
        displayMessage("Output path not selected.", "red", 1000);
        return; // Exit the function if no path is selected
    }

    currentTileIndex = 0; // Initialize the index

    // Create a new QWidget to display tiles
    tileViewerWindow = new QWidget(nullptr); // Use 'this' as parent to manage memory
    tileViewerWindow->setWindowTitle("Tile Viewer");
    tileViewerWindow->resize(800, 600);
    QVBoxLayout *layout = new QVBoxLayout(tileViewerWindow);

    // Create a QScrollArea to handle large images
    QScrollArea *scrollArea = new QScrollArea(tileViewerWindow);
    scrollArea->setWidgetResizable(true); // Resize the widget inside the scroll area
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded); // Show horizontal scrollbar as needed
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); // Show vertical scrollbar as needed

    // Create a QLabel to display the tile
    tileLabel = new QLabel(scrollArea);
    tileLabel->setStyleSheet("border: none; qproperty-alignment: AlignCenter;");
    tileLabel->setAlignment(Qt::AlignCenter); // Center the image in the label
    scrollArea->setWidget(tileLabel); // Set the label as the scroll area's widget

    layout->addWidget(scrollArea); // Add the scroll area to the layout

    QPushButton *nextTileButton = new QPushButton("Show Next Tile", tileViewerWindow);
    nextTileButton->setFixedWidth(120);
    layout->addWidget(nextTileButton);

    QPushButton *previousButton = new QPushButton("Show Previous Tile", tileViewerWindow);
    previousButton->setFixedWidth(120);
    layout->addWidget(previousButton);

    // Construct the expected tile file names based on the input image name
    QString baseName = QFileInfo(inputImageName).baseName();
    QString tileFileName;

    // Function to load the current tile based on currentTileIndex
    auto loadTile = [=](int index) mutable {
        tileFileName = QString("%1_out%2_out.jpg").arg(baseName).arg(index);
        QString tilePath = QDir(tileDirectory).filePath(tileFileName);

        QPixmap tilePixmap(tilePath);
        if (!tilePixmap.isNull()) {
            tileLabel->setPixmap(tilePixmap);
            tileLabel->setScaledContents(true); // Scale the pixmap to fit the label
            tileLabel->adjustSize(); // Adjust the label size to the pixmap size
        } else {
            // Handle case where the tile does not exist
            displayMessage("No more tiles to display.", "orange", 1000);
            nextTileButton->setEnabled(false); // Disable button if no more tiles
        }
    };

    // Load the first tile
    loadTile(currentTileIndex);

    // Connect the Next button
    connect(nextTileButton, &QPushButton::clicked, this, [=]() mutable {
        currentTileIndex++;
        loadTile(currentTileIndex);
        previousButton->setEnabled(currentTileIndex > 0); // Enable previous button if not at first tile
    });

    // Connect the Previous button
    connect(previousButton, &QPushButton::clicked, this, [=]() mutable {
        if (currentTileIndex > 0) {
            currentTileIndex--;
            loadTile(currentTileIndex);
        }
        previousButton->setEnabled(currentTileIndex > 0); // Enable previous button if not at first tile
        nextTileButton->setEnabled(true); // Enable next button
    });

    // Enable/disable buttons based on the current index
    previousButton->setEnabled(false); // Initially disable the previous button

    tileViewerWindow->setLayout(layout);
    tileViewerWindow->show(); // Show the tile viewer window
}
void MainWindow::displaySingleImage(const QString &imagePath) {
    // Create a new QWidget to display the image
    imageWindow = new QWidget(nullptr);
    imageWindow->setWindowTitle("Output Image");

    // Create a QLabel to display the image
    imageLabel = new QLabel(imageWindow);
    imageLabel->setStyleSheet("border: none; qproperty-alignment: AlignCenter;");

    // Load the image from the output path
    QPixmap image(imagePath);
    if (image.isNull()) {
        qDebug() << "Failed to load the saved image from path:" << imagePath;
        displayMessage("Failed to load the saved image.", "red", 1000);
        return;
    }

    // Set the pixmap to the label
    imageLabel->setPixmap(image);
    imageLabel->setScaledContents(false); // Set to false to maintain aspect ratio

    // Create a QScrollArea to allow scrolling if the image is larger than the window
    QScrollArea *scrollArea = new QScrollArea(imageWindow);
    scrollArea->setWidget(imageLabel);
    scrollArea->setWidgetResizable(true); // Make the scroll area resizable

    // Set the layout of the image window
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(scrollArea);
    imageWindow->setLayout(layout);

    // Show the image window
    imageWindow->resize(800, 600); // Set an initial size for the window
    imageWindow->show();
}


void MainWindow::on_resetBtn_clicked() {
    // Clear input and output paths
    ui->inputImagePathName->clear();
    ui->outputImagePathName->clear();

    // Reset the output image view button
    ui->outputImageViewBtn->setEnabled(true);

    // Reset radio buttons for resolution
    ui->radioButton_2x->setChecked(false);
    ui->radioButton_4x->setChecked(false);
    scaleFactor = 0;

    // Reset resolved image and input image path
    inputImagePath.clear();
    lastOutputFilePath.clear();

    // Reset default threshold size and tile size
    defaultThresholdSizeMb = 1; // Reset to default value
    defaultTileSize = "256x256"; // Reset to default value

    // Reset current settings to default values
    currentSettings["thresholdSize"] = defaultThresholdSizeMb;
    currentSettings["tileSize"] = defaultTileSize;

    if(imageWindow){
        imageWindow->close();
        imageWindow = nullptr;
    }

    // Reset or close the image display window
    if (inputImageView) {
        inputImageView->close(); // Close the image display window
        inputImageView = nullptr; // Reset the pointer to null
    }

    if(tileViewerWindow){
        tileViewerWindow->close();
        tileViewerWindow = nullptr;
    }


    displayMessage("Reset everything, choose again", "green", 1000);
}
