#ifndef SHOWSETTINGSDIALOG_H
#define SHOWSETTINGSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

class ShowSettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit ShowSettingsDialog(QWidget *parent = nullptr);

private:
    void loadSettings(); // Method to load settings from a file
    QLabel *settingsLabel; // Label to display settings
    QString settingsFilePath; // Path to the settings file
};

#endif // SHOWSETTINGSDIALOG_H
