#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qtTranslator = new QTranslator(this);

    if(qtTranslator->load("qt_de", QLibraryInfo::path(QLibraryInfo::TranslationsPath)))
        qApp->installTranslator(qtTranslator);

    ui->setupUi(this);

    init();
}

void MainWindow::init()
{
    // this->statusBar()->showMessage("Bereit");

    statusLabel = new QLabel(this);

    statusLabel->setIndent(ui->verticalLayout->contentsMargins().left());

    this->statusBar()->addWidget(statusLabel, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionBEenden_triggered()
{
    close();
}

void MainWindow::on_actionFfnen_triggered()
{
    openFile();
}

void MainWindow::openFile()
{
    QString actDir;

    QString defaultFilter = "Textdokumente (*.txt)";

     actDir = currentFile.isEmpty() ? QDir::homePath() : QFileInfo(currentFile).absolutePath();

    QString filename = QFileDialog::getOpenFileName(this, "Textdokument öffnen",
                                 actDir, "Alle Dateien (*.*);;" + defaultFilter, &defaultFilter);

    if(!filename.isEmpty())
        readFile(filename);
}

void MainWindow::readFile(const QString &filename)
{
    // qDebug() << filename;

    QFile file(filename);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::critical(this, "Datei öffnen", QString("Die Datei '%1' konnte nicht geöffnet werden:\n%2")
                                                        .arg(filename).arg(file.errorString()));

        return;
    }

    QTextStream in(&file);

    ui->textEdit->setPlainText(in.readAll());

    file.close();

    setCurrentFile(filename);
}

void MainWindow::setCurrentFile(const QString &filename)
{
    currentFile = filename;

    // statusLabel->setText(filename);

    // statusLabel->setText(QDir::toNativeSeparators(filename));

    statusLabel->setText(QFileInfo(filename).fileName());
}

bool MainWindow::queryExit()
{
    return QMessageBox::No != QMessageBox::question(this, "Programm beenden", "Soll das Programm wirklich beendet werden",
                          QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    queryExit() ? event->accept() : event->ignore();
}

void MainWindow::on_actionAutomatischerZeilenumbruch_toggled(bool checked)
{
    ui->textEdit->setLineWrapMode(checked ? QTextEdit::WidgetWidth : QTextEdit::NoWrap);
}
