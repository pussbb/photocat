#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_actionClose_triggered();

    void on_chooseDestDir_clicked();

    void on_chooseSorceFolder_clicked();

    void on_start_clicked();

private:
    Ui::MainWindow ui;
    void toStart();
    bool checkFolders(const QString &dirName);
    void parseFolder(const QString &dirName);
};

#endif // MAINWINDOW_H
