// custommessagebox.cpp
#include "custommessagebox.h"

CustomMessageBox::CustomMessageBox(const QString& message, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Confirmation");
    setFixedSize(300, 150);

    messageLabel = new QLabel(message, this);
    messageLabel->setStyleSheet("background-color: black; color: white; font-weight: bold;");

    okButton = new QPushButton("OK", this);
    okButton->setStyleSheet("background-color: white; color: black; font-weight: bold;");
    cancelButton = new QPushButton("Cancel", this); // Initialize Cancel button
    cancelButton->setStyleSheet("background-color: white; color: black; font-weight: bold;");

    layout = new QVBoxLayout;
    layout->addWidget(messageLabel);
    layout->addWidget(okButton);
    layout->addWidget(cancelButton);

    setLayout(layout);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

CustomMessageBox::~CustomMessageBox()
{
    delete messageLabel;
    delete okButton;
    delete cancelButton;
    delete layout;
}
