#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
    QFileInfo fi("/media/463B-FA5B/DCIM/100PHOTO/IMG_0624.jpg");
    qDebug()<<fi.created().toString();
    qDebug()<<fi.lastModified().toString();
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui.retranslateUi(this);
        break;
    default:
        break;
    }
}


void MainWindow::on_actionClose_triggered()
{
    exit(0);
}

void MainWindow::on_chooseDestDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose destination directory"),
                                                        "",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
        if(!dir.isEmpty())
        {
            ui.destFolder->setText(dir);
            toStart();
        }
}

void MainWindow::on_chooseSorceFolder_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Source Directory"),
                                                        "",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
        if(!dir.isEmpty())
        {
            ui.sourceFolder->setText(dir);
            toStart();
        }
}

void MainWindow::toStart()
{
    QString sourceDir = ui.sourceFolder->text();
    QString destDir = ui.destFolder->text();
    if ( checkFolders(sourceDir) && checkFolders(destDir) )
        ui.start->setEnabled(true);
    else
        ui.start->setEnabled(false);

}

bool MainWindow::checkFolders(const QString &dirName)
{
    if (dirName.isEmpty())
        return false;
    QFileInfo fi(dirName);
    if ( ! fi.isDir())
    {
        QMessageBox::warning(0,  QObject::tr("It's not a directory"),
                             QObject::tr("%1\nPlease choose another directory.")
                             .arg(dirName));
        return false;
    }
    if ( ! fi.isWritable())
    {
        QMessageBox::warning(0,  QObject::tr("Directory write protected"),
                             QObject::tr("%1\nPlease choose another directory.")
                             .arg(dirName));
        return false;
    }
    return true;
}

void MainWindow::parseFolder(const QString &dirName)
{
    QDir dir(dirName);
    dir.setFilter(QDir::Files| QDir::Dirs| QDir::NoDotAndDotDot);
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList list = dir.entryInfoList();
    QDir destFolder(ui.destFolder->text());
    ui.progressBar->setMaximum(ui.progressBar->maximum() + list.size());
    ui.filesCount->setText(QString::number(ui.progressBar->maximum()));
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fi = list.at(i);
        if(fi.isDir()) {
            ui.progressBar->setValue(ui.progressBar->value() + 1);
            parseFolder(fi.absoluteFilePath());
        }
        else{
            QString created = fi.created().toString("M_yyyy");
            QFileInfo d(destFolder.absolutePath() + QDir::toNativeSeparators("/")+created);
            if (! d.exists() || ! d.isDir())
            {
                destFolder.mkdir(created);
            }
            QString file = d.absoluteFilePath() + QDir::toNativeSeparators("/")+fi.fileName();
            qDebug()<<file;
            QFile::copy(fi.absoluteFilePath(), file);
            ui.progressBar->setValue(ui.progressBar->value() + 1);
        }
    }
}

void MainWindow::on_start_clicked()
{
    ui.filesCount->setText("");
    parseFolder(ui.sourceFolder->text());
}
