#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    this->setStyleSheet("QMenu{"
                        "   background: white;"
                        "   border: 1px solid #d9d9d9;"
                        "}"
                        "QMenu::Item{"
                        "   padding: 6px 24px 6px 24px;"
                        "}"
                        "QMenu::Item:selected{"
                        "   color: black;"
                        "   background: #cce8ff;"
                        "   border: 1px solid #a6d7ff"
                        "}");
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_actionAbout_triggered(){
    int year = QDate::currentDate().year();
    QMessageBox::about(this, "Notepad", QStringLiteral("© %1 Moses Odhiambo").arg(year));
}

void MainWindow::on_actionPrint_triggered(){
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle("Print");
    if (ui->textEdit->textCursor().hasSelection())
        dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if (dialog.exec() != QDialog::Accepted)
        return;
    ui->textEdit->print(&printer);
}

void MainWindow::on_actionFont_triggered(){
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Calibri", 12), this);
    if (ok)
        ui->textEdit->setFont(font);
}

void MainWindow::on_actionColor_triggered(){
    QColor color = QColorDialog::getColor(Qt::cyan, this);
    ui->textEdit->setTextColor(color);
}

void MainWindow::on_actionOpen_triggered(){
    QString filename = QFileDialog::getOpenFileName(this, "Open text file");

//    using namespace std;

//    fstream file(filename.toStdString(), ios::in | ios::binary | ios::ate);
//    streampos size = file.tellg();
//    char* memblock = new char [size];
//    file.seekg (0, ios::beg);
//    file.read (memblock, size);
//    file.close();
//    QString contents = QString::fromStdString(string(memblock));

//    ifstream file(filename.toStdString());
//    string line;
//    QString contents;
//    while(getline(file, line)){
//        contents += QString::fromStdString(line + '\n');
//    }

//    ui->textEdit->setText(contents);

    QFile file(filename);
    filedir = filename;
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Notepad","File not open");
        return;
    }
    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());
}

void MainWindow::on_actionUndo_triggered(){
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered(){
    ui->textEdit->redo();
}

void MainWindow::on_actionCut_triggered(){
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered(){
    ui->textEdit->paste();
}

void MainWindow::on_actionCopy_triggered(){
    ui->textEdit->copy();
}

void MainWindow::on_actionExit_triggered(){
    QApplication::quit();
}

void MainWindow::on_actionNew_triggered(){
    filedir = "";
    ui->textEdit->setText("");
}

void MainWindow::on_actionSave_triggered(){
    QFile file(filedir);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "File not open","Create a new file then click Save as.");
        return;
    }
    QTextStream out(&file);
    out<<ui->textEdit->toPlainText();
    file.flush();
    file.close();
}

void MainWindow::on_actionSave_As_triggered(){
    QString filename = QFileDialog::getSaveFileName(this, "Save file");
    QFile file(filename);
    filedir = filename;
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Notepad","File not saved.");
        return;
    }
    QTextStream out(&file);
    out<<ui->textEdit->toPlainText();
    file.flush();
    file.close();
}
