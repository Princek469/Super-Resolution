// custommessagebox.h
#ifndef CUSTOMMESSAGEBOX_H
#define CUSTOMMESSAGEBOX_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class CustomMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit CustomMessageBox(const QString& message, QWidget* parent = nullptr);
    ~CustomMessageBox();

private:
    QLabel* messageLabel;
    QPushButton* okButton;
    QPushButton* cancelButton; // Add Cancel button
    QVBoxLayout* layout;

signals:
    void accepted(); // Emit signal when OK is clicked
};

#endif // CUSTOMMESSAGEBOX_H
