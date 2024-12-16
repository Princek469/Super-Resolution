#include "TileSettingsDialog.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSettings>

TileSettingsDialog::TileSettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    // Initialize UI components
    thresholdLabel = new QLabel("Threshold Size (MB):", this);
    thresholdLabel->setStyleSheet("background-color: black; color: white;");
    thresholdLineEdit = new QLineEdit(this);
    thresholdLineEdit->setStyleSheet("background-color: black; color: white;");


    tileSizeLabel = new QLabel("Tile Size (e.g., 256x256):", this);
    tileSizeLabel->setStyleSheet("background-color: black; color: white;");
    tileSizeLineEdit = new QLineEdit(this);
    tileSizeLineEdit->setStyleSheet("background-color: black; color: white;");

    continueButton = new QPushButton("Continue", this);
    continueButton->setStyleSheet("background-color: gray; color: black;");

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(thresholdLabel);
    layout->addWidget(thresholdLineEdit);
    layout->addWidget(tileSizeLabel);
    layout->addWidget(tileSizeLineEdit);
    layout->addWidget(continueButton);

    setLayout(layout);
    setWindowTitle("Tile Settings");

    // Load previously saved settings
    loadSettings();

    // Connect continue button with validation
    connect(continueButton, &QPushButton::clicked, this, &TileSettingsDialog::onContinueClicked);
}

TileSettingsDialog::~TileSettingsDialog() {}

void TileSettingsDialog::onContinueClicked()
{
    bool ok;
    double thresholdSize = getThresholdSize().toDouble(&ok);
    if (!ok || thresholdSize <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid positive number for threshold size.");
        return; // Do not accept the dialog
    }

    // Save settings when the dialog is accepted
    saveSettings();

    // Emit signal to indicate settings were updated
    emit settingsUpdated();

    QDialog::accept(); // Accept the dialog if validation passes
}

QString TileSettingsDialog::getThresholdSize() const
{
    return thresholdLineEdit->text();
}

QString TileSettingsDialog::getTileSize() const
{
    return tileSizeLineEdit->text();
}

void TileSettingsDialog::loadSettings()
{
    QSettings settings("MyCompany", "MyApp");

    QString threshold = settings.value("thresholdSize", "1").toString();
    QString tileSize = settings.value("tileSize", "256x256").toString();

    thresholdLineEdit->setText(threshold);
    tileSizeLineEdit->setText(tileSize);
}

void TileSettingsDialog::saveSettings() const
{
    QSettings settings("MyCompany", "MyApp");

    settings.setValue("thresholdSize", getThresholdSize());
    settings.setValue("tileSize", getTileSize());
}

