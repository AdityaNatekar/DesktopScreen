#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_actionSLOT_triggered();

    void on_actionUSB_IO_triggered();

    void on_actionCAMERA_triggered();

    void on_actionJ1_TOOLS_triggered();

    void on_actionTerminal_triggered();

    void on_actionReboot_triggered();

    void on_actionPowerOff_triggered();

//    void showTime();

    void on_actionNetwork_triggered();

    void on_pushButtonclose_released();

    void on_actionFonts_triggered();

private:
    Ui::MainWindow *ui;

//     QTimer *timer;
};
#endif // MAINWINDOW_H
