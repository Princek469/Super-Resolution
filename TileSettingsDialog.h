#ifndef TILESETTINGSDIALOG_H
#define TILESETTINGSDIALOG_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class TileSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TileSettingsDialog(QWidget *parent = nullptr);
    ~TileSettingsDialog();

    QString getThresholdSize() const; // Getter for threshold size
    QString getTileSize() const;       // Getter for tile size
    void saveSettings() const; // Save settings to a file

signals:
    void settingsUpdated(); // Signal to notify that settings were updated

private slots:
    void onContinueClicked(); // Slot for handling continue button click

private:
    void loadSettings(); // Load settings from a file or default values
    //void saveSettings(const QJsonObject &settings) const; // Save settings to a file

    // UI components
    QLabel *thresholdLabel;
    QLineEdit *thresholdLineEdit;
    QLabel *tileSizeLabel;
    QLineEdit *tileSizeLineEdit;
    QPushButton *continueButton;
};

#endif // TILESETTINGSDIALOG_H

