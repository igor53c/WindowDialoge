#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTranslator>
#include <QLibraryInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionBEenden_triggered();

    void on_actionFfnen_triggered();

    void on_actionAutomatischerZeilenumbruch_toggled(bool arg1);

private:
    Ui::MainWindow *ui;

    QLabel* statusLabel;

    QTranslator* qtTranslator;

    QString currentFile;

    void init();

    void openFile();

    void readFile(const QString&);

    void setCurrentFile(const QString&);

    bool queryExit();

    void closeEvent(QCloseEvent*) override;
};
