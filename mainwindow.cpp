#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include<QTimer>
//#include<QDateTime>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
        ui->setupUi(this);
        ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::showTime()
//{
// ui->label_2->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));
// QDateTime current_time = QDateTime::currentDateTime();
// QString timestr = current_time.toString( "yyyy年MM月dd日  hh:mm:ss"); //Set the format of the display
// ui->label_2->setText(timestr); //Set the text content of the label as time
//}


void MainWindow::on_actionSLOT_triggered()
{
        ui->stackedWidget->setCurrentIndex(0);
        QProcess Slot;
        Slot.start("/opt/./SLOT ");
        Slot.waitForFinished(-1);
        Slot.close();
}

void MainWindow::on_actionUSB_IO_triggered()
{
       ui->stackedWidget->setCurrentIndex(0);
       QProcess IO;
       IO.start("/opt/./IO ");
       IO.waitForFinished(-1);
       IO.close();

}

void MainWindow::on_actionCAMERA_triggered()
{
       ui->stackedWidget->setCurrentIndex(0);
       QProcess Camera;
       Camera.start("/opt/CAMERA/./CAMERA >> file.log 2>&1");
       Camera.waitForFinished(-1);
       Camera.close();
}

void MainWindow::on_actionJ1_TOOLS_triggered()
{
       ui->stackedWidget->setCurrentIndex(0);
       QProcess J1Tool;
       J1Tool.start("/opt/J1Tool/./J1Tool >> file.log 2>&1");
       J1Tool.waitForFinished(-1);
       J1Tool.close();
}

void MainWindow::on_actionTerminal_triggered()
{
      ui->stackedWidget->setCurrentIndex(0);
      QApplication::quit();
}

void MainWindow::on_actionReboot_triggered()
{
      ui->stackedWidget->setCurrentIndex(0);
      QProcess Restart;
      Restart.start("reboot");
      Restart.waitForFinished(-1);
      Restart.close();
}

void MainWindow::on_actionPowerOff_triggered()
{
      ui->stackedWidget->setCurrentIndex(0);
      QProcess Poweroff;
      Poweroff.start("poweroff");
      Poweroff.waitForFinished(-1);
      Poweroff.close();
}

void MainWindow::on_actionNetwork_triggered()
{
     ui->stackedWidget->setCurrentIndex(1);

     //ip and subnetmask
     QProcess process1;
     QProcess process2;

    process1.setStandardOutputProcess(&process2);

    process1.start("ifconfig eth0");
    process2.start("grep \"inet addr\"");
    process2.setProcessChannelMode(QProcess::ForwardedChannels);

    bool retval = false;
    QByteArray buffer;
    while ((retval = process2.waitForFinished(-1)))
    buffer.append(process2.readAll());

    //qDebug() << "Bufferdata" << buffer;
    process1.close();
    process2.close();

    if(!(buffer==""))
    {

        QRegExp rx ("[0-9]{1,3}");
        QStringList captured;
        int pos = 0;

        while ((pos = rx.indexIn(buffer, pos)) != -1)
        {
        captured << rx.cap(0);
        pos+=rx.matchedLength();
        }

          //separate ip addres in xxx.xxx.xxx.xxx format
        QString last_ipaddr=captured[0]+"."+captured[1]+"."+captured[2]+"."+captured[3];
        QString last_submask=captured[8]+"."+captured[9]+"."+captured[10]+"."+captured[11];

        ui->label_IPValue->setText(last_ipaddr);
        ui->label_Subnetvalue->setText(last_submask);
      }
    else{
        ui->label_IPValue->setText("");
        ui->label_Subnetvalue->setText("");
    }

       //default gateway
       //Process to get DGW
       QProcess process1dg;
       QProcess process2dg;

       process1dg.setStandardOutputProcess(&process2dg);

       process1dg.start("ip r");
       process2dg.start("grep \"default\"");
       process2dg.setProcessChannelMode(QProcess::ForwardedChannels);

       bool retval2 = false;
       QByteArray buffer2;
       while ((retval2 = process2dg.waitForFinished(-1)))
       buffer2.append(process2dg.readAll());

           if(!(buffer2==""))
           {
               QRegExp rx ("[0-9]{1,3}");
               QStringList captureddgw;

               int pos = 0;

               while ((pos = rx.indexIn(buffer2, pos)) != -1)
               {
                   captureddgw << rx.cap(0);
                   pos+=rx.matchedLength();
               }


               process1dg.close();
               process2dg.close();

               QString  def_gateway = captureddgw[0]+"."+captureddgw[1]+"."+captureddgw[2]+"."+captureddgw[3];
               ui->label_GatewayValue->setText(def_gateway);
           }else{
            ui->label_GatewayValue->setText("");
           }
}

void MainWindow::on_pushButtonclose_released()
{
      ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionFonts_triggered()
{
      ui->stackedWidget->setCurrentIndex(0);
      QProcess Camera;
      Camera.start("/opt/FONTDEMO");
      Camera.waitForFinished(-1);
      Camera.close();

}
