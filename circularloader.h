#ifndef CIRCULARLOADER_H
#define CIRCULARLOADER_H

#include <QWidget>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QApplication>
#include <QThread>

class CircularLoader : public QWidget {
    Q_OBJECT

public:
    explicit CircularLoader(QWidget *parent = nullptr);
    void showLoader();
    void hideLoader();

private:
    QProgressBar *progressBar;
};

#endif // CIRCULARLOADER_H
