#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currFile.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    QString fname = QFileDialog::getOpenFileName(this, "Open the file");

    QFile file(fname);
    currFile = fname;

    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
    }
    else
    {
        setWindowTitle(fname);

        QTextStream in(&file);

        QString txt = in.readAll();
        ui->textEdit->setText(txt);

        file.close();
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fname = QFileDialog::getSaveFileName(this, "Save as");

    QFile file(fname);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
    }
    else
    {
        currFile = fname;
        setWindowTitle(fname);

        QTextStream out(&file);
        QString txt = ui->textEdit->toPlainText();
        out << txt;

        file.close();


    }
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;

    printer.setPrinterName("PrinterName");

    QPrintDialog pDialog(&printer, this);

    if(pDialog.exec() == QDialog::Rejected)
    {
        QMessageBox::warning(this, "Warning", "Cannot access printer");
    }
    else
    {
        ui->textEdit->print(&printer);
    }
 }

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
