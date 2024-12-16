#include "ShowSettingsDialog.h"
#include <QPalette>
#include <QFile>
#include <QTextStream>
#include <QPushButton>
#include <QVBoxLayout>

ShowSettingsDialog::ShowSettingsDialog(QWidget *parent) : QDialog(parent), settingsFilePath("settings.txt") {
    // Set up the dialog layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    settingsLabel = new QLabel(this);
    settingsLabel->setWordWrap(true); // Allow text to wrap
    settingsLabel->setStyleSheet("background-color:white; color:black;");

    // Set the background color of the dialog
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(240, 240, 240)); // Light gray background
    this->setPalette(palette);
    this->setAutoFillBackground(true); // Ensure the background color is applied

    // Set the text color of the label
    QPalette labelPalette = settingsLabel->palette();
    labelPalette.setColor(QPalette::WindowText, QColor(0, 0, 128)); // Dark blue text
    settingsLabel->setPalette(labelPalette);

    layout->addWidget(settingsLabel); // Add the label to the layout

    setLayout(layout);
    setWindowTitle("Settings"); // Set the window title

    // Load existing settings from the file
    loadSettings();
}

void ShowSettingsDialog::loadSettings() {
    QFile file(settingsFilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString settingsText;
        while (!in.atEnd()) {
            settingsText += in.readLine() + "\n"; // Read each line and append to settingsText
        }
        settingsLabel->setText(settingsText); // Set the label text to the loaded settings
        file.close();
    } else {
        settingsLabel->setText("No settings found."); // Display a message if no settings are found
    }
}

// void ShowSettingsDialog::saveSettings(const QString &settings) {
//     QFile file(settingsFilePath);
//     if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//         QTextStream out(&file);
//         out << settings; // Write the settings to the file
//         file.close();
//     }
// }
