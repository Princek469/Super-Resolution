#include "circularloader.h"

CircularLoader::CircularLoader(QWidget *parent) : QWidget(parent) {
    this->setFixedSize(100, 100);
    this->setStyleSheet("background-color: black; border: 5px solid white;");

    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 0); // Indeterminate mode
    progressBar->setValue(0);
    progressBar->setFixedSize(80, 80);
    progressBar->setStyleSheet("border: 3px dotted white; border-radius: 40px; background-color: black;");

    QVBoxLayout *progressLayout = new QVBoxLayout;
    progressLayout->addWidget(progressBar);
    progressLayout->setAlignment(Qt::AlignCenter);
    this->setLayout(progressLayout);

    this->setWindowFlags(Qt::WindowFlags()); // Remove window flags
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void CircularLoader::showLoader() {
    this->move(this->parentWidget()->width() / 2 - 50, this->parentWidget()->height() / 2 - 50);
    this->raise(); // Raise the progress widget to the top
    this->show();
}

void CircularLoader::hideLoader() {
    this->hide(); // Just hide the loader instead of deleting it
}
